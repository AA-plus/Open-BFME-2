from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for n,flag in enumerate(['/EHa','/EHac','/GX','/EHsc /Ob2','/Zc:wchar_t','/Gy-','/Gy','/Zd','/Z7','/Gr','/Gd']):
 b=base.replace('// cl:','// cl: '+flag,1) if n>2 else base.replace('/EHs',flag,1)
 r=run(b,'gather-extraflag-'+str(n),'gather')
 if r.get('exact'):raise SystemExit()
