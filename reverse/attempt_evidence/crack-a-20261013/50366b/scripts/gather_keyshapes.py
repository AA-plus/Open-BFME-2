from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(10):
    first=['int first;','volatile int first;','int first:32;','volatile int first:32;','const int first;'][mode%5]
    helper='struct RegionPairLocal { '+first+' '+('volatile ' if mode>=5 else '')+'Rva00501656 second; __forceinline RegionPairLocal(const int& a,const Rva00501656& b):first(a),second(b){} };\n'
    b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace(decl,'RegionPairLocal regionPair(info.m_ownerID,info);').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), *reinterpret_cast<const _STL::pair<int,Rva00501656>*>(&regionPair)')
    r=run(b,'gather-keyshape-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
for mode in range(4):
    helper='''struct RegionKey { int first[1]; __forceinline RegionKey(const int& a){first[0]=a;} };
struct RegionPairLocal : RegionKey { Rva00501656 second; __forceinline RegionPairLocal(const int& a,const Rva00501656& b):RegionKey(a),second(b){} };\n'''
    if mode&1:helper=helper.replace('int first[1]','volatile int first[1]')
    if mode&2:helper=helper.replace('struct RegionPairLocal : RegionKey {','struct RegionPairLocal { RegionKey key;').replace(':RegionKey(a),second(b)',':key(a),second(b)')
    b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace(decl,'RegionPairLocal regionPair(info.m_ownerID,info);').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), *reinterpret_cast<const _STL::pair<int,Rva00501656>*>(&regionPair)')
    r=run(b,'gather-keyarray-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
