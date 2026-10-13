# Status-screen and subtitle concat link repair

At checkout `52ae3981ffb3bece3441ac78fd2e2b60a12cb707`, the local census
index is measured at `d753dedd98` (2026-10-12 22:16), while the committed
link-status queue is measured at `3906ea7b97`. The queue served discovery;
all before/after previews use the same local index. Its metadata and hash are
in `index-meta.json`; no census/index/status counters were changed and no
per-row data-back ranking was used.

The two owned consumers still referenced the selected, non-retail
`AsciiString::concat(const char *)` definition. Original object relocation
positions prove three retail direct calls to RVA `0x00005629`: two in the
613-byte MilesAudioManager subtitle drain at `0x0005B708`, and one in the
954-byte AptPlayerStatus constructor at `0x004E4A45`. See `retail-calls.txt`.
The existing ledger provider is the 37-byte
`StringBase<char>::concat(const char *)` in `string_base.cpp`. Bind each of
these calls directly to it through the canonical one-pointer StringBase view.
No new ABI/layout claim, pin, alias or ledger range is introduced. The existing
source identities and semantics are unchanged; target call destinations and
complete byte/relocation verification justify this repair.

Reviewed BFME 1's verified input `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
and donor repair `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`, including its
GetSelectedPortraitImage consumer diff and reported 36/36 function gate.
Its direct StringBase binding principle applies; the compare implementation
and BFME 1 addresses do not. This adapts the already verified BFME 2 concat
repair in `../concat-link-20261012/` to these two independently checked units.
Official upstream was fetched at `c7907b7a8f67e2cf94bd3d438e9af2a9d87423fd`.
Its `b9df6f78d` init-thunk binding repair was also reviewed: the provider
principle is applicable, but its thunk/body and inline assembly are unrelated
to these callers and were not imported. The live foreign
`file:reference/open-bfme-1` claim (`codex-a44d-root`) blocks a pointer update;
the clean, committed verified pointer was retained and the overdue freshness
success stamp was not advanced. Comparative full verification remains with
the update owner.

Acceptance:

- `./build.sh` on both consumers and provider: 44/44 functions, 28 string
  literals, 17 empty-string references and five named imports verified;
  zero string baselines/skips. One complete emitted STLport constructor
  verified against retail owners and resolved callees.
- `link_check.py --prepare-current` on the same three sources: all three
  have strict reusable self-verification receipts, followed by normal byte
  gates. Object/source hashes and strict currency are in `objects-after.json`.
- `link_check.py --paths-from sources.txt`: the selected concat finding is
  removed from both consumers, with no new finding. This is a legacy census
  preview; provider remains LINKS (1,185 bytes). Both consumers remain blocked
  and the aggregate stays 1/3, 1,185 -> 1,185 linked bytes. This records two
  removed dependency findings, not a closed-strict or actual link.exe gain.
- `find_declared_unmatched.py` passed on both consumers before and after;
  the Miles unit's three pre-existing annotated helpers remain unchanged.
  `git diff --check` passed.

New authored C++ bytes: zero. Remaining independent blockers are UnicodeString
vector erase (COMDAT loser and wrong selected copy) in MilesAudioSubtitleDrain,
and `AptPlayerStatus::rva004E40A6(const char *)` plus
`rva004E44FB(int,int,const UnicodeString &)` in AptPlayerStatusScreen. These
need separate supported repairs. No maintainer-only link cycle, census build,
nightly or boot operation was started; no closed-strict gain is claimed.
