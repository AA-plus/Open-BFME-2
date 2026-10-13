from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
needle='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);'
for mode in range(12):
    args='RegionInfoMap &map, const _STL::pair<int,Rva00501656> &pair'
    operation='map.insert(map.begin(),pair)'
    if mode&1:operation='map.insert(map.begin(),converted)'
    local='RegionInfoMap::value_type converted(pair); ' if mode&1 else ''
    if mode<4:
        helper='__forceinline _STL::_Rb_tree_node_base* InsertRegion('+args+') { '+local+'return '+operation+'._M_node; }\n'
        call='RegionInfoMap::iterator it(InsertRegion(m_RegionInfo,regionPair));'
    elif mode<8:
        helper='struct InsertRegion : RegionInfoMap::iterator { __forceinline InsertRegion('+args+') { '+local+'*static_cast<RegionInfoMap::iterator*>(this) = '+operation+'; } };\n'
        call='InsertRegion it(m_RegionInfo,regionPair);'
    else:
        helper='__forceinline void InsertRegion('+args+', RegionInfoMap::iterator &result) { '+local+'result = '+operation+'; }\n'
        call='RegionInfoMap::iterator it; InsertRegion(m_RegionInfo,regionPair,it);'
    b=base.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace(needle,call)
    if mode&2:
        b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
    r=run(b,'gather-insertform-'+str(mode),'gather')
    if r.get('exact'):break
