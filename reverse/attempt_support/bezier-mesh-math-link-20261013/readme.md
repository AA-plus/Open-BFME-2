# Bezier and mesh-builder math-emitter repair

Base: 88123f9ddcfdf26bdc4312185517614f69bf5b95. The available local
census index measures d753dedd98, 2026-10-12 22:16. Committed
link_status.csv measures 2a20912cc9, 2026-10-13 08:08 and was used only
for discovery. Neither artifact was rewritten; no data-back ranking was used.

Both file-scope claims were acquired before editing. Include MSVC's original
math.h with scoped static-inline linkage before other headers, using the
existing verified geometry/float repair. BezierSegment removes sqrt(float)
and sqrtf; MeshBuilder removes fabs(float) and fabsf. The original arithmetic,
flags, class views, source provenance and existing identity uncertainty remain.
No layout or new identity is inferred from these bytes. No new provider,
pin, alias, global, marker, hatch or ledger row is introduced.

object-proof.json records source/object hashes and the complete four removed
copies. All 140 retained COMDATs (23 Bezier, 117 MeshBuilder) retain identical
whole bodies, sizes, relocations, digests and retail verdicts. There are no
added or changed copies. Strong definitions, undefined externals and weak
bindings are unchanged. Full before/after facts and source/object backups
remain in build/bezier-mesh-math-link-20261013.

Acceptance before and after: bounded --prepare-current over the two explicit
sources passes all three rows and establishes two strict reusable self receipts.
The final ordinary ./build.sh also passes 3/3 (223 retail bytes), with zero
skipped/baselined string references. New-variants admission, class gate,
declared-definition check, check_csv and whitespace checks pass. Enforced
converged-data checking finds zero second names or unjudged rows at eight
addresses. No shared header was edited.

The current-object local link check refreshes both touched definitions in
memory against the same index. Bezier findings fall 12 -> 10; MeshBuilder
7 -> 5. Exactly the four removed emitters disappear from the findings, with
no additions. The preview exits 1 because unrelated blockers remain; 0/2
units link and LINKED stays 0 -> 0. This is verified repair with +0 authored
C++ bytes. Self-strict is established; no closed-strict closure, actual linker
placement or measured census gain is claimed. No full census, link cycle,
nightly or boot runner was started.

Remaining Bezier blockers are the five BezFwdIterator members, Coord3D
length/scale, vector indexing/clear copies and selected vector resize.
MeshBuilder retains five Vector2/Vector3 comparison and normalization copies.
Those need separate provider or class evidence; their unresolved dependencies
were not retried. LivingWorldEyeTowerAim was probed read-only and retains its
atan2f, Matrix3 and rotation-helper conflicts; no change was attempted there.

Donor review: retained clean BFME1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its corresponding Bezier and
MeshBuilder units were reviewed for arithmetic/source provenance. Linking
repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d and its verification
account support suppressing unnecessary emitter copies; its string constructor
and alias scaffold are inapplicable and were not imported. The broader donor
scan already recorded by the preceding geometry/float repairs is unchanged
and was reused rather than repeated.

Official BFME1 master was fetched at 7fbed69e4. The overdue pointer update
remains under codex-a44d-root's live file:reference/open-bfme-1 claim. The
clean verified inputs and old success stamp were preserved. Comparative full
verification and pointer publication remain with that owner; freshness was
not marked successful. Existing unrelated untracked dumps/sweep files remain.
