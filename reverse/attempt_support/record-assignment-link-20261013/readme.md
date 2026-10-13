# Record assignment provider repair, 2026-10-13

At BFME 2 base `8befde4597bebcbd7de3c52851cd6af7dd179e42`, the available
local census index measures `d753dedd98` at 2026-10-12 22:20 UTC. Its SHA-256
is `ab00d079b270151a7af65abbe2dd92e85bc51a5f27b37d76d8902e92f428d05c`,
unchanged before and after. Committed link_status.csv instead measures
`67e1365aa9`; that queue supplied leads, not this before/after result.
No per-row data-back ranking or closed-strict artifact was used.

## Target evidence and scope

The STL algorithm emitter's historical size-only views generated implicit
assignments for BfmeAssignRecord28, 44 and 52. Each emitted a 43-byte
AsciiString-plus-words assignment. Independent verified owners at native
0x003F6388 (43 bytes), 0x0055AC1F (88 bytes) and 0x002B828A (75 bytes)
perform different operations: two vector assignments; tracker/list assignment;
and two member assignments plus seven word copies, respectively. Even the
same-size 28-byte-record assignment has different bytes and relocations.
The existing names remain structural views, not newly recovered application
identities. No new target layout is asserted.

Four direct relocations in the emitter's matched copy/fill rows independently
reach those native owners. Declare the three assignments instead of emitting
implicit bodies, following the existing declaration-only sibling policy.
Two consumers, Rva00414B0A and Rva00414F5ERun, also emitted the wrong 44-byte
record assignment through vector erase. Their complete native bodies call
the verified range-erase owner at 0x00414760. Declare that specialization so
they call the owner without emitting erase and its dependent helpers.
The unchanged range-erase provider is included in the acceptance scope.
No header, flag, pin, alias, marker, extent, ledger row or baseline changed.

objects-before.json captures all seven strict-current objects and the
competing assignment bodies. objects-after.json captures the retained owners,
suppressed definitions, and all six native call destinations. Before/after
ordinary gates verify every matched row, including the renumbered funclet.

## Donor review and freshness

Retained BFME 1 checkout/gitlink
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Reviewed official donor repair
`d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`, which suppresses TU-local
BfmeStrVKI constructor bodies by declaring the retained native provider.
That suppression principle applies; its class, implementation, addresses
and layouts are inapplicable and were not imported. The compare repair
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` was also reviewed; compare
semantics are inapplicable to assignment.

Freshness fetch reached official upstream
`b39065ac7f5e64207af26ad6be463c64b670ce04`.
The clean reference claim was acquired. Full ordinary verification of the
old inputs was started before attempting any update, but its Python process
waited on ~/.cache/open-bfme-build.lock (wchan locks_, fd3) for several
minutes without beginning compilation. The waiting process was terminated
with SIGTERM, exit 143; no verification success is claimed. The checkout,
gitlink and last-check stamp were preserved and the reference claim released.
Comparative old/new full gates and affected donor sweeps remain pending.
Changed upstream headers include target-specific meshgeometry.h accesses;
never substitute the new inputs without the comparative verification.

## Acceptance and result

- Changed-source ordinary byte gate: 59/59 exact across three sources.
- Bounded self-strict preparation before and after: seven providers/consumers,
  140/140 matched rows, one literal, zero skipped or baselined references;
  all seven strict reusable receipts current. This establishes self-strict
  currency, not closed-strict LINK closure.
- Ordinary local legacy link_check preview: 0/7 -> 3/7 clean units and
  0 -> 314 existing authored bytes. The clean units are
  BfmeAssignRecord52Assign.cpp (75), Rva0055A91AClear.cpp (213), and
  Rva00414B0A.cpp (26). No census/index/status was written and no full
  link.exe, census, nightly or boot verification was started.
- Both seven-unit previews intentionally exit 1: the other four sources
  retain separate blockers. The three assignment conflicts disappear.
  Rva00414F5ERun loses its erase/assignment conflicts but retains the
  unresolved tail name; the 28-byte record owner retains element-member
  references and vector assignment variants. The two broad STL emitters
  retain other layout-dependent COMDAT and provider blockers.
- Converged-data check: seven sources, eight addresses, zero second names
  and zero unjudged rows. Ordinary touched-source data check passes in
  shadow mode. Ledger, declared-definition and git diff checks pass.
- Authored C++ growth is zero. The +314 is a local legacy prediction,
  not a closed-strict gain or a new maintained census measurement.

## Handoff

The remaining Rva00414F5EHost::tail pin reaches native 0x00414DAA, already
rowed as ScoredKillEvaAnnouncer::addMoreTrackersForNewPlayers in
ScoredKillEvaAnnouncer.cpp. ScoredKillEvaAnnouncerView.h is canonical.
A future repair can examine calling that existing canonical declaration;
no extra alias, pin or private class should be introduced. That follow-up
was not attempted or included in the +314 result. Broader link closure and
the due BFME 1 pointer update remain outstanding.
