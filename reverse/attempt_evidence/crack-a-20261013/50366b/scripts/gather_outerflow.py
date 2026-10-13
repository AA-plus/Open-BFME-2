from trial import *
for sc in ['gather-base','gather-scope-4']:
 base=(ROOT/'build/crack-a'/sc/'c1.cpp').read_text()
 a=base.index('\tfor (unsigned int i = 0;');q=base.index('\n\t{',a)+len('\n\t{');z=base.index('\n\t}\n\n\tint playerCount',q)
 inner=base[q:z]
 for mode in range(12):
  body=inner
  if mode&1:body='\n{'+body+'\n}'
  form=mode//2
  if form==0:code='unsigned int i=0; for(;;++i){if(i>=regions->size())break;'+body+'\n}'
  elif form==1:code='unsigned int i=0; while(true){if(i>=regions->size())break;{'+body+'\n}++i;}'
  elif form==2:code='unsigned int i=0; regionTest: if(i>=regions->size())goto regionsDone;{'+body+'\n}++i;goto regionTest;regionsDone:;'
  elif form==3:code='unsigned int i=0; do{if(i>=regions->size())break;{'+body+'\n}++i;}while(true);'
  elif form==4:code='unsigned int i=0; for(;i<regions->size();++i){'+body+'\ngoto regionContinue;regionContinue:;} '
  else:code='unsigned int i=0; for(;i<regions->size();++i){{'+body+'\ngoto regionContinue;}regionContinue:;} '
  b=base[:a]+code+base[z+len('\n\t}'):]
  r=run(b,'gather-outerflow-'+sc+'-'+str(mode),'gather')
  if r.get('exact'):raise SystemExit()
