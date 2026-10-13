from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
end='m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));'
helper='''struct NamedRegionPair : _STL::pair<int,Rva00501656> {
    typedef _STL::pair<int,Rva00501656> P;
    __forceinline NamedRegionPair(const int& a,const Rva00501656& b):P(a,b){}
    __forceinline operator bool()const{return true;}
};
'''
spec='namespace _STL { template<> __forceinline pair<int,Rva00501656>::pair(const int &a,const Rva00501656 &b):first(a),second(b){} }\n'
for mode in range(8):
    b=base.replace('class LWAIWorldInformation',spec+helper+'class LWAIWorldInformation')
    if mode%4==0:b=b.replace(decl,'if (NamedRegionPair regionPair = NamedRegionPair(info.m_ownerID,info)) {').replace(end,end+'\n}')
    elif mode%4==1:b=b.replace(decl,'for (NamedRegionPair regionPair(info.m_ownerID,info);regionPair;){').replace(end,end+'\nbreak;\n}')
    elif mode%4==2:b=b.replace(decl,'switch(NamedRegionPair regionPair = NamedRegionPair(info.m_ownerID,info)){default:').replace(end,end+'\nbreak;\n}')
    else:b=b.replace(decl,'while(NamedRegionPair regionPair = NamedRegionPair(info.m_ownerID,info)){').replace(end,end+'\nbreak;\n}')
    b=b.replace('m_RegionInfo.begin(), regionPair','m_RegionInfo.begin(), static_cast<const NamedRegionPair::P&>(regionPair)')
    if mode>=4:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace(end+'\nbreak;\n}\n\t\t}',end+'\nbreak;\n}').replace(end+'\n}\n\t\t}',end+'\n}')
    r=run(b,'gather-condition-'+str(mode),'gather')
    if r.get('exact'):break
