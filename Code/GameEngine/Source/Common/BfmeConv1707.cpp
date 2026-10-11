// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1707.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeShutdownFY@BfmeOwnerFY@@QAEXXZ 0x004CF8D5 (49B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// LINK: the slot's close is rowed as Connection::doSend(bool); the flag word is
// passed the same way, so the call keeps its void/int shape through a cast.
class BfmeSlotFY;
class Connection
{
public:
	unsigned int doSend(bool flag);
};
typedef void (Connection::*BfmeCloseFYShape)(int);

// The native 0x004CF900 call reaches Transport::doSend. The outer owner
// remains address-derived; this field now uses the actual recovered provider.
#include "../../Include/GameNetwork/Transport.h"

class BfmeOwnerFY
{
public:
	void bfmeShutdownFY(void);

	unsigned char m_bfmeHeadFY[4];
	BfmeSlotFY *m_bfmeSlotsFY[8];
	unsigned char m_bfmeMidFY[0x12000];
	Transport *m_bfmeExtraFY;
};

void BfmeOwnerFY::bfmeShutdownFY(void)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_bfmeSlotsFY[i] != 0)
			(((Connection *)m_bfmeSlotsFY[i])->*reinterpret_cast<BfmeCloseFYShape>(&Connection::doSend))(0);
	}

	if (m_bfmeExtraFY != 0)
		m_bfmeExtraFY->doSend();
}
