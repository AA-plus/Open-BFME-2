// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UBfmeStringTailRecord156@@V?$allocator@UBfmeStringTailRecord156@@@_STL@@@_STL@@QAE@XZ @0x004CC1AD 63B.
// Vector dtor sibling of 0x2CC70 (StlportAsciiStringVectorDtor.cpp): destroys the
// range through the pinned _Destroy at 0x004CC195 then frees storage via 0x30830
// (EH states 0/-1); called by the ModelConditionAudioLoopClientBehaviorModuleData
// dtor at 0x004CC226. Same 63B Destroy+free shape as the family under /O1 /GX
// (/EHsc gives 59B missing the or-state). Element is size-free per the family
// rule; the range destroy folds with the rowed BfmeStringTailRecord156 destroy.
#include <vector>

struct BfmeStringTailRecord156 { public: ~BfmeStringTailRecord156(); };
template _STL::vector<BfmeStringTailRecord156>::~vector();
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *); }
namespace _STL { template <> void __destroy<BfmeStringTailRecord156 *,BfmeStringTailRecord156>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,BfmeStringTailRecord156 *); }
namespace _STL { template <> void __destroy_aux<BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,_STL::__false_type const &); }
// bfme link decl-only end
