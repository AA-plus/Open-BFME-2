# MMX transmission-order reduced IDCT draft

The new whole-function bank `reverse/attempts/0x001d3f30.cpp` implements
`MMX_idct10`, retail RVA `0x001D3F30`, 1,724 bytes through the RET at
`0x001D45EB`. Its inputs are 64 transmission-order coefficient and quantizer
words. This differs from the already banked `MMX_idct10_DX`: all 64 words are
multiplied and scattered before the reduced transform consumes the natural
4x4 square. The other 48 natural positions are read but ignored by the transform.

The implementation uses only the approved `001d3f30`, `001d35e0` and
`001c4300` specs, the complete 513-instruction retail body, and existing checked
MMX intrinsic helpers. No external decoder source was consulted. The native
zigzag table at VA `0x00BD8460` establishes the transmission permutation;
`permutation.json` records it and the quadrant-transposed internal layout.
The only external datum is the existing `Rva009B3A00Table` constant block.
Volatile reads reconstruct the six observed cache touches, without asserting
that the original pointer was volatile-qualified.

Reproduce with the normal diagnostic and then the read-only COFF/emulation
checker from the repository root:

```sh
python3 tools/explain_mismatch.py _MMX_idct10 --rva 0x001D3F30 --size 1724 --source reverse/attempts/0x001d3f30.cpp
python3 reverse/attempt_support/mmx-idct10-transmission-bank-20261012/verify.py
```

Five isolated normal compiler trials emitted 2,978, 2,672, 2,856, 2,878 and
2,856 bytes. The selected O2/G6 draft uses a single net shift per scattered
lane. Explicitly unrolling the dequant loop and using O1/G6 or O2/G7 did not
improve it. `trial-comparison.json` records sizes, object/source hashes and
raw byte sequence similarity. The selected similarity is 0.1956, and its
conservative bank score is 0.19; neither measures behavioral correctness.

The bank is **not byte-exact**. It differs from byte zero, has an aligned
compiler frame and MMX spills, and uses 89 absolute relocations to the existing
constant block. Retail preserves ECX and EDX in addition to cdecl's nonvolatile
registers; the draft fails that stronger contract in all 753 checked cases.
Retail's scatter shares shifted lanes across stores; the draft independently
masks each output lane, an unresolved source of its larger code.

`emulation.json` records 753 checked cases: 251 vectors at three disjoint-buffer
alignments (8, 2 and 4 bytes). The vectors cover explicit zero/DC/axis fixtures,
combined and saturation fixtures, deterministic random signed coefficients and
quantizers within the supported ten positions, the whole consumed 4x4 square,
and all 64 transmission positions. Each natural position is also tested alone.
Every complete output agrees with retail and an independent scalar oracle for
the spec's saturating/wrapping arithmetic. A native instruction hook confirms
the complete 64-word scatter before its first transform. Memory-read hooks
confirm all 128 bytes of both inputs are read. Checks also cover cdecl stack and
nonvolatile registers, unchanged input buffers, 16-byte canaries, unchanged
constant data, and absence of an EMMS instruction.

These checks do not establish destination-alias behavior, every intermediate
store of the draft, exhaustive behavior, MMX tag-state equivalence or decoder
integration. The draft buffers all dequantized products before scattering;
retail interleaves loads and working-buffer stores, so alias equivalence must
not be inferred. No `Code/` source, pin or matched ledger row was added. This
bank contributes no recovered bytes.
