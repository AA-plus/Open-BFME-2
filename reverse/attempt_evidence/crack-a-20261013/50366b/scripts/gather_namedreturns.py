from trial import *
for sc in ['gather-base','gather-scope-4']:
 base=(ROOT/'build/crack-a'/sc/'c1.cpp').read_text()
 for mode in range(1,16):
  b=base
  if mode&1:b=b.replace('((IntIntTree *)&m_RegionInfo)->equal_range(player->getID());','_STL::pair<IntIntTree::iterator,IntIntTree::iterator> regionRange = ((IntIntTree *)&m_RegionInfo)->equal_range(player->getID());')
  if mode&2:b=b.replace('m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(),','IntIntMap::iterator indexResult=m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(),')
  if mode&4:b=b.replace('regionArmies.insert(where, armyPair);','ArmyInfoMap::iterator armyResult=regionArmies.insert(where, armyPair);')
  if mode&8:b=b.replace('m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);','PlayerInfoMap::iterator playerResult=m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);')
  r=run(b,'gather-namedreturns-'+sc+'-'+str(mode),'gather')
  if r.get('exact'):raise SystemExit()
