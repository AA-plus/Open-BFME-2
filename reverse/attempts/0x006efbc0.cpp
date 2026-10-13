// ?Rva006EFBC0ObjectMemberLookup@@YAPAVAptValue@@PAV1@PBVEAStringC@@@Z
// partial score=0.7730629595203664 date=2026-10-13
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?Rva006EFBC0ObjectMemberLookup@@YAPAVAptValue@@PAV1@PBVEAStringC@@@Z
// partial score=0.671748132 date=2026-10-09
// cl:  /O2 /DNDEBUG /MD /EHsc
// AptCharacterInst::objectMemberLookup. Native EFBC0..F113C code
// and F1140..F12EF dispatch tables; WB1784910 is the semantic guide.
// All offsets below are measured from native accesses, not WB's +4 CIH view.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
}
#define CHARACTER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp"
#define CIH_FILE "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
class EAStringC {
 void *data;
public:
 EAStringC(){clear();} ~EAStringC(); EAStringC &clear();
 EAStringC &operator=(const EAStringC&);
 bool IsEmpty()const; const char *rva00620090()const;
 unsigned int rva006D3750()const;
 bool IsEqualTo(const EAStringC*)const;
 bool rva006D30D0(const EAStringC*)const;
 bool rva006D3510(const char*)const;
 EAStringC &MakeLower();
};
class AptCIH;
class AptValue {
public:
 bool isCIH(bool)const; AptCIH *c_cih(bool);
 bool isUndefined()const; int getVtblIndex()const;
 int toInteger()const; float toFloat()const;
 void toString(EAStringC&)const;void SetString(const char*);
};
class BfmeAptValue006DCD20 {
public:virtual void AddRef();unsigned flags;bool rva006E02B0()const; void *rva006E0F40()const;bool isCharacterInst()const;void setGCRootCount(unsigned);
};
class AptString:public AptValue {
public:static AptString *Create();
 __forceinline EAStringC &value(){return *(EAStringC*)((char*)this+8);}
};
struct AptNativeHash {void Set(const EAStringC *const,AptValue *const);};
class AptCIH {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual AptNativeHash *slot3();
 char unknown04[8]; float matrix[6];
 char unknown24[0x44-0x24]; float *properties; AptCIH *parent;
 void *instance;char unknown50[0x60-0x50];
 bool rva006CFCD0()const;
 bool IsSpriteInst(bool)const; bool IsAnimationInst(bool)const;
 void factorySetProperty(int,float,bool);
 void factoryEnsureProperties();void *rva006CFF40()const;bool IsCharacterInst()const; void rva006E1DD0(void*);
 void SetEventHandler(int); void RemoveEventHandler(int);
 bool rva006E1F90(int);
};
static __forceinline bool isText(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xC4);
 const AptValue *v=(const AptValue*)cih;
 return v->getVtblIndex()==15 && !v->isUndefined();
}
static __forceinline bool isButton(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xB5);
 const AptValue *v=(const AptValue*)cih;
 return v->getVtblIndex()==14 && !v->isUndefined();
}
class Rva006EBFF0 {public:void rva006EBE60(AptValue*);void rva006EBFF0(AptValue*);};
class Rva006E1260 {public:void call(void*);};
class Rva006E9A40List {public:void add(AptCIH*);};
class Rva006E0DE0 {public:int rva006E0DE0(AptValue*);};
template<class T>class AptValueSet {public:unsigned short reserved,count;T *items;bool has(T)const;};
class Rva006E34D0 {public:
 char unknown00[0x20]; AptValueSet<AptValue*> contexts,cihs;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
static __forceinline void addSet(AptValueSet<AptValue*> *set,AptValue *v){((Rva006E9A40List*)set)->add((AptCIH*)v);}
struct AptActionInterpreter {bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);};
extern AptActionInterpreter g_aptDateInterpreter;
struct R4Word {const char*name;int id;};
const R4Word *Rva008ABF40(const char*,unsigned int);
const R4Word *Rva008D48F0(const char*,unsigned int);
EAStringC *Rva0070B4F0GetString(int);
void __cdecl Rva006CC110Log(int,const char*,...);
struct TextDefinition {char unknown00[0x2C];int multiline,wordWrap;const char*defaultText;};
struct TextInstance {
 char unknown00[0xC]; TextDefinition *definition;
 char unknown10[8]; EAStringC text,variable; int unknown20;
 unsigned textColor; int maxScroll,scroll; unsigned backgroundColor,borderColor;
 int autoSize; char unknown3C[0x50-0x3C]; float left,top,right,bottom;
 char unknown60[0xC]; unsigned dirty; int unknown70;
 unsigned reserved0:1,border:1,background:1,mouseWheel:1,reserved4:28;
};
struct Rect {float left,top,right,bottom;};

