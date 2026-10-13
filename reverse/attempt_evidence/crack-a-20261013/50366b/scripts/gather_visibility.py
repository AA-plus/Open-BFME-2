from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
defs=[
'__declspec(noinline) Rva00501656::Rva00501656(const Rva00501656& o):m_regionID(o.m_regionID),m_ownerID(o.m_ownerID),m_08(o.m_08),m_0c(o.m_0c),m_10(o.m_10),m_1c(o.m_1c),m_28(o.m_28),m_34(o.m_34),m_40(o.m_40),m_armies(o.m_armies){}',
'__declspec(noinline) Rva00501656::Rva00501656(){}',
'__declspec(noinline) Rva00501656::~Rva00501656(){}',
'__declspec(noinline) Rva00501776::Rva00501776(const Rva00501776& o):m_00(o.m_00),m_04(o.m_04),m_08(o.m_08),m_regionCount(o.m_regionCount),m_10(o.m_10),m_heroArmies(o.m_heroArmies),m_garrisonArmies(o.m_garrisonArmies){}',
'__declspec(noinline) Rva00501776::~Rva00501776(){}',
]
for n in range(len(defs)+2):
    defs2='\n'.join(defs[:3] if n==5 else defs if n==6 else [defs[n]])+'\n'
    for mode in range(2):
        if mode:defs2=defs2.replace('__declspec(noinline)','')
        b=base.replace('void LWAIWorldInformation::GatherWorldInformation()',defs2+'void LWAIWorldInformation::GatherWorldInformation()')
        r=run(b,'gather-visibility-'+str(n)+'-'+str(mode),'gather')
        if r.get('exact'):raise SystemExit()
for n,flags in enumerate(['/D_STLP_NO_EXCEPTIONS','/D_STLP_USE_MALLOC','/D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC','/D_STLP_NO_ANACHRONISMS','/D_STLP_NO_EXTENSIONS','/D_BFME_RETAIL_TREE_INSERT_LAYOUT']):
    r=run(base.replace('// cl:','// cl: '+flags,1),'gather-stlflags-'+str(n),'gather')
    if r.get('exact'):raise SystemExit()
