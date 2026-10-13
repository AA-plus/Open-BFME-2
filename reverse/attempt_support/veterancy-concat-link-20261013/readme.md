# Veterancy name concat dependency repair

BFME 2 base: e42774cfa2f0973b7bf9b8929feaafb26236308e. Committed link
status was measured at e181b4b6c5 (2026-10-13 11:22 UTC). Local before/after
previews use the unchanged cb660e4d97 index (2026-10-13 04:02 UTC), whose
SHA256 and input/object hashes are in object-proof.json. No missing per-row
artifact was used for ranking, and no census measurement was run.

## Target evidence and binding

The whole 101-byte getVetUpgradeName body at 0x0026F08B has an E8 call
with relocation operand +0x36 whose retail displacement independently
decodes to 0x00005629. The existing StringBase<char>::concat(const char *)
provider owns that complete 37-byte body; its +0x1C operand calls the
established length overload at 0x000369A0. Bind the source's veterancy-name
append through the existing shared one-pointer StringBase view.

All 662 COMDAT bodies and extents are unchanged. The only changed COMDAT
digest is getVetUpgradeName: exactly one external REL32 changes its name
from AsciiString::concat to StringBase<char>::concat. Other parent
relocations retain their targets; local label section offsets agree.
Compiler EH labels renumber, and the normal gate verifies their positions
through the owning parents' EH graphs. No pins, aliases, markers, compiler
flags, headers, ledger sizes or class layouts change.

The unit's existing ZH semantic provenance and inferred identity remain
as documented in its source and ledger. The retail call edge establishes
the provider binding; byte equality does not establish additional identity
or layout facts.

## Donor review and freshness

Reviewed BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 and its
Rva000D4360Owner.cpp change at retained verified donor checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its canonical StringBase binding
principle applies; its comparison body, addresses and layouts are not
imported. BFME 2's previously verified concat repairs establish the local
pattern; this call was independently checked before editing.

Official BFME 1 master was fetched at
86113c355e41e3a2ec27f9b1aafa626d55990e8b. The live foreign
file:reference/open-bfme-1 claim (codex-a44d-root) prevents an overdue
pointer update in this seat. Retain verified inputs and the existing
freshness stamp; comparative full gates remain outstanding with that owner.

## Acceptance and limits

- Ordinary changed-unit gate: 11/11 exact rows, one literal, no skipped or
  baselined references; both renumbered cleanup labels verified by EH data.
- Explicit provider/consumer preparation before and after: 48/48 exact
  rows; five literals, 15 empty-string references, three named imports;
  both objects have current reusable self-strict receipts.
- Same-index legacy preview: 18 -> 17 consumer findings, removing only
  the selected concat provider finding. No finding added. Provider stays
  LINKS. Cohort linked bytes stay 1,185 -> 1,185; consumer's 533 authored
  bytes remain excluded. Self-strict receipts do not establish closed-strict
  closure; no actual-link or closed-strict gain is claimed.
- Declared-definition and canonical-class checks pass. Converged data
  check: two sources, eight addresses, zero second names or unjudged rows.
  Shadow data check: zero findings. CSV and diff checks pass.
- Placement resweep of Upgrade.cpp: zero bodies, zero pins.

Remaining local consumer findings: six unresolved providers (AudioEventRTS
constructor/destructor/assignment, academy classification names, memory
pool allocation and INI audio-event parser), five COMDAT findings (upgrade
constructors/assignment, bitset mask helper and string-vector destructor),
and six selected-provider findings. These require separate supported
provider/class repairs. No full link cycle, census, nightly or boot runner
was started.
