# Scored-kill announcer tail binding repair, 2026-10-13

BFME 2 base: `42117f4498b1a0b471098b631f9dea30a18a6a15`.
The available local census index measures `d753dedd98`, 2026-10-12
22:20 UTC, SHA-256
`ab00d079b270151a7af65abbe2dd92e85bc51a5f27b37d76d8902e92f428d05c`.
The committed repair queue instead measures `67e1365aa9`; it supplied
leads, not the before/after measurement. No per-row data-back artifact or
closed-strict result was used. Neither census index nor status was changed.

## Target evidence and change

The complete 39-byte native body at `0x00414F5E` calls the already matched
range erase at `0x00414760`, loads ThePlayerList, writes the two fields at
`+0x28` and `+0x2C`, then tail-jumps to `0x00414DAA` with the original
this pointer. The displacement at body offset 35 independently computes
that destination. The complete 247-byte destination is already owned by
ScoredKillEvaAnnouncer::addMoreTrackersForNewPlayers, with WB identity
evidence recorded in its ledger row and an existing canonical class header.

Rva00414F5ERun.cpp formerly bound that relocation to the undefined private
Rva00414F5EHost::tail name. Include the existing canonical header and call
the existing method on the same receiver. The private run name and its
field accesses remain unchanged; this repair asserts no new original name
or class layout. No provider implementation, header, compiler setting,
ledger row, pin, alias, marker, baseline or extent changed.

objects-before.json and objects-after.json capture strict-current objects
for the consumer, tail provider and range-erase provider. They prove the
consumer's complete compiled body is identical, with only its offset-35
REL32 name changed. Both complete provider objects are unchanged. The
ordinary gate also verifies every native relocation destination.

## Donor review and freshness

Retained clean BFME 1 checkout/gitlink:
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Official freshness fetch reached
`c338ecc7c0db0460045a4585256bb6c7746f2230`.
Reviewed donor repair `4b5d71a18c76439243dc5c641bdcc7890177c863`,
which routes a private call spelling to its independently matched clear
owner. That call-binding principle is applicable; its class, body, layout
and addresses are inapplicable and were not imported. The target's own
canonical declaration and native branch destination establish this repair.

The required reference pointer update remains outstanding. The previous
session's comparative old-input gate waited at the shared compiler lock
and was interrupted without verification success, documented in
../record-assignment-link-20261013/readme.md. This session preserves those
reference inputs and the last-check stamp; it does not claim freshness
success or substitute unverified upstream headers. Full comparative gates
and affected donor sweeps still need a separate reference-update pass.

## Acceptance

- Consumer ordinary byte gate: 1/1 exact, no skipped references.
- Bounded before/after preparation: 88/88 matched rows across three explicit
  providers/consumers, one literal, no skipped or baselined references,
  all three objects current under strict reusable compiler receipts.
  This is self-strict preparation, not closed-strict link closure.
- Local legacy link preview: 1/3 -> 2/3 clean units; 713 -> 752 existing
  authored bytes, a +39-byte local prediction. The consumer and tail
  provider both report LINKS. The broad range-erase unit retains independent
  unresolved and wrong-selected STL dependencies, so both three-unit
  previews intentionally exit 1. No full link.exe, census, nightly or boot
  runner was started; no maintained or closed-strict gain is claimed.
- Converged-data check: three sources, eight addresses, zero second names,
  zero unjudged rows. Ordinary consumer data audit: zero findings.
- Ledger check, declared-definition check and git diff checks pass.
  Hatch counters report no growth. Authored C++ growth is zero.

An optional deletion of the obsolete, correct-address tail pin was tested:
the consumer still passed and pin consistency passed, but name_dependents
conservatively expanded the verification scope to 321 units. The deletion
was reverted before landing. That independent cleanup remains available;
this source-only repair leaves the historical pin intact. The same-family
update consumer already uses the canonical method, so no second call-site
repair was needed.

The first concurrent converged-data probe ran while strict preparation
replaced the consumer object and refused one unjudged row. The final
probe after preparation is clean; no verifier exception was introduced.
