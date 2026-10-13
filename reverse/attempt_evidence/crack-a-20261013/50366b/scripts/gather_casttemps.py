from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
expressions=[
 'static_cast<const RegionInfoMap::value_type&>(regionPair)',
 'static_cast<const RegionInfoMap::value_type>(regionPair)',
 'static_cast<RegionInfoMap::value_type>(regionPair)',
 'RegionInfoMap::value_type(regionPair)',
 'AsConst(RegionInfoMap::value_type(regionPair))',
 'AsValue(regionPair)',
 'AsConst(regionPair)',
 '(0,RegionInfoMap::value_type(regionPair))',
 'true ? RegionInfoMap::value_type(regionPair) : RegionInfoMap::value_type(regionPair)',
]
for n,expr in enumerate(expressions):
    b=base.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), '+expr)
    helper='template<class T> __forceinline const T& AsConst(const T& value){return value;}\n__forceinline const RegionInfoMap::value_type& AsValue(const RegionInfoMap::value_type& value){return value;}\n'
    b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
    r=run(b,'gather-casttemp-'+str(n),'gather')
    if r.get('exact'):break
