# Shrub vertex scaling link repair

Source base: 9d1f0577de. The supplied index measures cb660e4d97 at
2026-10-13 04:02 UTC; object-proof.json records its SHA256. The committed
link_status.csv measurement at 67e1365aa9 served discovery only. No index,
census status/history or data-back artifact was changed or manufactured.

W3DShrubBufferRva000E8365.cpp emitted a surplus Vector3 scalar
multiply-assignment operator that differs from the first copy in link order.
That operator has no retail address in the index. Its arithmetic already
inlines into the complete matched vertex-buffer update. Use a static inline
helper for the same X/Y/Z multiplications, evaluating the scalar once and
preserving operation/store order. No shared header, compiler flag, type,
layout, pin, alias, global, marker or ledger change is needed.

The semantic lead is the existing clean BFME1
W3DShrubBufferRva0071D5E0.cpp donor and its resolved game/ WWMath/vector3.h
at cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The donor's operator spells
the same three component expressions. The existing BFME2 row and full byte
gate establish this consumer's target body, ABI and offsets; they do not
establish a target identity for the removed unrowed operator. The successful
tree-bound sibling repair prompted this same-cause follow-up.

Reviewed BFME1 d3f9000fe08615a100e844adfff57fa4a39cd615 and its verification
account. Suppressing unnecessary incidental definitions is applicable;
its TileData class/layout is unrelated and was not copied. The broader
unchanged donor linking review was reused. Official master was fetched at
49e35f6636748b0e1116265ce543de2f7aca0d39, unchanged from the preceding seat.
The verified checkout/gitlink and old freshness-success stamp were retained.
The overdue pointer update still lacks the comparative full byte gate after
the previously documented build-lock/5337-stale-TU preparation. This session
does not claim a successful freshness update or retry that unchanged blocker.

Acceptance:

- Before/after bounded strict-current preparation and ordinary build.sh:
  complete 753-byte row exact; zero skipped or baselined references. The
  final object has a strict reusable compiler receipt.
- Saved-before/current-after object proof removes exactly the 52-byte scalar
  operator COMDAT, adds none, and preserves all 18 remaining raw COMDAT
  bodies, extents and normalized relocation digests. Ordinary sections,
  including directives, are unchanged. The retained object does not call
  the removed operator. Escape-hatch counts are unchanged.
- Same-index saved-object legacy preview: eight findings become seven,
  exactly the removed operator finding; no new finding. The ordinary
  current-object preview agrees. Local LINKED remains 0 -> 0 bytes;
  the unit owns 752 real bytes after excluding one 0xCC from the 753-byte row.
- Declared-definition, class, new-variants admission, CSV and whitespace
  checks pass. Enforced converged-data check: eight addresses, zero second
  names or unjudged rows. Ordinary shadow data: zero findings. EH verifier:
  zero applicable row graphs. Placement resweep: zero new bodies or pins.

This is self-strict byte/object evidence and a legacy local link improvement.
No new authored coverage, closed-strict gain, measured census gain or actual
link.exe placement is claimed. No maintainer-only runner was started.

Seven independent findings remain: Vector3 copy/three-float constructors,
assignment and vector addition; Matrix3D and Vector4 indexing; compiler
vector-constructor iterator. Their existing bodies and relocations are
unchanged. A class/provider reconciliation needs separate evidence; this
repair does not claim it. Other same-cause peers (frustum, tcbspline and
bridge) require their own complete-byte checks and were not edited or
recorded as blocked. Full preparation snapshots and the proof script remain
in ignored build/shrub-scale-link-20261013. Unrelated untracked preparation
files were preserved.
