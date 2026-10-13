from trial import *
base=(ROOT/'build/crack-a/gather-base/c1.cpp').read_text()
begin=base.index('\t\tLivingWorldRegion *region')
end=base.index('\n\t}\n\n\tint playerCount',begin)
body=base[begin:end]
positions=[i for i in range(len(body)) if i==0 or body[i-1]=='\n']
positions=[i for i in positions if body[i:].startswith('\t\t') and not body[i:].startswith('\t\t\t') and body[i:].split('\n')[0].strip() not in ('','{','}')]
for n,at in enumerate(positions):
    b=base[:begin]+body[:at]+'\t\t{\n'+body[at:]+'\n\t\t}'+base[end:]
    r=run(b,'gather-block-'+str(n),'gather')
    if r.get('exact'):sys.exit()
b=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
for a in [1,2,4,8,16]:
    s=b.replace('_STL::pair<int, Rva00501656> regionPair','__declspec(align('+str(a)+')) _STL::pair<int, Rva00501656> regionPair')
    r=run(s,'gather-pair-align'+str(a),'gather')
    if r.get('exact'):sys.exit()
