"""Prove the whole native parameter-vector cleanup from its real parent."""
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'tools'))
import build
import eh_verify

SOURCE = ROOT / 'Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapManagerUpdateShadowMap.cpp'
PARENT = '?ReAcquireResources@Rva0007DA23ResourceManager@@QAE_NXZ'
RVA, SIZE = 0x75F3B7, 8
obj_path = build.obj_path(SOURCE)
obj, image = eh_verify.Obj(obj_path), eh_verify.Image()
assert eh_verify.verify_row(image, obj, PARENT, 0x7DA23) == ('EXACT', '')
locations = eh_verify.verified_funclet_locations(image, obj, PARENT, 0x7DA23)
labels = [name for name, address in locations.items() if address == RVA]
assert len(labels) == 1, labels
label = labels[0]
body, relocations = build.read_object_symbol_bytes(obj_path, label, SIZE, code_only=True)
relocations = [(offset, kind, name) for offset, kind, name in relocations if offset < SIZE]
callee = '??1?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@QAE@XZ'
assert body[:4] == bytes.fromhex('8d4dd8e9')
assert relocations == [(4, 20, callee)], relocations
symbols = build.load_symbol_map()
assert 0x7C632 in symbols[callee], symbols[callee]
thunk = build.read_target_bytes(0x7C632, 5)
assert thunk[0] == 0xE9
assert 0x7C632 + 5 + struct.unpack_from('<i', thunk, 1)[0] == 0x7C5D5
patched = bytearray(body[:SIZE])
struct.pack_into('<i', patched, 4, 0x7C632 - (RVA + SIZE))
assert bytes(patched) == build.read_target_bytes(RVA, SIZE)
row = {'name': PARENT, 'target_rva': '0x0007DA23', 'target_size': '478',
       'source': SOURCE.relative_to(ROOT).as_posix(), 'notes': ''}
parent = build.compile_function(row, symbols, obj_path)
assert not parent['unresolved']
assert parent['bytes'] == parent['target']
print(json.dumps({'parent': PARENT, 'parent_size': 478,
                  'parent_full_bytes': 'EXACT', 'eh_graph': 'EXACT',
                  'cleanup_rva': hex(RVA), 'cleanup_size': SIZE, 'label': label,
                  'full_cleanup_bytes': patched.hex(), 'relocations': relocations,
                  'native_destructor_thunk': '0x0007C632',
                  'rowed_vector_destructor': '0x0007C5D5'}, indent=2))
