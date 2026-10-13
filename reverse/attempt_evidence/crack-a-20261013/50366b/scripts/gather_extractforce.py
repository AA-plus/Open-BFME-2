from trial import *
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for n in range(10):
    b=(ROOT/'build/crack-a'/('gather-scopeextract-'+str(n))/'c1.cpp').read_text()
    b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
    r=run(b,'gather-extractforce-'+str(n),'gather')
    if r.get('exact'):break
