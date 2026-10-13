# CommUDP worker binding repair

BFME2 source base: 4264fbe0692c95262529fb6b4501236391707441.
The supplied census index was measured at cb660e4d97, 2026-10-13 04:02 UTC;
object-proof.json records its SHA256. The newer committed link-status report
at 67e1365aa9 was discovery only. No census, status, history or per-row
measurement artifact was regenerated.

Y4CommTransportLife.c's global pump now declares and calls CommUdpProcess
instead of Rva00817B30. The verified C-linkage provider already exists in
commudp.cpp at 0x00683A30. The former missing-provider verdict is reopened
because that real implementation has since landed, not because of a model
change. A Code-source search found no further consumer of Rva00817B30.
No flags, headers, implementation, pins, ledger ownership or extents change.

Target evidence: the pump's existing 110-byte row at 0x00684BB0 contains a
direct E8 call whose native REL32 resolves to 0x00683A30. The provider's
2247-byte row is independently byte-verified, and its current object defines
_CommUdpProcess with C linkage. The declaration retains the existing
int(unsigned int) ABI. Object proof establishes exactly one zero-addend
REL32 symbol-name change; every non-debug/non-directive section's bytes,
flags, association and normalized relocations, and every external definition,
are otherwise identical. The provider object is byte-for-byte unchanged.
This binding repair adds no new identity or layout claims.

Donor review: verified BFME1 gitlink and clean checkout remain
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its DirtySock pump has the same
old Rva00817B30 spelling while its commudp.cpp names the worker
CommUdpProcess. Official master was fetched at
001cf898fa5a0415d9d5c5db631b23b4d530ec3b; its pump still has the old spelling,
so no upstream pump-binding repair was available to inherit. Reviewed linking
repair 6ffd3f498c98872efbb0ad242c3afea4640e4ef5 supplies the general direct
provider-name technique; b870d563b7f4e8b58f433635a39783fb0d7d55cb is an
inapplicable compareNoCase repair. BFME2 call-target proof is independent of
these leads. No donor body is imported.

BFME1 freshness remains overdue. The prior session's required full baseline
comparison needed 5882 stale TUs and stopped at the shared compiler lock;
the old/new full-byte comparison has not completed. The verified pointer,
donor inputs and freshness stamp were preserved, not marked current.

Acceptance:

- Bounded strict reusable preparation before and after passes 33/33 rows
  across caller and provider. An independent ./build.sh check also passes
  33/33, with zero baselined or skipped string, float and import references.
- Both final objects have self-strict current compiler receipts. EH checking
  reports zero EH rows, zero non-exact or baseline entries. Declared-definition
  checks, class gate and git diff --check pass.
- Same-index ordinary legacy local previews remove exactly one unresolved
  finding, _Rva00817B30. The transport's remaining unresolved symbol is
  _g_Rva012C4F88Name, whose data ledger row at 0x009D96E0 is unowned.
  commudp.cpp already links in both previews; its 4740 authored linked bytes
  are retained. The transport remains unlinked. No net linked-byte gain,
  new authored bytes, self-strict link closure, closed-strict gain or full-link
  measurement is claimed.
- Raw gate and preview output and object/source hashes are attached here.
  Reproducible scratch script and before/after snapshots reside in
  build/commudp-caller-link-20261013. Normal commit and push hooks remain active.

The remaining data-provider blocker is logged separately for the constructor
that reads it. Broader link verification remains maintainer-only. Discovery
queues repair_queue.py link and link_rank.py are populated; many older-index
blockers already have current repairs. name_globals.py --dry-run reports zero
supported rewrites. rehome_rows.py --limit 12 cannot run because
build/link_census/census.log is missing; this is missing preparation, not an
empty lane. Unrelated untracked preparation is retained.
