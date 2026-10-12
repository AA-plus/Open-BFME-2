"""Verify the bank's INIException cleanup and catchability metadata, not its parser."""
import csv, hashlib, json, struct, sys
from pathlib import Path
sys.path.insert(0, 'tools')
import build
source = Path(sys.argv[1] if len(sys.argv)>1 else 'reverse/attempts/0x00688b10.cpp').resolve()
obj = build.obj_path(source)
ti = '__TI1?AVINIException@@'
cta = '__CTA1?AVINIException@@'
ct = '__CT??_R0?AVINIException@@@8??0INIException@@QAE@ABV0@@Z8'
descriptor = '??_R0?AVINIException@@@8'
destructor = '??1INIException@@QAE@XZ'
copy = '??0INIException@@QAE@ABV0@@Z'
owners = {}
with Path('reverse/functions.csv').open(newline='', encoding='utf-8') as handle:
    for row in csv.DictReader(handle):
        if row['name'] in (destructor, copy):
            assert row['status'] == 'matched'
            assert row['name'] not in owners
            owners[row['name']] = int(row['target_rva'], 16) + 0x400000
assert owners == {destructor: 0x42BD30, copy: 0x4588C5}
native_ti = struct.unpack('<4I', build.read_target_bytes(0x8FE2FC, 16))
native_cta = struct.unpack('<2I', build.read_target_bytes(native_ti[3]-0x400000, 8))
native_ct = struct.unpack('<7I', build.read_target_bytes(native_cta[1]-0x400000, 28))
compiled_ti, ti_rel = build.read_object_symbol_bytes(obj, ti, 16)
compiled_cta, cta_rel = build.read_object_symbol_bytes(obj, cta, 8)
compiled_ct, ct_rel = build.read_object_symbol_bytes(obj, ct, 28)
assert ti_rel == [(4, 6, destructor), (12, 6, cta)]
assert cta_rel == [(4, 6, ct)]
assert ct_rel == [(4, 6, descriptor), (24, 6, copy)]
normalized_ti = list(struct.unpack('<4I', compiled_ti))
normalized_cta = list(struct.unpack('<2I', compiled_cta))
normalized_ct = list(struct.unpack('<7I', compiled_ct))
assert normalized_ti[1] == normalized_ti[3] == 0
assert normalized_cta[1] == 0
assert normalized_ct[1] == normalized_ct[6] == 0
normalized_ti[1] = owners[destructor]; normalized_ti[3] = native_ti[3]
normalized_cta[1] = native_cta[1]
normalized_ct[1] = native_ct[1]; normalized_ct[6] = owners[copy]
assert tuple(normalized_ti) == native_ti
assert tuple(normalized_cta) == native_cta
assert tuple(normalized_ct) == native_ct
expected_name = b'.?AVINIException@@\0'
native_name = build.read_target_bytes(native_ct[1]-0x400000+8, len(expected_name))
compiled_descriptor, descriptor_rel = build.read_object_symbol_bytes(obj, descriptor)
assert descriptor_rel == [(0, 6, '??_7type_info@@6B@')]
assert compiled_descriptor[4:8] == bytes(4)
assert compiled_descriptor[8:8+len(expected_name)] == native_name == expected_name
code, relocs = build.read_object_symbol_bytes(obj, '?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z')
report = {'target_rva': '0x00688B10', 'target_bytes': 1578, 'compiled_bytes': len(code),
          'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
          'compiled_sha256': hashlib.sha256(code).hexdigest(),
          'retail_throw_info_rva': '0x008FE2FC', 'throw_info': list(native_ti),
          'catchable_array': list(native_cta), 'catchable_type': list(native_ct),
          'destructor': destructor, 'copy_constructor': copy,
          'coverage': 'INIException cleanup, catchable-type fields, object size, pointer-adjustment fields and RTTI name; type_info vtable placement, parser instructions, other EH data, literals and runtime behavior are not verified'}
destination = Path(sys.argv[2] if len(sys.argv)>2 else 'build/resume-subtitle-exception-metadata-20261012.json')
destination.write_bytes((json.dumps(report, indent=2)+'\n').encode())
print('PASS: canonical INIException cleanup and catchability metadata agree with retail; parser remains nonexact')
