"""Replay Apt timeline cleanups from complete native parent graphs."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineCtor.cpp'
PARENTS = {'??0Rva005202C8@@QAE@PAX@Z': (0x5202C8, 540),
           '??1Rva005202C8@@UAE@XZ': (0x5204EF, 224)}
CLEANUPS = {0x796102: (8, '??1Rva005202C8@@UAE@XZ'),
            0x796126: (14, '??1Rva005202C8@@UAE@XZ')}

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
fold_name = '??0?$_Vector_base@URva00520211Element@@V?$allocator@URva00520211Element@@@_STL@@@_STL@@QAE@ABV?$allocator@URva00520211Element@@@1@@Z'
fold = build.compile_function({'name': fold_name, 'target_rva': '0x00211E58',
                               'target_size': '29', 'source': source, 'notes': ''},
                              symbols, obj_path)
assert not fold['masked'] and not fold['unresolved']
assert fold['bytes'] == fold['target']
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'whole_vector_base_fold': fold['bytes'].hex()}, indent=2))
