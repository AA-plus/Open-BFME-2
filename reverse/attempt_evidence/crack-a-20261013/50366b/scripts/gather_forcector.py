from trial import *
for mode in range(8):
    folder=['gather-makeinline-0','gather-makeinline-1','gather-storage-4','gather-storage-6','gather-pair-make','gather-pairtypes-4','gather-scope-4','gather-wrapper-0'][mode]
    if folder=='gather-pairtypes-4':folder='gather-pairtype-4'
    b=(ROOT/'build/crack-a'/folder/'c1.cpp').read_text()
    spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
    # Place before any helper that instantiates the pair.
    marker='class LWAIWorldInformation'
    b=b.replace(marker,spec+marker,1)
    r=run(b,'gather-forcector-'+str(mode),'gather')
    if r.get('exact'):break
