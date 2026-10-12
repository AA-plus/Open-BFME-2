"""Differentially check the clean-room draft against retail and a spec oracle."""
from pathlib import Path
import hashlib
import json
import random
import struct
import sys
sys.path.insert(0, 'tools')
import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import *

source = Path(sys.argv[1] if len(sys.argv) > 1 else 'reverse/attempts/0x001d4d50.cpp').resolve()
compiled, relocs = build.read_object_symbol_bytes(build.obj_path(source), '_MMX_idct10_DX')
retail = build.read_target_bytes(0x1D4D50, 1034)
CODE, RETURN, TABLE, INPUT, QUANT, OUTPUT, STACK = 0x110000, 0x11F000, 0xE22980, 0x200000, 0x210000, 0x220000, 0x300000
patched = bytearray(compiled)
for offset, kind, name in relocs:
    assert kind == 6 and name == '?Rva009B3A00Table@@3PAGA', (offset, kind, name)
    addend = struct.unpack_from('<I', patched, offset)[0]
    struct.pack_into('<I', patched, offset, TABLE + addend)
assert all(i.mnemonic != 'emms' for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(compiled, CODE))
constants = [0] * 16
for index in (0, 5, 10, 15): constants[index] = 65535
for value in (64277, 60547, 54491, 46341, 36410, 25080, 12785): constants.extend([value] * 4)
constants.extend([8] * 4)
table_bytes = struct.pack('<48H', *constants)
saved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_EBP: 0x87654321,
         UC_X86_REG_ESI: 0x456789AB, UC_X86_REG_EDI: 0xABCDEF01}
retail_extra = {UC_X86_REG_ECX: 0x11223344, UC_X86_REG_EDX: 0x55667788}

def sat(x): return min(32767, max(-32768, x))
def wrap(x): return ((x + 32768) & 65535) - 32768

def inverse(values, rounding):
    i0, i1, i2, i3 = values
    mul = lambda value, cosine: (value * cosine) // 65536
    a, b, c, d = mul(i1, 64277), mul(i1, 12785), mul(i3, 54491), sat(-mul(i3, 36410))
    odd_ds, odd_dm = sat(a - c), sat(b - d)
    odd_ss, odd_sm = sat(sat(c + c) + odd_ds), sat(sat(d + d) + odd_dm)
    rot_s, rot_m, even = mul(odd_ds, 46341), mul(odd_dm, 46341), mul(i0, 46341)
    ps, pd = mul(i2, 60547), mul(i2, 25080)
    ea, oa, fa = sat(even - ps), sat(rot_m - pd), sat(even - rot_s)
    eb, ob, fb = sat(sat(ps + ps) + ea), sat(sat(pd + pd) + oa), sat(sat(rot_s + rot_s) + fa)
    result = [0] * 8
    for low, high, left, right in ((7, 0, eb, odd_ss), (2, 1, fb, ob), (4, 3, ea, odd_sm), (6, 5, fa, oa)):
        diff = sat(left - right)
        if rounding: diff = sat(diff + 8)
        total = sat(sat(right + right) + diff)
        result[low] = diff >> 4 if rounding else diff
        result[high] = total >> 4 if rounding else total
    return result

def oracle(coefficient, quantizer):
    rows = [[0] * 8 for _ in range(8)]
    for row in range(4):
        values = [wrap(coefficient[8 * col + row] * quantizer[8 * col + row]) for col in range(4)]
        rows[row] = inverse(values, False)
    result = [[0] * 8 for _ in range(8)]
    for col in range(8):
        values = inverse([rows[row][col] for row in range(4)], True)
        for row, value in enumerate(values): result[row][col] = value
    return [value for row in result for value in row]

