from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for region in range(4):
    for player in range(4):
      b=base
      # Construct ranges against the original text and apply innermost-first by descending positions.
      spans=[]
      pstart=b.index('\tint playerCount =')
      if region:
        rstart=b.index(['','\tLWAIRegionManager *manager','\t_STL::vector<LivingWorldRegion *> *regions','\tfor (unsigned int i'][region])
        spans.append((rstart,pstart))
      if player:
        ps=b.index('\tfor (int p =') if player==2 else pstart
        spans.append((ps,b.rfind('\n}')))
        if player==3:spans.append((ps,b.rfind('\n}')))
      edits=[]
      for a,z in spans:edits.extend([(a,'{\n'),(z,'\n}\n')])
      for at,text in sorted(edits,reverse=True):b=b[:at]+text+b[at:]
      r=run(b,'gather-outerscope-'+scope+'-'+str(region)+'-'+str(player),'gather')
      if r.get('exact'):raise SystemExit()
