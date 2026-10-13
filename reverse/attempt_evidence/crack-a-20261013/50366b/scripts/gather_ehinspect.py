from trial import *
from eh_verify import Image,Obj,verify_row,section_placements
import capstone
image=Image()
obj=Obj(ROOT/'build/crack-a/gather-scope-4/c1.obj')
name='?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ'
print('verdict',verify_row(image,obj,name,0x50366b))
symbol=obj.by_name[name]
eh=obj.eh_sections(symbol['section'])
base,conflicts=section_placements(image,obj,dict(symbol,retail_rva=0x50366b),eh)
print('frame_funcinfo',image.frame_funcinfo(0x50366b),'conflicts',conflicts)
cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
out=[]
for s in eh:
    at=base.get(s['index'])
    if at is None:continue
    ours=s['data'];retail=image.bytes[at:at+len(ours)]
    out.append(dict(name=s['name'],rva=hex(at),size=len(ours),raw=ours.hex(),retail=retail.hex()))
    if s['name'].startswith('.text$x'):
        print(s['name'],hex(at),len(ours))
        print('retail:','; '.join(x.mnemonic+' '+x.op_str for x in cs.disasm(retail,at)))
        print('object:','; '.join(x.mnemonic+' '+x.op_str for x in cs.disasm(ours,at)))
(ROOT/'build/crack-a/gather-eh-inspection.json').write_text(json.dumps(out,indent=2))
