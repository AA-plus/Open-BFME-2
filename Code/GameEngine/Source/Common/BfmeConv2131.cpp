void __cdecl operator delete(void *p);

class BfmeThingCDE;

class BfmeSubABI
{
public:
	virtual void bfmeSlot0ABI();
	virtual void bfmeSlot1ABI();
	virtual void bfmeSlot2ABI();
	virtual void bfmeSlot3ABI();
	virtual BfmeThingCDE *bfmeGetABI();
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();

	void *m_bfme00ABI;
	void *m_bfme04ABI;
};

class ShroudManager
{
public:
	class Data
	{
	public:
		bool KeepAsGhost();
	};
};

void __stdcall bfmeReleaseABI(void *owner);

void __stdcall bfmeReleaseABI(void *owner)
{
	if (owner == 0)
		return;

	if (((BfmeSubABI *)((char *)owner + *(int *)(*(char **)((char *)owner + 4) + 4) + 4))->bfmeGetABI() == 0)
		return;

	BfmeThingCDE *t = ((BfmeSubABI *)((char *)owner + *(int *)(*(char **)((char *)owner + 4) + 4) + 4))->bfmeGetABI();

	if (t->m_bfme04ABI != owner)
		return;

	if (((ShroudManager::Data *)t)->KeepAsGhost())
		return;

	t->bfmeDtorCDE();
	::operator delete(t);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeOneCDE@BfmeOwnerCDE@@QAEXPAX@Z=?bfmeReleaseABI@@YGXPAX@Z")
