// ?rva00045213@W3DDisplay@@AAEXPADI@Z
// partial score=0.8 date=2026-10-13
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva00045213@W3DDisplay@@AAEXPADI@Z @0x00045213 377B, thiscall ret 8.
// W3DDisplay::captureScreen: copy the client area of the front buffer into a
// 24-bit image (rowBytes apart), zero-filling the parts of the client area
// that lie outside the surface. Called from takeScreenShot (0x00049B3A) with
// the image and 3 * width.
// Evidence (target): GlobalData +0xEA5 gates a 500 ms Sleep before the grab;
// the DX8 thread lock (0x0011F520 / 0x00120F50) wraps the whole body;
// front buffer 0x0011DFE0, GetDesc/LockRect/Release at surface slots
// 12/13/2; LockRect error goes through Log_DX8_ErrorCode 0x0011F450; the
// client rectangle is converted to screen coordinates with GetClientRect +
// ClientToScreen exactly as takeScreenShot does. BFME 2 clamps each row and
// pixel against the surface description (8 words at the stack top).
// Donor (structure only): BFME 1 W3DDisplayCaptureScreen.cpp, whose body has
// no clamping and logs through a debug manager instead.

struct BfmeRect {
	long left, top, right, bottom;
};
struct BfmePoint {
	long x, y;
};

extern void *ApplicationHWnd;
extern "C" __declspec(dllimport) int __stdcall GetClientRect(void *, BfmeRect *);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(void *, BfmePoint *);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" void *__cdecl memset(void *, int, unsigned int);

extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct BfmeSurfaceDesc
{
	unsigned int format;
	unsigned int type;
	unsigned int usage;
	unsigned int pool;
	unsigned int multiSampleType;
	unsigned int multiSampleQuality;
	unsigned int width;
	unsigned int height;
};

struct BfmeLockedRect
{
	long pitch;
	void *bits;
};

class IDirect3DSurface9
{
public:
	virtual long __stdcall slot00(void *, void **);
	virtual unsigned long __stdcall slot04();
	virtual unsigned long __stdcall Release();
	virtual long __stdcall slot0c();
	virtual long __stdcall slot10();
	virtual long __stdcall slot14();
	virtual long __stdcall slot18();
	virtual long __stdcall slot1c();
	virtual long __stdcall slot20();
	virtual long __stdcall slot24();
	virtual long __stdcall slot28();
	virtual long __stdcall slot2c();
	virtual long __stdcall GetDesc(BfmeSurfaceDesc *desc);
	virtual long __stdcall LockRect(BfmeLockedRect *locked, const BfmeRect *rect, unsigned long flags);
};

class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
};

void Log_DX8_ErrorCode(unsigned int error);

class GlobalData
{
	unsigned char m_pad00[0xEA5];

public:
	bool m_delayBeforeCapture;
};

extern GlobalData *TheWritableGlobalData;

class W3DDisplay
{
private:
	void rva00045213(char *image, unsigned int rowBytes);
};

void W3DDisplay::rva00045213(char *image, unsigned int rowBytes)
{
	if (TheWritableGlobalData->m_delayBeforeCapture)
		Sleep(500);

	BFMEDX8DeviceLock lock;
	IDirect3DSurface9 *front = DX8Wrapper::_Get_DX8_Front_Buffer();
	BfmeSurfaceDesc desc;
	front->GetDesc(&desc);

	BfmeRect bounds;
	BfmePoint point;
	GetClientRect(ApplicationHWnd, &bounds);
	point.x = bounds.left;
	point.y = bounds.top;
	ClientToScreen(ApplicationHWnd, &point);
	bounds.left = point.x;
	bounds.top = point.y;
	point.x = bounds.right;
	point.y = bounds.bottom;
	ClientToScreen(ApplicationHWnd, &point);
	bounds.right = point.x;
	bounds.bottom = point.y;

	BfmeLockedRect locked;
	long result = front->LockRect(&locked, &bounds, 0x10);
	if (result != 0)
		Log_DX8_ErrorCode(result);

	unsigned int width = bounds.right - bounds.left;
	unsigned int height = bounds.bottom - bounds.top;
	for (unsigned int y = 0; y < height; ++y) {
		int row = bounds.top + y;
		const char *src = (const char *)locked.bits + y * locked.pitch;
		if (row < 0 || (unsigned int)row >= desc.height) {
			memset(image, 0, width * 3);
		} else {
			char *dest = image;
			for (unsigned int x = 0; x < width; ++x) {
				int column = bounds.left + x;
				if (column >= 0 && (unsigned int)column < desc.width) {
					dest[0] = src[0];
					dest[1] = src[1];
					dest[2] = src[2];
				} else {
					dest[0] = 0;
					dest[1] = 0;
					dest[2] = 0;
				}
				src += 4;
				dest += 3;
			}
		}
		image += rowBytes;
	}

	front->Release();
}
