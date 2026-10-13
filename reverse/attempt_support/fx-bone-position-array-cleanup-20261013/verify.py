"""Replay bone-position array cleanup from the complete native parent graph."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameClient/FXListAtBonePosFXNugget_doFxAtBones.cpp'
PARENTS = {
    '?doFxAtBones@FXListAtBonePosFXNugget@@IBEXPBVObject@@H@Z': (0x1E2DD6, 283),
}
CLEANUPS = {
    0x769E44: (22, '?doFxAtBones@FXListAtBonePosFXNugget@@IBEXPBVObject@@H@Z'),
}

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--rva', type=lambda value: int(value, 0), choices=CLEANUPS)
args = parser.parse_args()
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
symbols = build.load_symbol_map()
source = SOURCE.relative_to(ROOT).as_posix()
locations, parents, cleanups = {}, [], []
for parent, (rva, size) in PARENTS.items():
    assert eh_verify.verify_row(image, obj, parent, rva) == ('EXACT', '')
    locations[parent] = eh_verify.verified_funclet_locations(image, obj, parent, rva)
    result = build.compile_function({'name': parent, 'target_rva': hex(rva),
                                    'target_size': str(size), 'source': source, 'notes': ''},
                                   symbols, obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    parents.append({'name': parent, 'rva': hex(rva), 'size': size,
                    'whole_body': 'EXACT', 'eh_graph': 'EXACT'})
for rva, (size, parent) in CLEANUPS.items():
    if args.rva is not None and rva != args.rva:
        continue
    labels = [label for label, address in locations[parent].items() if address == rva]
    assert len(labels) == 1, (hex(rva), labels)
    label = labels[0]
    notes = 'gen-funclet;parent=' + parent + ';object-symbol=' + label
    result = build.compile_function({'name': '?rva%08x@@YAXXZ' % rva,
                                    'target_rva': hex(rva), 'target_size': str(size),
                                    'source': source, 'notes': notes}, symbols, obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    raw, relocations = build.read_object_symbol_bytes(obj_path, label, size, code_only=True)
    targets = []
    for offset, kind, name in relocations:
        if offset >= size:
            continue
        assert kind in (6, 20)
        address = (struct.unpack_from('<I', result['target'], offset)[0] - 0x400000
                   if kind == 6 else rva + offset + 4 +
                   struct.unpack_from('<i', result['target'], offset)[0])
        targets.append({'offset': offset, 'kind': kind, 'name': name,
                        'native_target_rva': hex(address)})
    cleanups.append({'rva': hex(rva), 'size': size, 'label': label,
                     'full_bytes': result['bytes'].hex(), 'relocations': targets})
providers = []
for name, rva, size, provider_source in [
    ('??0Coord3D@@QAE@XZ', 0x47A6A9, 3,
     'Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp'),
    ('??1Coord3D@@QAE@XZ', 0xB3FD0, 1,
     'Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp'),
]:
    provider_obj_path = build.obj_path(ROOT / provider_source)
    provider_obj = eh_verify.Obj(provider_obj_path)
    assert name in provider_obj.by_name
    result = build.compile_function({'name': name, 'target_rva': hex(rva),
        'target_size': str(size), 'source': provider_source, 'notes': ''},
        symbols, provider_obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    assert eh_verify.verify_row(image, provider_obj, name, rva) is None
    providers.append({'name': name, 'rva': hex(rva), 'size': size,
                      'whole_body': 'EXACT', 'eh_graph': 'absent on both sides'})
row = {'name': '??_M@YGXPAXIHP6EX0@Z@Z', 'target_rva': '0x00629110',
       'target_size': '96', 'source': 'vendor/msvc71crt/msvcrt.lib',
       'notes': 'member=build/intel/dll_obj/ehvecdtr.obj'}
# The committed archive uses backslashes in its member name.
row['notes'] = row['notes'].replace('/', chr(92))
lib_obj = build.obj_path(ROOT / row['source'], build.ledger_member(row))
result = build.compile_function(row, symbols, lib_obj)
assert not result['unresolved']
assert result['bytes'] == result['target']
providers.append({'name': row['name'], 'rva': row['target_rva'], 'size': 96,
                  'whole_body': 'EXACT', 'provenance': row['source'] + ';' + row['notes']})
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'providers': providers}, indent=2))
