// cl: /MD
// TheGameLogic is the global at 0x00DFE78C; the banked attempt read it
// through a literal-address macro, which changed the load order.
// ?getRemainingFrames@OCLUpdate@@QBEIXZ, retail 0x0049B303, 13 bytes.
// Frame delta: m_20 minus TheGameLogic frame at +0x40 via global 0x00DFE78C.
// Identity (donor, Zero Hour OCLUpdate::getRemainingFrames): the next
// creation frame minus the logic frame; ControlBar::updateContextOCLTimer
// (0x0053E2B6) calls it on the object's OCLUpdate module.
// Evidence: caller 0x0053E310; prev ModuleNameGetters next OCLUpdatePoolKey; same TheGameLogic shape as ObjectRva002900E0.
class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame;
};

extern GameLogic *TheGameLogic;
class OCLUpdate
{
public:
	unsigned int getRemainingFrames() const;
private:
	char m_pad[0x20];
	int m_20;
};

unsigned int OCLUpdate::getRemainingFrames() const
{
	int t = m_20;
	GameLogic *g = TheGameLogic;
	return t - g->m_frame;
}
