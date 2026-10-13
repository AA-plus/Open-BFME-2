# GameSpy configuration list construction cleanups

The complete 526-line Code/GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp
was read. Its six existing rows verify, including all 49 literals, 16 empty
string references and two imports. Both complete exception-bearing parents
and their native associative EH graphs are EXACT: GameSpyConfig construction
at 0x0054E8DC (2795 bytes), and the interface factory at 0x0054F4AF (89 bytes).
verify.py independently compares both entire parents and both full graphs.

The constructor directly owns two Ghidra-bounded eleven-byte cleanups. Each
loads saved this from EBP-0x60 and tail-jumps to the typed list<AsciiString>
destructor at 0x00207F08:

* 0x007985D0, $L41456, adds 4 for m_pingServers;
  complete bytes `8b4da083c104e92df9a6ff`.
* 0x007985F1, $L41459, adds 0x48 for m_qmMaps;
  complete bytes `8b4da083c148e90cf9a6ff`.

The same unit's entire emitted five-byte list destructor is independently
exact, with no masked or unresolved bytes: `e9af6d0f00`, forwarding to the
already owned list-base destructor at 0x002FECBC. Ownership is derived from
native EH data, not from adjacency or a generic cleanup shape.

The source retains its original 6d9434269164392c5ba62aaa7c15a86b5b020d76
transfer provenance and the constructor's documented BFME1 donor874e38488.
The currently retained donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 was
reviewed for the complete GameSpyConfig class/member declarations. The donor
supports the list semantics and relative member order; BFME2's complete
constructor, factory and native graph independently establish target layout,
frame slots and cleanup callees. The target's omitted rank table and separate
VIP allocator evidence are preserved, not inferred from the donor.

Before adding either row, the identity checker reported thirteen shadow
findings in this unchanged source. identity-before.json records the exact
four bindings and nine emitted definitions. They concern AsciiString/list-base,
the signed VIP set allocator view, and short-vector helpers. No check or
baseline is weakened and no finding is declared a false reject.
The saved census at 6963cc017c does not contain this source, so link_check
cannot preview it. No linking improvement is claimed.

No source/header/flag/global/pin/alias/marker change is made. The new rows
account for natural cleanups emitted by existing real C++ parents.
place_bodies reports zero further bodies or pins. Run the normal whole-file
build before verify.py.
