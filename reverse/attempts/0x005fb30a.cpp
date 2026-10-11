// ??0Rva005FB30A@@QAE@IIPAX@Z
// partial score=0.9 date=2026-10-11
// Remaining: register/stack allocation. Retail keeps the battle in ebx, spills
// the two keys (one into the dead first-argument slot) and uses edi for the
// loop record; this source keeps a key in edi (200 vs 207 bytes). Local
// order, record scope/type, and counter placement variants did not change it.
// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva005FB30A@@QAE@IIPAX@Z, retail 0x005FB30A..0x005FB3D9 (207 bytes,
// EH): a battle prompt list constructor (constructed by 0x005E97D5). Over
// the rowed Rva006003FC base (its three arguments) and table 0x00C79EF0 it
// resets the +8 list (rowed 0x005FFED5(1)), then for every record the
// battle (+0x14) reports for its two keys (+0x18, +0x1C; count 0x003F4DCA,
// record 0x003F48FE) it clones a Rva005FB22B prompt (rowed factory
// 0x005FB29A) and hands it to the list: records without a name go through
// 0x005FFEDD, the rest through 0x005FFEE5. Identities are not established.
#include "BattlePromptCallbackPayloadView.h"

template <class T> class StringBase
{
public:
	bool isEmpty() const;
};

class Rva005FB22B;
RvaCloneResult<Rva005FB22B> Rva005FB29ACreate(const void *arg);

class LivingWorldBattle
{
public:
	int rva003F48FE(int a, int b, int index);
};

class Rva003F4DCA
{
public:
	int rva003F4DCA(int a, int b);
};

class Rva005FFED5 { public: void rva005FFED5(int value); };
class Rva005FFEDD { public: void rva005FFEDD(const TreeHintRef00217D4C &prompt); };
class Rva005FFEE5 { public: int rva005FFEE5(const TreeHintRef00217D4C &prompt); };

class Rva006003FC
{
public:
	Rva006003FC(void *a, void *b, void *c);
	virtual ~Rva006003FC();
protected:
	int m_04;
	unsigned char m_list08[0xC];			// +0x08
	LivingWorldBattle *m_battle;			// +0x14
	int m_key18;					// +0x18
	int m_key1C;					// +0x1C
};

class Rva005FB30A : public Rva006003FC
{
public:
	Rva005FB30A(unsigned int a, unsigned int b, void *c);
	virtual ~Rva005FB30A();
};

Rva005FB30A::Rva005FB30A(unsigned int a, unsigned int b, void *c)
	: Rva006003FC((void *)a, (void *)b, c)
{
	((Rva005FFED5 *)m_list08)->rva005FFED5(1);
	int key1C = m_key1C;
	int key18 = m_key18;
	LivingWorldBattle *battle = m_battle;
	int count = ((Rva003F4DCA *)battle)->rva003F4DCA(key18, key1C);
	for (int i = 0; i < count; ++i)
	{
		int record = battle->rva003F48FE(key18, key1C, i);
		RvaCloneResult<Rva005FB22B> prompt = Rva005FB29ACreate(&record);
		if (((const StringBase<char> *)(record + 0x18))->isEmpty())
			((Rva005FFEDD *)m_list08)->rva005FFEDD(prompt);
		else
			((Rva005FFEE5 *)m_list08)->rva005FFEE5(prompt);
	}
}
