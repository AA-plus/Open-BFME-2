from trial import *
# Diagnostic only. These exception annotations are not established target facts
# and must not be promoted into production merely to obtain different codegen.
for n in range(8):
    b=(ROOT/'build/crack-a'/('gather-makeinline-'+str(n%2))/'c1.cpp').read_text()
    if n<2:b=b.replace('MakeRegionPair(const int &a,const Rva00501656 &b) {','MakeRegionPair(const int &a,const Rva00501656 &b) throw() {')
    elif n<4:b=b.replace('__forceinline _STL::pair<int,Rva00501656> MakeRegionPair','__declspec(nothrow) __forceinline _STL::pair<int,Rva00501656> MakeRegionPair')
    elif n<6:b=b.replace('MakeRegionPair(const int &a,const Rva00501656 &b) {','MakeRegionPair(const int &a,const Rva00501656 &b) throw(int) {')
    else:b=b.replace('__forceinline _STL::pair<int,Rva00501656> MakeRegionPair','__declspec(noalias) __forceinline _STL::pair<int,Rva00501656> MakeRegionPair')
    r=run(b,'gather-factoryeh-diagnostic-'+str(n),'gather')
    if r.get('exact'):print('DIAGNOSTIC ONLY: exception annotations need independent evidence.',flush=True)
