# AI team debug append dependency repair

BFME 2 base: 0ae322d527a583109c2640501d41038e676e3461. Committed link
status was measured at e181b4b6c5 (2026-10-13 11:22 UTC). Local before/after
previews use the unchanged cb660e4d97 index (2026-10-13 04:02 UTC). Its
SHA256 and current source/object hashes are in object-proof.json. No census
measurement or missing per-row artifact was used for ranking.

## Target evidence

AIPlayerTeamBuild.cpp's 20 emitted literal-append call edges, across eight
complete parent bodies, independently decode from retail E8 displacements
to 0x00005629. The existing StringBase<char>::concat(const char *) provider
owns that complete 37-byte body. Its +0x1C call operand reaches the existing
length overload at 0x000369A0. Bind the 22 source literal-append statements
through the existing shared one-pointer StringBase view; two statements are
eliminated by the compiler. Object-string appends retain their bindings.

All 188 COMDAT bodies and extents are unchanged. The only changed COMDAT
digests are those eight parents: exactly 20 external REL32 names change
from AsciiString::concat(const char *) to StringBase<char>::concat(const
char *). Every other parent relocation retains its target; compiler-local
label section offsets agree. The ordinary gate verifies owning-parent EH
graphs for cleanup labels that renumber. No pins, aliases, markers, compiler
flags, headers, ledger extents or class layouts change.

The unit's existing Zero Hour semantic provenance and inferred identities
remain as documented in its source and ledger. Retail call edges prove
these provider bindings; equal bytes establish no further identity or
layout facts.

## Donor review and freshness

Reviewed BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 and its
Rva000D4360Owner.cpp change at retained verified donor checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its canonical StringBase binding
principle applies. Its comparison body, addresses and layouts are not
imported. BFME 2's earlier concat repairs provide the local pattern; each
call edge here was independently checked before editing.

Official BFME 1 master was fetched at 3fdaab727. The live foreign
file:reference/open-bfme-1 claim (codex-a44d-root) prevents this seat's
overdue pointer update. Retain verified inputs and the existing freshness
stamp; comparative full gates remain outstanding with that owner.

## Acceptance and limits

- Consumer ordinary byte gate: 35/35 exact rows, 37 literals and three
  empty-string references, seven float literals, no baselined/skipped refs.
- Explicit provider/consumer preparation before and after: 72/72 exact
  rows, 41 literals and 18 empty-string references, seven float literals,
  three named imports. Both objects have current reusable self-strict
  receipts; the census index and link status remain unchanged.
- Same-index legacy preview: 32 -> 31 consumer findings, removing only the
  selected AsciiString literal-concat finding. No finding added. Provider
  remains LINKS. Cohort linked bytes remain 1,185 -> 1,185; consumer's
  9,097 authored bytes remain excluded. Self-strict object receipts do not
  establish closed-strict closure. No actual-link or closed-strict gain is
  claimed, and authored C++ bytes do not increase.
- Declared-definition and canonical-class checks pass. Converged data
  check: two sources, eight addresses, zero second names or unjudged rows.
  Shadow data check: zero findings. CSV and diff checks pass.
- Placement resweep: zero bodies, zero pins.

Remaining consumer findings are 13 unresolved providers, 16 COMDAT losers
and two selected list-base constructor/destructor providers, listed in
link-after.txt. They include TeamInQueue, Pathfinder, TeamFactory, script
and build-list dependencies, STL list/vector/allocator copies and private
engine getters. These need separate supported provider/class repairs.
No full link cycle, census, nightly or boot runner was started.
