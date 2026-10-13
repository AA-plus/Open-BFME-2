// cl: /DNDEBUG /MD
// ?rva0049D3BC@Rva0049D3BC@@QAEXXZ retail 0x0049D3BC 362B
// Expiry sweep over 4 entries at +0x3C with timeouts from +0x04 data (+0xC/+0x10/+0x14)
// and Disability-style bit tables at 0x00C51304/0x00C51314/0x00C51324 driving
// +0x7C set and +0xC8 clear/set plus +0x114 dirty flag. Evidence: TheGameLogic
// frame at +0x40, thresholds, bit-array shape, sibling +0x114 flag in Rva0049D526.
class GameLogic
{
public:
	int m_pad[0x40 / 4];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

struct Rva0049D3BCData
{
	char _pad[0x0C];
	unsigned int m_0C;
	unsigned int m_10;
	unsigned int m_14;
};

struct Rva0049D3BCEntry
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned char m_flag;
	char _pad[3];
};

// ProductionDoorOpeningFlags: matched references place it at VA 0xc51304; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned int ProductionDoorOpeningFlags[4] = {
	21, 25, 29, 33,
};
// ProductionDoorClosingFlags: matched references place it at VA 0xc51314; retail contents, sized to the
// 0x10-byte gap before the next known global there.
unsigned int ProductionDoorClosingFlags[4] = {
	22, 26, 30, 34,
};
// ProductionDoorWaitingOpenFlags: the third of the three consecutive 16-byte bit-index tables at
// VA 0xc51304 / 0xc51314 / 0xc51324 (RVA 0x00851324, .rdata, file offset
// 0x00850724): 17 1b 1f 23. The two siblings hold 20..32 in steps of five; this
// one continues the run, and the strings that follow it (HeroRevive,
// HeroPurchase, TimeMultiplier, CostMultiplier, ModifierFilter) are a separate
// record block, so the object the rowed body indexes is these four words.
extern unsigned int ProductionDoorWaitingOpenFlags[];
unsigned int ProductionDoorWaitingOpenFlags[4] = {
	0x17, 0x1b, 0x1f, 0x23,
};

class Rva0049D3BC
{
public:
	void rva0049D3BC();

private:
	const void *m_vtable;
	Rva0049D3BCData *m_data;
	char _pad08[0x3C - 0x08];
	Rva0049D3BCEntry m_entries[4];
	unsigned int m_7C[19];
	unsigned int m_C8[19];
	unsigned char m_114;
};

void Rva0049D3BC::rva0049D3BC()
{
	Rva0049D3BCData *data = m_data;
	unsigned int cur = TheGameLogic->m_40;
	for (int i = 0; i < 4; ++i)
	{
		if (m_entries[i].m_00 != 0)
		{
			if (cur - m_entries[i].m_00 > data->m_0C)
			{
				m_entries[i].m_00 = 0;
				m_entries[i].m_04 = cur;
				m_7C[ProductionDoorOpeningFlags[i] >> 5] |= (1u << (ProductionDoorOpeningFlags[i] & 31));
				m_C8[ProductionDoorOpeningFlags[i] >> 5] &= ~(1u << (ProductionDoorOpeningFlags[i] & 31));
				m_C8[ProductionDoorWaitingOpenFlags[i] >> 5] |= (1u << (ProductionDoorWaitingOpenFlags[i] & 31));
				m_114 = 1;
			}
		}
		else if (m_entries[i].m_04 != 0)
		{
			if (cur - m_entries[i].m_04 > data->m_10 && m_entries[i].m_flag == 0)
			{
				m_entries[i].m_04 = 0;
				m_entries[i].m_08 = cur;
				m_7C[ProductionDoorWaitingOpenFlags[i] >> 5] |= (1u << (ProductionDoorWaitingOpenFlags[i] & 31));
				m_C8[ProductionDoorWaitingOpenFlags[i] >> 5] &= ~(1u << (ProductionDoorWaitingOpenFlags[i] & 31));
				m_C8[ProductionDoorClosingFlags[i] >> 5] |= (1u << (ProductionDoorClosingFlags[i] & 31));
				m_114 = 1;
			}
		}
		else if (m_entries[i].m_08 != 0)
		{
			if (m_entries[i].m_flag == 0 && cur - m_entries[i].m_08 > data->m_14)
			{
				m_entries[i].m_08 = 0;
				m_7C[ProductionDoorClosingFlags[i] >> 5] |= (1u << (ProductionDoorClosingFlags[i] & 31));
				m_C8[ProductionDoorClosingFlags[i] >> 5] &= ~(1u << (ProductionDoorClosingFlags[i] & 31));
				m_114 = 1;
			}
		}
	}
}
