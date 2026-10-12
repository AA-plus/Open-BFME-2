// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva000EF7B8@Rva000EF7B8Texture@@UAEXH@Z, retail 0x000EF7B8..0x000EF876 (190 bytes, RET 4),
// the stage-apply entry of the texture class vtable at 0x007CEF60 (slot +0x18; its neighbours
// are the rowed texture-surface helpers). After the base apply step (rowed 0x00131CEA) it sets
// stage 0 to an unprojected, clamped (D3D9 sampler states through the device, slot +0x114),
// texture-times-diffuse colour with texture alpha, enables source-alpha blending and disables
// stage 1. The owning class and method names are not recovered.
struct IDirect3DDevice8
{
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68();
	virtual long __stdcall SetSamplerState(unsigned long sampler, unsigned long type, unsigned long value) = 0;
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned long state, unsigned value)
	{
		D3DDevice->SetSamplerState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_stage_state_changes;
};

class Rva00131CEAForwarder
{
public:
	void rva00131CEA(int stage);
};

class Rva000EF7B8Texture
{
public:
	virtual void rva000EF7B8(int stage);
};

void Rva000EF7B8Texture::rva000EF7B8(int stage)
{
	reinterpret_cast<Rva00131CEAForwarder *>(this)->rva00131CEA(stage);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 24, 0);		// TEXTURETRANSFORMFLAGS, DISABLE
	DX8Wrapper::Set_DX8_Sampler_State(0, 1, 3);			// ADDRESSU, CLAMP
	DX8Wrapper::Set_DX8_Sampler_State(0, 2, 3);			// ADDRESSV, CLAMP
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);		// COLORARG1, TEXTURE
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 0);		// COLORARG2, DIFFUSE
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);		// COLOROP, MODULATE
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 2);		// ALPHAOP, SELECTARG1
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0);		// TEXCOORDINDEX
	DX8Wrapper::Set_DX8_Render_State(27, 1);			// ALPHABLENDENABLE
	DX8Wrapper::Set_DX8_Render_State(19, 5);			// SRCBLEND, SRCALPHA
	DX8Wrapper::Set_DX8_Render_State(20, 6);			// DESTBLEND, INVSRCALPHA
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 1);		// stage 1 COLOROP, DISABLE
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 1);		// stage 1 ALPHAOP, DISABLE
}
