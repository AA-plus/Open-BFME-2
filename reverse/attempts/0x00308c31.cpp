// ?loadFXShaderSetup@StandingWaterArea@@QAEXXZ
// partial score=0.962 date=2026-10-12
// ?loadFXShaderSetup@StandingWaterArea@@QAEXXZ
// partial score=0.962 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct AsciiStringRef {const AsciiString *m_string;};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){}const char *m_ptr;int m_len;};
struct AsciiStringPlusText:AsciiStringRef {operator AsciiString();Rva000B3F84Pair m_right;};
AsciiStringPlusText operator+(const AsciiString &,const char *);
struct BfmeR1025 {char *m_bfmeName;};
char bfmeGo1025F(BfmeR1025 *);
class Rva003081C7 {public:unsigned char rva003081C7();};
struct Rva003080AARef;
class Rva003080AA {public:Rva003080AARef *rva003080AA(int);};
class Rva00152D1CObj {public:void rva152d1c(int);};
class GameLODManager;
extern GameLODManager *TheGameLODManager;
struct WaterLODView {char before[0x1784];int level;};
class MeshModelClass {public:
 virtual void deleteThis();
 int refs;char beforeMaterial[0x94-8];Rva003080AA *material;
};
class MeshClass {public:MeshModelClass *Get_Model();};
class RenderObjClass {public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 virtual int classID();virtual void slot4();virtual MeshClass *peekLOD();
};
RenderObjClass *Create_Render_Obj(const char *);
static const char WaterShaderSuffixes[8]={'L',0,'M',0,0,0,0,0};
static const char WaterNoShaderSuffix[1]={0};
static const int WaterShaderLODs[4]={0,1,2,3};
static __forceinline char shaderExists(AsciiString filename) {
 return bfmeGo1025F((BfmeR1025*)&filename);
}
static __forceinline RenderObjClass *createWaterModel(const AsciiString &filename) {
 AsciiString name(filename);
 return Create_Render_Obj(name.str());
}
class StandingWaterArea {public:
 void loadFXShaderSetup();
 char before[0x80];AsciiString shaderName;Rva003080AARef *shader;
};
void StandingWaterArea::loadFXShaderSetup() {
 if(!((Rva003081C7*)this)->rva003081C7())return;
 AsciiString base(shaderName);
 if(!base.isEmpty()) {
  for(int i=0;i<4;++i)base.removeLastChar();
 }
 if(!base.isEmpty()) {
  int lod=((WaterLODView*)TheGameLODManager)->level;
  const char *suffix=WaterNoShaderSuffix;
  for(;lod<4;++lod) {
   if(shaderExists(base+(WaterShaderSuffixes+2*lod))) {
    suffix=WaterShaderSuffixes+2*lod;
    break;
   }
  }
  RenderObjClass *obj=createWaterModel(base+suffix);
  if(obj && obj->classID()==0) {
   MeshClass *mesh=obj->peekLOD();
   if(mesh) {
    MeshModelClass *model=mesh->Get_Model();
    if(model) {
     shader=model->material->rva003080AA(0);
     if(--model->refs==0)model->deleteThis();
     if(shader)((Rva00152D1CObj*)shader)->rva152d1c(WaterShaderLODs[((WaterLODView*)TheGameLODManager)->level]);
    }
   }
  }
 }
}
