# Network options literal-concat provider repair

Base c1f0afaedf78ffc47c89aca953472e151f44cfb0. The available runner census
index measures d753dedd98 at 2026-10-12 22:16; the committed link status at
2a20912cc9 serves discovery only. index-meta.json records the index digest,
which remains unchanged. No per-row data-back artifact or ranking was used.
No census/status/history was written and no full link runner was started.

## Accepted target evidence

GameInfoToAsciiString at RVA 0x00400AF8 has a proved 827-byte matched body.
Its literal semicolon append to the rules string has a REL32 operand at +0xD1;
retail E8 independently targets 0x00005629. The existing 37-byte ledger owner
there is StringBase<char>::concat(const char *) in string_base.cpp.
The old call spelled AsciiString::concat(const char *), whose selected real
wrapper overrides the existing alternatename and is not retail's body.
Bind that one literal call directly through the canonical one-pointer
StringBase<char> view. All object-string and character appends keep their
established bindings. No class, layout, pin, alias, global, header, flag,
ledger row/range or hatch is introduced. The semantic body and its boundary
are unchanged. relocation-proof.txt proves the repaired symbol at the same
REL32 offset, native destination, and current strict compiler receipts.

## Donor review and freshness

Reviewed BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187: compare
consumers bind actual StringBase providers through non-derived views. Its
dependency reconciliation principle applies; compare implementations, BFME 1
addresses and target layout claims are not imported. Also reviewed newer
upstream d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (remove non-retail string
ctor wrappers) and d456456cd56156428c28a2f7cad49e396cc4d916 (remove wrong
terrain helper); their specific bodies/names are inapplicable to this change.
BFME 2 native calls and local gates are the independent acceptance evidence.
This continues the existing concat provider repairs, not an unchanged donor
rescan or speculative source reconstruction.

The initial pull fetched official BFME 1 master to
4fe1d0ff4462cabc7593685dc00559689d55da02. Verified clean pointer remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The overdue comparative update
is still held by codex-a44d-root's file:reference/open-bfme-1 claim. No
pointer or freshness success stamp changed; that update remains outstanding.

## Acceptance and limits

- Consumer plus unchanged provider: ./build.sh passes all 58/58 matched
  bodies, 34 string literals, 29 empty-string references and 25 named imports.
  Strict reusable compiler self-verification receipts are current before and
  after; bounded preparation including the rejected/restored peer unit passes
  59/59. This establishes byte identity and compiler currency, not closed
  strict link closure.
- Same three-source ordinary legacy local preview: GameInfo findings 16 -> 15,
  exactly the selected literal-concat wrapper removed; GameSpy 29 -> 29;
  provider 0 -> 0. No added findings. LINKED remains 1185 -> 1185 bytes, all
  from the unchanged provider. findings-delta.json compares complete lists.
- Declared-definition and CSV checks pass. Enforced converged-data check:
  two sources, eight addresses, zero second names, zero unjudged rows.
  Ordinary data shadow findings are preserved in data-shadow.txt.

New authored C++ bytes and measured linked-byte gains are both zero. The
verified improvement is one removed selected-provider finding. Four duplicate
GameInfo helpers and independent STL/container COMDAT and selected findings
remain; their names are in link-after.txt. No closed-strict gain or actual-link
measurement is claimed. A current runner census/full authorized link cycle
remains outstanding. Unrelated untracked dumps and ZH preparation are retained.

## Rejected independent consumer

PeerDefsGameOptions has five literal calls in its existing 1658-byte body at
0x00386501; retail independently targets the same 0x5629 provider for all five.
Direct binding resolves every call and keeps length 1658, but swaps four
stack-slot bytes: zero stores at +0x165/+0x168 use A8/A4 rather than A4/A8,
and loads at +0x258/+0x25B use 55/4D rather than 4D/55. Reordering the local
wins/losses declarations fails the second byte gate. Both rejected logs,
explanation and exact patch (JSON encoded) are retained. The whole file was restored from the
preparation backup, its strict 59/59 gate passed, and its RVA/file claims were
released. It remains blocked on compiler stack-slot allocation; no broken
source, extra pin or inflated extent remains. No partial C++ conversion was
claimed. Resume only with evidence that addresses this specific compiler delta.
