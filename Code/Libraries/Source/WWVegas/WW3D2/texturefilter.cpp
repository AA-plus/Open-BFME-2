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
// BFME 2 delta against the donor: stage 0's DEFAULT entries are seeded with
// the NONE values before the caps tests, and the stage index is unsigned (the
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
	virtual long __stdcall SetTextureStageState(DWORD Stage, int Type, DWORD Value);
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
	const D3DCAPS8 &Get_DX8_Caps() const { return Caps; }
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
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }
	static void Set_DX8_Texture_Stage_State(unsigned int stage, int state, DWORD value)
	{
		D3DDevice->SetTextureStageState(stage, state, value);
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
enum { D3DTSS_MAXANISOTROPY = 10 };
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
		FILTER_TYPE_DEFAULT,
		FILTER_TYPE_BFME,	// BFME 2's fifth column (20-byte stage rows); not written here
		FILTER_TYPE_COUNT
	};
	enum TextureFilterMode
	{
		TEXTURE_FILTER_BILINEAR,
		TEXTURE_FILTER_TRILINEAR,
		TEXTURE_FILTER_ANISOTROPIC
	};
	static void _Init_Filters(TextureFilterMode texture_filter);
};

unsigned _MinTextureFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];
unsigned _MagTextureFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];
unsigned _MipMapFilters[MAX_TEXTURE_STAGES][TextureFilterClass::FILTER_TYPE_COUNT];

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

	_MinTextureFilters[0][FILTER_TYPE_DEFAULT]=D3DTEXF_POINT;
	_MagTextureFilters[0][FILTER_TYPE_DEFAULT]=D3DTEXF_POINT;
	_MipMapFilters[0][FILTER_TYPE_DEFAULT]=D3DTEXF_NONE;

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
		_MagTextureFilters[i][FILTER_TYPE_DEFAULT]=_MagTextureFilters[i][FILTER_TYPE_BEST];
		_MinTextureFilters[i][FILTER_TYPE_DEFAULT]=_MinTextureFilters[i][FILTER_TYPE_BEST];
		_MipMapFilters[i][FILTER_TYPE_DEFAULT]=_MipMapFilters[i][FILTER_TYPE_BEST];

		DX8Wrapper::Set_DX8_Texture_Stage_State(i,D3DTSS_MAXANISOTROPY,2);
	}
}
