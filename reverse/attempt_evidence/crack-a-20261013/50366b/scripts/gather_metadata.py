from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
variants=[]
for flag in ['/Z7','/Zi','/Zd','/GF','/Gy-','/Ob2','/Oi','/GA','/EHs-','/Zp1','/Zp2']:
    variants.append(('flag'+flag[1:].replace('-','minus'),base.replace('// cl:','// cl: '+flag,1)))
for name in ['Rva00501656','Rva00501776','Rva00501E3FElement']:
    for method in ['copy','destructor','both']:
        b=base
        if method in ['copy','both']:
            b=b.replace(name+'(const '+name+' &that);',name+'(const '+name+' &that) throw();')
        if method in ['destructor','both']:
            b=b.replace('~'+name+'();','~'+name+'() throw();')
        variants.append((name+'-'+method,b))
for tag,b in variants:
    r=run(b,'gather-metadata-'+tag,'gather')
    if r.get('exact'):break
