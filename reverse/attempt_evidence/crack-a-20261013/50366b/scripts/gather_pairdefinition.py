from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for mode in range(12):
    decl='''namespace _STL {
template<> struct pair<int,Rva00501656> {
    typedef int first_type; typedef Rva00501656 second_type;
    int first; Rva00501656 second;
    __forceinline pair(const int &a,const Rva00501656 &b):first(a),second(b){}
    DTOR
    COPY
}; }
'''.replace('DTOR','__forceinline ~pair(){}' if mode&1 else '').replace('COPY','__forceinline pair(const pair& b):first(b.first),second(b.second){}' if mode&2 else '')
    if mode>=4 and mode<8:decl=decl.replace('const int &a','int a')
    if mode>=8:decl=decl.replace('int first; Rva00501656 second;','int first; struct Payload: Rva00501656 { __forceinline Payload(const Rva00501656& b):Rva00501656(b){} }; Payload second;')
    b=base.replace('typedef _STL::multimap<int, Rva00501656> RegionInfoMap;',decl+'typedef _STL::multimap<int, Rva00501656> RegionInfoMap;')
    r=run(b,'gather-pairdefinition-'+str(mode),'gather')
    if r.get('exact'):break
for mode in range(4):
    b=(ROOT/'build/crack-a'/('gather-insertform-'+str(mode))/'c1.cpp').read_text()
    b=b.replace('it(InsertRegion(m_RegionInfo,regionPair))','it(static_cast<RegionInfoMap::iterator::_Link_type>(InsertRegion(m_RegionInfo,regionPair)))')
    r=run(b,'gather-insertnode-'+str(mode),'gather')
    if r.get('exact'):break
