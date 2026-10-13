from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
end='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
forms=[('do {','continue; } while(false);'),('do {','break; } while(true);'),('for (;;) {','break; }'),('while(true) {','break; }'),('{','goto regionInserted; } regionInserted:;'),('if(true) {','goto regionInserted; } regionInserted:;')]
for n,(a,z) in enumerate(forms):
  for mode in range(3):
    b=base
    before=decl if mode==0 else '_STL::vector<const ModuleData *> buildings;' if mode==1 else 'Rva00501656 info;'
    b=b.replace(before,a+'\n'+before).replace(end,end+'\n'+z)
    r=run(b,'gather-pairloop-exit-'+str(n)+'-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
