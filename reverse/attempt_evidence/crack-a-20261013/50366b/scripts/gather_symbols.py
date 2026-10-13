from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
import random
rng=random.Random(50366)
for n in range(15):
    b=base
    for name in ['info','regionPair','playerPair','buildings','armies','playerInfo','armyPair','i','j','p','a','e']:
        b=re.sub(r'\b'+name+r'\b',name+'_'+str(rng.randrange(10**8)),b)
    r=run(b,'gather-rename-'+str(n),'gather')
    if r.get('exact'):raise SystemExit()
for mode in range(3):
    for n in [1,2,3,4,8,12,16,24,32]:
        decl='\n'.join(('int unusedLocal'+str(i)+';' if mode==0 else 'typedef int LocalInteger'+str(i)+';' if mode==1 else 'enum { LocalCount'+str(i)+' = '+str(i)+' };') for i in range(n))
        b=base.replace('\tm_PlayerInfo.clear();',decl+'\n\tm_PlayerInfo.clear();',1)
        r=run(b,'gather-symbols-'+str(mode)+'-'+str(n),'gather')
        if r.get('exact'):raise SystemExit()
