# Narrow string cleanup: three alias hatches removed

At BFME 2 base `b59e5c939e326f2e19c3ba643c1b56a70e2f340a`, replace the
narrow destructor forwarding declaration and `/alternatename` in the three
units in `consumers.txt` with a forced-inline specialization calling the existing
`releaseBuffer` worker. Keep the local class layouts and wide teardown unchanged.
Remove exactly their three narrow-destructor keys from `reverse/hatch_baseline.tsv`.
No new function rows, pins, compiler flags or authored retail bytes.

## Target evidence and acceptance

`object-proof.json` records the unchanged COMDAT symbol sets, raw bytes and
extents, object hashes, and the only COMDAT relocation changes: narrow teardown
now names `?releaseBuffer@?$StringBase@D@@AAEXXZ` directly. Independent decoding
of all four changed call operands in matched retail parents proves their target
is RVA `0x00036410`. Wrapper COMDATs retain the same five-byte forwarding shape.
The unchanged worker is supplied by `StringBaseWideReleaseBuffer.cpp`.

`./build.sh` passes all 8/8 rows in the changed units, all eight literals and two
empty-string references, and the named import with no baseline or skip.
Bounded `link_check.py --prepare-current` verifies 39/39 rows across the seven
trial consumers plus the unchanged provider and makes strict reusable receipts.
`prepare-first-before.txt` covers the first consumer's original and provider;
`prepare-before.txt` covers the other six original consumers (the first had
already been edited). `prepare-after.txt` covers the final, reverted cohort.
`eh-after.txt` independently passes 13/13 parent exception tables/funclets;
`eh-before.txt` also passes 13/13. Freeze checks accept all three changed sources.

The local link acceptance uses the index measured at `cb660e4d97`,
2026-10-13 04:02; its hash and the checkout base are in `object-proof.json`.
Discovery also used the committed repair queue/status measured at `67e1365aa9`.
Refresh all eight objects together in an in-memory copy of the same index for
both sides, substituting saved original consumer objects and the **same current
provider object** before the edit. Do not write the index or link status.
`link-before.txt` and `link-after.txt` show identical findings: the three changed
consumers already link locally with the current provider, covering 971 bytes
before and after. The verified gain is **three removed alias hatches**, zero
additional legacy-linked bytes and zero authored C++ bytes. The CLI's reported
940 -> 2,276 aggregate compares against stale census objects and is not a gain
attributable to this change. `link-cli.txt` exits 1 because the unchanged provider
has a duplicate `??1?$StringBase@D@@QAE@XZ` in both comparisons.

Strict receipts certify byte-verified object inputs, not executable placements.
No self-strict or closed-strict placement gain is claimed. No full link cycle,
nightly, boot run or census rebuild was performed.

## Donor lead and limitations

Reviewed BFME 1 revision `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`, including
`5fa9bfd662c427a198176b0b727c4c11d0965733` (Anim2D lookup cleanup binding to
canonical string release). Its cleanup-worker binding is the applicable lead;
this is a local BFME 2 adaptation proven by target calls, not an import of the
donor's class layout or ABI. Existing BFME 2 allocator methods use the same
inline emission control. No reference or shared header was changed.

Four other trial consumers (BannerCarrierUpdateModuleDataDtor,
ShellMenuSchemeDtor, Rva003FAFB9Dtor and Rva0020D583Dtor) passed main-body byte
verification but failed five exception-data checks: the specialization produced
incorrect imported-destructor calls in unwind code. Their originals pass all
EH checks. Revert those four completely and record blocked attempts through
`re_log.py`; see `eh-trial.json` for exact rows, sections and retail boundaries.
This is a true regression, not a claimed verifier false reject. A future attempt
needs an emission strategy preserving unwind code. Do not repeat this strategy.

Provider duplicate-definition closure remains outstanding. BFME 1 upstream
fetch found `b39065ac7f5e64207af26ad6be463c64b670ce04` beyond the clean verified
pointer. The previously documented comparative full-gate/cache blocker remains;
no pointer or successful-freshness timestamp was advanced in this repair.
Unrelated untracked dump preparations and sweep data were preserved.
