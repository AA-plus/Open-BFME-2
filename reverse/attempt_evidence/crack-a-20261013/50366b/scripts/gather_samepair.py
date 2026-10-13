from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for mode in range(10):
    b=base
    b=b.replace('_STL::pair<int, Rva00501656> regionPair','_STL::pair<const int, Rva00501656> regionPair')
    b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), RegionInfoMap::value_type(regionPair)')
    if mode&1:b=b.replace('> regionPair(info.m_ownerID, info);','> const regionPair(info.m_ownerID, info);')
    if mode&2:
        spec='namespace _STL {template<> pair<const int,Rva00501656>::pair(const pair<const int,Rva00501656>&);}\n'
        b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
    if mode&4:
        b=b.replace('RegionInfoMap::value_type(regionPair)','static_cast<const RegionInfoMap::value_type&>(RegionInfoMap::value_type(regionPair))')
    if mode>=8:
        b=b.replace('_STL::pair<const int, Rva00501656> regionPair','_STL::pair<int, Rva00501656> regionPair')
    r=run(b,'gather-samepair-'+str(mode),'gather')
    if r.get('exact'):break
