// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// W3DScriptedModelDraw::getAnimationFrameCount, the model variant resolver
// rva000C2E3A and the two numbering helpers they call, which share this unit:
// retail keeps the module's state pointer (getAnimationFrameCount) and the
// drawable (rva000C2E3A) in EDX across a helper call, which cl only does for
// callees it has already compiled in the same unit.
//
// ?Rva000B2BA3Get@@YAHPBURva000B2BE5Src@@PA_N@Z, retail 0x000B2BA3..0x000B2BE5
// (66 bytes), cdecl: the animation numbering mode from TheGameLODManager's
// +0x1774 setting. Unless that is 3, a drawable with the 0x20 status bit
// (+0x114) forces mode 0 and reports it through the optional flag. Mode 0
// answers 2, mode 1 answers 1, anything else 0. Sibling of the rowed
// Rva000B2BE5Get (0x000B2BE5), which tests the same bit; WorldBuilder twin
// 0x0091E640 unnamed.
//
// ?getAnimationFrameCount@W3DScriptedModelDraw@@UAE_NABVAsciiString@@PAH@Z,
// retail 0x000BF953..0x000BF9FC (169 bytes, ret 8), named by its
// WorldBuilder twin 0x00930960 (W3DScriptedModelDraw.cpp). It overrides an
// interface virtual whose subobject sits at +0x0C, so this points there:
// module data at -8, drawable at -4, the current state at +8 and an index at
// +0xB0. Without an output it fails. Otherwise it looks the animation up
// through the rowed 0x000BF7E8 with the state's base (+0x58) and model
// (+0x70) names:
//  - numbered by Rva000B2BA3Get when the module data's +0x135 flag is set;
//  - numbered by Rva000B2BE5Get when its +0x134 flag is set;
//  - unnumbered otherwise.
// It stores the clip's frame count, reads its frame rate (unused), releases
// it and succeeds.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <set>
#include <vector>
#include "ascii_string.h"

class Team;enum Relationship{ENEMIES,NEUTRAL,ALLIES};
class Player {public:Relationship getRelationship(const Team*)const;};
class PlayerList{char prefix[16];public:Player *local;};extern PlayerList *ThePlayerList;
struct Rva000B5FE6Template {char prefix[0x108];unsigned flags[19];char gap[0x632-0x154];bool special632;};
class Object{public:char prefix[4];Rva000B5FE6Template *definition;char pad8[0x304-8];Team *team;char pad308[0x437-0x308];unsigned char state437,state438;bool isLocallyControlled()const;};
struct Rva000B5FE6Drawable{char prefix[4];Rva000B5FE6Template *definition;char pad8[0xfc-8];Object *object;char pad100[0x258-0x100];unsigned status258[19]; __forceinline bool testStatus(int n)const {return (status258[n>>5] & (1U<<(n&31)))!=0;}};
class Rva000B5FE6Render {
public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void v021();
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void v029();
 virtual void v030();
 virtual void v031();
 virtual void v032();
 virtual void v033();
 virtual void v034();
 virtual void v035();
 virtual void v036();
 virtual void v037();
 virtual void v038();
 virtual void v039();
 virtual void v040();
 virtual void v041();
 virtual void v042();
 virtual void v043();
 virtual void v044();
 virtual void v045();
 virtual void v046();
 virtual void v047();
 virtual void v048();
 virtual void v049();
 virtual void v050();
 virtual void v051();
 virtual void v052();
 virtual void v053();
 virtual void v054();
 virtual void v055();
 virtual void v056();
 virtual void v057();
 virtual void v058();
 virtual void v059();
 virtual void v060();
 virtual void v061();
 virtual void v062();
 virtual void v063();
 virtual void v064();
 virtual void v065();
 virtual void v066();
 virtual void v067();
 virtual void v068();
 virtual void v069();
 virtual void v070();
 virtual void v071();
 virtual void v072();
 virtual void v073();
 virtual void v074();
 virtual void v075();
 virtual void v076();
 virtual void v077();
 virtual void v078();
 virtual void v079();
 virtual void v080();
 virtual void v081();
 virtual void v082();
 virtual void v083();
 virtual void v084();
 virtual void v085();
 virtual void v086();
 virtual void v087();
 virtual void v088();
 virtual void v089();
 virtual void v090();
 virtual void v091();
 virtual void v092();
 virtual void v093();
 virtual void v094();
 virtual void v095();
 virtual void v096();
 virtual void v097();
 virtual void v098();
 virtual void v099();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual void v110();
 virtual void v111();
 virtual void v112();
 virtual void v113();
 virtual void v114();
 virtual void v115();
 virtual void v116();
 virtual void v117();
 virtual void v118();
 virtual void v119();
 virtual unsigned flags(); virtual void addFlags(unsigned,bool);
};

