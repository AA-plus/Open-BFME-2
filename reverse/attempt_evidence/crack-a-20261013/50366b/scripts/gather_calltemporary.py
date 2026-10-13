from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
old=decl+'\n\t\tRegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);\n\t\tm_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
assert old in base
for mode in range(8):
    helper='''__forceinline void insertRegionIndex(RegionInfoMap &map, IntIntMap &index,
    const Rva00501656 &info, const _STL::pair<int,Rva00501656> &regionPair)
{
    RegionInfoMap::iterator it = map.insert(map.begin(), regionPair);
    index.insert(index.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));
}
'''
    b=base.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace(old,'insertRegionIndex(m_RegionInfo,m_RegionInfoByRegion,info,_STL::pair<int,Rva00501656>(info.m_ownerID,info));')
    if mode&1:b=b.replace('const Rva00501656 &info','Rva00501656 &info')
    if mode&2:
        b=b.replace('class LWAIWorldInformation','namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\nclass LWAIWorldInformation')
    if mode&4:
        b=b.replace('const Rva00501656 &info, const _STL::pair<int,Rva00501656> &regionPair','const _STL::pair<int,Rva00501656> &regionPair, const Rva00501656 &info').replace('Rva00501656 &info, const _STL::pair<int,Rva00501656> &regionPair','const _STL::pair<int,Rva00501656> &regionPair, Rva00501656 &info').replace('m_RegionInfoByRegion,info,_STL::pair<int,Rva00501656>(info.m_ownerID,info)','m_RegionInfoByRegion,_STL::pair<int,Rva00501656>(info.m_ownerID,info),info')
    r=run(b,'gather-calltemporary-'+str(mode),'gather')
    if r.get('exact'):break
