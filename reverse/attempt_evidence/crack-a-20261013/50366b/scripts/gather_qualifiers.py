from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(8):
    b=base
    if mode<4:
        q=['register','volatile','const volatile','register const'][mode]
        b=b.replace(decl,q+' '+decl)
        if 'volatile' in q:b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), const_cast<const _STL::pair<int,Rva00501656>&>(regionPair)')
    else:
        spec='namespace _STL { template<> template<> __declspec(noinline) pair<const int,Rva00501656>::pair(const pair<int,Rva00501656>& p):first(p.first),second(p.second){} }\n'
        b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
        if mode&1:b=b.replace('template<> template<>','template<>')
        if mode&2:b=b.replace('__declspec(noinline)','__forceinline')
    r=run(b,'gather-qualifier-'+str(mode),'gather')
    if r.get('exact'):break
