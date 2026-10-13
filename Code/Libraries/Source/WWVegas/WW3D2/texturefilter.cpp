// cl: /O2 /arch:SSE /G7 /MD /EHsc
//
// texturefilter.cpp -- TextureFilterClass: the per-stage min/mag/mip filter
// tables every texture's filter indexes when it is applied.
//
// Source: Zero Hour GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp
// (KM 08/05/02). Target facts: _Init_Filters is retail 0x0013EB60 (420 bytes,
// RET), reached from DX8Wrapper::Do_Onetime_Device_Dependent_Inits (the rowed
// caller's REL32 names it). It fills the three 16-stage tables at VA
// 0x00DF3048 (min), 0x00DF3188 (mag) and 0x00DF32C8 (mip), 20-byte stage rows,
// reads the caps filter bits through DX8Wrapper::CurrentCaps (VA 0x00DEDA7C)
// and writes D3DTSS_MAXANISOTROPY = 2 for every stage straight through the
// device (VA 0x00DEDA34, vtable slot 0x114) with the two call counters.
// BFME 2 deltas against the donor: a fifth filter type sits before DEFAULT
// (DEFAULT is column 4, as the constructor and the _Set_Default_* setters
// write it); _Init_Filters seeds stage 0's column 3 with the NONE values where
// Zero Hour seeds DEFAULT, and its final loop copies BEST into DEFAULT
// (column 4, min before mag); stage indices are unsigned (the
// loops close on unsigned compares). The constant 1 stays in a register for
// the whole body (/G7 adds it to the counters and the stage index).

typedef unsigned long DWORD;

struct IDirect3DDevice8
{
#define BFME_DEVICE_SLOT(n) virtual void __stdcall slot##n(void);
	BFME_DEVICE_SLOT(0) BFME_DEVICE_SLOT(1) BFME_DEVICE_SLOT(2) BFME_DEVICE_SLOT(3)
	BFME_DEVICE_SLOT(4) BFME_DEVICE_SLOT(5) BFME_DEVICE_SLOT(6) BFME_DEVICE_SLOT(7)
	BFME_DEVICE_SLOT(8) BFME_DEVICE_SLOT(9) BFME_DEVICE_SLOT(10) BFME_DEVICE_SLOT(11)
	BFME_DEVICE_SLOT(12) BFME_DEVICE_SLOT(13) BFME_DEVICE_SLOT(14) BFME_DEVICE_SLOT(15)
	BFME_DEVICE_SLOT(16) BFME_DEVICE_SLOT(17) BFME_DEVICE_SLOT(18) BFME_DEVICE_SLOT(19)
	BFME_DEVICE_SLOT(20) BFME_DEVICE_SLOT(21) BFME_DEVICE_SLOT(22) BFME_DEVICE_SLOT(23)
	BFME_DEVICE_SLOT(24) BFME_DEVICE_SLOT(25) BFME_DEVICE_SLOT(26) BFME_DEVICE_SLOT(27)
	BFME_DEVICE_SLOT(28) BFME_DEVICE_SLOT(29) BFME_DEVICE_SLOT(30) BFME_DEVICE_SLOT(31)
	BFME_DEVICE_SLOT(32) BFME_DEVICE_SLOT(33) BFME_DEVICE_SLOT(34) BFME_DEVICE_SLOT(35)
	BFME_DEVICE_SLOT(36) BFME_DEVICE_SLOT(37) BFME_DEVICE_SLOT(38) BFME_DEVICE_SLOT(39)
	BFME_DEVICE_SLOT(40) BFME_DEVICE_SLOT(41) BFME_DEVICE_SLOT(42) BFME_DEVICE_SLOT(43)
	BFME_DEVICE_SLOT(44) BFME_DEVICE_SLOT(45) BFME_DEVICE_SLOT(46) BFME_DEVICE_SLOT(47)
	BFME_DEVICE_SLOT(48) BFME_DEVICE_SLOT(49) BFME_DEVICE_SLOT(50) BFME_DEVICE_SLOT(51)
	BFME_DEVICE_SLOT(52) BFME_DEVICE_SLOT(53) BFME_DEVICE_SLOT(54) BFME_DEVICE_SLOT(55)
	BFME_DEVICE_SLOT(56) BFME_DEVICE_SLOT(57) BFME_DEVICE_SLOT(58) BFME_DEVICE_SLOT(59)
	BFME_DEVICE_SLOT(60) BFME_DEVICE_SLOT(61) BFME_DEVICE_SLOT(62) BFME_DEVICE_SLOT(63)
	BFME_DEVICE_SLOT(64) BFME_DEVICE_SLOT(65) BFME_DEVICE_SLOT(66) BFME_DEVICE_SLOT(67)
	BFME_DEVICE_SLOT(68)
#undef BFME_DEVICE_SLOT
	virtual long __stdcall SetSamplerState(DWORD Sampler, int Type, DWORD Value);
};

