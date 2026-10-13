# Tree bound scaling dependency repair

Source base: a8f53504e0. The supplied index measures cb660e4d97 at
2026-10-13 04:02 UTC; object-proof.json records its SHA256. Committed
link_status.csv (67e1365aa9, 16:47) was used for queue discovery only.
No census, status/history, full link cycle or data-back artifact was changed.

W3DTreeBufferAddTree.cpp previously had one remaining local link finding:
its Vector3 scalar multiply-assignment COMDAT differs from the first copy
in link order. That name has no retail address in the supplied index.
The operator is already inlined in the complete matched 1284-byte tree
body; its out-of-line copy is unnecessary. Spell its three component
multiplications in a static inline helper and call that helper at the
original site. The scalar remains evaluated once, with the original
X/Y/Z operation and store order. No new type, pin, alias, compiler flag,
header, ledger row or source escape hatch is introduced.

The algorithm and arithmetic come from the pre-existing donor and its
resolved vector3.h at the verified BFME1 checkout cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The compiler receipt names the actual header under
game/Libraries/Source/WWVegas/WWMath/vector3.h; its operator defines the
same X/Y/Z expressions as the resolved Zero Hour reference.
Target verification establishes this consumer's entire retail body; it
does not establish a new target identity for the unrowed operator.
Reviewed BFME1 d3f9000fe08615a100e844adfff57fa4a39cd615 and its verification
account: removing an unnecessary incidental emitter is applicable, while
its TileData class and layout are unrelated and were not copied. The
previous broader donor review was reused. Official master fetched at
49e35f6636748b0e1116265ce543de2f7aca0d39, unchanged from the preceding seat.
The verified pointer and old freshness stamp remain unchanged. The overdue
old/new full-gate comparison remains incomplete after the prior documented
build-lock/5337-stale-TU preparation; no successful freshness update is claimed.

Acceptance:

- Bounded link_check.py --prepare-current before and after: 1/1 complete
  row, two literals and three compiler float constants; no skips or baseline.
  The final object has a strict reusable current receipt.
- ./build.sh on the complete unit: 1/1 exact, including the existing retail
  calls, bounds multiplication, literals and body extent.
- Saved-before/current-after object proof removes only the unused operator.
  All 13 remaining COMDAT raw bodies, extents and normalized relocation
  digests are unchanged. No COMDAT is added. Ordinary sections, including
  directives, are unchanged. The removed operator is not externally called
  by the current object. Escape-hatch counts are unchanged.
- Same-index saved-object legacy check: one COMDAT finding becomes zero;
  no finding added. Current ordinary link_check also reports LINKS.
  Local LINKED goes 0 -> 1281 existing authored bytes (three 0xCC bytes
  excluded from the 1284-byte row). No new authored coverage is claimed.
- Declared-definition, class, new-variants, CSV, whitespace, converged-data
  (eight addresses, zero second names or unjudged rows), ordinary shadow
  data (zero findings) and EH (zero applicable rows) checks pass.

This is self-strict byte/object evidence plus a legacy local link preview,
not closed-strict closure, a measured census gain or actual link.exe placement.
No maintainer-only verification runner was started. The first direct-local
expansion changed address calculation order and failed the byte gate; the
static helper preserves native evaluation shape. That trial remains only
in ignored build/tree-scale-link-20261013, with the original preparation
backup and proof script.

The same-index cause sweep also names frustum.cpp, tcbspline.cpp,
W3DBridgeGetModelVerticesFixed.cpp and W3DShrubBufferRva000E8365.cpp.
Their different compiler contexts and remaining dependencies require their
own complete-byte/object checks; no global operator/provider reconciliation
or gain for those peers is claimed. They were not edited or recorded as
blocked. Unrelated untracked dumps and ZH preparation were preserved.
