// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8ac0.md plus retail only. No
// decoder source was consulted.
//
// Dering threshold table initialiser (retail 0x001D8AC0). Sets the cut-off
// field (+0x4538) to 64 and fills the 256-entry table at +0x453C from the top
// downwards: a linear ramp (6 * cutoff - 5 * written) / cutoff for the first
// cut-off entries, then one for the rest down to index 1. Index 0 is not written.

// RVA 0x001D8AC0
extern "C" void __cdecl InitLoopDeringThresholds(void *context)
{
	unsigned char *base = (unsigned char *)context;
	unsigned int index = 0;
	*(int *)(base + 0x4538) = 0x40;
	unsigned int offset = 0;
	volatile int *write = (volatile int *)(base + 0x4938);

	while (index < *(int *)(base + 0x4538))
	{
		unsigned int count = *(unsigned int *)(base + 0x4538);
		unsigned int value = (count * 6 - offset) / count;
		++index;
		offset += 5;
		write[0] = (int)value;
		--write;
	}

	unsigned int count = *(unsigned int *)(base + 0x4538);
	if (count < 0xff)
	{
		int *fill = (int *)(base + (0x124e - count) * 4);
		int remaining = 0xff - count;
		do
		{
			*fill = 1;
			--fill;
			--remaining;
		} while (remaining != 0);
	}
}
