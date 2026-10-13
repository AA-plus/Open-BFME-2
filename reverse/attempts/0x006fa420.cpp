// ?rva006FA420@Rva006FB860@@QAEPAVAptCIH@@HH@Z
// partial score=0.99 date=2026-10-13
// cl: /O2 /G6 /EHsc /MD /DNDEBUG
// ?rva006FACA0@Rva006FB860@@QAE_NHHPAPAX@Z, retail 0x006FACA0..0x006FAF73.
// WB 0x017999A0 explicitly identifies AptAnimationPoolData::HandleFocusButton,
// AptInput.cpp:1207..1304. Target instructions occupy 687 bytes; their aligned
// five-target jump table and fifteen-byte case map extend the body to 723.
// The target map sends 1/2/14/15 to string IDs 10/13/19/3 respectively.
// Retail independently proves ECX=this, RET12, AL result, current+6C,
// CIH parent+48/instance+4C, instance hash+10, and checked-string name+8.
// Partial ABI views retain the already pinned neutral method and class name.
// The BFME1 AptInput.cpp donor at 575ba2b04 supplies the related suffix-search
// semantics, but its clean compiled bodies do not place this handler; the
// complete string-resolution and interpreter paths here follow WB and retail.
// No donor layout or complete class identity is asserted by byte matching.
class EAStringC {
    void *data;
public:
    EAStringC();
    ~EAStringC();
    const char *rva00620090() const;
    unsigned int rva006D3750() const;
};
class AptValue;
class BfmeAptValue006DCD20 {
public:
    bool isString() const;
    bool isUndefined() const;
    void *rva006E04A0() const;
    int isScriptFunction() const;
    BfmeAptValue006DCD20 *rva006DCEE0();
    void setGCRootCount(unsigned int);
    bool isCIH(bool) const;
    bool rva006DCC60(bool) const;
    BfmeAptValue006DCD20 *rva006DCF60(bool);
    BfmeAptValue006DCD20 *checkedString();
};
class AptCIH {public:bool rva006CFCD0()const;void *rva006E1170()const;int rva006E1F90(int);};
struct AptNativeHash;
class AptValue {public:virtual void AddRef();virtual void Release();virtual void ForceDelete();virtual AptNativeHash *GetNativeHashVirtual();virtual bool ContainsNativeHashVirtual() const;AptValue *findChild(const EAStringC *,AptValue *);};
struct AptNativeHash {int mnTotalSize;void *mpData;AptValue *mp__proto__;AptValue *mpPrototype;unsigned int nEventHandlers;};
class Rva0070B380 {public:void *lookup(const EAStringC&);};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);void rva006FE920();};
struct AptActionSetup {AptValue *context,*value;const char *name;int action;};
struct AptActionInterpreter {public:void *PrepareForExecution(AptActionSetup*);void CleanupAfterExecution(void*,AptActionSetup*);void callFunction(AptValue*,AptValue*,int);};
extern AptActionInterpreter g_aptDateInterpreter;
class Rva006E34D0;extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
struct Rva006E3710Node;class Rva006E3710 {public:bool rva006E3710(Rva006E3710Node*);};
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
EAStringC *__cdecl Rva0070B4F0GetString(int);
unsigned char __cdecl rva006FEC00(int,int,EAStringC*,int*,EAStringC*);
class Rva006FB860 {public:char pad[0x6C];AptCIH *current;bool rva006FACA0(int,int,void**);void rva006FAB40(BfmeAptValue006DCD20 *,int,int);void rva006FA100(AptCIH *,int);AptCIH *rva006FA420(int,int);};
bool Rva006FB860::rva006FACA0(int event,int transition,void **out)
{
 if (!out) {
  g_bfmeAptAssertAtE17734("ppNewButton","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x4B7);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 *out=0;if (!current) return false;
 if (transition) return false;
 EAStringC *key;
 switch(event) {
 case 14:key=Rva0070B4F0GetString(0x13);break;
 case 15:key=Rva0070B4F0GetString(3);break;
 case 1:key=Rva0070B4F0GetString(10);break;
 case 2:key=Rva0070B4F0GetString(13);break;
 default:return false;
 }
 AptCIH *context=*(AptCIH**)((char*)current+0x48);
 Rva0070B380 *hash=*(Rva0070B380**)((char*)context->rva006E1170()+0x10);
 BfmeAptValue006DCD20 *value=(BfmeAptValue006DCD20*)hash->lookup(*key);if(!value)return false;
 if(value->isString()) {
  EAStringC rest;BfmeAptValue006DCD20 *resolved;
  EAStringC *source=(EAStringC*)((char*)value->checkedString()+8);
  rva006FEC00((int)context,0,source,(int*)&resolved,&rest);
  if(resolved) {
   BfmeAptValue006DCD20 *node=resolved->rva006DCF60(false);
   if(rest.rva006D3750()==0 && (node->rva006DCC60(false)||((AptCIH*)node)->rva006CFCD0())) *out=node;
   else if((int)rest.rva006D3750()>0 && ((AptCIH*)node)->rva006CFCD0()) {
    Rva0070B380 *members=*(Rva0070B380**)((char*)*(void**)((char*)node+0x4C)+0x10);
    BfmeAptValue006DCD20 *found=(BfmeAptValue006DCD20*)members->lookup(rest);if(found)value=found;
   }
  }
 }
 if((unsigned char)value->isScriptFunction()) {
  AptActionSetup setup;const char *text=key->rva00620090();setup.context=(AptValue*)context;setup.value=(AptValue*)value;setup.name=text;setup.action=0x400000;
  void *saved=g_aptDateInterpreter.PrepareForExecution(&setup);
  g_aptDateInterpreter.callFunction((AptValue*)context,(AptValue*)value,0);
  g_aptDateInterpreter.CleanupAfterExecution(saved,&setup);
  BfmeAptValue006DCD20 *result=(BfmeAptValue006DCD20*)((AptBasePtrStack*)&g_aptDateInterpreter)->At(0);
  if(result->isCIH(false)){((AptValue*)result)->AddRef();((AptBasePtrStack*)&g_aptDateInterpreter)->rva006FE920();value=result;}
  else {
   ((AptBasePtrStack*)&g_aptDateInterpreter)->rva006FE920();
   return true;
  }
 } else ((AptValue*)value)->AddRef();
 if(value->rva006DCF60(false)->rva006DCC60(false)||((AptCIH*)value->rva006DCF60(false))->rva006CFCD0()) {
  if(!((Rva006E3710*)g_bfmeAptPtrAtE176D0)->rva006E3710((Rva006E3710Node*)value->rva006DCF60(false))) *out=value->rva006DCF60(false);
 }
 ((AptValue*)value)->Release();return false;
}

struct AptInputEventName {unsigned int mask;int stringId;};
extern AptInputEventName g_00DDC8EC[6];
struct Rva006E0AC0Entry {int m_mask;int m_str;};
extern Rva006E0AC0Entry g_00DDC2E8[];
class Rva006E0D40 {public:void rva006E0D40();};
class Rva006F97B0 {public:void rva006F97B0();};
class Rva006DBB60ShrNAndField {public:bool get() const;};
class AptActionQueueC {public:void rva006E3740(AptValue *,AptValue *,AptValue *,int,int);void rva006E3810(AptValue *,AptValue *,AptValue *,int,int);void rva006E4B80(void *,AptCIH *,int,int);};
class AptInputScriptFunction {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();virtual void slot38();
 virtual AptInputScriptFunction *Duplicate(AptValue *);
 virtual void slot40();
 virtual AptValue *GetNumArguments();
 char pad04[0x20-4];
 AptCIH *owner;
 AptCIH *parent;
};
struct AptInputPoolView {
 char pad[0xA0];
 AptActionQueueC *queue;
 void AddActionToQueue(AptValue *ctx,AptValue *fn,AptValue *res,int code,int arg){queue->rva006E3740(ctx,fn,res,code,arg);}
};
void Rva006FB860::rva006FAB40(BfmeAptValue006DCD20 *value,int mask,int arg)
{
 AptValue *pValue=(AptValue*)value;
 if(!pValue->ContainsNativeHashVirtual()) {
  g_bfmeAptAssertAtE17734("pValue->ContainsNativeHashVirtual()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x483);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 if(value->isCIH(false) && !((AptCIH*)value->rva006DCF60(false))->rva006E1F90(mask)) return;
 if(!value->isCIH(false) && !(pValue->GetNativeHashVirtual()->nEventHandlers&mask) && !(pValue->GetNativeHashVirtual()->mp__proto__->GetNativeHashVirtual()->nEventHandlers&mask)) return;
 for(int i=0;i<6;i++) {
  if(g_00DDC8EC[i].mask&mask) {
   BfmeAptValue006DCD20 *child=(BfmeAptValue006DCD20*)pValue->findChild(Rva0070B4F0GetString(g_00DDC8EC[i].stringId),0);
   if(child && ((Rva006DBB60ShrNAndField*)child)->get() && (unsigned char)child->isScriptFunction()) {
    AptInputScriptFunction *fn=(AptInputScriptFunction*)child->rva006DCEE0();
    AptCIH *oldOwner=fn->owner;
    if(oldOwner!=(AptCIH*)pValue) {
     fn=fn->Duplicate(pValue);
     ((Rva006E0D40*)fn->parent)->rva006E0D40();
     ((AptValue*)fn->parent)->Release();
     fn->parent=oldOwner;
     ((Rva006F97B0*)oldOwner)->rva006F97B0();
     ((AptValue*)fn->parent)->AddRef();
     ((BfmeAptValue006DCD20*)fn)->setGCRootCount(1);
    }
    ((AptInputPoolView*)g_bfmeAptPtrAtE176D0)->AddActionToQueue(pValue,(AptValue*)fn,fn->GetNumArguments(),g_00DDC2E8[i].m_mask,arg);
   }
  }
 }
}

// ?rva006FA100@Rva006FB860@@QAEXPAVAptCIH@@H@Z, retail 0x006FA100..0x006FA340
// (RET8; the 8-entry case table completes the 576B extent). WB 0x01797C60
// places it in AptInput.cpp by its asserts at lines 257/258/267 (pInst,
// pInst->isButtonInst(), pInst->pParent): button-instance event broadcast. The BFME 1 AptInput.cpp donor at 575ba2b04
// (BfmeBroadcast1282) is the semantic guide only; its original name is unknown.
// Retail fixes the +0x48 parent/+0x4C character, descriptor +0x34/+0x38/+0x3C,
// the 7x12B key-route table at 0xDDC898 and the pool queue callees.
class Rva006DBB30SarDwordField {public:int get() const;};
class AptAnimationPoolData {public:void rva006E6540();};
extern int g_00E17704;
extern void (__cdecl *g_bfmeAptFreeAtE17784)(void *,int);
struct AptButtonRoute {unsigned int mask;int stringId;int keyCode;};
extern AptButtonRoute g_00DDC898[7];
struct AptButtonFlags {char pad[0x10];unsigned int flags;};
class AptButtonInstView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual AptButtonFlags *GetNativeHashVirtual();
 char pad04[0x48-4];
 AptCIH *pParent;
 void *payload;
};
struct AptButtonRecord {int mask;void *actions;};
struct AptButtonSound {char pad[8];void *handle;};
struct AptButtonDescriptor {char pad[0x34];int count;AptButtonRecord *records;AptButtonSound **sounds;};
struct AptButtonCharacter {char pad[0xc];AptButtonDescriptor *descriptor;};
void Rva006FB860::rva006FA100(AptCIH *inst,int mode)
{
 AptButtonInstView *pInst=(AptButtonInstView*)inst;
 if (!pInst) {
  g_bfmeAptAssertAtE17734("pInst","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x101);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 if (!pInst) {
  g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB5);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 if (((const Rva006DBB30SarDwordField*)pInst)->get()!=0xE || ((const BfmeAptValue006DCD20*)pInst)->isUndefined()) {
  g_bfmeAptAssertAtE17734("pInst->isButtonInst()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x102);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 AptButtonDescriptor *desc=((AptButtonCharacter*)pInst->payload)->descriptor;
 for (int i=0;i<desc->count;i++) {
  if (desc->records[i].mask&mode) {
   if (!pInst->pParent) {
    g_bfmeAptAssertAtE17734("pInst->pParent","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x10B);
    if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
   }
   (*(AptActionQueueC**)((char*)this+0xA0))->rva006E4B80(&desc->records[i].actions,pInst->pParent,0x400000,g_00E17704);
  }
 }
 int keyMask=0;
 if (mode&0x08) keyMask=0x800;
 if (mode&0x04) keyMask|=0x400;
 if (mode&0x40) keyMask|=0x1000;
 if (mode&0x01) keyMask|=0x2000;
 if (mode&0x02) keyMask|=0x4000;
 if (mode&0x20) keyMask|=0x8000;
 if (mode&0x10) keyMask|=0x10000;
 if (pInst->GetNativeHashVirtual()->flags&keyMask) {
  for (int j=0;j<7;j++) {
   if (g_00DDC898[j].mask&keyMask) {
    AptValue *found=(AptValue*)((Rva0070B380*)((BfmeAptValue006DCD20*)pInst)->rva006E04A0())->lookup(*Rva0070B4F0GetString(g_00DDC898[j].stringId));
    if (found)
     (*(AptActionQueueC**)((char*)g_bfmeAptPtrAtE176D0+0xA0))->rva006E3810((AptValue*)pInst,found,0,g_00DDC2E8[j].m_mask,((g_00DDC898[j].keyCode&0x7f)<<10)|5);
   }
  }
 }
 if (desc->sounds) {
  switch (mode) {
  case 2: if (desc->sounds[0]) g_bfmeAptFreeAtE17784(desc->sounds[0]->handle,0); break;
  case 1: if (desc->sounds[1]) g_bfmeAptFreeAtE17784(desc->sounds[1]->handle,0); break;
  case 4: if (desc->sounds[2]) g_bfmeAptFreeAtE17784(desc->sounds[2]->handle,0); break;
  case 8: if (desc->sounds[3]) g_bfmeAptFreeAtE17784(desc->sounds[3]->handle,0); break;
  }
 }
 ((AptAnimationPoolData*)this)->rva006E6540();
}

struct BfmeM1208 {float m[6];};
void __cdecl bfmeMul1208(const BfmeM1208 *,const BfmeM1208 *,BfmeM1208 *);
struct BfmeMesh1290;
struct BfmeTransform2_1290;
class BfmePicker1284 {public:bool bfmeMeshHitTest1290(BfmeMesh1290 *,const BfmeTransform2_1290 *,int,int);};
struct AptButtonShape {int eType;int unknown04;float x0,y0,x1,y1;};
struct AptButtonHitRecord {unsigned int flags;AptButtonShape *shape;int unknown08;BfmeM1208 matrix;char unknown24[0x44-0x24];};
struct AptButtonHitDescriptor {char pad[0x24];int recordCount;AptButtonHitRecord *records;};
struct AptButtonHitCharacter {int eType;char pad04[4];AptButtonHitDescriptor desc;};
struct AptButtonHitCharInst {char pad[0xc];AptButtonHitCharacter *pCharacter;};
class AptButtonHitCIH {
public:
 __forceinline bool isButtonInst() const {
  if (!this) {
   g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB5);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  return ((const Rva006DBB30SarDwordField*)this)->get()==0xE && !((const BfmeAptValue006DCD20*)this)->isUndefined();
 }
 __forceinline bool isCharacterInst() const {
  return ((const Rva006DBB30SarDwordField*)this)->get()>=0xC && ((const Rva006DBB30SarDwordField*)this)->get()<=0x13 && !((const BfmeAptValue006DCD20*)this)->isUndefined();
 }
 __forceinline AptButtonHitCharInst *getCharacterInst() const {
  if (!this) {
   g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB0);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  if (!isCharacterInst()) {
   g_bfmeAptAssertAtE17734("isCharacterInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xA5);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  return inst;
 }
 char pad[0x4c];
 AptButtonHitCharInst *inst;
};
struct AptButtonInstance {AptButtonHitCIH *pCIH;BfmeM1208 matrix;};
struct AptButtonPoolView {char pad[0x10];int nButtonInstances;AptButtonInstance *aButtonInstanceList;};
#define gpButtonPool ((AptButtonPoolView*)g_bfmeAptPtrAtE176D0)
AptCIH *Rva006FB860::rva006FA420(int x,int y)
{
 int checked=0;
 for (int i=gpButtonPool->nButtonInstances-1;i>=0;i--) {
  if (gpButtonPool->aButtonInstanceList[i].pCIH==0) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1F0);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  if (((BfmeAptValue006DCD20*)gpButtonPool->aButtonInstanceList[i].pCIH)->isUndefined()) continue;
  if (!gpButtonPool->aButtonInstanceList[i].pCIH->isButtonInst()) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH->isButtonInst()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1F8);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  AptButtonHitDescriptor *desc=&gpButtonPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->desc;
  if (gpButtonPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->eType!=4) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->eType == AptCharacterTypeButton","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1FB);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  for (int j=0;j<desc->recordCount;j++) {
   if (!(desc->records[j].flags&8)) continue;
   BfmeM1208 matrix=desc->records[j].matrix;
   bfmeMul1208(&gpButtonPool->aButtonInstanceList[i].matrix,&matrix,&matrix);
   AptButtonShape *shape=desc->records[j].shape;
   if (shape->eType==1) {
    if (((BfmePicker1284*)this)->bfmeMeshHitTest1290((BfmeMesh1290*)desc,(const BfmeTransform2_1290*)&matrix,x,y))
     return (AptCIH*)gpButtonPool->aButtonInstanceList[i].pCIH;
   } else if (shape->eType==2) {
    float x0=shape->x0,x1=shape->x1,y0=shape->y0,y1=shape->y1;
    if ((float)x>matrix.m[0]*x0+matrix.m[1]*y0+matrix.m[4] && (float)x<matrix.m[0]*x1+matrix.m[1]*y1+matrix.m[4]
     && (float)y>matrix.m[2]*x0+matrix.m[3]*y0+matrix.m[5] && (float)y<matrix.m[2]*x1+matrix.m[3]*y1+matrix.m[5])
     return (AptCIH*)gpButtonPool->aButtonInstanceList[i].pCIH;
   }
  }
  if (++checked==gpButtonPool->nButtonInstances) break;
 }
 return 0;
}
