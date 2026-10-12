// cl: /DNDEBUG /MD
//
// ?q4Notify002CC841@@YAXPAXPAVMade002CC841@@HH@Z @0x00509780 (77B).
// ProjectileNugget field parser: MultiIni tmp, add table from getter
// 0x00507552 with index 0, add FieldParse table at 0x00864640 with
// index 0, then INI initFromINIMulti. Caller parseProjectileNugget
// at 0x002CC886. Same tail as q4Notify002CCBCA precedent.

class Made002CC841;

class INI;
class MultiIniFieldParse;

// The projectile-nugget FieldParse table, recovered from retail 0x00864640
// (.rdata, six 16-byte entries plus the null terminator): names are pooled
// field-name literals, parse functions are the rowed INI statics, userData
// is null, offsets walk 0x130-0x14C. Field identifiers are descriptive;
// the original table spelling is unknown.
struct FieldParse
{
    const char *name;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    unsigned int offset;
};

class INI
{
public:
    void initFromINIMulti(void *p, const MultiIniFieldParse &m);
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
    static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
    static void parseBool(INI *ini, void *instance, void *store, const void *userData);
    static void Rva005096FF_ParseWeaponSlot(INI *ini, void *instance, void *store, const void *userData);
};

extern const char BfmeProjectileWarheadTemplateNameField[];
const char BfmeProjectileWarheadTemplateNameField[] = "WarheadTemplateName";
extern const char BfmeProjectileTemplateNameField[];
const char BfmeProjectileTemplateNameField[] = "ProjectileTemplateName";
extern const char BfmeProjectileStreamNameField[];
const char BfmeProjectileStreamNameField[] = "ProjectileStreamName";
extern const char BfmeWeaponLaunchBoneSlotOverrideField[];
const char BfmeWeaponLaunchBoneSlotOverrideField[] = "WeaponLaunchBoneSlotOverride";
extern const char BfmeAlwaysAttackHereOffsetField[];
const char BfmeAlwaysAttackHereOffsetField[] = "AlwaysAttackHereOffset";
extern const char BfmeUseAlwaysAttackOffsetField[];
const char BfmeUseAlwaysAttackOffsetField[] = "UseAlwaysAttackOffset";

const FieldParse TheProjectileFieldTable[] = {
    { BfmeProjectileWarheadTemplateNameField,   INI::parseAsciiString,            0, 0x130 },
    { BfmeProjectileTemplateNameField,          INI::parseAsciiString,            0, 0x134 },
    { BfmeProjectileStreamNameField,            INI::parseAsciiString,            0, 0x138 },
    { BfmeWeaponLaunchBoneSlotOverrideField,    INI::Rva005096FF_ParseWeaponSlot, 0, 0x13C },
    { BfmeAlwaysAttackHereOffsetField,          INI::parseCoord3D,                0, 0x140 },
    { BfmeUseAlwaysAttackOffsetField,           INI::parseBool,                   0, 0x14C },
    { 0, 0, 0, 0 }
};

int __cdecl Rva00507552Get();

class MultiIniFieldParse
{
public:
    MultiIniFieldParse();
    void add(const FieldParse *p, unsigned int u);

    char m_pad[0x84];
};

void q4Notify002CC841(void *ini, Made002CC841 *m, int c, int d)
{
    MultiIniFieldParse tmp;
    tmp.add((const FieldParse *)Rva00507552Get(), 0);
    tmp.add(TheProjectileFieldTable, 0);
    ((INI *)ini)->initFromINIMulti(m, tmp);
}
