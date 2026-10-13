from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
choices=[('int ownerID = info.m_ownerID;','ownerID','info'),('const int ownerID = info.m_ownerID;','ownerID','info'),('const int &ownerID = info.m_ownerID;','ownerID','info'),('int &ownerID = info.m_ownerID;','ownerID','info'),('const Rva00501656 &sourceInfo = info;','info.m_ownerID','sourceInfo'),('Rva00501656 &sourceInfo = info;','info.m_ownerID','sourceInfo'),('const Rva00501656 *sourceInfo = &info;','info.m_ownerID','*sourceInfo'),('int ownerID=info.m_ownerID;const Rva00501656 &sourceInfo=info;','ownerID','sourceInfo')]
for mode,(intro,a,b) in enumerate(choices):
    for where in ['near','block']:
        s=base.replace(decl,'_STL::pair<int, Rva00501656> regionPair('+a+', '+b+');')
        if where=='near':s=s.replace('_STL::pair<int, Rva00501656> regionPair(',intro+'\n\t\t_STL::pair<int, Rva00501656> regionPair(')
        else:s=s.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t{\n\t\t'+intro+'\n\t\t_STL::vector<const ModuleData *> buildings;')
        r=run(s,'gather-aliaslocal-'+str(mode)+'-'+where,'gather')
        if r.get('exact'):sys.exit()
# Bind an lvalue reference to the first pair before the implicit conversion.
for mode,ty in enumerate(['const _STL::pair<int,Rva00501656> &','_STL::pair<int,Rva00501656> &','const _STL::pair<int,Rva00501656> *']):
    s=base.replace(decl,decl+'\n'+ty+' firstPair = '+('&regionPair' if '*' in ty else 'regionPair')+';').replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), '+('*firstPair' if '*' in ty else 'firstPair'))
    r=run(s,'gather-pairref-'+str(mode),'gather')
    if r.get('exact'):sys.exit()
