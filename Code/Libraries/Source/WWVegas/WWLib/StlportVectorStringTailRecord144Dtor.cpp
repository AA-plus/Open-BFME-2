// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x56ACB destroys the BfmeStringTailRecord144 range through the rowed
// _Destroy 0x00054ED9 (which reaches the rowed record dtor 0x2D9A43), then
// frees the storage through 0x00030830. The element is a code-generation view
// with the same virtual destructor the separately verified record owner
// carries; only its size and destructibility enter this instantiation.
#include <vector>

struct BfmeStringTailRecord144
{
	virtual ~BfmeStringTailRecord144();
	unsigned char body[0x90 - 4];
};

typedef char VerifyRecordSize[(sizeof(BfmeStringTailRecord144) == 0x90) ? 1 : -1];

template _STL::vector<BfmeStringTailRecord144>::~vector();
