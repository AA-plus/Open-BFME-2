from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
last='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for mode in range(12):
 helper=spec+'''struct RegionCondition : _STL::pair<int,Rva00501656> {
 __forceinline RegionCondition(const int&a,const Rva00501656&b):_STL::pair<int,Rva00501656>(a,b){}
 __forceinline operator int()const{return 1;}
 };\n'''
 start=['if','while','switch'][mode%3]+'(RegionCondition regionPair=RegionCondition(info.m_ownerID,info)) {'
 end='}' if mode%3==0 else 'break;}'
 if mode%3==2:start+='default:'
 b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace(decl,start).replace(last,last+'\n'+end)
 b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), static_cast<const _STL::pair<int,Rva00501656>&>(regionPair)')
 if mode>=3 and mode<6 or mode>=9:b=b.replace('operator int','operator bool').replace('return 1','return true')
 if mode>=6:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace(end+'\n\t\t}',end)
 r=run(b,'gather-paircondition-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
