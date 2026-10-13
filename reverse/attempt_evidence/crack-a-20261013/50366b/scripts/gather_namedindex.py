from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=(ROOT/'build/crack-a/gather-base/c1.cpp').read_text()
needle='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
for scope,base in [('best',best),('orig',orig)]:
 for mode in range(12):
  ty=['_STL::pair<int,int>','_STL::pair<const int,int>','_STL::pair<int,Rva00501656*>'][mode%3]
  rhs='(int)&it->second' if mode%3!=2 else '&it->second'
  decl=ty+' regionIndexPair(info.m_regionID,'+rhs+');'
  arg='regionIndexPair' if mode%3!=2 else '*reinterpret_cast<const _STL::pair<int,int>*>(&regionIndexPair)'
  b=base.replace(needle,decl+'\n\t\tm_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), '+arg+');')
  if mode>=3 and mode<6:b=b.replace(decl,ty+' regionIndexPair; regionIndexPair.first=info.m_regionID; regionIndexPair.second='+rhs+';')
  if mode>=6:b=b.replace('RegionInfoMap::iterator it = m_RegionInfo.insert','it = m_RegionInfo.insert').replace('Rva00501656 info;','RegionInfoMap::iterator it;\n\t\tRva00501656 info;' if mode>=9 else 'Rva00501656 info;\n\t\tRegionInfoMap::iterator it;')
  r=run(b,'gather-namedindex-'+scope+'-'+str(mode),'gather')
  if r.get('exact'):raise SystemExit()
