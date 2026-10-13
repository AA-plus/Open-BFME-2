from trial import *
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for d in sorted((ROOT/'build/crack-a').glob('gather-*')):
    p=d/'result.json'
    if not p.exists():continue
    r=json.loads(p.read_text())
    if r.get('raw_size',r.get('size'))!=1701:continue
    b=(d/'c1.cpp').read_text()
    if 'pair<int,Rva00501656>::pair' in b:continue
    if not ('aliaslocal' in d.name or 'lifetime' in d.name):continue
    b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation',1)
    r=run(b,d.name+'-forced','gather')
    if r.get('exact'):raise SystemExit()
