// WotR player member ownership, 2026-10-12. Target table C04948 and its
// LWPlayerDef literal establish Snapshot identity independently of the bank.
// Default2E0EF7/copy2E0A0A/dtor2E0F1E and xfer52BA0A establish the 0x28-byte
// physical contract: wide handle04, narrow08/0C/10/14, ints18/1C/20, flag24.
// Legacy address-named views retain existing callers while emitting the same
// complete four-slot table. Every added fold has whole-body/relocation proof;
// no unique-byte credit for member aliases. See attempt_evidence/player-owners.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// ??1Rva002E0F1E@@UAE@XZ @0x002E0F1E 99B Snapshot-derived dtor with five StringBase members.
// Wide at +4 via 0x00036E70 then four narrow at +8 +0xC +0x10 +0x14 via 0x00036410 in reverse with EH states 4 to 0 then base vtable 0x00BBB554.
// Evidence: caller 0x002E18A7 is 28B deleting dtor plus sibling ??1EventParameter@@UAE@XZ same Snapshot base plus prev 0x002E0E7C next 0x002E1001 same dir.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

#include "Common/Snapshot.h"
// bfme link decl-only begin
template <> StringBase<char>::~StringBase();
// bfme link decl-only end
class __declspec(novtable) Rva002E0F1E : public Snapshot
{
public:
	virtual ~Rva002E0F1E();
private:
	StringBase<unsigned short> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0c;
	StringBase<char> m_10;
	StringBase<char> m_14;
 int m_18,m_1c,m_20;bool m_24;
};
Rva002E0F1E::~Rva002E0F1E()
{
}

class __declspec(novtable) LWPlayerDef : public Snapshot
{
public:
	virtual ~LWPlayerDef();
private:
	StringBase<unsigned short> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0c;
	StringBase<char> m_10;
	StringBase<char> m_14;
 int m_18,m_1c,m_20;bool m_24;
};
LWPlayerDef::~LWPlayerDef()
{
}

class __declspec(novtable) Rva002E0EF7 : public Snapshot
{
public:
	virtual ~Rva002E0EF7();
private:
	StringBase<unsigned short> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0c;
	StringBase<char> m_10;
	StringBase<char> m_14;
 int m_18,m_1c,m_20;bool m_24;
};
Rva002E0EF7::~Rva002E0EF7()
{
}

class __declspec(novtable) Rva002E0A0A : public Snapshot
{
public:
	virtual ~Rva002E0A0A();
private:
	StringBase<unsigned short> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0c;
	StringBase<char> m_10;
	StringBase<char> m_14;
 int m_18,m_1c,m_20;bool m_24;
};
Rva002E0A0A::~Rva002E0A0A()
{
}
