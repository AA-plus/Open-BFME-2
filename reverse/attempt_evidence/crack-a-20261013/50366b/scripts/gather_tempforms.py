from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
decl='_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);'
for mode in range(12):
    b=base
    ty='_STL::pair<int,Rva00501656>'
    val=ty+'(info.m_ownerID,info)'
    expr=[val,'(0,'+val+')','(info.m_ownerID,'+val+')','(true?'+val+':'+val+')'][mode%4]
    b=b.replace(decl,('const '+ty+'&' if mode<8 else ty)+' regionPair = '+expr+';')
    if mode>=4 and mode<8:b=b.replace('const '+ty+'& regionPair','const '+ty+' regionPair')
    if mode>=8:b='#pragma inline_depth(255)\n'+b
    r=run(b,'gather-tempform-'+str(mode),'gather')
    if r.get('exact'):break
for mode in range(3):
    b=(ROOT/'build/crack-a/gather-makeinline-'+str(mode)+'/c1.cpp').read_text()
    b='#pragma inline_depth(255)\n#pragma inline_recursion(on)\n'+b
    r=run(b,'gather-inlinedepth-'+str(mode),'gather')
    if r.get('exact'):break