def run(code, coefficients, quantizer, alias):
    emulator = Uc(UC_ARCH_X86, UC_MODE_32)
    emulator.mem_map(0x100000, 0x20000)
    for address in (0xE20000, INPUT, QUANT, OUTPUT, STACK): emulator.mem_map(address, 0x10000)
    emulator.mem_write(CODE, bytes(code)); emulator.mem_write(TABLE, table_bytes)
    initial = {}
    for address, data in ((INPUT, coefficients), (QUANT, quantizer), (OUTPUT, [0x1234] * 64)):
        contents = b'\xA5' * 16 + struct.pack('<64h', *data) + b'\x5A' * 16
        emulator.mem_write(address, contents); initial[address] = contents
    destination = {'none': OUTPUT, 'input': INPUT, 'quantizer': QUANT}[alias] + 16
    sp = STACK + 0xF000
    emulator.mem_write(sp, struct.pack('<4I', RETURN, INPUT + 16, QUANT + 16, destination))
    emulator.reg_write(UC_X86_REG_ESP, sp)
    for register, value in saved.items(): emulator.reg_write(register, value)
    for register, value in retail_extra.items(): emulator.reg_write(register, value)
    emulator.emu_start(CODE, RETURN, timeout=3000000, count=100000)
    assert emulator.reg_read(UC_X86_REG_EIP) == RETURN
    assert emulator.reg_read(UC_X86_REG_ESP) == sp + 4
    assert all(emulator.reg_read(reg) == value for reg, value in saved.items())
    assert bytes(emulator.mem_read(TABLE, 96)) == table_bytes
    for address, contents in initial.items():
        actual = bytes(emulator.mem_read(address, len(contents)))
        assert actual[:16] == contents[:16] and actual[-16:] == contents[-16:]
        if address + 16 != destination: assert actual == contents
    return list(struct.unpack('<64h', bytes(emulator.mem_read(destination, 128)))), all(emulator.reg_read(reg) == value for reg, value in retail_extra.items())

def case(entries, quant=None):
    coefficients = [0] * 64
    for (row, col), value in entries.items(): coefficients[8 * col + row] = value
    return coefficients, quant if quant is not None else [1] * 64

vectors = [case({}), case({(0, 0): 64}), case({(0, 0): -64}), case({(0, 1): 64}), case({(1, 0): 64}),
    case({(0, 0): 100, (0, 1): -70, (1, 0): 50, (1, 1): -30, (2, 0): 20}),
    case({(0, 0): 32767, (0, 1): 32767, (1, 0): -32768, (0, 2): 32767, (2, 0): 32767})]
positions = ((0, 0), (0, 1), (1, 0), (2, 0), (1, 1), (0, 2), (0, 3), (1, 2), (2, 1), (3, 0))
rng = random.Random(0x1D4D50)
for amplitude in (1, 64, 32767):
    for unused in range(25):
        vector = case({position: rng.randint(-amplitude, amplitude) for position in positions}, [rng.randint(-32768, 32767) for _ in range(64)])
        # Unread input slots contain nonzero data; six loaded but unsupported
        # coefficients inside the four spans remain zero as the spec requires.
        for index in range(64):
            if index not in [8 * col + row for col in range(4) for row in range(4)]: vector[0][index] = rng.randint(-32768, 32767)
        vectors.append(vector)
count = 0
draft_extra_preserved = 0
for index, (coefficients, quantizer) in enumerate(vectors):
    expected = oracle(coefficients, quantizer)
    for alias in ('none', 'input', 'quantizer'):
        native, native_extra = run(retail, coefficients, quantizer, alias)
        draft, draft_extra = run(patched, coefficients, quantizer, alias)
        assert native_extra, ('retail extra saved-register contract', index, alias)
        draft_extra_preserved += int(draft_extra)
        assert native == expected, ('retail-oracle', index, alias, native, expected)
        assert draft == native, ('draft-retail', index, alias, draft, native)
        count += 1
report = {'target_rva': '0x001D4D50', 'retail_bytes': len(retail), 'compiled_bytes': len(compiled),
    'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
    'compiled_sha256': hashlib.sha256(compiled).hexdigest(), 'relocations': relocs, 'cases': count,
    'retail_extra_ecx_edx_preserved_cases': count, 'draft_extra_ecx_edx_preserved_cases': draft_extra_preserved,
    'coverage': '82 supported-domain vectors times 3 destination alias layouts: complete 64-word result, cdecl stack, nonvolatile registers, input/quantizer preservation, canaries, constant table; independent spec arithmetic and retail; not byte exactness or exhaustive behavior. Retail preserves extra volatile ECX/EDX registers, draft does not reproduce that stronger contract.'}
output = Path(sys.argv[2] if len(sys.argv) > 2 else 'build/mmx-idct10-banked-emulation-20261012.json')
output.write_bytes((json.dumps(report, indent=2) + '\n').encode())
print('PASS', count, 'retail + independent spec + draft differential cases;', len(compiled), '/', len(retail), 'bytes, nonexact')
