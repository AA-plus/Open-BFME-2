"""Compare caller behavior with retail using an identical recorded scale stub."""
import hashlib, json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *

source = Path(sys.argv[1] if len(sys.argv) > 1 else 'reverse/attempts/0x001baf30.cpp').resolve()
compiled, relocs = build.read_object_symbol_bytes(build.obj_path(source), '_AnyRatioFrameScale')
retail = build.read_target_bytes(0x1BAF30, 606)
CODE, HELPER, CONTEXT, FRAME, CONFIG, Y, U, V, STACK, RETURN = (
    0x110000, 0x10FD70, 0x200000, 0x300000, 0x400000,
    0x500000, 0x600000, 0x700000, 0x800000, 0x11F000)
patched = bytearray(compiled)
assert len(relocs) == 3
for offset, kind, name in relocs:
    assert kind == 20 and name == '_AnyRatio_2D_Scale'
    assert struct.unpack_from('<i', patched, offset)[0] == 0
    struct.pack_into('<i', patched, offset, HELPER - (CODE + offset + 4))
saved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_EBP: 0x87654321,
         UC_X86_REG_ESI: 0x456789AB, UC_X86_REG_EDI: 0xABCDEF01}

def fill(output, destination, pitch, width, height, index):
    plane, offset = divmod(destination - Y, 0x100000)
    assert 0 <= plane < 3 and 0 <= width < 128 and 0 <= height < 128
    for row in range(height):
        start = offset + row * pitch
        output[plane][start:start + width] = bytes([(index * 37 + row + 1) & 255]) * width

def run(code, context, config, initial, result):
    emulator = Uc(UC_ARCH_X86, UC_MODE_32)
    emulator.mem_map(0x100000, 0x20000)
    for address in (CONTEXT, FRAME, CONFIG, Y, U, V, STACK):
        emulator.mem_map(address, 0x10000)
    emulator.mem_write(CODE, bytes(code)); emulator.mem_write(HELPER, b'\xc3')
    emulator.mem_write(CONTEXT, bytes(context)); emulator.mem_write(CONFIG, config)
    for address, contents in zip((Y, U, V), initial): emulator.mem_write(address, contents)
    initial_sp = STACK + 0xF000
    emulator.mem_write(initial_sp, struct.pack('<IIIIII', RETURN, CONTEXT, FRAME, CONFIG, 5, 3))
    emulator.reg_write(UC_X86_REG_ESP, initial_sp)
    for register, value in saved.items(): emulator.reg_write(register, value)
    calls = []
    def stub(uc, address, size, data):
        if address != HELPER: return
        sp = uc.reg_read(UC_X86_REG_ESP)
        args = struct.unpack('<9I', bytes(uc.mem_read(sp + 4, 36)))
        calls.append(args)
        output = [bytearray(uc.mem_read(p, 0x10000)) for p in (Y, U, V)]
        fill(output, args[5], args[6], args[7], args[8], len(calls))
        for p, contents in zip((Y, U, V), output): uc.mem_write(p, bytes(contents))
        target = struct.unpack('<I', bytes(uc.mem_read(sp, 4)))[0]
        uc.reg_write(UC_X86_REG_EAX, result if len(calls) == 1 else 123)
        uc.reg_write(UC_X86_REG_ECX, 0xDEADBEEF); uc.reg_write(UC_X86_REG_EDX, 0xCAFEBABE)
        uc.reg_write(UC_X86_REG_ESP, sp + 4); uc.reg_write(UC_X86_REG_EIP, target)
    emulator.hook_add(UC_HOOK_CODE, stub, begin=HELPER, end=HELPER)
    emulator.emu_start(CODE, RETURN, timeout=3000000, count=1000000)
    assert emulator.reg_read(UC_X86_REG_EIP) == RETURN
    assert emulator.reg_read(UC_X86_REG_ESP) == initial_sp + 4
    assert all(emulator.reg_read(reg) == val for reg, val in saved.items())
    assert bytes(emulator.mem_read(CONTEXT, len(context))) == bytes(context)
    assert bytes(emulator.mem_read(CONFIG, len(config))) == config
    assert bytes(emulator.mem_read(FRAME, 0x10000)) == bytes(0x10000)
    return calls, [bytes(emulator.mem_read(p, 0x10000)) for p in (Y, U, V)], emulator.reg_read(UC_X86_REG_EAX)

results = []
for width, height in ((11, 7), (32, 24)):
    for hs, hr in ((1, 1), (2, 3), (4, 5), (3, 2)):
        for vs, vr in ((1, 1), (2, 3), (4, 5), (3, 2)):
            for result in (0, 7):
                context = bytearray(0xB8)
                fields = {0x40: 96, 0x58: hs, 0x5C: hr, 0x60: vs, 0x64: vr,
                          0x70: width, 0x74: height, 0x78: 1000, 0x7C: 14000, 0x80: 28000, 0xB4: 16}
                for offset, value in fields.items(): struct.pack_into('<I', context, offset, value)
                config = struct.pack('<9I', width, height, 128, (width+1)//2, (height+1)//2, 64, Y, U, V)
                initial = [bytes([0xA5 + i]) * 0x10000 for i in range(3)]
                sw = (width * hr + hs - 1) // hs; sh = (height * vr + vs - 1) // vs
                pw = ((sw + (3 if hr == 3 else 8) - 1) // (3 if hr == 3 else 8)) * (3 if hr == 3 else 8) * hs // hr
                ph = ((sh + (3 if vr == 3 else 8) - 1) // (3 if vr == 3 else 8)) * (3 if vr == 3 else 8) * vs // vr
                expected_calls = [(CONTEXT, FRAME+1000, 128, sw, sh, Y+5, 128, width, height)]
                expected = [bytearray(p) for p in initial]
                fill(expected, Y+5, 128, width, height, 1)
                for row in range(ph):
                    start = 5 + row * 128 + width
                    expected[0][start:start+pw-width] = bytes(pw-width)
                for row in range(height, ph):
                    start = 5 + row * 128
                    expected[0][start:start+pw] = bytes(pw)
                if result:
                    for index, (offset, plane) in enumerate(((14000, U), (28000, V)), 2):
                        args = (CONTEXT, FRAME+offset, 64, (sw+1)//2, (sh+1)//2, plane+3, 64, (width+1)//2, (height+1)//2)
                        expected_calls.append(args); fill(expected, args[5], args[6], args[7], args[8], index)
                expected = (expected_calls, [bytes(p) for p in expected], result)
                assert run(retail, context, config, initial, result) == expected, ('retail', fields, result)
                assert run(patched, context, config, initial, result) == expected, ('bank', fields, result)
                results.append({'width': width, 'height': height, 'horizontal': [hs, hr], 'vertical': [vs, vr], 'luma_result': result})
report = {'target_rva': '0x001BAF30', 'retail_bytes': len(retail), 'compiled_bytes': len(compiled),
          'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
          'compiled_sha256': hashlib.sha256(compiled).hexdigest(), 'relocations': relocs,
          'coverage': '64 positive dimension caller cases with a shared scale stub; arguments, destination padding, return, context, config, frame, cdecl stack and saved registers; not callee behavior or byte exactness', 'cases': results}
output = Path(sys.argv[2] if len(sys.argv) > 2 else 'build/resume-anyratio-bank-emulation-20261012.json')
output.write_bytes((json.dumps(report, indent=2)+'\n').encode())
print('PASS', len(results), 'caller cases against retail and independent spec oracle; byte exactness remains incomplete')
