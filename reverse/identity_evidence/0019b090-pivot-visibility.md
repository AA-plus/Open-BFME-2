# Pivot visibility accessor at 0x0019B090

The complete 23-byte native entry spans RVA 0x0019B090..0x0019B0A7.
It reads the stack index, computes index*0x58, loads the array pointer
from receiver +0x14 and returns its byte at record +0x50 in AL. The
terminal `ret 4` starts at 0x0019B0A4. Padding follows through
0x0019B0AF before the independently admitted scalar accessor at
0x0019B0B0. The preceding matched nine-byte accessor starts at
0x0019B080. No Ghidra entry or prior ledger row names this body.

The clean semantic guide is the complete HTreeClass::Get_Visibility inline
body in `game/Libraries/Source/WWVegas/WW3D2/htree.h` from Open-BFME-1
revision `9e3be919b10ae956e3c8a13995e0d62f2be1d016`. Release assertions
emit no code. Its array accessor is adapted to BFME 2's independently
matched PivotClass constructor and assignment: 0x58-byte record, byte
flag at +0x50 and float at +0x54. The target instructions themselves
establish this accessor's pointer offset and stride. /G7 reproduces all
23 bytes, and the scalar sibling remains exact after exposing the flag
in the local record view. No header, pin or global provider changes.

Visibility semantics are carried from the donor and supported by the
matched pivot record's flag, rather than established by a target name.
The original method and owning class identities remain unproven; both
accessors use the same address-derived view because their target access
layouts agree. This is bounded byte and structural evidence, not a
runtime or full-class identity claim.
