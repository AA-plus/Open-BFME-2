# Button-record native cleanups

The complete owning source is `Code/GameEngine/Source/Common/Rva005E92F7Dtor.cpp`.
Its real C++ image lookup (149 bytes at 0x005E936A), constructor (140 bytes at
0x005E93FF) and destructor (60 bytes at 0x005E92F7) each reproduce the entire
retail body and complete native associative exception graph. The graph places
these cleanups directly; neither adjacency nor a masked search supplies ownership.

* 0x007A40C3, 13 bytes, compiler label $L1359: the image helper's local-static
  initialization rollback. Both DIR32 references point to its compiler-owned
  guard at data RVA 0x00A06774. The complete bytes are
  `a17467e00024fea37467e000c3`, including the final RET. This restores coverage
  of the real parent emission after the earlier synthetic free-function guard
  was retracted; no separate global or callable guard function is introduced.
* 0x007A40F2, 11 bytes, compiler label $L1378: constructor cleanup loads the
  saved receiver from EBP-0x14, adds 8 for the existing holder base, and tail
  jumps to the already rowed 99-byte destructor at 0x005E12D1. The complete
  bytes are `8b4dec83c108e9d4d1e3ff`, including the native REL32 target.

Ghidra independently gives the complete 13- and 11-byte unwind extents.
`verify.py` replays all three complete parents and exception graphs and checks
both complete cleanup bodies with every relocation against retail.
Run the normal whole-source build before replaying the proof.

Target facts and retained uncertainty are documented separately in
`reverse/identity_evidence/button-record-base-constructor.md` and
`reverse/identity_evidence/image-helper-static-initializer.md`. The record-base
relationship is a code-generation inference, and the original application
class and input type remain unknown. Existing opaque names, binding choices,
and source content are retained. These rows add exact C++ parent emissions;
they do not establish an original application identity or link-census result.

The local `tools/link_check.py` preview reports this source absent from saved
census `6963cc017c`; it cannot preview link placement for this unit. No linking
runner was started and no linking gain is claimed.

The normal commit hook's shadow identity check reports the existing divergent
complete and scalar-deleting destructor copies for `Rva005F5C77Base0`
(`??1Rva005F5C77Base0@@UAE@XZ` and `??_GRva005F5C77Base0@@UAEPAXI@Z`).
The source declaration and definitions were not changed by these cleanup rows;
this inheritance-model debt also appears in the earlier constructor evidence.
The findings remain open and visible; byte equality does not resolve them.
