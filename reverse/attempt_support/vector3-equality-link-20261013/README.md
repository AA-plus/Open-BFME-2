# Vector3 equality emitter repair

Base: `feaa5b65708d4d90f1513bf995900ff7ed2ec41e`.
Local census index: measurement `cb660e4d97`, 2026-10-13 04:02 UTC.
The committed link status is older (`e956901d31`); it served leads only.
Neither the census index nor link status was rewritten. No link cycle ran.

## Supported change

The free `??8@YA_NABVVector3@@0@Z` equality helper has no ledger row or
symbol pin. Its census copies have two optimization shapes: 58 bytes in
`WWMath/vector3.cpp` and `W3DVolumetricShadowUpdate.cpp`, versus 60 bytes
in seven consumer units. The difference is the true return sequence and
branch displacements; the component comparisons agree. Both variants have
no relocations. Without a retail address the census uses the first copy,
which was the 58-byte address-taking scaffold. This is a first-copy
consistency repair, not a claim that either helper shape has retail identity.

Remove the `_eq` address-taking anchor from vector3.cpp and express the
shadow Update comparison directly, removing its private free helper. Update
already inlined that comparison. Its matched body remains byte-exact, as do
all other ledger bodies in the two edited units. No header, pin, ledger row,
compiler setting, or consumer source changed. The remaining 60-byte copies
agree; object-before.txt and object-after.txt record bytes and receipt state.

## Before/after acceptance

All eight paths in sources.txt were file-claimed before preparation.
`collect.cpp` also has a 60-byte census copy but belongs to another worker;
it was not prepared or edited, and no gain for it is claimed.

Commands, executed sequentially around the source change:

```
python3 tools/link_check.py --prepare-current --paths-from sources.txt
python3 tools/link_check.py --prepare-current --paths-from strict-sources.txt
python3 tools/link_check.py --paths-from sources.txt
./build.sh Code/Libraries/Source/WWVegas/WWMath/vector3.cpp Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdate.cpp
python3 tools/link_check.py --prepare-current --paths-from strict-sources.txt
python3 tools/link_check.py --paths-from sources.txt
./build.sh Code/Libraries/Source/WWVegas/WW3D2/meshmdl_sidehash.cpp
```

The first bounded preparation refused meshmdl_sidehash.cpp because its
include inventory cannot prove the search roots; prepare-before.txt records
the actual refusal. The check was not modified or bypassed. Seven other
explicit providers have strict reusable compiler receipts before and after
the edit, and their scoped byte gates pass 88/88 rows, with no baselined or
skipped literal checks. These are self-strict inputs, not a checked closure.

The two changed units separately pass 11/11 rows; the remaining consumer
passes the normal byte gate 19/19 rows but still lacks a reusable strict
receipt. That consumer's local link result is therefore a **legacy preview**.
The current-object preview against the same index changes from 0/8 clean,
0 bytes, to 1/8 clean, 2,408 bytes, all in meshmdl_sidehash.cpp. The equality
conflict disappears from the five other prepared consumers. No closed-strict
gain or real linker placement is asserted. Both cohort link commands return
1 because seven units still have other blockers; their complete reports are
retained. No regression appears in their remaining blocker lists.

Additional checks: check_csv passes; find_declared_unmatched passes for both
edited sources; converged data check passes for all eight paths (8 addresses,
zero second names or unjudged rows); git diff --check passes.

## Donor review and remaining work

The verified BFME1 input pointer remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Its clean vector3.h and shadow
Update provide the same component-comparison semantics. The compiler bytes
and emitter relationships above are BFME2 object evidence; donor names alone
do not establish a new target identity.

Reviewed upstream BFME1 linking repairs after fetching official master:
`d3f9000fe08615a100e844adfff57fa4a39cd615` (TileData constructor) and
`5093777e8373a843f1f1ccfc648601ae78351aaa` (ShareBuffer destructor) support
removing competing incidental emitters. That principle is applicable here;
their bodies were not imported. `84e866570d997a7fa9a0d1becc77f37b5f7bd05e`
(ExperienceUpdate override) is inapplicable to this equality blocker.

Fetched upstream is `e3d43d8be32ace711f352de5ea7767f1236957a8`. The submodule
has a live foreign scope claim, so the verified pointer and freshness stamp
were preserved; the comparative full byte-gated update remains outstanding.

Remaining cohort blockers include Vector3::Lerp selection, shadow
updateVolumes, RefCount/AABox/RenderObj variants, mesh material dependencies,
and the SideIndexInfo/HashTemplate variants. The strict include-inventory
barrier for meshmdl_sidehash is a separate tooling/dependency task. Broader
link verification requires the maintainer lane; no new authored C++ bytes
were claimed by this repair.
