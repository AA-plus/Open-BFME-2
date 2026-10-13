// ?rva005F4891@Rva005F4891@@QAEXXZ
// partial score=0.75 date=2026-10-13
// 0x005F4891 (91B) virtual-base-adjusted cleanup, home TU
// StrategicInGameUIArmyUnitIcon.cpp (contiguous 0x5F4891+91=0x5F48EC+43=
// 0x5F4917 rowed here; flags resolve all 3 calls; non-EH insns positional).
// Trial 1 (plain statements) emits NO EH at all: retail has C++ EH states
// (and-0 before GameFree, or-(-1) after) so a cleanup exists. try/catch
// around GameFree is REFUTED (forces ebx/edi frame bloat). Retail FuncInfo
// tryCount=0 (pure unwind). UnwindMap state 0 -> funclet 0x7A5218:
//   mov ecx,[ebp-0x10]; sub ecx,0x14; jmp 0x5F8F96
// i.e. on unwind it destroys entity (dtor 0x5F8F96) at this-0x14, while the
// normal epilogue destroys entity (dtor 0x5F422C) at this-0x10. Same wall
// class as twins 0x5E4202/0x5E426F (their funclets: sub ecx,0x10; jmp
// parent-dtor, no stack access): needs the true secondary-entry/virtual-base
// hierarchy, not expressible with stack locals (any local forces lea).
// Next: identify 0x5F8F96 + the icon virtual-base layout (cf 0x5F4179 note
// on shared ArmyDetailsPanel icon virtual bases), then real-hierarchy dtor.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
void __cdecl Rva00030830GameFree(void *);
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005F4891 { public: void rva005F4891(); };
void Rva005F4891::rva005F4891()
{
    unsigned int subobject = *(unsigned int *)((char *)this - 0x20);
    unsigned int table = *(unsigned int *)(subobject + 4);
    *(unsigned int *)(table + (unsigned int)this - 0x20) = 0x00C794AC;
    subobject = *(unsigned int *)((char *)this - 0x20);
    table = *(unsigned int *)(subobject + 4);
    *(unsigned int *)(table + (unsigned int)this - 0x24) = table - 0x20;
    void *heap = *(void **)((char *)this - 0x10);
    if (heap != 0)
        Rva00030830GameFree(heap);
    TargetRef00217D4C *ref = *(TargetRef00217D4C **)((char *)this - 0x14);
    if (ref != 0)
        ReleaseTreeHintRef00217D4C(ref);
}
