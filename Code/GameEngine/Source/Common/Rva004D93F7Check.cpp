// cl: /DNDEBUG /MD /EHsc
// ?countsAsMoveIntoCamp@@YAEIPBUBfmePointFD@@@Z, retail 0x004D93F7, 92 bytes.
// Shroud-audio bounds check: TheAudio slot 0x134 bounds vs two
// Rva00739830 cell sums via TheShroudManager; unsigned char return.
// Evidence: TheAudio 0x00DFE6E8; TheShroudManager 0x00DFE74C precedent
// Rva000D1BEA; rowed rva00739830; sbb-inc unsigned char per §4.6;
// caller 0x004DA8C4.
extern class PartitionManager *TheShroudManager;

struct BfmePointFD;
struct AudioBounds
{
	char m_pad[0x44];
	unsigned int m_44;
	unsigned int m_48;
};
class AudioManager
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
	virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
	virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
	virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
	virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51();
	virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
	virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59();
	virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63();
	virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67();
	virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71();
	virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75();
	virtual void p76();
	virtual AudioBounds *slot134();
};
extern AudioManager *TheAudio;
class Rva00739830
{
public:
	int rva00739830(const BfmePointFD *pt, int a, unsigned int b) const;
};
#define TheShroudManager (*(Rva00739830 **)&TheShroudManager)
unsigned char __cdecl countsAsMoveIntoCamp(unsigned int a, const BfmePointFD *pt1, const BfmePointFD *pt2)
{
	AudioManager *audio = TheAudio;
	if (audio == 0)
		return 0;
	AudioBounds *b = audio->slot134();
	if (b == 0)
		return 0;
	if (TheShroudManager == 0)
		return 0;
	int x = TheShroudManager->rva00739830(pt1, 2, a);
	if (x > b->m_44)
		return 0;
	int y = TheShroudManager->rva00739830(pt2, 2, a);
	return (unsigned char)(y >= b->m_48);
}

// --- 0x004D9453 (76B, file-static): resolve enter message and attack-move predicate
// for voice response; callers 0x004DAB48 and 0x004DAF9A preload EAX/ESI out pointers and ECX context.
class Object;
class DrawableList;
class GameMessage
{
public:
	enum Type {};
};
class ActionManager
{
public:
	GameMessage::Type getEnterMessage(const Object *obj, const DrawableList *drawList);
};
extern ActionManager *TheActionManager;
bool Rva004D933BIs(int messageId);

struct Rva004D9453Inner
{
	char m_pad[0xFC];
	const Object *m_obj;
};

struct Rva004D9453Context
{
	int m_pad;
	Rva004D9453Inner *m_inner;
};

static __declspec(noinline) void rva004D9453(
	const DrawableList *drawList,
	int messageId,
	bool *out_bool,
	const Object **out_obj,
	GameMessage::Type *out_enterMessage,
	const Rva004D9453Context *ctx)
{
	*out_obj = 0;
	if (ctx && ctx->m_inner)
		*out_obj = ctx->m_inner->m_obj;

	*out_enterMessage = (GameMessage::Type)-1;
	if (*out_obj && messageId == 0x42c)
		*out_enterMessage = TheActionManager->getEnterMessage(*out_obj, drawList);

	*out_bool = Rva004D933BIs(messageId);
}

// ?rva004D9453Caller absent-from-retail
void rva004D9453Caller(
	const DrawableList *drawList,
	int messageId,
	bool *out_bool,
	const Object **out_obj,
	GameMessage::Type *out_enterMessage,
	const Rva004D9453Context *ctx)
{
	rva004D9453(drawList, messageId, out_bool, out_obj, out_enterMessage, ctx);
}
