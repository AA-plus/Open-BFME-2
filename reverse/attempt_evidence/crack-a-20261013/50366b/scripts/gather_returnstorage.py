from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
helper='''struct RegionPlacement { void *p; RegionPlacement(void *q):p(q){} };
__forceinline void* operator new(unsigned int,RegionPlacement p) throw(){return p.p;}
struct RegionRaw { int first; char second[sizeof(Rva00501656)]; };
__forceinline RegionRaw MakeRegionRaw(const int& a,const Rva00501656& b) {
    RegionRaw result; result.first=a; new(RegionPlacement(result.second)) Rva00501656(b); return result;
}
struct RegionOwner : RegionRaw {
    __forceinline RegionOwner(const RegionRaw& r):RegionRaw(r){}
    __forceinline RegionOwner(const int& a,const Rva00501656& b):RegionRaw(MakeRegionRaw(a,b)){}
    __forceinline ~RegionOwner(){reinterpret_cast<Rva00501656*>(second)->~Rva00501656();}
    __forceinline const _STL::pair<int,Rva00501656>& get()const{return *reinterpret_cast<const _STL::pair<int,Rva00501656>*>(this);}
};
'''
for mode in range(6):
    b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation')
    decl=['RegionOwner regionPair(MakeRegionRaw(info.m_ownerID,info));','RegionOwner regionPair(info.m_ownerID,info);','const RegionOwner& regionPair = RegionOwner(MakeRegionRaw(info.m_ownerID,info));'][mode%3]
    b=b.replace('_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);',decl).replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), regionPair.get()')
    if mode>=3:b=b.replace('struct RegionOwner : RegionRaw {','struct RegionOwner {\n RegionRaw raw;').replace(':RegionRaw(r)',':raw(r)').replace(':RegionRaw(MakeRegionRaw(a,b))',':raw(MakeRegionRaw(a,b))').replace('reinterpret_cast<Rva00501656*>(second)','reinterpret_cast<Rva00501656*>(raw.second)')
    r=run(b,'gather-returnstorage-'+str(mode),'gather')
    if r.get('exact'):break
