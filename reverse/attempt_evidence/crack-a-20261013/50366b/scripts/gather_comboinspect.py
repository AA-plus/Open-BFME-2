from trial import *
import hashlib,capstone
root=ROOT/'build/crack-a/neutral-combinations';sm=build.load_symbol_map();unique={}
for p in sorted(root.glob('*/result.json'),key=lambda p:int(p.parent.name)):
 r=json.loads(p.read_text())
 if r.get('diffbytes')!=7:continue
 obj=p.parent/'c1.obj';row=dict(name='?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ',target_rva='0x0050366B',target_size='1706',source=(p.parent/'c1.cpp').relative_to(ROOT).as_posix(),notes='')
 got=build.compile_function(row,sm,obj);a,b=got['bytes'],got['target'];h=hashlib.sha256(a).hexdigest()
 if h in unique:continue
 unique[h]=p.parent.name;print('UNIQUE',p.parent.name,'parents',r['parents'],'unresolved',got['unresolved'])
 cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for x,y in zip(cs.disasm(a,0x50366b),cs.disasm(b,0x50366b)):
  if x.bytes!=y.bytes:print(hex(x.address),x.mnemonic,x.op_str,'|',y.mnemonic,y.op_str)
print('unique',unique)
