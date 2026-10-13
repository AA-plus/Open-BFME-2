from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
start=base.index('\t\t_STL::pair<int, Rva00501656> regionPair')
end=base.index('\n\t\t}',start)
for mode in range(16):
 helper='''struct RegionInserter {
 _STL::pair<int,Rva00501656> pair;
 __forceinline RegionInserter(const Rva00501656& info,RegionInfoMap& map,IntIntMap& index):pair(info.m_ownerID,info) {
 RegionInfoMap::iterator it=map.insert(map.begin(),pair);
 index.insert(index.begin(),_STL::make_pair(info.m_regionID,(int)&it->second));
 }
};
'''
 if mode&1:helper=helper.replace('const Rva00501656& info','Rva00501656& info')
 if mode&2:helper=helper.replace('struct RegionInserter {\n _STL::pair<int,Rva00501656> pair;','struct RegionInserter : _STL::pair<int,Rva00501656> {').replace(':pair(info.m_ownerID,info)',':_STL::pair<int,Rva00501656>(info.m_ownerID,info)').replace('map.begin(),pair','map.begin(),*this')
 if mode&4:helper='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'+helper
 b=base[:start]+'\t\tRegionInserter '+('inserted' if mode&8 else '')+'(info,m_RegionInfo,m_RegionInfoByRegion);'+base[end:]
 b=b.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation')
 r=run(b,'gather-inserter-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
