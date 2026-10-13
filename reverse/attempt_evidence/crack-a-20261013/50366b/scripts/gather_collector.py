from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
old='''class Rva003F287F
{
public:
\tvoid rva003F287F(_STL::vector<const ModuleData *> &out);
};'''
new='''struct RegionCollectEntry {char p0[0x20];const ModuleData* volatile data;char p24[0x10];unsigned char flag;};
class Rva003F287F {
public: void rva003F287F(_STL::vector<const ModuleData*>& out);
private: char pad[0x170];_STL::vector<RegionCollectEntry*> items;
};'''
body='''void Rva003F287F::rva003F287F(_STL::vector<const ModuleData*>& out){
 for(unsigned i=0;i<items.size();++i){RegionCollectEntry* e=items[i];if(e->data!=0 && e->flag==0){const ModuleData* tmp=e->data;out.push_back(tmp);}}
}\n'''
for n in range(16):
 b=base.replace(old,new);assert b!=base
 spec='namespace _STL {template<> void vector<const ModuleData*>::push_back(const ModuleData*const&);}\n'
 if n&4:spec+='namespace _STL {template<> vector<const ModuleData*>::vector(const allocator<const ModuleData*>&);}\n'
 method=['__declspec(noinline) ','','__forceinline ',''][n%4]+body
 b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
 if n%4==3:b+='\n'+method
 else:b=b.replace('class LWAIWorldInformation',method+'class LWAIWorldInformation')
 if n&8:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
 r=run(b,'gather-collector-'+str(n),'gather')
 if r.get('exact'):raise SystemExit()
