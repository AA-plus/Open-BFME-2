from trial import *
for n in [0,1,4,5,8,9]:
    b=(ROOT/'build/crack-a'/('gather-convertwrapper-'+str(n))/'c1.cpp').read_text()
    b=b.replace('_STL::pair<int,Rva00501656>& p','_STL::pair<const int,Rva00501656>& p').replace('_STL::pair<int, Rva00501656> regionPair','_STL::pair<const int, Rva00501656> regionPair')
    r=run(b,'gather-constcopywrap-'+str(n),'gather')
    if r.get('exact'):break
for n in range(6):
    b=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
    needle='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);'
    b=b.replace('_STL::pair<int, Rva00501656> regionPair','_STL::pair<const int, Rva00501656> regionPair')
    # Constructor copy remains a real class construction; route its expression through a reference conversion.
    new='RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), CopyRegionPair(regionPair));'
    h='''struct CopyRegionPair : RegionInfoMap::value_type {
      __forceinline CopyRegionPair(const RegionInfoMap::value_type& p):RegionInfoMap::value_type(p){}
      __forceinline operator const RegionInfoMap::value_type&()const{return *this;}
    };\n'''
    if n&1:h=h.replace('const RegionInfoMap::value_type& p','RegionInfoMap::value_type& p')
    if n>=2:h=h.replace('return *this;','return *reinterpret_cast<const RegionInfoMap::value_type*>(this);')
    if n>=4:b=b.replace('_STL::pair<const int, Rva00501656> regionPair','const _STL::pair<const int, Rva00501656> regionPair')
    b=b.replace('class LWAIWorldInformation',h+'class LWAIWorldInformation').replace(needle,new)
    r=run(b,'gather-constcopyderive-'+str(n),'gather')
    if r.get('exact'):break
