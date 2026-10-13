# Frustum incidental-copy link repair

Source base: a88dcefbd6. The supplied census index measures cb660e4d97
at 2026-10-13 04:02 UTC; object-proof.json records its unchanged SHA256.
Committed reverse/link_status.csv (67e1365aa9, 16:47) is queue discovery
only. No census, index, status/history or data-back artifact was changed.

frustum.cpp emitted two unused COMDAT copies which fail the local link
rules: Vector3::operator*=(float) differs from the first copy in link
order (no retail address), and Matrix3D::Get_Z_Vector() differs from the
kept retail-supported provider. Both operations are already inlined in
the donor FrustumClass::Init. Local static inline helpers retain the
donor's X/Y/Z multiplication expressions, reference return and matrix
column reads while avoiding these external definitions. No global
provider, class, header, compiler flag, ledger row, pin or hatch changes.

The compiler receipt identifies the actual vector3.h and matrix3d.h
under reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/
GeneralsMD/Code/Libraries/Source/WWVegas/WWMath. Their operator/getter
definitions supply the expressions used here. Target verification
establishes the four already rowed bodies; it does not establish an
identity or retail match for the unrowed FrustumClass::Init or the local
helpers. The Init COMDAT remains 1724 bytes with identical relocations.
Only +0x2d2..+0x3fc changes: scalar SSE operand selection and scheduling
for the normal-camera corner multiplications. Its source expressions,
branching, component order and operations remain the donor's. No new
recovery or byte-identity claim is made for that body.

BFME1 donor repair reviewed: d3f9000fe08615a100e844adfff57fa4a39cd615
(remove a redundant TileData constructor copy): applicable incidental
emitter removal mechanism; no TileData class or layout is imported.
Also reviewed d4ab8b980fe916fe70e137b2c2d2d04bceda8c9a (five WWVegas
array-allocation declarations): BFME1's scalar/array pin issue needs
separate BFME2 call evidence, inapplicable to these two operations.
Earlier broad donor review and tree-scale repair evidence were reused.

Official BFME1 master fetched at c338ecc7c0db0460045a4585256bb6c7746f2230.
The clean committed checkout remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The prior old/new full-gate freshness comparison remains incomplete after
the documented build-lock/5337-stale-TU preparation; see
../tree-scale-link-20261013/readme.md. The verified pointer is retained;
no successful freshness stamp or submodule update is claimed.

Acceptance:

- Bounded link_check.py --prepare-current before and after: four complete
  rows exact, no skipped/baselined literals, strict reusable self-verification
  receipts for the sole changed provider. ./build.sh also verifies 4/4.
- Saved-before/current-after object comparison: exactly the two unused
  external copies are removed; no COMDAT is added. Every remaining COMDAT
  except unrowed Init preserves raw bytes, extent and relocation digest.
  This includes all four matched bodies. Ordinary sections and linker
  directives are unchanged. Neither removed name is externally called by
  the final object. Escape-hatch counts are unchanged.
- Same-index, same-provider-replacement before/after local link check:
  two COMDAT findings become zero; no finding is added. The ordinary local
  link_check also reports LINKS. Legacy local LINKED: 0 -> 313 existing
  authored bytes. Self-strict byte receipts are distinct from link closure.
- Converged-data, ordinary shadow-data, EH, declared-definition, class,
  staged hatch, CSV and whitespace checks pass.

Cause sweep: tcbspline.cpp has the same scalar-copy finding but nine
undeclared definitions and seventeen other census blockers; it needs
separate whole-unit work. W3DBridgeGetModelVerticesFixed.cpp has 22 census
blockers, including an unrowed competing getModelVertices; removing a
single incidental copy does not resolve that dependency. The shrub unit
already uses a local scaleShrubVertex helper, so the old scalar-copy
census finding is not a reason to repeat that rewrite. These peer units
were inspected, not edited or claimed; no gain or blocked conversion
verdict is asserted for them.

Authored C++ coverage: +0. This is a local link repair with +313 legacy
preview bytes, not closed-strict closure, a measured census gain or an
actual link.exe placement. No maintainer-only runner was started.
Unrelated untracked assembly dumps and reverse/zh_sweep are preserved.
