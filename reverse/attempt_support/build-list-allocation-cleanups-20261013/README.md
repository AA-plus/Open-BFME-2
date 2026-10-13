# Build-list allocation-failure cleanups

Read the complete BuildListInfoCtor.cpp, both constructor and duplicate method.
Existing provenance uses the ZH SidesList.cpp algorithm, while target vtable,
assignment/copy callers, member accesses and allocation sizes establish the
BFME2 layout and list-copy relationship. No new original base-class identity
is inferred from the constructor's existing EmptyBase shaping view.

The whole165B duplicate method at0x0032A1FE, whole184B constructor0x0032A0CE,
and both complete native associative exception graphs are EXACT. The duplicate
graph owns two independent Ghidra10B cleanup extents:

- 0x0077B4FF ($L1308): ff75f0e859488bff59c3; frees [EBP-0x10].
- 0x0077B509 ($L1309): ff75ece84f488bff59c3; frees [EBP-0x14].

Each passes its saved allocation to the real scalar operator delete0x0002FD60,
removes the argument and returns. The graph establishes ownership/frame slots
for the first node and later linked-list nodes; no adjacency inference is used.
Both are naturally emitted by the real C++ new expressions. Bank them as
separate commits. The constructor's other8B/11B/11B cleanup siblings already
have generated C++ rows.

verify.py checks both whole methods/graphs, full cleanup extents and every
relocation, plus the entire21B scalar operator delete (no EH data on either
side). mem_ops.cpp was read in the preceding verified allocation-cleanup pass;
its four rows pass normal build.sh. Run the owning source and mem_ops.cpp through
normal build.sh before replaying this proof.

Allfour original owning rows pass normal byte verification and frozen-file
inspection. Before-row identity audit has zero findings; place_bodies finds
zero further bodies/pins. Old local6963cc017c census reports unresolved
_vtbl_00C0D904, so no clean linking gain is claimed. The existing vtable alias
is unchanged; no new source/header/flag/global/pin/alias/marker is introduced.
