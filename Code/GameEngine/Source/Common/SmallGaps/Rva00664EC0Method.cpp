// ?rva00664EC0@Rva00664EC0@@QAEXH@Z
// partial score=1.0 date=2026-10-13
// cl: /O2 /G5 /DNDEBUG /MD /EHsc
struct Rva00804150ProtoMangleRef;
void Rva008054A0(Rva00804150ProtoMangleRef *);
int Rva00806040(Rva00804150ProtoMangleRef *,unsigned *,int *);
int Rva008060B0(Rva00804150ProtoMangleRef *,int,int);
int Rva00656B60Get();
struct MangleClockView {virtual void v0();virtual void v1();virtual int getTime();};
class BfmeE1036 {public:void bfmeGo1036E();};
typedef void (__cdecl *MangleCallback)(void *,void *);
class Rva00664EC0 {
public:
 void rva00664EC0(int unused);
 void *unknown00;Rva00804150ProtoMangleRef *ref04;int state08;
 unsigned callback0c[2];unsigned address14;int port18,time1c;unsigned char report20;
 MangleCallback callback24;void *context28;
};
void Rva00664EC0::rva00664EC0(int unused)
{
 if(ref04 && callback24) {
  Rva008054A0(ref04);
  int port=0;unsigned address=0;
  int status=Rva00806040(ref04,&address,&port);
  address14=address;port18=port;
  switch(state08) {
   case 1:
    if(status>0) {
     callback24(callback0c,context28);
     if(report20) {
      int elapsed=((MangleClockView *)Rva00656B60Get())->getTime()-time1c;
      Rva008060B0(ref04,0,elapsed);state08=2;
     } else state08=3;
    } else if(status<0) {
     callback24(callback0c,context28);
     if(report20) {
      int elapsed=((MangleClockView *)Rva00656B60Get())->getTime()-time1c;
      Rva008060B0(ref04,1,elapsed);state08=2;
     } else state08=3;
    }
    break;
   case 2:if(status!=0)state08=3;break;
   case 3:((BfmeE1036 *)((char *)this-4))->bfmeGo1036E();state08=0;break;
  }
 }
}
