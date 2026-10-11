// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b5840.md plus retail only. No
// decoder source was consulted.
//
// VP6_StartDecoder (retail 0x001B5840): creates the decoder instance, stores
// the image size into the scale, output and frame size fields, creates the
// post-processor and quantizer, copies the global CPU frequency, then runs
// the frame detail initialisation; on failure the instance is deleted and 0
// is returned. On success the quantizer's cached quality is cleared and the
// configuration is initialised.

struct Vp6QuantizerHead
{
	int m_gap[14];
	int m_cachedQuality;
};

struct CodecState
{
	unsigned char m_head[0x13c];
	Vp6QuantizerHead *m_quantizer;
	unsigned char m_gap0[0x64];
	int m_cpuFrequency;
	int m_gap1[2];
	int m_frameWidth;
	int m_frameHeight;
	unsigned char m_gap2[0x7c];
	int m_scaleWidth;
	int m_scaleHeight;
	int m_outputWidth;
	int m_outputHeight;
	unsigned char m_gap3[0x50];
	void *m_gap4;
	void *m_postProc;
};

struct PB_INSTANCE;

extern int g_bfmeSharedJX; // retail 0x00E23300: CPU frequency

extern "C" CodecState * __cdecl VP6_CreatePBInstance();
extern "C" int __cdecl VP6_InitFrameDetails(CodecState *state);
extern "C" void *__cdecl CreatePostProcInstance(void *config);
extern "C" Vp6QuantizerHead *__cdecl VP6_CreateQuantizer();
extern "C" void __cdecl VP6_InitialiseConfiguration(PB_INSTANCE *pbi);
extern "C" void __cdecl VP6_DeletePBInstance(PB_INSTANCE **instance);

// RVA 0x001B5840
extern "C" int __cdecl VP6_StartDecoder(CodecState **p, int width, int height)
{
	*p = VP6_CreatePBInstance();

	(*p)->m_scaleWidth = width;
	(*p)->m_scaleHeight = height;
	(*p)->m_outputWidth = width;
	(*p)->m_outputHeight = height;
	(*p)->m_frameWidth = width;
	(*p)->m_frameHeight = height;
	(*p)->m_postProc = CreatePostProcInstance((char *)*p + 0x1b0);
	(*p)->m_quantizer = VP6_CreateQuantizer();
	(*p)->m_cpuFrequency = g_bfmeSharedJX;

	if (VP6_InitFrameDetails(*p) == 0)
	{
		VP6_DeletePBInstance((PB_INSTANCE **)p);

		return 0;
	}

	(*p)->m_quantizer->m_cachedQuality = 0;

	VP6_InitialiseConfiguration((PB_INSTANCE *)*p);

	return 1;
}
