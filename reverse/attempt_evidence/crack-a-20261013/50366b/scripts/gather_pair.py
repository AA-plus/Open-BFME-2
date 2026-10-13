from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
variants=[
('const','const '+decl),
('make','_STL::pair<int, Rva00501656> regionPair = _STL::make_pair(info.m_ownerID, info);'),
('ref','const _STL::pair<int, Rva00501656>& regionPair = _STL::make_pair(info.m_ownerID, info);'),
('copy','_STL::pair<int, Rva00501656> regionPair = _STL::pair<int, Rva00501656>(info.m_ownerID, info);'),
('refexplicit','const _STL::pair<int, Rva00501656>& regionPair = _STL::pair<int, Rva00501656>(info.m_ownerID, info);')]
for mode,repl in variants:
    r=run(base.replace(decl,repl),'gather-pair-'+mode,'gather')
    if r.get('exact'):sys.exit()
for n in range(1,5):
    b=base.replace(decl,'{\n'*n+decl)
    needle='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
    b=b.replace(needle,needle+'\n'+'}\n'*n)
    r=run(b,'gather-pair-scope'+str(n),'gather')
    if r.get('exact'):sys.exit()
