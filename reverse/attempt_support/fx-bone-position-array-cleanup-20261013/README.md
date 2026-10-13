# Bone-position local array cleanup

Read the complete FXListAtBonePosFXNugget_doFxAtBones.cpp and coord3d.cpp.
The existing named parent applies effects at bone positions: its target
calls retrieve a Drawable, collect bone positions and transforms, convert
both to world coordinates and dispatch a positional effect. The GeneralsMD
FXList.cpp definition at the verified BFME1 reference pointer
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 provides the same named behavioral
and structural guide; its layout and constants are not independently assumed
to be BFME2 facts. Target code proves the 40-element, 12-byte coordinate array.

The full 283-byte parent at 0x001E2DD6 and its complete native associative
exception graph are EXACT. The graph identifies the Ghidra-bounded 22-byte
cleanup at 0x00769E44 as compiler label $L1335, resolving the old log's
unknown-parent blocker without inferring ownership from adjacency:

`68d03f4b006a286a0c8d85d4fdffff50e8b7f2ebffc3`

It pushes the existing Coord3D destructor at 0x000B3FD0, count40, stride12,
and the frame-local array at EBP-0x22C, then calls the existing CRT EH vector
destructor iterator at 0x00629110. The real C++ local array emits it naturally.
The complete native graph has no additional unrowed cleanup siblings.

verify.py checks the complete parent, graph, cleanup extent and both
relocations. It independently verifies the complete three-byte Coord3D
constructor and one-byte destructor from the existing 68-row coord3d.cpp,
plus the existing 96-byte CRT iterator from msvcrt.lib. The CRT remains
prebuilt provenance and earns no new C++ credit. Run normal builds of both
sources and ??_M@YGXPAXIHP6EX0@Z@Z before replaying verify.py.

Normal verification passes both original owning rows, one empty-string
reference, and all68 coordinate-provider rows (three strings/nine floats).
Frozen-file inspection passes; the before-row identity audit has zero
findings. place_bodies finds no additional bodies or pins. The old local
census at6963cc017c does not contain the owning file, so this is no claim of
new clean linking. No source, header, flags, globals, pins, aliases or markers
are changed. Existing private views remain existing debt.
