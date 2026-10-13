from trial import *
best=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
orig=best.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
for mode in range(12):
    helper='''struct BuildingList {
    typedef _STL::vector<const ModuleData*> V;
    V data;
    CTOR
    DTOR
    __forceinline operator V&(){return data;}
    __forceinline unsigned int size()const{return data.size();}
};
'''.replace('CTOR','__forceinline BuildingList(){}' if mode&1 else '').replace('DTOR','__forceinline ~BuildingList(){}' if mode&2 else '')
    if mode>=4 and mode<8:
        helper=helper.replace('struct BuildingList {','struct BuildingList : _STL::vector<const ModuleData*> {').replace('V data;','').replace('return data;','return *this;').replace('return data.size();','return V::size();')
    if mode>=8:
        helper=helper.replace('V data;','V data[1];').replace('return data;','return data[0];').replace('return data.size();','return data[0].size();')
    for scope,base in [('orig',orig),('best',best)]:
        b=base.replace('class LWAIWorldInformation',helper+'class LWAIWorldInformation').replace('_STL::vector<const ModuleData *> buildings;','BuildingList buildings;')
        r=run(b,'gather-vectorwrapper-'+scope+'-'+str(mode),'gather')
        if r.get('exact'):raise SystemExit()
