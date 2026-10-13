# Direct material-vector vtable references

BFME2 base: a17fb6762aad29f68bbe0c143742caa0ac188a5e.
Available legacy census index: d753dedd98, 2026-10-12 22:16, as saved in
index-meta.json. The committed link-status measurement is different and is
used only for queue discovery. No census/status/history or per-row data-back
artifact is changed or manufactured.

Four consumers now name their existing DynamicVectorClass vtable providers
with __identifier instead of address-named extern arrays and linker aliases:
MaterialInfoClassCtor.cpp (two), MaterialCollectorClassCtor.cpp (three),
MaterialInfoCopyCtor.cpp (two), and MeshLoadContextCtor.cpp (one). The eight
corresponding hatch-baseline entries are deleted. Their common provider is
MaterialCollectorDestructor.cpp, which emits all three real decorated names.
That provider is foreign-claimed and stays unchanged; its existing strict
current object is a read-only witness. See sources.txt and witnesses.txt.

Target identities are existing evidence, not new guesses: vertex-material
DynamicVectorClass vtable BD4658 is independently documented in
reverse/identity_evidence/vertex-material-vector-constructor.md; the texture
handle table BD4688 is established by the matched collector constructor,
the 16FE00 constructor and the Resize vtable dispatch documented in the
ledger. Collector constructor target accesses likewise establish the shader
table BD46A0. No class layouts, donor bodies, pins, row extents or compiler
settings change. object-symbols-before/after.json records the provider's
three actual definitions and the four consumers' direct references.

Donor review uses the existing dedicated linking sweep and BFME1 repair
ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd (direct vtable naming in MaterialInfo).
Its direct-name technique is applicable; donor addresses and class layouts
are not transferred. Official master was fetched at
88c40fcc0; the verified clean checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The overdue pointer update and its
comparative full verification are held by file:reference/open-bfme-1 owner
codex-a44d-root. The success timestamp is not advanced and updated donor
headers are not substituted. The unchanged broader donor sweep is reused.

Acceptance:

- Strict preparation before: 47/47 rows in five candidate units. After the
  blocked unit was restored: 46/46 rows in the four changed consumers, all
  with strict reusable self-verification receipts and zero skipped literal
  checks. The provider's receipt is also strict-current, before and after.
- Standalone ./build.sh on the four full units passes 46/46, 2786 ledger bytes.
  relocation-proof.json compares every body byte and every relocation:
  bytes are unchanged, and the only relocation changes are the eight aliases
  replaced with their previously declared target names in four constructors.
- Legacy local link_check.py previews the same six objects before/after.
  LINKED remains 0 -> 0; the nonretail/duplicate/selected dependencies listed
  in link-after.txt remain. The provider object hash is unchanged.
- The ledger, undeclared-definition and staged hatch checks pass. The hatch
  improvement is eight alternatename occurrences removed, with no additions.

These are self-strict compiler/byte receipts and a legacy local link preview,
not closed-strict closure or an executable placement measurement. Authored
C++ bytes and locally linked bytes grow by zero. The verified improvement
is removal of eight linkage escape hatches. Broader maintainer-only linking,
nightly and boot operations were not run.

One independent candidate was restored and released: direct declaration of
DynamicVectorBfmeHandleCtor.cpp's own template vtable produces MSVC C2373,
both for const-pointer and donor nonconst-pointer array declarations. The
trial diagnostics are retained in trial-type-error*.txt and the blocked
verdict is recorded with re_log. Its original alias/baseline remain. The
restored normal gate passes 1/1 (46B), and its object hash is unchanged.
Its strict receipt was invalidated by the failed trials, so that restored
object is not claimed as strict-current. Further repair needs reconciled
compiler vtable emission, rather than another declaration spelling.
