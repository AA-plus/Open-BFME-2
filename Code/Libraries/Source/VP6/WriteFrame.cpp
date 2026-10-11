// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bb3b0.md and 001bb420.md plus
// retail only. No decoder source was consulted.
//
// Raw frame dump helpers (retail 0x001BB3B0 and 0x001BB420): each formats a
// file name from the frame number into a 256-byte stack buffer, opens it for
// binary writing, writes one record from the data pointer and closes it.

struct PB_INSTANCE
{
	unsigned char m_pad[0x1EC];
	unsigned int m_ySize;            // 0x1EC
	unsigned char m_pad1F0[0x18];
	int m_reconYSize;                // 0x208
	int m_reconUvSize;               // 0x20C
};

extern "C" {
__declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, ...);
__declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, void *stream);
__declspec(dllimport) void *__cdecl fopen(const char *name, const char *mode);
__declspec(dllimport) int __cdecl fclose(void *stream);
}

// RVA 0x001BB3B0: record length is the recon Y plane plus twice the recon UV plane.
extern "C" void __cdecl vp6_writeframe(PB_INSTANCE *pbi, void *buf, int index)
{
	char name[0x100];
	sprintf(name, "y%04d.raw", index);
	void *fp = fopen(name, "wb");
	unsigned int size = pbi->m_reconYSize + pbi->m_reconUvSize * 2;
	fwrite(buf, size, 1, fp);
	fclose(fp);
}

// RVA 0x001BB420: unpadded name, record length is the Y plane size.
extern "C" void __cdecl vp6_writeframe2(PB_INSTANCE *pbi, void *data, int index)
{
	char name[0x100];
	sprintf(name, "y%d.raw", index);
	void *file = fopen(name, "wb");
	fwrite(data, pbi->m_ySize, 1, file);
	fclose(file);
}
