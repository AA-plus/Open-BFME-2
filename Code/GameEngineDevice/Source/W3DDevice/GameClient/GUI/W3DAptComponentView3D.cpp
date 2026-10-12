// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
// Whole native 0x00740BCD..0x00740E76 RET12, 683B.
// WB 0x017EDEB0 asserts W3DAptComponentView3D::AddRenderObj.
// This is target reconstruction; BFME1 same-path donor only implements the
// separate animation binding operation, not this method.
// The first stack word is unused: its original source type remains unknown.
// Every view field and used virtual slot is based on this retail body; these
// view names do not establish original class names or undocumented slots.
#include <stdlib.h>
#include "ascii_string.h"
// Reuse the existing opaque 12-byte empty-set constructor ABI. Its source
// name is an established view, not an identity claim for the asset keys.
class Rva002EE9B7 { public: Rva002EE9B7(); private: unsigned storage[3]; };
void j_00015d7a();
// The registry already uses this 20-byte lifetime view and the same verified
// member-call projection of the tree destructor; no new template is emitted.
struct Q1ReceiverLocalSet {
 // The parent inlines these field stores; suppress the unused constructor
 // COMDAT, whose relocation spelling would compete with the registry copy.
 __declspec(dllimport) __forceinline Q1ReceiverLocalSet() : pad(0),changed(true) {}
 ~Q1ReceiverLocalSet() {
  typedef void (Rva002EE9B7::*TreeDestructor)();
  union { void (*raw)(); TreeDestructor member; } destroy;
  destroy.raw=j_00015d7a;
  (keys.*destroy.member)();
 }
 Rva002EE9B7 keys;
 unsigned pad;
 bool changed;
};
typedef char AptAssetHolderExtent[(sizeof(Q1ReceiverLocalSet)==20)?1:-1];
class AssetList { public: AssetList &operator<<(const AsciiString &); };
void bfmeMergeReceiverKeys(int);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
// Retail VA0x00E1F2B4 is a zero-initialized unsigned call counter.
// This descriptive name is reconstructed; the original identifier is unknown.
unsigned AptViewAddRenderObjCounter = 0;
struct AptVector { float x,y,z; void set(float a,float b,float c) {x=a;y=b;z=c;} };
struct AptSphere { AptVector center; float radius; };
struct AptMatrix {
 float m[3][4];
 AptMatrix() {
  m[0][0]=1.0f;m[0][1]=0.0f;m[0][2]=0.0f;m[0][3]=0.0f;
  m[1][0]=0.0f;m[1][1]=1.0f;m[1][2]=0.0f;m[1][3]=0.0f;
  m[2][0]=0.0f;m[2][1]=0.0f;m[2][2]=1.0f;m[2][3]=0.0f;
 }
};
class LightClass;
class AptRenderView {
public:
	virtual void release();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void setTransform(const AptMatrix &);
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void attachBone(LightClass *,int,int);
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual int boneCount();
	virtual const char *boneName(int);
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual const AptSphere &bounds();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void setVisible(int);
 int refCount;
};
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
class LightClass {
public:
 enum LightType { POINT=0,DIRECTIONAL,SPOT };
 LightClass(LightType);
 char prefix[0xC4];
 int type;
 unsigned flags;
 bool shadows;
 float intensity;
 AptVector ambient,diffuse,specular;
 float nearStart,nearEnd,farStart,farEnd;
 float spotAngle,spotAngleCos,spotExponent;
 AptVector direction;
};
// ABI-only projection of LightClass into its existing render-object prefix.
typedef char AptLightExtent[(sizeof(LightClass)==0x120)?1:-1];

class AptSceneView {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void addRenderObj(AptRenderView *);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void addLight(LightClass *,int);
};
class Rva00740AB4RefTarget;
class HTreeClass;
int Rva00740A60Get(const StringBase<char> &);
class W3DAptComponentView3D {
public:
 class AnimInfo {
 public:
  bool Init(const AsciiString &,Rva00740AB4RefTarget *,int);
  Rva00740AB4RefTarget *owner;
  HTreeClass *animation;
  int second,first;
 };
 void AddRenderObj(unsigned unused,const AsciiString &name,const StringBase<char> &mode);
 char unknown00[0xC];
 AptSceneView *scene;
 char unknown10[8];
 AptRenderView *camera;
 int cameraBone;
 AnimInfo anim;
};
void W3DAptComponentView3D::AddRenderObj(unsigned unused,const AsciiString &name,const StringBase<char> &mode) {
 ++AptViewAddRenderObjCounter;
 if (!scene) return;
 if (Rva0134FAA0) {
  Q1ReceiverLocalSet assets;
  *(AssetList *)&assets << name;
  bfmeMergeReceiverKeys((int)&assets);
 }
 AptRenderView *obj=(AptRenderView *)Create_Render_Obj(name.str());
 if (!obj) return;
 int count=obj->boneCount();
 for(int i=0;i<count;++i) {
  const char *bone=obj->boneName(i);
  if (!bone || !*bone) continue;
  if (!camera && !_strcmpi(bone,"CAMERA")) {
   ++obj->refCount;
   AptRenderView *old=camera;
   if (old && --old->refCount==0) old->release();
   camera=obj;cameraBone=i;
  } else if (strstr(bone,"LIGHT")) {
   const char *suffix=strchr(bone,'_');
   if (suffix && *suffix) {
    float factor=(float)(atoi(suffix+1)*0.01);
    if (factor>0.0f) {
     LightClass *light=new LightClass(LightClass::POINT);
     light->diffuse.set(0.5f,0.5f,0.5f);
     light->ambient.set(0.5f,0.5f,0.5f);
     light->specular.set(0.5f,0.5f,0.5f);
     light->shadows=true;
     const AptSphere &s=obj->bounds();
     double end=2.0*s.radius;
     double start=s.radius;
     light->farStart=(float)start;
     light->farEnd=(float)end;
     scene->addLight(light,1);
     obj->attachBone(light,i,0);
     AptRenderView *ref=(AptRenderView *)light;
     if (--ref->refCount==0) ref->release();
    }
   }
  }
 }
 AptMatrix identity;
 obj->setTransform(identity);
 obj->setVisible(0);
 scene->addRenderObj(obj);
 int modeIndex=Rva00740A60Get(mode);
 anim.Init(name,(Rva00740AB4RefTarget *)obj,modeIndex);
 if (--obj->refCount==0) obj->release();
}
