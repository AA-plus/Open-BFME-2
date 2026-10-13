from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for n,marker in enumerate(['\tm_PlayerInfo.clear();','\tLWAIRegionManager *manager','\t\tRva00501656 info;','\t\t_STL::vector<const ModuleData *> buildings;']):
    for const in ['', 'const ']:
      b=base.replace('_STL::vector<const ModuleData *> buildings;','_STL::vector<const ModuleData *> buildings(buildingAllocator);')
      if marker.endswith('buildings;'):marker=marker.replace('buildings;','buildings(buildingAllocator);')
      b=b.replace(marker,const+'_STL::allocator<const ModuleData *> buildingAllocator;\n'+marker,1)
      r=run(b,'gather-allocator-'+scope+'-'+str(n)+('-const' if const else ''),'gather')
      if r.get('exact'):raise SystemExit()
