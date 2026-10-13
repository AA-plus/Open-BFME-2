# Apt timeline base and record cleanups

The entire source is
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineCtor.cpp`.
The complete 540-byte constructor at 0x005202C8 and 224-byte destructor at
0x005204EF both verify EXACT, including their full native associative
exception graphs. The destructor graph directly locates two complete bodies:

* 0x00796102, 8 bytes, $L6001: saved receiver EBP-0x10 tail-jumps to the
  existing 90-byte _bfme_AptGameWindow destructor at 0x005126F5. Complete
  bytes: `8b4df0e9ebc5d7ff`.
* 0x00796126, 14 bytes, $L6004: the same receiver plus 0x2C4 tail-jumps to
  the existing 63-byte Rva0051C0E7 record destructor at 0x0051E471. Complete
  bytes: `8b4df081c1c4020000e93d83d8ff`.

Both Ghidra extents and every byte/REL32 target agree. The proof script checks
both whole parents, both full exception graphs and both complete cleanups;
location is not inferred from adjacency or a masked placement.

The source already identifies the timeline screen from WorldBuilder's
AptTimeLine constructor, image literals and singleton behavior. That existing
identity evidence is retained; the legacy Rva005202C8 spelling is unchanged.
The +0x2C4 member's 48-byte record layout and teardown relationship are already
recorded with its owned constructor/destructor, while its original record name
remains unknown. No source, pin, global, header, allocator specialization or
class-layout declaration is changed by these two rows.

The normal whole-source gate verifies the two STLport constructor folds,
five string literals and one floating literal. Run it before replaying
`verify.py`. The saved census 6963cc017c does not include this source, so the
link preview cannot establish placement. No linking gain is asserted and no
linking runner was started.
