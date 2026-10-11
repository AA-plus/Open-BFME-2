// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bb330.md plus retail only.
// No decoder source was consulted.
// ScaleOrCenter retail 0x001BB330 (126 bytes): after the border update the
// frame is either centred in the YUV config buffer by the any-ratio scaler
// (modes 0 and 1) or handed to CenterImage (mode 2).

struct POSTPROC_INSTANCE;

struct ScaleOrCenterInstance
{
	unsigned char pad00[0x08];
	void *level;                 // 0x08 post-processing level
	unsigned char pad0C[0x68 - 0x0C];
	unsigned int scalingMode;    // 0x68
	unsigned char pad6C[0x70 - 0x6C];
	unsigned int expandedWidth;  // 0x70
	unsigned int expandedHeight; // 0x74
};

struct ScaleOrCenterConfig
{
	unsigned int yWidth;         // 0x00
	unsigned int yHeight;        // 0x04
	unsigned char pad08[0x0C - 0x08];
	unsigned int uvWidth;        // 0x0C
};

void __cdecl d_009a8c50();                                  // 0x001B96A0 UpdateUMVBorder
void __cdecl d_009aa4f0();                                  // 0x001BAF30 AnyRatioFrameScale
struct Rva009AA750Context;
struct Rva009AA750Block;
extern void __cdecl Rva009AA750CopyPlanes(
	Rva009AA750Context *context, int frame, Rva009AA750Block *config); // 0x001BB190 CenterImage

// RVA 0x001BB330
extern "C" void __cdecl ScaleOrCenter(ScaleOrCenterInstance *instance, int frame,
	ScaleOrCenterConfig *config)
{
	if (instance->level != 0)
		((void (__cdecl *)(ScaleOrCenterInstance *, int))d_009a8c50)(instance, frame);
	if (instance->scalingMode > 1)
	{
		if (instance->scalingMode != 2)
			return;
		Rva009AA750CopyPlanes(
			(Rva009AA750Context *)instance, frame, (Rva009AA750Block *)config);
		return;
	}
	unsigned int verticalMargin = (config->yHeight - instance->expandedHeight) >> 1;
	int halfVertical = (int)verticalMargin >> 1;
	unsigned int horizontalMargin = (config->yWidth - instance->expandedWidth) >> 1;
	int halfHorizontal = (int)horizontalMargin >> 1;
	int chromaOffset = halfVertical * config->uvWidth + halfHorizontal;
	int lumaOffset = (int)verticalMargin * config->yWidth + horizontalMargin;
	((void (__cdecl *)(ScaleOrCenterInstance *, int, ScaleOrCenterConfig *, int, int))d_009aa4f0)(
		instance, frame, config, lumaOffset, chromaOffset);
}
