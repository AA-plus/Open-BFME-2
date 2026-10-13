from trial import *
for bank in ['gather-base','gather-scope-4']:
    base=(ROOT/'build/crack-a'/bank/'c1.cpp').read_text()
    begin=base.index('\t\tLWAIPlayerView *player')
    end=base.rindex('\n\t}\n}')
    body=base[begin:end]
    positions=[i for i in range(len(body)) if i==0 or body[i-1]=='\n']
    positions=[i for i in positions if body[i:].startswith('\t\t') and not body[i:].startswith('\t\t\t') and body[i:].split('\n')[0].strip() not in ('','{','}')]
    for n,at in enumerate(positions):
        b=base[:begin]+body[:at]+'\t\t{\n'+body[at:]+'\n\t\t}'+base[end:]
        r=run(b,bank+'-playerblock-'+str(n),'gather')
        if r.get('exact'):sys.exit()