class AptInteger {public:static AptValue *Create(int);};
class AptBoolean {public:static AptValue *Create(bool);};
AptValue *Rva008A4EA0MakeFloat(float);
extern AptValue *gpUndefinedValue;
struct BfmeM1208 {float a,b,c,d,e,f;};
void bfmeMul1208(const BfmeM1208*,const BfmeM1208*,BfmeM1208*);
struct BfmeQ1206 {int m_bfme00,m_bfme04,m_bfme08,m_bfme0c,m_bfme10,m_bfme14;};
extern "C" BfmeQ1206 g_bfmeD1206;
struct LookupMouse {char pad[0x74];int x,y;};

struct CharacterInstance {char pad[12];struct Definition {int a,b;int frames;};Definition *definition;};
void rva006ffc30(AptValue*,EAStringC&);
void rva006ffce0(AptValue*,EAStringC&);
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void*,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500:public BfmeAptValue006DCD20 {
 char rest[28];
 public:Rva006D6500(int);
 static void *operator new(unsigned n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
class Acac0Releaseable;
extern AptValue *g_shutdownAtE180A8; // lookup property 24; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18080; // lookup property 25; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18084; // lookup property 26; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE180B4; // lookup property 27; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18074; // lookup property 28; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE1806C; // lookup property 29; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern Acac0Releaseable *g_Va00E181A0; // lookup property 100; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181AC; // lookup property 101; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E1819C; // lookup property 103; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E18198; // lookup property 104; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181A4; // lookup property 105; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D8; // lookup property 106; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E0; // lookup property 107; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E8; // lookup property 108; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B0; // lookup property 109; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181DC; // lookup property 110; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F0; // lookup property 111; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181EC; // lookup property 112; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E4; // lookup property 113; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B8; // lookup property 114; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181BC; // lookup property 115; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D4; // lookup property 116; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C8; // lookup property 117; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D0; // lookup property 118; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B4; // lookup property 119; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C0; // lookup property 120; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181A8; // lookup property 121; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C4; // lookup property 122; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F8; // lookup property 123; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181FC; // lookup property 124; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F4; // lookup property 125; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181CC; // lookup property 126; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E18200; // lookup property 127; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
AptValue *Rva006EC3E0LoadMovie(AptValue *self,int nParams);
AptValue *Rva006EC590UnloadMovie(AptValue *self,int nParams);
BfmeAptValue006DCD20 *rva006ec670(BfmeAptValue006DCD20 *pValue, int nParams);
AptValue *Rva006EC6F0Depth(AptValue *context,int unusedArgumentCount);
void __cdecl lookupCallback006EC730(); // measured callback RVA0x006EC730; signature pending
AptValue *__cdecl Rva006EC900StartDrag(AptValue *self,int count);
AptValue *__cdecl Rva006ECA70PointHitTest(void *self,int count);
AptValue *Rva006ECC20LoadVariables(AptValue *self,int count);
void __cdecl lookupCallback006ECCB0(); // measured callback RVA0x006ECCB0; signature pending
AptValue *aptHelperClearFlag008AE450(void *entry, int count);
AptValue *aptHelperSetFlag008AE470(void *entry, int count);
void __cdecl lookupCallback006ED580(); // measured callback RVA0x006ED580; signature pending
AptValue *Rva006ED770RemoveMovieClip(AptValue *self,int);
void __cdecl lookupCallback006ED810(); // measured callback RVA0x006ED810; signature pending
void __cdecl lookupCallback006EDBD0(); // measured callback RVA0x006EDBD0; signature pending
AptValue *Rva006EDF20SwapDepths(AptValue *self,int count);
void __cdecl lookupCallback006EDFF0(); // measured callback RVA0x006EDFF0; signature pending
AptValue *rva006ee1b0(BfmeAptValue006DCD20 *entry);
AptValue *rva006ee210(BfmeAptValue006DCD20 *entry);
AptValue *rva006ee270(BfmeAptValue006DCD20 *entry);
AptValue *rva006ee310(BfmeAptValue006DCD20 *entry);
AptValue *__cdecl rva006ee3b0(AptValue *value);
AptValue *__cdecl rva006ee540(AptValue *value);
void __cdecl lookupCallback006EF570(); // measured callback RVA0x006EF570; signature pending
void __cdecl lookupCallback006EF6D0(); // measured callback RVA0x006EF6D0; signature pending
void __cdecl lookupCallback006EF920(); // measured callback RVA0x006EF920; signature pending

static __forceinline void refreshText(AptValue *context,TextInstance *text){
 if(text->dirty&4){AptCIH *parent=context->c_cih(false)->parent;((Rva006E1260*)context->c_cih(false))->call(parent);}
}
static __forceinline AptValue *makeLookupString(const EAStringC &s){AptString *v=AptString::Create();v->value()=s;return v;}
AptValue *__cdecl Rva006EFBC0ObjectMemberLookup(AptValue *context,const EAStringC *name){

 float number;

 AptCIH *initial=context->c_cih(false);

 if(isText(initial)){

  const R4Word *word=Rva008ABF40(name->rva00620090(),name->rva006D3750());

  if(word){

   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)context)->rva006E0F40();

   switch(word->id){

   case 1:{
AptString *v=AptString::Create();
switch(text->autoSize){
case 0:v->value()=*Rva0070B4F0GetString(0x56);
break;
case 1:v->value()=*Rva0070B4F0GetString(0x7E);
break;
case 2:v->value()=*Rva0070B4F0GetString(0x29);
break;
case 3:v->value()=*Rva0070B4F0GetString(0x61);
break;
default:v->value()=*Rva0070B4F0GetString(0x61);
break;
}
return v;
}

   case 2:return AptBoolean::Create(text->background);

   case 3:return AptInteger::Create(text->backgroundColor&0xFFFFFF);

   case 4:return AptBoolean::Create(text->border);

   case 5:return AptInteger::Create(text->borderColor&0xFFFFFF);

   case 7:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)context->c_cih(false));
return AptInteger::Create(text->text.rva006D3750());

   case 8:return gpUndefinedValue;

   case 9:refreshText(context,text);
return AptInteger::Create(text->maxScroll);

   case 10:return AptBoolean::Create((text->definition->multiline&0xFFFFFF)!=0);

   case 11:refreshText(context,text);
return AptInteger::Create(text->scroll);

   case 12:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)context->c_cih(false));
