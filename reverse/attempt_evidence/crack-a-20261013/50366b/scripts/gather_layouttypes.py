from trial import *
base=(ROOT/'build/crack-a/gather-forcector-2/c1.cpp').read_text()
for mode in range(12):
    b=base
    if mode&1:b=b.replace('struct RegionPairLocal','union RegionPairLocal')
    if mode&2:b=b.replace('__declspec(align(4)) char storage[sizeof(P)]','char storage[sizeof(P)]')
    if mode&4:b=b.replace('char storage[sizeof(P)]','unsigned int storage[sizeof(P)/4]')
    if mode>=8:
        b=b.replace('struct RegionPairLocal','#pragma pack(push, 1)\nstruct RegionPairLocal').replace('union RegionPairLocal','#pragma pack(push, 1)\nunion RegionPairLocal').replace('class LWAIWorldInformation','#pragma pack(pop)\nclass LWAIWorldInformation')
    r=run(b,'gather-layouttype-'+str(mode),'gather')
    if r.get('exact'):break
