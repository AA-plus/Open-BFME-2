// cl: /O1 /DNDEBUG /MD /EHsc
// W3DShaderManager dependent-resource creation, retail 0x000754DE..0x00075649
// (363 bytes, plain RET) and its EH handler 0x0075EF58. Original name unknown:
// W3DShaderManager::init (0x00077F80) calls it with no arguments at +0x0E; WB
// 0x7CEA80 is the same body with RefCountClass::Release_Ref's refcount.h:164
// assertion and the "Creating POOL_DEFAULT surface: W3DShaderManager::
// m_oldRenderSurface / m_renderTexture / m_newRenderSurface / m_oldDepthSurface"
// logs. Semantic donor: Open-BFME-1 W3DShaderManagerCreateResources.cpp
// (BfmeShaderShutdown::rva00716770), the counterpart of the rowed
// releaseDependentResources at 0x00076790.
// The quad vertex buffer is released through the global itself (REF_PTR_RELEASE
// with Release_Ref inlined), which keeps the object in EAX and gives retail's
// mov ecx,eax / add eax,4 counter address.

void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *) throw();

// Native dynamic vertex buffer, constructor rowed at 0x0013AC00 (0x20 bytes).
class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned type, unsigned short vertexCount, unsigned usage, unsigned vertexSize);
	virtual void Delete_This();
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
	unsigned type;
	unsigned short vertexCount;
	int engineReferences;
	void *format;
	bool usesDeclaration;
	void *buffer;
};

typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long HRESULT;

struct ShaderD3DSurfaceDesc
{
	DWORD Format;
	DWORD Type;
	DWORD Usage;
	DWORD Pool;
	DWORD MultiSampleType;
	DWORD MultiSampleQuality;
	UINT Width;
	UINT Height;
};

// Device slots used here (Direct3D 9 layout under the ledger's Direct3D 8
// spelling): CreateTexture (23, with the shared-handle argument),
// GetRenderTarget (38) and GetDepthStencilSurface (40).
struct IDirect3DDevice8
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual HRESULT __stdcall CreateTexture(UINT width, UINT height, UINT levels, DWORD usage,
		DWORD format, DWORD pool, struct IDirect3DTexture8 **texture, void **sharedHandle);
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual HRESULT __stdcall GetRenderTarget(UINT index, struct IDirect3DSurface8 **surface);
	virtual void slot39();
	virtual HRESULT __stdcall GetDepthStencilSurface(struct IDirect3DSurface8 **surface);
};

struct IDirect3DSurface8
{
	virtual void slot00(); virtual void slot01();
	virtual DWORD __stdcall Release();
	virtual void slot03(); virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11();
	virtual HRESULT __stdcall GetDesc(ShaderD3DSurfaceDesc *desc);
};

struct IDirect3DTexture8
{
	virtual void slot00(); virtual void slot01();
	virtual DWORD __stdcall Release();
	virtual void slot03(); virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual HRESULT __stdcall GetSurfaceLevel(UINT level, IDirect3DSurface8 **surface);
};

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
protected:
	static IDirect3DDevice8 *D3DDevice;
};

// Shader-manager render-to-texture globals at VA 0x009E1F64..0x009E1F70 and
// the quad vertex buffer / index at 0x009E1F7C / 0x009E1F80, spelled as the
// data ledger names them.
class W3DShaderManager
{
public:
	static IDirect3DSurface8 *m_oldRenderSurface;
	static IDirect3DTexture8 *m_renderTexture;
};
extern unsigned int g_Va009E1F6C;	// m_newRenderSurface
struct ShaderComResourceRef;
extern ShaderComResourceRef *rva012F9D10;	// m_oldDepthSurface
class VertexBufferClass;
extern VertexBufferClass *g_vb;
extern int g_quadIndex;

#define m_newRenderSurface (*(IDirect3DSurface8 **)&g_Va009E1F6C)
#define m_oldDepthSurface (*(IDirect3DSurface8 **)&rva012F9D10)
#define ShaderQuadBuffer (*(BfmeDynamicNativeVB **)&g_vb)

void __cdecl Rva000754DEInit()
{
	if (ShaderQuadBuffer) {
		ShaderQuadBuffer->Release_Ref();
		ShaderQuadBuffer = 0;
	}
	ShaderQuadBuffer = new BfmeDynamicNativeVB(0, 200, 1, 0x1C);
	g_quadIndex = 0;

	if (W3DShaderManager::m_oldRenderSurface || W3DShaderManager::m_renderTexture ||
		m_newRenderSurface || m_oldDepthSurface)
		return;

	DX8Wrapper::_Get_D3D_Device8()->GetRenderTarget(0, &W3DShaderManager::m_oldRenderSurface);
	ShaderD3DSurfaceDesc desc;
	W3DShaderManager::m_oldRenderSurface->GetDesc(&desc);
	HRESULT hr = DX8Wrapper::_Get_D3D_Device8()->CreateTexture(desc.Width, desc.Height, 1, 1,
		desc.Format, 0, &W3DShaderManager::m_renderTexture, 0);
	if (hr != 0) {
		if (W3DShaderManager::m_oldRenderSurface)
			W3DShaderManager::m_oldRenderSurface->Release();
		W3DShaderManager::m_oldRenderSurface = 0;
		W3DShaderManager::m_renderTexture = 0;
		return;
	}
	hr = W3DShaderManager::m_renderTexture->GetSurfaceLevel(0, &m_newRenderSurface);
	if (hr != 0) {
		if (W3DShaderManager::m_renderTexture)
			W3DShaderManager::m_renderTexture->Release();
		m_newRenderSurface = 0;
		W3DShaderManager::m_renderTexture = 0;
		return;
	}
	hr = DX8Wrapper::_Get_D3D_Device8()->GetDepthStencilSurface(&m_oldDepthSurface);
	if (hr != 0) {
		if (m_newRenderSurface)
			m_newRenderSurface->Release();
		if (W3DShaderManager::m_renderTexture)
			W3DShaderManager::m_renderTexture->Release();
		m_oldDepthSurface = 0;
		m_newRenderSurface = 0;
		W3DShaderManager::m_renderTexture = 0;
	}
}
