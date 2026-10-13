from trial import *
for n in range(12):
 b=(ROOT/'build/crack-a'/('gather-extractforce-'+str(n%6))/'c1.cpp').read_text()
 b=b.replace('_STL::vector<const ModuleData *> &buildings','_STL::vector<const ModuleData *> buildings')
 if n>=6:b=b.replace('\t\t{\nGatherRegionEntries','GatherRegionEntries').replace('());\n\t\t}', '());').replace('region);\n\t\t}', 'region);').replace('m_RegionInfoByRegion);\n\t\t}', 'm_RegionInfoByRegion);')
 r=run(b,'gather-buildparam-'+str(n),'gather')
 if r.get('exact'):raise SystemExit()
