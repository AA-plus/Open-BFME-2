// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?getPivotPoint@Rva0015334F@@QAE?AURva005AA05APoint@@PAURva005AA55DRecord@@PBUCoord3D@@1@Z
// retail 0x005AA05A..0x005AA0CA (112B), RET 16 with a hidden Coord3D result.
// WB AIFlankAttackTacticImp::getPivotPoint (wb151B250): the record owner's
// position (+0x554) when its 2D squared distance to the record point is at
// least 160000, else the destination argument. The equal-arm conditional on
// the owner receiver reproduces retail's load order (W7-S2 r4 sweep).
#include "../../../../../../../Libraries/Include/Lib/Coord3D.h"
// Hidden-result view: retail copies the 12-byte result member by member (fld/fstp
// then two integer moves), the shape of a user copy constructor, which the canonical
// Coord3D does not have.
struct Rva005AA05APoint { float x, y, z; Rva005AA05APoint(const Coord3D &v) { x = v.x; y = v.y; z = v.z; } };
struct PivotOwner { char pad[0x554]; Coord3D position; };
struct Rva005AA55DRecord { char pad[0x0C]; Coord3D point; char pad18[0x24-0x18]; PivotOwner *owner; };
class Rva0015334F { public: Rva005AA05APoint getPivotPoint(Rva005AA55DRecord*,const Coord3D*,const Coord3D*); };
Rva005AA05APoint Rva0015334F::getPivotPoint(Rva005AA55DRecord *record,const Coord3D *from,const Coord3D *to) {
 float dx=record->owner->position.x-record->point.x;
 float dy=(record ? record->owner->position.y : record->owner->position.y)-record->point.y;
 if (dy*dy+dx*dx >= 160000.0f) return record->owner->position;
 return *to;
}
