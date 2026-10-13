# Attack-move allocation cleanups and frame handler

Read the entire AIAttackMoveStateMachine.cpp. Existing ZH AIStates.cpp donor
structure is distinguished from BFME2 vtable/name-getter, constructor-call,
name-key and field-access evidence in the source. Native target evidence
identifies the two state constructors and their allocation of an attack-move
machine; the four complete parent bodies and native EH graphs verify EXACT:
206B at34C6EF,147B at34EBE8,113B at34F153,158B at34E307.

Two Ghidra10B cleanup bodies are emitted naturally by new expressions:
- 0x0077CFFE ($L733): ff7508e85a2d8bff59c3, allocation saved at EBP+8.
- 0x0077D01A ($L768): ff750ce83e2d8bff59c3, allocation saved at EBP+0xC.
Each pushes the saved pointer, calls scalar operator delete0x0002FD60, pops
the argument and returns. Native parent graph proves ownership/frame reuse;
no adjacency inference. Each cleanup is banked as its own commit.

The206B machine constructor installs handler0x0077CF93. Its complete10B
compiler-emitted body b8e868d200e9e5c1eaff loads native FuncInfo RVA9268E8 and
tail-jumps to629182. Extent follows the complete MOV/JMP body and COFF/native
parent graph, without requiring a Ghidra function label. The existing6B thunk
629182 imports msvcr71.dll!__CxxFrameHandler through slotVA00BBA6C8. Normal
build.sh verification of that row checks the named import. The handler is
banked separately using its compiler symbol, no object-symbol alias.

verify.py checks allfour whole parents/graphs, both cleanup extents and
relocations, the handler and its FuncInfo/import-thunk targets, the full21B
scalar operator delete and existing6B import thunk. No new credit is claimed
for providers. Run the owning source, mem_ops.cpp and ?ji_00629182@@YAXXZ
through normal build.sh before replaying this proof.

Whole-file inspection also finds8B base cleanups77CFF6 and77D012. Their
native target368793 is already rowed as a five-byte destructor forwarding to
33FF2B. This source's Rva0034005D/Rva00342BAE destructor names remain unresolved,
as does their AIInternalMoveToState destructor dependency. Their current
strict bytes have unresolved calls; do not land them by assigning a pin.
A class/destructor identity reconciliation and independently proven fold are
needed. These deferrals do not affect the two verified operator-delete calls.
Other cleanup siblings already have C++ rows.

Normal owning source passes11 original rows, frozen-file inspection and
before-row identity audit (zero findings); place_bodies finds no more bodies
or pins. Old local6963cc017c census lacks the source; no clean linking claim.
No source/header/flag/global/pin/alias/marker change is made for these rows.
