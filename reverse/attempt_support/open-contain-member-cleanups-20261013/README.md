# OpenContain member cleanups

The complete source `Code/GameEngine/Source/GameLogic/Object/Contain/Rva00465124BaseDtor.cpp`
emits the real 134-byte OpenContainModuleData destructor at 0x00257481.
Its full body and entire native associative exception graph verify EXACT.
The graph independently places both complete 11-byte cleanups, whose extents
also agree with Ghidra:

* 0x00772048, $L466: saved receiver EBP-0x10, member +0x48, tail jump to
  0x00257464. Complete bytes: `8b4df083c148e91154aeff`.
* 0x00772053, $L467: saved receiver EBP-0x10, member +0x4C, tail jump to
  0x00256641. Complete bytes: `8b4df083c14ce9e345aeff`.

These native entries are complete five-byte unadjusted jumps to the existing
member destructor bodies at 0x002572D7 (23 bytes) and 0x00256461 (56 bytes).
The normal symbol resolver already includes these native thunk addresses;
no new pin, alias or relocation masking is introduced. `verify.py` checks the
whole parent, complete graph, both entire cleanups and all relocations, and
independently decodes both complete native thunk bodies to their destinations.

Target ownership comes from the native constructor 0x00465124, vtable
0x00C43658 and scalar destructor 0x00465221 calling this destructor, with the
existing ledger's ModuleFactory identity correction. The constructor's whole
source was also read: its +0x48 list and +0x4C set wrappers use the same
unwind callees. The current destructor source uses the already owned Rva00257464 wrapper
for its +0x48 member and retains the other private member views and opaque names. These cleanups add no original member-type or
new class-layout claim. They are natural compiler emissions of existing C++;
no synthetic parent is used.

Link preview against saved census 6963cc017c (2026-10-02) reports an unresolved
Rva002572D7Member destructor, duplicate/non-retail-selected OpenContain
copy and non-retail-selected Rva003623E5Filter, Rva003623E5Member and Snapshot
scalar destructor copies. The ledger now owns Rva002572D7Member's body, so the
old census is not proof of current placement. These existing reconciliation
issues remain visible; no linking gain is claimed and no link runner started.

The first list-cleanup commit exposed a shadow identity finding: the source
named the base destructor at the native wrapper entry. A local member-view
repair now uses the already owned Rva00257464 empty destructor over the same
four-byte base member, mirroring its existing provider. The compiler inlines
that wrapper in the parent and names it directly in the unwind cleanup. The
entire 134-byte parent, full exception graph, both 11-byte cleanups and emitted
five-byte wrapper remain exact. No new symbol pin, alias, header or marker was
added. This is a code-generation model consistent with the established native
wrapper, not a claim about the original C++ inheritance declaration.
