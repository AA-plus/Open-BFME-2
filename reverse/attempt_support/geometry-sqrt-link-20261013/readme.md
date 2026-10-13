# Preparation recovery (2026-10-13)

The evidence below describes the original db66991b82 attempt, not a new
repair at today's upstream. Preparation rebased that commit onto
b59e5c939e326f2e19c3ba643c1b56a70e2f340a and stopped on a comment-only
conflict in Rva009F66F0.cpp. Upstream 6b4082fee4 already contains the same
scoped math-header linkage fix, and 6c83ef8077 subsequently renamed the
geometry call to its rowed CollidesWith identity. Kept the complete current
upstream source and comment; no obsolete code or pin was reintroduced.
Continued the rebase without aborting or skipping the saved evidence commit.
The recovered commit contains historical evidence and the original attempt
log entry; it claims no fresh source/link improvement.

Applied the retained stash with --index. It has no tracked worktree or
index edits. All 31 untracked files (20 assembly dumps and 11 ZH sweep
artifacts) restored byte-for-byte; recovery-manifest.json records their
paths and SHA256 digests. They remain untracked, available for their owners.
The stash, backup ref and preparation record are retained for the runner.
The conflict index is clear, and the source equals origin/master exactly.

Recovery acceptance at b59e5c939e plus retained evidence: check_csv passes;
./build.sh Rva009F66F0.cpp passes all 3 rows, both float literals and all
reference checks; link_check.py --prepare-current accepts one explicit
provider with strict reusable receipts. find_declared_unmatched reports all
definitions matched; class_gate passes; git diff --check passes. No source,
header, symbols, baseline or tooling change was needed during recovery.

The ordinary local link_check uses the preserved census index measuring
d753dedd98 (2026-10-12 22:16), not the newer committed status measurement.
It still reports LINKED 0 -> 0 for this 263-real-byte unit, unresolved
GeometryInfo::CollidesWith and a selected non-retail GeometryInfo constructor.
The CollidesWith finding is against the old index; this recovery did not
refresh the whole tree or establish a closed-strict closure. Do not read the
historical bfmeIntersects finding below as a current source reference.
Self-strict preparation passes; legacy preview remains blocked. No census
build/measure/history, full link cycle, nightly or boot operation was run.

Required progress.py origin/master reports +0 authored C++ bytes and +0
linked bytes. The wrapper fix was already published upstream; the session
recovers preserved evidence and files only. No new task was drawn.

---

# Geometry query square-root emitter repair

Base: 2d18d8a31aef8b0e6a384d9ab66b6a48c518c968. Discovery used
repair_queue.py link and link_rank.py. The available local census measures
d753dedd98, 2026-10-12 22:16; committed link_status.csv measures
2a20912cc9, 2026-10-13 08:08 and serves discovery only. The index SHA256
is in object-proof.json. No census, history, status or data-back ranking
was changed or manufactured.

Claimed file:Code/GameEngine/Source/Common/Rva009F66F0.cpp before editing.
Include MSVC's original math.h with scoped static-inline linkage. The
existing geometry query already inlines its square root. Its arithmetic,
flags, class views, static lifetime, code identity uncertainty and target
calls remain unchanged. No pin, alias, new provider, global, marker,
optimization pragma, shared header or ledger row was added.

The target proof is the three existing whole byte-verified rows: parent
at 0x00628A60 (253 bytes), registered static cleanup at 0x007B9AE0
(10 bytes), and EH handler at 0x007A795E (10 bytes). The source's BFME1
address remains donor provenance, not the target address. Independent target
layout and identity uncertainties remain as recorded in the original rows.

object-proof.json shows exactly two removed 7-byte COMDATs, sqrt(float)
and sqrtf. All four retained COMDATs have identical complete bodies,
relocation tuples, sizes, digests and retail verdicts. Strong definitions,
undefined symbols and weak bindings are unchanged. Before/after strict
self receipts are current, with source/object hashes attached. Complete
snapshots and source/object preparation backups remain locally under
build/link-seat-20261013.

Acceptance: bounded --prepare-current passes all three rows before and
after; ordinary ./build.sh passes 3/3 and both float literals, zero skipped
or baselined references. EH graph is EXACT. Declared-definition, class,
new-variants admission, CSV and whitespace checks pass. Enforced converged
data checking finds zero second names or unjudged rows at eight addresses.
The shadow data check retains one baseline finding (the existing static
initialization guard); unchanged external facts prove no new binding.

Same-index current-object local link checks remove exactly the two surplus
COMDAT findings, with no additions: four findings become two. Consumer
LINKED stays 0 -> 0 (263 own real bytes); it remains blocked on
GeometryInfo::bfmeIntersects and the selected non-retail GeometryInfo
constructor. These are separate provider investigations and were not
retried. Self-strict is established; no closed-strict closure, actual linker
placement or census gain is claimed. This repair adds zero authored C++ bytes.
No maintainer-only census build/measure/history, link cycle, nightly or boot
runner was started.

Donor review: verified checkout/gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
and its corresponding Rva009F66F0.cpp were inspected. Its source remains
the semantic provenance. Reviewed d2e21369067f2f2c762c1c7ec2792c75f1ecf53d:
suppressing a redundant external emitter is applicable; its constructor
alias and pin scaffold are inapplicable and were not imported. Reused the
unchanged broader donor linking scan recorded in prior geometry/math repairs.
Official BFME1 master was fetched at 7fbed69e46153928a20329704ec6e8aec2782f40.
The overdue verified-pointer update remains foreign-claimed by codex-a44d-root;
retained clean verified inputs and the old success stamp. Comparative full
verification and pointer publication remain with that owner.

A read-only check of Rva003FA781.cpp found its current object already LINKS
(769 bytes); its census cos(float) finding is stale, so no edit was made and
its file claim was released. name_globals.py --dry-run found no rewrites for
Rva004FA738ListenerWalks.cpp or WinMain.cpp. Pre-existing untracked dumps
and ZH sweep files are preserved.
