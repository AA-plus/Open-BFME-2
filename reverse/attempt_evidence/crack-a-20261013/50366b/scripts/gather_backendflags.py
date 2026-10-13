from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
flags=['/GS','/GS-','/Og-','/Oy-','/Op','/Gf','/J','/vd0','/Zl','/O2 /Os','/Ox /Os','/O1 /Ot','/O1 /Og-','/O1 /Ow-','/O1 /Oa-','/O1 /Oi-','/O1 /Ob2 /Oy-','/O1 /GL','/G7 /arch:SSE2']
for n,f in enumerate(flags):
    b=base.replace('// cl: /O1 /G7 /arch:SSE','// cl: /O1 /G7 /arch:SSE '+f)
    r=run(b,'gather-backend-'+str(n),'gather')
    if r.get('exact'):break
