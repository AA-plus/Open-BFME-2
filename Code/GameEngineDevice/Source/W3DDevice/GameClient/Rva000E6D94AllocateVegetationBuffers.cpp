// cl: /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native E6D94..E6EE9 RET4 is the complete 341-byte allocator of the
// receiver already owned by rva000E6B99 and rva000EC9C6. The original
// class/method spellings remain unresolved. Donor a10e4cbab8c3fbe88a0d7dfb4acf5f8b97248a0e,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp,
// allocateTreeBuffers supplies the resource-allocation and device-lock
// semantic guide. Target bytes establish all four vector offsets, dynamic
// vertex FVF0x252/count0x7534/stride0, index count0xEA64, 32/24-byte buffer
// allocations, the counted holder at34, and the final receiver slot5 call.
// BF1 texture/shader operations are not carried into BF2: target uses
// Vegetation.fx/Default through the existing147-byte shader-setup factory.
// All vectors keep the existing by-value void-pointer resize spelling;
// counts are stored as the same four-byte words with no element identity claim.
#include <vector>
namespace _STL {
template<> class vector<void*,allocator<void*> >:public _Vector_base<void*,allocator<void*> > {
public:
 void **begin(){return _M_start;}
 unsigned size() const {return _M_finish-_M_start;}
 void *&operator[](unsigned n){return *(begin()+n);}
 void resize(unsigned,void*);
};
}
class BfmeDynamicNativeVB {public:BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);private:char bytes[0x20];};
class DX8IndexBufferClass {public:enum UsageType{USAGE_DEFAULT,USAGE_DYNAMIC};DX8IndexBufferClass(unsigned,UsageType);private:char bytes[0x18];};
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct DeviceLock{DeviceLock(){BFME_DX8_Thread_Lock();}~DeviceLock(){BFME_DX8_Thread_Assert();}};
class RefCountClass {public:virtual void Delete_This();void Add_Ref(){++refs;}void Release_Ref(){if(--refs==0)Delete_This();}private:int refs;};
class FXShaderSetup:public RefCountClass{};
template<class T>class RefCountPtr{public:RefCountPtr():m_ptr(0){}RefCountPtr(const RefCountPtr&o):m_ptr(o.m_ptr){if(m_ptr)m_ptr->Add_Ref();}~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();}T*m_ptr;};
struct Rva0007BB16Record;
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char*,const char*,const _STL::vector<Rva0007BB16Record>*,int);
class Rva00072A94{public:Rva00072A94&operator=(const Rva00072A94&);};
class Rva000EC9C6 {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void update();
 void rva000E6B99();
 void rva000E6D94(unsigned);
private:
 _STL::vector<void*>vertices,vertexCounts,indices,indexCounts;
 RefCountPtr<FXShaderSetup>method;
};
void Rva000EC9C6::rva000E6D94(unsigned count)
{
 rva000E6B99();
 int zero=0;
 vertices.resize(count,(void*)zero);vertexCounts.resize(count,(void*)zero);indices.resize(count,(void*)zero);indexCounts.resize(count,(void*)zero);
 DeviceLock lock;
 for(unsigned i=0;i<vertices.size();++i){
  vertices[i]=new BfmeDynamicNativeVB(0x252,0x7534,1,zero);
  indices[i]=new DX8IndexBufferClass(0xea64,DX8IndexBufferClass::USAGE_DYNAMIC);
  vertexCounts[i]=(void*)zero;indexCounts[i]=(void*)zero;
 }
 *(Rva00072A94*)&method=(const Rva00072A94&)Rva00152C47_CreateFXShaderSetup("Vegetation.fx","Default",(const _STL::vector<Rva0007BB16Record>*)zero,4);
 update();
}
