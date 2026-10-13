from trial import *
import difflib,random,hashlib
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
head,body=base.split('#include',1);body=('#include'+body).splitlines(keepends=True)
pool=[];seen=set()
for p in (ROOT/'build/crack-a').glob('gather-*/result.json'):
 try:
  r=json.loads(p.read_text()); s=(p.parent/'c1.cpp').read_text()
  if r.get('diffbytes')!=7 or r.get('size')!=1706 or r.get('raw_size',1706)!=1706:continue
  if '#include' not in s:continue
  s=('#include'+s.split('#include',1)[1]).splitlines(keepends=True)
  edits=[(a,z,s[c:d]) for op,a,z,c,d in difflib.SequenceMatcher(None,body,s,autojunk=False).get_opcodes() if op!='equal']
  if not edits:continue
  key=repr(edits)
  if key in seen:continue
  seen.add(key);pool.append((p.parent.name,edits))
 except Exception:pass
out=ROOT/'build/crack-a/neutral-combinations';out.mkdir(exist_ok=True)
(out/'pool.json').write_text(json.dumps(pool,indent=2))
rng=random.Random(50366);sources=set();outputs={};done=0
from variant_search import Scorer
symbol='?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ'
while done<600:
 chosen=[];edits=[]
 for name,ee in rng.sample(pool,min(len(pool),rng.randint(2,7))):
  if any(not(z<a2 or z2<a) for a,z,t in ee for a2,z2,t2 in edits):continue
  chosen.append(name);edits+=ee
 if len(chosen)<2:continue
 s=body
 for a,z,t in sorted(edits,reverse=True):s=s[:a]+t+s[z:]
 s=head+''.join(s);k=hashlib.sha256(s.encode()).hexdigest()
 if k in sources:continue
 sources.add(k);done+=1;dest=out/str(done)
 scorer=Scorer(symbol,0x50366b,1706,dest);r=scorer(s)
 summary={k:v for k,v in r.items() if k not in ('compiled','target')};summary.update(trial=done,parents=chosen)
 if 'compiled' in r:
  a,b=r['compiled'],r['target'];raw,rel=build.read_object_symbol_bytes(dest/'c1.obj',symbol)
  summary.update(raw_size=len(raw),diffbytes=sum(x!=y for x,y in zip(a,b))+abs(len(a)-len(b)))
  h=hashlib.sha256(a).hexdigest();outputs[h]=outputs.get(h,0)+1
 (dest/'result.json').write_text(json.dumps(summary,indent=2))
 with (out/'scores.jsonl').open('a') as f:f.write(json.dumps(summary)+'\n')
 if done%20==0 or r.get('exact'):print(dict(trial=done,score=r.get('fitness'),diff=summary.get('diffbytes'),unique_outputs=len(outputs),exact=r.get('exact')),flush=True)
 if r.get('exact'):
  (out/'win.cpp').write_text(s);break
print('done',done,'pool',len(pool),'unique_outputs',len(outputs),flush=True)
