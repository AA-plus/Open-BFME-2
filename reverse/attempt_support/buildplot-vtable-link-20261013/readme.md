# Build-plot icon direct vtable binding

BFME2 source base: 457d35342936c7f24c4fc3778fbb5963f0f6d0d7.
The supplied census index is cb660e4d97, 2026-10-13 04:02 UTC;
its SHA256 is in object-proof.json. Committed link_status.csv at
67e1365aa9 served discovery only. No census, status, history or per-row
measurement artifact was regenerated.

LivingWorldBuildPlotIconCtor.cpp now directly references the existing
??_7Rva0059E242@@6B@ provider via __identifier, removing the address-named
vtbl_00C70F88 declaration and its /alternatename directive. The read-only
provider is OpaqueScalarDeletingDtorsB13.cpp. There was no corresponding
hatch-baseline entry to delete. The source's actual hatch count falls by one.

Target ownership and original constructor identity are inherited evidence:
the constructor's matched vptr store binds C70F88, and the existing destructor
and deleting-destructor rows at 59E242 and 59E28F document that table's slot 0.
The provider object actually defines that exact decorated table name.
Rva0059E242 remains an address-derived identity; this repair does not rename
it to LivingWorldBuildPlotIcon or assert additional class/table layout facts.
No implementation, header, flags, extent, ledger row, pin or alias is added.

Acceptance:

- Strict reusable preparation before and after: 29/29 rows across consumer
  and provider. Standalone ./build.sh also passes 29/29, with all source,
  STLport fold, string, float and import checks; no baselined/skipped references.
- EH verification: four EXACT parents, zero baseline entries.
- object-proof.json compares every non-debug/non-directive section's raw
  bytes, flags, association and normalized relocations. All are identical;
  all external definitions are unchanged. Exactly one zero-addend DIR32
  operand replaces the former alias with its existing target. The provider
  object is byte-for-byte unchanged. Both objects are strict-current.
  Reproducible proof and snapshots: build/buildplot-vtable-link-20261013.
- Class gate, declared definitions, CSV, shadow data and enforced converged
  data checks pass; data has zero findings. git diff --check passes.
- Same-index legacy local preview remains 0 -> 0 linked bytes. Consumer
  blockers remain the base constructor ??0Rva00539411@@QAE@PAXPBH@Z and
  nonretail/selected vector<Rva005C4230 *>::reserve. Provider blockers remain
  ??1Rva00578189@@UAE@XZ and the conflicting Rva0053947D base vtable.
  Self-strict receipts establish the verified hatch reduction. No self-strict
  link closure, closed-strict gain, new authored bytes or full-link gain is claimed.

Dedicated donor scan is reused. BFME1 ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd
supplies the already reviewed direct-vtable-naming technique; its addresses
and types are not transferred. New donor linking commit b870d563b7f4e8b58f433635a39783fb0d7d55cb
was reviewed this session: its compareNoCase repair is inapplicable to this
vtable dependency. Official BFME1 master was fetched at
001cf898fa5a0415d9d5c5db631b23b4d530ec3b.
The clean verified checkout/gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
is retained. Freshness remains overdue: the prior baseline full-gate attempt
(build/seat-current-baseline-full.log) needed 5882 stale TUs and was interrupted
while waiting for the shared compiler lock. The required old/new full-byte
comparison remains outstanding. No freshness stamp or donor inputs changed.

Other permitted leads: name_globals.py --dry-run finds zero supported
rewrites. rehome_rows.py --limit 12 fails because build/link_census/census.log
is absent; this is missing runner preparation, not queue exhaustion. The
repair queue and link_rank remain populated. No maintainer-only runner was
started. Unrelated untracked dumps and ZH preparation remain preserved.
