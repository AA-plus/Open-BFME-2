from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for n,(ty,name,old,new) in enumerate([
    ('unsigned int','i','for (unsigned int i = 0;','for (i = 0;'),
    ('unsigned int','j','for (unsigned int j = 0;','for (j = 0;'),
    ('int','p','for (int p = 0;','for (p = 0;'),
    ('unsigned int','a, armyCount','for (unsigned int a = 0, armyCount = armies.size();','for (a = 0, armyCount = armies.size();'),
    ('int','e','for (int e = 0;','for (e = 0;')]):
    for where in range(5):
      decl=ty+' '+name+';\n'
      b=base.replace(old,new)
      marker=['\tm_PlayerInfo.clear();','\tLWAIRegionManager *manager','\t\tRva00501656 info;','\tint playerCount','\t\t_STL::vector<const ModuleData *> buildings;'][where]
      if (name=='i' and where in [2,4]) or (name in ['i','j'] and where==3) or (name in ['p','a, armyCount','e'] and where in [2,4]):continue
      b=b.replace(marker,decl+marker,1)
      r=run(b,'gather-counter-'+scope+'-'+str(n)+'-'+str(where),'gather')
      if r.get('exact'):raise SystemExit()
  for mode in range(7):
    b=base
    if mode&1:b=b.replace('for (unsigned int a = 0, armyCount = armies.size();','unsigned int armyCount = armies.size();\n\t\tfor (unsigned int a = 0;')
    if mode&2:b=b.replace('for (unsigned int i = 0;', 'unsigned int i = 0;\n\tfor (;')
    if mode&4:b=b.replace('for (unsigned int j = 0;', 'unsigned int j = 0;\n\t\tfor (;')
    r=run(b,'gather-counter-combo-'+scope+'-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
