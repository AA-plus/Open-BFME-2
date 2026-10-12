// ?Render@RTS3DScene@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.97 date=2026-10-12
// ?Render@RTS3DScene@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.97 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
class Vector3 { public: float X, Y, Z; Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {} };
class RenderInfoClass;
class Overridable
{
public:
	virtual ~Overridable();
	__declspec(noinline) Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride; // +4
};
class WeatherSetting : public Overridable
{
public:
	char m_pad08[0x8C - 8];
	float fogR, fogG, fogB; // +0x8C
	bool fogEnabled; // +0x98
	char m_pad99[3];
	float fogStart; // +0x9C
	float fogEnd; // +0xA0
};
template <class T> class OVERRIDE { public: T *m_overridable; int m_pad04; int m_pad08; };
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern bool bfmeCameraProjectionOverride;
extern int g_lightCount; // 0xDB5FA0
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView { char gap[0x68]; bool enableBehindBuildingMarkers; };
class ShaderClass { protected: static bool ShaderDirty; public: static void Invalidate() { ShaderDirty = true; } };
class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static bool Has_Stencil();
	static unsigned Convert_Color(const Vector3 &color, float alpha);
	static bool FogEnable;
	static unsigned long FogColor;
	static float FogStart, FogEnd;
};
__forceinline unsigned DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;
	__asm
	{
		sub	esp,20
		fwait
		fstcw		[esp+16]
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)
		or			eax,(1024|2048)
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or		eax,ecx
		or		eax,ebx
		or		eax,edx
		fstp	st(0)
		cmp	edi,0
		je		not_changed
		fwait
		fldcw	[esp+16];
not_changed:
		add	esp,20
		mov	col,eax
	}
	return col;
}
__forceinline void Set_Fog(bool enable, const Vector3 &color, float start, float end)
{
	DX8Wrapper::FogEnable = enable;
	DX8Wrapper::FogColor = DX8Wrapper::Convert_Color(color, 0.0f);
	DX8Wrapper::FogStart = start;
	DX8Wrapper::FogEnd = end;
	ShaderClass::Invalidate();
	DX8Wrapper::Set_DX8_Render_State(36, *(unsigned *)(&start));
	DX8Wrapper::Set_DX8_Render_State(37, *(unsigned *)(&end));
}
class RTS3DScene
{
public:
	virtual void sceneSlot00();
	virtual void sceneSlot01();
	virtual void sceneSlot02();
	virtual void sceneSlot03();
	virtual void sceneSlot04();
	virtual void sceneSlot05();
	virtual void sceneSlot06();
	virtual void sceneSlot07();
	virtual void Set_Fog_Enable(bool enable);
	virtual void sceneSlot09();
	virtual void Set_Fog_Color(const Vector3 &color);
	virtual void sceneSlot0B();
	virtual void Set_Fog_Range(float start, float end);
	virtual void sceneSlot0D();
	virtual void sceneSlot0E();
	virtual void sceneSlot0F();
	virtual void sceneSlot10();
	virtual void sceneSlot11();
	virtual void sceneSlot12();
	virtual void sceneSlot13();
	virtual void sceneSlot14();
	virtual void sceneSlot15();
	virtual void sceneSlot16();
	virtual void Customized_Render(RenderInfoClass &rinfo);
	char gap04[0x18 - 0x04];
	int polygonMode; // +0x18
	bool fogEnabled; // +0x1C
	char gap1D[3];
	Vector3 fogColor; // +0x20
	float fogStart; // +0x2C
	float fogEnd; // +0x30
	char gap34[0x7EC - 0x34];
	int customPassMode; // +0x7EC
	virtual void Render(RenderInfoClass &rinfo);
	void Flush(RenderInfoClass &rinfo);
protected:
	void updateFixedLightEnvironments(RenderInfoClass &rinfo);
};

static __forceinline const WeatherSetting *weatherFinal(const WeatherSetting *p)
{
	if (!p)
		return 0;
	if (p->m_nextOverride)
		return (const WeatherSetting *)p->m_nextOverride->friend_getFinalOverride();
	return p;
}

#define WEATHER weatherFinal(TheWeatherSetting.m_overridable)
void RTS3DScene::Render(RenderInfoClass &rinfo)
{
	if (WEATHER)
	{
		Set_Fog_Enable(WEATHER->fogEnabled && !bfmeCameraProjectionOverride && g_lightCount >= 1);
		if (WEATHER->fogEnabled)
		{
			Set_Fog_Color(Vector3(WEATHER->fogR, WEATHER->fogG, WEATHER->fogB));
			Set_Fog_Range(WEATHER->fogStart, WEATHER->fogEnd);
		}
	}
	Set_Fog(fogEnabled, fogColor, fogStart, fogEnd);
	GlobalDataView *gd = (GlobalDataView *)TheWritableGlobalData;
	gd->enableBehindBuildingMarkers = gd->enableBehindBuildingMarkers && DX8Wrapper::Has_Stencil();
	if (polygonMode == 0)
	{
		if (customPassMode == 0 || customPassMode == 3 || customPassMode == 4)
			updateFixedLightEnvironments(rinfo);
		if (customPassMode == 0 || customPassMode == 3 || customPassMode == 4 || customPassMode == 5 || customPassMode == 6 || customPassMode == 7)
		{
			Customized_Render(rinfo);
			Flush(rinfo);
		}
	}
}
