// ?rva002B5A5F@LivingWorldLogic@@QAE_NPAUParent00575E4E@@@Z
// partial score=0.85 date=2026-10-11
// ?rva002B5A5F@LivingWorldLogic@@QAE_NPAUParent00575E4E@@@Z @0x002B5A5F 152B
// Append to Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp
// (CRLF file; LivingWorldLogic, Rva002B254F, Rva003B8BAA and TheCampaignManager
// are declared there). Corrected flow; register-save sinking wall remains.

// Retail 0x002B5A5F, 152 bytes (RET 4; callers 0x002B5AF7, 0x0057548A and
// 0x00576323): whether the local player may act on the given campaign item.
// It needs a local player and 0x002B59FF; when 0x002B254F holds, the
// campaign manager's object (0x003B8BAA) must accept the item through its
// slot 1; the item must be active (+0x58) and pass 0x00318D05 for the local
// player's +0x14 id; then outside turn phase 0 a named item is accepted
// only in phase 4 when 0x002B4BC9 agrees. Address-derived names.
class Rva002B59FF { public: Bool rva002B59FF(); };				// 0x002B59FF
class Rva00318D05 { public: Bool rva00318D05(Int playerID); };	// 0x00318D05
struct Rva002B4BC9Arg;
class Rva002B4BC9 { public: Bool rva002B4BC9(Rva002B4BC9Arg *arg); };	// 0x002B4BC9
class Rva002B5A5FCampaignVet
{
public:
	virtual void slot00();
	virtual Bool vet(Parent00575E4E *item);		// +0x04
};
struct Rva002B5A5FItem
{
	unsigned char m_pad00[0x18];
	AsciiString m_name;				// +0x18
	unsigned char m_pad1C[0x58 - 0x1c];
	Bool m_active;					// +0x58
};
struct Rva002B5A5FPlayer
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
};

Bool LivingWorldLogic::rva002B5A5F(Parent00575E4E *parent)
{
	if (!m_localPlayer || !((Rva002B59FF *)this)->rva002B59FF())
		return false;
	Rva002B5A5FItem *item = (Rva002B5A5FItem *)parent;
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		if (!((Rva002B5A5FCampaignVet *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->vet(parent))
			return false;
	}
	if (!item->m_active)
		return false;
	if (!((Rva00318D05 *)parent)->rva00318D05(((Rva002B5A5FPlayer *)m_localPlayer)->m_id))
		return false;
	if (!item->m_active)
		return false;
	Int phase = m_turnPhase;
	if (phase == 0)
		return true;
	if (item->m_name.isEmpty())
		return false;
	if (phase != 4)
		return false;
	if (((Rva002B4BC9 *)this)->rva002B4BC9((Rva002B4BC9Arg *)parent))
		return true;
	return false;
}
