// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// GlobalData.cpp -- GlobalData members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's newOverride also copies the current data
// into the new override; BFME2's retail body only constructs a fresh
// GlobalData (0x1254 bytes, ctor 0x0023631C) and links it in front of the
// chain through m_next at +0x1250 (target evidence).

#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

typedef bool Bool;
// Canonical BFME2 subsystem layout: flag4 and name8,12B total.
#include "subsystem_interface.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base(); }
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *, unsigned int); }
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, unsigned int) const; }
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void __destroy<AsciiString *, AsciiString>(AsciiString *, AsciiString *, AsciiString *); }
namespace _STL { template <> void __destroy_aux<AsciiString *>(AsciiString *, AsciiString *, __false_type const &); }
// bfme link decl-only end
namespace _STL { template<> vector<AsciiString>::~vector(); }
class Rva00360D26Member { unsigned handle; public: Rva00360D26Member(); ~Rva00360D26Member(); };
// MultiPlayMults() (0x002358A2), Rva00236285() (0x00236285) and
// RGBColor::setFromInt (0x00004EDF) cannot throw. Retail's constructor stores
// no unwind state before calling them (the first two sit earlier in retail's
// own unit), so they are declared throw() here.
class Rva00236285 { char words[36]; public: Rva00236285() throw(); };
class Rva002362B4 : public Rva00236285 { public: ~Rva002362B4(); };
class Version { char words[48]; public: Version(); ~Version(); };
struct Rva004216D3Coord { float x,y,z; Rva004216D3Coord() {} ~Rva004216D3Coord() {} };
struct GlobalDataLightingView { Rva004216D3Coord ambient,diffuse,position; GlobalDataLightingView() {} };


extern "C" __declspec(dllimport) int __stdcall SHGetSpecialFolderPathW(void *owner, unsigned short *path, int folder, int create);
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryW(const unsigned short *path, void *security);

// TheGameText's vslot 15 (0x3C) looks a label up by its text.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;


enum TimeOfDay { TIME_OF_DAY_INVALID=-1 };
// The logic frame rate (data ledger owner of VA 0x00DBA4E4).
extern int g_Va00DBA4E4;
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4
extern "C" __declspec(dllimport) unsigned int __stdcall GetDoubleClickTime();
struct Rva00235A21 { char words[528]; Rva00235A21(); };
class Rva00235A37 { public: char words[48]; Rva00235A37 &operator=(const Rva00235A37&); };
extern Version *TheVersion;
struct MultiPlayMults { char words[480]; MultiPlayMults() throw(); };
struct RvaGDNoCleanupCoord { float x,y,z; RvaGDNoCleanupCoord() {} };
struct RvaGDConst3 { float x,y,z; RvaGDConst3(float v):x(v),y(v),z(v){} };
struct RvaGDConst2 { float x,y; RvaGDConst2(float v):x(v),y(v){} };
struct RGBColor { float red,green,blue; void setFromInt(int) throw(); };
// Inline-constructed subobjects of the constructor (retail: lea this, then the
// member stores). +D54 and +D68..+DA4 are {int 0, float 0, float 0}, the shape
// of BFME1's GameClientRandomVariable; +DB8..+DC8, +DEC/+DF4 and +E04..+E7C are
// two-int pairs. Original type names are unknown.
struct GDRandomVar { int m_type; float m_low, m_high; GDRandomVar():m_type(0),m_low(0),m_high(0){} };
struct GDPair { int a,b; GDPair(int x,int y):a(x),b(y){} };
struct RvaGDColor:RGBColor { RvaGDColor(int v) {setFromInt(v);} };

// The INI field parsers GlobalData's table names (all rowed elsewhere).
class INI
{
public:
 static void parseBool(INI *ini, void *instance, void *store, const void *userData);
 static void parseInt(INI *ini, void *instance, void *store, const void *userData);
 static void parseUnsignedByte(INI *ini, void *instance, void *store, const void *userData);
 static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
 static void parseReal(INI *ini, void *instance, void *store, const void *userData);
 static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
 static void parseAccelerationReal(INI *ini, void *instance, void *store, const void *userData);
 static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
 static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
 static void parseQuotedAsciiString(INI *ini, void *instance, void *store, const void *userData);
 static void parseAsciiStringVectorAppend(INI *ini, void *instance, void *store, const void *userData);
 static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
 static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);
 static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
 static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
 static void parseICoord2D(INI *ini, void *instance, void *store, const void *userData);
 static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
 static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);
 static void dup_002F0F7(INI *ini, void *instance, void *store, const void *userData);
};
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse { const char *token; INIFieldParseProc parse; const void *userData; int offset; };
class WeaponBonusSet
{
public:
 static void parseWeaponBonusSetPtr(INI *ini, void *instance, void *store, const void *userData);
};
void parseCommandPoints(INI *ini, void *instance, void *store, const void *userData);
void parseMultiPlayMoneyMult(INI *ini, void *instance, void *store, const void *userData);
void parseMultiPlayUnitXPMult(INI *ini, void *instance, void *store, const void *userData);
void parseMultiPlayBuildingXPMult(INI *ini, void *instance, void *store, const void *userData);
void parseMultiPlayUnitSpeedMult(INI *ini, void *instance, void *store, const void *userData);
void parseMultiPlayBuildingSpeedMult(INI *ini, void *instance, void *store, const void *userData);
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

// Zero Hour defines these two in this unit through DEFINE_TERRAIN_LOD_NAMES
// (TerrainVisual.h) and DEFINE_BODYDAMAGETYPE_NAMES (BodyModule.h), each a
// per-unit static; retail's copies are VA 0x00DBA470 (BFME 2 keeps ZH's ten
// names) and VA 0x00DBA444 (TerrainRoads has its own at 0x00DBCF30).
static const char *TerrainLODNames[] =
{
 "NONE", "MIN", "STRETCH_NO_CLOUDS", "HALF_CLOUDS", "NO_CLOUDS",
 "STRETCH_CLOUDS", "NO_WATER", "MAX", "AUTOMATIC", "DISABLE",
 0
};
static const char *TheBodyDamageTypeNames[] =
{
 "PRISTINE", "DAMAGED", "REALLYDAMAGED", "RUBBLE",
 0
};
// GameType.cpp (VA 0x00DBE958 / 0x00DBE974).
extern char *TimeOfDayNames[];
extern char *WeatherNames[];

