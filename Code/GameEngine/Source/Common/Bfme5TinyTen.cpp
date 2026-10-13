// A destructor that unhooks itself from a global head.
//
// Trimmed from the Open-BFME-1 Bfme5TinyTen.cpp donor (their retail 0x004902A0,
// same 23 bytes): the file's other two bodies (bfmeIsClear, bfmeBit) have no
// unique placement in game.dat, so only this one is claimed here.
//
// game.dat keeps the list head at 0x00E01E1C (BFME1: 0x012F3350), read from the
// two DIR32 slots of the retail body.

class ProgressIndicator
{
public:
	ProgressIndicator(void);
	virtual ~ProgressIndicator(void);				// slot +0x00

	ProgressIndicator *m_bfmeNext;				// +0x04
};

// Descriptive name: retail's original global name is unknown. The constructor
// links this node at the head; the destructor removes it when it is the head.
ProgressIndicator *BfmeProgressIndicatorHead = 0;

ProgressIndicator::ProgressIndicator(void)
{
	m_bfmeNext = BfmeProgressIndicatorHead;
	BfmeProgressIndicatorHead = this;
}

// ??1ProgressIndicator@@UAE@XZ
ProgressIndicator::~ProgressIndicator(void)
{
	if (BfmeProgressIndicatorHead == this)
		BfmeProgressIndicatorHead = m_bfmeNext;
}
