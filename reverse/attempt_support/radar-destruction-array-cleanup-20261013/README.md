# Radar destruction event-array cleanup

Read the complete RadarDtor.cpp, RadarRva002D7BD3.cpp and Radar_reset.cpp
while recovering the paired Radar array lifetimes. Existing target vtables,
constructor/destructor relationships and field accesses prove the Radar
identity, 64 events at +0x2C and their 0x50-byte stride. The source records its
BFME1 behavioral guide separately from target MI and layout facts. No new
original type identity is inferred.

The complete 98-byte Radar destructor at 0x002D7CED and its entire native
associative exception graph are EXACT. That graph owns the Ghidra-bounded
22-byte cleanup at 0x007779F1, object label $L7319:

`68e07c6d006a406a508b45f083c02c50e80a17ebffc3`

The body pushes the real RadarEvent destructor at 0x002D7CE0, count 64,
stride 80 and saved this at EBP-0x10 plus 0x2C, then calls the existing CRT
exception-aware vector-destructor iterator at 0x00629110. Native exception
ownership identifies the parent and frame slot; no adjacency inference is
used. The real C++ member array emits this cleanup naturally.

verify.py independently checks the complete parent/graph, cleanup extent and
both relocations, the entire seven-byte event constructor, thirteen-byte
event destructor, eleven-byte RadarEventRef::release, and the existing full
96-byte CRT iterator from msvcrt.lib's ehvecdtr.obj member. The three C++
providers have no EH data on either side. The CRT is existing prebuilt
provenance; only the new 22-byte cleanup earns C++ coverage.

Normal verification passes all six original owning rows, the five current
constructor-unit rows, four Radar_reset rows and named CRT iterator. The
before-row identity audit has zero findings (identity-before.json). No source,
header, flags, pins, aliases, globals or markers are changed. place_bodies
finds no further bodies or pins. The old local census (6963cc017c, 2026-10-02)
reports selected SubsystemInterface-destructor and Snapshot-deleting-destructor
copies that it judges non-retail; no new clean linking result is claimed.
Run normal builds of all three source files and ??_M@YGXPAXIHP6EX0@Z@Z before
replaying verify.py.
