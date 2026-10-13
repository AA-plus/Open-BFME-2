# SmudgeSet node-base destructor cleanup

Read the entire SmudgeListAddHead.cpp, including all list insertion/removal
operations, both node instantiations and the SmudgeSet destructor. Existing
provenance uses the BFME1 Smudge list model; target calls, vtables and the
four-byte node-base adjustment support the target instantiations. This row
adds no class identity or layout assertion beyond that existing evidence.

The whole 67-byte SmudgeSet destructor at 0x002D287D and its complete native
associative exception graph are EXACT. The graph binds $L661 to the Ghidra
20-byte unwind extent at 0x00777328:

    8b4df08b45f083c004f7d91bc923c8e918b5b5ff

It reads saved this at EBP-0x10, computes a nullable +4 node-base pointer
using NEG/SBB/AND, and tail-jumps to the actual DLNodeClass<SmudgeSet>
destructor at 0x002D2854. The sole REL32 starts at offset 16. The full 5-byte
destructor and its entire 117-byte Remove provider at 0x002D2700 are also
strictly compared from this same object, with no unresolved references.
Both providers have no EH data on either side. The cleanup is naturally
emitted by the real C++ base destruction, not hand-written asm or a naked lift.

The other native cleanup at 0x0077733C already has an 11-byte generated C++
row. The installed handler at 0x00777347 is also already rowed. All 16 original
source rows pass the normal build; frozen-file inspection and the before-row
identity audit pass. place_bodies finds no incidental ordinary bodies or pins.
The old local 6963cc017c census predicts LINKS (688 -> 698 bytes before this
new row), but no fresh measured linking gain is claimed.

Run normal build.sh on SmudgeListAddHead.cpp before verify.py. The replay
checks the full parent, complete graph, whole cleanup and every relocation,
plus both complete same-file provider bodies. No source, header, pin, alias,
marker or compiler setting is changed.
