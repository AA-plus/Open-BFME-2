from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
helper='''struct RegionPlacement { void *p; RegionPlacement(void *q):p(q){} };
__forceinline void* operator new(unsigned int,RegionPlacement p) throw(){return p.p;}
typedef _STL::pair<int,Rva00501656> RegionPairValue;
struct RegionReady{};
__forceinline RegionReady InitializeRegion(void *where,const int& a,const Rva00501656& b){new(RegionPlacement(where)) RegionPairValue(a,b);return RegionReady();}
struct RegionOwner {
    __declspec(align(4)) char data[sizeof(RegionPairValue)];
    __forceinline RegionOwner(RegionReady){}
    __forceinline RegionOwner(void *where,const int& a,const Rva00501656& b){new(RegionPlacement(where)) RegionPairValue(a,b);}
    __forceinline ~RegionOwner(){reinterpret_cast<RegionPairValue*>(data)->~RegionPairValue();}
    __forceinline const RegionPairValue& get()const{return *reinterpret_cast<const RegionPairValue*>(data);}
};
'''
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for mode in range(8):
    b=base.replace('class LWAIWorldInformation',spec+helper+'class LWAIWorldInformation')
    decl='RegionOwner regionPair('+('InitializeRegion(&regionPair,info.m_ownerID,info)' if mode&1 else '&regionPair,info.m_ownerID,info')+');'
    if mode&2:decl=decl.replace('&regionPair','regionPair.data')
    b=b.replace('_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);',decl).replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), regionPair.get()')
    if mode&4:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
    r=run(b,'gather-selfstorage-'+str(mode),'gather')
    if r.get('exact'):break
