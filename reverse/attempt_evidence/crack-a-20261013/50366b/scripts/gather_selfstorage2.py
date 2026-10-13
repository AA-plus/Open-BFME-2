from trial import *
for n in range(8):
    b=(ROOT/'build/crack-a'/('gather-selfstorage-'+str(n))/'c1.cpp').read_text().replace('RegionOwner regionPair(','RegionOwner regionPair = RegionOwner(')
    r=run(b,'gather-selfstorage2-'+str(n),'gather')
    if r.get('exact'):break