class GlobalData:public SubsystemInterface {
public:
 GlobalData();
 bool setTimeOfDay(TimeOfDay);
 virtual ~GlobalData();
 virtual void init();
 virtual void reset();
 virtual void update();
 virtual bool vslot04(int);
 virtual int vslot06();
 static const FieldParse s_GlobalDataFieldParseTable[];
 static GlobalData *newOverride();
 AsciiString getPicturePath() const;
private: static GlobalData *m_theOriginal;
 AsciiString m_000C;
 AsciiString m_0010;
 AsciiString m_0014;
 AsciiString m_0018;
 bool m_001C;
 bool m_001D;
 char unknown001E[2];
 int m_0020;
 bool m_0024;
 bool m_0025;
 bool m_0026;
 bool m_0027;
 int m_0028;
 bool m_002C;
 bool m_002D;
 char unknown002E[2];
 int m_0030;
 int m_0034;
 int m_0038;
 bool m_003C;
 bool m_003D;
 bool m_003E;
 bool m_003F;
 bool m_0040;
 bool m_0041;
 char unknown0042[2];
 int m_0044;
 bool m_0048;
 bool m_0049;
 bool m_004A;
 bool m_004B;
 bool m_004C;
 bool m_004D;
 bool m_004E;
 char unknown004F[1];
 int m_0050;
 bool m_0054;
 char unknown0055[3];
 int m_0058;
 bool m_005C;
 bool m_005D;
 bool m_005E;
 bool m_005F;
 bool m_0060;
 bool m_0061;
 bool m_0062;
 char unknown0063[1];
 int m_0064;
 bool m_0068;
 char unknown0069[3];
 float m_006C;
 float m_0070;
 float m_0074;
 float m_0078;
 float m_007C;
 int m_0080;
 bool m_0084;
 bool m_0085;
 bool m_0086;
 bool m_0087;
 bool m_0088;
 char unknown0089[3];
 AsciiString m_008C;
 int m_0090;
 float m_0094;
 float m_0098;
 float m_009C;
 float m_00A0;
 float m_00A4;
 float m_00A8;
 float m_00AC;
 float m_00B0;
 float m_00B4;
 float m_00B8;
 float m_00BC;
 float m_00C0;
 float m_00C4;
 float m_00C8;
 int m_00CC;
 bool m_00D0;
 char unknown00D1[3];
 float m_00D4;
 float m_00D8;
 RvaGDConst3 m_00DC;
 RvaGDConst3 m_00E8;
 RvaGDConst2 m_00F4;
 RvaGDConst2 m_00FC;
 float m_0104;
 float m_0108;
 int m_010C;
 int m_0110;
 int m_0114;
 int m_0118;
 AsciiString m_011C;
 float m_0120;
 float m_0124;
 AsciiString m_0128;
 float m_012C;
 float m_0130;
 int m_0134;
 int m_0138;
 bool m_013C;
 bool m_013D;
 bool m_013E;
 bool m_013F;
 GlobalDataLightingView m_0140[18];
 GlobalDataLightingView m_03C8[18];
 GlobalDataLightingView m_0650[18];
 RvaGDNoCleanupCoord m_08D8[3];
 RvaGDNoCleanupCoord m_08FC[3];
 Rva004216D3Coord m_0920[3];
 RvaGDConst3 m_0944;
 float m_0950;
 float m_0954[8];
 int m_0974;
 int m_0978;
 int m_097C;
 int m_0980;
 float m_0984;
 int m_0988;
 int m_098C;
 int m_0990;
 int m_0994;
 int m_0998;
 bool m_099C;
 bool m_099D;
 bool m_099E;
 bool m_099F;
 bool m_09A0;
 bool m_09A1;
 bool m_09A2;
 bool m_09A3;
 bool m_09A4;
 bool m_09A5;
 bool m_09A6;
 bool m_09A7;
 float m_09A8;
 bool m_09AC;
 bool m_09AD;
 bool m_09AE;
 bool m_09AF;
 bool m_09B0;
 bool m_09B1;
 char unknown09B2[2];
 int m_09B4;
 int m_09B8;
 bool m_09BC;
 bool m_09BD;
 bool m_09BE;
 bool m_09BF;
 bool m_09C0;
 bool m_09C1;
 bool m_09C2;
 bool m_09C3;
 bool m_09C4;
 bool m_09C5;
 bool m_09C6;
 bool m_09C7;
 bool m_09C8;
 char unknown09C9[3];
 int m_09CC;
 bool m_09D0;
 bool m_09D1;
 bool m_09D2;
 char unknown09D3[1];
 int m_09D4;
 bool m_09D8;
 char unknown09D9[3];
 AsciiString m_09DC;
 AsciiString m_09E0;
 bool m_09E4;
 char unknown09E5[3];
 int m_09E8;
 float m_09EC;
 AsciiString m_09F0;
 AsciiString m_09F4;
 int m_09F8;
 AsciiString m_09FC;
 AsciiString m_0A00;
 int m_0A04;
 AsciiString m_0A08;
 AsciiString m_0A0C;
 int m_0A10;
 AsciiString m_0A14;
 AsciiString m_0A18;
 int m_0A1C;
 AsciiString m_0A20;
 AsciiString m_0A24;
 int m_0A28;
 AsciiString m_0A2C;
 AsciiString m_0A30;
 int m_0A34;
 AsciiString m_0A38;
 AsciiString m_0A3C;
 int m_0A40;
 int m_0A44;
 int m_0A48;
 int m_0A4C;
 bool m_0A50;
 char unknown0A51[3];
 int m_0A54;
 unsigned short m_0A58;
 char unknown0A5A[2];
 int m_0A5C;
 int m_0A60;
 float m_0A64;
 float m_0A68;
 float m_0A6C;
 float m_0A70;
 float m_0A74;
 float m_0A78;
 float m_0A7C;
 float m_0A80;
 float m_0A84;
 int m_0A88;
 float m_0A8C;
 float m_0A90;
 int m_0A94;
 int m_0A98;
 float m_0A9C;
 float m_0AA0;
 float m_0AA4;
 int m_0AA8;
 float m_0AAC;
 float m_0AB0;
 bool m_0AB4;
 bool m_0AB5;
 char unknown0AB6[2];
 AsciiString m_0AB8;
 AsciiString m_0ABC;
 AsciiString m_0AC0;
 bool m_0AC4;
 bool m_0AC5;
 char unknown0AC6[2];
 int m_0AC8;
 int m_0ACC;
 Rva00235A21* m_weaponBonusSet;
 float m_0AD4[4];
 float m_0AE4;
 float m_0AE8;
 AsciiString m_0AEC;
 bool m_0AF0;
 bool m_0AF1;
 bool m_0AF2;
 bool m_0AF3;
 bool m_0AF4;
 bool m_0AF5;
 char unknown0AF6[2];
 float m_0AF8;
 float m_0AFC;
 bool m_0B00;
 bool m_0B01;
 char unknown0B02[2];
 int m_0B04;
 Version m_0B08;
 int m_0B38;
 int m_0B3C;
 float m_0B40;
 int m_0B44;
 float m_0B48;
 float m_0B4C;
 int m_0B50;
 float m_0B54;
 bool m_0B58;
 char unknown0B59[3];
 float m_0B5C;
 float m_0B60;
 int m_0B64;
 bool m_0B68;
 bool m_0B69;
 bool m_0B6A;
 bool m_0B6B;
 bool m_0B6C;
 bool m_0B6D;
 bool m_0B6E;
 bool m_0B6F;
 bool m_0B70;
 bool m_0B71;
 char unknown0B72[2];
 float m_0B74;
 float m_0B78;
 float m_0B7C;
 float m_0B80;
 float m_0B84;
 float m_0B88;
 float m_0B8C;
 float m_0B90;
 float m_0B94;
 float m_0B98;
 int m_0B9C;
 int m_0BA0;
 AsciiString m_0BA4;
 _STL::vector<AsciiString> m_0BA8;
 bool m_0BB4;
 char unknown0BB5[7];
 bool m_0BBC;
 bool m_0BBD;
 char unknown0BBE[2];
 int m_0BC0;
 float m_0BC4;
 int m_0BC8;
 float m_0BCC;
 int m_0BD0;
 bool m_0BD4;
 char unknown0BD5[3];
 int m_0BD8;
 RvaGDColor m_0BDC;
 unsigned char m_0BE8;
 unsigned char m_0BE9;
 bool m_0BEA;
 char unknown0BEB[1];
 RvaGDColor m_0BEC;
 char unknown0BF8[12];
 unsigned char m_0C04;
 char unknown0C05[3];
 int m_0C08;
 int m_0C0C;
 int m_0C10;
 int m_0C14;
 int m_0C18;
 int m_0C1C;
 int m_0C20;
 int m_0C24;
 int m_0C28;
 float m_0C2C;
 int m_0C30;
 int m_0C34;
 float m_0C38;
 int m_0C3C;
 int m_0C40;
 float m_0C44;
 float m_0C48;
 float m_0C4C;
 float m_0C50;
 _STL::vector<AsciiString> m_0C54;
 int m_0C60;
 bool m_0C64;
 bool m_0C65;
 bool m_0C66;
 bool m_0C67;
 bool m_0C68;
 bool m_0C69;
 bool m_0C6A;
 bool m_0C6B;
 bool m_0C6C;
 bool m_0C6D;
 bool m_0C6E;
 bool m_0C6F;
 int m_0C70;
 bool m_0C74;
 bool m_0C75;
 char unknown0C76[2];
 int m_0C78;
 bool m_0C7C;
 bool m_0C7D;
 char unknown0C7E[2];
 int m_0C80;
 char unknown0C84[4];
 int m_0C88;
 bool m_0C8C;
 char unknown0C8D[3];
 int m_0C90;
 int m_0C94;
 bool m_0C98;
 char unknown0C99[3];
 int m_0C9C;
 int m_0CA0;
 bool m_0CA4;
 char unknown0CA5[39];
 bool m_0CCC;
 char unknown0CCD[3];
 float m_0CD0;
 int m_0CD4;
 char unknown0CD8[32];
 bool m_0CF8;
 bool m_0CF9;
 bool m_0CFA;
 bool m_0CFB;
 bool m_0CFC;
 bool m_0CFD;
 bool m_0CFE;
 bool m_0CFF;
 bool m_0D00;
 bool m_0D01;
 char unknown0D02[2];
 AsciiString m_0D04;
 AsciiString m_0D08;
 int m_0D0C;
 int m_0D10;
 int m_0D14;
 int m_0D18;
 int m_0D1C;
 int m_0D20;
 bool m_0D24;
 char unknown0D25[3];
 int m_0D28;
 bool m_0D2C;
 bool m_0D2D;
 bool m_0D2E;
 bool m_0D2F;
 AsciiString m_0D30;
 bool m_0D34;
 bool m_0D35;
 bool m_0D36;
 char unknown0D37[1];
 AsciiString m_0D38;
 AsciiString m_0D3C;
 float m_0D40;
 bool m_0D44;
 bool m_0D45;
 bool m_0D46;
 char unknown0D47[1];
 int m_0D48;
 AsciiString m_0D4C;
 int m_0D50;
 GDRandomVar m_0D54;
 char unknown0D60[4];
 int m_0D64;
 GDRandomVar m_0D68;
 GDRandomVar m_0D74;
 GDRandomVar m_0D80;
 GDRandomVar m_0D8C;
 GDRandomVar m_0D98;
 GDRandomVar m_0DA4;
 bool m_0DB0;
 char unknown0DB1[3];
 int m_0DB4;
 GDPair m_0DB8;
 GDPair m_0DC0;
 GDPair m_0DC8;
 bool m_0DD0;
 bool m_0DD1;
 char unknown0DD2[2];
 float m_0DD4;
 float m_0DD8;
 bool m_0DDC;
 char unknown0DDD[3];
 float m_0DE0;
 float m_0DE4;
 bool m_0DE8;
 char unknown0DE9[3];
 GDPair m_0DEC;
 GDPair m_0DF4;
 int m_0DFC;
 int m_0E00;
 GDPair m_0E04;
 GDPair m_0E0C;
 GDPair m_0E14;
 GDPair m_0E1C;
 GDPair m_0E24;
 GDPair m_0E2C;
 GDPair m_0E34;
 GDPair m_0E3C;
 GDPair m_0E44;
 GDPair m_0E4C;
 GDPair m_0E54;
 GDPair m_0E5C;
 GDPair m_0E64;
 GDPair m_0E6C;
 GDPair m_0E74;
 GDPair m_0E7C;
 int m_0E84;
 float m_0E88;
 int m_0E8C;
 int m_0E90;
 int m_0E94;
 float m_0E98;
 bool m_0E9C;
 bool m_0E9D;
 char unknown0E9E[2];
 int m_0EA0;
 bool m_0EA4;
 bool m_0EA5;
 bool m_0EA6;
 bool m_0EA7;
 float m_0EA8;
 float m_0EAC;
 Rva00360D26Member m_0EB0;
 Rva00360D26Member m_0EB4;
 Rva00360D26Member m_0EB8;
 Rva00360D26Member m_0EBC;
 Rva00360D26Member m_0EC0;
 MultiPlayMults m_0EC4;
 float m_10A4[20];
 _STL::vector<AsciiString> m_10F4;
 bool m_1100;
 char unknown1101[3];
 int m_1104;
 int m_1108;
 float m_110C;
 bool m_1110;
 bool m_1111;
 char unknown1112[2];
 Rva002362B4 m_1114;
 Rva002362B4 m_1138;
 int m_115C;
 int m_1160;
 int m_1164;
 Rva00360D26Member m_1168;
 float m_116C[20];
 bool m_11BC;
 char unknown11BD[3];
 int m_11C0;
 float m_11C4;
 bool m_11C8;
 bool m_11C9;
 bool m_11CA;
 bool m_11CB;
 int m_11CC;
 float m_11D0;
 float m_11D4;
 int m_11D8;
 int m_11DC;
 int m_11E0;
 float m_11E4;
 int m_11E8;
 int m_11EC;
 int m_11F0;
 int m_11F4;
 int m_11F8;
 int m_11FC;
 int m_1200;
 int m_1204;
 int m_1208;
 int m_120C;
 int m_1210;
 int m_1214;
 int m_1218;
 int m_121C;
 char unknown1220[4];
 float m_1224;
 int m_1228;
 int m_122C;
 int m_1230;
 int m_1234;
 int m_1238;
 bool m_123C;
 bool m_123D;
 char unknown123E[2];
 AsciiString m_1240;
 UnicodeString m_1244;
 AsciiString m_picturePath;
 AsciiString m_124C;
 GlobalData* m_next;
};

// TheWritableGlobalData, VA 0x00DFE758.
extern GlobalData *TheWritableGlobalData;

