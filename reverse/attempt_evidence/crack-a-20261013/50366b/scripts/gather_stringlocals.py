from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('orig',orig),('best',best)]:
  for mask in range(1,16):
    b=base
    for n,(name,key) in enumerate([('commandPoints','IncreaseCommandPoints'),('spawnArmy','SpawnArmy'),('strengthen','StrengthenArmy'),('upgrade','UpgradeTroops')]):
      if mask&(1<<n):
        old='BuildingNuggetView *'+name+' = building->m_template->findNugget(AsciiString("'+key+'"));'
        new='BuildingNuggetView *'+name+'; { AsciiString nuggetName("'+key+'"); '+name+' = building->m_template->findNugget(nuggetName); }'
        b=b.replace(old,new)
    r=run(b,'gather-stringlocals-'+scope+'-'+str(mask),'gather')
    if r.get('exact'):raise SystemExit()
