from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for mode in range(12):
 if mode<6:
  s='template<> template<> '+('__declspec(noinline) ' if mode%3==1 else '')+'pair<const int,Rva00501656>::pair(const pair<int,Rva00501656>& x)'
  s+=':first(x.first),second(x.second){}' if mode%3 else ';'
 else:
  s='''template<> struct pair<const int,Rva00501656> {
  const int first; Rva00501656 second;
  template<class A,class B> pair(const pair<A,B>& x) BODY
  };'''.replace('BODY',':first(x.first),second(x.second){}' if mode%3 else ';')
  if mode%3==1:s=s.replace('template<class A,class B> pair','template<class A,class B> __declspec(noinline) pair')
 s='namespace _STL {'+s+'}\n'
 b=base.replace('typedef _STL::multimap<int, Rva00501656> RegionInfoMap;',s+'typedef _STL::multimap<int, Rva00501656> RegionInfoMap;')
 if mode in (3,4,5,9,10,11):b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
 r=run(b,'gather-convertspec-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
