"""Read the normally built parent object; prove the whole return cleanup."""
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngine/Source/Common/Rva003ED498Count.cpp'
PARENT = '?rva003ED4E5@BitRange@@QAE?AVAsciiString@@XZ'
RVA, SIZE = 0x7836E8, 25
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
assert eh_verify.verify_row(image, obj, PARENT, 0x3ED4E5) == ('EXACT', '')
locations = eh_verify.verified_funclet_locations(image, obj, PARENT, 0x3ED4E5)
labels = [name for name, address in locations.items() if address == RVA]
assert len(labels) == 1, labels
label = labels[0]
body, relocations = build.read_object_symbol_bytes(obj_path, label, SIZE, code_only=True)
relocations = [(offset, kind, name) for offset, kind, name in relocations if offset < SIZE]
assert relocations == [(20, 20, '??1AsciiString@@QAE@XZ')], relocations
patched = bytearray(body[:SIZE])
struct.pack_into('<i', patched, 20, 0x48BA39 - (RVA + 24))
assert bytes(patched) == build.read_target_bytes(RVA, SIZE)
row = {'name': PARENT, 'target_rva': '0x003ED4E5', 'target_size': '192',
       'source': SOURCE.relative_to(ROOT).as_posix(), 'notes': ''}
parent = build.compile_function(row, build.load_symbol_map(), obj_path)
assert not parent['unresolved']
assert parent['bytes'] == parent['target']
print(json.dumps({'parent': PARENT, 'parent_size': 192, 'parent_full_bytes': 'EXACT',
                  'eh_graph': 'EXACT', 'cleanup_rva': hex(RVA), 'cleanup_size': SIZE,
                  'label': label, 'full_cleanup_bytes': patched.hex(),
                  'relocations': relocations, 'retail_destructor_rva': '0x0048BA39'}, indent=2))
