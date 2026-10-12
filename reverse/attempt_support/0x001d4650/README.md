# Full MMX IDCT clean-room attempt

Target MMX_idct_DX: 0x001D4650..0x001D4D41, 1777 bytes, cdecl three pointers.
Only the full approved spec reverse/vp6_cleanroom/specs/001d4650.md, all 533
retail instructions, and existing repository clean-room code were read. No
external decoder source was consulted. The body is evidence, not recovery.

The complete C++ intrinsic draft multiplies all 64 coefficients, uses native
quadrant-transposed storage, transforms four parallel rows and columns with the
spec's wrapping and saturating value tree, rounds before the difference-first
sum, and leaves MMX state active. Existing Rva009B3A00Table provides all constants;
no new datum, pin or class identity was introduced. Six volatile cache-touch
reads are a reconstruction choice, not a statement of original source types.

O2/G6 emits 2547 bytes and differs at byte zero. O1/G6 emits 2661 bytes; a
separate in-place working-buffer variant emits 2713. The initial by-value fourth
MMX transpose parameter failed MSVC alignment requirements and was changed to
const references. None of these trials is an exact match. The banked O2 body
recompiles to the identical symbol bytes and relocations that were emulated.

252 differential cases compare all 64 output words with retail and an
independent integer spec oracle: nine directed vectors (including the two
full-domain vectors in the spec), 75 deterministic full-domain random vectors
at three amplitudes with arbitrary quantisers, each under three destination
layouts (separate, input alias, quantiser alias). Cdecl stack, nonvolatile
registers, canaries, other input contents and the constant block are checked.
No EMMS instruction is emitted. These checks establish observed arithmetic and
memory behavior, not exhaustive behavior or byte identity. Retail preserves
incoming volatile ECX and EDX in all cases; the draft preserves both in zero
cases. That stronger retail contract remains unresolved.

The conservative byte score is 286 ordered matching bytes / max(1777,2547),
0.1122889674, after resolving only the existing constant-table ABS relocations.
It measures byte alignment, not recovered coverage or probability of correctness.

Reproduce from the repository root with the normal mismatch tool, then:

    python3 tools/explain_mismatch.py _MMX_idct_DX --rva 0x001D4650 --size 1777 --source reverse/attempts/0x001d4650.cpp
    python3 reverse/attempt_support/0x001d4650/verify_intrinsics.py

The second command requires the repo's Capstone and Unicorn dependencies. The
expected result is PASS 252 with 2547/1777 bytes, nonexact. Further work must
resolve register/frame scheduling and the extra saved-register contract; do not
install this bank as a matched production row.

During this work master independently landed the target as MASM in MmxIDct.asm.
That row does not make this intrinsic draft byte exact or confer C++ coverage.
The draft is retained as evidence for a future C++ conversion.
