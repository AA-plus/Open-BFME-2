# Skirmish warning concat link repair

BFME 2 base: 6566b119655a0c5fda5e65e4eec76b9402b7046c. Committed link status measured at
e181b4b6c5 (2026-10-13 11:22 UTC). Both local previews use the unchanged
cb660e4d97 index (2026-10-13 04:02 UTC); SHA256 in object-proof.json.
No per-row data-back ranking or whole-link measurement was used.

## Target evidence and change

The complete 622-byte acquireEnemy at 0x004EFB3D has literal concat
operand +0x222 to native 0x5629. The complete 830-byte
recruitSpecificAITeam at 0x004EFFC9 has the same literal call at operands
+0x7C, +0xD2, +0x129, +0x1E5, +0x201, +0x223 and +0x30D.
Nine source statements emit eight calls through compiler tail merging.
The existing StringBase<char>::concat(const char *) owns the whole
37-byte native provider at 0x5629, with its internal operand +0x1C
calling the established length overload at 0x369A0.

Bind the literal appends through the existing shared one-pointer StringBase
view. Object overloads retain their binding to native 0x6987. Both full
parent bodies retain identical bytes and extents; exactly eight callee
relocations change names. No COMDAT is added or removed; the other
107 COMDAT bodies and relocation digests remain unchanged.
The adjustBuildList local switch labels renumber, but their section-relative
target offsets remain identical and its full 704-byte extent (including
jump table) passes the byte gate. All native call destinations were checked
before editing; calls-after confirms the same targets with the new names.

Existing ZH semantic provenance, WB/retail identity evidence and target
layouts remain as established by the current source and ledger. The shared
view and independently checked target call edges support this binding;
exact bytes alone do not establish new class identity or layout.

## Donor review and freshness

Reviewed BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
at retained verified checkout cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Its direct StringBase binding principle is applicable; its compare body,
addresses and layouts are inapplicable and not imported. This follows
verified BFME 2 AI-upgrade and garrison warning repairs. Official master
was fetched at d28d78454; the live foreign file:reference/open-bfme-1
claim (codex-a44d-root) blocks this seat's pointer update. Verified inputs
were retained, no success timestamp written; comparative full gate remains
pending with that owner. Deferred map-cache and peer-options repairs were
not retried.

## Acceptance and limits

- Changed-unit ordinary gate: 22/22 rows exact, including all five EH
  handlers and the switch table; 22 literal and three empty-string refs,
  18 floats, zero baselined/skipped references.
- Provider and consumer preparation before and after: 59/59 rows exact;
  26 literal and 18 empty-string refs, 18 floats, three named imports;
  both sources have current reusable self-strict receipts.
- Same-index legacy local findings: consumer 9 -> 8, removing only the
  selected literal-concat wrapper; no added findings. Provider still LINKS.
  Cohort LINKED stays 1185 -> 1185 bytes; the consumer's 3398 authored
  bytes remain excluded. Zero new authored bytes; no closed-strict or
  actual-link gain claimed. Self-strict receipts do not prove closure.
- Declared definitions, canonical class gate, converged-data check (two
  sources, eight addresses, zero second names/unjudged rows), CSV and
  diff checks pass.

Remaining consumer findings: five unresolved names (TeamInQueue constructor,
TeamFactory findTeam, AIPlayer ready-queue prepend and reinforcement selector,
BuildListInfo template-name getter); three COMDAT findings (sin, cos,
BuildListInfo getNext). These need separate provider/class work.
No full census, link cycle, nightly or boot verification was run.
