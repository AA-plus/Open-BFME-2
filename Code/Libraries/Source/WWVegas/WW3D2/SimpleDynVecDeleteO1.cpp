// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// SimpleDynVecClass<Vector3>::Delete (0x00100306): retail holds one size-optimised (/O1) out-of-line copy of the template body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#include "../../../../../reference/shims/bfmesegline/rendobj.h" // scoped retail collision slots
#include "segline.h"
#include "ww3d.h"
#include "rinfo.h"
#include "predlod.h"
#include "v3_rnd.h"
#include "texture.h"
#include "coltest.h"
#include "w3d_file.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vp.h"
#include "vector3i.h"
#include "sortingrenderer.h"

// Retail Delete calls the 31-byte Shrink worker at 0x00100210. That worker is
// already rowed under the opaque BfmePod4 instantiation; its whole body reads
// only VectorMax (+8) and ActiveCount (+12), then dispatches virtual Resize.
// It never touches elements. Project the common container prefix to that owner
// while keeping this Vector3 object's vtable, hence its Vector3 Resize callback.
// BfmePod4 does not describe the Vector3 payload or establish a retail type name.
struct BfmePod4 { int a[1]; };
template <> bool SimpleDynVecClass<BfmePod4>::Shrink(void);
struct BfmeNativeShrinkAccess : SimpleDynVecClass<BfmePod4> {
    using SimpleDynVecClass<BfmePod4>::Shrink;
};

template <> inline bool SimpleDynVecClass<Vector3>::Delete(int index, bool allow_shrink)
{
    if (index < ActiveCount - 1) {
        memmove(&Vector[index], &Vector[index + 1],
            (ActiveCount - index - 1) * sizeof(Vector3));
    }
    --ActiveCount;
    if (allow_shrink) {
        reinterpret_cast<BfmeNativeShrinkAccess *>(this)->Shrink();
    }
    return true;
}

extern bool (SimpleDynVecClass<Vector3>::*const g_bfmeDynVecV3DeleteAnchor)(int, bool);
bool (SimpleDynVecClass<Vector3>::*const g_bfmeDynVecV3DeleteAnchor)(int, bool) = &SimpleDynVecClass<Vector3>::Delete;
