# LAN reset global binding

`LANGameInfoSlots.cpp` retains its three retail bodies: `getLocalSlotNum`
at `0x00447794` (51 bytes), `resetAccepted` at `0x004477E0` (47 bytes),
and `amIHost` at `0x004477C7` (20 bytes).

The reset body formerly declared `g_Va009FE958` with the private
`Global009FE958` pointer type and used it through a `TheLAN` macro. The data
ledger instead prefers `?TheLAN@@3PAVLANAPI@@A` at RVA `0x009FE958`;
`Common/Rva00446A77Enable.cpp` already defines that global. The repaired
declaration uses that existing `LANAPI *TheLAN` and casts its value to the
existing virtual-slot view for the timer call.

The nullable receiver, virtual slot 31, eight-slot loop, and slot layouts are
unchanged. The canonical global spelling is a ledger/provider fact; the view
only describes the target accesses required here. This does not establish the
complete `LANAPI` layout or inherit Zero Hour's omitted host-button update.

The normal source gate verifies all three bodies. Data checks report no new
binding finding. The two actual address-global occurrences become zero, so
only the corresponding `g_Va009FE958` hatch-baseline key is removed. No pin,
alias, source marker, or additional global is introduced. Link and gameplay
parity are not claimed; this repair adds no C++ coverage bytes.

The code-identity shadow check still reports the existing call from `amIHost`
to the unconverted `LANGameSlot::isLocalPlayer` at `0x0044770F`. Canonicalizing
the global does not recover that helper or establish a linked implementation.
