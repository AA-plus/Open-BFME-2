from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
needle='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);'
for mode in range(12):
    b=base
    if mode<4:
        pair='RegionInfoMap::value_type converted(regionPair);'
        if mode&1:pair='const '+pair
        if mode&2:pair='const RegionInfoMap::value_type& converted = RegionInfoMap::value_type(regionPair);'
        b=b.replace(needle,'RegionInfoMap::iterator it; { '+pair+' it = m_RegionInfo.insert(m_RegionInfo.begin(), converted); }')
    else:
        helper='__forceinline RegionInfoMap::iterator insertRegionPair(RegionInfoMap &map, const _STL::pair<int,Rva00501656> &pair) { '+('RegionInfoMap::value_type converted(pair); return map.insert(map.begin(),converted);' if mode&1 else 'return map.insert(map.begin(),pair);')+' }\n'
        b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace(needle,'RegionInfoMap::iterator it = insertRegionPair(m_RegionInfo,regionPair);')
        if mode&2:b=b.replace('const _STL::pair<int,Rva00501656> &pair','_STL::pair<int,Rva00501656> &pair')
        if mode>=8:
            decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
            b=b.replace(decl,'').replace('insertRegionPair(m_RegionInfo,regionPair)','insertRegionPair(m_RegionInfo,_STL::pair<int,Rva00501656>(info.m_ownerID,info))')
    r=run(b,'gather-converted-'+str(mode),'gather')
    if r.get('exact'):break
