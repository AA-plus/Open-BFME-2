# Pitch/roll corner-array exception bodies

Read all of DrawableCalcPitchRollRva00270276.cpp. Existing identity evidence
uses the named WorldBuilder calcPitchRoll twin and retail callers/callee graph;
the source retains the pinned address-derived spelling and existing argument
views. Terrain/footprint field meanings are structural inferences as documented
there. No new class layout or original-name assertion is introduced.

The entire 931-byte parent at 0x00270276 and its complete native associative
exception graph are EXACT. The graph binds $L1147 to the 19-byte Ghidra extent
at 0x007732D5:

    68d03f4b006a046a0c8d458c50e8295eebffc3

It supplies destructor 0x000B3FD0, count 4, stride 12 and the corner array at
EBP-0x74 to CRT vector-destructor iterator 0x00629110. Every byte and both
relocations compare strictly. The real C++ array naturally emits the cleanup.
The 3-byte coordinate constructor and 1-byte destructor in coord3d.cpp also
compare strictly; the normal provider build passes all 68 rows.

Whole-file graph inspection finds an unrowed 10-byte handler at 0x007732E8,
installed by this same parent. Its full bytes are b834a0d100e9905eebff: MOV
FuncInfo RVA 0x0091A034 then JMP 0x00629182. Complete COFF extent, native
parent installation and terminal jump establish the boundary; no Ghidra label
or adjacency assumption is needed. The compiler's own __ehhandler$<parent>
name is retained. The existing 6-byte import thunk is strictly checked and
normal build.sh verifies its msvcr71.dll!__CxxFrameHandler import. The CRT
implementation itself is not newly reconstructed.

The before-row identity audit has zero findings; frozen-file inspection passes.
Normal owning-file build verifies the original 931-byte row and four float
literals. place_bodies finds no further ordinary bodies or pins. The old local
census 6963cc017c has no entry, so no linking gain is claimed. No source,
header, flag, pin, alias, marker or private-class exception is added or changed.

Before replay, run normal build.sh for this source, coord3d.cpp,
?ji_00629182@@YAXXZ and ??_M@YGXPAXIHP6EX0@Z@Z. verify.py compares the whole
parent, complete graph, full cleanup and handler including every relocation,
both coordinate lifetimes, the 6-byte import thunk and entire 96-byte existing
CRT archive member. Existing providers do not earn new bytes. Bank the two
new bodies in separate commits.
