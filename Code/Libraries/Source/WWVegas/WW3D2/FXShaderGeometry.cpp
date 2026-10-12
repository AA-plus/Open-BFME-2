// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native18C131..18C262 RET16. Original helper name unknown. FXShaderGeometry::Init supplies this + four
// stack arguments: effect, technique handle, FVF output and basis flag.
// D3DXGetShaderInputSemantics is the owned stdcall12 PE thunk 62AFC2.
// Descriptor extents/fields and usage branches come from target accesses.
// These are narrow effect API views; no complete effect object layout is claimed.
// The 64-record stack array and reference binding preserve native SIB loads.
// Texture-count min/max use reference semantics to retain native address selection.
struct FxTechniqueDesc {const char *name;unsigned passes,annotations;};
struct FxPassDesc {const char *name;unsigned annotations;const unsigned long *vertexShader,*pixelShader;};
struct FxShaderSemantic {unsigned usage,index;};
extern "C" long __stdcall D3DXGetShaderInputSemantics(const unsigned long *,FxShaderSemantic *,unsigned *);
class FxEffectView {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual long __stdcall GetTechniqueDesc(void *,FxTechniqueDesc *);
 virtual long __stdcall GetPassDesc(void *,FxPassDesc *);
 virtual void slot07();virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();
 virtual void *__stdcall GetPass(void *,unsigned);
};
class FXShaderGeometry {public:void rva0018C131(FxEffectView *,void *,unsigned *,bool *);};
void FXShaderGeometry::rva0018C131(FxEffectView *effect,void *technique,unsigned *fvf,bool *basis)
{
 *fvf=0;*basis=false;
 int textureCount=0;
 if(effect) {
  FxTechniqueDesc td;
  if(effect->GetTechniqueDesc(technique,&td)>=0) {
   for(unsigned passIndex=0;passIndex<td.passes;++passIndex) {
    void *pass=effect->GetPass(technique,passIndex);
    unsigned count=0;
    if(pass) {
     FxPassDesc pd;
     if(effect->GetPassDesc(pass,&pd)>=0) {
      FxShaderSemantic semantics[64];
      if(D3DXGetShaderInputSemantics(pd.vertexShader,semantics,&count)>=0) {
       for(unsigned i=0;i<count;++i) {
        const FxShaderSemantic &semantic=semantics[i];
        if(semantic.usage==0) *fvf|=2;
        else if(semantic.usage==10 && semantic.index==0) *fvf|=0x40;
        else if(semantic.usage==10 && semantic.index==1) *fvf|=0x80;
        else if(semantic.usage==3) *fvf|=0x10;
        else if(semantic.usage==6 || semantic.usage==7) *basis=true;
        else if(semantic.usage==5) {
         int nextCount=semantic.index+1;
         const int &largest=textureCount>nextCount?textureCount:nextCount;
         textureCount=largest;
        }
       }
      }
     }
    }
   }
  }
  int limit=8;
  const int &clamped=textureCount<limit?textureCount:limit;
  *fvf|=((unsigned)clamped&15)<<8;
 }
}
