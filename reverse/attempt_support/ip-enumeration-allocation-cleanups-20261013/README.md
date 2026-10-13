# IP enumeration allocation-failure cleanups

Read the entire IPEnumerationGetAddresses.cpp, EnumeratedIPCtor.cpp and
mem_ops.cpp. The existing donor provenance is BFME1 revision
10af19f44a89ab7ecc23195bb9a842ceafbc02c9. Target allocation size12 and member
accesses establish the BFME2 node layout without the donor MemoryPoolObject
base. Winsock calls, address formatting, sorting and the fallback IP distinguish
the existing named parent; donor structure is not treated as proof of layout.

The complete463B getAddresses body0x0050C02E and native associative exception
graph are EXACT. That graph owns two independent Ghidra10B cleanup extents:

- 0x007944E1 ($L1324): ff75f0e877b889ff59c3; frees [EBP-0x10].
- 0x007944EB ($L1326): ff75e4e86db889ff59c3; frees [EBP-0x1C].

Both push the allocation pointer, call the actual scalar operator delete at
0x0002FD60, pop the argument and return. The saved allocations belong to the
two new EnumeratedIP expressions; ownership and frame slots are established
by the complete native exception graph, not adjacency or byte shape alone.
Both are naturally emitted by the real C++ allocation expressions. Bank each
verified cleanup as its own commit. The third8B graph cleanup at7944F5 is
already backed by generated C++.

verify.py checks the whole parent/graph, full cleanup extents and every
relocation, plus the entire21B operator delete and57B EnumeratedIP constructor
with its own exact native EH graph. Delete has no EH data on either side.
Normal builds pass the two original owning rows (two literals/five named
imports), allfour mem_ops rows and both node-constructor rows (one empty
string). Run those three sources through normal build.sh before replay.

Frozen-file inspection passes and the before-row identity audit has no
findings. place_bodies returns zero additional bodies/pins. The old local
6963cc017c census lacks the owning source, so no new linking gain is claimed.
No source/header/flag/global/pin/alias/marker changes accompany these rows.