// D3DCAPS8 up to TextureFilterCaps (+0x40); only the filter bits are read.
struct D3DCAPS8
{
	int DeviceType;
	unsigned int AdapterOrdinal;
	DWORD Caps;
	DWORD Caps2;
	DWORD Caps3;
	DWORD PresentationIntervals;
	DWORD CursorCaps;
	DWORD DevCaps;
	DWORD PrimitiveMiscCaps;
	DWORD RasterCaps;
	DWORD ZCmpCaps;
	DWORD SrcBlendCaps;
	DWORD DestBlendCaps;
	DWORD AlphaCmpCaps;
	DWORD ShadeCaps;
	DWORD TextureCaps;
	DWORD TextureFilterCaps;
};

class DX8Caps
{
public:
	__declspec(dllimport) __forceinline const D3DCAPS8 &Get_DX8_Caps() const { return Caps; }
private:
	// The ZH layout: the caps follow the two display limits (+0x08), so the
	// filter bits are read at +0x48 of DX8Wrapper::CurrentCaps.
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCAPS8 Caps;
};

extern unsigned int number_of_DX8_calls;

class DX8Wrapper
{
public:
	__declspec(dllimport) __forceinline static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }
	// BFME 2 renders through Direct3D 9: the filter states go to the sampler
	// (device slot 0x114) straight, with the two call counters.
	__declspec(dllimport) __forceinline static void Set_DX8_Sampler_State(unsigned int stage, int state, DWORD value)
	{
		D3DDevice->SetSamplerState(stage, state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static DX8Caps *CurrentCaps;
	static unsigned int texture_stage_state_changes;
};

enum { MAX_TEXTURE_STAGES = 16 };
enum { D3DTEXF_NONE = 0, D3DTEXF_POINT = 1, D3DTEXF_LINEAR = 2, D3DTEXF_ANISOTROPIC = 3 };
enum { D3DTADDRESS_WRAP = 1, D3DTADDRESS_CLAMP = 3 };
enum { D3DSAMP_ADDRESSU = 1, D3DSAMP_ADDRESSV = 2, D3DSAMP_MAGFILTER = 5, D3DSAMP_MINFILTER = 6, D3DSAMP_MIPFILTER = 7, D3DSAMP_MAXANISOTROPY = 10 };

enum MipCountType
{
	MIP_LEVELS_ALL=0,	// generate all mipmap levels down to 1x1 size
	MIP_LEVELS_1,		// no mipmapping at all (just one mip level)
	MIP_LEVELS_2,
	MIP_LEVELS_3,
	MIP_LEVELS_4,
	MIP_LEVELS_5,
	MIP_LEVELS_6,
	MIP_LEVELS_7,
	MIP_LEVELS_8,
	MIP_LEVELS_10,
	MIP_LEVELS_11,
	MIP_LEVELS_12,
	MIP_LEVELS_MAX
};
#define D3DPTFILTERCAPS_MINFLINEAR		0x00000200L
#define D3DPTFILTERCAPS_MINFANISOTROPIC	0x00000400L
#define D3DPTFILTERCAPS_MIPFLINEAR		0x00020000L
#define D3DPTFILTERCAPS_MAGFLINEAR		0x02000000L
#define D3DPTFILTERCAPS_MAGFANISOTROPIC	0x04000000L

class TextureFilterClass
{
public:
	enum FilterType
	{
		FILTER_TYPE_NONE,
		FILTER_TYPE_FAST,
		FILTER_TYPE_BEST,
		FILTER_TYPE_3,		// BFME 2 inserts a type before DEFAULT (20-byte stage rows);
					// _Init_Filters seeds stage 0's entry where Zero Hour seeds
					// DEFAULT. Its name is in neither binary.
		FILTER_TYPE_DEFAULT,	// 4: the constructor's and the _Set_Default_* column
		FILTER_TYPE_COUNT
	};
	enum TextureFilterMode
	{
		TEXTURE_FILTER_BILINEAR,
		TEXTURE_FILTER_TRILINEAR,
		TEXTURE_FILTER_ANISOTROPIC
	};
	enum TxtAddrMode
	{
		TEXTURE_ADDRESS_REPEAT=0,
		TEXTURE_ADDRESS_CLAMP
	};

	TextureFilterClass(MipCountType mip_level_count);
	void Apply(unsigned int stage);
	void Set_Mip_Mapping(FilterType mipmap);

	__declspec(dllimport) __forceinline TxtAddrMode Get_U_Addr_Mode(void) const { return UAddressMode; }
	__declspec(dllimport) __forceinline TxtAddrMode Get_V_Addr_Mode(void) const { return VAddressMode; }

	static void _Init_Filters(TextureFilterMode texture_filter);
	static void _Set_Default_Min_Filter(FilterType filter);
	static void _Set_Default_Mag_Filter(FilterType filter);
	static void _Set_Default_Mip_Filter(FilterType filter);

private:
	FilterType TextureMinFilter;
	FilterType TextureMagFilter;
	FilterType MipMapFilter;
	TxtAddrMode UAddressMode;
	TxtAddrMode VAddressMode;
};

unsigned _MinTextureFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];
unsigned _MagTextureFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];
unsigned _MipMapFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];

