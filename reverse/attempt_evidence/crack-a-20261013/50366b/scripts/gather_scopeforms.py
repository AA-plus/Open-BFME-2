from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
end='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
for mode in range(12):
    b=base
    if mode<6:
        if mode==0:b=b.replace(decl,'for ('+decl[:-1]+'; ; ) {').replace(end,end+'\nbreak;\n}')
        elif mode==1:b=b.replace(decl,'for ('+decl[:-1]+'; true; ) {').replace(end,end+'\nbreak;\n}')
        elif mode==2:b=b.replace(decl,'if (true) {\n'+decl).replace(end,end+'\n}')
        elif mode==3:b=b.replace(decl,'do {\n'+decl).replace(end,end+'\n} while(false);')
        elif mode==4:b=b.replace(decl,'switch(0){default:\n'+decl).replace(end,end+'\nbreak;\n}')
        elif mode==5:b=b.replace(decl,'goto constructRegionPair; constructRegionPair:\n'+decl)
    else:
        vector='_STL::vector<const ModuleData *> buildings;'
        if mode==6:b=b.replace(vector,'for ('+vector[:-1]+'; ; ) {').replace(end,end+'\nbreak;\n}')
        elif mode==7:b=b.replace(vector,'if (true) {\n'+vector).replace(end,end+'\n}')
        elif mode==8:b=b.replace(vector,'do {\n'+vector).replace(end,end+'\n} while(false);')
        elif mode==9:b=b.replace('Rva00501656 info;','for (Rva00501656 info; ; ) {').replace('\n\tint playerCount','\n\tint playerCount')
        elif mode==10:b=b.replace(decl,'for ('+decl[:-1]+'; ; ) {').replace(end,end+'\ngoto regionPairDone;\n}\nregionPairDone:;')
        elif mode==11:b=b.replace(decl,'if (true) {\n'+decl).replace(end,end+'\ngoto regionPairDone;\n}\nregionPairDone:;')
        if mode==9:b=b.replace('\n\t}\n\n\tint playerCount','\n\tbreak;}\n\t}\n\n\tint playerCount')
    r=run(b,'gather-scopeform-'+str(mode),'gather')
    if r.get('exact'):break