return makeLookupString(text->text);

   case 13:return AptInteger::Create(text->textColor&0xFFFFFF);

   case 14:refreshText(context,text);
return Rva008A4EA0MakeFloat(*(float*)((char*)text+0x48));

   case 15:refreshText(context,text);
return Rva008A4EA0MakeFloat(*(float*)((char*)text+0x44));

   case 16:{
AptString *v=AptString::Create();
v->SetString("dynamic");
return v;
}

   case 17:if(text->variable.IsEmpty())return gpUndefinedValue;
return makeLookupString(text->variable);

   case 18:return AptBoolean::Create((text->definition->wordWrap&0xFFFFFF)!=0);

   case 19:{
refreshText(context,text);
Rect r;
context->c_cih(false)->rva006E1DD0(&r);
float n=r.bottom-r.top;
_ReadWriteBarrier();
if(n<0)n=0;
return Rva008A4EA0MakeFloat(n);
}

   case 20:{
refreshText(context,text);
Rect r;
context->c_cih(false)->rva006E1DD0(&r);
float n=r.right-r.left;
if(n<0)n=0;
return Rva008A4EA0MakeFloat(n);
}

   case 21:return AptBoolean::Create(text->mouseWheel);

   }

  }

 }

 const R4Word *word=context && context->isCIH(false)?Rva008D48F0(name->rva00620090(),name->rva006D3750()):0;

 if(!word)return 0;

 AptCIH *cih=context->c_cih(false);

 if(!cih->IsCharacterInst())aptAssert("isCharacterInst()",CIH_FILE,0xA5);

 CharacterInstance *inst=(CharacterInstance*)cih->instance;

 switch(word->id){

 case 1:{
if(((BfmeAptValue006DCD20*)cih)->rva006E02B0()){
TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)cih)->rva006E0F40();
if(text->autoSize!=3 && text->autoSize!=0 && text->dirty&4)((Rva006E1260*)cih)->call(cih->parent);
}
number=cih->matrix[4];
break;
}

 case 2:number=cih->matrix[5];
