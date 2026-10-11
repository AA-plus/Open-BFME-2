// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2renderobj /DNDEBUG /DBFME_SNAPSHOT_NAME_SLOT /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/shims/moduledata/Common
// stlport
// Native E3B41..E3BD9 is the complete 152-byte terrain subtype destructor.
// Its four vptr stores and constructor E3BFE establish the RenderObj,
// cleanup-hook and Snapshot bases; the owned base destructor is 6D0D7.
// The 199-byte constructor proves the base extent 3884, two 12-byte headers
// at 38B4/38C4 and eight opaque 12-byte records at 38D0. Original subtype
// and element names remain unknown. BF1 FlatHeightMap.cpp at 9e3be919b10a
// supplies the release-tiles/singleton-clear lifetime guide; target fields
// and additional owners come from retail, not that donor layout.
// Native FuncInfo D06D90 has four unwind entries: base 6D0D7, wrapper
// 8B4CD at +38B4, buffer 7FAB3 at +38C4, counted holder 7B724 at +3938.
// These members, rather than explicit cleanup in the destructor body,
// generate states 3,2,1,0,-1. A local retained pointer avoids a reload in
// the counted holder's inline destruction. Free uses the already verified
// game allocator; the CRT free declaration from the headers is different.
// Deleting destructor E3CC5 and adjustments E3BD9/E3BE1 share this view.

#include "rendobj.h"
#include "Snapshot.h"

class DX8_CleanupHook
{
public:
    virtual void ReleaseResources() = 0;
    virtual void ReAcquireResources() = 0;
};

class Rva006D0D7 : public RenderObjClass, public DX8_CleanupHook, public Snapshot
{
public:
    virtual ~Rva006D0D7();
private:
    char m_unmodelledCC[0x3884 - 0xCC];
};

struct Rva0008B470
{
    ~Rva0008B470();
    char m_header[12];
};

struct Rva0008B4CD
{
    ~Rva0008B4CD() {}
    Rva0008B470 m_vector;
};

void __cdecl Rva00030830GameFree(void *);
struct RvaE3VecBase
{
    void *m_start;
    void *m_finish;
    void *m_end;
    ~RvaE3VecBase()
    {
        if (m_start)
            Rva00030830GameFree(m_start);
    }
};

struct RvaE3Ref
{
    virtual void release();
    int m_refs;
};

struct RvaE3RefOwner
{
    RvaE3Ref *m_pointer;
    __forceinline ~RvaE3RefOwner()
    {
        RvaE3Ref *p = m_pointer;
        if (p)
        {
            if (--p->m_refs == 0)
                p->release();
        }
    }
};

class Rva000E15D1 { public: void rva000E14C4(); };
class BfmeTaintModeView;
extern BfmeTaintModeView *g_bfmeTaintModeView;

class Rva000E3B41 : public Rva006D0D7
{
public:
    virtual ~Rva000E3B41();
private:
    void *m_3884;
    char m_unmodelled3888[0x38B4 - 0x3888];
    Rva0008B4CD m_38B4;
    char m_unmodelled38C0[4];
    RvaE3VecBase m_38C4;
    char m_unmodelled38D0[8 * 12];
    char m_unmodelled3930[8];
    RvaE3RefOwner m_3938;
};

Rva000E3B41::~Rva000E3B41()
{
    ((Rva000E15D1 *)this)->rva000E14C4();
    g_bfmeTaintModeView = 0;
}

void Rva000E3B41_Delete(Rva000E3B41 *p) { delete p; }
