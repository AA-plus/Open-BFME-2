"""Replay full army-constructor cleanups using both exact real parent graphs."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldArmy.cpp'
PARENTS = {
    'default': ('??0LivingWorldArmy@@QAE@XZ', 0x31A257, 283),
    'arguments': ('??0LivingWorldArmy@@QAE@HPAVRva004E3184@@PAURva002B6A04Player@@@Z', 0x31A372, 543),
}
CLEANUPS = {0x77AA4A: (11, 'default'), 0x77AA55: (14, 'default'),
            0x77AA63: (10, 'default'), 0x77AAE2: (11, 'arguments'),
            0x77AAED: (14, 'arguments'), 0x77AAFB: (10, 'arguments')}
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--rva', type=lambda value: int(value, 0), choices=CLEANUPS)
args = parser.parse_args()
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
symbols = build.load_symbol_map()
source = SOURCE.relative_to(ROOT).as_posix()
locations, parents = {}, []
for key, (name, rva, size) in PARENTS.items():
    assert eh_verify.verify_row(image, obj, name, rva) == ('EXACT', '')
    locations[key] = eh_verify.verified_funclet_locations(image, obj, name, rva)
    result = build.compile_function({'name': name, 'target_rva': hex(rva),
                                     'target_size': str(size), 'source': source, 'notes': ''},
                                    symbols, obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    parents.append({'name': name, 'size': size, 'full_bytes': 'EXACT', 'eh_graph': 'EXACT'})
proofs = []
for rva, (size, parent_key) in CLEANUPS.items():
    if args.rva is not None and rva != args.rva:
        continue
    parent = PARENTS[parent_key][0]
    labels = [name for name, address in locations[parent_key].items() if address == rva]
    assert len(labels) == 1, (hex(rva), labels)
    label = labels[0]
    row = {'name': '?rva%08x@@YAXXZ' % rva, 'target_rva': hex(rva),
           'target_size': str(size), 'source': source,
           'notes': 'gen-funclet;parent=' + parent + ';object-symbol=' + label}
    result = build.compile_function(row, symbols, obj_path)
    assert not result['unresolved'], (hex(rva), result['unresolved'])
    assert result['bytes'] == result['target'], hex(rva)
    raw, relocations = build.read_object_symbol_bytes(obj_path, label, size, code_only=True)
    relocations = [(offset, kind, name) for offset, kind, name in relocations if offset < size]
    assert len(relocations) == 1 and relocations[0][1] == 20, relocations
    offset, kind, callee = relocations[0]
    target = rva + offset + 4 + struct.unpack_from('<i', result['target'], offset)[0]
    proofs.append({'rva': hex(rva), 'size': size, 'parent': parent, 'label': label,
                   'full_bytes': result['bytes'].hex(), 'callee': callee,
                   'native_callee_rva': hex(target)})
print(json.dumps({'parents': parents, 'cleanups': proofs}, indent=2))
