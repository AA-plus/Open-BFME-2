// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z
// partial score=0.97 date=2026-10-13
// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z
// partial score=0.97 date=2026-10-13
// W7-SOL2 r1 (chain.py seed): _ReadWriteBarrier after the end read + begin inlined into its two uses => size-exact 116 (was 117), residue 6 instr: retail loads end->ecx then begin->eax (a1 form) and keeps count in ecx; ours end->eax, begin->ecx.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z
// partial score=0.96 date=2026-10-01
// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z retail 0x002197A6 116B:
// find an entry by id in the 8 GameInfo slots when the game info exists, else
// in the global vector [0x009FE358,0x009FE35C). Levers measured 2026-10-01:
// /arch:SSE gives the retail cmove in the vector loop; declaring result before
// i makes xor esi,esi (i) precede xor edi,edi (result) and reuse esi as the
// zero for the null test. Left (40 B of diffs, same length): the vector loop
// registers rotate: retail end->ecx begin->eax element->edx, cl here
// end->edx begin->ecx element->eax, unchanged by temp-only bodies, pointer
// locals, count-less compare, branch order or a single return.
// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z
// partial score=0.95 date=2026-09-28
// cl: /O1 /G7 /MD /arch:SSE
class Rva002197A6Entry
{
public:
    int m_unk0;
    int m_id;
};
class GameSlot
{
public:
    char m_pad[0x60];
    unsigned char m_has;
    char m_pad61[3];
    Rva002197A6Entry m_obj;
};
class GameInfo
{
public:
    GameSlot *getSlot(int i);
};
extern GameInfo *g_Rva00E02EEC;
extern Rva002197A6Entry **g_Rva009FE358;
extern Rva002197A6Entry **g_Rva009FE35C;
class Rva002197A6
{
public:
    Rva002197A6Entry *rva002197A6(int id);
};
// ?rva002197A6@Rva002197A6@@QAEPAVRva002197A6Entry@@H@Z present-unmatched
Rva002197A6Entry *Rva002197A6::rva002197A6(int id)
{
    Rva002197A6Entry *result = 0;
    unsigned int i = 0;
    if (g_Rva00E02EEC != 0) {
        for (; result == 0 && i < 8; ++i) {
            GameSlot *slot = g_Rva00E02EEC->getSlot(i);
            if (slot == 0)
                continue;
            Rva002197A6Entry *obj = slot->m_has ? &slot->m_obj : (Rva002197A6Entry *)0;
            if (obj == 0)
                continue;
            if (obj->m_id == id)
                result = obj;
        }
        return result;
    } else {

        Rva002197A6Entry **end = g_Rva009FE35C;
        _ReadWriteBarrier();
        unsigned int count = (unsigned int)(end - (g_Rva009FE358));
        for (; result == 0 && i < count; ++i) {
            Rva002197A6Entry *obj = (g_Rva009FE358)[i];
            result = (id == obj->m_id) ? obj : result;
        }
        return result;
    }
}
