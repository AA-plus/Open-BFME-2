// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?reset@W3DDisplay@@UAEXXZ, retail 0x00043418..0x00043511 (249 bytes), W3DDisplay vtable
// 0x007C3C80 slot 9 (WB 0x00966600). Zero Hour's W3DDisplay::reset spine: the base display
// reset (rowed 0x0025D9E3), then every render object leaves m_3DScene through a scene
// iterator; BFME 2 also clears the global +0xBBD flag and +0x98 value, the clip flag at
// +0x17C and two display globals, and under the DX8 thread lock evicts managed resources,
// clears the texture cache (rowed 0x0012641F) and re-inits the streak renderer.
typedef bool Bool;
typedef float Real;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
struct BFMEDX8DeviceLock
{
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

void Log_DX8_ErrorCode(unsigned int error);
void Rva0012641FClear();

class SimpleStreakRendererClass
{
public:
	static void Init(bool flag);
};

struct IDirect3DDevice8
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual long __stdcall EvictManagedResources();
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *D3DDevice;
};

class GlobalData
{
public:
	unsigned char m_pad000[0x62];
	Bool m_flag62;			// +0x62
	unsigned char m_pad063[0x98 - 0x63];
	Real m_value98;			// +0x98
	unsigned char m_pad09C[0xBBD - 0x9C];
	Bool m_flagBBD;			// +0xBBD
};
extern GlobalData *TheWritableGlobalData;

extern int g_Va00DE1B40;
extern int g_Va00DB3BDC;

class RenderObjClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { NumRefs++; }
	void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
	int NumRefs;
};

class SceneIterator
{
public:
	virtual void s00();
	virtual void First();
	virtual void Next();
	virtual Bool Is_Done();
	virtual RenderObjClass *Current_Item();
};

class RTS3DScene
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void Remove_Render_Object(RenderObjClass *obj);	// +0x0C
	virtual SceneIterator *Create_Iterator();			// +0x10
	virtual void Destroy_Iterator(SceneIterator *it);		// +0x14
};

class BfmeStrVM0
{
public:
	void rva0025D9E3();
};

class W3DDisplay
{
public:
	virtual ~W3DDisplay();
	virtual void init();
	virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05();
	virtual void s06(); virtual void s07(); virtual void s08();
	virtual void reset();

	static RTS3DScene *m_3DScene;

private:
	unsigned char m_pad04[0x17C - 4];
	Bool m_isClippedEnabled;		// +0x17C
};

void W3DDisplay::reset()
{
	((BfmeStrVM0 *)this)->rva0025D9E3();
	TheWritableGlobalData->m_flagBBD = false;

	SceneIterator *sceneIter = m_3DScene->Create_Iterator();
	sceneIter->First();
	while (!sceneIter->Is_Done()) {
		RenderObjClass *robj = sceneIter->Current_Item();
		if (robj) {
			robj->Add_Ref();
			m_3DScene->Remove_Render_Object(robj);
			robj->Release_Ref();
		}
		sceneIter->Next();
	}
	m_3DScene->Destroy_Iterator(sceneIter);

	m_isClippedEnabled = false;
	if (TheWritableGlobalData)
		TheWritableGlobalData->m_value98 = 0.0f;
	g_Va00DE1B40 = 0;
	g_Va00DB3BDC = -1;

	BFMEDX8DeviceLock lock;
	long hr = DX8Wrapper::D3DDevice->EvictManagedResources();
	if (hr)
		Log_DX8_ErrorCode(hr);
	Rva0012641FClear();
	SimpleStreakRendererClass::Init(TheWritableGlobalData->m_flag62);
}
