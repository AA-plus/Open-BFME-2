// ?rva003593E8@Rva003593E8@@QAE_NABVAsciiString@@_N@Z
// partial score=0.8564 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003593E8@Rva003593E8@@QAE_NABVAsciiString@@_N@Z @0x003593E8 366B evidence: chain from 0x00358ACB; TheGameLogic isGamePaused plus TheInGameUI 0x15 0x16 plus vtable 0x17c gates; lower then upper map finds at +0xc +0x18 via rowed 0x1F8437; virtuals +4 +8 +0xc plus audio 0x358A53 0x358ACB
#include <map>
#include <stdlib.h>

#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiMap;

class GameLogic
{
public:
	unsigned char isGamePaused();
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual bool s95();
	char m_pad[0x11];
	unsigned char m_15;
	unsigned char m_16;
};

extern InGameUI *TheInGameUI;

class Entry
{
public:
	virtual ~Entry();
	virtual bool f1(bool v);
	virtual bool f2(bool v);
	virtual bool f3(bool v);
};

class HotKeyManager { public: void rva00358A53(); void rva00358ACB(); };

class Rva003593E8
{
public:
	bool rva003593E8(const AsciiString &key, bool val);
private:
	char m_00[12];
	AsciiMap m_0c;
	AsciiMap m_18;
};

static __forceinline Entry *lookupAction(AsciiMap &map, const AsciiString &key)
{
 AsciiMap::iterator i = map.find(key);
 if (i == map.end()) return 0;
 return *(Entry **)&i->second;
}

// Control flow follows WB1132020: two case-normalized lookups, then dispatch.
bool Rva003593E8::rva003593E8(const AsciiString &key, bool val)
{
 if (TheGameLogic->isGamePaused() || TheInGameUI->m_15 == 0 || TheInGameUI->m_16 == 0 || TheInGameUI->s95()) return false;
 AsciiString tmp(key);
 tmp.toLower();
 bool ready = false;
 bool disabled = false;
 Entry *entry = 0;
 entry = lookupAction(m_0c, tmp);
 if (!entry) {
  entry = lookupAction(m_18, tmp);
 }
 if (entry && !entry->f1(val)) {
  if (entry->f2(val)) ready = true;
  else disabled = true;
 }
 if (!ready) {
  tmp.toUpper();
  entry = lookupAction(m_0c, tmp);
  if (!entry) {
   entry = lookupAction(m_18, tmp);
  }
  if (entry && !entry->f1(val)) {
   if (entry->f2(val)) ready = true;
   else disabled = true;
  }
 }
 if (ready) {
  if (entry->f3(val)) ((HotKeyManager *)this)->rva00358A53();
  return true;
 }
 if (disabled) ((HotKeyManager *)this)->rva00358ACB();
 return false;
}
