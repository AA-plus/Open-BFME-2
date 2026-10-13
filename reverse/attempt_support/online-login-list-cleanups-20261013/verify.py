"""Replay online-login list cleanups and all sixteen native parent graphs."""
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineLogin.cpp'
PARENTS = {'?InitGadgets@AptOnlineLogin@@QAEXPBDPAXPAVGameWindow@@@Z': (5702783, 597),
 '?OnAccountDeleted@AptOnlineLogin@@QAEX_N@Z': (5707155, 196),
 '?OnBttnRegisterFESL@AptOnlineLogin@@QAEXPBD@Z': (5695561, 335),
 '?rva0056FEA8@AptOnlineLogin@@QAEXXZ': (5701288, 504),
 '?rva005700A0@AptOnlineLogin@@QAEXXZ': (5701792, 869),
 '?rva005709D1@AptOnlineLogin@@QAEXAAVAsciiString@@0@Z': (5704145, 659),
 '?rva00570C64@AptOnlineLogin@@QAEXXZ': (5704804, 210),
 '?rva00570D36@AptOnlineLogin@@QAEXXZ': (5705014, 1011),
 '?rva00571129@AptOnlineLogin@@QAEXXZ': (5706025, 1130),
 '?rva0057166C@AptOnlineLogin@@UAEHPAXI00@Z': (5707372, 305),
 '?rva0057179D@AptOnlineLogin@@QAEX_N@Z': (5707677, 984),
 '?rva00571B75@AptOnlineLogin@@QAEXXZ': (5708661, 235),
 '?rva00571C9D@AptOnlineLogin@@QAEXXZ': (5708957, 2260),
 '?rva00572632@AptOnlineLogin@@QAEXPBD@Z': (5711410, 310),
 '?rva00572768@AptOnlineLogin@@QAEXPBD@Z': (5711720, 265),
 '?rva005706D4@AptOnlineLogin@@QAE_NXZ': (5703380, 760)}
CLEANUPS = {0x79AAFE: (8, '?rva005709D1@AptOnlineLogin@@QAEXAAVAsciiString@@0@Z'),
            0x79AB26: (8, '?rva005709D1@AptOnlineLogin@@QAEXAAVAsciiString@@0@Z'),
            0x79AB40: (8, '?rva00570C64@AptOnlineLogin@@QAEXXZ')}

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
list_name = '??1?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ'
wrapper = build.compile_function({'name': list_name, 'target_rva': '0x00207F08',
                                  'target_size': '5', 'source': source, 'notes': ''},
                                 symbols, obj_path)
assert not wrapper['masked'] and not wrapper['unresolved']
assert wrapper['bytes'] == wrapper['target']
assert wrapper['target'][0] == 0xE9
assert 0x207F08 + 5 + struct.unpack_from('<i', wrapper['target'], 1)[0] == 0x2FECBC
print(json.dumps({'parents': parents, 'cleanups': cleanups,
                  'whole_list_wrapper': wrapper['bytes'].hex()}, indent=2))
