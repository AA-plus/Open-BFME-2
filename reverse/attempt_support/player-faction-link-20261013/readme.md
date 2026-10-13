# playerFaction cache ownership repair

At BFME 2 base `19e6bde293`, rename the existing eight-byte cache definition
and its three matched consumers from `g_00DBDE44` to `TheKey_playerFaction`.
Add one verified data owner in `reverse/data_rows.csv`. No code row, symbol
pin, alias, layout, shared header or census/status counter changes.

## Target proof

Retail RVA `0x009BDE44` holds `00000000 9c95c000`: a zero cache key and VA
`0x00C0959C`, pointing to the complete `playerFaction` string including null.
The existing provider emits two words and one DIR32 string relocation;
compiler sizeof, allocation extent, initializer and relocation are checked by
the normal data gate. The three native code operands at RVAs `0x0032DF85`,
`0x002AC51D` and `0x0032A649` all contain VA `0x00DBDE44`. Before/after object
proofs identify each consumer, decoration, row extent and relocation kind.
All definitions and declarations found for the old spelling are changed
together; the sole provider remains in its established TU.

The spelling is descriptive and donor-derived, not a recovered BFME 2 symbol.
Verified BFME 1 pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` was reviewed:
`targets/game/reverse/identity_evidence/012a77a8-012ac510-data-identities.md`
records the eight-byte faction key's data ownership repair, and its
`data_rows.csv` and `Rva000D1C30FindSkirmishTemplateSide.cpp` bind one
`TheKey_playerFaction` provider to the Player consumer. That ownership repair
is applicable as a lead. BFME 2 retains its own cache type, mutability,
addresses and accessor contract; initializer and consumer evidence are
independently verified here. Other donor key/table repairs were not imported.

## Acceptance and measured improvement

- Normal four-source byte gate: 16/16 function rows, six data rows, six literals
  plus two empty-string refs (zero baseline/skips), and one float ref pass.
- Bounded `link_check.py --prepare-current --paths-from sources.txt` passes
  before and after, giving strict reusable self-verification receipts for all
  four explicit providers. It does not establish closed-strict closure.
- Shadow data identity audit improves **7 -> 4 findings**: all three faction-key
  wrong-name findings are removed. The four residual findings concern the
  unrelated Type cache, playerName cache and neutral display-name object.
- Enforced converged-data check: four sources, eight addresses, zero second
  names and zero unjudged rows. CSV and frozen-file checks pass.
- Legacy local link preview, index measurement `cb660e4d97` (2026-10-13 04:02):
  **three of four units link, 1,644 existing authored bytes, before and after**.
  The preview's printed `0 -> 1,644` compares with its older census; that gain
  predates this repair and is not attributed to it. PlayerSkirmishSideFind still
  fails on wrong-selected `SidesList::getSkirmishSideInfo(int)`.

The verified improvement is eight newly owned retail data bytes and three
resolved data-name findings, with **zero new authored C++ bytes and zero
incremental legacy linked-byte gain**. Seven old source spelling occurrences
are removed. The current hatch counter does not recognize plain `g_<hex>`
spellings; no hatch-register reduction is claimed and no baseline is edited.
No closed-strict gain, link.exe measurement or actual data-back placement is
asserted. No maintainer-only census, full link cycle, nightly or boot runner
was started.

## Remaining work

Official BFME 1 freshness fetch found master at
`339b31084dfc5b2e33be3b0b336f42e97c2e0dda`, beyond the verified pointer.
A baseline full byte build was started but interrupted before any verdict;
comparative verification and pointer update remain outstanding. The clean
verified checkout/pointer and missing success stamp are preserved. The bounded
repair above has independent successful verification against those inputs.

Other inspected linker leads are already repaired, foreign-claimed, or have
unchanged recorded compiler-shape blockers. No unchanged deferred body was
retried. The Player method provider and four residual data findings need
separate evidence and claims; they are not hidden by this ownership repair.
