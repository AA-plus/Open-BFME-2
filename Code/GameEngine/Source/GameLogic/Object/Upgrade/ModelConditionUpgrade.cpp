// ?rva004B65E4@Rva004B65E4@@SAXPAVINI@@PAX1PBX@Z
// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
// Retail 0x004B65E4..0x004B6691: ModelConditionUpgrade's
// RemoveConditionFlagsInRange parser (field table at VA 0x00C58730).
// The native calls establish a 19-dword (591-bit) model-condition set.
// The established copy/intersection providers retain their opaque set name;
// no original spelling for this parser is asserted.
// WB 0x0123DA50 independently exposes BitFlags::test/SetBit assertions;
// the indexed helpers preserve their operation without claiming a class layout
// beyond the native 19-word storage. Stop after filling the second endpoint.
// All callees resolve through existing matched rows; no new address pins.
class INI;
class WeaponTemplateSetHead
{
public:
    unsigned int bits[19];
    __forceinline bool test(int bit) const
    {
        return (bits[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
    }
    __forceinline void set(int bit)
    {
        bits[(unsigned int)bit >> 5] |= 1u << (bit & 31);
    }
    WeaponTemplateSetHead(const WeaponTemplateSetHead &);
    void rva000B3ED3(const WeaponTemplateSetHead &);
};
template<int N> class BitFlags
{
public:
    int count() const;
};
class Rva000B937E
{
public:
    void rva000B937E(INI *, void *);
};
struct INIException
{
    INIException(int, const char *, ...);
    char *mFailureMessage;
    int mErrorCode;
};
extern "C" void __stdcall _CxxThrowException(void *, const _s__ThrowInfo *);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

class Rva004B65E4
{
public:
    static void rva004B65E4(INI *, void *, void *, const void *);
};
void Rva004B65E4::rva004B65E4(INI *ini, void *, void *store, const void *)
{
    WeaponTemplateSetHead *dest = (WeaponTemplateSetHead *)store;
    WeaponTemplateSetHead added(*dest);
    int bit = 0;
    ((Rva000B937E *)dest)->rva000B937E(ini, 0);
    for (unsigned int w = 0; w < 19; ++w)
        added.bits[w] ^= ~0u;
    added.rva000B3ED3(*dest);
    if (((const BitFlags<591> *)&added)->count() != 2)
    {
        INIException e(1, "you must specifly only two bit flags for a range.");
        _CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
    }
    bool first = false;
    bool last = false;
    for (; !last && bit < 591; ++bit)
    {
        if (!first)
        {
            if (!added.test(bit))
                continue;
            first = true;
        }
        else if (added.test(bit))
            last = true;
        dest->set(bit);
    }
}
