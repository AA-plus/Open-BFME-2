# Module-tag two-handle array cleanup

Read the entire ModuleTagStringSwap.cpp and both destructor provider files.
The existing swap identity comes from target container accesses, the related
inline-container swap, and the sole caller's clear-by-swap operation. Count,
capacity, data and two inline handle slots are target-supported structural
facts; address-derived element/handle names preserve original-type uncertainty.

The whole 306-byte swap at 0x006D0F50 and native associative exception graph
are EXACT. That graph binds $L442 to the 19-byte Ghidra extent at 0x007A8520:

    68f39d4a006a026a048d45ec50e8de0be8ffc3

The cleanup uses the destructor at 0x000A9DF3, count 2, stride 4 and local
array EBP-0x14, calling the CRT vector-destructor iterator at 0x00629110.
Every byte and both relocations compare strictly, without unresolved names.
The real C++ two-element temporary emits this cleanup naturally.

The entire 5-byte element destructor and its 30-byte BfmeRefVGO destructor
provider at 0x000A9822 also compare strictly. Their normal builds pass 1/1 and
2/2 rows; both providers have no EH graph. The existing 96-byte CRT archive
member is independently compared. These existing bodies earn no new bytes.

The file's before-row identity audit reports TWO pre-existing findings: the
Rva004A9DF3Element constructor binding at 0x00013260 and divergent deleting
destructor Rva006D0280. Before/after snapshots preserve the same findings;
this cleanup adds none. No source, header, pin, alias, marker, layout or flag
is changed. Do not describe this file as identity-clean or newly linkable.
The old local census 6963cc017c has no entry for it.

Whole-file sibling review also finds native 8-byte cleanup 0x007A8533 ($L443),
which jumps to 0x000A9DF3. Strict verification leaves its local
Rva006D0F50Handle destructor unresolved. The current object emits that name
as a 36-byte inline release body referencing Rva006D0280 destruction, the
chain allocator and freeBlock; it is not the target's 5-byte wrapper. This
sibling is blocked pending real type/destructor reconciliation. No pin or
alias is added to mask it. Graph EXACT masks relocation slots and alone does
not establish the sibling's binding. The installed handler 0x007A853B already
has its own row.

Frozen-file inspection passes, both original rows pass normal verification,
and place_bodies finds no further ordinary bodies or pins. Run normal build.sh
on this source, both destructor provider sources, and ??_M@YGXPAXIHP6EX0@Z@Z
before verify.py. The replay checks the full parent/graph, selected complete
cleanup and relocations, both complete C++ destructor providers and CRT body.