// Retail 0x0013EA00, 43 bytes. Called by the texture constructors and the
// shared fallback filter of TextureClass::Get_Filter.
TextureFilterClass::TextureFilterClass(MipCountType mip_level_count)
:	TextureMinFilter(FILTER_TYPE_DEFAULT),
	TextureMagFilter(FILTER_TYPE_DEFAULT),
	UAddressMode(TEXTURE_ADDRESS_REPEAT),
	VAddressMode(TEXTURE_ADDRESS_REPEAT)
{
	if (mip_level_count!=MIP_LEVELS_1)
	{
		MipMapFilter=FILTER_TYPE_DEFAULT;
	}
	else
	{
		MipMapFilter=FILTER_TYPE_NONE;
	}
}

// Retail 0x0013EA30, 291 bytes: the stage's min, mag and mip filters from the
// tables, then the U and V address modes.
void TextureFilterClass::Apply(unsigned int stage)
{
	DX8Wrapper::Set_DX8_Sampler_State(stage,D3DSAMP_MINFILTER,_MinTextureFilters[stage][TextureMinFilter]);
	DX8Wrapper::Set_DX8_Sampler_State(stage,D3DSAMP_MAGFILTER,_MagTextureFilters[stage][TextureMagFilter]);
	DX8Wrapper::Set_DX8_Sampler_State(stage,D3DSAMP_MIPFILTER,_MipMapFilters[stage][MipMapFilter]);

	switch (Get_U_Addr_Mode())
	{
	case TEXTURE_ADDRESS_REPEAT:
		DX8Wrapper::Set_DX8_Sampler_State(stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		break;

	case TEXTURE_ADDRESS_CLAMP:
		DX8Wrapper::Set_DX8_Sampler_State(stage, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		break;
	}

	switch (Get_V_Addr_Mode())
	{
	case TEXTURE_ADDRESS_REPEAT:
		DX8Wrapper::Set_DX8_Sampler_State(stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;

	case TEXTURE_ADDRESS_CLAMP:
		DX8Wrapper::Set_DX8_Sampler_State(stage, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
	}
}

void TextureFilterClass::_Init_Filters(TextureFilterMode filter_type)
{
	const D3DCAPS8& dx8caps=DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps();

	_MinTextureFilters[0][FILTER_TYPE_NONE]=D3DTEXF_POINT;
	_MagTextureFilters[0][FILTER_TYPE_NONE]=D3DTEXF_POINT;
	_MipMapFilters[0][FILTER_TYPE_NONE]=D3DTEXF_NONE;

	_MinTextureFilters[0][FILTER_TYPE_FAST]=D3DTEXF_LINEAR;
	_MagTextureFilters[0][FILTER_TYPE_FAST]=D3DTEXF_LINEAR;
	_MipMapFilters[0][FILTER_TYPE_FAST]=D3DTEXF_POINT;

	_MagTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_POINT;
	_MinTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_POINT;
	_MipMapFilters[0][FILTER_TYPE_BEST]=D3DTEXF_POINT;

	_MinTextureFilters[0][FILTER_TYPE_3]=D3DTEXF_POINT;
	_MagTextureFilters[0][FILTER_TYPE_3]=D3DTEXF_POINT;
	_MipMapFilters[0][FILTER_TYPE_3]=D3DTEXF_NONE;

	if (dx8caps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR) _MagTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_LINEAR;
	if (dx8caps.TextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR) _MinTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_LINEAR;

	// Set anisotropic filtering only if requested and available
	if (filter_type==TEXTURE_FILTER_ANISOTROPIC) {
		if (dx8caps.TextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC) _MagTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_ANISOTROPIC;
		if (dx8caps.TextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC) _MinTextureFilters[0][FILTER_TYPE_BEST]=D3DTEXF_ANISOTROPIC;
	}

	// Set linear mip filter only if requested trilinear or anisotropic, and linear available
	if (filter_type==TEXTURE_FILTER_ANISOTROPIC || filter_type==TEXTURE_FILTER_TRILINEAR) {
		if (dx8caps.TextureFilterCaps&D3DPTFILTERCAPS_MIPFLINEAR) _MipMapFilters[0][FILTER_TYPE_BEST]=D3DTEXF_LINEAR;
	}

	// For stages above zero, set best filter to the same as the stage zero, except if anisotropic
	unsigned int i;
	for (i=1;i<MAX_TEXTURE_STAGES;++i) {
		_MinTextureFilters[i][FILTER_TYPE_NONE]=_MinTextureFilters[i-1][FILTER_TYPE_NONE];
		_MagTextureFilters[i][FILTER_TYPE_NONE]=_MagTextureFilters[i-1][FILTER_TYPE_NONE];
		_MipMapFilters[i][FILTER_TYPE_NONE]=_MipMapFilters[i-1][FILTER_TYPE_NONE];

		_MinTextureFilters[i][FILTER_TYPE_FAST]=_MinTextureFilters[i-1][FILTER_TYPE_FAST];
		_MagTextureFilters[i][FILTER_TYPE_FAST]=_MagTextureFilters[i-1][FILTER_TYPE_FAST];
		_MipMapFilters[i][FILTER_TYPE_FAST]=_MipMapFilters[i-1][FILTER_TYPE_FAST];

		if (_MagTextureFilters[i-1][FILTER_TYPE_BEST]==D3DTEXF_ANISOTROPIC) {
			_MagTextureFilters[i][FILTER_TYPE_BEST]=D3DTEXF_LINEAR;
		}
		else {
			_MagTextureFilters[i][FILTER_TYPE_BEST]=_MagTextureFilters[i-1][FILTER_TYPE_BEST];
		}

		if (_MinTextureFilters[i-1][FILTER_TYPE_BEST]==D3DTEXF_ANISOTROPIC) {
			_MinTextureFilters[i][FILTER_TYPE_BEST]=D3DTEXF_LINEAR;
		}
		else {
			_MinTextureFilters[i][FILTER_TYPE_BEST]=_MinTextureFilters[i-1][FILTER_TYPE_BEST];
		}
		_MipMapFilters[i][FILTER_TYPE_BEST]=_MipMapFilters[i-1][FILTER_TYPE_BEST];
	}

	// Set default to best. The level of best filter mode is controlled by the input parameter.
	for (i=0;i<MAX_TEXTURE_STAGES;++i) {
		// Retail copies BEST into the DEFAULT column (+0x10, the column every filter
		// starts in), min before mag.
		_MinTextureFilters[i][FILTER_TYPE_DEFAULT]=_MinTextureFilters[i][FILTER_TYPE_BEST];
		_MagTextureFilters[i][FILTER_TYPE_DEFAULT]=_MagTextureFilters[i][FILTER_TYPE_BEST];
		_MipMapFilters[i][FILTER_TYPE_DEFAULT]=_MipMapFilters[i][FILTER_TYPE_BEST];

		DX8Wrapper::Set_DX8_Sampler_State(i,D3DSAMP_MAXANISOTROPY,2);
	}
}

// Retail 0x0013ED10, 10 bytes, the function after _Init_Filters; the linker
// folded the identical setters already rowed there (ICF).
void TextureFilterClass::Set_Mip_Mapping(FilterType mipmap)
{
	MipMapFilter=mipmap;
}

// Retail 0x0013ED20, 0x0013ED50 and 0x0013ED80, 38 bytes each: copy one filter
// type into every stage's DEFAULT column.
void TextureFilterClass::_Set_Default_Min_Filter(FilterType filter)
{
	for (unsigned int i=0;i<MAX_TEXTURE_STAGES;++i)
	{
		_MinTextureFilters[i][FILTER_TYPE_DEFAULT]=_MinTextureFilters[i][filter];
	}
}

void TextureFilterClass::_Set_Default_Mag_Filter(FilterType filter)
{
	for (unsigned int i=0;i<MAX_TEXTURE_STAGES;++i)
	{
		_MagTextureFilters[i][FILTER_TYPE_DEFAULT]=_MagTextureFilters[i][filter];
	}
}

void TextureFilterClass::_Set_Default_Mip_Filter(FilterType filter)
{
	for (unsigned int i=0;i<MAX_TEXTURE_STAGES;++i)
	{
		_MipMapFilters[i][FILTER_TYPE_DEFAULT]=_MipMapFilters[i][filter];
	}
}
