# Spiral animation math emitter repair

Source base 897bc9424f6033c1da5ee24c10019d2b42e90e10. Available runner
index measures cb660e4d97 at 2026-10-13 04:02 UTC; committed link_status.csv
measures 2a20912cc9 and serves discovery only. object-proof.json binds the
local previews to the index digest. No index, census, status or history was
written, and no per-row data-back ranking was used.

ProcessAnimateWindowSpiralUpdate and ProcessAnimateWindowSpiralReverse
include the original CRT math.h float overloads with static inline linkage
before PreRTS.h. Their matched trigonometric operations already inline to
the established double CRT calls. This removes competing external copies
without changing operations, compiler flags, layouts, identities, call
bindings, donor provenance, headers, pins, ledger extents or hatch counts.

Target evidence: the existing complete matched rows are update at
0x005C5D33, 333 bytes, and reverse at 0x005C5E80, 261 bytes. The before/after
COFF comparison removes exactly cos(float), sin(float), cosf and sinf from
each object. All 550 retained update copies and 548 retained reverse copies
have identical bytes, sizes, relocation tuples, digests and retail verdicts.
Strong definitions, undefined references and weak bindings are unchanged.
There are no added or changed COMDATs. object-proof.json retains the owned
bodies and relocation tuples, all removed copies, strict source/object hashes
and aggregate hashes of the identical retained sets. Full snapshots and
source backups remain locally in build/spiral-math-link-20261013.

Donor review: BFME1's clean verified checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its ProcessAnimateWindow.cpp
supplies the existing spiral animation semantics, with update/reverse names
interchanged relative to these BFME2 rows. No new donor identity or layout
claim is imported. Reviewed BFME1 repair
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: suppressing surplus non-retail
copies is applicable; its string constructor and pin mechanism is
inapplicable. This adapts the verified BFME2 float/laser/texture math repair
to these independently checked objects. The previous broader donor scan is
reused, rather than repeated without changed evidence.

Official BFME1 master was fetched as
2aa1f01b6a9201ce4026594eea916605e31f7b64. The overdue pointer update
remains foreign-claimed by codex-a44d-root. Verified inputs and the old
freshness stamp are preserved; comparative full verification and pointer
publication remain outstanding with the update owner.

Acceptance:

- Strict reusable self preparation passes before and after for both units.
  The normal ./build.sh gate passes 2/2 complete rows, two float literals
  and one named import, with zero skipped or baselined references.
- Same-index ordinary legacy preview: update findings 8 -> 6, reverse
  findings 7 -> 5. Exactly four trig COMDAT findings disappear; no new
  findings appear. Cohort remains 0/2 clean, LINKED 0 -> 0 bytes.
- New-variants admission, class gate, declared-definition check, CSV and
  whitespace checks pass. EH verification finds no EH rows. Ordinary data
  shadow has zero findings; enforced converged-data check has zero second
  names or unjudged rows across eight addresses.

The verified improvement is eight removed external emitters and four fewer
legacy link blockers, with zero new authored C++ bytes. Self-strict compiler
verification is established; closed-strict closure, actual link.exe placement
and measured census gains are not claimed. No full census, link cycle,
nightly or boot runner was started. A current authorized measurement remains
outstanding.

Remaining AnimateWindow blockers: getCurPos, getEndPos, setCurPos, setVel,
setFinished, and update-only getRestPos. These require a separate supported
class/provider repair; unchanged findings were not retried. Discovery probes
also found WinMain, AptPlayer, AIGateUpdateTrigger and Rva004E5372CloudArcs
already locally clean. GlobalData is foreign-claimed; Object's voice-response
provider has an existing unresolved reconstruction dependency. None was edited.

Required progress.py origin/master reports zero deltas in authored, matched,
linking and linked bytes at this source base. This repair changes no ledger
rows. Unrelated untracked dumps and ZH preparation are preserved.
