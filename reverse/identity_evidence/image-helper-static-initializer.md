# Image lookup static initialization

The complete native body at `0x005E936A..0x005E93FF` is 149 bytes. The caller
at `0x005E946A` pushes the copied record's image pointer and cleans its one
stack argument. The helper reads an `AsciiString` at input offset `0x14`,
looks it up through the already owned `ImageCollection::findImageByName`,
and falls back to the cached `BuildingNoArt` image. The address-derived
name does not establish the original application identity or input class.

The older bank manually tested and set the initialization flag. Its temporary
string did not reproduce retail's two exception states. A normal local static
pointer initialized by `findImageByName(AsciiString("BuildingNoArt"))` emits
all 149 native bytes with `/O1 /G7 /EHsc /MD`, including the guard rollback
state before temporary construction. The isolated trial uses the existing
`TheMappedImageCollection` global, not the bank's extra address-named global.

`eh_verify.verify_row` returns `EXACT` for the trial's entire associated EH
graph. `verified_funclet_locations` places the guard rollback at
`0x007A40C3` and the temporary destructor at `0x007A40D0` from the parent's
relocations and retail unwind table, not from adjacent addresses or a masked
placement. The guard's complete 13 bytes are
`a1 74 67 e0 00 24 fe a3 74 67 e0 00 c3`.

The former `Rva007A40C3ClearFlag` row was a synthetic free-function view of
this compiler cleanup. Its independent `g_Va00E06774` definition would create
separate storage alongside the parent's compiler-owned local-static guard.
Retract that row, definition and global in their own commit before landing the
parent; the parent gate then verifies this cleanup as part of its EH graph.
The 13 retired bytes must be deducted from C++ coverage, not counted twice.

The local static owns its cached pointer at data RVA `0x00A06770` (three parent
DIR32 references) and guard at `0x00A06774` (two). These are four-byte
zero-initialized COMDAT objects. The preceding ledger entry at `0x00A0675C`
has an inferred gap extent of 24 bytes; admitting the pointer splits that gap
at 20 bytes, consistent with the existing constructor's eight-byte base and
three four-byte member words. This is evidence for the boundary, not an
original type or name recovery.

The real parent is recovered in `Rva005E92F7Dtor.cpp`, beside its constructor
consumer and existing destructor. All three bodies and their complete EH
sections verify together. The data ledger binds each local-static object to
this unit alone, and the temporary helper pin is removed now that the normal
matched row supplies its address. No additional alias or global is introduced.

Scratch evidence is in `build/resume-20261011-image-helper-static.log` and
`build/resume-20261011-image-helper-eh.log`. Linking and gameplay remain open.
