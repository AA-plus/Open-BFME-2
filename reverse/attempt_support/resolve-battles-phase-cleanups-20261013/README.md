# Resolve-battles phase member cleanups

Read the complete Code/GameEngine/Source/Common/Rva00576C4BDtor.cpp and
its complete callee provider Rva005CD651Dtor.cpp. The existing source retains
address-derived class names and target-proven 0x48-byte three-base lifetime.
The original member type identities remain unknown; no new donor identity or
layout claim is introduced. Existing source comments distinguish named phase
WB/vtable evidence from the retained address-derived destructor identity.

The complete 186-byte destructor at 0x00576C4B and 232-byte constructor at
0x00576DF1 both reproduce retail, as do their complete native associative
exception graphs. Those graphs own these Ghidra-bounded eleven-byte cleanups:

* 0x0079B559, $L709, destructor: `8b4df083c130e94521e3ff`.
* 0x0079B5AD, $L752, constructor: `8b4df083c130e9f120e3ff`.

Each loads saved this at EBP-0x10, adjusts to member +0x30, and jumps to
Rva005CD651::~Rva005CD651 at 0x005CD6A9. The entire 67-byte provider and its
complete exception graph independently verify EXACT. Its normal build passes
both rows. verify.py checks the complete parents, native graphs, full cleanup
extents, every relocation, and complete provider. Run normal builds of both
source files before replaying the proof. Before these rows the owning file's
normal build passes all seven rows; no undeclared definition blocks the file.

The before-row identity audit has one inherited duplicate definition:
`??0Base0_00576C4B@@QAE@XZ` (identity-before.json). No finding is suppressed,
no baseline is enlarged to hide it, and no source, header, compiler flag,
pin, alias, global or marker is changed. The new bodies are compiler-emitted
cleanups of real C++ parents, with ownership established by the whole native
exception graphs rather than adjacency.

place_bodies finds zero further bodies or pins. The old local census
(2026-10-02, 6963cc017c) reports unresolved translator/phase/helper/global
providers for this file; link_check therefore cannot establish a new clean
linking result. These additions make no linking-progress claim.
