from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
spec='namespace _STL { template<> __forceinline pair<int,Rva00501776>::pair(const int &a,const Rva00501776 &b):first(a),second(b){} template<> __forceinline pair<int,Rva00501E3FElement>::pair(const int &a,const Rva00501E3FElement &b):first(a),second(b){} }\n'
for scope,base in [('orig',orig),('best',best)]:
  for mode in range(6):
    start=base.index('\tint playerCount =')
    end=base.rfind('\n}')
    inner=base[start:end]
    if mode<2:
      helper='__forceinline void GatherPlayers(PlayerInfoMap& m_PlayerInfo,RegionInfoMap& m_RegionInfo,IntIntMap& m_RegionInfoByRegion){\n'+inner+'\n}\n'
      b=base[:start]+'GatherPlayers(m_PlayerInfo,m_RegionInfo,m_RegionInfoByRegion);'+base[end:]
      b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
    elif mode<4:
      helper='__forceinline void LWAIWorldInformation::GatherPlayers(){\n'+inner+'\n}\n'
      b=base[:start]+'GatherPlayers();'+base[end:]
      b=b.replace('void GatherWorldInformation();','void GatherWorldInformation();\n __forceinline void GatherPlayers();').replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
    else:
      start=base.index('\t\tLWAIPlayerView *player =')
      end=base.index('\n\t}\n}',start)
      inner=base[start:end]
      helper='__forceinline void GatherPlayer(int p,PlayerInfoMap& m_PlayerInfo,RegionInfoMap& m_RegionInfo,IntIntMap& m_RegionInfoByRegion){\n'+inner+'\n}\n'
      b=base[:start]+'GatherPlayer(p,m_PlayerInfo,m_RegionInfo,m_RegionInfoByRegion);'+base[end:]
      b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()')
    if mode&1:b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
    r=run(b,'gather-playerextract-'+scope+'-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
