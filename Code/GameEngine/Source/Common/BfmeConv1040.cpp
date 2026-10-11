// BFME1 byte-identical donor: reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv1040.cpp
// Trimmed to the bodies that reproduce game.dat bytes. The file's other members
// (bfmeGo1040A/C/F/K) are BFME1-only shapes with no matching body here, so they
// stay out and every defined function has a ledger row.

struct BfmeS1040
{
	int m_bfmeIdx;
	void *m_bfmeNext;
	char m_bfmePad[0x30];
	void *m_bfmeCur;
	void *m_bfmeTab[1];
	unsigned char m_bfmePad2[0x101];
	unsigned char m_bfmeData[0x3f];
	unsigned short *m_bfmeDestA;
	unsigned short *m_bfmeDestB;
};

extern void (__cdecl *g_bfmeHook1040)(BfmeS1040 *s);

// Tables A/B were static-initialized pointers to BFME1 VAs (0x01141708/
// 0x01141808) in the donor; retail reads BFME2 tables (A at 0xBD7860) via
// direct absolute access. As extern arrays the accesses emit DIR32 slots
// the pipeline patches, same as tables C/D below (retail 0x01141D08/C at
// 0xBD7E60 in BFME2; D follows the same pattern).
extern const unsigned short g_bfmeApplyTableA[];
extern const unsigned short g_bfmeApplyTableB[];
extern const unsigned short g_bfmeApplyTableC[]; // retail 0x01141D08
extern const unsigned short g_bfmeApplyTableD[]; // retail 0x01141D88

void bfmeApply1040(BfmeS1040 *s, int)
{
	unsigned char *p = s->m_bfmeData + 1;
	int count = 0x15;

	do
	{
		s->m_bfmeDestA[p[-1]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestA[p[0]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestA[p[1]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_bfmeDestA[0] = g_bfmeApplyTableC[s->m_bfmeIdx] << 2;

	p = s->m_bfmeData + 1;
	count = 0x15;

	do
	{
		s->m_bfmeDestB[p[-1]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestB[p[0]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestB[p[1]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_bfmeDestB[0] = g_bfmeApplyTableD[s->m_bfmeIdx] << 2;
}

