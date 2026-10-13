from trial import *
for n in range(6):
    b=(ROOT/'build/crack-a'/('gather-makeinline-'+str(n%2))/'c1.cpp').read_text()
    b='#pragma inline_depth(255)\n#pragma inline_recursion(on)\n#pragma warning(default:4714)\n'+b
    if n&2:b=b.replace('// cl:','// cl: /Ob2 /W4',1)
    if n&4:b=b.replace('/O1','/O2')
    r=run(b,'gather-makedepth-'+str(n),'gather')
    if r.get('exact'):break
for n in range(6):
    b=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
    # Specialize the const-key pair's copy/converting constructor so its declaration context is controlled.
    old='template <> RegionInfoMap::iterator RegionInfoMap::insert(RegionInfoMap::iterator, const RegionInfoMap::value_type &);'
    spec='template<> template<> __declspec(noinline) pair<const int,Rva00501656>::pair(const pair<int,Rva00501656>& p):first(p.first),second(p.second) {}'
    if n&1:spec=spec.replace('__declspec(noinline)','')
    b=b.replace(old,spec+'\n'+old)
    if n>=2:b=b.replace('_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);','const _STL::pair<int, Rva00501656>& regionPair = _STL::pair<int, Rva00501656>(info.m_ownerID, info);')
    if n>=4:b=b.replace('namespace _STL {\ntemplate <> void PlayerInfoMap', '#pragma inline_depth(1)\nnamespace _STL {\ntemplate <> void PlayerInfoMap')
    r=run(b,'gather-copycontext-'+str(n),'gather')
    if r.get('exact'):break