break;

 case 3:number=cih->properties?cih->properties[2]:cih->matrix[0]*100.0f;
break;

 case 4:number=cih->properties?cih->properties[3]:cih->matrix[3]*100.0f;
break;

 case 7:number=cih->properties?cih->properties[7]:*(float*)((char*)cih+0x24)*100.0f;
break;

 case 8:number=cih->properties?cih->properties[11]:1.0f;
break;

 case 5:number=(float)(*(int*)((char*)cih->rva006CFF40()+0x18)+1);
break;

 case 24:return g_shutdownAtE180A8;

 case 25:return g_shutdownAtE18080;

 case 26:return g_shutdownAtE18084;

 case 27:return g_shutdownAtE180B4;

 case 28:return g_shutdownAtE18074;

 case 29:return g_shutdownAtE1806C;

 case 12:{
EAStringC s;
rva006ffc30((AptValue*)cih,s);
return makeLookupString(s);
}

 case 9:{
Rect r;
cih->rva006E1DD0(&r);
number=r.right-r.left;
if(number<0)number=0;
break;
}

 case 10:{
Rect r;
cih->rva006E1DD0(&r);
number=r.bottom-r.top;
if(number<0)number=0;
break;
}

 case 11:cih->factoryEnsureProperties();
number=cih->properties[6];
break;

 case 6:number=(float)inst->definition->frames;
break;

 case 13:number=(float)inst->definition->frames;
