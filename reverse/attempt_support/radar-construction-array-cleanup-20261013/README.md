# Radar construction event-array cleanup

Read the complete RadarRva002D7BD3.cpp, RadarDtor.cpp, and Radar_reset.cpp.
The existing target vtables, constructor/destructor pair and adjacent rowed
methods establish Radar identity and the 64 event records at +0x2C, each 0x50
bytes. Existing source comments distinguish BFME1 Radar behavior from target
MI adjustments and field offsets. This addition asserts no new type names.

The complete 207-byte Radar constructor at 0x002D87B9 and its entire native
associative exception graph are EXACT. The graph uniquely owns the 22-byte
Ghidra-bounded body at 0x00777A24, object label $L459:

`68e07c6d006a406a508b45f083c02c50e8d716ebffc3`

It passes the actual RadarEvent destructor at 0x002D7CE0, count 64, stride 80,
and saved this at EBP-0x10 plus 0x2C to the existing CRT vector-destructor
iterator 0x00629110. The native graph proves ownership and the frame slot;
the C++ member array proves the emitted lifetime operation.

verify.py independently checks the complete parent and graph, full cleanup
and both relocations, the entire seven-byte RadarEvent constructor, thirteen-
byte RadarEvent destructor, eleven-byte RadarEventRef::release, and existing
96-byte CRT iterator from msvcrt.lib's ehvecdtr.obj member. The three C++
providers have no EH data on either side. The CRT is existing prebuilt
provenance, not newly recovered C++; only this 22-byte cleanup earns credit.

The original owning file passes all four rows, RadarDtor all six, Radar_reset
all four, and the named CRT iterator its one normal library verification.
Before-row code identity has zero findings (identity-before.json). No source,
header, flags, pins, aliases, globals or markers change. place_bodies finds
zero further bodies or pins. The old local link census does not establish a
new clean linking result: it reports unresolved RadarSecondBase destructor/unused
and selected SubsystemInterface-constructor/Snapshot-deleting-destructor copies
that it judges non-retail. These are old census results; no linking gain is claimed. Run normal builds
of those three sources and ??_M@YGXPAXIHP6EX0@Z@Z before replaying verify.py.
