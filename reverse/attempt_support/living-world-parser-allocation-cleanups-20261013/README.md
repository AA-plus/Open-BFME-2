# LivingWorld parser allocation-failure cleanups

Read the entire Rva002E2386Parse.cpp, including both parsers, their table
records, declarations and layout views. Existing target evidence identifies
LivingWorldPlayerTemplate and LivingWorldAITemplate registrations, their
field tables and allocation sizes. The same-file player parser is a compiler
shape lead for the AI parser, not independent donor identity evidence. Keep
the existing address-derived constructor and parser identities.

Both whole 231-byte parents, at 0x002E2386 and 0x00420A29, and their complete
native associative exception graphs are EXACT. Each graph owns one unrowed
allocation cleanup whose 10-byte extent also agrees with Ghidra:

- 0x00778836 ($L5152): ff75ece822758bff59c3, player parser.
- 0x00786EEC ($L5204): ff75ece86c8e8aff59c3, AI parser.

Both push the saved allocation at [EBP-0x14], call scalar operator delete
0x0002FD60, remove the argument and return. These are naturally emitted by
the real C++ new expressions. Ownership and frame slots come from each
complete graph, not adjacency. The other 8-byte graph siblings at 0x0077882E
and 0x00786EE4 already have generated C++ rows. Existing 10-byte handlers are
already assigned to this owning source.

Run normal build.sh on this source and WWLib/mem_ops.cpp before verify.py.
The replay independently compares each complete parent, both graphs, every
cleanup byte and relocation, and the entire 21-byte scalar delete provider.
No source, header, flag, pin, alias or marker is changed by these two rows.
Each verified body is banked separately.

All four original source rows and all four mem_ops rows pass normal byte
verification. Frozen-file inspection passes; the before-row identity audit
has zero findings. place_bodies found no incidental bodies or pins. The file
is absent from old local census 6963cc017c, so linking is not previewable and
no linking gain is claimed.
