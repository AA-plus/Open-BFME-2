// ?rva006DF9A0@Rva006DF9A0@@QAEXXZ
// partial score=0.8701 date=2026-10-13
// cl: /O2
// ?findChild@AptValue@@QAEPAV1@PBVEAStringC@@PAV1@@Z
// partial score=0.88 date=2026-10-11
// Native6DF9A0 lookup: owned gperf vocabulary proves the built-in cases;
// getVariable caller proves AptValue::findChild name and two pointer arguments.
// Final RET8 ends6DFD92, then13 targets and37 compact indices end6DFDED.
// Layout facts below come from native accesses, not an inferred donor layout.
#include "../AptObject/AptScriptFunction.h"
#include <stdlib.h>
class EAStringC 
{
 void *mpData;
 public: unsigned int rva006D3750() const;
 const char *rva00620090() const;
 
}
;
struct R4Word 
{
 const char *name;
 int value;
 
}
;
const R4Word *Rva00897FD0(const char *,unsigned int);
class BfmeAptValue006DCD20 
{
 public: int isCIH(bool=false) const;
 int isObject() const;
 int isPrototype() const;
 int rva006DCC60(bool=false) const;
 BfmeAptValue006DCD20 *rva006DCF60(bool=false);
 BfmeAptValue006DCD20 *rva006DD0E0();
 BfmeAptValue006DCD20 *rva006DD120();
 void *rva006E04A0() const;
 
}
;
class Rva006DC9E0 
{
 public: int rva006DC9E0();
 
}
;
class BfmeN1034;
class Rva0070A5C0 
{
 public: BfmeN1034 *rva0070A5C0(int);
 
}
;
class AptValuePtrStack 
{
 public: int count,capacity;
 BfmeAptValue006DCD20 **elements;
 BfmeAptValue006DCD20 *rva006DE160();
 
}
;
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
struct FindChildInterpreterView 
{
 AptValuePtrStack args,withScope,unused,contexts;
 void *currentFunction;
 
}
;
struct FindChildFunctionView 
{
 char prefix[0x24];
 AptValue *parentAnim;
 
}
;
struct FindChildCIHView 
{
 char prefix[0x48];
 AptValue *parent;
 
}
;
struct FindChildObjectView 
{
 char prefix[0x1c];
 unsigned int flags;
 
}
;
AptCIH *_AptGetAnimationAtLevel(int);
extern AptValue *gpUndefinedValue;
extern AptValue *g_shutdownAtE18068,*g_shutdownAtE18070,*g_shutdownAtE180AC,*g_shutdownAtE180B8,*g_shutdownAtE180BC,*g_shutdownAtE18360;
class Rva00898D60Target;
extern Rva00898D60Target *g_Rva01337A20;
extern EAStringC g_00E18650;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define APT_ASSERT(c,t,n) if(!(c)) { g_bfmeAptAssertAtE17734(t,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValue.cpp",n); if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
#define B(v) ((BfmeAptValue006DCD20 *)(v))
#define I ((FindChildInterpreterView *)&g_aptDateInterpreter)
#define GLOBAL (*(AptValue **)&g_00E18650)
AptValue *AptValue::findChild(const EAStringC *name,AptValue *context)

{
 if(!context) context=this;
 const R4Word * t1_live_word_106 = Rva00897FD0(name->rva00620090(),name->rva006D3750());
 const R4Word * volatile word = t1_live_word_106;
 if(t1_live_word_106) 
 {
  switch(word->value) 
  {
   case 1: return 0;
   case 2: 
   {
    context=(AptValue *)I->contexts.rva006DE160();
    if(context==this) return this;
    if(I->withScope.count>0 && !((AptValue *)I->withScope.rva006DE160())->isUndefined()) 
    {
     AptValue *pWithStkTop=(AptValue *)I->withScope.rva006DE160();
     APT_ASSERT(pWithStkTop!=0,"pWithStkTop != NULL",0x42a);
     APT_ASSERT(pWithStkTop->ContainsNativeHashVirtual(),"pWithStkTop->ContainsNativeHashVirtual()",0x42b);
     if(context==pWithStkTop) return context;
     AptNativeHash *h=pWithStkTop->GetNativeHashVirtual();
     AptValue *prototype;
     while(h && (prototype=h->mp__proto__)) 
     {
      if(prototype==context) return pWithStkTop;
      h=prototype->GetNativeHashVirtual();
      
     }
     
    }
    AptNativeHash *h=GetNativeHashVirtual();
    AptValue *prototype;
    while(h && (prototype=h->mp__proto__)) 
    {
     if(prototype==context) break;
     h=prototype->GetNativeHashVirtual();
     
    }
    if(h && prototype) context=this;
    else context=(AptValue *)I->contexts.rva006DE160();
    return context;
    
   }
   case 3:
   if(!(unsigned char)B(context)->isCIH(false)) 
   {
    AptValue *root=((FindChildFunctionView *)I->currentFunction)->parentAnim;
    if(root && (unsigned char)B(root)->isCIH(false)) 
    {
     while(((FindChildCIHView *)root)->parent) root=((FindChildCIHView *)root)->parent;
     return root;
     
    }
    return (AptValue *)_AptGetAnimationAtLevel(0);
    
   }
   if((unsigned char)B(context)->isCIH(false)) 
   {
    AptValue *root=(AptValue *)B(context)->rva006DCF60(false);
    AptValue *parent=((FindChildCIHView *)root)->parent;
    while(parent) 
    {
     root=parent;
     parent=((FindChildCIHView *)root)->parent;
     
    }
    return root;
    
   }
   return 0;
   case 19: return GLOBAL;
   case 4: return g_shutdownAtE180B8;
   case 20: return g_shutdownAtE18068;
   case 5: return g_shutdownAtE18070;
   case 36: return g_shutdownAtE180AC;
   case 37: return g_shutdownAtE180BC;
   case 17: return (AptValue *)g_Rva01337A20;
   case 18: 
   {
    context=(AptValue *)I->contexts.rva006DE160();
    AptNativeHash *h=context->GetNativeHashVirtual();
    if(h && h->mp__proto__) 
    {
     AptValue *prototype=h->mp__proto__;
     if(context!=this && ((Rva006DC9E0 *)context)->rva006DC9E0() && !(unsigned char)B(context)->isCIH(false)) 
     {
      if((unsigned char)B(context)->isObject() && (((FindChildObjectView *)B(context)->rva006DD0E0())->flags&0x200)) 
      {
       h=prototype->GetNativeHashVirtual();
       if(h) prototype=h->mp__proto__;
       
      }
      return prototype;
      
     }
     if((unsigned char)B(context)->isPrototype()) return prototype;
     if((unsigned char)B(prototype)->isPrototype() && ((FindChildObjectView *)B(prototype)->rva006DD120())->flags) return prototype;
     h=prototype->GetNativeHashVirtual();
     if(h && h->mp__proto__) return h->mp__proto__;
     
    }
    return gpUndefinedValue;
    
   }
   case 16:
   if((unsigned char)B(context)->isCIH(false)) return ((FindChildCIHView *)B(context)->rva006DCF60(false))->parent;
   return 0;
   case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
   case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35:
   return (AptValue *)_AptGetAnimationAtLevel(atoi(name->rva00620090()+6));
   default: APT_ASSERT(0,"NOT_REACHED",0x51d);
   return 0;
   
  }
  
 }
 if(context->isUndefined()) return 0;
 AptNativeHash *hash=context->GetNativeHashVirtual();
 if(!hash && (unsigned char)B(context)->isCIH(false) && (unsigned char)B(context)->rva006DCF60(false)->rva006DCC60(false))
 hash=(AptNativeHash *)B(context)->rva006DCF60(false)->rva006E04A0();
 while(hash) 
 {
  AptValue *value=hash->Lookup(name);
  if(value) return value;
  if(!hash->mp__proto__) break;
  AptValue *prototype=hash->mp__proto__;
  hash=prototype->GetNativeHashVirtual();
  
 }
 AptValue *value=(AptValue *)((Rva0070A5C0 *)g_shutdownAtE18360)->rva0070A5C0((int)name);
 if(value) return value;
 return (AptValue *)((Rva0070A5C0 *)GLOBAL)->rva0070A5C0((int)name);
 
}
