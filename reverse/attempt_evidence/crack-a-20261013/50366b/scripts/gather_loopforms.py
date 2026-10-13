from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for mode in range(1,8):
    b=base
    if mode&1:
      b=b.replace('for (unsigned int i = 0; i < regions->size(); ++i)','unsigned int i = 0;\n\twhile (i < regions->size())').replace('\n\t}\n\n\tint playerCount','\n\t++i;\n\t}\n\n\tint playerCount')
    if mode&2:
      b=b.replace('for (unsigned int j = 0; j < buildings.size(); ++j)','unsigned int j = 0;\n\t\twhile (j < buildings.size())').replace('\n\t\t}\n\n\t\t_STL::pair<int, Rva00501656>','\n\t\t++j;\n\t\t}\n\n\t\t_STL::pair<int, Rva00501656>')
    if mode&4:
      b=b.replace('for (int p = 0; p < playerCount; ++p)','int p = 0;\n\twhile (p < playerCount)').replace('m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);','m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);\n\t\t++p;')
    r=run(b,'gather-loopform-'+scope+'-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
for mode in range(8):
    b=(ROOT/'build/crack-a'/('gather-calltemporary-'+str(mode))/'c1.cpp').read_text()
    b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('info));\n\t\t}','info));').replace('info);\n\t\t}','info);')
    r=run(b,'gather-calltemp-orig-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
