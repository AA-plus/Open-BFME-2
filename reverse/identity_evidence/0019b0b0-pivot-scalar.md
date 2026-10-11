# Pivot scalar accessor at 0x0019B0B0

The complete 23-byte native body starts at aligned VA 0x0059B0B0 and ends
with `ret 4` at 0x0059B0C4. The preceding accessor ends with `ret 4` at
0x0059B0A4, followed by padding through 0x0059B0AF. Padding follows this
body through 0x0059B0CF; the next entry is the already matched
Animatable3DObjClass::Set_Hierarchy_Valid at RVA 0x0019B0D0.
There is no Ghidra entry or pre-existing ledger row at 0x0019B0B0.

Target instructions read the index from the sole stack argument, compute
11 times that index, load an array pointer from receiver +0x14, and return
the float at array + index*0x58 +0x54 through x87. ECX is the receiver and
the return pops four bytes. This establishes the accessor's ABI and layout.
The matched PivotClass constructor at 0x00197830 and assignment at
0x00197950 independently establish a 0x58-byte record with a float at +0x54.

The semantic and structural guide is the complete clean BFME 1 donor
`game/Libraries/Source/WWVegas/WW3D2/Rva009793C0PivotFade.cpp` at revision
`9e3be919b10ae956e3c8a13995e0d62f2be1d016`. Its original BFME 1 layout does
not place in BFME 2. Replacing that donor layout with the independently
proved BFME 2 record layout gives the unique complete 23-byte placement
under /G7. No shared header, callee pin or global datum is introduced.

The donor calls its member PivotFade. The target getter itself establishes
only a scalar read; its original method name, owning class identity and fade
meaning remain unproven. The source therefore uses address-derived views.
The constant receiver offset and record stride are target facts, while the
association with the HTree/Pivot family is a structural inference supported
by the matched record layout. Byte verification is not runtime evidence.
