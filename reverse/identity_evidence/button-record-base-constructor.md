# Button constructor and copied record

RVA `0x005E93FF` is the complete 140-byte constructor ending with `ret 8`
at `0x005E9488`. Its paired destructor at `0x005E92F7` already owns the
derived primary/secondary vtables at VA `0x00C78030/0x00C78010`. The factory
at `0x005CEB03` allocates 40 bytes and forwards its argument and a three-word
context at receiver `+8`. These target facts support reconciling the former
constructor-only `Rva005E93FF` view with the existing `Rva005E92F7` owner.
The original application class and the first argument's meaning remain unknown.

The prior bank (attempt 37222) treated the holder as four bytes and assigned a
record member in the constructor body. Moving that member into an initializer
still left the copy after the derived vtable stores. The independently matched
holder constructor `0x005E1680` and destructor `0x005E12D1` instead establish
a 20-byte prefix through its `+0x10` field. With the eight-byte primary prefix,
this puts a copied 12-byte record at object `+0x1C` without artificial padding.
Modeling that record as a nonvirtual third base reproduces retail's three
MOVSD copies before the final derived vtable stores, and the later reuse of
ESI for the holder at `+8`. The record base is a structural/code-generation
inference; it does not recover an original base-class name. All accessed
offsets and the 40-byte allocation extent are independently visible in retail.

The constructor pin is renamed at its existing address, and its sole source
consumer is updated coherently. No second constructor name is placed there.
The `Rva005E936AGet(const void*)` pin names the previously unowned image lookup:
its complete 149-byte retail body reads an AsciiString at argument `+0x14`,
calls the rowed `ImageCollection::findImageByName`, and uses `BuildingNoArt`
as a fallback. Its caller pushes a pointer from the record's third word and
cleans the stack with POP ECX. The callable name is address-derived, and its
original application identity remains unknown. The helper body remains banked;
its callable pin does not count as C++ coverage.

The primary base vtable uses the existing `Rva005F5C77Base0` data identity.
The two derived vtable relocations retain the already owned destructor's
identities. Both the constructor and destructor must verify together, as
must the renamed factory consumer, literal references, EH cleanup and data
bindings. The normal pin-admission tool also removed five obsolete pin-count
keys and five stale grant tokens while admitting the helper; no gate code or
gate-baseline allowance is changed. Linking and gameplay parity remain open.

The code-identity shadow still reports four existing unowned factory
constructors (`0x005E8DCF`, `0x005E91ED`, `0x005FB30A`, `0x005FB4DF`), the
newly named but unconverted image helper, and differing complete/scalar
deleting destructor copies for `Rva005F5C77Base0`. The hierarchy needed by
this target destructor is not yet reconciled across that base's other units.
These are open ownership/linking issues, not additional recovered bodies.
