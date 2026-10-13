from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
helper='''struct RegionPlacement { void *p; RegionPlacement(void *q):p(q){} };
__forceinline void *operator new(unsigned int,RegionPlacement p) throw(){return p.p;}
struct RegionPairLifetime {
    typedef _STL::pair<int,Rva00501656> P;
    P *const p;
    __forceinline RegionPairLifetime(void *storage,const int &a,const Rva00501656& b):p(new(RegionPlacement(storage)) P(a,b)){}
    __forceinline ~RegionPairLifetime(){p->~P();}
    __forceinline const P& get()const{return *p;}
};
'''
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for mode in range(8):
    b=base.replace('class LWAIWorldInformation',spec+helper+'class LWAIWorldInformation')
    storage='__declspec(align(4)) char regionStorage[92];\n\t\t'
    before=['Rva00501656 info;','{\n\t\t_STL::vector<const ModuleData *> buildings;','_STL::pair<int, Rva00501656> regionPair','LivingWorldRegion *region ='][mode%4]
    b=b.replace(before,storage+before,1).replace(decl,'RegionPairLifetime regionPair(regionStorage,info.m_ownerID,info);').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), regionPair.get()')
    if mode&4:
        b=b.replace('P *const p;','P &p;').replace(':p(new(RegionPlacement(storage)) P(a,b))',':p(*new(RegionPlacement(storage)) P(a,b))').replace('p->~P();','p.~P();').replace('return *p;','return p;')
    r=run(b,'gather-buffer-'+str(mode),'gather')
    if r.get('exact'):break
