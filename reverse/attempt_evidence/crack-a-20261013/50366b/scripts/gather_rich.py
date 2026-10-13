from trial import *
import struct
p=build.EXE; data=p.read_bytes();r=data.find(b'Rich',0,1024)
print('retail',str(p),'RichOffset',r)
if r>=0:
 key=struct.unpack_from('<I',data,r+4)[0]; start=None
 for a in range(r-4,0,-4):
  if struct.unpack_from('<I',data,a)[0]^key==0x536e6144:start=a;break
 print('start',start,'key',hex(key))
 if start is not None:
  for a in range(start+16,r,8):
   x,n=struct.unpack_from('<II',data,a);x^=key;n^=key;print('product',hex(x>>16),'build',x&65535,'count',n)
