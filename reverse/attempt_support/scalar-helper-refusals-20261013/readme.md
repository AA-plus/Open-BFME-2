# Scoped scalar-helper link refusals

Index measurement cb660e4d97, 2026-10-13 04:02 UTC; BFME2 base6e6ad620f2.
Following the independently verified tree/shrub scalar-helper repairs, tested
these two consumers under their unchanged flags. No same-cause fix established.

- tcbspline.cpp: void and reference-return component helpers both remove the
  surplus 51-byte Vector3 multiply-assignment COMDAT and pass all four matched
  rows. Both also reschedule unrowed Update_Tangents (1675 bytes): changed scalar
  load/store schedule and literal relocation 1471 -> 1470. Complete object
  invariance is therefore not established; no source change or gain accepted.
- W3DBridgeGetModelVerticesFixed.cpp: both helper forms change the existing
  573-byte getModelVerticesFixed and 1038-byte getIndicesNVertices. Bounded
  byte gates reject 2/2 rows. No more trial shapes or header workaround attempted.

Both original sources were restored from their saved preparation copies.
The restored combined ordinary byte gate passes 6/6 rows; 13 float literals
and one import verify with zero skips/baselines. Current local preview retains
all original findings and LINKED0 -> 0 bytes. Both file claims were released.
Blocked records are in re_attempts.log. Full source/object snapshots and trial
logs remain in build/tcb-scale-link-20261013 and build/bridge-scale-link-20261013.
These refusals are scoped to this helper technique; they do not exhaust linking
work or refute the files' existing matched bodies. No nonmatching Code retained.