class HTreeClass;

HTreeClass *Rva000BF7E8FindAnimTree(const AsciiString &pattern, const AsciiString &base,
	const AsciiString &model, bool numbered, int number);

struct Rva000B2BE5Src
{
	char pad[0x114];
	unsigned char flag;
};


class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct Rva000B2BA3LOD
{
	char m_pad0000[0x1774];
	int m_mode1774; // +0x1774
};

int __cdecl Rva000B2BA3Get(const Rva000B2BE5Src *p, bool *forced)
{
	int mode = reinterpret_cast<Rva000B2BA3LOD *>(TheGameLODManager)->m_mode1774;
	if (mode != 3 && p && (p->flag & 0x20))
	{
		if (forced)
			*forced = true;
		mode = 0;
	}
	switch (mode)
	{
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
	case 3:
		return 0;
	}
	return 0;
}

// ?Rva000B2BE5Get@@YAHPBURva000B2BE5Src@@H@Z, retail 0x000B2BE5..0x000B2BFF
// (26 bytes), cdecl: 2 for a drawable with the 0x20 status bit, else the
// fallback (callers 0x000BF33F 0x000BF4D2 0x000BF996 0x000C2ECC).
int __cdecl Rva000B2BE5Get(const Rva000B2BE5Src *p, int fallback)
{
	if (p && (p->flag & 0x20))
		return 2;
	return fallback;
}

typedef bool Bool;
typedef int Int;

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &operator<<(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};

template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &text);

extern Debug *theDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

Bool Render_Obj_Exists(const char *name);

AsciiString Rva000B69EAGet(const AsciiString &name, int kind);

struct W3DScriptedModelDrawTemplateView
{
	const StringBase<char> &getName() const { return *(const StringBase<char> *)&m_name; }
	unsigned char m_unmodelled00[0x64];
	AsciiString m_name;
};

class Drawable
{
public:
	const W3DScriptedModelDrawTemplateView *getTemplate() const { return m_template; }

	void *m_vtable;
	const W3DScriptedModelDrawTemplateView *m_template;
};

// ZH ModelState.h ModelConditionFlagType, the bits this body tests.
enum
{
	MODELCONDITION_DAMAGED = 3,
	MODELCONDITION_REALLY_DAMAGED = 4,
	MODELCONDITION_RUBBLE = 5,
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

template <size_t NUMBITS> class BitFlags
{
public:
	Bool test(Int i) const { return (m_bits[i >> 5] >> (i & 31)) & 1; }

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<591> ModelConditionFlags;

// The loaded clip: Delete_This (slot 0), frame count (slot 5), frame rate
// (slot 6) and its reference count at +4.
class Rva000BF953Clip
{
public:
	virtual void deleteThis();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual int getNumFrames();
	virtual float getFrameRate();

	void releaseRef()
	{
		if (--m_refs == 0)
			deleteThis();
	}

private:
	int m_refs; // +0x04
};

struct Rva000BF953ModuleData
{
	char m_pad000[0x6a];
	bool hidden;
	char m_pad06B[0x134-0x6b];
	bool m_numberByStatus134; // +0x134
	bool m_numberByLOD135;    // +0x135
	bool m_136;               // +0x136
	bool m_findVariant137;    // +0x137
};

struct Rva000BF953State
{
	char m_pad00[0x58];
	AsciiString m_base58;     // +0x58
	char m_pad5C[0x70 - 0x5C];
	AsciiString m_model70;    // +0x70
};

class Rva000BF953Module
{
public:
	virtual void m00();

	const Rva000B2BE5Src *getDrawable() const { return m_drawable; }

protected:
	Rva000BF953ModuleData *m_moduleData; // +0x04
	Rva000B2BE5Src *m_drawable;          // +0x08
};

class Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames) = 0;
};

