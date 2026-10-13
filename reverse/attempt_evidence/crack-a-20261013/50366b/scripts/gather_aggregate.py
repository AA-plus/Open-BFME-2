from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(8):
    b=base
    definition='struct RegionInfoPair {int first; Rva00501656 second;};'
    init='RegionInfoPair regionPair = {info.m_ownerID, info};'
    if mode&1:
        definition='struct RegionInfoPair {int first; Rva00501656 second; __forceinline RegionInfoPair(const int &a,const Rva00501656&b):first(a),second(b){} };'
        init='RegionInfoPair regionPair(info.m_ownerID,info);'
    if mode&2:
        definition=definition.replace('int first','const int first')
    if mode&4:
        definition='#pragma pack(push, 1)\n'+definition+'\n#pragma pack(pop)'
    b=b.replace(decl,definition+'\n'+init).replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), reinterpret_cast<const _STL::pair<int,Rva00501656>&>(regionPair)')
    r=run(b,'gather-aggregate-'+str(mode),'gather')
    if r.get('exact'):break
