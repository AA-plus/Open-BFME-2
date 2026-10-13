# Matrix copy dependency repair

BFME 2 starting HEAD: 23e6d41775. Same-index local previews use census
cb660e4d97, 2026-10-13 04:02. The newer committed link_status.csv measurement
67e1365aa9 was discovery evidence only. Index SHA256 and starting HEAD are
recorded in index.json; the index and census status were not changed.

Rva000B3649Fetch.cpp now includes the existing BFME matrix3d_copy_link.h.
ThingSetPosition.cpp includes the existing Zero Hour variant before PreRTS.h,
which otherwise loads the original matrix header. Receipt dependencies proved
that the latter consumer uses the Zero Hour matrix/vector declarations. Each
consumer keeps its existing donor family, class layouts, compiler settings,
method bodies, retail boundaries, identities and relocations.

The two consumers formerly emitted Matrix3D copy COMDATs and were charged with
the selected nonretail copy. The established shims inline the copy while
suppressing the surplus external bodies. This removes three COMDATs from the
fetch unit and two from Thing. All 25 retained COMDATs preserve raw bytes,
extents, digests and normalized relocation targets. Ordinary nondebug sections
also agree. Object hashes and complete provider bodies are in object-proof.json.
The retained Matrix3D owner at 0x6645C is FloatUpdate.cpp's exact 98-byte body;
the independent OBBox Transform owner at 0xB2A4C is exact for its entire 231 bytes.
These owners were checked with the consumers, without editing either provider.

Donor review: retained clean BFME 1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 and its game/ and inputs/reference/
matrix/vector headers. BFME 1 repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d
supports suppressing surplus inline constructor definitions; its aliases and
pins are not imported. BFME 2 repairs 3cd8394af7eb and c58056e165 supply the
existing shim pattern. Target identities and layouts remain the previously
verified source/ledger evidence; equal bytes make no further donor identity
claim. Newly fetched BFME 1 master was 4b5d71a18c76439243dc5c641bdcc7890177c863;
its WWMath directory has no changes from the retained pointer. The freshness
update remains outstanding: the previous baseline full gate required 5882 stale
TUs and was interrupted at the shared compiler lock
(build/seat-current-baseline-full.log). No pointer or success stamp was advanced;
the old/new full verification still needs completion.

Acceptance:

- Before: fetch/provider strict cohort 5/5 exact; Thing strict gate 1/1 exact.
- After: four explicit consumer/provider self-strict receipts, normal cohort
  byte gate 6/6 exact, no skipped/baselined string, float or import references.
- Each consumer's local legacy findings fall from two to one. Fetch retains
  selected OBBoxClass::Transform; Thing retains its Set_Y_Translation COMDAT
  loser. Provider findings remain independent and unchanged, as listed in
  cohort-link-after.txt. Linked bytes stay zero. Self-strict currency does not
  establish closed-strict closure; no closed-strict, census or actual-link gain
  is claimed. New authored C++ bytes: zero.
- Declared-definition and canonical-class checks pass. Enforced converged-data
  check: eight addresses, zero second names or unjudged rows. Shadow data check:
  zero findings. EH check: no EH-bearing rows, no missing objects. CSV and diff
  checks pass. Placement resweep: zero bodies, zero pins.

Adjacent AnimatableGetBoneTransform.cpp was tested once using the same supported
cause. Both the shim alone and preloading Vector4 before its existing optimization
anchor alter the native 133-byte by-name and 537-byte by-index bodies, adding
vector constructor iterator calls and changing SSE scheduling. Both gates reject
2/3 rows. Original source restored and verified 3/3; verdict logged and all four
claims released. Trials and before object/source/dependency receipts remain in
build/bone-fetch-matrix-link-20261013. It must not be retried without new evidence.

Commands: link_check.py --prepare-current on the explicit cohorts above;
./build.sh on both consumers and the restored Animatable unit; link_check.py
on consumers/providers together; find_declared_unmatched.py, class_gate.py,
data_check.py (shadow and --converged), eh_verify.py, place_bodies.py and
check_csv.py. No full link cycle, census, nightly, boot or publisher runner ran.