class W3DScriptedModelDraw : public Rva000BF953Module, public Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames);
	AsciiString rva000C2E3A(const AsciiString &modelName);
	void rva000B5FE6();
	void rva000C2CBF(int count, _STL::vector<AsciiString> *originals, _STL::vector<AsciiString> *replacements);
	// The one-character append retail expands in place (StringBase concat
	// 0x000369A0 on a stack copy of the character).
	static __forceinline void appendChar(AsciiString &s, char c)
	{
		((StringBase<char> *)&s)->concat(&c, 1);
	}

private:
	char m_pad10[0x14 - 0x10];
	Rva000BF953State *m_state14; // +0x14
	char m_pad18[0x50 - 0x18];
	Rva000B5FE6Render *render;
	char m_pad54[0xBC - 0x54];
	int m_index0BC;              // +0xBC
	char m_pad0C0[0x17C - 0xC0];
	ModelConditionFlags m_conditions17C; // +0x17C
	char m_pad1C8[0x214-0x1C8];
	int mode;
};

bool W3DScriptedModelDraw::getAnimationFrameCount(const AsciiString &name, int *frames)
{
	if (frames == 0)
		return false;

	HTreeClass *found;
	if (m_moduleData->m_numberByLOD135)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BA3Get(getDrawable(), 0));
	else if (m_moduleData->m_numberByStatus134)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BE5Get(getDrawable(), m_index0BC));
	else
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, false, 0);

	if (found == 0)
		return false;
	Rva000BF953Clip *clip = reinterpret_cast<Rva000BF953Clip *>(found);
	*frames = clip->getNumFrames();
	clip->getFrameRate();
	clip->releaseRef();
	return true;
}

