// Native stance-name table at VA C3C210: six pointers followed by null.
// Complete measured label extents and native indexed consumers are recorded
// in reverse/attempt_support/stance-names-owner/README.md.
// The existing TheStanceNames identifier is retained as the sole table owner.
// Label identifiers are descriptive; their original names are unknown.
// .rdata and all four executable references prove read-only table use.

// Native stance table: six complete NUL-terminated labels and a null.
// Label object names are descriptive; original names are unknown.
// The first label is the pooled string literal: retail 0x0083C260 is the one
// "Uninitialized" that dxerr9 (DXGetErrorDescription9A) also references, so it
// is no separately named object.
extern const char BfmeStanceNameBattle[];
const char BfmeStanceNameBattle[] = "Battle";
extern const char BfmeStanceNameAggressive[];
const char BfmeStanceNameAggressive[] = "Aggressive";
extern const char BfmeStanceNameHoldGround[];
const char BfmeStanceNameHoldGround[] = "HoldGround";
extern const char BfmeStanceNamePorcupine[];
const char BfmeStanceNamePorcupine[] = "Porcupine";
extern const char BfmeStanceNameHoldGroundMoving[];
const char BfmeStanceNameHoldGroundMoving[] = "HoldGroundMoving";
extern const char *const TheStanceNames[];
const char *const TheStanceNames[] = {
    "Uninitialized",
    BfmeStanceNameBattle,
    BfmeStanceNameAggressive,
    BfmeStanceNameHoldGround,
    BfmeStanceNamePorcupine,
    BfmeStanceNameHoldGroundMoving,
    0
};

// Complete native entry 425DC2 follows RET4; its 27 bytes include fallback DD7.
// One signed stack index and full pointer result are observed. Original spelling,
// original owner and any unused parameters remain unknown.
const char *__cdecl Rva00425DC2StanceName(int index)
{
    if (index >= 0 && index < 6)
        return TheStanceNames[index];
    return "Unknown";
}
