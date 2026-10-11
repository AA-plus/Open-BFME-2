// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?update_cached_box@OBBoxRenderObjClass@@MAEXXZ @ 0x001758C0 (251B).
// Dedicated TU: boxrobj.cpp cannot take another row (bulk import left defs
// without rows or markers, failing find_declared_unmatched on any staging).
// Same headers and /arch:SSE2 (retail inlines Transform_Vector as SSE math),
// so layout and codegen match the home TU. Verbatim BFME1 body.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"
#include "boxrobj.h"

// LINK: this TU's header-inline Transform_Vector copy is not retail's. The
// call below inlines it (SSE, no E8) but the live call still emits the loser
// COMDAT. Manual inline of the identical BFME1 body (matrix3d.h:1739) via a
// file-static helper keeps the bytes and drops the emission (no flags touched).
static __forceinline void bfme_obbox_xform(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v;

	// check for aliased parameters
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;		// whats the right way to do this...
	}

	out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
	out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
	out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
}

// ?update_cached_box@OBBoxRenderObjClass@@MAEXXZ
void OBBoxRenderObjClass::update_cached_box(void)
{
	bfme_obbox_xform(Transform, ObjSpaceCenter, &CachedBox.Center);
	CachedBox.Extent.Set(ObjSpaceExtent);
	CachedBox.Basis.Set(Transform);
}
