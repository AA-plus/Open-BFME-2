# Script debug literal-concat emitter repair, 2026-10-13

At worktree base `15ff632216dce093e030e17201f080eee50c4495`, the local census
index measured at `cb660e4d97` (2026-10-13 04:02) selects one wrong
`?concat@AsciiString@@QAEXPBD@Z` forwarding COMDAT, emitted by
`ScriptEngine_appendMessage_Rva00341350AdjustVariableForwarder.cpp`.
`repair_queue.py link` and `link_rank.py --near 2 --top 25` served this shared
blocker. Current-object checks, rather than the old queue's consumer counts,
establish the before/after improvement below. No per-row data-back artifact
was available or used; no census index, status or counters were edited.

## Target evidence and change

The existing ledger owns the 37-byte retail literal-concat provider at RVA
`0x00005629` as `?concat@?$StringBase@D@@QAEXPBD@Z`, in `string_base.cpp`.
The existing 261-byte `_appendMessage` row at `0x002053FA` selects one of two
literal pointers, then calls this provider at `0x0020549B`. The two source
branches converge on one REL32 operand, at body offset `+0xA2`;
`relocation-proof.txt` checks this against retail and the strict current object.
The first attempt-log entry incorrectly counted two operands; its immediately
following correction records the shared call.

Declare the AsciiString literal overload without a forwarding definition and
bind the two literal branches to the existing StringBase<char> base view.
The complete five-row byte gate proves the matched code is unchanged; the
object no longer defines or references the wrong literal wrapper. The existing
inheritance relationship supports the cast. No new identity, layout, pin,
alias, global, header, ledger row or range is claimed.

## Donor review and freshness

Reviewed verified BFME 1 input `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` and
its `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` compare repair: bind callers to
the real StringBase provider and avoid the extra AsciiString emitter. This is a
structural lead; BFME 2's own call and byte verification establish applicability.
Pool-binding donor `0835ab92bef30e3303e729a0ce09cf591368d0cd` and constant repair
`43eba9f405f09034e88f79250ac667c166d5370a` were reviewed as separate leads;
the latter does not apply to this code-only blocker. No donor body or offset
was imported.

Official freshness fetch found BFME 1 master at
`13617ada5219e1dcc58774bb8ba9abc8f28fdf47`. The live foreign
`file:reference/open-bfme-1` claim held by `codex-a44d-root` prevents the pointer
update. Retained the clean committed inputs; did not advance the success stamp.
Comparative full-byte verification of updated donor inputs remains outstanding.

## Acceptance and measured improvement

- `./build.sh` on the changed source: 5/5 rows, 11 literals, six empty-string
  refs, six imports; zero skipped or baseline refs.
- `link_check.py --prepare-current --paths-from sources.txt`, before and after:
  all eight explicit owned safe providers have strict reusable self receipts;
  62/62 rows, 40 literals, 28 empty-string refs, 11 float refs, 17 imports pass.
- Ordinary `link_check.py --paths-from sources.txt`, before and after:
  **legacy census preview**, seven of eight units link, **4,468 -> 4,468 current
  authored bytes**. The emitting unit's blockers fall **8 -> 6**, removing the
  wrong literal-concat COMDAT and wrong-selected finding. Its five unrelated
  unresolved symbols and wrong-selected `ScriptEngine::updateFades` remain.
  Both previews print 1,185 -> 4,468 relative to the older census; that difference
  predates this repair and is not credited here.
- `before-symbols.txt` and `after-symbols.txt`: every checked object self-strict
  current; wrong wrapper defined before, absent afterwards; provider and all
  six named consumer references remain bound to StringBase<char>.
- `find_declared_unmatched.py` on the cohort accepted; `data_check.py --converged`
  found eight addresses, zero second names, zero unjudged rows.
- `check_csv.py`: 86,975 functions, 17,275 symbols, 298 data rows accepted.
  `git diff --check` accepted.

New authored C++ bytes and incremental linked bytes are zero. The verified
improvement is removal of the single non-retail emitter and two local blocker
findings. No closed-strict or actual link.exe gain is asserted. No full census,
link cycle, nightly or boot verification was started. Broader closure and the
foreign-claimed reference update remain pending.
