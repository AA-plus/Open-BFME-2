"""Approved clean-room spec plus retail differential check, no decoder references."""
from pathlib import Path
import sys,struct,random,hashlib,json
sys.path.insert(0,'tools')
import build
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
from difflib import SequenceMatcher
CODE,RET,TABLE,SCALE,FRAME,STACK=0x110000,0x11F000,0xDB7A28,0x200000,0x300000,0x400000
native=build.read_target_bytes(0x1C22C0,1526)
table=build.read_target_bytes(0x9B7A28,256)
sharpen=struct.unpack('<64i',table)
saved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789A,UC_X86_REG_EBP:0x456789AB}
def weight(a,b,quality,sharp):
 v=quality+32-2*abs(a-b)
 if v < -64:return sharp
 return min(min(3*quality,24),max(0,v))
def oracle(frame,src,dst,pitch,q,scale):
 v=[[weight(frame[src+(r-1)*pitch+c],frame[src+r*pitch+c],scale[q],sharpen[q]) for c in range(8)] for r in range(9)]
 h=[[weight(frame[src+r*pitch+c-1],frame[src+r*pitch+c],scale[q],sharpen[q]) for c in range(9)] for r in range(8)]
 out=bytearray(frame)
 for r in range(8):
  for c in range(8):
   up,down,left,right=v[r][c],v[r+1][c],h[r][c],h[r][c+1]
   at=src+r*pitch+c
   value=((128-up-down-left-right)*out[at]+up*out[at-pitch]+down*out[at+pitch]+left*out[at-1]+right*out[at+1]+64)>>7
   out[dst+r*pitch+c]=min(255,max(0,value))
 return bytes(out)
def run(code,frame,src,dst,pitch,q,scale):
 u=Uc(UC_ARCH_X86,UC_MODE_32)
 for base,size in ((CODE,0x10000),(TABLE&~4095,4096),(SCALE,4096),(FRAME,0x10000),(STACK,0x20000)):u.mem_map(base,size)
 u.mem_write(CODE,code);u.mem_write(TABLE,table)
 scaleBytes=struct.pack('<64i',*scale)
 u.mem_write(SCALE,scaleBytes);u.mem_write(FRAME,frame)
 sp=STACK+0x18000
 u.mem_write(sp,struct.pack('<7I',RET,0xFEED1234,FRAME+src,FRAME+dst,pitch&0xffffffff,q,SCALE))
 for reg,value in saved.items():u.reg_write(reg,value)
 u.reg_write(UC_X86_REG_ESP,sp)
 u.emu_start(CODE,RET,count=200000)
 assert u.reg_read(UC_X86_REG_EIP)==RET
 assert u.reg_read(UC_X86_REG_ESP)==sp+4
 assert all(u.reg_read(reg)==value for reg,value in saved.items())
 assert bytes(u.mem_read(TABLE,len(table)))==table
 assert bytes(u.mem_read(SCALE,len(scaleBytes)))==scaleBytes
 assert bytes(u.mem_read(sp+4,24))==struct.pack('<6I',0xFEED1234,FRAME+src,FRAME+dst,pitch&0xffffffff,q,SCALE)
 return bytes(u.mem_read(FRAME,len(frame)))
randomizer=random.Random(0x1C22C0)
cases=[]
for index in range(72):
 pitch=(10,11,16,24,32,48)[index%6]
 if index%9==8:pitch=-pitch
 q=(0,1,7,8,15,16,23,24,39,40,63)[index%11]
 scale=[randomizer.randrange(0,256) for _ in range(64)]
 if index<12:scale[q]=(0,1,7,8,16,24)[index%6]
 frame=bytearray(randomizer.randbytes(0x10000))
 src=0x2000
 if index<6:
  for r in range(-1,9):
   for c in range(-1,9):frame[src+r*pitch+c]=(0,255,64,128,192,127)[index]
 elif index<12:
  for r in range(-1,9):
   for c in range(-1,9):frame[src+r*pitch+c]=255*((r+c)&1)
 for layout,dst in [('separate',0x8000),('same',src),('shift-right',src+1),('next-row',src+pitch)]:
  want=oracle(frame,src,dst,pitch,q,scale)
  assert run(native,bytes(frame),src,dst,pitch,q,scale)==want,(index,layout,'native vs spec')
  cases.append((index,layout,bytes(frame),src,dst,pitch,q,scale,want))
results=[]
for path in (sys.argv[1:] or ['reverse/attempts/0x001c22c0.cpp']):
 source=Path(path).resolve()
 code,relocs=build.read_object_symbol_bytes(build.obj_path(source),'_DeringBlockWeak_C')
 patched=bytearray(code)
 for offset,kind,name in relocs:
  assert kind==6 and name=='_Vp6FilterEdgeTagTable',(offset,kind,name)
  addend=struct.unpack_from('<I',patched,offset)[0]
  struct.pack_into('<I',patched,offset,TABLE+addend)
 for index,layout,frame,src,dst,pitch,q,scale,want in cases:
  assert run(bytes(patched),frame,src,dst,pitch,q,scale)==want,(path,index,layout,'draft vs spec/retail')
 matching=sum(m.size for m in SequenceMatcher(None,native,bytes(patched),autojunk=False).get_matching_blocks())
 result={'source':source.name,'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'compiled_sha256':hashlib.sha256(code).hexdigest(),'relocations':relocs,'compiled_bytes':len(code),'target_bytes':1526,'cases':len(cases),'native_spec_cases':len(cases),'matching_bytes_ordered':matching,'score':matching/max(len(code),1526),'q_indices':sorted(set(c[6] for c in cases)),'pitches':sorted(set(c[5] for c in cases)),'layouts':['separate','same','shift-right','next-row']}
 results.append(result);print(json.dumps(result))
Path('build/dering-weak-verification.json').write_text(json.dumps({'results':results,'limits':'288 deterministic cases; not exhaustive or byte identity. Entire mapped frame, cdecl stack, nonvolatile registers, arguments, quantizer and sharpen tables compared.'},indent=2)+'\n')
