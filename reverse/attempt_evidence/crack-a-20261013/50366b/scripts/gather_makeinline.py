from trial import *
base=(ROOT/'build/crack-a/gather-pair-make/c1.cpp').read_text()
for mode in range(8):
    ty='_STL::pair<int,Rva00501656>'
    ret='return '+ty+'(a,b);' if mode%2==0 else ty+' result(a,b); return result;'
    helper='__forceinline '+ty+' MakeRegionPair(const int &a,const Rva00501656 &b) { '+ret+' }\n'
    b=base.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace('_STL::make_pair(info.m_ownerID, info)','MakeRegionPair(info.m_ownerID, info)')
    if mode&2:b=b.replace('const int &a','int a')
    if mode&4:b=b.replace('_STL::pair<int, Rva00501656> regionPair =','const _STL::pair<int, Rva00501656>& regionPair =')
    r=run(b,'gather-makeinline-'+str(mode),'gather')
    if r.get('exact'):break
