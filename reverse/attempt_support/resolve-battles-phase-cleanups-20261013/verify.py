"""Replay resolve-battles phase cleanups from the complete native parent graph."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/Common/Rva00576C4BDtor.cpp'
PARENTS = {
    '??1Rva00576C4B@@UAE@XZ': (0x576C4B, 186),
    '??0Rva00576C4B@@QAE@PAVRva00576B5E@@H@Z': (0x576DF1, 232),
}
CLEANUPS = {
    0x79B559: (11, '??1Rva00576C4B@@UAE@XZ'),
    0x79B5AD: (11, '??0Rva00576C4B@@QAE@PAVRva00576B5E@@H@Z'),
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
for name, rva, provider_source in [
    ('??1Rva005CD651@@UAE@XZ', 0x5CD6A9,
     'Code/GameEngine/Source/Common/Rva005CD651Dtor.cpp'),
]:
    provider_obj_path = build.obj_path(ROOT / provider_source)
    provider_obj = eh_verify.Obj(provider_obj_path)
    result = build.compile_function({'name': name, 'target_rva': hex(rva),
        'target_size': '67', 'source': provider_source, 'notes': ''},
        symbols, provider_obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    assert eh_verify.verify_row(image, provider_obj, name, rva) == ('EXACT', '')
    providers.append({'name': name, 'rva': hex(rva), 'size': 67,
                      'whole_body': 'EXACT', 'eh_graph': 'EXACT'})
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'providers': providers}, indent=2))
