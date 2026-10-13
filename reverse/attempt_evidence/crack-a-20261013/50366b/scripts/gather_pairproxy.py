from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(16):
 helper='''struct RegionArgs { const int* a; const Rva00501656* b; };
 __forceinline RegionArgs MakeRegionArgs(const int&a,const Rva00501656&b){RegionArgs r={&a,&b};return r;}
 struct RegionPairLocal {
 int first; Rva00501656 second;
 __forceinline RegionPairLocal(RegionArgs p):first(*p.a),second(*p.b){}
 };
'''
 if mode&1:helper=helper.replace('RegionPairLocal(RegionArgs p)','RegionPairLocal(const RegionArgs& p)')
 if mode&2:helper=helper.replace('const int* a;','int a;').replace('r={&a,&b}','r={a,&b}').replace('first(*p.a)','first(p.a)')
 if mode&4:helper=helper.replace('struct RegionPairLocal {\n int first; Rva00501656 second;','struct RegionPairLocal : _STL::pair<int,Rva00501656> {').replace(':first(*p.a),second(*p.b)',':_STL::pair<int,Rva00501656>(*p.a,*p.b)').replace(':first(p.a),second(*p.b)',':_STL::pair<int,Rva00501656>(p.a,*p.b)')
 b=base.replace('class LWAIWorldInformation',helper+'\nclass LWAIWorldInformation').replace(decl,'RegionPairLocal regionPair = MakeRegionArgs(info.m_ownerID,info);').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), reinterpret_cast<const _STL::pair<int,Rva00501656>&>(regionPair)')
 if mode&8:b=b.replace('RegionPairLocal regionPair = MakeRegionArgs(info.m_ownerID,info);','RegionPairLocal regionPair(MakeRegionArgs(info.m_ownerID,info));')
 r=run(b,'gather-pairproxy-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
