// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b9e40.md plus retail only.
// No decoder source was consulted.
//
// Scale_4_5_2D (retail 0x001B9E40, 332 bytes): scales a plane up by 5/4 in both
// directions in bands of 4 source rows to 5 destination rows, through the
// installed callbacks: the horizontal line scaler, the vertical band filter
// and the last-band vertical filter. Source row 0 is scaled into destination
// row 0; then for (destination height / 5) - 1 bands, source rows 1..3 go to
// destination rows 1..3, source row 4 to destination row 5, the vertical band
// filter runs on the destination band and both pointers advance (4 source
// rows, 5 destination rows). Finally the last band's rows 1..3 are scaled and
// the last-band filter runs. The first argument and the source height are
// unused.

struct ScaleContext;

typedef void (__cdecl *HorizontalScaleCallback)(
	const unsigned char *, unsigned int, unsigned char *, unsigned int);
typedef void (__cdecl *VerticalScaleCallback)(
	unsigned char *, unsigned int, unsigned int);

// Callback slots owned by the generic scaler's unit (image 0x00E22Fxx).
extern HorizontalScaleCallback g_horizontalScale45Slot;
extern VerticalScaleCallback g_verticalScale45Slot;
extern VerticalScaleCallback g_lastVerticalScale45Slot;

// RVA 0x001B9E40
extern "C" void __cdecl Scale_4_5_2D(
    ScaleContext *, const unsigned char *source, int source_pitch,
    unsigned int source_width, unsigned int, unsigned char *dest,
    unsigned int dest_pitch, unsigned int dest_width, unsigned int dest_height)
{
    unsigned int i, k;
    g_horizontalScale45Slot(source, source_width, dest, dest_width);
    for (k = 0; k < dest_height / 5 - 1; ++k) {
        for (i = 1; i < 4; ++i)
            g_horizontalScale45Slot(source + i * source_pitch, source_width,
                dest + i * dest_pitch, dest_width);
        g_horizontalScale45Slot(source + 4 * source_pitch, source_width,
            dest + 5 * dest_pitch, dest_width);
        g_verticalScale45Slot(dest, dest_pitch, dest_width);
        source += 4 * source_pitch;
        dest += 5 * dest_pitch;
    }
    for (i = 1; i < 4; ++i)
        g_horizontalScale45Slot(source + i * source_pitch, source_width,
            dest + i * dest_pitch, dest_width);
    g_lastVerticalScale45Slot(dest, dest_pitch, dest_width);
}
