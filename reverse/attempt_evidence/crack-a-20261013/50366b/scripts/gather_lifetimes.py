from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for n,(ty,name,init) in enumerate([
('Rva00501656','info',''),
('_STL::vector<const ModuleData *>','buildings',''),
('Rva00501776','playerInfo',''),
('_STL::vector<unsigned int>','armies','player->m_armies'),
('_STL::pair<int, Rva00501656>','regionPair','info.m_ownerID, info'),
('_STL::pair<int, Rva00501776>','playerPair','player->getID(), playerInfo'),
('_STL::pair<int, Rva00501E3FElement>','armyPair','player->getID(), armyInfo')]):
    old=ty+' '+name+(' = '+init if name=='armies' else '('+init+')' if init else '')+';'
    for scope,base in [('best',best),('orig',orig)]:
        for mode in range(3):
            new=ty+(' &' if mode==0 else ' const &' if mode==1 else ' ')+name+' = '+ty+'('+init+');'
            if mode==1 and name in ['info','buildings','playerInfo']:
                new=ty+' const &'+name+'Const = '+ty+'('+init+'); '+ty+' &'+name+' = const_cast<'+ty+'&>('+name+'Const);'
            b=base.replace(old,new)
            assert b!=base,old
            r=run(b,'gather-lifetime-'+str(n)+'-'+scope+'-'+str(mode),'gather')
            if r.get('exact'):raise SystemExit()
