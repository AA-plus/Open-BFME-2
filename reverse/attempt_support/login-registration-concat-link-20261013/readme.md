# Login registration concat provider repair

Base checkout: `4c3004f564`. The local census index measures `d753dedd98`
(2026-10-12 22:16); its hash and base revision are in `index-meta.json`.
The committed repair queue instead measures `2a20912cc9` and served discovery
only. No per-row data-back artifact was used; no census or status was rewritten.

## Target evidence

The existing 335-byte `AptOnlineLogin::OnBttnRegisterFESL` at RVA `0x0056E849`
appends the registration executable suffix. Original object relocation `+0x7F`
names `AsciiString::concat(const char *)`, but the retail REL32 operand reaches
`0x00005629`. The existing ledger owns that complete 37-byte body as
`StringBase<char>::concat(const char *)` in WWLib/string_base.cpp.

Bind this call directly through the existing one-pointer StringBase view,
as supported by the canonical AsciiString shim. Before/after call inventories
prove the same operand and native destination, and the full byte gate proves
all consumer rows unchanged. This introduces no identity, layout, pin, alias,
header, compiler flag or ledger range. Existing donor provenance stays intact.

## Donor review and deferred work

Reviewed verified BFME 1 pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
and donor repair `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`, including its
GetSelectedPortraitImage diff and 36/36 gate evidence. Its direct StringBase
provider principle applies; its compare body and BFME 1 addresses do not.
BFME 2's native destination and complete verification independently justify
this local adaptation.

Official master was fetched at `4a6944e728305f824ef3ed103e703114d8d62fb6`.
The overdue pointer update is held by the live foreign
`file:reference/open-bfme-1` claim (`codex-a44d-root`). The clean verified
checkout and success stamp were retained. Comparative full verification of
updated donor inputs remains outstanding.

MapCacheWriteCacheINI was screened and immediately handed back without edits:
its existing blocked entry records a direct-concat trial changing later flag
select instructions (concat-team-map-base-link-20261013). No new evidence
addresses that compiler-shape wall. Its file/RVA claims were released; no
blocked build was repeated.

## Acceptance

- Entire consumer ordinary byte gate: 35/35 rows, 91 literals, 12 empty-string
  references, five named imports; no skipped or baseline references. The
  renumbered InitGadgets funclet is verified from its parent's EH placement.
- Before/after bounded `link_check.py --prepare-current` on consumer and
  provider: 72/72 rows, 95 literals, 27 empty-string references, eight imports.
  Both final objects have current strict reusable self-verification receipts.
- Ordinary local `link_check.py` on these two sources: findings **50 -> 49**,
  removing only selected `AsciiString::concat(const char *)`; zero added
  findings. Provider stays LINKS, consumer stays blocked; aggregate linked
  bytes **1,185 -> 1,185**. This is a legacy census preview with self-strict
  objects, not closed-strict closure or an actual link.exe measurement.
- Declared-definition check accepts all consumer definitions; converged-data
  check accepts both sources, eight addresses, zero second names/unjudged rows.

New authored C++ bytes and incremental linked bytes are zero. The verified
improvement is one removed dependency finding. Remaining findings include
MessageBoxOkCancel/rva005AF12F providers, duplicate encoded-string helpers,
STLport COMDATs and selected InitGadgets/password-provider copies; the complete
inventory is in `link-after.txt`. No full link cycle, census build/history,
nightly or boot operation was started. Broader closure remains outstanding.
