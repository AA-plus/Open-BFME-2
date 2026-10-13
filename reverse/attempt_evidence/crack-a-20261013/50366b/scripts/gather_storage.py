from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(8):
    b=base
    ty='_STL::pair<int,Rva00501656>'
    if mode<4:
        b=b.replace(decl,ty+' regionPair[1] = { '+ty+'(info.m_ownerID,info) };').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), regionPair[0]')
        if mode&1:b=b.replace('> regionPair[1]','> const regionPair[1]')
        if mode&2:b=b.replace('= { '+ty+'(info.m_ownerID,info) }','= { {info.m_ownerID,info} }')
    else:
        helper='struct PairPlace {void *p; PairPlace(void *q):p(q){}}; __forceinline void *operator new(unsigned int,PairPlace p) throw(){return p.p;}\n'
        helper+='struct RegionPairLocal { typedef '+ty+' P; __declspec(align(4)) char storage[sizeof(P)]; __forceinline RegionPairLocal(int a,const Rva00501656& b){new(PairPlace(storage)) P(a,b);} __forceinline ~RegionPairLocal(){get().~P();} __forceinline P& get(){return *reinterpret_cast<P*>(storage);} };\n'
        b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace(decl,'RegionPairLocal regionPair(info.m_ownerID,info);').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), regionPair.get()')
        if mode&1:b=b.replace('char storage[sizeof(P)]','int storage[sizeof(P)/4]')
        if mode&2:b=b.replace('RegionPairLocal(int a','RegionPairLocal(const int &a')
    r=run(b,'gather-storage-'+str(mode),'gather')
    if r.get('exact'):break