// GlobalData::newOverride, retail 0x00237A6B.
GlobalData *GlobalData::newOverride()
{
	GlobalData *override = new GlobalData;
	override->m_next = TheWritableGlobalData;
	TheWritableGlobalData = override;
	return override;
}

// GlobalData::getPicturePath, retail 0x0023611A: the folder the create-a-hero
// screen saves pictures to. The first call makes it, the user's My Pictures
// (CSIDL_MYPICTURES, 0x27) plus the localised "APPDATA:PictureFolder", and
// records it in TheWritableGlobalData.
AsciiString GlobalData::getPicturePath() const
{
	if (((const StringBase<char> *)&m_picturePath)->isEmpty() && TheGameText)
	{
		unsigned short path[260];
		if (SHGetSpecialFolderPathW(0, path, 0x27, 1))
		{
			UnicodeString folder = TheGameText->fetch("APPDATA:PictureFolder");
			if (path[wcslen(path) - 1] != L'\\')
				wcscat(path, L"\\");
			wcscat(path, folder.str());
			wcscat(path, L"\\");
			CreateDirectoryW(path, 0);
			TheWritableGlobalData->m_picturePath = UnicodeString(path);
		}
	}
	return m_picturePath;
}

// BFME1 donor2f243e26 GlobalDataDestructor.cpp supplies the cleanup purpose;
// WBBA5220 independently names the target destructor. Native2376CC..237A6B,
// 927B, has54 member cleanup states plus the12B subsystem base. Native array
// callbacks atB3FD0 are empty; the36B lighting shape is established separately
// by setTimeOfDay and ZH GlobalData::TerrainLighting. Unknown fields retain
// offset names and padding. No explicit member-destructor calls or vptr stores.
GlobalData *GlobalData::m_theOriginal=0;
GlobalData::~GlobalData()
{
 if(m_weaponBonusSet) ::operator delete(m_weaponBonusSet);
 m_weaponBonusSet=0;
 if(m_theOriginal==this) { m_theOriginal=0;TheWritableGlobalData=0; }
}

// Primary tableBED1C4 slot9 independently identifies reset. Native52B
// uses global delete so the virtual destructor receives flag0, then memory
// is released by the existing global operator delete.
void GlobalData::reset()
{
 while(TheWritableGlobalData!=m_theOriginal) {
  GlobalData *next=TheWritableGlobalData->m_next;
  ::delete TheWritableGlobalData;
  TheWritableGlobalData=next;
 }
}

// Table BED1C4: reload notice slot4 and literal-preserving table getter slot6.
// Slots1 and10 are empty; original names of slots4/6 remain unknown.

class InGameUI { public:
 virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
 virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
 virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
 virtual void message(UnicodeString format,...);
};
extern InGameUI *TheInGameUI;
bool GlobalData::vslot04(int reason)
{
 if(loadIniFilesFromLegend()) {
  if(TheInGameUI) TheInGameUI->message(UnicodeString(L"RIF: GameData reloaded (changes are effective immediately)"));
  return true;
 }
 return false;
}

