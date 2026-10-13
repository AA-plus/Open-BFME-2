# DataChunkOutput table cleanups

The entire owning source is
`Code/GameEngine/Source/Common/System/DataChunkOutputDestructor.cpp`.
Its constructor is the complete 142-byte body at 0x00306FA5 and its destructor
is the complete 249-byte body at 0x00307680. Both real C++ parents and both
complete native associative exception graphs independently verify EXACT.

The constructor graph places $L1450 at 0x00779B86, a complete 11-byte cleanup
`8b4df083c108e9cbd1b8ff`. It loads saved this from EBP-0x10, adds 8 for the
table member and tail-jumps to the existing 31-byte
DataChunkTableOfContents destructor at 0x00306D5C.

The destructor graph places $L1501 at 0x00779C35, a complete 11-byte cleanup
`8b4de483c108e91cd1b8ff`. Its saved this is at EBP-0x1C; the member adjustment
and native callee are the same. Ghidra independently supplies both complete
11-byte extents. `verify.py` checks all bytes and each REL32 relocation, with
ownership derived from the complete parent graph rather than nearby addresses.

An older attempt log incorrectly proposed MeshBuilderClass::Optimize_Mesh
for 0x00779B86 and refuted that identity. The real DataChunkOutput parent and
its verified native exception graph now provide the missing ownership proof;
the rejected mesh identity is not reused.

The source's recorded donor is Open-BFME-1
34f59164f6d1efd413c5fd37f4894ec834c3c0fe, with Zero Hour DataChunk.cpp as the
semantic guide. The current verified donor checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 and its Zero Hour source were inspected.
The output teardown and 256-byte copy loop are donor facts. The native parents,
WB BD8650 witness, stream at +0, FILE at +4, table at +8, wide path getter
0x002360FC, wide filename operations and added _wunlink are target evidence
already established by the source recovery. No source, global, pin or class
layout is changed for these two compiler-generated cleanups.

The normal whole-source build verifies all parent rows, four literals and six
named imports. Run it before replaying `verify.py`. The saved census
6963cc017c does not include this source, so `tools/link_check.py` cannot preview
its link placement. These cleanups add exact C++ emissions; no new linking
result is asserted and no linking runner was started.
