// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva004EE9E9XferVector@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z, retail
// 0x004EE9E9 (245 bytes, EH): the std::vector snapshot transfer over the
// 12-byte Elem003AF8C0 records (vtable 0x00C62A28, three zeroed shorts),
// the same body as the rowed Rva0039C4F7XferSnapshotVector
// (ScoreKeeperPerFrameStatsVectorXfer.cpp) with the record built inline
// rather than by an out-of-line constructor; reserve is the rowed
// Rva004EE55EVector::reserve 0x004EE55E and insertion the rowed
// Rva004EE6D0::push_back 0x004EE9B1. The owner is unknown. The empty-on-load
// error is a block-local XferException built by the rowed formatter and
// thrown through retail's throw info 0x00CFFD18, which lets its slot share
// the record's (frame 0x10), as in Rva00207F91Xfer.cpp.
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

extern "C" const void *const vtbl_00C62A28[];  // ??_7Elem003AF8C0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C62A28=??_7Elem003AF8C0@@6B@")

struct __declspec(novtable) Elem003AF8C0 : public Snapshot
{
	Elem003AF8C0()
	{
		*(const void **)this = vtbl_00C62A28;
		field04 = 0;
		field06 = 0;
		field08 = 0;
	}
	virtual __forceinline ~Elem003AF8C0() {}
	short field04, field06, field08;
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
};
class Rva004EE6D0
{
public:
	void push_back(const Elem003AF8C0 &value);
	Elem003AF8C0 *start, *finish, *end;
};
class Rva004EE55EVector
{
public:
	void reserve(unsigned int count);
};
struct XferVersion
{
    unsigned char minimum, current;
};

class Xfer
{
public:
 virtual ~Xfer();
 virtual void slot01();
 virtual bool IsStoring() const;
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual Xfer &xferVersion(XferVersion *);
 virtual Xfer &xferTypeName(const char *const &);
 virtual Xfer &xferSnapshot(Elem003AF8C0 *);
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual Xfer &xferUnsignedInt(unsigned int *);
};
struct XferException
{
    char *text;
    int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_Va00CFFD18;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

Xfer *Rva004EE9E9XferVector(Xfer *xfer, Rva004EE6D0 *vector)
{
    XferVersion version = {1, 1};
    xfer->xferVersion(&version);
    unsigned int count = vector->finish - vector->start;
    xfer->xferTypeName("std::vector").xferUnsignedInt(&count);
    if (xfer->IsStoring())
    {
        Elem003AF8C0 *end = vector->finish;
        Elem003AF8C0 *it = vector->start;
        while (it != end)
        {
            xfer->xferSnapshot(it);
            ++it;
        }
    }
    else
    {
        if (vector->start != vector->finish)
        {
            XferException error;
            bfmeFormatText(&error, 4, "Vector must be empty on load");
            _CxxThrowException(&error, (const _s__ThrowInfo *)&g_Va00CFFD18); __assume(0);
        }
        else
        {
            reinterpret_cast<Rva004EE55EVector *>(vector)->reserve(count);
            Elem003AF8C0 value;
            while (count != 0)
            {
                --count;
                vector->push_back(value);
                xfer->xferSnapshot(vector->finish - 1);
            }
        }
    }
    return xfer;
}
