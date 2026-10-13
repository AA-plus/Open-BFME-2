from trial import *
for n in range(12):
    b=(ROOT/'build/crack-a'/('gather-pairdefinition-'+str(n%4))/'c1.cpp').read_text()
    ty='_STL::pair<int,Rva00501656>'
    helper='__forceinline '+ty+' MakeRegionPair(const int &a,const Rva00501656 &b) {'+('return '+ty+'(a,b);' if n<4 else ty+' result(a,b);return result;')+'}\n'
    b=b.replace('void LWAIWorldInformation::GatherWorldInformation()',helper+'void LWAIWorldInformation::GatherWorldInformation()').replace('_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);','_STL::pair<int, Rva00501656> regionPair = MakeRegionPair(info.m_ownerID, info);')
    if n>=8:b=b.replace('int, Rva00501656> regionPair =','int, Rva00501656> const &regionPair =')
    r=run(b,'gather-pairmake-'+str(n),'gather')
    if r.get('exact'):break
