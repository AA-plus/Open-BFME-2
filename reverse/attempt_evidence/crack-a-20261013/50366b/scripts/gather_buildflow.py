from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
head='for (unsigned int j = 0; j < buildings.size(); ++j)\n\t\t{'
tail='\n\t\t}\n\n\t\t_STL::pair<int, Rva00501656> regionPair'
for mode in range(8):
    b=base
    if mode<4:
        b=b.replace(head,'unsigned int j = 0;\n\t\tif (j >= buildings.size()) goto regionInsertion;\n\t\tdo {')
        b=b.replace(tail,'\n\t\t} while (++j < buildings.size());\nregionInsertion:;\n\t\t_STL::pair<int, Rva00501656> regionPair')
    else:
        b=b.replace(head,'unsigned int j = 0;\nregionBuildingTest:\n\t\tif (j >= buildings.size()) goto regionInsertion;\n\t\t{')
        b=b.replace(tail,'\n\t\t}\n\t\t++j; goto regionBuildingTest;\nregionInsertion:;\n\t\t_STL::pair<int, Rva00501656> regionPair')
    if mode&1:b=b.replace('if (j >= buildings.size())','if (buildings.size() == 0)' if mode<4 else 'if (!(j < buildings.size()))')
    if mode&2:b=b.replace('\t\t{\n\t\t_STL::vector<const ModuleData *> buildings;','\t\t_STL::vector<const ModuleData *> buildings;').replace('(int)&it->second));\n\t\t}','(int)&it->second));')
    r=run(b,'gather-buildflow-'+str(mode),'gather')
    if r.get('exact'):raise SystemExit()
