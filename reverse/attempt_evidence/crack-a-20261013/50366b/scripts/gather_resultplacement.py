from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
place='''struct RegionPlacement { void *p; RegionPlacement(void *q):p(q){} };
__forceinline void* operator new(unsigned int,RegionPlacement p) throw(){return p.p;}
'''
needle='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);'
for mode in range(8):
    helper=place+'''struct RegionInsertResult {
      __declspec(align(4)) char data[sizeof(RegionInfoMap::iterator)];
      __forceinline RegionInsertResult(RegionInfoMap& map,const _STL::pair<int,Rva00501656>& pair) {
        LOCAL
        new(RegionPlacement(data)) RegionInfoMap::iterator(map.insert(map.begin(),VALUE));
      }
      __forceinline RegionInfoMap::value_type* operator->()const {return reinterpret_cast<const RegionInfoMap::iterator*>(data)->operator->();}
    };\n'''
    helper=helper.replace('LOCAL','RegionInfoMap::value_type converted(pair);' if mode&1 else '').replace('VALUE','converted' if mode&1 else 'pair')
    if mode&2:
        helper=helper.replace('struct RegionInsertResult {','struct RegionInsertResult : RegionInfoMap::iterator {').replace('__declspec(align(4)) char data[sizeof(RegionInfoMap::iterator)];','').replace('RegionPlacement(data)','RegionPlacement(this)').replace('reinterpret_cast<const RegionInfoMap::iterator*>(data)','static_cast<const RegionInfoMap::iterator*>(this)')
    b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace(needle,'RegionInsertResult it(m_RegionInfo,regionPair);')
    if mode&4:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
    r=run(b,'gather-resultplacement-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
