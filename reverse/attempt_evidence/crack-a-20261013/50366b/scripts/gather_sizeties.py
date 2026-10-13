from trial import *
base=(ROOT/'build/crack-a/gather-wrapper-0/c1.cpp').read_text()
for n,pad in enumerate(['char reserved[0];','char reserved:0;','int reserved:0;','unsigned int :0;','char :0;','struct Empty{};','typedef char Reserved[1];']):
    b=base.replace('_STL::pair<int,Rva00501656> value;','_STL::pair<int,Rva00501656> value; '+pad)
    r=run(b,'gather-sizetie-'+str(n),'gather')
    if r.get('exact'):raise SystemExit()
for n in [0,1,4,5,8,9]:
    b=(ROOT/'build/crack-a'/('gather-convertwrapper-'+str(n))/'c1.cpp').read_text()
    b=b.replace('struct RegionConversion {','#pragma pack(push, 1)\nstruct RegionConversion {').replace('struct RegionConversion :','#pragma pack(push, 1)\nstruct RegionConversion :').replace('class LWAIWorldInformation','#pragma pack(pop)\nclass LWAIWorldInformation')
    r=run(b,'gather-convertpack-'+str(n),'gather')
    if r.get('exact'):raise SystemExit()
