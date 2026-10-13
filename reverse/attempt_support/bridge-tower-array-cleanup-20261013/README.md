# Bridge tower-position array cleanup

Read the complete BridgeObjectCtor.cpp, both the 1449-byte constructor and
241-byte createTower method. Existing provenance distinguishes ZH/BFME1
algorithm and naming leads from target layout/call/constant evidence. The
BFME2 polygon and triangle additions, four tower positions and construction
order remain exactly as recovered; no new identity or layout is inferred.

The entire constructor at 0x00280C21 and complete native associative exception
graph are EXACT. That graph binds $L1688 to the 19-byte Ghidra extent at
0x00773901:

    68d03f4b006a046a0c8d459450e8fd57ebffc3

It passes destructor 0x000B3FD0, count 4, stride 12 and local array EBP-0x6C
to the CRT vector-destructor iterator at 0x00629110. The full extent and both
relocations compare strictly, with no unresolved names. This is emitted by
the real C++ tower-position array. The older verdict lacking a parent is
superseded by this complete native graph and owning C++ body.

The same-file 241-byte createTower helper is strictly compared too and has no
EH graph. The 3-byte coordinate constructor, 1-byte destructor and entire
96-byte existing CRT archive member are independently compared. They add no
new coverage. Other graph siblings 0x007738EE (11 bytes), 0x007738F9 and
0x00773914 (8 bytes each) already have generated C++ rows; handler 0x0077391C
is also already rowed.

Normal owning-file build verifies all three original rows and three float
literals. Frozen-file inspection passes. The before/after identity audit
retains four existing divergent definitions: Coord3D copy constructor,
Object::getBodyModule, Object::getGeometryInfo and
ThingTemplate::getTemplateGeometryInfo. This row adds none. The old local
census has no entry, so no linking gain is claimed. place_bodies finds no
incidental ordinary bodies or pins. Source, headers, flags, pins, aliases and
existing private-class exceptions remain unchanged.

Run normal build.sh on BridgeObjectCtor.cpp, coord3d.cpp and
??_M@YGXPAXIHP6EX0@Z@Z before verify.py.
