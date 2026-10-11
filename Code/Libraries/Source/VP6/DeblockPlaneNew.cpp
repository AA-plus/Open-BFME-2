// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bfac0.md plus retail only.
// No decoder source was consulted.
//
// DeblockPlaneNew (retail 0x001BFAC0, 303 bytes): deblocks one plane with the
// new filter. The first four lines are copied from source to destination;
// for each further band the plane pointers advance eight lines and the band
// routine (pointer at image 0x00E22FD0) runs with (instance, source,
// destination, line step, across, start, scale), start gaining the fragments
// across. The final four lines are copied and the vertical-edge routine
// (0x001BE490, DeblockVerticalEdgesInNonFilteredBandNewFilter) finishes with
// the same seven arguments.

extern "C" void * __cdecl memcpy(void *destination, const void *source,
	unsigned int bytes);
#pragma intrinsic(memcpy)

struct Rva009AF200Context;

typedef void (__cdecl *DeblockBandCallback)(
    Rva009AF200Context *, unsigned char *, unsigned char *,
    unsigned int, unsigned int, int, const unsigned int *);

struct DeblockPlaneLocals
{
    int distance;
    unsigned char *directDestination;
    unsigned int directRows;
    DeblockBandCallback rowFunction;
};

static DeblockBandCallback g_rva01356EB4;
// Retail 0x001BE490; pinned under this address-derived name.
extern void __cdecl Rva009ADAA0(
	Rva009AF200Context *, unsigned char *, unsigned char *,
	unsigned int, unsigned int, int, const unsigned int *);

// RVA 0x001BFAC0
extern "C" void __cdecl DeblockPlaneNew(
    Rva009AF200Context *context,
	unsigned int stride,
	int index,
	unsigned int width,
	unsigned int height,
	unsigned char *source,
    unsigned char *destination,
    const unsigned int *table)
{
    DeblockPlaneLocals locals;
    locals.rowFunction = g_rva01356EB4;
    locals.directDestination = destination;
    locals.distance = (int)(source - destination);
    locals.directRows = 4;
    do
    {
        memcpy(locals.directDestination,
            locals.directDestination + locals.distance, stride);
        locals.directDestination += stride;
        --locals.directRows;
    }
    while (locals.directRows != 0);

    if (height > 1)
    {
        unsigned int eightRows = stride * 8;
        --height;
        do
        {
            source += eightRows;
            destination += eightRows;
            locals.rowFunction(
                context, source, destination,
                stride, width, index, table);
            index += width;
            --height;
		}
		while (height != 0);
	}

    unsigned char *tailDestination = destination + stride * 4;
    locals.distance = (int)(source - destination);
    locals.directRows = 4;
    do
    {
        memcpy(tailDestination, tailDestination + locals.distance, stride);
        tailDestination += stride;
        --locals.directRows;
    }
    while (locals.directRows != 0);

    Rva009ADAA0(
        context, source, destination, stride, width, index, table);
}
