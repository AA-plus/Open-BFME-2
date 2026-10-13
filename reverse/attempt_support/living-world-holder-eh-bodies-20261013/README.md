# LivingWorld holder exception bodies

Read all of Rva0057590EHolderSet.cpp: the 151-byte region-based setter at
0x0057590E and the 277-byte value-based setter at 0x005757F9, all declarations,
and both allocation branches. Existing evidence comes from target callers,
virtual slots, field accesses, allocation sizes and rowed callees. WorldBuilder
and the matched sibling setter are compiler-shape leads; class and field
identities remain unresolved as documented in the unchanged source.

Both whole parents and both complete native associative exception graphs are
EXACT. The value-based setter owns two 10-byte allocation-failure cleanups,
also independently bounded by Ghidra:

- 0x0079B1DE, $L733: ff75e8e87a4b89ff59c3, saved allocation at EBP-0x18.
- 0x0079B1E8, $L734: ff75ece8704b89ff59c3, saved allocation at EBP-0x14.

Both call scalar operator delete 0x0002FD60 and remove the pushed argument.
They are naturally emitted by the real C++ new expressions for the alternative
0x24-byte and 0x10-byte allocations. Native graph ownership establishes the
saved-frame relationship. The other parent's cleanup at 0x0079B1FC already
has a matched C++ row and is not counted again.

Whole-file graph inspection also finds two unrowed 10-byte native handlers:

- 0x0079B1F2: b81405d500e986dfe8ff, installed by parent 0x005757F9,
  with FuncInfo RVA 0x00950514.
- 0x0079B206: b83805d500e972dfe8ff, installed by parent 0x0057590E,
  with FuncInfo RVA 0x00950538.

Each uses the compiler's own __ehhandler$<parent> name. Their extents are
established by the complete COFF bodies and native MOV FuncInfo / terminal JMP
sequence reached from each parent, not a nearby Ghidra label. Both jump to
0x00629182, whose existing 6-byte import thunk is independently verified,
including normal build.sh's named msvcr71.dll!__CxxFrameHandler import check.
The imported runtime implementation is not newly reconstructed here.

verify.py strictly compares both full parents, their complete graphs, all four
new bodies and every relocation, the whole 21-byte scalar delete provider and
the existing 6-byte import thunk. First run normal build.sh on the owning
source, WWLib/mem_ops.cpp and ?ji_00629182@@YAXXZ. Existing provider bytes do
not add new progress.

The two original rows pass normal verification. Frozen-file inspection passes;
the before-row identity audit has zero findings. place_bodies finds no further
ordinary bodies or pins. This file is absent from old local census 6963cc017c;
no linking gain is claimed. No source, header, flag, pin, alias or marker changes
are needed. Bank each of the four bodies as its own normal commit.
