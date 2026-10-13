// Open-BFME5 conversion.
// AptArray::CleanNativeFunctions at retail 0x006D92E0 (236 bytes): WorldBuilder
// 178EA20 names it in its asserts (AptArray.cpp lines 95..105) and releases the
// same eleven native-function slots in the same order.

class AptArray
{
public:
	static void CleanNativeFunctions(void);
};

class Rva008B8B80Releasable
{
public:
	virtual void unused(void) = 0;
	virtual void release(void) = 0;
};

extern Rva008B8B80Releasable *g_rva008B8B80_0;
// g_rva008B8B80_0: matched references place it at VA 0xe1802c (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_0;
extern Rva008B8B80Releasable *g_rva008B8B80_1;
// g_rva008B8B80_1: matched references place it at VA 0xe18030 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_1;
extern Rva008B8B80Releasable *g_rva008B8B80_2;
// g_rva008B8B80_2: matched references place it at VA 0xe18034 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_2;
extern Rva008B8B80Releasable *g_rva008B8B80_3;
// g_rva008B8B80_3: matched references place it at VA 0xe18038 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_3;
extern Rva008B8B80Releasable *g_rva008B8B80_4;
// g_rva008B8B80_4: matched references place it at VA 0xe1803c (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_4;
extern Rva008B8B80Releasable *g_rva008B8B80_5;
// g_rva008B8B80_5: matched references place it at VA 0xe18040 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_5;
extern Rva008B8B80Releasable *g_rva008B8B80_6;
// g_rva008B8B80_6: matched references place it at VA 0xe18054 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_6;
extern Rva008B8B80Releasable *g_rva008B8B80_7;
// g_rva008B8B80_7: matched references place it at VA 0xe1804c (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_7;
extern Rva008B8B80Releasable *g_rva008B8B80_8;
// g_rva008B8B80_8: matched references place it at VA 0xe18058 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_8;
extern Rva008B8B80Releasable *g_rva008B8B80_9;
// g_rva008B8B80_9: matched references place it at VA 0xe1805c (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_9;
extern Rva008B8B80Releasable *g_rva008B8B80_10;
// g_rva008B8B80_10: matched references place it at VA 0xe18050 (zero-filled .bss).
Rva008B8B80Releasable * g_rva008B8B80_10;

void AptArray::CleanNativeFunctions(void)
{
	if (g_rva008B8B80_0 != 0)
	{
		g_rva008B8B80_0->release();
		g_rva008B8B80_0 = 0;
	}
	if (g_rva008B8B80_1 != 0)
	{
		g_rva008B8B80_1->release();
		g_rva008B8B80_1 = 0;
	}
	if (g_rva008B8B80_2 != 0)
	{
		g_rva008B8B80_2->release();
		g_rva008B8B80_2 = 0;
	}
	if (g_rva008B8B80_3 != 0)
	{
		g_rva008B8B80_3->release();
		g_rva008B8B80_3 = 0;
	}
	if (g_rva008B8B80_4 != 0)
	{
		g_rva008B8B80_4->release();
		g_rva008B8B80_4 = 0;
	}
	if (g_rva008B8B80_5 != 0)
	{
		g_rva008B8B80_5->release();
		g_rva008B8B80_5 = 0;
	}
	if (g_rva008B8B80_6 != 0)
	{
		g_rva008B8B80_6->release();
		g_rva008B8B80_6 = 0;
	}
	if (g_rva008B8B80_7 != 0)
	{
		g_rva008B8B80_7->release();
		g_rva008B8B80_7 = 0;
	}
	if (g_rva008B8B80_8 != 0)
	{
		g_rva008B8B80_8->release();
		g_rva008B8B80_8 = 0;
	}
	if (g_rva008B8B80_9 != 0)
	{
		g_rva008B8B80_9->release();
		g_rva008B8B80_9 = 0;
	}
	if (g_rva008B8B80_10 != 0)
	{
		g_rva008B8B80_10->release();
		g_rva008B8B80_10 = 0;
	}
}
