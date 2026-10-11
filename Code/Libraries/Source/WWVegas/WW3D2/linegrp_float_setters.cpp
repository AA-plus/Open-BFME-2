// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// LineGroupClass::Set_Line_Size, ::Set_Line_Alpha and ::Set_Line_UCoord, split
// out of linegrp.cpp because retail stores these floats with movss.  The rest of
// the accessor block in that unit is integer struct copies, which compile the
// same either way; the float setters live here, where the flag costs nothing else.
//
// Set_Line_UCoord has no body of its own: the linker folded it into the
// identical movss xmm0,[esp+4] / movss [ecx+0x44],xmm0 / ret 4 at 0x00179010
// (PointGroupClass::Set_Point_Alpha), where symbols.csv already pins the name.
//
// Retail 0x001B35F0 is movss xmm0,[esp+4] / movss [ecx+0x30],xmm0 / ret 4 and
// 0x001B3690 is the same shape against [ecx+0x40] -- DefaultLineSize and
// DefaultLineAlpha at the offsets linegrp.h already gives them, confirmed by the
// neighbouring landed rows (Set_Line_Color at +0x34, Set_Tail_Diffuse at +0x48).
#include "linegrp.h"

void LineGroupClass::Set_Line_Size(float size)
{
	DefaultLineSize = size;
}

void LineGroupClass::Set_Line_Alpha(float alpha)
{
	DefaultLineAlpha = alpha;
}

void LineGroupClass::Set_Line_UCoord(float ucoord)
{
	DefaultLineUCoord = ucoord;
}
