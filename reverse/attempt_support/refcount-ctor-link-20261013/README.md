# RefCountClass constructor provider repair, 2026-10-13

BFME 2 session base: `0c09e0beba`. Against the local census index measured at
`d753dedd98` (2026-10-12 22:16 UTC), the local preview prefers a consumer copy
of the constructor, but GapBodiesGE31 owns an exclusive definition. All 64 indexed constructor
COMDATs have the same masked digest, `9e55bcec2e7c`. The exclusive owner causes
an ownership-based `wrong_selected` result and a duplicate-definition blocker.
The committed link status names `d9e9abdc70`; it supplied queue leads only.
No per-row data-back artifact was used or census measurement rewritten.

## Change and target evidence

Make the existing 16-byte constructor inline, keeping it interchangeable with
the consumers' COMDATs. Reconcile the existing private class view with donor
refcount.h and the checked consumers: virtual Delete_This first, then the
protected virtual destructor. Declare Delete_This without emitting another
helper. No canonical header is registered or new private class copy added.

Retail independently establishes count-at-4 initialized to one and the base
and derived vtable stores in the two complete 16-byte constructors. Its vtables
at RVAs `0x007C650C` and `0x007C6514` have Delete_This at slot zero and deleting
destruction at slot one. The original derived class name remains unknown.
`object-proof.txt` checks both constructors, the shared seven-byte destructor
and 29-byte base deleting destructor, including native relocation operands.
It records the compiler's existing weak deleting-destructor defaults; no
linker alias directive or symbol pin was added.

A direct donor-header trial preserved the ledger bodies but emitted a
12-byte Delete_This helper where the native slot names a 20-byte body. Reject
that trial. The final declaration follows the existing consumer policy and
emits no Delete_This definition. The source keeps its original compiler flags.

## Donor review and freshness

Reviewed clean verified BFME 1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`,
including `game/Libraries/Source/WWVegas/WWLib/refcount.h`. Donor class names,
access control and inline semantics are source evidence; native field stores
and virtual-slot ordering are separate target evidence.

Reviewed donor repairs `d3f9000fe08615a100e844adfff57fa4a39cd615` (avoid a
competing TileData constructor) and `5093777e8373a843f1f1ccfc648601ae78351aaa`
(reconcile a shared-buffer destructor provider). Their provider/declaration
principle applies; their concrete bodies and emission anchors were not imported.
The texture release repair `22b25355a906b00da0786d115f4b68c4b2913877` concerns
different dependencies and was not applied.

Official BFME 1 fetch reached `8a91b417cc7cf1bebda0700bf882f7c25dfb5b76`.
Worker `codex-a44d-root` holds `file:reference/open-bfme-1`. Preserve the clean
verified pointer; no pointer update or freshness success stamp was made.
The comparative full verification remains outstanding with that worker.

## Acceptance and remaining work

- Ordinary changed-unit byte gate: **26/26** matched rows, four float literals.
- Bounded `link_check.py --prepare-current --paths-from sources.txt` before
  and after: **45/45** rows across eight explicitly checked sources, six float
  literals, zero skipped/baselined string or import references, current
  self-strict receipts. No closed-strict closure was established.
- Ordinary local link preview: **0/8 -> 7/8** clean units;
  **0 -> 1,534 existing authored bytes**. This is a legacy census preview,
  not a new census or an actual link.exe result. Before/after transcripts list
  each consumer and its bytes. No wider gain from the 64 indexed copies is
  counted without refreshed consumer evidence.
- GapBodiesGE31 loses its constructor duplicate, selected-definition and
  vtable COMDAT blockers, but still has six unresolved globals; they are listed
  in `after-link.txt`. The mixed-scope preview therefore exits 1 as expected.
- Converged-data check: eight sources, eight addresses, zero second names or
  unjudged rows. Declared-definition check, ledger check and diff check pass.

New authored C++ bytes: **0**. No full link cycle, census build/history, nightly,
boot operation, gate modification, baseline edit or escape hatch was used.
