from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for scope,base in [('best',best),('orig',orig)]:
  for rmode in range(4):
    for pmode in range(4):
      if not rmode and not pmode:continue
      b=base
      if rmode:
        old='for (unsigned int i = 0; i < regions->size(); ++i)\n\t{'
        first='unsigned int i = 0;\n\t'+('while (i < regions->size())' if rmode==1 else 'if (regions->size() != 0) do')+'\n\t{\n\t{'
        last='\n\t}\n\t++i;\n\t}'+(' while (i < regions->size());' if rmode!=1 else '')+'\n\n\tint playerCount'
        b=b.replace(old,first).replace('\n\t}\n\n\tint playerCount',last)
        if rmode==3:b=b.replace('if (regions->size() != 0) do','if (i < regions->size()) do')
      if pmode:
        old='for (int p = 0; p < playerCount; ++p)\n\t{'
        first='int p = 0;\n\t'+('while (p < playerCount)' if pmode==1 else 'if (playerCount > 0) do')+'\n\t{\n\t{'
        b=b.replace(old,first)
        at=b.rfind('\n\t}\n}')
        b=b[:at]+'\n\t}\n\t++p;\n\t}'+(' while (p < playerCount);' if pmode!=1 else '')+'\n}'+b[at+len('\n\t}\n}'):]
        if pmode==3:b=b.replace('if (playerCount > 0) do','if (p < playerCount) do')
      r=run(b,'gather-doloop-'+scope+'-'+str(rmode)+'-'+str(pmode),'gather')
      if r.get('exact'):raise SystemExit()
