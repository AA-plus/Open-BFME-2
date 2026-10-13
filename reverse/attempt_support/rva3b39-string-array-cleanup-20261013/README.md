# Address-named record string-array destruction cleanup

Read the complete Rva003B39C7Dtor.cpp and Rva003B39C7Ctor.cpp. The existing
address-named record preserves its unknown original type identity. Target
caller pairing, constructor writes, array setup and destructor calls establish
the twelve four-byte strings at+0x18. The destructor's trailing+0x7C string
view refines the constructor's older scalar view; no broader type unification
is asserted by this cleanup admission.

The whole103B destructor0x002045AB and complete native associative exception
graph are EXACT. The graph owns Ghidra's22B cleanup0x0076C729, compiler$L1170:

`6839ba88006a0c6a048b45f083c01850e8d2c9ebffc3`

It pushes the real AsciiString destructor0x0048BA39,count12,stride4 and
saved-thisEBP-0x10 plus0x18, then calls CRT vector iterator0x00629110.
The native graph proves parent and frame ownership without adjacency inference.
The existing real C++ member array naturally emits the complete cleanup.

verify.py independently checks whole parent/graph, cleanup extent and both
relocations, full5B AsciiString destructor, full133B narrow releaseBuffer and
its existing folded StringBase destructor (including both native EH graphs),
and the full96B prebuilt CRT iterator. No new credit is claimed for those
providers. Normal current builds pass15 ascii_string rows and7 buffer-release
rows, including six named imports. Run those sources, the owning source and
??_M@YGXPAXIHP6EX0@Z@Z through normal build.sh before replaying verify.py.

The whole owning source passes both original rows and frozen-file inspection.
The before-row identity audit has zero findings. Its other three11B cleanups
are already generated C++ rows. place_bodies finds zero further bodies/pins.
link_check against the old6963cc017c census predicts the source links with its
existing103B; this is not a fresh census or a claim of a new measured linking
gain. No source/header/flag/global/pin/alias/marker edits accompany this row.
