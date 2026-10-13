# Radar viewbox corner-array cleanup

Read the entire W3DRadarDrawViewBox.cpp and W3DRadarCornerLifetimes.cpp.
Existing source preserves ZH drawViewBox as a semantic guide and the BFME1
start/end storage shape as a compiler lead. Target evidence establishes the
490-byte drawViewBox body, float projection helper, four corner elements,
callbacks and the RadarWindowOverrideSource handoff. No new class identity is
inferred from this cleanup, and the existing lifetime adapter names remain.

The entire 490-byte parent at 0x0004DBD5 and complete native associative EH
graph are EXACT. Current compiler label $L584 maps through that graph to the
19-byte Ghidra unwind extent at 0x0075D418. The older candidate cache's $L572
is stale after dependency changes; the row uses the current graph-proven label.

    68d03f4b006a046a088d45a850e8e6bcecffc3

The cleanup supplies destructor 0x000B3FD0, count 4, stride 8 and local array
at EBP-0x58 to the 96-byte CRT vector-destructor iterator at 0x00629110.
Every byte and both relocations match strictly, with no unresolved references.
The real C++ four-element array emits it naturally. The installed 10-byte
handler at 0x0075D42B is already rowed; there are no other cleanup siblings.

Normal owning-file build verifies all three original rows and three float
literals. The lifetime-provider source passes all four existing alias rows.
The replay separately compares the actual 3-byte BfmeRadarMapPoint constructor
and 1-byte destructor and the complete 96-byte existing CRT archive member.
These pre-existing providers and aliases earn no new recovery bytes.

Frozen-file inspection and before-row identity audit pass. place_bodies finds
no other ordinary bodies or pins. The old local census 6963cc017c has no entry
for this file, so no linking gain is claimed. No source, header, alias, pin,
marker or compiler setting changes are needed.

Before verify.py, run normal build.sh for W3DRadarDrawViewBox.cpp,
W3DRadarCornerLifetimes.cpp and ??_M@YGXPAXIHP6EX0@Z@Z.
