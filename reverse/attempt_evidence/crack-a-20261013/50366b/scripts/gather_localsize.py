from trial import *
base=(ROOT/'build/crack-a/gather-wrapper-0/c1.cpp').read_text()
for n in [1,2,4,8,12,16,24,32,44,48,88,92]:
  for where in ['before','after']:
    old='_STL::pair<int,Rva00501656> value;'
    pad='char reserved['+str(n)+'];'
    b=base.replace(old,pad+' '+old if where=='before' else old+' '+pad)
    r=run(b,'gather-localsize-'+str(n)+'-'+where,'gather')
    if r.get('exact'):raise SystemExit()
