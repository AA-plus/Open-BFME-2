# Single-state button constructor

Retail `0x005E91ED..0x005E9279` is a complete 140-byte constructor returning
with `RET 8`. Its initial primary table is `0x00C7A630`, followed by derived
tables `0x00C77FF0` and `0x00C77FD0`. Those derived tables and the adjacent
independently rowed destructor at `0x005E91A9` establish the same address-derived
owner. Rename the old constructor-only `Rva005E91ED` view to `Rva005E91A9`,
including the real factory at `0x005CEA92`; do not add a second constructor name.

The factory allocates 32 bytes and supplies one opaque word and its context
at receiver offset eight. The constructor initializes the eight-byte primary
prefix and passes the first context word to the independently rowed holder
constructor at `0x005E1680`, using a temporary `AsciiString("button")`. The
holder begins at offset eight and occupies 20 bytes, as independently shown
by its constructor and destructor accesses through holder offset `0x10`.
The remaining four-byte field at object offset `0x1C` receives context word
four after the final derived vtable stores.

The retail image lookup uses global `0x00E0675C` and rowed 33-byte member
`Rva005E16B9::rva005E16B9`, then calls rowed image setter `0x005E1158` on the
holder at object offset eight. The source declares the data ledger's existing
`g_rva00E0675C` with its existing opaque `Rva005E16DA` type and casts at the
member call. It creates no second global at that address.

The original 2026-10-02 refusal predates the verified typed holder constructor.
With that declaration and measured prefix sizes, ordinary C++ emits the whole
140-byte constructor and preserves the existing whole 60-byte destructor.
The 216-byte unnamed WorldBuilder alignment is only a structural lead: its
three-word copy and different image helper do not establish target behavior.
Native bytes determine the one target state word and global image lookup.

`Rva005F5C77Base0` supplies the existing primary table identity; its inferred
inheritance models the observed prefix and destructor restoration. Original
application identities and the shared base's class contract remain unresolved.
As documented for the copied-record sibling, this private view emits divergent
base destructor copies relative to other units. Exact constructor/destructor
bytes and zero data findings do not prove link closure or gameplay parity.