// GlobalData::s_GlobalDataFieldParseTable, retail VA 0x00BE8520 (457 fields
// and a null record, 0x1CA0 bytes): the function at 0x00237AB1 (unrowed) loads
// it (data_xrefs), and slot 6 returns it. Tokens, parsers, userData and offsets are
// retail's; the token names and the ZH table name (GlobalData.cpp) say what
// each offset-named member holds.
const FieldParse GlobalData::s_GlobalDataFieldParseTable[] =
{
	{ "Windowed", INI::parseBool, 0, 0x002C },
	{ "XResolution", INI::parseInt, 0, 0x0030 },
	{ "YResolution", INI::parseInt, 0, 0x0034 },
	{ "MapName", INI::parseAsciiString, 0, 0x000C },
	{ "MoveHintName", INI::parseAsciiString, 0, 0x0010 },
	{ "GenericDamageFieldName", INI::parseAsciiString, 0, 0x0014 },
	{ "GenericDamageWarningName", INI::parseAsciiString, 0, 0x0018 },
	{ "ShowProps", INI::parseBool, 0, 0x001C },
	{ "UseFPSLimit", INI::parseBool, 0, 0x0026 },
	{ "PushAsideShrubs", INI::parseBool, 0, 0x001D },
	{ "DumpAssetUsage", INI::parseBool, 0, 0x0027 },
	{ "FramesPerSecondLimit", INI::parseInt, 0, 0x0028 },
	{ "MaxShellScreens", INI::parseInt, 0, 0x0038 },
	{ "UseCloudMap", INI::parseBool, 0, 0x003C },
	{ "ShowWater", INI::parseBool, 0, 0x003D },
	{ "ShowRoads", INI::parseBool, 0, 0x003E },
	{ "ShowTrees", INI::parseBool, 0, 0x003F },
	{ "AllowTreeFading", INI::parseBool, 0, 0x0040 },
	{ "UseLightMap", INI::parseBool, 0, 0x0048 },
	{ "AdjustCliffTextures", INI::parseBool, 0, 0x004B },
	{ "Use3WayTerrainBlends", INI::parseInt, 0, 0x0044 },
	{ "StretchTerrain", INI::parseBool, 0, 0x004C },
	{ "UseHalfHeightMap", INI::parseBool, 0, 0x004D },
	{ "UserDataLeafName", INI::parseQuotedAsciiString, 0, 0x124C },
	{ "UseReverseMouseScroll", INI::parseBool, 0, 0x0041 },
	{ "PlanningModeEnabled", INI::parseBool, 0, 0x11CA },
	{ "LiveCampaignMode", INI::parseBool, 0, 0x0086 },
	{ "HideLivingWorldRegions", INI::parseBool, 0, 0x0087 },
	{ "LivingWorldCampaignOverrride", INI::parseBool, 0, 0x008C },
	{ "LivingWorldTurbo", INI::parseBool, 0, 0x0088 },
	{ "DrawEntireTerrain", INI::parseBool, 0, 0x004E },
	{ "TerrainLOD", INI::parseIndexList, TerrainLODNames, 0x0050 },
	{ "TerrainLODTargetTimeMS", INI::parseInt, 0, 0x0058 },
	{ "RightMouseAlwaysScrolls", INI::parseBool, 0, 0x005D },
	{ "UseCloudPlane", INI::parseBool, 0, 0x005F },
	{ "DownwindAngle", INI::parseReal, 0, 0x0094 },
	{ "UseShadowVolumes", INI::parseBool, 0, 0x0060 },
	{ "UseShadowDecals", INI::parseBool, 0, 0x0061 },
	{ "UseShadowMapping", INI::parseBool, 0, 0x0062 },
	{ "ShowSelectedUnitMarker", INI::parseBool, 0, 0x09A5 },
	{ "UseSimpleHordeDecals", INI::parseBool, 0, 0x09A6 },
	{ "UseSimpleMergeDecals", INI::parseBool, 0, 0x09A7 },
	{ "OpacityOfSimpleMergeDecals", INI::parsePercentToReal, 0, 0x09A8 },
	{ "UseBehindBuildingMarker", INI::parseBool, 0, 0x0068 },
	{ "WaterPositionX", INI::parseReal, 0, 0x006C },
	{ "WaterPositionY", INI::parseReal, 0, 0x0070 },
	{ "WaterPositionZ", INI::parseReal, 0, 0x0074 },
	{ "WaterExtentX", INI::parseReal, 0, 0x0078 },
	{ "WaterExtentY", INI::parseReal, 0, 0x007C },
	{ "WaterType", INI::parseInt, 0, 0x0080 },
	{ "FeatherWater", INI::parseInt, 0, 0x0090 },
	{ "ShowSoftWaterEdge", INI::parseBool, 0, 0x0084 },
	{ "DefaultUnitHealingBuffFxList", INI::parseAsciiString, 0, 0x09DC },
	{ "DefaultStructureRepairBuffFxList", INI::parseAsciiString, 0, 0x09E0 },
	{ "TimeAfterDamageUntilRepairAllowed", INI::parseUnsignedInt, 0, 0x0A88 },
	{ "DrawSkyBox", INI::parseBool, 0, 0x0098 },
	{ "DefaultCameraMinHeight", INI::parseReal, 0, 0x009C },
	{ "DefaultCameraMaxHeight", INI::parseReal, 0, 0x00A0 },
	{ "DefaultCameraPitchAngle", INI::parseReal, 0, 0x00A4 },
	{ "DefaultCameraYawAngle", INI::parseReal, 0, 0x00A8 },
	{ "DefaultCameraScrollSpeedScalar", INI::parseReal, 0, 0x00AC },
	{ "CameraLockHeightDelta", INI::parseReal, 0, 0x0DD4 },
	{ "CameraEaseFactor", INI::parseReal, 0, 0x0DE0 },
	{ "TerrainHeightAtEdgeOfMap", INI::parseReal, 0, 0x00B0 },
	{ "UnitDamagedThreshold", INI::parseReal, 0, 0x00B4 },
	{ "UnitReallyDamagedThreshold", INI::parseReal, 0, 0x00B8 },
	{ "GroundStiffness", INI::parseReal, 0, 0x00BC },
	{ "StructureStiffness", INI::parseReal, 0, 0x00C0 },
	{ "Gravity", INI::parseAccelerationReal, 0, 0x00C4 },
	{ "StealthFriendlyOpacity", INI::parsePercentToReal, 0, 0x00C8 },
	{ "DefaultOcclusionDelay", INI::parseDurationUnsignedInt, 0, 0x00CC },
	{ "PartitionCellSize", INI::parseReal, 0, 0x00D4 },
	{ "TerrainResourceCellSize", INI::parseReal, 0, 0x00D8 },
	{ "AmmoPipScaleFactor", INI::parseReal, 0, 0x0104 },
	{ "ContainerPipScaleFactor", INI::parseReal, 0, 0x0108 },
	{ "AmmoPipWorldOffset", INI::parseCoord3D, 0, 0x00DC },
	{ "ContainerPipWorldOffset", INI::parseCoord3D, 0, 0x00E8 },
	{ "AmmoPipScreenOffset", INI::parseCoord2D, 0, 0x00F4 },
	{ "ContainerPipScreenOffset", INI::parseCoord2D, 0, 0x00FC },
	{ "MaxTerrainTracks", INI::parseInt, 0, 0x010C },
	{ "TimeOfDay", INI::parseIndexList, TimeOfDayNames, 0x0134 },
	{ "Weather", INI::parseIndexList, WeatherNames, 0x0138 },
	{ "MakeTrackMarks", INI::parseBool, 0, 0x013C },
	{ "HideGarrisonFlags", INI::parseBool, 0, 0x013D },
	{ "ForceModelsToFollowTimeOfDay", INI::parseBool, 0, 0x013E },
	{ "ForceModelsToFollowWeather", INI::parseBool, 0, 0x013F },
	{ "LevelGainAnimationName", INI::parseAsciiString, 0, 0x011C },
	{ "LevelGainAnimationTime", INI::parseReal, 0, 0x0120 },
	{ "LevelGainAnimationZRise", INI::parseReal, 0, 0x0124 },
	{ "GetHealedAnimationName", INI::parseAsciiString, 0, 0x0128 },
	{ "GetHealedAnimationTime", INI::parseReal, 0, 0x012C },
	{ "GetHealedAnimationZRise", INI::parseReal, 0, 0x0130 },
	{ "TerrainLightingMorningAmbient", INI::parseRGBColor, 0, 0x01AC },
	{ "TerrainLightingMorningDiffuse", INI::parseRGBColor, 0, 0x01B8 },
	{ "TerrainLightingMorningLightPos", INI::parseCoord3D, 0, 0x01C4 },
	{ "TerrainLightingAfternoonAmbient", INI::parseRGBColor, 0, 0x0218 },
	{ "TerrainLightingAfternoonDiffuse", INI::parseRGBColor, 0, 0x0224 },
	{ "TerrainLightingAfternoonLightPos", INI::parseCoord3D, 0, 0x0230 },
	{ "TerrainLightingEveningAmbient", INI::parseRGBColor, 0, 0x0284 },
	{ "TerrainLightingEveningDiffuse", INI::parseRGBColor, 0, 0x0290 },
	{ "TerrainLightingEveningLightPos", INI::parseCoord3D, 0, 0x029C },
	{ "TerrainLightingNightAmbient", INI::parseRGBColor, 0, 0x02F0 },
	{ "TerrainLightingNightDiffuse", INI::parseRGBColor, 0, 0x02FC },
	{ "TerrainLightingNightLightPos", INI::parseCoord3D, 0, 0x0308 },
	{ "TerrainObjectsLightingMorningAmbient", INI::parseRGBColor, 0, 0x0434 },
	{ "TerrainObjectsLightingMorningDiffuse", INI::parseRGBColor, 0, 0x0440 },
	{ "TerrainObjectsLightingMorningLightPos", INI::parseCoord3D, 0, 0x044C },
	{ "TerrainObjectsLightingAfternoonAmbient", INI::parseRGBColor, 0, 0x04A0 },
	{ "TerrainObjectsLightingAfternoonDiffuse", INI::parseRGBColor, 0, 0x04AC },
	{ "TerrainObjectsLightingAfternoonLightPos", INI::parseCoord3D, 0, 0x04B8 },
	{ "TerrainObjectsLightingEveningAmbient", INI::parseRGBColor, 0, 0x050C },
	{ "TerrainObjectsLightingEveningDiffuse", INI::parseRGBColor, 0, 0x0518 },
	{ "TerrainObjectsLightingEveningLightPos", INI::parseCoord3D, 0, 0x0524 },
	{ "TerrainObjectsLightingNightAmbient", INI::parseRGBColor, 0, 0x0578 },
	{ "TerrainObjectsLightingNightDiffuse", INI::parseRGBColor, 0, 0x0584 },
	{ "TerrainObjectsLightingNightLightPos", INI::parseCoord3D, 0, 0x0590 },
	{ "TerrainLightingMorningAmbient2", INI::parseRGBColor, 0, 0x01D0 },
	{ "TerrainLightingMorningDiffuse2", INI::parseRGBColor, 0, 0x01DC },
	{ "TerrainLightingMorningLightPos2", INI::parseCoord3D, 0, 0x01E8 },
	{ "TerrainLightingAfternoonAmbient2", INI::parseRGBColor, 0, 0x023C },
	{ "TerrainLightingAfternoonDiffuse2", INI::parseRGBColor, 0, 0x0248 },
	{ "TerrainLightingAfternoonLightPos2", INI::parseCoord3D, 0, 0x0254 },
	{ "TerrainLightingEveningAmbient2", INI::parseRGBColor, 0, 0x02A8 },
	{ "TerrainLightingEveningDiffuse2", INI::parseRGBColor, 0, 0x02B4 },
	{ "TerrainLightingEveningLightPos2", INI::parseCoord3D, 0, 0x02C0 },
	{ "TerrainLightingNightAmbient2", INI::parseRGBColor, 0, 0x0314 },
	{ "TerrainLightingNightDiffuse2", INI::parseRGBColor, 0, 0x0320 },
	{ "TerrainLightingNightLightPos2", INI::parseCoord3D, 0, 0x032C },
	{ "TerrainObjectsLightingMorningAmbient2", INI::parseRGBColor, 0, 0x0458 },
	{ "TerrainObjectsLightingMorningDiffuse2", INI::parseRGBColor, 0, 0x0464 },
	{ "TerrainObjectsLightingMorningLightPos2", INI::parseCoord3D, 0, 0x0470 },
	{ "TerrainObjectsLightingAfternoonAmbient2", INI::parseRGBColor, 0, 0x04C4 },
	{ "TerrainObjectsLightingAfternoonDiffuse2", INI::parseRGBColor, 0, 0x04D0 },
	{ "TerrainObjectsLightingAfternoonLightPos2", INI::parseCoord3D, 0, 0x04DC },
	{ "TerrainObjectsLightingEveningAmbient2", INI::parseRGBColor, 0, 0x0530 },
	{ "TerrainObjectsLightingEveningDiffuse2", INI::parseRGBColor, 0, 0x053C },
	{ "TerrainObjectsLightingEveningLightPos2", INI::parseCoord3D, 0, 0x0548 },
	{ "TerrainObjectsLightingNightAmbient2", INI::parseRGBColor, 0, 0x059C },
	{ "TerrainObjectsLightingNightDiffuse2", INI::parseRGBColor, 0, 0x05A8 },
	{ "TerrainObjectsLightingNightLightPos2", INI::parseCoord3D, 0, 0x05B4 },
	{ "TerrainLightingMorningAmbient3", INI::parseRGBColor, 0, 0x01F4 },
	{ "TerrainLightingMorningDiffuse3", INI::parseRGBColor, 0, 0x0200 },
	{ "TerrainLightingMorningLightPos3", INI::parseCoord3D, 0, 0x020C },
	{ "TerrainLightingAfternoonAmbient3", INI::parseRGBColor, 0, 0x0260 },
	{ "TerrainLightingAfternoonDiffuse3", INI::parseRGBColor, 0, 0x026C },
	{ "TerrainLightingAfternoonLightPos3", INI::parseCoord3D, 0, 0x0278 },
	{ "TerrainLightingEveningAmbient3", INI::parseRGBColor, 0, 0x02CC },
	{ "TerrainLightingEveningDiffuse3", INI::parseRGBColor, 0, 0x02D8 },
	{ "TerrainLightingEveningLightPos3", INI::parseCoord3D, 0, 0x02E4 },
	{ "TerrainLightingNightAmbient3", INI::parseRGBColor, 0, 0x0338 },
	{ "TerrainLightingNightDiffuse3", INI::parseRGBColor, 0, 0x0344 },
	{ "TerrainLightingNightLightPos3", INI::parseCoord3D, 0, 0x0350 },
	{ "TerrainObjectsLightingMorningAmbient3", INI::parseRGBColor, 0, 0x047C },
	{ "TerrainObjectsLightingMorningDiffuse3", INI::parseRGBColor, 0, 0x0488 },
	{ "TerrainObjectsLightingMorningLightPos3", INI::parseCoord3D, 0, 0x0494 },
	{ "TerrainObjectsLightingAfternoonAmbient3", INI::parseRGBColor, 0, 0x04E8 },
	{ "TerrainObjectsLightingAfternoonDiffuse3", INI::parseRGBColor, 0, 0x04F4 },
	{ "TerrainObjectsLightingAfternoonLightPos3", INI::parseCoord3D, 0, 0x0500 },
	{ "TerrainObjectsLightingEveningAmbient3", INI::parseRGBColor, 0, 0x0554 },
	{ "TerrainObjectsLightingEveningDiffuse3", INI::parseRGBColor, 0, 0x0560 },
	{ "TerrainObjectsLightingEveningLightPos3", INI::parseCoord3D, 0, 0x056C },
	{ "TerrainObjectsLightingNightAmbient3", INI::parseRGBColor, 0, 0x05C0 },
	{ "TerrainObjectsLightingNightDiffuse3", INI::parseRGBColor, 0, 0x05CC },
	{ "TerrainObjectsLightingNightLightPos3", INI::parseCoord3D, 0, 0x05D8 },
	{ "NumberGlobalLights", INI::parseInt, 0, 0x0988 },
	{ "MaxTranslucentObjects", INI::parseInt, 0, 0x0974 },
	{ "OccludedColorLuminanceScale", INI::parseReal, 0, 0x0984 },
	{ "MaxRoadSegments", INI::parseInt, 0, 0x098C },
	{ "MaxRoadVertex", INI::parseInt, 0, 0x0990 },
	{ "MaxRoadIndex", INI::parseInt, 0, 0x0994 },
	{ "MaxRoadTypes", INI::parseInt, 0, 0x0998 },
	{ "ValuePerSupplyBox", INI::parseInt, 0, 0x0A5C },
	{ "SupplyBoxesPerTree", INI::parseInt, 0, 0x0A60 },
	{ "AudioOn", INI::parseBool, 0, 0x099C },
	{ "MusicOn", INI::parseBool, 0, 0x099D },
	{ "AmbientStreamsOn", INI::parseBool, 0, 0x09A1 },
	{ "SoundsOn", INI::parseBool, 0, 0x099E },
	{ "Sounds3DOn", INI::parseBool, 0, 0x099F },
	{ "SpeechOn", INI::parseBool, 0, 0x09A0 },
	{ "VideoOn", INI::parseBool, 0, 0x09A3 },
	{ "DisableCameraMovements", INI::parseBool, 0, 0x09A4 },
	{ "UseCameraInReplay", INI::parseBool, 0, 0x0B71 },
	{ "DebugAI", INI::parseBool, 0, 0x09B8 },
	{ "DebugAIObstacles", INI::parseBool, 0, 0x09BC },
	{ "ShowClientPhysics", INI::parseBool, 0, 0x09B0 },
	{ "ShowTerrainNormals", INI::parseBool, 0, 0x09B1 },
	{ "ShowObjectHealth", INI::parseBool, 0, 0x09BD },
	{ "ShowTooltips", INI::parseBool, 0, 0x09BF },
	{ "ParticleScale", INI::parseReal, 0, 0x09EC },
	{ "AutoFireParticleSmallPrefix", INI::parseAsciiString, 0, 0x09F0 },
	{ "AutoFireParticleSmallSystem", INI::parseAsciiString, 0, 0x09F4 },
	{ "AutoFireParticleSmallMax", INI::parseInt, 0, 0x09F8 },
	{ "AutoFireParticleMediumPrefix", INI::parseAsciiString, 0, 0x09FC },
	{ "AutoFireParticleMediumSystem", INI::parseAsciiString, 0, 0x0A00 },
	{ "AutoFireParticleMediumMax", INI::parseInt, 0, 0x0A04 },
	{ "AutoFireParticleLargePrefix", INI::parseAsciiString, 0, 0x0A08 },
	{ "AutoFireParticleLargeSystem", INI::parseAsciiString, 0, 0x0A0C },
	{ "AutoFireParticleLargeMax", INI::parseInt, 0, 0x0A10 },
	{ "AutoSmokeParticleSmallPrefix", INI::parseAsciiString, 0, 0x0A14 },
	{ "AutoSmokeParticleSmallSystem", INI::parseAsciiString, 0, 0x0A18 },
	{ "AutoSmokeParticleSmallMax", INI::parseInt, 0, 0x0A1C },
	{ "AutoSmokeParticleMediumPrefix", INI::parseAsciiString, 0, 0x0A20 },
	{ "AutoSmokeParticleMediumSystem", INI::parseAsciiString, 0, 0x0A24 },
	{ "AutoSmokeParticleMediumMax", INI::parseInt, 0, 0x0A28 },
	{ "AutoSmokeParticleLargePrefix", INI::parseAsciiString, 0, 0x0A2C },
	{ "AutoSmokeParticleLargeSystem", INI::parseAsciiString, 0, 0x0A30 },
	{ "AutoSmokeParticleLargeMax", INI::parseInt, 0, 0x0A34 },
	{ "AutoAflameParticlePrefix", INI::parseAsciiString, 0, 0x0A38 },
	{ "AutoAflameParticleSystem", INI::parseAsciiString, 0, 0x0A3C },
	{ "AutoAflameParticleMax", INI::parseInt, 0, 0x0A40 },
	{ "BuildSpeed", INI::parseReal, 0, 0x0A64 },
	{ "MinDistFromEdgeOfMapForBuild", INI::parseReal, 0, 0x0A68 },
	{ "SupplyBuildBorder", INI::parseReal, 0, 0x0A6C },
	{ "AllowedHeightVariationForBuilding", INI::parseReal, 0, 0x0A70 },
	{ "MinLowEnergyProductionSpeed", INI::parseReal, 0, 0x0A74 },
	{ "MaxLowEnergyProductionSpeed", INI::parseReal, 0, 0x0A78 },
	{ "LowEnergyPenaltyModifier", INI::parseReal, 0, 0x0A7C },
	{ "MultipleFactory", INI::parseReal, 0, 0x0A80 },
	{ "RefundPercent", INI::parsePercentToReal, 0, 0x0A84 },
	{ "CommandCenterHealRange", INI::parseReal, 0, 0x0A8C },
	{ "CommandCenterHealAmount", INI::parseReal, 0, 0x0A90 },
	{ "MaxLineBuildObjects", INI::parseInt, 0, 0x0A94 },
	{ "MaxTunnelCapacity", INI::parseInt, 0, 0x0A98 },
	{ "MaxParticleCount", INI::parseInt, 0, 0x0AC8 },
	{ "MaxFieldParticleCount", INI::parseInt, 0, 0x0ACC },
	{ "HorizontalScrollSpeedFactor", INI::parseReal, 0, 0x0A9C },
	{ "VerticalScrollSpeedFactor", INI::parseReal, 0, 0x0AA0 },
	{ "ScreenEdgeScrollSpeedFactor", INI::parseReal, 0, 0x0AA4 },
	{ "ScreenEdgeScrollRampTime", INI::dup_002F0F7, 0, 0x0AA8 },
	{ "ScrollAmountCutoff", INI::parseReal, 0, 0x0AAC },
	{ "CameraAdjustSpeed", INI::parseReal, 0, 0x0AB0 },
	{ "EnforceMaxCameraHeight", INI::parseBool, 0, 0x0AB4 },
	{ "KeyboardScrollSpeedFactor", INI::parseReal, 0, 0x0AF8 },
	{ "KeyboardDefaultScrollSpeedFactor", INI::parseReal, 0, 0x0AFC },
	{ "MovementPenaltyDamageState", INI::parseIndexList, TheBodyDamageTypeNames, 0x0B3C },
	{ "HealthBonus_Veteran", INI::parsePercentToReal, 0, 0x0AD8 },
	{ "HealthBonus_Elite", INI::parsePercentToReal, 0, 0x0ADC },
	{ "HealthBonus_Heroic", INI::parsePercentToReal, 0, 0x0AE0 },
	{ "HumanSoloPlayerHealthBonus_Easy", INI::parsePercentToReal, 0, 0x0954 },
	{ "HumanSoloPlayerHealthBonus_Normal", INI::parsePercentToReal, 0, 0x0958 },
	{ "HumanSoloPlayerHealthBonus_Hard", INI::parsePercentToReal, 0, 0x095C },
	{ "AttributeModifierArmorMaxBonus", INI::parsePercentToReal, 0, 0x0AE8 },
	{ "AISoloPlayerHealthBonus_Easy", INI::parsePercentToReal, 0, 0x0964 },
	{ "AISoloPlayerHealthBonus_Normal", INI::parsePercentToReal, 0, 0x0968 },
	{ "AISoloPlayerHealthBonus_Hard", INI::parsePercentToReal, 0, 0x096C },
	{ "WeaponBonus", WeaponBonusSet::parseWeaponBonusSetPtr, 0, 0x0AD0 },
	{ "DefaultStructureRubbleHeight", INI::parseReal, 0, 0x0AE4 },
	{ "FixedSeed", INI::parseInt, 0, 0x09E8 },
	{ "ShellMapName", INI::parseAsciiString, 0, 0x0AEC },
	{ "ShellMapOn", INI::parseBool, 0, 0x0AF0 },
	{ "ShellMapOffByCommandArgument", INI::parseBool, 0, 0x0AF1 },
	{ "SkipMapUnroll", INI::parseBool, 0, 0x002D },
	{ "PlayIntro", INI::parseBool, 0, 0x0AF2 },
	{ "FirewallBehavior", INI::parseInt, 0, 0x0A4C },
	{ "FirewallPortOverride", INI::parseInt, 0, 0x0A54 },
	{ "FirewallPortAllocationDelta", INI::parseInt, 0, 0x0A58 },
	{ "DamageRadiusMinimumForSplash", INI::parseReal, 0, 0x0B40 },
	{ "GroupSelectMinSelectSize", INI::parseInt, 0, 0x0B44 },
	{ "GroupSelectVolumeBase", INI::parseReal, 0, 0x0B48 },
	{ "GroupSelectVolumeIncrement", INI::parseReal, 0, 0x0B4C },
	{ "MaxUnitSelectSounds", INI::parseInt, 0, 0x0B50 },
	{ "SelectionFlashSaturationFactor", INI::parseReal, 0, 0x0B54 },
	{ "SelectionFlashHouseColor", INI::parseBool, 0, 0x0B58 },
	{ "CameraAudibleRadius", INI::parseReal, 0, 0x0B5C },
	{ "GroupMoveClickToGatherAreaFactor", INI::parseReal, 0, 0x0B60 },
	{ "ShakeSubtleIntensity", INI::parseReal, 0, 0x0B74 },
	{ "ShakeNormalIntensity", INI::parseReal, 0, 0x0B78 },
	{ "ShakeStrongIntensity", INI::parseReal, 0, 0x0B7C },
	{ "ShakeSevereIntensity", INI::parseReal, 0, 0x0B80 },
	{ "ShakeCineExtremeIntensity", INI::parseReal, 0, 0x0B84 },
	{ "ShakeCineInsaneIntensity", INI::parseReal, 0, 0x0B88 },
	{ "MaxShakeIntensity", INI::parseReal, 0, 0x0B8C },
	{ "MaxShakeRange", INI::parseReal, 0, 0x0B90 },
	{ "SellPercentage", INI::parsePercentToReal, 0, 0x0B94 },
	{ "BaseRegenHealthPercentPerSecond", INI::parsePercentToReal, 0, 0x0B98 },
	{ "BaseRegenDelay", INI::parseDurationUnsignedInt, 0, 0x0B9C },
	{ "SpecialPowerViewObject", INI::parseAsciiString, 0, 0x0BA4 },
	{ "StandardPublicBone", INI::parseAsciiStringVectorAppend, 0, 0x0BA8 },
	{ "ShowMetrics", INI::parseBool, 0, 0x0BB4 },
	{ "DefaultStartingCash", INI::parseUnsignedInt, 0, 0x0BB8 },
	{ "ShroudColor", INI::parseRGBColor, 0, 0x0BDC },
	{ "ClearAlpha", INI::parseUnsignedByte, 0, 0x0BE8 },
	{ "FogAlpha", INI::parseUnsignedByte, 0, 0x0BE9 },
	{ "ShroudAlpha", INI::parseUnsignedByte, 0, 0x0BEA },
	{ "TaintOn", INI::parseBool, 0, 0x0C6A },
	{ "TaintColor", INI::parseRGBColor, 0, 0x0BEC },
	{ "ElvenWoodColor", INI::parseRGBColor, 0, 0x0BF8 },
	{ "TaintAlpha", INI::parseUnsignedByte, 0, 0x0C04 },
	{ "HotKeyTextColor", INI::parseColorInt, 0, 0x0BA0 },
	{ "PowerBarBase", INI::parseInt, 0, 0x0BC0 },
	{ "PowerBarIntervals", INI::parseReal, 0, 0x0BC4 },
	{ "PowerBarYellowRange", INI::parseInt, 0, 0x0BC8 },
	{ "UnlookPersistDuration", INI::parseDurationUnsignedInt, 0, 0x0BD0 },
	{ "NetworkFPSHistoryLength", INI::parseInt, 0, 0x0C08 },
	{ "NetworkLatencyHistoryLength", INI::parseInt, 0, 0x0C0C },
	{ "NetworkRunAheadMetricsTime", INI::parseInt, 0, 0x0C10 },
	{ "NetworkCushionHistoryLength", INI::parseInt, 0, 0x0C14 },
	{ "NetworkRunAheadSlack", INI::parseInt, 0, 0x0C18 },
	{ "NetworkKeepAliveDelay", INI::parseInt, 0, 0x0C1C },
	{ "NetworkDisconnectTime", INI::parseInt, 0, 0x0C20 },
	{ "NetworkPlayerTimeoutTime", INI::parseInt, 0, 0x0C24 },
	{ "NetworkDisconnectScreenNotifyTime", INI::parseInt, 0, 0x0C28 },
	{ "KeyboardCameraRotateSpeed", INI::parseReal, 0, 0x0C2C },
	{ "PlayStats", INI::parseInt, 0, 0x0C30 },
	{ "DefaultVoiceAttackChargeTimeout", INI::parseDurationUnsignedInt, 0, 0x0C34 },
	{ "DefaultMaxDistanceForEngaged", INI::parseReal, 0, 0x0C38 },
	{ "DefaultEngagedStateTimeout", INI::parseDurationUnsignedInt, 0, 0x0C3C },
	{ "AnimationSharingCap", INI::parseInt, 0, 0x0C40 },
	{ "AnimationSharingFrameTolerance", INI::parseReal, 0, 0x0C44 },
	{ "AnimationSharingSpeedTolerance", INI::parseReal, 0, 0x0C48 },
	{ "AnimationSharingWorryThreshold", INI::parseReal, 0, 0x0C4C },
	{ "AnimationSharingDrasticThreshold", INI::parseReal, 0, 0x0C50 },
	{ "ParticleCursorAnim2DTemplateName", INI::parseAsciiString, 0, 0x0D4C },
	{ "ParticleCursorBurstCount", INI::parseUnsignedInt, 0, 0x0D50 },
	{ "ParticleCursorBurstFactor", INI::parseGameClientRandomVariable, 0, 0x0D54 },
	{ "ParticleCursorStopBurstFactor", INI::parseReal, 0, 0x0D60 },
	{ "ParticleCursorBurstFrequency", INI::parseUnsignedInt, 0, 0x0D64 },
	{ "ParticleCursorParticleLife", INI::parseGameClientRandomVariable, 0, 0x0D68 },
	{ "ParticleCursorSystemLife", INI::parseGameClientRandomVariable, 0, 0x0D74 },
	{ "ParticleCursorDriftVelX", INI::parseGameClientRandomVariable, 0, 0x0D80 },
	{ "ParticleCursorDriftVelY", INI::parseGameClientRandomVariable, 0, 0x0D8C },
	{ "ParticleCursorVelocityDrag", INI::parseGameClientRandomVariable, 0, 0x0D98 },
	{ "ParticleCursorParticleSize", INI::parseGameClientRandomVariable, 0, 0x0DA4 },
	{ "ParticleCursorPerFrameSize", INI::parseBool, 0, 0x0DB0 },
	{ "ParticleCursorAlpha", INI::parseInt, 0, 0x0DB4 },
	{ "ParticleCursorOffset", INI::parseICoord2D, 0, 0x0DB8 },
	{ "ProgressMovieOffset", INI::parseICoord2D, 0, 0x0DC0 },
	{ "ProgressMovieSize", INI::parseICoord2D, 0, 0x0DC8 },
	{ "UseHelpTextSystem", INI::parseBool, 0, 0x0DD0 },
	{ "GuiTextureFiltering", INI::parseBool, 0, 0x0DD1 },
	{ "CameraTerrainSampleRadiusForHeight", INI::parseReal, 0, 0x0DD8 },
	{ "EnableHouseColor", INI::parseBool, 0, 0x0DDC },
	{ "GoodCommandPoints", parseCommandPoints, 0, 0x0DEC },
	{ "EvilCommandPoints", parseCommandPoints, 0, 0x0DF4 },
	{ "GoodCommandPointsBonus", INI::parseInt, 0, 0x0DFC },
	{ "EvilCommandPointsBonus", INI::parseInt, 0, 0x0E00 },
	{ "GoodCommandPointsAI", parseCommandPoints, 0, 0x0E04 },
	{ "EvilCommandPointsAI", parseCommandPoints, 0, 0x0E0C },
	{ "GoodCommandPointsMP2", parseCommandPoints, 0, 0x0E14 },
	{ "EvilCommandPointsMP2", parseCommandPoints, 0, 0x0E1C },
	{ "GoodCommandPointsMP3", parseCommandPoints, 0, 0x0E24 },
	{ "EvilCommandPointsMP3", parseCommandPoints, 0, 0x0E2C },
	{ "GoodCommandPointsMP4", parseCommandPoints, 0, 0x0E34 },
	{ "EvilCommandPointsMP4", parseCommandPoints, 0, 0x0E3C },
	{ "GoodCommandPointsMP5", parseCommandPoints, 0, 0x0E44 },
	{ "EvilCommandPointsMP5", parseCommandPoints, 0, 0x0E4C },
	{ "GoodCommandPointsMP6", parseCommandPoints, 0, 0x0E54 },
	{ "EvilCommandPointsMP6", parseCommandPoints, 0, 0x0E5C },
	{ "GoodCommandPointsMP7", parseCommandPoints, 0, 0x0E64 },
	{ "EvilCommandPointsMP7", parseCommandPoints, 0, 0x0E6C },
	{ "GoodCommandPointsMP8", parseCommandPoints, 0, 0x0E74 },
	{ "EvilCommandPointsMP8", parseCommandPoints, 0, 0x0E7C },
	{ "GoodCommandPointsMP56", parseCommandPoints, 0, 0x0E54 },
	{ "EvilCommandPointsMP56", parseCommandPoints, 0, 0x0E5C },
	{ "GoodCommandPointsMP78", parseCommandPoints, 0, 0x0E74 },
	{ "EvilCommandPointsMP78", parseCommandPoints, 0, 0x0E7C },
	{ "InitialMaxRingLevel", INI::parseInt, 0, 0x0E84 },
	{ "ResourceBonusMultiplier", INI::parseReal, 0, 0x0E88 },
	{ "GoodCommandPointLimit", INI::parseInt, 0, 0x0E8C },
	{ "EvilCommandPointLimit", INI::parseInt, 0, 0x0E90 },
	{ "PowerLimit", INI::parseInt, 0, 0x0E94 },
	{ "ResourceMultiplierLimit", INI::parseReal, 0, 0x0E98 },
	{ "TreeFadeObjectFilter", iniParseObjectFilter, 0, 0x0EB0 },
	{ "CamouflageDetectorObjectFilter", iniParseObjectFilter, 0, 0x0EB4 },
	{ "VeterancyPipDrawObjectFilter", iniParseObjectFilter, 0, 0x0EB8 },
	{ "VictoryConditionStructureObjectFilter", iniParseObjectFilter, 0, 0x0EBC },
	{ "VictoryConditionUnitObjectFilter", iniParseObjectFilter, 0, 0x0EC0 },
	{ "MultiPlayMoneyMult", parseMultiPlayMoneyMult, 0, 0x0EC4 },
	{ "MultiPlayUnitXPMult", parseMultiPlayUnitXPMult, 0, 0x0EC4 },
	{ "MultiPlayBuildingXPMult", parseMultiPlayBuildingXPMult, 0, 0x0EC4 },
	{ "MultiPlayUnitSpeedMult", parseMultiPlayUnitSpeedMult, 0, 0x0EC4 },
	{ "MultiPlayBuildingSpeedMult", parseMultiPlayBuildingSpeedMult, 0, 0x0EC4 },
	{ "HandicapBuildSpeed5", INI::parsePercentToReal, 0, 0x10A4 },
	{ "HandicapBuildSpeed10", INI::parsePercentToReal, 0, 0x10A8 },
	{ "HandicapBuildSpeed15", INI::parsePercentToReal, 0, 0x10AC },
	{ "HandicapBuildSpeed20", INI::parsePercentToReal, 0, 0x10B0 },
	{ "HandicapBuildSpeed25", INI::parsePercentToReal, 0, 0x10B4 },
	{ "HandicapBuildSpeed30", INI::parsePercentToReal, 0, 0x10B8 },
	{ "HandicapBuildSpeed35", INI::parsePercentToReal, 0, 0x10BC },
	{ "HandicapBuildSpeed40", INI::parsePercentToReal, 0, 0x10C0 },
	{ "HandicapBuildSpeed45", INI::parsePercentToReal, 0, 0x10C4 },
	{ "HandicapBuildSpeed50", INI::parsePercentToReal, 0, 0x10C8 },
	{ "HandicapBuildSpeed55", INI::parsePercentToReal, 0, 0x10CC },
	{ "HandicapBuildSpeed60", INI::parsePercentToReal, 0, 0x10D0 },
	{ "HandicapBuildSpeed65", INI::parsePercentToReal, 0, 0x10D4 },
	{ "HandicapBuildSpeed70", INI::parsePercentToReal, 0, 0x10D8 },
	{ "HandicapBuildSpeed75", INI::parsePercentToReal, 0, 0x10DC },
	{ "HandicapBuildSpeed80", INI::parsePercentToReal, 0, 0x10E0 },
	{ "HandicapBuildSpeed85", INI::parsePercentToReal, 0, 0x10E4 },
	{ "HandicapBuildSpeed90", INI::parsePercentToReal, 0, 0x10E8 },
	{ "HandicapBuildSpeed95", INI::parsePercentToReal, 0, 0x10EC },
	{ "HandicapBuildSpeed100", INI::parsePercentToReal, 0, 0x10F0 },
	{ "BasicTutorialMap", INI::parseAsciiString, 0, 0x1114 },
	{ "BasicTutorialLoadMovie", INI::parseAsciiString, 0, 0x1118 },
	{ "BasicTutorialLoadScreenStillImage", INI::parseAsciiString, 0, 0x111C },
	{ "BasicTutorialLoadScreenVoiceTrack", INI::parseAsciiString, 0, 0x1120 },
	{ "BasicTutorialLoadScreenMusicTrack", INI::parseAsciiString, 0, 0x1124 },
	{ "BasicTutorialObjective", INI::parseAsciiStringVectorAppend, 0, 0x1128 },
	{ "BasicTutorialMillisecondsAfterStartToStartFadeUp", INI::parseDurationUnsignedInt, 0, 0x1134 },
	{ "AdvancedTutorialMap", INI::parseAsciiString, 0, 0x1138 },
	{ "AdvancedTutorialLoadMovie", INI::parseAsciiString, 0, 0x113C },
	{ "AdvancedTutorialLoadScreenStillImage", INI::parseAsciiString, 0, 0x1140 },
	{ "AdvancedTutorialLoadScreenVoiceTrack", INI::parseAsciiString, 0, 0x1144 },
	{ "AdvancedTutorialLoadScreenMusicTrack", INI::parseAsciiString, 0, 0x1148 },
	{ "AdvancedTutorialObjective", INI::parseAsciiStringVectorAppend, 0, 0x114C },
	{ "AdvancedTutorialMillisecondsAfterStartToStartFadeUp", INI::parseDurationUnsignedInt, 0, 0x1158 },
	{ "BlockedByWallLeeway", INI::parseInt, 0, 0x1108 },
	{ "SecondsBeforeBaseCheckActive", INI::parseReal, 0, 0x110C },
	{ "ObjectsThatScore", iniParseObjectFilter, 0, 0x1168 },
	{ "ScoreKeeper_UnitsBuiltMultiplier", INI::parseReal, 0, 0x116C },
	{ "ScoreKeeper_UnitsDestroyedMultiplier", INI::parseReal, 0, 0x1170 },
	{ "ScoreKeeper_StructuresBuiltMultiplier", INI::parseReal, 0, 0x1174 },
	{ "ScoreKeeper_StructuresDestroyedMultiplier", INI::parseReal, 0, 0x1178 },
	{ "ScoreKeeper_HeroesVettedMultiplier", INI::parseReal, 0, 0x117C },
	{ "ScoreKeeper_UnitsVettedMultiplier", INI::parseReal, 0, 0x1180 },
	{ "ScoreKeeper_ObjectivesCompletedMultiplier", INI::parseReal, 0, 0x1184 },
	{ "ScoreKeeper_SuppliesCollectedMultiplier", INI::parseReal, 0, 0x1188 },
	{ "ScoreKeeper_PowerPointsMultiplier", INI::parseReal, 0, 0x118C },
	{ "ScoreKeeper_RegionCommandPointsMultiplier", INI::parseReal, 0, 0x1190 },
	{ "ScoreKeeper_RegionResourcesMultiplier", INI::parseReal, 0, 0x1194 },
	{ "ScoreKeeper_RegionPowerPointsMultiplier", INI::parseReal, 0, 0x1198 },
	{ "ScoreKeeper_SkillPointsMultiplier", INI::parseReal, 0, 0x11B4 },
	{ "ScoreKeeper_PlayerEliminatedMultiplier", INI::parseReal, 0, 0x11B8 },
	{ "ScoreKeeper_TimeTakenMultiplier", INI::parseReal, 0, 0x119C },
	{ "ScoreKeeper_TimeTakenMaximumScore", INI::parseReal, 0, 0x11A0 },
	{ "ScoreKeeper_TimeTakenMinimumScore", INI::parseReal, 0, 0x11A4 },
	{ "ScoreKeeper_TotalVictoryRequiredScore", INI::parseReal, 0, 0x11A8 },
	{ "ScoreKeeper_NormalVictoryRequiredScore", INI::parseReal, 0, 0x11AC },
	{ "ScoreKeeper_NormalVictoryRequiredObjectivesPercentage", INI::parseReal, 0, 0x11B0 },
	{ "TintUnitIfPathingForMoreThan", INI::parseInt, 0, 0x11C0 },
	{ "ClampedLOSHeightForCastleStructures", INI::parseReal, 0, 0x11C4 },
	{ "ReinvisibityDelay", INI::parseDurationUnsignedInt, 0, 0x11CC },
	{ "InvisibilityOpacityMin", INI::parseReal, 0, 0x11D0 },
	{ "InvisibilityOpacityMax", INI::parseReal, 0, 0x11D4 },
	{ "InvisibilityOpacityCycleFrames", INI::parseUnsignedInt, 0, 0x11D8 },
	{ "BuilderFadeOutTime", INI::parseDurationUnsignedInt, 0, 0x11DC },
	{ "BuilderFadeInTime", INI::parseDurationUnsignedInt, 0, 0x11E0 },
	{ "BuilderMoveFromNewStructureDistance", INI::parseReal, 0, 0x11E4 },
	{ "MaxPathfindCellsPerFrame", INI::parseUnsignedInt, 0, 0x11E8 },
	{ "MaxCellsFindMeleeEngagementLocation", INI::parseUnsignedInt, 0, 0x11EC },
	{ "MaxCellsAdjustDestination", INI::parseUnsignedInt, 0, 0x11F0 },
	{ "MaxCellsAdjustHordeMeleeDestination", INI::parseUnsignedInt, 0, 0x11F4 },
	{ "MaxCellsAdjustTargetDestination", INI::parseUnsignedInt, 0, 0x11F8 },
	{ "MaxCellsAdjustToPossibleDestination", INI::parseUnsignedInt, 0, 0x11FC },
	{ "MaxCellsAdjustToMeleeDestination", INI::parseUnsignedInt, 0, 0x1200 },
	{ "MaxCellsAdjustToNearestGroundCell", INI::parseUnsignedInt, 0, 0x1204 },
	{ "MaxCellsAdjustToNearestValidCell", INI::parseUnsignedInt, 0, 0x1208 },
	{ "MaxCellsPatchPath", INI::parseUnsignedInt, 0, 0x120C },
	{ "MaxCellsFindPathLimit", INI::parseUnsignedInt, 0, 0x1210 },
	{ "MaxCellsFindAttackPath", INI::parseUnsignedInt, 0, 0x1214 },
	{ "MaxCellsFindAttackPathSideways", INI::parseUnsignedInt, 0, 0x1218 },
	{ "MaxCellsToExamineTowardsGoal", INI::parseUnsignedInt, 0, 0x121C },
	{ "MaxCastleRadius", INI::parseReal, 0, 0x1220 },
	{ "GarrisonedRangeMultiplier", INI::parseReal, 0, 0x1224 },
	{ "NumMinutesBeforePlayersCanTransferMoney", INI::parseInt, 0, 0x122C },
	{ "MaxNumMembersToForceToImmediatelyEnter", INI::parseUnsignedInt, 0, 0x1230 },
	{ "WaitToForceMemberToEnterDelay", INI::parseUnsignedInt, 0, 0x1234 },
	{ 0, 0, 0, 0 }
};

