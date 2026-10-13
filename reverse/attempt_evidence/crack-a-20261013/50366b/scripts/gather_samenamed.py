from trial import *
for n in range(12):
 folder=('gather-resultplacement-'+str([1,3,5,7][n%4])) if n<8 else ('gather-valueinsert-'+str([4,5,12,13][n%4]))
 b=(ROOT/'build/crack-a'/folder/'c1.cpp').read_text()
 b=b.replace('_STL::pair<int, Rva00501656> regionPair','_STL::pair<const int, Rva00501656> regionPair').replace('_STL::pair<int,Rva00501656>& pair','_STL::pair<const int,Rva00501656>& pair')
 if n>=4 and n<8:
  spec='namespace _STL { template<> pair<const int,Rva00501656>::pair(const pair<const int,Rva00501656>&); }\n'
  b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
 r=run(b,'gather-samenamed-'+str(n),'gather')
 if r.get('exact'):raise SystemExit()
