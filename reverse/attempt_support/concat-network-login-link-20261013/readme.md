At checkout `cc3bd1b0be942fbbdcf113a314aaa6c60246bcc7`, the link-repair
queue and ranked selected-provider blockers led to three remaining unclaimed
literal-concat consumers. The committed status is measured at `2a20912cc9`
(2026-10-13 08:08), while this local index is measured at `cb660e4d97`
(2026-10-13 04:02). All before/after previews use that same index;
`retail-calls.json` records its metadata and unchanged SHA-256. No index,
census/status counters or per-row data-back artifact was changed or ranked.

Retail evidence: the original object REL32 operands in
`LadderList::checkLadder` (299B, 0x0054E2FB, +0x73),
`GameInfoToAsciiString` (827B, 0x00400AF8, +0xD1), and
`AptOnlineLogin::OnBttnRegisterFESL` (335B, 0x0056E849, +0x7F)
all call native 0x00005629. The existing ledger owns that complete 37B body
as `StringBase<char>::concat(const char *)` in `string_base.cpp`.
Bind these calls through the existing canonical StringBase view. Each edited
object now references the real provider at its original operand position,
without defining or referencing the selected non-retail AsciiString literal
wrapper. Object-string overloads and other expressions are unchanged. Complete
byte and relocation gates establish target applicability; existing source
identity/provenance uncertainty is retained. No new layout, ABI, identity,
header, pin, alias, marker, flag, row or extent is introduced.

Donor review: BFME 1 committed clean input remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Reviewed repair
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`, which reconciles string compare
callers with the actual StringBase owner: the direct-provider principle is
applicable, its compare implementation and donor addresses are inapplicable.
Also reviewed `d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`, removing seven
non-retail inline BfmeStrVKI constructor wrappers; emitter ownership is a
related principle, but no constructor code was imported. The overdue freshness
fetch reached official master `d567d6e61a2188aac9d62a2cb8771c22d07cb374`.
Another live worker (`codex-a44d-root`) owns `file:reference/open-bfme-1`;
retained verified inputs and did not advance the freshness stamp. Comparative
full verification of updated reference inputs remains with the update owner.

Acceptance:

- Ordinary byte gate before and after: 104/104 matched rows across the three
  consumers and provider, 158 literals, 44 empty-string references, 32 imports,
  zero baseline/skipped references. Renumbered funclet labels verify through
  their owning parent EH graphs.
- `link_check.py --prepare-current --paths-from sources.txt` before and after:
  four strict reusable self receipts, then the unchanged normal byte gates.
  Source/object hashes and currency are recorded in the receipt JSON files.
- `link_check.py --paths-from sources.txt`: legacy census preview removes
  precisely one selected literal-concat finding per consumer, none added:
  LadderDefs 20 -> 19, GameInfoPlayerCounts 16 -> 15, AptOnlineLogin 50 -> 49.
  `findings-delta.json` records the exact differences. Provider still LINKS;
  the three consumers remain blocked; 1/4 units and 1,185 -> 1,185 linked bytes
  are unchanged. No closed-strict closure or actual link.exe gain is claimed.
- Declared-definition check accepted all three touched sources, before/after.
  Converged-data check: four sources, eight addresses, zero second names or
  unjudged rows. Ledger check and `git diff --check` accepted.

New authored C++ bytes: zero. Remaining consumer findings are independently
listed in `after-link.txt`: unresolved FileSystem/PlayerTemplateStore and
container/string COMDAT ownership in LadderDefs; duplicate GameInfo/GameSlot
providers and string/map ownership in GameInfoPlayerCounts; Apt login providers,
STLport/list and InitGadgets ownership in AptOnlineLogin. These require separate
supported repairs. No maintainer-only full census, link cycle, nightly or boot
operation was started. Preserved unrelated untracked `reverse/zh_sweep/` work.

Preparation recovery (2026-10-13): the runner stopped rebasing original
commit `f0a2eda0d0d6713a7d2b0c960b027cae74014066` onto
`8befde4597bebcbd7de3c52851cd6af7dd179e42`. All three source fixes were
already landed independently in upstream: login in `576ba37a82`, network
rules in `a4c9d1b541`, ladder in `36bce8d6f5`. Retained the upstream login
cast spelling when resolving the single conflict; network and ladder edits
were already identical. The recovered commit preserves historical evidence
and its attempt record; it adds no source or ledger changes relative to the
recovery base. No commit was skipped, and the rebase completed normally.

Applied saved stash `c2987715ac06282ee1e74a167459417a948491b8` with `--index`.
Its tracked and index diffs were empty. All six saved untracked sweep files
were restored byte-for-byte and remain untracked; their paths and hashes are
in `recovery-state.json`. The backup ref
`refs/runner/preparation/1791885218405222267`, stash and preparation record
remain available. No saved change was discarded or left conflicted.

Current acceptance at the recovery base is recorded separately from the
historical results above: `recovery-prepare.txt` verifies 110/110 rows across
the same four providers, with four strict reusable self receipts, 158 literals,
44 empty-string refs and 32 named imports, with no baselined or skipped refs.
`recovery-receipts.json` confirms each consumer still binds the original
literal-concat operand to the StringBase provider. `recovery-link.txt` is a
legacy census preview against unchanged measurement `cb660e4d97`, not a
closed-strict result: one of four units links, 1,185 linked bytes unchanged;
the three consumers retain independent blockers. Its findings are compared
with the historical after-preview in `recovery-state.json`: ladder findings
are 19 -> 18 from intervening upstream work, with no added findings; network
and login remain 15 and 49. No new linked
or authored bytes and no actual link.exe or closed-strict gain are claimed.
Ledger, declared-definition, converged-data (four sources, eight addresses,
zero second names or unjudged rows), and whitespace checks passed. No source,
header, verifier, baseline, index or census status was changed by recovery;
no new tasks or claims and no maintainer-only operations were started.
