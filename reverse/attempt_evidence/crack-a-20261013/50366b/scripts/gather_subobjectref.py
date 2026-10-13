from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
ty='_STL::pair<int,Rva00501656>'
expressions=[
'*reinterpret_cast<const '+ty+'*>(&regionPair.first)',
'*reinterpret_cast<const '+ty+'*>(reinterpret_cast<const char*>(&regionPair.second)-4)',
'*reinterpret_cast<const '+ty+'*>(reinterpret_cast<const int*>(&regionPair.second)-1)',
'*static_cast<const '+ty+'*>(static_cast<const void*>(&regionPair.first))',
'*reinterpret_cast<const '+ty+'*>(reinterpret_cast<unsigned int>(&regionPair))',
'*(&regionPair)',
'*reinterpret_cast<const '+ty+'*>(&regionPair)',
]
for n,expr in enumerate(expressions):
    for local in [False,True]:
        b=base
        if local:
            b=b.replace('RegionInfoMap::iterator it =', 'const '+ty+'& pairView = '+expr+';\n\t\tRegionInfoMap::iterator it =',1)
            expr2='pairView'
        else:expr2=expr
        b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), '+expr2)
        r=run(b,'gather-subobject-'+str(n)+'-'+str(local),'gather')
        if r.get('exact'):raise SystemExit()
