# MMX reduced IDCT intrinsic draft

The new whole-function bank at `reverse/attempts/0x001d4d50.cpp` implements
`MMX_idct10_DX`, native RVA `0x001D4D50`, 1034 bytes through its RET at
`0x001D5159`. It was written from the approved reduced and full transform specs,
the complete 313-instruction retail routine, and the existing
`FillIdctConstants.cpp` provider. No external decoder source was consulted.

The bank uses ordinary MMX intrinsics for the four dequantisation spans,
saturating butterfly, two quadrant transposes and two rounded column groups.
Its only external datum is the existing 96-byte `Rva009B3A00Table` global.
The six volatile cache-touch reads reconstruct observed retail accesses;
they do not establish an original volatile-qualified output pointer.

Reproduce from the repository root with the normal diagnostic, then the
read-only object/emulation checker:

```sh
python3 tools/explain_mismatch.py _MMX_idct10_DX --rva 0x001D4D50 --size 1034 --source reverse/attempts/0x001d4d50.cpp
python3 reverse/attempt_support/mmx-idct10-intrinsic-bank-20261012/verify.py
```

The selected O1/G6 draft emits **1444 bytes**, first difference at byte zero.
O2/G6 emitted 1510; an in-place rewrite emitted 1549; O2/G7 emitted 1512.
`trial-comparison.json` records those read-only object measurements. The selected
draft's raw sequence similarity is 0.1178; its conservative bank score is 0.1.
This score measures byte proximity, not the arithmetic checks below.

The checker compares all 64 output words against both retail execution and an
independent scalar arithmetic oracle in 246 cases: 82 supported-domain vectors
with disjoint output, output aliasing input, and output aliasing quantizer.
Cases include the spec's zero, signed DC, horizontal/vertical, combined and
saturation inputs, plus deterministic random signed coefficients and quantizers.
Unused input slots contain nonzero data while the six loaded but unsupported
coefficient slots remain zero. It checks the cdecl stack, nonvolatile registers,
unchanged non-output inputs, 16-byte canaries and the unchanged constant table.
Only DIR32 relocations to the existing table are permitted. It also refuses an
EMMS instruction in the compiled draft.

**The draft is not byte-exact or register-identical to retail.** Retail preserves
ECX and EDX in addition to the standard cdecl nonvolatile registers. The draft
does not preserve those two extra registers in any of the 246 checked cases.
It also has an aligned EBP frame, MMX spills, different instruction scheduling
and repeated absolute table references. These are unresolved recovery issues.
The case checks are not exhaustive or a claim about unsupported coefficient
inputs, every intermediate store, MMX tag state, or decoder integration.

No `Code/` source, matched ledger row or pin was added. The bank is evidence for
continued reconstruction and contributes no recovered bytes.

The independent O2/G6 draft in `root-o2-g6.cpp` is preserved alongside the
selected bank after an add/add rebase. It emits 1390 bytes versus retail 1034
and has an aligned 88-byte compiler frame. Its original six fixtures and
256 seeded output comparisons passed, but it remains nonexact and does not
reproduce retail ECX/EDX preservation. The measurements and emulation above
refer to the selected 1444-byte bank, not this alternate.

The same read-only checker also passes all 246 supported-domain, destination
alias, canary and cdecl checks for the alternate; `root-o2-g6-emulation.json`
records its source and object hashes. It preserves ECX/EDX in zero of those
cases. Reproduce with `explain_mismatch.py` using `--source` set to the alternate,
then pass that source path and an output JSON path to `verify.py`.
