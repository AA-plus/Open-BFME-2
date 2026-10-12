# Complete weak deringing bank

Approved specs 001c22c0.md and 001c1ad0.md plus all native instructions in
1C22C0..1C28B6 guided this work. No external decoder source was consulted.
The old complete bank, including all vertical/horizontal weights and output,
was read. The bank reuses the existing Vp6FilterEdgeTagTable data owner.

The selected change walks horizontal source and short-weight rows through
pointers and uses a signed column index. Vertical/output traversal is retained.
The exact frame0x160 survives; compiled1485B differs from native1526B at+15.
No production row, pin, new datum or escape hatch was added.

Six whole-function shapes each passed288 deterministic executions against
retail and an independent integer specification oracle. These cover11 Q indices,
8 signed pitch values, flat/checkerboard/random inputs, randomized scale entries,
and separate/source-alias/right-shift/next-row destination layouts. The entire
mapped frame, cdecl stack, nonvolatile registers, argument slots and both tables
are compared. The oracle precomputes weights from original source, then reads
current source for each immediate output store, preserving overlap semantics.
These tests are finite behavioral evidence, not exhaustive or byte-exact proof.

| Shape | Compiled bytes | Ordered byte score |
| --- | ---: | ---: |
| Old current bank |1485|901/1526=.590433|
| Vertical pointers |1533|930/1533=.606654|
| Horizontal pointers (selected) |1485|1106/1526=.724771|
| Both weight pointers |1517|929/1526=.608781|
| Output pointers, two load orders |1504|443/1526=.290301|

Score is SequenceMatcher ordered byte alignment with autojunk disabled, after
resolving only the one existing sharpen-table absolute relocation. It is not
coverage or a probability. Further work needs the native vertical pointer and
output allocation/scheduling shape. No extra speculative flags were swept.

Reproduce with the supported compile before running the evidence checker:

    python3 tools/explain_mismatch.py _DeringBlockWeak_C --rva 0x001C22C0 --size 1526 --source reverse/attempts/0x001c22c0.cpp
    python3 reverse/attempt_support/0x001c22c0/verify_differential.py

The checker requires the repository's Unicorn dependency, and writes an ignored
build/dering-weak-verification.json receipt. Expect288 cases,1485/1526B,nonexact.
