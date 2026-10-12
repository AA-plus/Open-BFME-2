// ?rva001818C0@BfmeFVFDescriptor@@QAEPAXXZ
// partial score=0.945369359573774 date=2026-10-12
// cl: /O2 /G7 /EHs /Ob2 /arch:SSE /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Op
// stlport
#include <vector>
struct FxVertexElement {unsigned short stream,offset;unsigned char type,method,usage,index;};

namespace _STL {
typedef vector<FxVertexElement> FxVertexElements;
template<> __forceinline void FxVertexElements::push_back(const FxVertexElement &value) {
 if(this->_M_finish!=this->_M_end_of_storage._M_data){_Construct(this->_M_finish,value);++this->_M_finish;}
 else _M_insert_overflow(this->_M_finish,value,_IsPODType(),1UL,true);
}
}
struct IDirect3DDevice8;
class BfmeFVFDescriptor;
class DX8Wrapper {friend class BfmeFVFDescriptor;protected:static IDirect3DDevice8 *D3DDevice;};
struct FxDeclarationDevice {
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
 V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7)
 V(80) V(81) V(82) V(83) V(84) V(85)
#undef V10
#undef V
 virtual long __stdcall CreateVertexDeclaration(const FxVertexElement *,void **);
};
class BfmeFVFDescriptor {
public:
 void *rva001818C0();
 unsigned fvf;bool basis;unsigned count;char rest[0x60-0xc];
};
void *BfmeFVFDescriptor::rva001818C0()
{
 _STL::vector<FxVertexElement> elements;
 FxVertexElement e;
 unsigned format=fvf;
 elements.reserve(16);
 e.stream=0;e.offset=0;e.type=0;e.method=0;e.usage=0;e.index=0;
 if(format&2) {e.type=2;e.usage=0;elements.push_back(e);e.offset=12;}
 format=fvf;if(format&4) {e.type=3;e.usage=9;elements.push_back(e);e.offset+=16;}
 format=fvf;if((format&0x4002)==0x4002) {e.type=3;e.usage=0;elements.push_back(e);e.offset+=16;}
 if(elements.empty())return 0;
 if(fvf&0x10) {e.type=2;e.usage=3;elements.push_back(e);e.offset+=12;}
 if(fvf&0x20) {e.type=0;e.usage=4;elements.push_back(e);e.offset+=4;}
 if(fvf&0x40) {e.type=4;e.usage=10;elements.push_back(e);e.offset+=4;}
 if(fvf&0x80) {e.type=4;e.usage=10;e.index=1;elements.push_back(e);e.offset+=4;}
 e.usage=5;e.index=0;
 int textures=(fvf>>8)&15;
 while(e.index<textures) {
  int dimension=0;
  unsigned code=(fvf>>(16+e.index*2))&3;
  if(code==3)dimension=1;
  else if(0 == code)dimension=2;
  else if(code==1)dimension=3;
  else if(code==2)dimension=4;
  e.type=dimension-1;
  elements.push_back(e);
  ++e.index;e.offset+=dimension*4;
 }
 e.index=0;
 if(basis) {
  e.type=2;e.usage=6;elements.push_back(e);e.offset+=12;
  e.type=2;e.usage=7;elements.push_back(e);e.offset+=12;
 }
 if(count>0) {
  e.type=4;e.usage=2;elements.push_back(e);e.offset+=4;
  if(count>1) {
   e.type=count-1;e.usage=1;elements.push_back(e);e.offset+=count*4;
   e.type=2;e.usage=0;e.index=1;elements.push_back(e);e.offset+=12;
   e.type=2;e.usage=3;e.index=1;elements.push_back(e);
  }
 }
 e.stream=0xff;e.offset=0;e.type=17;e.method=0;e.usage=0;e.index=0;
 elements.push_back(e);
 void *result=0;
 if(((FxDeclarationDevice*)DX8Wrapper::D3DDevice)->CreateVertexDeclaration(&elements[0],&result)<0)return 0;
 return result;
}
