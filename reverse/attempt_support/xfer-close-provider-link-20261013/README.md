# Xfer close provider binding repair

Seven consumers referenced `?close@XferSave@@QAEXXZ`, a pin at retail RVA
`0x0060C8CD` with no compiled definition. The existing whole 45-byte provider is
`?bfmeClose@Gen009D6DD0@@QAEXXZ` in `Gen009D6DD0.cpp`. The provider and its
existing callers retain their spelling; seven declaration-only views bind nine
calls directly to that provider. No new symbol pin, implementation, alias,
ledger row, shared header or baseline change is needed.

Target evidence: each changed call operand in its own matched retail row targets
`0x0060C8CD`. All nine object REL32 operands have zero addend. Before/after
non-debug, non-directive sections and their relocations are identical after
normalizing the one callee spelling and compiler-generated local label names
with unchanged sections/offsets. External definitions are identical. The provider
object is unchanged. Object and source hashes and each retail call are recorded
in `object-proof.json`; scratch objects are retained locally under
`build/xfer-close-link-20261013/`.

Reference review: BFME 1 checkout `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
contains the same provider name in `game/Libraries/Source/xfer/Gen009D6DD0.cpp`
and a declaration/cast caller in
`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerRva006B7AE0.cpp`.
That naming pattern is applicable; the donor body, ABI, offsets and settings are
not imported. BFME 2 call identity is independently established by retail operands
and the existing whole-body byte gate. The outdated provider source comment's
BFME 1 RVA does not supply the BFME 2 address. The previously blocked reference
freshness comparison remains unresolved; the verified checkout and stamp are
preserved.

## Acceptance and measurement limits

Source base: `f1133bec9d`. Census discovery index: `cb660e4d97`, dated
2026-10-13 04:02; its SHA256 is recorded in `index-meta.json`. These checks do not
update the census, index or status. The later status measurement is not used to
claim a gain.

Before and after:

- `python3 tools/link_check.py --prepare-current --paths-from SOURCES` passes
  all 420/420 matched functions in eight units with strict reusable receipts,
  two data rows and no byte baselines, skips or unverified literal references.
- `python3 tools/link_check.py --paths-from SOURCES` returns 1 because other
  blockers remain. Exactly seven `XferSave::close` unresolved findings disappear;
  every other finding remains unchanged. Legacy LINKED stays 45 -> 45 bytes,
  with the provider the only clean unit. This is a dependency repair, not a
  claim of additional linked bytes.
- `python3 tools/eh_verify.py --sources-from SOURCES --json OUTPUT` passes
  90/90 tables. Renumbered funclets are independently located through parent EH
  data by the byte gate.
- `python3 tools/find_declared_unmatched.py --fail --paths-from SOURCES` and
  `python3 tools/check_csv.py` pass.
- `python3 tools/data_check.py SOURCE...` reports the same 18 pre-existing
  shadow wrong-name findings before/after, with zero unread rows.
  `python3 tools/data_check.py --converged --sources-from NUL_SOURCES` passes:
  eight addresses, zero second names and zero unjudged rows.

`--refresh --current-ledger` refuses closure because 451 current-ledger objects
are missing. Strict byte receipts do not establish self-strict link closure;
no self-strict or closed-strict gain is claimed. Remaining blockers include
XferSave constructors, XferMD5CRC definitions, subsystem providers, global names,
STLport COMDAT selections and wrong selected Xfer destructors. Full link-cycle
verification remains a maintainer lane. Authored C++ coverage gain: zero bytes.

The source list and raw local check results are stored alongside this record.
