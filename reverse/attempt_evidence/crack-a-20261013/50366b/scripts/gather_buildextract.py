from trial import *
import itertools
for sc in ['gather-base','gather-scope-4']:
 base=(ROOT/'build/crack-a'/sc/'c1.cpp').read_text()
 a=base.index('\t\tfor (unsigned int j = 0;');z=base.index('\n\n\t\t_STL::pair<int, Rva00501656>',a)
 inner=base[a:z]
 for n,params in enumerate(itertools.permutations([('LivingWorldRegion* region','region'),('Rva00501656& info','info'),('_STL::vector<const ModuleData*>& buildings','buildings')])):
  for mode in range(2):
   helper='__forceinline void GatherBuildingRecords('+','.join(x for x,y in params)+'){\n'+inner+'\n}\n'
   call='GatherBuildingRecords('+','.join(y for x,y in params)+');'
   if mode:
    helper=helper.replace('Rva00501656& info','Rva00501656* infoPtr').replace('{\n'+inner,'{\nRva00501656& info=*infoPtr;\n'+inner)
    call=call.replace('info','&info')
   b=base[:a]+call+base[z:]
   b=b.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation')
   r=run(b,'gather-buildextract-'+sc+'-'+str(n)+'-'+str(mode),'gather')
   if r.get('exact'):raise SystemExit()
