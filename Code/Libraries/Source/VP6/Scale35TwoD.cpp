// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001ba1f0.md plus retail only.
// No decoder source was consulted.
//
// Scale_3_5_2D (retail 0x001BA1F0, 300 bytes): scales a plane up by 5/3 in both
// directions in bands of 3 source rows to 5 destination rows, through the
// installed callbacks: the horizontal line scaler, the vertical band filter
// and the last-band vertical filter. Source row 0 is scaled into destination
// row 0; then for (destination height / 5) - 1 bands, source rows 1..2 go to
// destination rows 1..2, source row 3 to destination row 5, the vertical band
// filter runs on the destination band and both pointers advance (3 source
// rows, 5 destination rows). Finally the last band's rows 1..2 are scaled and
// the last-band filter runs. The first argument and the source height are
// unused.

struct ScaleContext;

typedef void (__cdecl *HorizontalScaleCallback)(
	const unsigned char *, unsigned int, unsigned char *, unsigned int);
typedef void (__cdecl *VerticalScaleCallback)(
	unsigned char *, unsigned int, unsigned int);

// Callback slots owned by the generic scaler's unit (image 0x00E22Fxx).
extern HorizontalScaleCallback g_horizontalScale35Slot;
extern VerticalScaleCallback g_verticalScale35Slot;
extern VerticalScaleCallback g_lastVerticalScale35Slot;

// RVA 0x001BA1F0
extern "C" void __cdecl Scale_3_5_2D(
    ScaleContext *, const unsigned char *source, int source_pitch,
    unsigned int source_width, unsigned int, unsigned char *dest,
    unsigned int dest_pitch, unsigned int dest_width, unsigned int dest_height)
{
    unsigned int i, k;
    g_horizontalScale35Slot(source, source_width, dest, dest_width);
    for (k = 0; k < dest_height / 5 - 1; ++k) {
        for (i = 1; i < 3; ++i)
            g_horizontalScale35Slot(source + i * source_pitch, source_width,
                dest + i * dest_pitch, dest_width);
        g_horizontalScale35Slot(source + 3 * source_pitch, source_width,
            dest + 5 * dest_pitch, dest_width);
        g_verticalScale35Slot(dest, dest_pitch, dest_width);
        source += 3 * source_pitch;
        dest += 5 * dest_pitch;
    }
    for (i = 1; i < 3; ++i)
        g_horizontalScale35Slot(source + i * source_pitch, source_width,
            dest + i * dest_pitch, dest_width);
    g_lastVerticalScale35Slot(dest, dest_pitch, dest_width);
}
