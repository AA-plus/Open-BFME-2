"""Replay Beacon local cleanups using all three exact real parent graphs."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdate.cpp'
PARENTS = {'?createParticleSystem@@YA?AVBfmeParticleSystemHandle@@PAVDrawable@@@Z': (0x4C9674, 355),
           '?hideBeacon@BeaconClientUpdate@@QAEXXZ': (0x4C97D7, 216),
           '?clientUpdate@BeaconClientUpdate@@UAEXXZ': (0x4C98AF, 225)}
CLEANUPS = {0x79050A: (8, '?createParticleSystem@@YA?AVBfmeParticleSystemHandle@@PAVDrawable@@@Z'),
            0x790524: (8, '?hideBeacon@BeaconClientUpdate@@QAEXXZ'),
            0x79052C: (8, '?hideBeacon@BeaconClientUpdate@@QAEXXZ'),
            0x79053E: (8, '?clientUpdate@BeaconClientUpdate@@UAEXXZ')}

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--rva', type=lambda value: int(value, 0), choices=CLEANUPS)
args = parser.parse_args()
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
symbols = build.load_symbol_map()
source = SOURCE.relative_to(ROOT).as_posix()
provider = build.compile_function({'name': '??1BfmeParticleSystemHandle@@QAE@XZ',
                                   'target_rva': '0x002115C5', 'target_size': '11',
                                   'source': source, 'notes': ''}, symbols, obj_path)
assert not provider['unresolved']
assert provider['bytes'] == provider['target']
assert provider['target'][:6] == bytes.fromhex('8339007405e9')
assert provider['target'][-1] == 0xC3
assert 0x2115C5 + 10 + struct.unpack_from('<i', provider['target'], 6)[0] == 0x4CBC0
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
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'existing_inline_handle_provider': {'rva': '0x2115c5', 'size': 11,
                                                      'whole_body_and_relocation': 'EXACT'}}, indent=2))
