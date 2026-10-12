// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ?rva0013275A@TextureBaseClass@@QBEHXZ @ 0x0013275A (42B) and siblings 0x00132784/0x001327D8/0x00132802,
// plus 0x00132731 (41B, +0x0C, 0 when absent) and 0x0013282C (42B, +0x3C).
// Honest address-named const getters of TextureBaseClass following the proven
// Peek_D3D_Base_Texture pattern (flag via Is_Initialized/Init at vtable
// 0x28/0x2C then handle at +0x14) returning dword fields at +0x28/+0x2C/+0x34/+0x38.
// Proven by neighbours in texture.cpp and 14 callers; callees are virtuals.
class BFMETextureBaseVirtuals
{
public:
	virtual void Slot_0() = 0;
	virtual void Slot_1() = 0;
	virtual void Slot_2() = 0;
	virtual void Slot_3() = 0;
	virtual void Slot_4() = 0;
	virtual void Slot_5() = 0;
	virtual void Slot_6() = 0;
	virtual void Slot_7() = 0;
	virtual void Slot_8() = 0;
	virtual void Slot_9() = 0;
	virtual bool Is_Initialized() const = 0;
	virtual void Init() = 0;
};

class TextureBaseClass
{
public:
	int rva00132731() const;
	int rva0013275A() const;
	int rva00132784() const;
	int rva001327D8() const;
	int rva00132802() const;
	int rva0013282C() const;

private:
	BFMETextureBaseVirtuals *m_texture;
};

int TextureBaseClass::rva00132731() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 0;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0xc);
	return 0;
}

int TextureBaseClass::rva0013275A() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 1;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0x28);
	return 1;
}

int TextureBaseClass::rva00132784() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 1;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0x2c);
	return 1;
}

int TextureBaseClass::rva001327D8() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 1;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0x34);
	return 1;
}

int TextureBaseClass::rva00132802() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 1;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0x38);
	return 1;
}

int TextureBaseClass::rva0013282C() const
{
	BFMETextureBaseVirtuals *texture = *(BFMETextureBaseVirtuals *const *)this;
	if (texture == 0)
		return 1;
	if (!texture->Is_Initialized())
		texture->Init();
	void *handle = *(void **)((char *)texture + 0x14);
	if (handle != 0)
		return *(int *)((char *)handle + 0x3c);
	return 1;
}
