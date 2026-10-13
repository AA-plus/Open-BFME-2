# Address-named owner string-array destruction cleanup

Read the entire Rva0030C1FCOwnerDtor.cpp. The source explicitly uses an
address-named owner, preserving uncertainty about its original identity.
Target destructor stores establish its vtables/virtual-base relationship;
listener calls, buffer teardown and four strings at+0x40 establish the
structural interpretation. No new donor type identity is asserted.

The whole156B destructor0x0030C40A and its complete native associative EH
graph are EXACT. That graph binds Ghidra's22B cleanup0x0077A0BF to$L1285:

`6839ba88006a046a048b45f083c04050e83cf0eaffc3`

The cleanup pushes the real AsciiString destructor0x0048BA39,count4,stride4,
and saved-thisEBP-0x10 plus0x40, then calls the CRT vector iterator0x00629110.
Parent/frame ownership comes from the native graph, not adjacency; the
existing real C++ string member array naturally emits the cleanup.

verify.py independently checks whole parent/graph, cleanup extent and both
relocations, full5B AsciiString destructor, full133B narrow releaseBuffer
and existing folded StringBase destructor spelling (both with exact native
EH graphs), and the full96B prebuilt CRT iterator. The prebuilt body earns
no new C++ coverage. Complete ascii_string.cpp and StringBaseWideReleaseBuffer.cpp
were read and normal builds passed all15 and7 rows respectively. Run those
normal builds, the owning source and ??_M@YGXPAXIHP6EX0@Z@Z before replay.

The owning file's four original rows pass normal byte verification and
frozen-file inspection. The complete native graph's other8B,20B and11B
cleanups already have C++ rows. place_bodies finds no additional body or pin.
The old6963cc017c census has no entry for this source; no clean linking claim.

identity-before.json records three existing findings: the primary-base
destructor at0x00538133 is pinned but unowned in two existing callers, and
the owner's scalar-deleting destructor differs across existing definitions.
identity-after.json must preserve precisely these findings; the cleanup
itself uses the independently verified real string destructor and CRT iterator.
No source/header/flag/global/pin/alias/marker or identity-baseline changes.
