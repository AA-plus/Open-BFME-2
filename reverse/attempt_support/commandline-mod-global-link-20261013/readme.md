# Command-line FileSystem dependency repair

BFME2 base 6e6ad620f2. The supplied index measures cb660e4d97 at
2026-10-13 04:02 UTC; object-proof.json records its SHA256. The committed
link status at 67e1365aa9 served discovery only. No census, status, history
or per-row data artifact was regenerated.

CommandLineMod.cpp now declares the canonical class FileSystem global
TheFileSystem and casts it to its existing BFME2FileSystemFacade access view.
This replaces the private BFME2FileFacade extern and its alternatename.
Exactly one escape-hatch occurrence and its keyed register line are removed.
No new alias, pin, layout, function row, boundary, compiler flag or header
is introduced. This is dependency/debt repair, with zero new authored bytes.

Target facts: the complete parseMod body remains 403 bytes and its existing
10-byte EH handler remains exact. Its zero-addend DIR32 at the recorded object
offset reads native VA 0x00E06A48, whose data_ledger owner is TheFileSystem
in Common/System/FileSystem.cpp. The existing direct facade worker at
0x0060068A remains the provider; no new facade identity is inferred.
Object comparison changes exactly that relocation name and removes the alias
directive. All other nondebug section bytes and flags and relocation targets
remain unchanged. Compiler-local EH label numbers shift by two; comparison
normalizes these to their unchanged section and offset. EH graphs independently
verify exact. The original narrow StringBase teardown alias is retained.

Donor review: verified BFME1 checkout/gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Reviewed 0835ab92bef30e3303e729a0ce09cf591368d0cd and its byte/link account:
using the real data owner instead of a private extern is applicable, while
its Apt pool identities/layouts are unrelated and were not copied. BFME2's
native operand, existing data owner and full byte gate establish this repair.
Official master was fetched at 46c35bc4ddf58df1e7b5552cfc23a4e1d0b36eac.
The previously recorded old/new full-byte freshness comparison remains
unresolved after compiler-lock/stale-TU preparation. The verified pointer,
clean checkout and success stamp were preserved; no freshness success claimed.

Acceptance:

- Before and after bounded strict-current caller preparation: 2/2 rows exact.
  Caller plus unchanged direct worker provider: 14/14 rows exact under both
  prepare-current and ordinary build.sh; three literals, one named import,
  zero reference skips or baselines. Current caller has a strict reusable receipt.
- EH verification: 5/5 graphs EXACT, no baseline/nonexact/missing-object entries.
- Whole-object proof records one canonical zero-addend DIR32, unchanged other
  bytes/relocation targets, and alternatename count 2 -> 1. The baseline loses
  only that proven-removed occurrence. Source original/object snapshots and
  proof script are retained in build/commandline-mod-global-link-20261013.
- Local same-index legacy findings before/after are identical. The pair preview
  remains 467 -> 467 LINKED bytes: worker provider links, caller still fails on
  the selected public narrow StringBase destructor. No self-strict link closure,
  closed-strict gain, census gain or actual link.exe measurement is claimed.
- Frozen-file, class, new-variants, CSV and whitespace checks pass. Converged
  data: eight addresses, zero second names/unjudged rows. Shadow data: zero
  findings. Placement resweep: zero new bodies/pins.

Prior independent scalar-operator trials in tcbspline and the bridge are
recorded blocked, restored and released; see ../scalar-helper-refusals-20261013/.
Other ranked consumers already carry provider repairs newer than the index.
Naming fallback found zero supported rewrites in four screened units.
Rehoming cannot run: build/link_census/census.log is absent (build/wt_link also
absent); this is missing preparation, not an empty lane. Class reconciliation
queue remains populated and needs independent ABI evidence. No maintainer-only
runner was started. Unrelated untracked preparation files were preserved.