int GlobalData::vslot06() { return (int)s_GlobalDataFieldParseTable; }
void GlobalData::init() {}
void GlobalData::update() {}


// GlobalData::GlobalData, retail 0x0023631C (5034 B). WB 0xBA1D40 names it
// (wb_name_leads); newOverride news 0x1254 bytes and runs it. Zero Hour's
// constructor gives the purpose (registration in m_theOriginal, scalar
// defaults, the 3x6 terrain lighting loop, setTimeOfDay). BFME2 initialises
// in offset order through the member-initializer list: retail interleaves
// member construction with the scalar stores. Values and widths are
// retail's; frame counts are multiples of the logic frame rate
// LOGICFRAMES_PER_SECOND (x3 at +CC, x10 at +C34, x2 at +C3C). Field names stay
// offset labels.
GlobalData::GlobalData():
m_001C(1),
m_001D(0),
m_0020(1),
m_0024(0),
m_0025(1),
m_0026(0),
m_0027(0),
m_0028(0),
m_002C(0),
m_002D(0),
m_0030(0x400),
m_0034(0x300),
m_0038(0),
m_003C(0),
m_003D(1),
m_003E(1),
m_003F(1),
m_0040(0),
m_0041(0),
m_0044(1),
m_0048(0),
m_0049(1),
m_004A(1),
m_004B(0),
m_004C(0),
m_004D(0),
m_004E(0),
m_0050(8),
m_0054(1),
m_0058(0),
m_005C(1),
m_005D(0),
m_005E(0),
m_005F(0),
m_0060(0),
m_0061(0),
m_0062(0),
m_0064(0),
m_0068(1),
m_006C(0.0f),
m_0070(0.0f),
m_0074(0.0f),
m_0078(0.0f),
m_007C(0.0f),
m_0080(0),
m_0084(1),
m_0085(0),
m_0086(1),
m_0087(0),
m_0088(0),
m_0090(0),
m_0094(-0.785f),
m_0098(0.0f),
m_009C(100.0f),
m_00A0(300.0f),
m_00A4(37.5f),
m_00A8(0.0f),
m_00AC(1.0f),
m_00B0(0.0f),
m_00B4(0.5f),
m_00B8(0.1f),
m_00BC(0.5f),
m_00C0(0.5f),
m_00C4(-1.0f),
m_00C8(0.5f),
m_00CC(LOGICFRAMES_PER_SECOND*3),
m_00D0(0),
m_00D4(0.0f),
m_00D8(0.0f),
m_00DC(0.0f),
m_00E8(0.0f),
m_00F4(0.0f),
m_00FC(0.0f),
m_0104(1.0f),
m_0108(1.0f),
m_010C(0),
m_0110(0x64),
m_0114(0x19),
m_0118(0x493e0),
m_0120(0.0f),
m_0124(0.0f),
m_012C(0.0f),
m_0130(0.0f),
m_0134(2),
m_0138(0),
m_013C(0),
m_013D(0),
m_013E(1),
m_013F(1),
m_0944(1.0f),
m_0950(1.0f),
m_0974(0x200),
m_0978(0x200),
m_097C(0x200),
m_0980(0x200),
m_0984(0.5f),
m_0988(3),
m_098C(0),
m_0990(0),
m_0994(0),
m_0998(0),
m_099C(1),
m_099D(1),
m_099E(1),
m_099F(1),
m_09A0(1),
m_09A1(1),
m_09A2(0),
m_09A3(1),
m_09A4(0),
m_09A5(1),
m_09A6(0),
m_09A7(0),
m_09A8(0.3f),
m_09AC(0),
m_09AD(0),
m_09AE(0),
m_09AF(1),
m_09B0(1),
m_09B1(0),
m_09B4(0),
m_09B8(0),
m_09BC(0),
m_09BD(1),
m_09BE(0),
m_09BF(1),
m_09C0(0),
m_09C1(0),
m_09C2(0),
m_09C3(0),
m_09C4(0),
m_09C5(1),
m_09C6(1),
m_09C7(0),
m_09C8(0),
m_09CC(1),
m_09D0(0),
m_09D1(0),
m_09D2(0),
m_09D4(0),
m_09D8(0),
m_09E4(0),
m_09E8(-1),
m_09EC(1.0f),
m_09F8(0),
m_0A04(0),
m_0A10(0),
m_0A1C(0),
m_0A28(0),
m_0A34(0),
m_0A40(0),
m_0A44(1),
m_0A48(0),
m_0A4C(0),
m_0A50(0),
m_0A54(0),
m_0A58(0),
m_0A5C(0x64),
m_0A60(1),
m_0A64(0.0f),
m_0A68(0.0f),
m_0A6C(0.0f),
m_0A70(0.0f),
m_0A74(0.0f),
m_0A78(0.0f),
m_0A7C(0.0f),
m_0A80(0.0f),
m_0A84(0.0f),
m_0A88(0xa),
m_0A8C(0.0f),
m_0A90(0.0f),
m_0A94(0x64),
m_0A98(0),
m_0A9C(1.0f),
m_0AA0(1.0f),
m_0AA4(1.0f),
m_0AA8(0x12c),
m_0AAC(10.0f),
m_0AB0(0.1f),
m_0AB4(1),
m_0AB5(0),
m_0AC4(0),
m_0AC5(0),
m_0AC8(0),
m_0ACC(0x1e),
m_weaponBonusSet(new Rva00235A21),
m_0AE4(1.0f),
m_0AE8(1.0f),
m_0AEC("Maps\\ShellMap1\\ShellMap1.map"),
m_0AF0(1),
m_0AF1(0),
m_0AF2(1),
m_0AF3(0),
m_0AF4(0),
m_0AF5(0),
m_0AF8(1.0f),
m_0AFC(1.0f),
m_0B00(1),
m_0B01(0),
m_0B04(0),
m_0B38(-1),
m_0B3C(2),
m_0B40(4.0f),
m_0B44(5),
m_0B48(0.5f),
m_0B4C(0.02f),
m_0B50(8),
m_0B54(0.5f),
m_0B58(0),
m_0B5C(500.0f),
m_0B60(1.0f),
m_0B64(0),
m_0B68(1),
m_0B69(0),
m_0B6A(0),
m_0B6B(0),
m_0B6C(0),
m_0B6D(0),
m_0B6E(0),
m_0B6F(0),
m_0B70(0),
m_0B71(0),
m_0B74(0.5f),
m_0B78(1.0f),
m_0B7C(2.5f),
m_0B80(5.0f),
m_0B84(8.0f),
m_0B88(12.0f),
m_0B8C(10.0f),
m_0B90(150.0f),
m_0B94(1.0f),
m_0B98(0.0f),
m_0B9C(0),
m_0BA0(0xffffff00),
m_0BB4(0),
m_0BBC(0),
m_0BBD(0),
m_0BC0(7),
m_0BC4(3.0f),
m_0BC8(5),
m_0BCC(1.0f),
m_0BD0(0x1e),
m_0BD4(0),
m_0BD8(GetDoubleClickTime()),
m_0BDC(0xFFFFFF),
m_0BE8(0xff),
m_0BE9(0x7f),
m_0BEA(0),
m_0BEC(0xFFFFFF),
m_0C04(0x80),
m_0C08(0x1e),
m_0C0C(0xc8),
m_0C10(0x1f4),
m_0C14(0xa),
m_0C18(0xa),
m_0C1C(0x14),
m_0C20(0x1388),
m_0C24(0xea60),
m_0C28(0x3a98),
m_0C2C(0.1f),
m_0C30(-1),
m_0C34(LOGICFRAMES_PER_SECOND*10),
m_0C38(30.0f),
m_0C3C(LOGICFRAMES_PER_SECOND*2),
m_0C40(0x64),
m_0C44(5.0f),
m_0C48(0.1f),
m_0C4C(0.25f),
m_0C50(0.5f),
m_0C60(-1),
m_0C64(0),
m_0C65(0),
m_0C66(0),
m_0C67(1),
m_0C68(1),
m_0C69(1),
m_0C6A(0),
m_0C6B(0),
m_0C6C(0),
m_0C6D(0),
m_0C6E(0),
m_0C6F(0),
m_0C70(-1),
m_0C74(0),
m_0C75(0),
m_0C78(0),
m_0C7C(0),
m_0C7D(0),
m_0C80(0x20),
m_0C88(LOGICFRAMES_PER_SECOND),
m_0C8C(0),
m_0C90(0x1388),
m_0C94(LOGICFRAMES_PER_SECOND),
m_0C98(0),
m_0C9C(0x2710),
m_0CA0(LOGICFRAMES_PER_SECOND),
m_0CA4(0),
m_0CCC(0),
m_0CD0(33.0f),
m_0CD4(0x4d),
m_0CF8(0),
m_0CF9(0),
m_0CFA(0),
m_0CFB(0),
m_0CFC(0),
m_0CFD(0),
m_0CFE(0),
m_0CFF(0),
m_0D00(0),
m_0D01(0),
m_0D04(".\\"),
m_0D08("MOTD.txt"),
m_0D0C(0),
m_0D10(0),
m_0D14(0),
m_0D18(0),
m_0D1C(0),
m_0D20(0),
m_0D24(1),
m_0D28(0x5a),
m_0D2C(1),
m_0D2D(0),
m_0D2E(0),
m_0D2F(0),
m_0D34(0),
m_0D35(0),
m_0D36(0),
m_0D40(1.0f),
m_0D44(0),
m_0D45(0),
m_0D46(1),
m_0D48(0),
m_0D50(0xa),
m_0D64(5),
m_0DB0(0),
m_0DB4(0xff),
m_0DB8(0,0),
m_0DC0(0xffffff6a,0xffffff60),
m_0DC8(0x80,0x80),
m_0DD0(0),
m_0DD1(1),
m_0DD4(250.0f),
m_0DD8(0.0f),
m_0DDC(0),
m_0DE0(0.2f),
m_0DE4(1.0f),
m_0DE8(0),
m_0DEC(0x3c,0x3c),
m_0DF4(0x7d,0x7d),
m_0DFC(0xa),
m_0E00(0x19),
m_0E04(100,100),
m_0E0C(300,300),
m_0E14(100,100),
m_0E1C(300,300),
m_0E24(80,80),
m_0E2C(150,150),
m_0E34(80,80),
m_0E3C(120,120),
m_0E44(70,70),
m_0E4C(100,100),
m_0E54(60,60),
m_0E5C(80,80),
m_0E64(55,55),
m_0E6C(70,70),
m_0E74(50,50),
m_0E7C(60,60),
m_0E84(2),
m_0E88(10.0f),
m_0E8C(0xc8),
m_0E90(0x258),
m_0E94(0xa),
m_0E98(4.0f),
m_0E9C(0),
m_0E9D(0),
m_0EA0(0),
m_0EA4(1),
m_0EA5(1),
m_0EA6(0),
m_0EA7(1),
m_0EA8(0.7f),
m_0EAC(0.0f),
m_1100(0),
m_1104(0),
m_1108(3),
m_110C(5.0f),
m_1110(1),
m_1111(0),
m_115C(0),
m_1160(0xff0b5ef2),
m_1164(0xffd92102),
m_11BC(1),
m_11C0(0),
m_11C4(40.0f),
m_11C8(0),
m_11C9(0),
m_11CA(1),
m_11CB(0),
m_11CC(0),
m_11D0(1.0f),
m_11D4(1.0f),
m_11D8(0xa),
m_11DC(5),
m_11E0(5),
m_11E4(10.0f),
m_11E8(0xfa0),
m_11EC(0x32),
m_11F0(0x190),
m_11F4(0xc8),
m_11F8(0x190),
m_11FC(0x190),
m_1200(0x190),
m_1204(0x190),
m_1208(0x190),
m_120C(0x7d0),
m_1210(0x3a98),
m_1214(0x9c4),
m_1218(0x9c4),
m_121C(0x61a8),
m_1224(-1.0f),
m_1228(-1),
m_122C(5),
m_1230(1),
m_1234(5),
m_1238(0),
m_123C(0),
m_123D(0) {
 if(!m_theOriginal) m_theOriginal=this;
 m_next=0;
 m_008C.clear(); m_000C.clear();m_0010.clear();m_0014.clear();m_0018.clear();
 for(int i=0;i<3;++i) {
  m_08D8[i].x=0.0f;
  m_08D8[i].y=0.0f;
  m_08D8[i].z=0.0f;
  m_08FC[i].x=0.0f;
  m_08FC[i].y=0.0f;
  m_08FC[i].z=0.0f;
  m_0920[i].x=0.0f;
  m_0920[i].y=0.0f;
  m_0920[i].z=-1.0f;
  for(int j=0;j<6;++j) {
   m_0140[j*3+i].ambient.x=0.0f;
   m_0140[j*3+i].ambient.y=0.0f;
   m_0140[j*3+i].ambient.z=0.0f;
   m_0140[j*3+i].diffuse.x=0.0f;
   m_0140[j*3+i].diffuse.y=0.0f;
   m_0140[j*3+i].diffuse.z=0.0f;
   m_0140[j*3+i].position.x=0.0f;
   m_0140[j*3+i].position.y=0.0f;
   m_0140[j*3+i].position.z=-1.0f;
   m_03C8[j*3+i].ambient.x=0.0f;
   m_03C8[j*3+i].ambient.y=0.0f;
   m_03C8[j*3+i].ambient.z=0.0f;
   m_03C8[j*3+i].diffuse.x=0.0f;
   m_03C8[j*3+i].diffuse.y=0.0f;
   m_03C8[j*3+i].diffuse.z=0.0f;
   m_03C8[j*3+i].position.x=0.0f;
   m_03C8[j*3+i].position.y=0.0f;
   m_03C8[j*3+i].position.z=-1.0f;
   m_0650[j*3+i].ambient.x=0.0f;
   m_0650[j*3+i].ambient.y=0.0f;
   m_0650[j*3+i].ambient.z=0.0f;
   m_0650[j*3+i].diffuse.x=0.0f;
   m_0650[j*3+i].diffuse.y=0.0f;
   m_0650[j*3+i].diffuse.z=0.0f;
   m_0650[j*3+i].position.x=0.0f;
   m_0650[j*3+i].position.y=0.0f;
   m_0650[j*3+i].position.z=-1.0f;
  }
 }
m_09F0.clear();
m_09FC.clear();
m_0A08.clear();
m_0A14.clear();
m_0A20.clear();
m_0A2C.clear();
m_0A38.clear();
m_09F4.clear();
m_0A00.clear();
m_0A0C.clear();
m_0A18.clear();
m_0A24.clear();
m_0A30.clear();
m_0A3C.clear();
m_011C.clear();
m_0128.clear();
m_0BA4.clear();
m_0BA8.clear();setTimeOfDay((TimeOfDay)m_0134);
m_0ABC.clear();m_0AC0.clear();
for(int i=0;i<4;++i)m_0AD4[i]=1.0f;
for(int i=0;i<8;++i)m_0954[i]=1.0f;
if(TheVersion)*reinterpret_cast<Rva00235A37*>(&m_0B08)=*reinterpret_cast<Rva00235A37*>(TheVersion);
for(int i=0;i<20;++i)m_10A4[i]=1.0f;
for(int i=0;i<20;++i)m_116C[i]=1.0f;
m_116C[19]=0.1f;
}

typedef char S4GlobalDataSize[(sizeof(GlobalData)==0x1254)?1:-1];
