from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for mode in range(12):
    helper='''struct RegionConversion {
    RegionInfoMap::value_type value;
    __forceinline RegionConversion(const _STL::pair<int,Rva00501656>& p):value(p){}
    __forceinline operator const RegionInfoMap::value_type&()const{return value;}
    DTOR
};
'''.replace('DTOR','__forceinline ~RegionConversion(){}' if mode&1 else '')
    if mode>=4 and mode<8:
        helper=helper.replace('struct RegionConversion {','struct RegionConversion : RegionInfoMap::value_type {').replace('RegionInfoMap::value_type value;','').replace(':value(p)',':RegionInfoMap::value_type(p)').replace('return value;','return *this;')
    if mode>=8:
        helper='''struct RegionPlacement { void *p; RegionPlacement(void *q):p(q){} };
__forceinline void* operator new(unsigned int,RegionPlacement p) throw(){return p.p;}
struct RegionConversion {
    typedef RegionInfoMap::value_type V;
    __declspec(align(4)) char data[sizeof(V)];
    __forceinline RegionConversion(const _STL::pair<int,Rva00501656>& p){new(RegionPlacement(data)) V(p);}
    __forceinline ~RegionConversion(){reinterpret_cast<V*>(data)->~V();}
    __forceinline operator const V&()const{return *reinterpret_cast<const V*>(data);}
};
'''
    b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), RegionConversion(regionPair)')
    if mode&2:
        b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
    if mode==9 or mode==11:b=b.replace('char data[sizeof(V)]','int data[sizeof(V)/sizeof(int)]')
    r=run(b,'gather-convertwrapper-'+str(mode),'gather')
    if r.get('exact'):break
