from trial import *
from eh_verify import Obj
import struct
obj=Obj(ROOT/'build/crack-a/gather-metadata-flagZ7/c1.obj')
for s in obj.sections:
    if s['name']!='.debug$S':continue
    d=s['data']
    print('section',s['index'],'size',len(d),'head',d[:32].hex())
    # Older CodeView symbol records are length-prefixed. Inspect local names
    # and their neighboring records without assuming modern C13 headers.
    for word in [b'regionPair',b'buildings',b'info\0',b'playerPair']:
      at=d.find(word)
      if at>=0: print(word.decode(errors='replace'),hex(at),d[max(0,at-32):at+len(word)+16].hex())
