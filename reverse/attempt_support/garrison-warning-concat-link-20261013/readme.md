# Object-creation warning concat link repair

BFME 2 base: 6b4082fee4. Queue: committed link status measured at e181b4b6c5
(2026-10-13 11:22 UTC). The unchanged local census index used for both
previews is cb660e4d97 (2026-10-13 04:02 UTC), with its SHA256 recorded in
object-proof.json. No per-row data-back artifact or whole-link measurement
was used. No ledger, pin, baseline, compiler flag or shared header changed.

## Native evidence and change

The two existing warning paths in ScriptActions_garrison.cpp append the
object/unit name and the literal ` already exists. Failed Create.` before
AppendDebugMessage. The complete 479-byte doCreateObject at 0x003C4EC3
calls object concat at operand +0x65 (native destination 0x6987) and literal
concat at +0x72 (native destination 0x5629). The complete 658-byte
createUnitOnTeamAt at 0x003C50A2 has the same calls at +0x54 and +0x61.
The existing 37-byte StringBase<char>::concat(const char *) provider in
string_base.cpp owns 0x5629; its operand +0x1C calls the established
length-overload at 0x369A0.

Bind each literal through the existing shared StringBase<char> view.
The object concat overloads keep their original binding. Full body bytes
are unchanged; exactly one relocation in each parent changes to the
retail-proven provider name. The other 109 emitted COMDATs retain identical
bodies, relocation digests and names. No new COMDAT appears or disappears.
The change removes the consumer's reference to the selected non-retail
AsciiString literal-concat wrapper. The existing shared one-pointer view
and native call edges justify the adaptation; no new layout or identity
is inferred from bytes alone. Existing WB/ZH provenance remains intact.

## Donor review and freshness

Reviewed official BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187:
its direct StringBase binding principle is applicable; its compare body,
BFME 1 addresses and layouts are inapplicable and were not imported.
This continues the already verified BFME 2 threat-warning and AI-upgrade
concat repairs. Retained committed verified BFME 1 checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master was fetched and
reached 96180b9f28c3161ef16c2f620d283d0de3ada95f. The live foreign
file:reference/open-bfme-1 claim (codex-a44d-root) prevents this seat's
pointer update. Preserve its work and the verified inputs; no freshness
success stamp was written. Comparative full verification remains pending
with that owner. Existing deferred map-cache/peer-options repairs were
checked and not retried.

## Acceptance and remaining findings

- Ordinary changed-unit gate: 26/26 rows exact, including EH handlers and
  four funclets resolved through their exact parent graphs.
- Explicit consumer/provider preparation before and after: 63/63 rows,
  14 string literals, 17 empty-string references, one compiler float,
  three named imports, zero baselined or skipped references. Both sources
  have reusable current self-strict receipts.
- Local legacy preview: consumer findings **13 -> 12**, removing only the
  selected literal-concat finding and adding none. Provider still LINKS.
  Cohort LINKED remains **1,185 -> 1,185 bytes**; the consumer's 3,921 real
  authored bytes still do not link. This is a verified blocker reduction,
  with zero new authored bytes; no closed-strict or actual-link gain claimed.
- Declared definitions, canonical class gate, converged data (two sources,
  eight addresses, zero second names or unjudged rows), CSV and diff checks pass.

Remaining consumer findings: four unresolved names (filter allow, two
Team position methods, notification-box forwarder); seven COMDAT findings
(filter/vtable and ObjectID-vector families); one selected vector-clear
finding. These need separate provider/class reconciliation. No unchanged
blocked reconstruction was retried. Full link cycle, census rebuild,
nightly and boot verification were not run.
