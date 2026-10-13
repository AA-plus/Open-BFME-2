# MapMetaData copy-constructor list cleanups

The whole 163-line Code/GameEngine/Source/GameClient/MapMetaDataCopy.cpp was
read. Its normal build verifies all 33 existing rows; all four complete
exception-bearing parents and their native associative EH graphs are EXACT:
MapMetaData copy (0x003039E8, 257 bytes), destructor (0x0022DBC6, 156),
Coord3D list copy (0x002820DD, 88), and faction-set tree destructor
(0x000589BE, 56). verify.py checks all four whole bodies independently.

The copy constructor directly owns these Ghidra-bounded eleven-byte cleanups:

* 0x007797D2, current compiler label $L8907, saved this at EBP-0x10 plus
  0x48 (supplyPositions), bytes `8b4df083c148e98a6ea8ff`.
* 0x007797DD, current label $L8908, the same saved receiver plus 0x4C
  (techPositions), bytes `8b4df083c14ce97f6ea8ff`.

Both jump to the existing typed list<Coord3D> destructor at 0x00200667.
The entire emitted five-byte destructor is independently compared, with no
masked or unresolved bytes: `e929bd2e00`, a tail jump to the already verified
23-byte list-base destructor at 0x004EC395. No new pin or folded alias is
needed. Labels are discovered through the complete parent graph rather than
copied from the older sweep inventory ($L9009/$L9010).

The prior blocked 0x007797DD attempt only had unrelated same-shape donors and
no parent. This new whole-parent and EH-table evidence resolves that specific
blocker; no parent is inferred from adjacency or from generic cleanup bytes.

The retained reference revision is
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its complete MapMetaData_ctor.cpp,
MapMetaData_dtor.cpp and MapMetaData_assign.cpp were reviewed. Those donors
support member-copy/destruction semantics; target source and already verified
BFME2 constructor/copy chains establish the 256-byte target layout, coordinate
list identity and offsets. BFME1's differing trailing members and opaque views
are not imported. The target's unknown word at 0xF4 remains unknown.

These are natural emissions of the existing real C++ copy constructor. No
source/header/flags/pin/global/alias/marker change is made. Existing alternatename
and private-view debt is unchanged. Whole-file place_bodies reports zero extra
bodies and zero pins. Byte proof alone does not establish a new linking result.
Run the normal whole-file build before verify.py.

The normal commit hooks verify 35/35 rows and all four EH graphs. Their shadow
identity pass reports three definition discrepancies already emitted by this
unchanged source: _List_iterator_base::operator==, AsciiString's scalar deleting
destructor, and the faction-set tree's _M_erase. Neither new cleanup has a
binding discrepancy. No baseline or check is weakened to hide those findings.
The saved local linking index (6963cc017c, 2026-10-02) reports COMDAT/provider
conflicts and zero linked bytes for this file; this old census is not evidence
of a new regression or a current repository-wide linking result.
