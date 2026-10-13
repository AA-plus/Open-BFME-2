from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
needle='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);'
place='struct RegionPlacement {void*p;RegionPlacement(void*q):p(q){}}; __forceinline void*operator new(unsigned int,RegionPlacement p)throw(){return p.p;}\n'
for mode in range(16):
 arg='RegionInfoMap::value_type pair' if not mode&1 else 'const RegionInfoMap::value_type pair'
 if mode//2%4==0:
  helper='__forceinline RegionInfoMap::iterator InsertRegion(RegionInfoMap& map,'+arg+'){return map.insert(map.begin(),pair);}'
  call='RegionInfoMap::iterator it=InsertRegion(m_RegionInfo,regionPair);'
 elif mode//2%4==1:
  helper='__forceinline RegionInfoMap::iterator::_Link_type InsertRegion(RegionInfoMap& map,'+arg+'){return (RegionInfoMap::iterator::_Link_type)map.insert(map.begin(),pair)._M_node;}'
  call='RegionInfoMap::iterator it(InsertRegion(m_RegionInfo,regionPair));'
 elif mode//2%4==2:
  helper=place+'''struct RegionResult {
 __declspec(align(4)) char data[4];
 __forceinline RegionResult(RegionInfoMap& map,ARG){new(RegionPlacement(data)) RegionInfoMap::iterator(map.insert(map.begin(),pair));}
 __forceinline RegionInfoMap::value_type*operator->() const{return reinterpret_cast<const RegionInfoMap::iterator*>(data)->operator->();}
 };'''.replace('ARG',arg)
  call='RegionResult it(m_RegionInfo,regionPair);'
 else:
  helper=place+'__forceinline void InsertRegion(RegionInfoMap& map,void* result,'+arg+'){new(RegionPlacement(result)) RegionInfoMap::iterator(map.insert(map.begin(),pair));}'
  call='__declspec(align(4)) char itStorage[4]; InsertRegion(m_RegionInfo,itStorage,regionPair); RegionInfoMap::iterator& it=*reinterpret_cast<RegionInfoMap::iterator*>(itStorage);'
 b=base.replace('class LWAIWorldInformation',helper+'\nclass LWAIWorldInformation').replace(needle,call)
 if mode&8:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
 r=run(b,'gather-valueinsert-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
