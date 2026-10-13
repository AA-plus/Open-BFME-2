from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(12):
    b=base
    if mode<6:
        t='_STL::pair<int,Rva00501656>'
        wrapper='struct LocalRegionPair { '+t+' value; __forceinline LocalRegionPair(int a,const Rva00501656 &b):value(a,b){} '+('__forceinline ~LocalRegionPair(){}' if mode&1 else '')+' };\n'
        if mode in (2,3):wrapper='struct LocalRegionPair : '+t+' { __forceinline LocalRegionPair(int a,const Rva00501656 &b):'+t+'(a,b){} '+('__forceinline ~LocalRegionPair(){}' if mode&1 else '')+' };\n'
        b=b.replace(decl,wrapper+'LocalRegionPair regionPair(info.m_ownerID,info);')
        expr='regionPair.value' if mode not in (2,3) else 'static_cast<'+t+'&>(regionPair)'
        b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), '+expr)
        if mode>=4:b=b.replace('struct LocalRegionPair {','struct __declspec(align(4)) LocalRegionPair {')
    else:
        # Names may affect deterministic symbol-table allocation ties.
        b=re.sub(r'\bregionPair\b',['regionInfoPair','pair','regionInfo','tmpRegionInfo','regionEntry','entry'][mode-6],b)
    r=run(b,'gather-wrapper-'+str(mode),'gather')
    if r.get('exact'):break
