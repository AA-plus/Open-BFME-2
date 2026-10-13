# GameClient singleton consumer binding repair

Base: `55bd70000e2ee21bd48a5fd7c339f9677af39bf3`.
The available census index measures `d753dedd98`, 2026-10-12 22:16.
The committed link-status file describes a newer measurement; this repair's
local preview uses the actual index metadata, not that newer status.

PeerThread and ParticleBaseConstructor declared `TheGameClient` as a pointer
to their private `ClientFrameSubsystem` view. That decoration refers to a
different datum from the existing `GameClient *TheGameClient` definition in
GameClient.cpp. Both now declare the existing global's exact pointer type.
PeerThread already casts to its frame view; the particle constructor now
casts at its slot-31 call. Neither view's vtable or layout changes.

## Target evidence

The complete row at RVA `0x001F4B63` has a DIR32 operand at offset 154;
`listingGamesCallback` at `0x0038CBBA` has one at offset 1404. Both retail
operands are VA `0x00DFE77C`, with zero object addends before and after.
The data ledger's existing provisional entry at RVA `0x009FE77C` assigns
that slot to `?TheGameClient@@3PAVGameClient@@A`, defined in GameClient.cpp.
The provider object contains exactly one strong definition of that name.
Both edited objects now reference it and contain no old private-view spelling.

This is a binding correction using the existing inventory and provider;
it neither promotes the provisional data entry nor recovers an additional
original class name or layout. `verify.py` checks the two current relocation
sites, absence of the old spelling, consumer self-strict receipts and the
provider definition. Archived relocation evidence records the before state.

## Donor review and freshness

Verified BFME 1 pointer: `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Official master was fetched at `d3c65531b`; the submodule remained clean at
the verified pointer. Another worker (`codex-a44d-root`) holds
`file:reference/open-bfme-1`, preventing the required pointer-update work.
The overdue freshness check was not marked successful.

Donor repair `908413c254f83e1f402b991541d4cf68db48ea4e` corrects Apt pool
externs to their owned data-row type. Its binding pattern applies here;
its addresses, layouts and C++ bodies do not. Donor `0a3a4f6052f8c8d25c6c9fbfbf47047a2fe96fdd`
replaces a Miles string literal with the owned empty-string member and is
inapplicable to these frame-counter references. No donor source was imported.

## Acceptance and limits

Before and after, both whole consumer units pass `link_check.py
--prepare-current`: 112/112 function rows, two data rows, 117 literals,
26 empty-string references and 26 named imports; strict reusable self
receipts pass. After compilation renumbered two particle cleanup labels;
the normal byte gate verifies their placements through the parent EH graph.
The existing provider separately passes its normal gate, 3/3 rows and two
data rows. Its object lacks a strict reusable receipt, so this is not a
closed-strict provider proof.

The same two-source legacy local link preview removes one unresolved
singleton reference from each unit and adds no blocker. PeerThread's
unresolved names fall 11 to 10; ParticleBaseConstructor's fall two to one.
Both retain independent blockers; LINKED remains zero bytes. The provider
also retains independent COMDAT/selection blockers. No measured census,
closed-strict, full-link or authored-byte gain is claimed.

Data-name shadow findings fall three to one, with outside-baseline findings
two to zero. The remaining finding is already baselined. The enforced
converged-data check reports eight addresses, zero second names and zero
unjudged rows. CSV, declared-definition and whitespace checks pass.
No pin, alias, baseline, header or data ledger was changed.

A same-cause sweep finds one unused `ClientFrameSubsystem *TheGameClient`
declaration in RenderParticleConstructor.cpp; that unit never references
the global, so it has no corresponding relocation or unresolved link debt.
It is left alone. Large string-class repairs and the GameClient provider
are held by other workers. The particle unit still needs
`Rva001F376E::~Rva001F376E` and a compatible RvaSmartPtr12 destructor COMDAT;
PeerThread retains unrelated constructors, SDK calls, one duplicate and
STL/string COMDAT/selection blockers. No maintainer-only runner was started.
