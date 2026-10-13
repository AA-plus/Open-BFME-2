from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
start=base.index('\t\t_STL::vector<const ModuleData *> buildings;',base.index('void LWAIWorldInformation::Gather'))
end=base.index('\n\t\t}\n\t}\n\n\tint playerCount',start)
body=base[start:end]
decl='_STL::vector<const ModuleData *> buildings;'
params=[('LivingWorldRegion *region','region'),('Rva00501656 &info','info'),('RegionInfoMap &m_RegionInfo','m_RegionInfo'),('IntIntMap &m_RegionInfoByRegion','m_RegionInfoByRegion')]
for mode in range(10):
    args=params[:]
    inner=body
    if mode<6:
        inner=inner.replace(decl,'')
        args.insert(mode%5,('_STL::vector<const ModuleData *> &buildings','_STL::vector<const ModuleData *>()'))
    if mode in [5,7,9]:args.reverse()
    helper='__forceinline void GatherRegionEntries('+', '.join(x for x,y in args)+') {\n'+inner+'\n}\n'
    call='GatherRegionEntries('+', '.join(y for x,y in args)+');'
    b=base[:start]+call+base[end:]
    b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
    if mode>=8:
        b=b.replace('Rva00501656 &info','Rva00501656 *infoPtr').replace('{\n'+inner,'{\n Rva00501656 &info = *infoPtr;\n'+inner).replace('GatherRegionEntries(region, info,','GatherRegionEntries(region, &info,').replace('m_RegionInfo, info, region);','m_RegionInfo, &info, region);')
    r=run(b,'gather-scopeextract-'+str(mode),'gather')
    if r.get('exact'):break
