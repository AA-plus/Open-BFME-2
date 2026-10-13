# TeamTemplateInfo script-array construction cleanup

Read the entire TeamTemplateInfoInitFromDict.cpp again after the foreign
assembly-file claim was released. Existing target class identity comes from
the C1AE70 vtable getter/WB EEF600; loader and destructor establish the Snapshot
base and 0x1EC layout. Existing constructor comments distinguish the donor
behavioral guide. Native array setup/teardown proves32 four-byte strings at
+0x118. The original script member names are carried from the donor guide.

The whole399B constructor at0x003A26E6 and complete native associative EH graph
are EXACT. The graph binds the Ghidra24B cleanup0x007817FB to compiler label
$L1369, resolving the assembly row's unknown-parent qualification:

`6839ba88006a206a048b45f0051801000050e8fe78eaffc3`

It pushes the real AsciiString destructor0x0048BA39,count32,stride4 and the
saved-this pointer at EBP-0x10 plus0x118, then calls CRT iterator0x00629110.
Parent and frame ownership are proven by native graph, not adjacency. The
existing real C++ member array emits every byte naturally. Repoint the one
existing24B assembly row to the owning C++ source; no duplicate range or new
original symbol identity is introduced. The orphan assembly text is unchanged.
This moves24 bytes from ASM-only exact coverage to C++ exact coverage.

verify.py checks the complete parent/graph, cleanup extent and both relocations,
full5B AsciiString destructor, full133B narrow releaseBuffer and its existing
folded StringBase destructor spelling. Both133B native EH graphs are EXACT;
the5B destructor has no EH data on either side. It also checks the full96B
CRT iterator from msvcrt.lib, which remains existing prebuilt provenance.
Both complete provider sources were read. Normal builds pass15 ascii_string
rows and7 StringBaseWideReleaseBuffer rows, including six named imports.
Run normal builds of these sources, TeamTemplateInfoInitFromDict.cpp and
??_M@YGXPAXIHP6EX0@Z@Z before replaying verify.py.

The owning source's three original rows and frozen-file check pass; identity
before has zero findings. The previously inspected complete graph's other
cleanup siblings are already C++-backed. Prior place_bodies found no additional
bodies or pins. The old local6963cc017c census lacks the owning file, so no clean
linking result is claimed. No source/header/flags/global/pin/alias/marker edits.
