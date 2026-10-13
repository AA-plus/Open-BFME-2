from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for mode in range(16):
 b=base
 if mode&1:
  b=b.replace('for (unsigned int i = 0; i < regions->size();','for (int i = 0; (unsigned int)i < regions->size();').replace('for (int p = 0; p < playerCount; ++p)','for (i = 0; i < playerCount; ++i)').replace('rva002B52A8(p)','rva002B52A8(i)')
 if mode&2:
  b=b.replace('for (unsigned int j = 0;','for (unsigned int j = 0;')
  b=b.replace('for (unsigned int a = 0, armyCount = armies.size(); a < armyCount; ++a)','unsigned int armyCount = armies.size();\n\t\tfor (j = 0; j < armyCount; ++j)').replace('armies[a]','armies[j]')
  b=b.replace('for (unsigned int j = 0;','for (j = 0;').replace('\tm_PlayerInfo.clear();','\tunsigned int j;\n\tm_PlayerInfo.clear();')
 if mode&4:
  b=b.replace('int entryCount = summary->m_entries.size();','armyCount = summary->m_entries.size();').replace('e < entryCount','e < (int)armyCount')
  # This variant changes the army loop limit and is rejected before compilation as semantically different.
  continue
 if mode&8:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
 r=run(b,'gather-counterreuse-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
