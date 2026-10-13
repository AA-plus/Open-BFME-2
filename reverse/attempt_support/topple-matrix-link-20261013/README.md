# Topple Matrix3D copy link repair

Base checkout: 772dc3f042. Local census: cb660e4d97, 2026-10-13 04:02;
index SHA256 is recorded in index.json. The committed link_status measurement
67e1365aa9 is newer; it is discovery evidence, not this preview's baseline.

ToppleUpdate.cpp and StructureToppleUpdateCrushing.cpp now include the existing
BFME-specific matrix3d_copy_link.h instead of the donor's matrix3d.h. No header,
flags, layout, method body, ledger name or pin changes. This applies the supported
cause already repaired by BFME 2 commit 3cd8394af7eb6233a25bcf764ef8f5bbb8f6436d.

Donor reviewed: clean verified BFME 1 pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Its game/ matrix header supplies the existing Row copy semantics. The selected
shim preserves those declarations and forces the copy inline, suppressing three
surplus COMDATs per consumer. The ZH variant was not used because its Matrix3 and
Matrix4 declarations differ. BFME 1 repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d
supports removing surplus inline constructor COMDATs; its specific aliases and
pins were not imported. Target ABI, extents and identities remain those of the
existing byte-verified BFME 2 rows, rather than new donor-derived claims.

Acceptance:

- Before strict gates: Topple plus FloatUpdate 6/6; Structure 13/13.
- After ./build.sh on both consumers and FloatUpdate: 19/19, all string, float
  and import references verified; EH graphs 3/3 EXACT with no baselines.
- Frozen-definition and class gates passed for both edited sources.
- Converged-data check: eight addresses, zero second names or unjudged rows.
- Current receipts proven for both consumers and the read-only FloatUpdate
  provider. All 84 retained COMDATs preserve raw bytes, extents and normalized
  relocation targets. Nondebug ordinary sections match; .sxdata symbol-table
  indices are compared as handler names because removed symbols renumber them.
- Only Matrix3D copy construction, Vector4 default construction and Vector4
  assignment COMDATs disappear, once per consumer; no COMDATs are added.
- FloatUpdate's existing 98-byte Matrix3D copy body matches the whole masked
  retail extent at 0x6645c; its two relocation destinations are recorded.
- Same-index local legacy preview improves both consumers from blocked to clean:
  2,318 + 3,586 = 5,904 existing bytes. FloatUpdate retains independent unresolved,
  duplicate and selected-definition findings. No closed-strict, full-link or
  fresh census gain is claimed. New authored C++ bytes: zero.

Commands: bounded link_check.py --prepare-current for these three sources,
./build.sh on the three sources, link_check.py on the three sources,
eh_verify.py on both consumers, data_check.py --converged on both consumers,
find_declared_unmatched.py and class_gate.py on both consumers. No full census,
link cycle, nightly or boot runner was started.

BFME 1 upstream was fetched at b14299726; advancing the verified pointer still
requires the full comparative freshness verification. No success stamp or pointer
update was made in this repair.
