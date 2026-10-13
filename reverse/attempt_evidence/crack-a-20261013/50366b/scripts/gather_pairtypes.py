from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(9):
    b=base
    if mode<4:
        b=b.replace(decl,('_STL::pair<const int, Rva00501656>' if mode&1 else '_STL::pair<unsigned int, Rva00501656>')+' regionPair(info.m_ownerID, info);')
        b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), reinterpret_cast<const _STL::pair<int,Rva00501656>&>(regionPair)')
        if mode&2:b=b.replace('> regionPair(info.m_ownerID, info);','> const regionPair(info.m_ownerID, info);')
    else:
        # Give the first pair's constructor a separate inlining context without a temporary return.
        helper='__forceinline void insertRegions(RegionInfoMap &map, IntIntMap &index, Rva00501656 &info) { '+decl+' RegionInfoMap::iterator it = map.insert(map.begin(),regionPair); index.insert(index.begin(),_STL::make_pair(info.m_regionID,(int)&it->second)); }\n'
        old=decl+'\n\t\tRegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);\n\t\tm_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
        b=b.replace(old,'insertRegions(m_RegionInfo,m_RegionInfoByRegion,info);').replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
        if mode&1:b=b.replace('int, Rva00501656> regionPair','int, Rva00501656> const regionPair')
        if mode>=6:
            # Declaration-only specialization preserves the native conversion helper boundary.
            spec='namespace _STL { template<> template<> pair<const int,Rva00501656>::pair(const pair<int,Rva00501656>&); }\n'
            b=b.replace('__forceinline void insertRegions',spec+'__forceinline void insertRegions')
        if mode==8:b=b.replace('__forceinline void insertRegions','inline void insertRegions')
    r=run(b,'gather-pairtype-'+str(mode),'gather')
    if r.get('exact'):break
