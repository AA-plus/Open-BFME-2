# Grid mapper RefCountClass link repair

Source base: BFME 2 `6ea7f9acebe0538067c71f6f46b747ac5a0e7b76`.
Local census/index: `cb660e4d97`, measured `2026-10-13 04:02`.
The committed link-status CSV predates that index and was not used to claim a
new measurement. No census, full link cycle, or status publication was run.

## Supported correction

`GridTextureMapperClassCopyCtor.cpp` used a public, declaration-only base
destructor and an implicit default constructor that only installed a vptr.
Its TextureMapper copy constructor set the reference count itself. This emitted
a wrong RefCount constructor, a wrong TextureMapper copy constructor, a
one-slot base vtable, and a reference to an undefined public destructor.

Use the established base view from `GapBodiesGE31.cpp`: inline construction
with one reference, virtual Delete_This first, and the inline protected virtual
destructor second. Leave Delete_This declaration-only, supplied by existing
providers. The derived copy constructor now initializes Stage; the base owns
NumRefs. No flags, pins, aliases, markers, shared headers, or ledger claims were
added. Existing mapper copy/Reset source behavior and both row extents remain.

Target facts: owned constructor `0x00072882` is 16 bytes and initializes NumRefs
at +4 to one. The owned protected destructor at `0x00072892` is seven bytes.
Both install the RefCount vtable at VA `0x00BC650C`, with Delete_This at slot zero
and scalar deletion at slot one. `native-facts.json` contains the retail bytes
and this unit's emitted bytes/relocations. These target facts support the base
layout; donor names alone do not establish it.

Donor lead: retained BFME 1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`,
`game/Libraries/Source/WWVegas/WWLib/refcount.h`, and BFME 2's prior verified
`reverse/attempt_support/refcount-ctor-link-20261013` repair. The constructor,
virtual order, and protected destructor semantics are inherited; the target
bytes and existing providers establish applicability. This unit's constructor,
destructor, base vtable, and TextureMapper copy constructor COMDAT digests now
agree with mapper.cpp/hlod.cpp or the owned GapBodies constructor.
The standalone retail-truth preview reports these code bodies as unknown where
vtable relocation identity is not pinned; the normal byte gates and native
evidence are recorded separately rather than upgrading that verdict.

## Acceptance and limits

- `./build.sh Code/Libraries/Source/WWVegas/WW3D2/GridTextureMapperClassCopyCtor.cpp`:
  **2/2 rows exact**, preserving 127-byte copy construction and 51-byte Reset.
- `find_declared_unmatched.py` passes; the existing nonretail anchor marker
  remains unchanged. `check_csv.py` and `git diff --check` pass.
- `link_check.py --prepare-current` on this unit, GapBodiesGE31, mapper.cpp and
  hlod.cpp: **254/254 rows exact**, four strict reusable provider receipts;
  all string, float and import reference checks pass. This is scoped
  self-strict byte evidence, not closed-strict link evidence.
- `link_check.py --new-variants` on the changed unit: exit **0**. The emitted
  31-byte protected deleting destructor is mapper.cpp's existing variant,
  not a new COMDAT body.
- Controlled legacy local link previews on this unit plus GapBodiesGE31:
  Grid blockers **7 -> 4**; three removed net. The incorrect base constructor,
  base vtable, TextureMapper constructor and unresolved public destructor
  disappear; the existing protected deleting-destructor variant is now exposed.
  GapBodiesGE31 retains its same six unrelated globals. **0/2 -> 0/2 clean**
  and **0 -> 0 LINKED bytes**. Four-provider after-preview likewise remains
  0/4; no closed-strict gain or complete linkability is claimed.

Grid still loses on the two incomplete mapper vtables, the selected wrong Grid
copy constructor, and the established /O2 protected deleting-destructor variant
versus the first /O1 copy. mapper.cpp additionally needs Apply/texture-matrix
providers and other existing repairs; hlod.cpp's blockers are listed in the
provider preview. Resolving these requires separate supported class/provider
work; this correction does not change their bodies.

## Reference freshness and reviewed leads

Fetched official BFME 1 master `88c40fcc06f9823feb8b60f2abe446a0b2836439`.
Reviewed donor linking repairs for Anim2DCollectionTemplates (`5fa9bfd66`),
RenderObjClassCtor_Thunk (`8bee328d6`), W3DSnow/WaterTracks (`22b25355a`),
ExperienceUpdate (`84e866570`), Miles (`0a3a4f605`) and dx8renderer
(`713150f41`). Canonical-provider/declaration repairs are relevant principles;
the exact units are inherited, absent here, or need different BFME 2 evidence.
The RefCount sibling repair directly supports the correction above.

The due retained-pointer full baseline required 5,337 stale TUs (16,974 cached)
and waited over six minutes on the host-wide compiler lock without compiling.
Stopped that owned attempt with SIGINT, exit 130. Another worker holds the
reference submodule file claim. Kept the verified pointer and success stamp
unchanged; no old/new full-gate comparison or pointer-update success is claimed.
The local baseline log and freshness handoff remain under ignored build/.
