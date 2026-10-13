// cl: /DNDEBUG /MD /EHsc
// Retail 0x00904230: DX8CALL(BeginScene()) wrapped by a matching enter/leave helper.

struct IDirect3DDevice8;
struct IDirect3DSurface8;

struct D3DLOCKED_RECT
{
	int Pitch;
	void *pBits;
};

struct IDirect3DSurface8Vtbl
{
	void *reserved0[2];
	unsigned long (__stdcall *Release)(IDirect3DSurface8 *self);
	void *reserved1[10];
	long (__stdcall *LockRect)(IDirect3DSurface8 *self, D3DLOCKED_RECT *locked,
		const void *rect, unsigned long flags);
	long (__stdcall *UnlockRect)(IDirect3DSurface8 *self);
};

struct IDirect3DSurface8
{
	IDirect3DSurface8Vtbl *lpVtbl;
};

struct IDirect3DDevice8Vtbl
{
	void *reserved0[18];
	long (__stdcall *GetBackBuffer)(IDirect3DDevice8 *self, unsigned int swap_chain,
		unsigned int back_buffer, int type, IDirect3DSurface8 **surface);
	void *reserved1[22];
	long (__stdcall *BeginScene)(IDirect3DDevice8 *self);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

// Retail 0x009588E0 is the error-reporting inline COM wrapper reached from
// Begin_Scene_Inner's enter and leave edges.  The browser dispatch object is
// shared with the WOL wrapper family; this view only supplies the slot that
// this body actually calls.
struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);

struct BfmeGuidTSA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidTSA g_bfmeIidTSA;

class Rva00958D30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0c;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1c;
		void *slot20;
		void *slot24;
		void *slot28;
		void *slot2c;
		void *slot30;
		void *slot34;
		void *slot38;
		long (__stdcall *slot3c)(Rva00958D30 *self);
	};

	long invoke()
	{
		long result = vtable->slot3c(this);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this,
				reinterpret_cast<const GUID &>(g_bfmeIidTSA));
		return result;
	}

	Vtable *vtable;
};

struct Rva00959410Ptr
{
	Rva00958D30 *m_p;
	operator bool() const
	{
		return m_p != 0;
	}
};

extern Rva00959410Ptr Rva00959410Dispatch;

// ?bfmeDebugTouch009588e0@@YAXXZ
__declspec(noinline) void bfmeDebugTouch009588e0(void)
{
	if (Rva00959410Dispatch)
		Rva00959410Dispatch.m_p->invoke();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Begin_Scene_Inner(void);
	static void Rva0011D2D0WaitForBackBuffer(void);

private:
protected:
	static IDirect3DDevice8 *D3DDevice;
private:
	static unsigned D3DCallCount;
};

// ?Begin_Scene_Inner@DX8Wrapper@@SAXXZ
void DX8Wrapper::Begin_Scene_Inner(void)
{
	bfmeDebugTouch009588e0();
	D3DDevice->lpVtbl->BeginScene(D3DDevice);
	++D3DCallCount;
	bfmeDebugTouch009588e0();
}

// Retail 0x0011D2D0 (87 B), between Begin_Scene_Inner and Clear: when a
// device exists, fetch back buffer 0 (GetBackBuffer, vtable +0x48), lock it
// read-only (LockRect +0x34, flags 0x800 = D3DLOCK_READONLY), unlock it if the
// lock succeeded (+0x38) and release the surface (+0x08). A lock of the back
// buffer stalls until the GPU has drained, so this reads as a frame sync.
// It has no direct caller or data reference and no Zero Hour counterpart:
// the name is address-derived.
void DX8Wrapper::Rva0011D2D0WaitForBackBuffer(void)
{
	if (D3DDevice) {
		IDirect3DSurface8 *surface = 0;
		if (D3DDevice->lpVtbl->GetBackBuffer(D3DDevice, 0, 0, 0, &surface) >= 0) {
			D3DLOCKED_RECT locked;
			if (surface->lpVtbl->LockRect(surface, &locked, 0, 0x800) >= 0) {
				surface->lpVtbl->UnlockRect(surface);
			}
			surface->lpVtbl->Release(surface);
		}
	}
}
// ?Rva00959410Dispatch@@3URva00959410Ptr@@A: the global at VA 0xdf7040 is ?g_bfmeObjECF@@3PAUBfmeObjECF@@A.
#pragma comment(linker, "/alternatename:?Rva00959410Dispatch@@3URva00959410Ptr@@A=?g_bfmeObjECF@@3PAUBfmeObjECF@@A")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?D3DCallCount@DX8Wrapper@@0IA=?number_of_DX8_calls@@3IA")
