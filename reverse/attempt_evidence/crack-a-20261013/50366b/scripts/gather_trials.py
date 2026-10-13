from trial import *
base=(ROOT/'reverse/attempts/0x0050366b.cpp').read_text()
start=base.index('void LWAIWorldInformation::GatherWorldInformation()')
prefix,body=base[:start],base[start:]
candidates=[]
def add(tag,b,p=prefix):candidates.append((tag,p+b))
# Identical container specialization in disjoint lexical lifetimes.
add('same-vector',body.replace('_STL::vector<const ModuleData *> buildings;','_STL::vector<unsigned int> buildings;').replace('rva003F287F(buildings)','rva003F287F((_STL::vector<const ModuleData *>&)buildings)'))
# Explicit lifetime scopes, without changing construction/destruction order.
for mode in range(7):
    b=body
    if mode&1:b=b.replace('\tLWAIRegionManager *manager','\t{\n\tLWAIRegionManager *manager').replace('\n\tint playerCount','\n\t}\n\tint playerCount')
    if mode&2:b=b.replace('\tint playerCount','\t{\n\tint playerCount');b=b[:-2]+'\t}\n}\n' if mode&2 else b
    if mode&4:b=b.replace('\t\t_STL::vector<const ModuleData *> buildings;','\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;').replace('\n\t}\n\n\tint playerCount','\n\t\t}\n\t}\n\n\tint playerCount')
    add('scope-'+str(mode),b)
# Declaration order of scalar locals before their original initializations.
for n,(decl,name) in enumerate([('int','playerCount'),('int','bonus'),('int','entryCount'),('int','entry'),('int','templateID'),('int','armyRegion'),('LWAIRegionManager *','manager'),('_STL::vector<LivingWorldRegion *> *','regions'),('LivingWorldRegion *','region'),('LWAIPlayerView *','player'),('LWAIArmyView *','army'),('LWAIArmySummary *','summary'),('BuildingNuggetView *','strengthen'),('BuildingNuggetView *','spawnArmy')]):
    needle=decl+('' if decl.endswith('*') else ' ')+name+' ='
    if needle not in body:print('missing',needle);continue
    for where in ['top','phase']:
        b=body.replace(needle,name+' =')
        declaration=decl+('' if decl.endswith('*') else ' ')+name+';\n'
        if where=='top':b=b.replace('{\n','{\n\t'+declaration,1)
        elif n<6 or name in ('player','army','summary'):b=b.replace('\tint playerCount','\t'+declaration+'\tint playerCount',1) if name!='playerCount' else b.replace('\tplayerCount =','\t'+declaration+'\tplayerCount =',1)
        else:b=b.replace('\tLWAIRegionManager *manager' if name!='manager' else '\tmanager =','\t'+declaration+('\tLWAIRegionManager *manager' if name!='manager' else '\tmanager ='),1)
        add('decl-'+name+'-'+where,b)
for tag,s in candidates:
    r=run(s,'gather-'+tag,'gather')
    if r.get('exact'):break
