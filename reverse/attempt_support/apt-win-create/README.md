# AptPlayer window creation

WB `0x00B93760` names `AptPlayer::WinCreate` in `AptPlayer.cpp` (assertion
lines 1022..1030). The complete retail body is `0x00223263..0x002233A6`,
323 bytes, ending in `RET 8`. BFME1 `9cbfb551fe20`'s clean
`Rva0046A870CreateMainWindow.cpp` supplies the semantic guide; retail proves
the target-specific descriptor, fields, call order, and cleanup.

The old bank's four stack-slot differences came from pointer lifetime.
Retail retains the incoming name in EDI only after constructing the 52-byte
`GadgetCreateView`, then reuses the dead incoming pointer word at EBP+8 for
the found-window output. Ordinary placement construction starts the new
pointer lifetime in that word after retaining the name. This reproduces all
323 bytes without assembly, a pragma, or a changed signature. The existing
pointer ABI view is retained; it does not establish whether the original
source used a pointer or reference formal.

The callback now references the owned 55-byte factory at `0x002223FE` with
its actual compiled signature. Its 169-byte constructor is the upstream
provider at `0x0040FDD1`. The registry declaration uses the sole owned
`TheRva00DFF024Registry` datum, casting its receiver for the named lexicon
call rather than introducing a second global. The pointer-list operation
reuses the existing ObjectSellInfo-pointer provider only as a four-byte
pointer representation; no application payload identity is asserted.

Adding the same `bfmealloc` include shim as that matched list provider removes
four divergent allocator COMDAT copies and preserves every current body.
The ordinary gate passes 26/26 rows, 9 literals plus one empty-string
reference, and both named imports. All 11 EH rows are exact. Scoped code
identity reports zero new findings, and the data check reports zero findings.
The unit rescan finds no additional bodies or pins.

The local link index remains from `7bcd61f5c1`. Its final preview still names
the newer factory and the now-owned `Rva006CC600` provider as unresolved,
and an old duplicate AddExternHandler copy as selected. Current sources have
one AddExternHandler definition, and the final identity check sees no
duplicate. The latest committed census reports the prior AptPlayer home
linking. The old preview is retained as a limitation, not presented as a
fresh link result; no census or verifier was changed.
