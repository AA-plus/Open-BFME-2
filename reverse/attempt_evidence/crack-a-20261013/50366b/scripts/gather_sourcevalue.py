from trial import *
for mode in range(16):
 b=(ROOT/'build/crack-a'/('gather-calltemporary-'+str(mode%8))/'c1.cpp').read_text()
 b=b.replace('const _STL::pair<int,Rva00501656> &regionPair','_STL::pair<int,Rva00501656> regionPair')
 if mode>=8:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('info));\n\t\t}','info));').replace('info);\n\t\t}','info);')
 r=run(b,'gather-sourcevalue-'+str(mode),'gather')
 if r.get('exact'):raise SystemExit()
