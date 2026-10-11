// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b6520.md plus retail only. No decoder source was consulted.
// InitPostProcessing, retail RVA 0x001B6520 (193 bytes).
// Retail RVA 0x009A5AA0, 193 bytes.  Rva009A4D00Init (0x009A4D00) calls it
// directly as cdecl with three table pointers (all its 64-entry int table
// 0x0134C6D8) and the tier constant 7.  The body builds the saturating clamp
// table read by the loop filters, publishes the three table pointers, copies
// the 64-entry source table, picks the tier's pair of tables and runs the CPU
// dispatch installer.

// Retail passes the tier on the stack although the installer's landed body
// (0x009B0D60) never reads an argument, so the call goes through a typed cast
// of its ledger name.
extern void __cdecl bfmeInstallCpuDispatchTable(void);
typedef void (__cdecl *Rva009A5AA0TierInstaller)(int);

extern const unsigned char g_bfmeClampTable[];	// retail 0x01356FE0 (zero point)
extern const unsigned int *g_rva01356AA0;
// g_rva01356AA0: matched references place it at VA 0xe22cf0 (zero-filled .bss).
const unsigned int * g_rva01356AA0;
extern const unsigned int *g_rva01356A98;
// g_rva01356A98: matched references place it at VA 0xe22ce8 (zero-filled .bss).
const unsigned int * g_rva01356A98;
extern const void *g_rva01356A88;
// g_rva01356A88: matched references place it at VA 0xe22ce4 (zero-filled .bss).
const void * g_rva01356A88;
// g_rva01356940: matched references place it at VA 0xe22be0 (zero-filled).
int g_rva01356940[64] = { 0 };
unsigned short *Rva009C0D10Src;			// .bss VA 0x00E22CE0 (BFME1 0x01356A7C); set here
extern int *g_rva01356A9C;

// g_rva012D7C58: matched references place it at VA 0xdb7528 (retail .data contents).
unsigned short g_rva012D7C58[128] = {
	0x1eu, 0u, 0x19u, 0u, 0x14u, 0u, 0x14u, 0u,
	0xfu, 0u, 0xfu, 0u, 0xeu, 0u, 0xeu, 0u,
	0xdu, 0u, 0xdu, 0u, 0xcu, 0u, 0xcu, 0u,
	0xbu, 0u, 0xbu, 0u, 0xau, 0u, 0xau, 0u,
	9u, 0u, 9u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 3u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	2u, 0u, 2u, 0u, 2u, 0u, 2u, 0u,
	1u, 0u, 1u, 0u, 1u, 0u, 1u, 0u,
	1u, 0u, 1u, 0u, 1u, 0u, 1u, 0u,
};
// g_rva012D7D58: matched references place it at VA 0xdb7628 (retail .data contents).
unsigned short g_rva012D7D58[128] = {
	0xeu, 0u, 0xeu, 0u, 0xdu, 0u, 0xdu, 0u,
	0xcu, 0u, 0xcu, 0u, 0xau, 0u, 0xau, 0u,
	0xau, 0u, 0xau, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	7u, 0u, 7u, 0u, 6u, 0u, 6u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 3u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 2u, 0u,
};
// g_rva012D7E58: matched references place it at VA 0xdb7728 (retail .data contents).
unsigned short g_rva012D7E58[128] = {
	0xeu, 0u, 0xeu, 0u, 0xdu, 0u, 0xdu, 0u,
	0xcu, 0u, 0xcu, 0u, 0xau, 0u, 0xau, 0u,
	0xau, 0u, 0xau, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	8u, 0u, 8u, 0u, 8u, 0u, 8u, 0u,
	7u, 0u, 7u, 0u, 7u, 0u, 7u, 0u,
	7u, 0u, 7u, 0u, 6u, 0u, 6u, 0u,
	6u, 0u, 6u, 0u, 6u, 0u, 6u, 0u,
	5u, 0u, 5u, 0u, 5u, 0u, 5u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 4u, 0u,
	4u, 0u, 4u, 0u, 4u, 0u, 3u, 0u,
	3u, 0u, 3u, 0u, 3u, 0u, 2u, 0u,
};
// g_rva012D7858: matched references place it at VA 0xdb7128 (retail .data contents).
int g_rva012D7858[64] = {
	0x1e, 0x19, 0x14, 0x14, 0xf, 0xf, 0xe, 0xe,
	0xd, 0xd, 0xc, 0xc, 0xb, 0xb, 0xa, 0xa,
	9, 9, 8, 8, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	4, 4, 4, 4, 3, 3, 3, 3,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
};
// g_rva012D7958: matched references place it at VA 0xdb7228 (retail .data contents).
int g_rva012D7958[64] = {
	0xf, 0xf, 0xf, 0xf, 0xa, 0xa, 0xa, 0xa,
	0xa, 0xa, 0xa, 0xa, 0xa, 9, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 7, 7, 7, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	5, 4, 4, 4, 4, 4, 4, 3,
	3, 3, 3, 3, 3, 2, 2, 2,
	2, 2, 1, 1, 1, 0, 0, 0,
};
// g_rva012D7A58: matched references place it at VA 0xdb7328 (retail .data contents).
int g_rva012D7A58[64] = {
	0xf, 0xf, 0xf, 0xf, 0xa, 0xa, 0xa, 0xa,
	0xa, 0xa, 0xa, 0xa, 0xa, 9, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 7, 7, 7, 7, 7, 7, 7,
	6, 6, 6, 6, 5, 5, 5, 5,
	5, 4, 4, 4, 4, 4, 4, 3,
	3, 3, 3, 3, 3, 2, 2, 2,
	2, 2, 1, 1, 1, 0, 0, 0,
};

extern "C" void __cdecl InitPostProcessing(void *firstTable, void *secondTable, void *sourceTable, int tier)
{
	unsigned char *clamp = (unsigned char *)g_bfmeClampTable;
	int i;
	for (i = -256; i < 512; ++i)
	{
		int value;
		if (i < 0)
			value = 0;
		else
		{
			value = i;
			if (value > 255)
				value = 255;
		}
		clamp[i] = (unsigned char)value;
	}

	g_rva01356AA0 = (const unsigned int *)firstTable;
	g_rva01356A98 = (const unsigned int *)secondTable;
	g_rva01356A88 = sourceTable;
	for (i = 0; i < 64; ++i)
		g_rva01356940[i] = ((const int *)sourceTable)[i];

	if ((unsigned)tier >= 6)
	{
		Rva009C0D10Src = g_rva012D7E58;
		g_rva01356A9C = g_rva012D7A58;
	}
	else if ((unsigned)tier >= 5)
	{
		Rva009C0D10Src = g_rva012D7D58;
		g_rva01356A9C = g_rva012D7958;
	}
	else
	{
		Rva009C0D10Src = g_rva012D7C58;
		g_rva01356A9C = g_rva012D7858;
	}
	((Rva009A5AA0TierInstaller)bfmeInstallCpuDispatchTable)(tier);
}