break;

 case 21:{
BfmeM1208 m=*(const BfmeM1208*)&g_bfmeD1206;
for(AptCIH *p=cih;
p;
p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);
number=((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->x-m.e)*m.a-((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->y-m.f)*m.b;
break;
}

 case 22:{
BfmeM1208 m=*(const BfmeM1208*)&g_bfmeD1206;
for(AptCIH *p=cih;
p;
p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);
number=((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->y-m.f)*m.d+((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->x-m.e)*m.c;
break;
}

 case 118:if(!g_Va00E181D0){
g_Va00E181D0=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ECA70PointHitTest);
((Rva006D6500*)g_Va00E181D0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D0)->AddRef();
}
return (AptValue*)g_Va00E181D0;

 case 126:if(!g_Va00E181CC){
g_Va00E181CC=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC900StartDrag);
((Rva006D6500*)g_Va00E181CC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181CC)->AddRef();
}
return (AptValue*)g_Va00E181CC;

 case 106:if(!g_Va00E181D8){
g_Va00E181D8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ECC20LoadVariables);
((Rva006D6500*)g_Va00E181D8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D8)->AddRef();
}
return (AptValue*)g_Va00E181D8;

 case 103:if(!g_Va00E1819C){
g_Va00E1819C=(Acac0Releaseable*)new Rva006D6500((int)&aptHelperSetFlag008AE470);
((Rva006D6500*)g_Va00E1819C)->setGCRootCount(1);
((Rva006D6500*)g_Va00E1819C)->AddRef();
}
return (AptValue*)g_Va00E1819C;

 case 104:if(!g_Va00E18198){
g_Va00E18198=(Acac0Releaseable*)new Rva006D6500((int)&aptHelperClearFlag008AE450);
((Rva006D6500*)g_Va00E18198)->setGCRootCount(1);
((Rva006D6500*)g_Va00E18198)->AddRef();
}
return (AptValue*)g_Va00E18198;

 case 100:if(!g_Va00E181A0){
g_Va00E181A0=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006ED580);
((Rva006D6500*)g_Va00E181A0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A0)->AddRef();
}
return (AptValue*)g_Va00E181A0;

 case 107:if(!g_Va00E181E0){
g_Va00E181E0=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee210);
((Rva006D6500*)g_Va00E181E0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E0)->AddRef();
}
return (AptValue*)g_Va00E181E0;

 case 110:if(!g_Va00E181DC){
g_Va00E181DC=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee1b0);
((Rva006D6500*)g_Va00E181DC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181DC)->AddRef();
}
return (AptValue*)g_Va00E181DC;

 case 108:if(!g_Va00E181E8){
g_Va00E181E8=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee310);
((Rva006D6500*)g_Va00E181E8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E8)->AddRef();
}
return (AptValue*)g_Va00E181E8;

 case 113:if(!g_Va00E181E4){
g_Va00E181E4=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee270);
((Rva006D6500*)g_Va00E181E4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E4)->AddRef();
}
return (AptValue*)g_Va00E181E4;

 case 112:if(!g_Va00E181EC){
g_Va00E181EC=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee3b0);
((Rva006D6500*)g_Va00E181EC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181EC)->AddRef();
}
return (AptValue*)g_Va00E181EC;

 case 111:if(!g_Va00E181F0){
g_Va00E181F0=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee540);
((Rva006D6500*)g_Va00E181F0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F0)->AddRef();
}
return (AptValue*)g_Va00E181F0;

 case 101:if(!g_Va00E181AC){
g_Va00E181AC=(Acac0Releaseable*)new Rva006D6500((int)&rva006ec670);
((Rva006D6500*)g_Va00E181AC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181AC)->AddRef();
}
return (AptValue*)g_Va00E181AC;

 case 109:if(!g_Va00E181B0){
g_Va00E181B0=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ED770RemoveMovieClip);
((Rva006D6500*)g_Va00E181B0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B0)->AddRef();
}
return (AptValue*)g_Va00E181B0;

 case 105:if(!g_Va00E181A4){
g_Va00E181A4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC3E0LoadMovie);
((Rva006D6500*)g_Va00E181A4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A4)->AddRef();
}
return (AptValue*)g_Va00E181A4;

 case 121:if(!g_Va00E181A8){
g_Va00E181A8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC590UnloadMovie);
((Rva006D6500*)g_Va00E181A8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A8)->AddRef();
}
return (AptValue*)g_Va00E181A8;

 case 114:if(!g_Va00E181B8){
g_Va00E181B8=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006ED810);
((Rva006D6500*)g_Va00E181B8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B8)->AddRef();
}
return (AptValue*)g_Va00E181B8;

 case 119:if(!g_Va00E181B4){
g_Va00E181B4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ED770RemoveMovieClip);
((Rva006D6500*)g_Va00E181B4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B4)->AddRef();
}
return (AptValue*)g_Va00E181B4;

 case 115:if(!g_Va00E181BC){
g_Va00E181BC=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC6F0Depth);
((Rva006D6500*)g_Va00E181BC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181BC)->AddRef();
}
return (AptValue*)g_Va00E181BC;

 case 117:if(!g_Va00E181C8){
g_Va00E181C8=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EC730);
((Rva006D6500*)g_Va00E181C8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C8)->AddRef();
}
return (AptValue*)g_Va00E181C8;

 case 116:if(!g_Va00E181D4){
g_Va00E181D4=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EDFF0);
((Rva006D6500*)g_Va00E181D4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D4)->AddRef();
}
return (AptValue*)g_Va00E181D4;

 case 120:if(!g_Va00E181C0){
g_Va00E181C0=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EDBD0);
((Rva006D6500*)g_Va00E181C0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C0)->AddRef();
}
return (AptValue*)g_Va00E181C0;

 case 122:if(!g_Va00E181C4){
g_Va00E181C4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EDF20SwapDepths);
((Rva006D6500*)g_Va00E181C4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C4)->AddRef();
}
return (AptValue*)g_Va00E181C4;

 case 127:if(!g_Va00E18200){
g_Va00E18200=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006ECCB0);
((Rva006D6500*)g_Va00E18200)->setGCRootCount(1);
((Rva006D6500*)g_Va00E18200)->AddRef();
}
return (AptValue*)g_Va00E18200;

 case 14:return makeLookupString(*(EAStringC*)((char*)cih+8));

 case 16:{
AptString *v=AptString::Create();
EAStringC s;
rva006ffce0((AptValue*)context->c_cih(false),s);
v->SetString(s.rva00620090());
return v;
}

 case 124:if(!g_Va00E181FC){
g_Va00E181FC=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EF920);
((Rva006D6500*)g_Va00E181FC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181FC)->AddRef();
}
return (AptValue*)g_Va00E181FC;

 case 123:if(!g_Va00E181F8){
g_Va00E181F8=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EF6D0);
((Rva006D6500*)g_Va00E181F8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F8)->AddRef();
}
return (AptValue*)g_Va00E181F8;

 case 125:if(!g_Va00E181F4){
g_Va00E181F4=(Acac0Releaseable*)new Rva006D6500((int)&lookupCallback006EF570);
((Rva006D6500*)g_Va00E181F4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F4)->AddRef();
}
return (AptValue*)g_Va00E181F4;

 default:return 0;

 }

 _ReadWriteBarrier();
return Rva008A4EA0MakeFloat(number);

}

