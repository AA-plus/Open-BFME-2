from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for mode in range(1,16):
    b=base
    if mode&1:
      end='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
      b=b.replace(end,end+'\n\t\tcontinue;')
    if mode&2:b=b.replace('m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);','m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);\n\t\tcontinue;')
    if mode&4:b=b.replace('regionArmies.insert(where, armyPair);\n\t\t\t}\n\t\t}','regionArmies.insert(where, armyPair);\n\t\t\t}\n\t\t\tcontinue;\n\t\t}')
    if mode&8:b=b.replace('info.m_40.push_back((ScienceType)building->m_id);\n\t\t\t}\n\t\t}','info.m_40.push_back((ScienceType)building->m_id);\n\t\t\t}\n\t\t\tcontinue;\n\t\t}')
    r=run(b,'gather-continue-'+scope+'-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
