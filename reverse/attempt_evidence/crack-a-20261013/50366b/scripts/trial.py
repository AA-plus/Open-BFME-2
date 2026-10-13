import sys,json,re,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from variant_search import Scorer,instructions
import build

def run(src, tag, kind='distance'):
    rva,symbol,size=(0x5020cc,'?Rva005020CCBuildRegionDistances@@YAXXZ',447) if kind=='distance' else (0x50366b,'?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ',1706)
    dest=ROOT/'build/crack-a'/tag
    scorer=Scorer(symbol,rva,size,dest)
    old_try=build.try_compile_source
    def wrapped(*args,**kwargs):
        answer=old_try(*args,**kwargs)
        (dest/'compiler.txt').write_text(str(answer),errors='replace')
        return answer
    build.try_compile_source=wrapped
    result=scorer(src)
    build.try_compile_source=old_try
    summary={k:v for k,v in result.items() if k not in ('compiled','target')}
    if 'compiled' in result:
        raw,relocs=build.read_object_symbol_bytes(dest/'c1.obj',symbol)
        summary['raw_size']=len(raw)
        (dest/'raw.bin').write_bytes(raw)
        (dest/'relocs.json').write_text(json.dumps(relocs,indent=2))
        a,b=result['compiled'],result['target']
        summary.update(size=len(a),diffbytes=sum(x!=y for x,y in zip(a,b))+abs(len(a)-len(b)))
        (dest/'compiled.bin').write_bytes(a);(dest/'target.bin').write_bytes(b)
        import capstone
        cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
        aa=list(cs.disasm(a,rva));bb=list(cs.disasm(b,rva))
        for name,seq in [('compiled',aa),('target',bb)]:
            (dest/(name+'.txt')).write_text('\n'.join(f'{x.address:08x} {x.bytes.hex():20} {x.mnemonic} {x.op_str}' for x in seq))
        (dest/'diff.txt').write_text('\n'.join(f'{i}: {x.address:08x} {x.mnemonic} {x.op_str:50} | {y.mnemonic} {y.op_str}' for i,(x,y) in enumerate(zip(aa,bb)) if x.bytes!=y.bytes))
    (dest/'result.json').write_text(json.dumps(summary,indent=2))
    print(tag,json.dumps(summary),flush=True)
    return summary

if __name__=='__main__':
    kind=sys.argv[1];src=Path(sys.argv[2]).read_text() if len(sys.argv)>2 else (ROOT/'reverse/attempts'/('0x005020cc.cpp' if kind=='distance' else '0x0050366b.cpp')).read_text()
    run(src,sys.argv[3] if len(sys.argv)>3 else kind+'-base',kind)
