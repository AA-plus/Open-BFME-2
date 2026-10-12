"""Check the recovered clean-room bank against retail and the reviewed plane spec."""
import hashlib, json, random, struct, sys
from pathlib import Path
sys.path.insert(0,'tools')
import build
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EIP, UC_X86_REG_ESP, UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI

source=Path(sys.argv[1] if len(sys.argv)>1 else 'reverse/attempts/0x001b96a0.cpp').resolve()
compiled,relocations=build.read_object_symbol_bytes(build.obj_path(source),'_UpdateUMVBorder')
assert not relocations
retail=build.read_target_bytes(0x1B96A0,1047)
CODE,CONTEXT,FRAME,STACK,RETURN=0x100000,0x200000,0x300000,0x400000,0x10F000
saved={UC_X86_REG_EBX:0x11223344,UC_X86_REG_EBP:0x55667788,UC_X86_REG_ESI:0x99AABBCC,UC_X86_REG_EDI:0x10203040}

def run(code,context,frame):
    emulator=Uc(UC_ARCH_X86,UC_MODE_32)
    for address in (CODE,CONTEXT,FRAME,STACK):emulator.mem_map(address,0x10000)
    emulator.mem_write(CODE,bytes(code))
    emulator.mem_write(CONTEXT,bytes(context));emulator.mem_write(FRAME,bytes(frame))
    initial_sp=STACK+0xF000
    emulator.mem_write(initial_sp,struct.pack('<III',RETURN,CONTEXT,FRAME))
    emulator.reg_write(UC_X86_REG_ESP,initial_sp)
    for register,value in saved.items():emulator.reg_write(register,value)
    emulator.emu_start(CODE,RETURN,timeout=3000000,count=2000000)
    assert emulator.reg_read(UC_X86_REG_EIP)==RETURN,'execution did not return'
    assert emulator.reg_read(UC_X86_REG_ESP)==initial_sp+4,'cdecl return cleanup changed'
    assert all(emulator.reg_read(reg)==value for reg,value in saved.items()),'callee-saved register changed'
    assert bytes(emulator.mem_read(CONTEXT,len(context)))==bytes(context),'context modified'
    return bytes(emulator.mem_read(FRAME,len(frame)))

def oracle(frame,planes):
    output=bytearray(frame)
    for offset,width,height,stride,border in planes:
        for row in range(height):
            left=offset+row*stride;right=left+width-1
            output[left-border:left]=bytes([output[left]])*border
            output[right+1:right+1+border]=bytes([output[right]])*border
        first=offset-border;last=first+(height-1)*stride
        top=first-border*stride;bottom=last+stride
        first_row=bytes(output[first:first+stride]);last_row=bytes(output[last:last+stride])
        for row in range(border):
            output[top+row*stride:top+(row+1)*stride]=first_row
            output[bottom+row*stride:bottom+(row+1)*stride]=last_row
    return bytes(output)

results=[]
for h,v in ((1,1),(2,3),(8,5),(11,7)):
    for border in (8,16,32):
        width,height=8*h,8*v;ystride=width+2*border;uvstride=4*h+border;half=border//2
        ysize=(height+2*border)*ystride;uvsize=(4*v+border)*uvstride
        offsets=(border*ystride+border,ysize+half*uvstride+half,ysize+uvsize+half*uvstride+half)
        planes=((offsets[0],width,height,ystride,border),(offsets[1],4*h,4*v,uvstride,half),(offsets[2],4*h,4*v,uvstride,half))
        rng=random.Random(0x1B96A0+h*1000+v*100+border)
        frame=bytes(rng.randrange(256) for _ in range(ysize+2*uvsize))
        context=bytearray(0xB8)
        for field,value in zip((0x78,0x7C,0x80,0x90,0x94,0x98,0x9C,0xB4),(*offsets,h,v,ystride,uvstride,border)):
            struct.pack_into('<i',context,field,value)
        expected=oracle(frame,planes);native=run(retail,context,frame);recovered=run(compiled,context,frame)
        assert native==expected,(h,v,border,'retail versus spec')
        assert recovered==expected,(h,v,border,'recovered versus spec')
        results.append({'horizontal_fragments':h,'vertical_fragments':v,'border':border,'frame_bytes':len(frame),'equal':True})
report={'target_rva':'0x001B96A0','retail_bytes':len(retail),'compiled_bytes':len(compiled),
        'compiled_sha256':hashlib.sha256(compiled).hexdigest(),
        'relocations':len(relocations),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'coverage':'12 legal positive-dimension Y/U/V frame layouts; output and cdecl preserved registers, context and stack; not byte exact',
        'cases':results}
Path(sys.argv[2] if len(sys.argv)>2 else 'build/resume-border-recovered-bank-emulation-20261012.json').write_bytes((json.dumps(report,indent=2)+'\n').encode('utf-8'))
print('PASS',len(results),'cases; all Y/U/V border bytes equal retail and the independent spec oracle; cdecl ABI preserved')
print('byte-match remains incomplete:',len(compiled),'compiled versus',len(retail),'retail')
