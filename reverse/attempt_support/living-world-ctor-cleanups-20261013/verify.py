"""Replay complete LivingWorld constructor cleanup bytes from the exact real parent graph."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCtor.cpp'
PARENT = '??0Rva0022B12DSubsystem@@QAE@XZ'
CLEANUPS = {0x76DE7C: 14, 0x76DE8A: 14, 0x76DEFA: 14,
            0x76DF08: 14, 0x76DF16: 14}
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--rva', type=lambda value: int(value, 0), choices=CLEANUPS)
args = parser.parse_args()
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
assert eh_verify.verify_row(image, obj, PARENT, 0x213EEF) == ('EXACT', '')
locations = eh_verify.verified_funclet_locations(image, obj, PARENT, 0x213EEF)
symbols = build.load_symbol_map()
source = SOURCE.relative_to(ROOT).as_posix()
parent = build.compile_function({'name': PARENT, 'target_rva': '0x00213EEF',
                                'target_size': '355', 'source': source, 'notes': ''},
                               symbols, obj_path)
assert not parent['unresolved']
assert parent['bytes'] == parent['target']
proofs = []
for rva, size in CLEANUPS.items():
    if args.rva is not None and rva != args.rva:
        continue
    labels = [label for label, address in locations.items() if address == rva]
    assert len(labels) == 1, (hex(rva), labels)
    label = labels[0]
    notes = 'gen-funclet;parent=' + PARENT + ';object-symbol=' + label
    row = {'name': '?rva%08x@@YAXXZ' % rva, 'target_rva': hex(rva),
           'target_size': str(size), 'source': source, 'notes': notes}
    result = build.compile_function(row, symbols, obj_path)
    assert not result['unresolved'], (hex(rva), result['unresolved'])
    assert result['bytes'] == result['target'], hex(rva)
    raw, relocations = build.read_object_symbol_bytes(obj_path, label, size, code_only=True)
    relocations = [(offset, kind, name) for offset, kind, name in relocations if offset < size]
    targets = []
    for offset, kind, name in relocations:
        assert kind in (6, 20), (hex(rva), offset, kind, name)
        value = struct.unpack_from('<I', result['target'], offset)[0]
        address = (value - 0x400000) if kind == 6 else (rva + offset + 4 + struct.unpack_from('<i', result['target'], offset)[0])
        targets.append({'offset': offset, 'kind': kind, 'name': name,
                        'native_target_rva': hex(address)})
    proofs.append({'rva': hex(rva), 'size': size, 'label': label,
                   'full_bytes': result['bytes'].hex(), 'relocations': targets})
print(json.dumps({'parent': PARENT, 'parent_size': 355,
                  'parent_full_bytes': 'EXACT', 'eh_graph': 'EXACT',
                  'cleanups': proofs}, indent=2))
