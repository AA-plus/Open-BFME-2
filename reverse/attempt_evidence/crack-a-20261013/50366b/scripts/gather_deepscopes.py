from trial import *
for sc in ['gather-base','gather-scope-4']:
 base=(ROOT/'build/crack-a'/sc/'c1.cpp').read_text()
 sections=[('army','\t\t\tLWAIArmyView *army','\n\t\t}\n\t\t_STL::pair<int, Rva00501776>',3),('entry','\t\t\t\tint entry =','\n\t\t\t}\n\t\t\tint armyRegion',4),('building','\t\t\tLivingWorldBuilding *building','\n\t\t}\n\n\t\t_STL::pair<int, Rva00501656>',3)]
 for name,st,en,indent in sections:
  a=base.index(st);z=base.index(en,a);chunk=base[a:z]
  positions=[i for i in range(len(chunk)) if i==0 or chunk[i-1]=='\n']
  positions=[i for i in positions if chunk[i:].startswith('\t'*indent) and not chunk[i:].startswith('\t'*(indent+1)) and chunk[i:].split('\n')[0].strip() not in ('','{','}')]
  for n,pos in enumerate(positions):
   b=base[:a]+chunk[:pos]+'\t'*indent+'{\n'+chunk[pos:]+'\n'+'\t'*indent+'}'+base[z:]
   r=run(b,'gather-deepscope-'+sc+'-'+name+'-'+str(n),'gather')
   if r.get('exact'):raise SystemExit()
