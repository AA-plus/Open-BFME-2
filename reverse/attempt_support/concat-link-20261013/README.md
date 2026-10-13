# Literal concat provider repair, 2026-10-13

At BFME 2 base `55d19e7104`, the local census index measured at `d753dedd98`
(2026-10-12 22:16) identifies the selected
`?concat@AsciiString@@QAEXPBD@Z` as the sole blocker of the 13 consumers in
`sources.txt`. The last source is the unchanged provider, checked alongside
all consumers. The committed `reverse/link_status.csv` snapshot names
`d9e9abdc70`; it was used for queue discovery, not the before/after measurement.
No per-row data-back artifact was used or census/status counters edited.

## Target evidence

The existing ledger owns the 37-byte retail body at RVA `0x00005629` as
`?concat@?$StringBase@D@@QAEXPBD@Z`, in
`Code/Libraries/Source/WWVegas/WWLib/string_base.cpp`. Retail's 21 edited
call sites target that RVA; `retail-calls.txt` gives each caller's existing
ledger name, RVA, extent and call address. The selected AsciiString literal
wrapper is an additional forwarding body, not this retail provider; an
alternatename does not override a real selected definition.

Bind these const-char-pointer calls directly to StringBase<char> using the
existing canonical one-pointer AsciiString view. String-object and explicit
length overloads keep their established bindings. This continues the five-unit
repair in `../concat-link-20261012/`; it does not change that earlier cohort.
No new layout, pin, alias, global, header, function row or range is introduced.
The canonical header relationship supports the view cast; independent target
proof is the native call destination and complete byte gate.
`relocation-proof.txt` additionally checks strict current object receipts and
all 21 REL32 operands against the provider and native destination.

## Donor review and freshness

Reviewed verified BFME 1 input `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`,
especially donor repair `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`:
AsciiString compare consumers bind the actual StringBase provider directly,
using casts for non-derived views. The direct-provider principle applies;
no donor compare implementation or target ABI claim is imported. BFME 2's
retail calls and local gates justify each adaptation separately. Pool-binding
repairs `0835ab92bef3` and `908413c25`, and nothrow repair `6a18725a5`, were
reviewed as independent leads and not imported into this change.

Official freshness fetch found BFME 1 master at
`ca3f8994d5303c1e7d566a406275352b9a8ef70f`. The live foreign
`file:reference/open-bfme-1` claim held by `codex-a44d-root` prevents the update.
Kept the clean verified pointer and did not advance the freshness success
stamp. Its comparative full-byte verification remains outstanding; this
unchanged blocker is already recorded by the preceding seat.

## Acceptance

- `./build.sh` on all 14 sources: 66/66 matched rows; 54 literals and 32
  empty-string refs, zero baseline/skips; four float refs and 13 named imports.
- `link_check.py --prepare-current --paths-from sources.txt`: all 14 explicit
  safe providers byte-verified with strict reusable self-verification receipts.
  This bounded preparation refreshes the touched objects and leaves the census,
  index and status unchanged. It does not assert closed-strict closure.
- Ordinary `link_check.py --paths-from sources.txt`: **legacy census preview**,
  all 14 units LINKS, 1,185 -> 8,074 bytes, **+6,889 existing authored bytes**.
  Before, all 13 consumers fail solely on the wrong selected literal wrapper;
  see the two before logs and combined after log. Current selected objects are
  refreshed together in the preview's in-memory index.
- `find_declared_unmatched.py`: all 14 accepted before and after edits.
- `data_check.py --converged`: 14 sources, eight addresses, zero second names
  and zero unjudged rows.
- `check_csv.py`: 86,783 functions, 17,253 symbols, 293 data rows accepted.

New authored C++ bytes are zero. The gain is a local legacy preview with
self-strict byte receipts, not a closed-strict or link.exe measurement. No
maintainer-only link cycle, census build, nightly or boot run was started.
Normal commit and push hooks remain required.

## Handoff

`Rva00562BF7SelectModelName.cpp` is another 484-byte sole-blocker lead, but
contains a local inline StringBase specialization; a direct call change needs
separate compiler-shape investigation. No attempt or claim was made here.
`Vp6StreamAudio.cpp` is outside the bounded preparation tool's safe decoder
scope and was not touched. The selected wrapper remains for other consumers.
Broader closure/actual-link evidence and the foreign-claimed BFME 1 update
remain pending. Previously recorded WinMain SRCCOPY false reject and missing
vtable providers were not retried.
