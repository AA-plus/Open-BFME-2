// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/moduledata
// stlport
// HordeMeleeAmoeba slot 3, native 00588ABB..00588B8A (207B, RET4).
// WB 01470F20 paired by the ctor's vtable; the class name is independently
// owned by 00587D9C. BFME1 Xfer/version conventions guide the transfer;
// the 60B record, version bytes, field offsets and chained calls are target facts.
#include <vector>
#include "Coord3DBase.h"
#include "Common/Snapshot.h"
struct BfmePod60 {
 BfmePod60();
 Coord3DBase position;
 bool needsPosition;char opaque0d[3];int index;
 int values[8];int opaque34;unsigned char opaque38;bool loaded39;char opaque3a[2];
};
namespace _STL {template<> void vector<BfmePod60>::resize(size_type);}
struct HmaTransferVersion {unsigned char minimum,current; HmaTransferVersion(unsigned char c,unsigned char m):minimum(m),current(c) {}};
class HmaTransferView {
public:
 virtual void s0();
 virtual bool isLoading();
 virtual void s2();
 virtual bool isCRC();
 virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();
 virtual HmaTransferView &version(HmaTransferVersion &);
 virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();
 virtual HmaTransferView &position(Coord3DBase &);
 virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();
 virtual HmaTransferView &count(unsigned &);
 virtual HmaTransferView &integer(int &);virtual void s32();virtual void s33();virtual void s34();virtual void s35();
 virtual HmaTransferView &boolean(bool &);
};
class Rva0058731DHost;
Rva0058731DHost *Rva0058731DCheck(Rva0058731DHost*,int);
class Rva005D6FCC : public Snapshot {public:virtual ~Rva005D6FCC();void *held;};
class HordeMeleeAmoeba : public Rva005D6FCC {
public:
 virtual void xfer(Xfer *);
 _STL::vector<BfmePod60> slots;
 bool flag14;void *other;
};
void HordeMeleeAmoeba::xfer(Xfer *xfer)
{
 HmaTransferView *view=(HmaTransferView*)xfer;
 if(view->isCRC())return;
 HmaTransferVersion version(3,1);
 view->version(version);
 if(version.current<2)return;
 view->boolean(flag14);
 unsigned count=slots.size();
 view->count(count);
 slots.resize(count);
 for(BfmePod60 *p=slots.begin();p!=slots.end();++p) {
  HmaTransferView &a=view->position(p->position);
  HmaTransferView &b=((HmaTransferView*)&a)->boolean(p->needsPosition);
  Rva0058731DCheck((Rva0058731DHost*)&((HmaTransferView*)&b)->integer(p->index),(int)p->values);
  if(version.current>2)view->boolean(p->loaded39);
  else if(view->isLoading())p->loaded39=true;
 }
}
