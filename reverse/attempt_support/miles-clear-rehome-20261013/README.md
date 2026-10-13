# Miles holder-clear ownership repair, 2026-10-13

Session base: `523bac6cb5`. The local census index was measured at
`d753dedd98` (2026-10-12 22:16 UTC). The committed link-status snapshot at
`f6c432fac6` supplied queue leads only. No per-row data-back artifact was used.

## Verified repair

Move the existing 19-byte `Rva000A8C9B::clear` row at `0x000A8C9B` from
`Rva000A8C9BClear.cpp` to MilesAudioManager.cpp and delete the split source.
The home already emits an exact retail COMDAT, used at five call sites. Its
body and compiler flags are unchanged. The split source emits an exclusive
definition, which conflicts with the home COMDAT. Removing that provider
eliminates one duplicate-definition cause without adding authored C++ bytes.

`object-proof.txt` records the exact relocated native body, the current
strict home receipt, the historical provider inventory, the sole remaining
ledger owner and the absence of the deleted source. Retail establishes the
pointer-at-zero null test, Release_Ref call and zero store. The existing
address-derived class name remains an inference; this repair adds no name,
layout claim, pin, alias, global or escape hatch.

## Donor review

Reviewed BFME 1 repair `63955ed0f3d52748d67c899cfa5e60d72848300e`, which
re-homes FVF helper rows in their existing retail callers and removes competing
definitions. That ownership principle applies; its concrete code and ABI do
not apply to this holder. No donor body was imported. The retained verified
BFME 1 pointer is `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; official master
was fetched to `fc5658cca3167be185f1c20b8e4cbe731979f4ea`. The overdue pointer
update remains held by `codex-a44d-root`'s `file:reference/open-bfme-1` claim.
No pointer advance or successful freshness stamp was made.

## Acceptance and limits

- `rehome_rows.py --limit 1`: exact home placement for the selected split row.
- `add_match.py --replace-existing`: home byte gate **165/165**, row verified.
- `link_check.py --prepare-current` on home, split and SetRef before, then
  home and SetRef after: **168/168** matched rows both times, 19 strings,
  24 float literals and 86 named imports; zero skipped/baselined references.
  These establish current self-strict compiler receipts and byte gates only.
- Ordinary `link_check.py` on the same explicitly listed sources before and
  after: **0 linked bytes**. Full transcripts are retained. The old index
  still includes the removed split object, so the after preview still names
  its stale duplicate. No index/status measurement was edited, no custom
  deletion-adjusted preview was substituted, and no closed-strict gain is
  claimed. A future runner census will measure the ownership repair.
- Declared-definition check, `check_csv.py` and `git diff --check` pass.
- `data_check.py --converged` on home and SetRef: two sources, eight addresses,
  zero second names and zero unjudged rows.

MilesAudioManager retains other STL/provider and unresolved-call blockers;
SetRef still needs the `Rva0010F058` constructor and `Rva0010F962` method.
An independent Matrix3D lead was handed back in re_attempts.log: several
wrong constructor emitters need coordinated repair and the folded Vector4
callee identity is not independently admitted. Three dry-run name_globals
candidates produced zero supported rewrites. No full link cycle, census
build/history, nightly or boot operation was run.
