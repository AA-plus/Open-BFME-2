// ?rva00564EC0@LivingWorldCampaignAct@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Native 0x00564EC0..0x00565085, 453 bytes. WB1439A90 and caller56696F
// establish the act's stride-0x28 entries and conditional region orders.
// This address-owned method's original name is unknown.
// Getter calls bind existing folded physical owners; their class names do not
// identify campaign entry types. The AptCampaignReview binding is the existing
// empty RET12 provider shared with both WB SetRegionForcedBattle overloads.
// Its three pointer words are unused in retail; temporary lifetimes remain
// scoped to the full expression, including the empty pair destructor.
// A named vector-base local preserves native index/base load scheduling.
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct BfmePairWI
{
    BfmePairWI() {}
    BfmePairWI(const BfmePairWI &o) : m_f(o.m_f), m_i(o.m_i) {}
    ~BfmePairWI() {}
    float m_f;
    int m_i;
};


class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };
class Anim2DTemplate { public: AsciiString getName() const; };
class Rva00564E0D { public: AsciiString rva00564E0D(); };
class CDDrive { public: virtual AsciiString getDiskName(); };
class Rva00564BF6 { public: BfmePairWI rva00564BF6(); };
class AsciiStringWI;
class Rva002B8767 { public: void rva002B8767(BfmePairWI,const AsciiStringWI&,bool,const AsciiStringWI&); };
class Rva002B778A { public: void rva002B778A(const AsciiString&); };
class GameWindow;
class AptCampaignReview { public: void rva000D1407(const char*,void*,GameWindow*); };

// One 0x28-byte entry of the act's +0x14 list.
class LivingWorldCampaignActEntry
{
public:

	unsigned char m_pad00[0x1c];
	Bool getFlag1C() const { return m_1c; }
	Bool getFlag1D() const { return m_1d; }
	Bool m_1c;				// +0x1C
	Bool m_1d;				// +0x1D
	unsigned char m_pad1e[2];
	unsigned char m_20[8];			// +0x20
};

struct CampaignActLogicView
{
    unsigned char m_pad00[0xb0];
    void *getB0() const { return m_b0; }
    void *m_b0;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

template <class T> class ActVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { T *base=m_start; return *(base+i); }
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

class LivingWorldCampaignAct
{
public:
	void rva00564EC0();
private:
	unsigned char m_pad00[0x14];
	ActVectorView<LivingWorldCampaignActEntry> m_entries;	// +0x14
};

void LivingWorldCampaignAct::rva00564EC0()
{
	if (((CampaignActLogicView*)TheLivingWorldLogic)->getB0() == 0)
		return;
	for (UnsignedInt i = 0; i < m_entries.size(); ++i)
	{
		LivingWorldCampaignActEntry &entry = m_entries[i];
		if (((CDDrive*)&entry)->CDDrive::getDiskName().getLength() != 0)
		{
			if (entry.getFlag1D())
				((Rva002B778A*)TheLivingWorldLogic)->rva002B778A(((const Anim2DTemplate*)&entry)->getName());
			else
				((Rva002B8767*)TheLivingWorldLogic)->rva002B8767(
					((Rva00564BF6*)&entry)->rva00564BF6(),
					(const AsciiStringWI&)((CDDrive*)&entry)->CDDrive::getDiskName(),
					entry.getFlag1C(),
					(const AsciiStringWI&)((const Anim2DTemplate*)&entry)->getName());
		}
		else if (((const Rva00564DF2NameView*)&entry)->rva00564DF2().getLength() != 0)
		{
			((AptCampaignReview*)TheLivingWorldLogic)->rva000D1407(
				(const char*)&(const AsciiString&)((const Rva00564DF2NameView*)&entry)->rva00564DF2(),
				(void*)&(const AsciiString&)((Rva00564E0D*)&entry)->rva00564E0D(),
				(GameWindow*)entry.m_20);
		}
		else
		{
			((AptCampaignReview*)TheLivingWorldLogic)->rva000D1407(
				(const char*)&(const BfmePairWI&)((Rva00564BF6*)&entry)->rva00564BF6(),
				(void*)&(const AsciiString&)((Rva00564E0D*)&entry)->rva00564E0D(),
				(GameWindow*)entry.m_20);
		}
	}
}
