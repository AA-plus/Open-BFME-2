// Native callback 0x006DDCE0..0x006DDDDF (255 bytes), registered by
// _constructBuiltInObjects. Target calls establish a two-argument native
// callback using the shared interpreter stack and a lazily allocated hash.
// The key string is checked through the existing predicates; undefined
// values erase a key, others assign it. The callback purpose/name is unknown.
class AptValue;
class EAStringC;
class BfmeAptValue006DCD20 {
public:
 virtual void slot0();
 struct { unsigned int low : 4; unsigned int defined : 1; unsigned int rest : 27; } flags;
 int isString() const;
 bool isUndefined() const;
 int rva006DBFA0() const;
 BfmeAptValue006DCD20 *checkedString();
};
class AptBasePtrStack {
public:
 BfmeAptValue006DCD20 *At(int);
 int count, capacity;
 BfmeAptValue006DCD20 **elements;
};
struct AptActionInterpreter { AptBasePtrStack stack; };
extern AptActionInterpreter g_aptDateInterpreter;
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270 { public: void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
struct AptNativeHash {
 AptNativeHash(int);
 void Unset(const EAStringC *const);
 void Set(const EAStringC *const, AptValue *const);
 static void *operator new(unsigned n) {return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n);}
 static void operator delete(void *p,unsigned n) {g_pChainBlockAllocator->freeBlock(p,n);}
 int count; void *entries; AptValue *proto, *prototype; unsigned events;
};
extern AptNativeHash *g_bfmeAptHashAtE180E4;
class AptBoolean {public: static AptValue *Create(bool);};
AptValue *Rva006DDCE0(AptValue *,int argc)
{
 if (argc != 2) return AptBoolean::Create(false);
 {
  BfmeAptValue006DCD20 *key = g_aptDateInterpreter.stack.At(0);
  if ((unsigned char)key->flags.defined) {
   if ((unsigned char)key->isString()) {
    BfmeAptValue006DCD20 *value = g_aptDateInterpreter.stack.At(1);
    if (!key->isUndefined()) {
     if (!g_bfmeAptHashAtE180E4) g_bfmeAptHashAtE180E4 = new AptNativeHash(8);
     if ((unsigned char)value->rva006DBFA0()) {
      g_bfmeAptHashAtE180E4->Unset((const EAStringC *)((char *)key->checkedString()+8));
      return AptBoolean::Create(true);
     } else {
      BfmeAptValue006DCD20 *str = key->checkedString();
      g_bfmeAptHashAtE180E4->Set((const EAStringC *)((char *)str+8),(AptValue *)value);
      return AptBoolean::Create(true);
     }
    }
   }
  }
 }
 return AptBoolean::Create(false);
}
