// cl: /Oy- /DNDEBUG /MD /GX-
// ?ParseINI@BuildingRestriction@ModuleData@LivingWorldRegion@@YAXPAVINI@@PAX@Z @0x003F2576 104B
// Renamed from placeholder Rva003F2576Parse: the retail INIException literal
// "Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI"
// names this function and its class nesting (WorldBuilder string, score 1.0).
// The second parameter's real type is not yet proven; PAX follows the
// ParseEyeTowerPointData opaque-argument precedent. The +0x14 holder view is
// TU-local and claims nothing about the owner class.
// Body provenance: placeholder Rva003F2576Parse.cpp (matched), itself built from
// landed callees initFromINI 0x0002DE78, new 0x0002FDA0, Rva003F1FB6 ctor
// 0x003F1FB6, holder 0x003F255C, INIException 0x0002F681; table VA 0x00C36EE0.
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class ModuleData;

class Rva003F1FB6
{
public:
	Rva003F1FB6();
private:
	char m_pad[0x10];
};

class Rva003F255C
{
public:
	void rva003F255C(const ModuleData *p);
};

struct Rva003F2576Outer
{
	char _pad[0x14];
	Rva003F255C m_holder;
};

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva003F2576ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva003F2576ThrowInfoAnchor rva003F2576ThrowInfoAnchor = { 0, 0, 0, 0 };

extern const FieldParse g_00C36EE0;

class LivingWorldRegion
{
public:
	class ModuleData
	{
	public:
		class BuildingRestriction
		{
		public:
			static void ParseINI(INI *ini, void *outer);
		};
	};
};

void LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI(INI *ini, void *outer)
{
	if (!ini || !outer)
	{
		INIException exc(3, "Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI");
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva003F2576ThrowInfoAnchor); __assume(0);
	}
	Rva003F255C *holder = &reinterpret_cast<Rva003F2576Outer *>(outer)->m_holder;
	Rva003F1FB6 *p = new Rva003F1FB6;
	ini->initFromINI(p, &g_00C36EE0);
	holder->rva003F255C((const ::ModuleData *)p);
}
