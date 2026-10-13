"""Replay attack-move allocation cleanups from the complete native parent graph."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameLogic/AI/AIAttackMoveStateMachine.cpp'
PARENTS = {
    '??0AIAttackMoveStateMachine@@QAE@PAVObject@@I@Z': (0x34C6EF, 206),
    '??0AIAttackMoveToState@@QAE@PAVStateMachine@@@Z': (0x34EBE8, 147),
    '??0AIAttackFollowWaypointPathState@@QAE@PAVStateMachine@@_N@Z': (0x34F153, 113),
    '??0AIFollowPathAsTeamState@@QAE@PAVStateMachine@@_NI@Z': (0x34E307, 158),
}
CLEANUPS = {
    0x77CFFE: (10, '??0AIAttackMoveToState@@QAE@PAVStateMachine@@@Z'),
    0x77D01A: (10, '??0AIAttackFollowWaypointPathState@@QAE@PAVStateMachine@@_N@Z'),
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
parent = '??0AIAttackMoveStateMachine@@QAE@PAVObject@@I@Z'
handler_rva, funcinfo_rva = image.frame_funcinfo(PARENTS[parent][0])
assert handler_rva == 0x77CF93
handler_name = '__ehhandler$' + parent
assert handler_name in obj.by_name
result = build.compile_function({'name': handler_name, 'target_rva': hex(handler_rva),
    'target_size': '10', 'source': source, 'notes': 'gen-ehstub;parent=' + parent},
    symbols, obj_path)
assert not result['unresolved'] and result['bytes'] == result['target']
assert result['bytes'][0] == 0xB8 and result['bytes'][5] == 0xE9
assert struct.unpack_from('<I', result['bytes'], 1)[0] - image.base == funcinfo_rva
assert handler_rva + 10 + struct.unpack_from('<i', result['bytes'], 6)[0] == 0x629182
handler = {'rva': hex(handler_rva), 'size': 10, 'name': handler_name,
           'funcinfo_rva': hex(funcinfo_rva), 'full_bytes': result['bytes'].hex(),
           'native_import_thunk': '0x629182'}
providers = []
for name, rva, size, provider_source in [
    ('?ji_00629182@@YAXXZ', 0x629182, 6, 'Code/gen_small/imports_000.cpp'),
    ('??3@YAXPAX@Z', 0x2FD60, 21,
     'Code/Libraries/Source/WWVegas/WWLib/mem_ops.cpp'),
]:
    provider_obj_path = build.obj_path(ROOT / provider_source)
    provider_obj = eh_verify.Obj(provider_obj_path)
    assert name in provider_obj.by_name
    result = build.compile_function({'name': name, 'target_rva': hex(rva),
        'target_size': str(size), 'source': provider_source, 'notes': ''},
        symbols, provider_obj_path)
    assert not result['unresolved']
    assert result['bytes'] == result['target']
    graph = eh_verify.verify_row(image, provider_obj, name, rva)
    assert graph is None
    providers.append({'name': name, 'rva': hex(rva), 'size': size,
                      'whole_body': 'EXACT', 'eh_graph': 'EXACT' if graph else 'absent on both sides'})
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'providers': providers, 'handler': handler}, indent=2))