// ?rva000C2E3A@W3DScriptedModelDraw@@QAE?AVAsciiString@@ABV2@@Z
// retail 0x000C2E3A..0x000C32C7 (1165 bytes).
// Model variant resolver called twice by W3DScriptedModelDraw::setModelState
// (0x000C4E23 at 0x000C4FDC; WorldBuilder twin 0x00932CA0) and from
// 0x0007A9A6: the model name with its level-of-detail suffix (0x000B69EA on
// the kind from 0x000B2BA3 or 0x000B2BE5), reporting once per name a model
// that falls back to low detail without StaticModelLODMode and once per name
// a missing low detail model (which falls back to the plain name), then, when
// the module data asks (+0x137), the first existing "_[n][d|e|r][s]" variant
// for the current model condition flags at +0x17C (NIGHT 7 DAMAGED 3
// REALLY_DAMAGED 4 RUBBLE 5 SNOW 8 in Zero Hour's ModelConditionFlagType
// order).
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/Rva007739F0ModelVariant.cpp (BFME1 0x007739F0, /O2); the
// control flow, statics, report text and suffix loops carry over. Target
// facts: module data flags +0x134/+0x135/+0x137, the kind member +0xBC, the
// condition flags +0x17C, the template name at +0x64 of the drawable's
// template, the three-argument debug stream opener and the out-of-line kind
// helper 0x000B2BE5 (BFME1 inlined that choice). WorldBuilder twin 0x00948520
// (4052 bytes) has the same calls, strings and order.
AsciiString W3DScriptedModelDraw::rva000C2E3A(const AsciiString &modelName)
{
	AsciiString name = modelName;
	if (name.isEmpty())
		return name;

	const Rva000BF953ModuleData *data = m_moduleData;
	// forcedLow lives in this block only: retail reuses its frame slot for
	// the appended character below.
	{
		Bool forcedLow = false;
		Int kind = Rva000B2BA3Get(m_drawable, &forcedLow);

		if (data->m_numberByLOD135 || forcedLow)
			name = Rva000B69EAGet(modelName, kind);
		else if (data->m_numberByStatus134)
			name = Rva000B69EAGet(modelName, Rva000B2BE5Get(m_drawable, m_index0BC));

		if (!data->m_numberByLOD135 && forcedLow)
		{
			static _STL::set<AsciiString> s_reportedStaticLOD;
			_STL::set<AsciiString>::iterator found = s_reportedStaticLOD.find(name);
			if (found == s_reportedStaticLOD.end())
			{
				s_reportedStaticLOD.insert(name);
				if (_bfme_debugReportingEnabled())
				{
					_bfme_debugRecordCallsite(1);
					theDebug->slot60();
					(theDebug->slot6C(0, 0, 0) << *(const StringBase<char> *)&name
						<< " INI setting required: Model "
						<< ((const Drawable *)getDrawable())->getTemplate()->getName()
						<< " does not have StaticModelLODMode = Yes entry... Please correct this. Still attempting low detail use.")
						.slot4C(2);
				}
			}
		}

		if (!Render_Obj_Exists(name.str()))
		{
			if (forcedLow)
			{
				static _STL::set<AsciiString> s_reportedMissing;
				_STL::set<AsciiString>::iterator found = s_reportedMissing.find(name);
				if (found == s_reportedMissing.end())
				{
					s_reportedMissing.insert(name);
					if (_bfme_debugReportingEnabled())
					{
						_bfme_debugRecordCallsite(1);
						theDebug->slot60();
						(theDebug->slot6C(0, 0, 0) << *(const StringBase<char> *)&name
							<< " MISSING: Model " << ((const Drawable *)getDrawable())->getTemplate()->getName()
							<< " requires low detail model " << *(const StringBase<char> *)&name
							<< " but doesn't exist, so using regular model " << *(const StringBase<char> *)&modelName
							<< ". Please add this model for horde performance reasons.")
							.slot4C(2);
					}
				}
			}
			name = modelName;
		}
	}

	if (data->m_findVariant137)
	{
		Bool snow = m_conditions17C.test(MODELCONDITION_SNOW);
		Bool night = m_conditions17C.test(MODELCONDITION_NIGHT);
		if (!m_conditions17C.test(MODELCONDITION_RUBBLE)
			&& !m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
			&& !m_conditions17C.test(MODELCONDITION_DAMAGED)
			&& !night && !snow)
			return name;

		for (Int damage = 3; damage >= 0; --damage)
		{
			switch (damage)
			{
			case 3:
				if (!m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 2:
				if (!m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			case 1:
				if (!m_conditions17C.test(MODELCONDITION_REALLY_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_DAMAGED)
					&& !m_conditions17C.test(MODELCONDITION_RUBBLE))
					continue;
				break;
			}

			for (Int n = 1; n >= 0; --n)
			{
				if (n && !night)
					continue;
				for (Int s = 1; s >= 0; --s)
				{
					if (s && !snow)
						continue;

					AsciiString candidate = name;
					appendChar(candidate, '_');
					if (n)
						appendChar(candidate, 'n');
					switch (damage)
					{
					case 1:
						appendChar(candidate, 'd');
						break;
					case 2:
						appendChar(candidate, 'e');
						break;
					case 3:
						appendChar(candidate, 'r');
						break;
					}
					if (s)
						appendChar(candidate, 's');
					if (Render_Obj_Exists(candidate.str()))
						return candidate;
				}
			}
		}
	}
	return name;
}

// ZH W3DModelDraw.cpp parseBoneNameKey is the semantic guide; WB925020
// and retail C2BD1 independently prove the token/registration/key path.
#include <vector>
class INI {
public:
 const char *getNextToken(const char *separators = 0);
 static void Rva000C2C5FParseBoneRecord(INI *, void *, void *, const void *);
 static void Rva000C2CA4ParseTurretPitch(INI *, void *, void *, const void *);
};
class Rva000C2AA4 {
public: void rva000C2AA4(const AsciiString &);
private: char unmodelled[0x78]; AsciiString *begin; AsciiString *end; void *storage;
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator {
public: NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
static __declspec(noinline) void parseBoneNameKey(INI *ini, void *instance, void *store, const void *)
{
 Rva000C2AA4 *self = static_cast<Rva000C2AA4 *>(instance);
 NameKeyType *key = static_cast<NameKeyType *>(store);
 AsciiString tmp(ini->getNextToken());
 ((StringBase<char> &)(tmp)).toLower();
 if (self) self->rva000C2AA4(tmp);
 if (tmp.isEmpty() || tmp.isNone()) *key = NAMEKEY_INVALID;
 else *key = TheNameKeyGenerator->nameToKey(((const StringBase<char> *)&tmp)->str());
}
struct BfmePod24 { int a[6]; };
struct Rva000C2C5FRecord {
 int key, at04; float at08, at0C; int at10, at14;
 Rva000C2C5FRecord() : key(0), at04(0), at08(0.0f), at0C(0.0f), at10(0), at14(0) {}
};
struct Rva000C2C5FOwner {
 char unmodelled[0xD0]; _STL::vector<BfmePod24> records;
};
void INI::Rva000C2C5FParseBoneRecord(INI *ini, void *instance, void *, const void *userData)
{
 Rva000C2C5FRecord record;
 parseBoneNameKey(ini, instance, &record.key, userData);
 static_cast<Rva000C2C5FOwner *>(instance)->records.push_back(
  reinterpret_cast<const BfmePod24 &>(record));
}

// Native379B C2CBF..C2E3A; same-valued finish expression keeps native prepass registers.
// Semantic guide: BF1 f98983a7 TextureSelection007781C0.cpp. Retail379
// changes the receiver offsets and returns two AsciiString vectors; WB932920
// additionally proves the equal-length synchronization pass.
struct Rva000C2CBFTextureEntry {
 AsciiString name; _STL::vector<AsciiString> choices; int unmodelled10;
};
struct Rva000C2CBFData {
 char at00[0x7C]; _STL::vector<Rva000C2CBFTextureEntry> textures;
 bool synchronized; char at89[0xB8-0x89]; bool useRelatedSeed;
};
struct Rva000C2CBFObject {
 char at00[0xFC]; char *related; char at100[0x364-0x100]; int seed;
};
static inline int clampTexturePick(int value, int low, int high)
{
 if (value < low) return low;
 if (value > high) return high;
 return value;
}
void W3DScriptedModelDraw::rva000C2CBF(int count, _STL::vector<AsciiString> *originals, _STL::vector<AsciiString> *replacements)
{
 replacements->clear(); originals->clear();
 Rva000C2CBFData *data = reinterpret_cast<Rva000C2CBFData *>(m_moduleData);
 Rva000C2CBFObject *object = reinterpret_cast<Rva000C2CBFObject *>(m_drawable);
 int seed;
 if (data->useRelatedSeed) seed = *reinterpret_cast<int *>(object->related + 0x78);
 else seed = object->seed;
 int ordinal = 0;
 bool synchronized = data->synchronized;
 if (synchronized) {
  int length = -1;
  for (_STL::vector<Rva000C2CBFTextureEntry>::const_iterator it = data->textures.begin(); it != data->textures.end(); ++it) {
   int n = static_cast<int>((synchronized ? it->choices.end() : it->choices.end())-it->choices.begin());
   if (n != length) {
    if (length != -1) { synchronized = false; break; }
    length = n;
   }
  }
 }
 int pick = 0;
 bool selected = false;
 for (_STL::vector<Rva000C2CBFTextureEntry>::const_iterator it = data->textures.begin(); it != data->textures.end(); ++it, ++ordinal) {
  int upper = clampTexturePick(count - 1, 0, static_cast<int>(it->choices.size()) - 1);
  if (!it->choices.empty()) {
   if (!synchronized || !selected) {
    int value = (seed + seed/3 + seed/5 + ordinal + (seed & 15)*(ordinal+1)) % it->choices.size();
    pick = clampTexturePick(value, 0, upper);
    selected = true;
   }
   if (it->choices[pick].compareNoCase(it->name) != 0) {
    replacements->push_back(it->choices[pick]);
    originals->push_back(it->name);
   }
  }
 }
}

// Native C2CA4..C2CBF, 27B: TurretPitch FieldParse at BCAD00 selects
// word+4 in the last24B turret record. The same-unit private bone-key
// helper retains its proven ECX/EDI ABI; no new helper alias is introduced.
void INI::Rva000C2CA4ParseTurretPitch(INI *ini, void *instance, void *, const void *userData)
{
 Rva000C2C5FOwner *owner = static_cast<Rva000C2C5FOwner *>(instance);
 parseBoneNameKey(ini, instance, &owner->records.back().a[1], userData);
}

// Retail 0x000B5FE6..0x000B61AB (453B), same-this collision-type updater
// called by scripted/horde model-state changes and the +0x50-guarded vslot.
// WB 0x00949620 preserves the branches and calls; its BitFlags label belongs
// to an inline assertion, not this function. The original method name is unknown.
// ZH W3DModelDraw.cpp supplies the collision-selection/rubble purpose; BFME2
// native accesses establish every offset and added condition used here.
// Keep local-control paths separate: joining them into else-if changes GRA.
// Named team/player snapshots preserve the native argument/receiver load order.
void W3DScriptedModelDraw::rva000B5FE6(){
 Rva000B5FE6Drawable *d=(Rva000B5FE6Drawable*)m_drawable;Rva000B5FE6Template *t=d->definition;
 if(!t)return;
 if(mode==-1){if((t->flags[0]&2)||(t->flags[1]&0x10000000))render->addFlags(4,true);}else if(mode==1)render->addFlags(4,true);
 if(t->flags[0]&0x40)render->addFlags(8,true);
 else if((t->flags[3]&2)||(t->flags[4]&0x100))render->addFlags(0x200,true);
 Object *o=d->object;
 if(render->flags()&4){
  unsigned f=4;
  if((t->flags[2]&0x4000000)||(t->flags[0]&0x400)||(t->flags[5]&0x1000))f|=0x80;
  if(o){Team *team=o->team; Player *player=ThePlayerList->local;Relationship r=player->getRelationship(team);
   bool local=o->isLocallyControlled(); if(local)f|=0x100;
   if(!local && r==ENEMIES && !(o->definition->flags[1]&0x10000000))f|=0x10;
  }
  render->addFlags(f,true);
 }
 if(t->flags[2]&0x10)render->addFlags(0x20,true);
 if(t->flags[2]&0x1000)render->addFlags(0,true);
 if(o){
  if(o->state437&0x10)render->addFlags(0x40,true);
  Rva000B5FE6Template *ot=o->definition;
  if(!(ot->flags[0]&0x400000) && !(o->definition->flags[0]&0x1000000) && !o->definition->special632) {
    if((o->definition->flags[0]&0x80) && d->testStatus(5))render->addFlags(0,true);
    else if(o->state438&1)render->addFlags(0,true);
  }
 }
 if(m_moduleData->hidden)render->addFlags(0,true);
}
