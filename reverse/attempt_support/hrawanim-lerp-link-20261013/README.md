# HRawAnim interpolation emitter repair

Base: `6ea7f9acebe0538067c71f6f46b747ac5a0e7b76`.
Local census index: measurement `d753dedd98`, 2026-10-12 22:20 UTC.
The committed link status measures a different revision (`3906ea7b97`);
it and the index supplied leads, not current placement proof. Neither was
rewritten. No census build, full link cycle or maintainer runner was started.

## Supported change

Replace the two calls to Vector3::Lerp in HRawAnimClass::Get_Translation and
Get_Transform with its three component expressions, in their original order.
These callers already inline the interpolation. Naming the helper also emits
an incidental 87-byte COMDAT (digest `5a1caec9078e`) which retail evidence
rejects. The ledger's Vector3::Lerp provider at 0x0009AA48 emits retail's
85-byte body (`d858ac913ecf`). After the change HRawAnim emits no Lerp copy;
the provider is unchanged. Object snapshots include full bodies, relocations
(none), and self-strict receipt state before and after.

The expressions and sequential component stores come from vector3.h at the
verified BFME1 donor pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Assertions are already disabled by this unit's /DNDEBUG setting. The existing
Get_Transform output at matrix offset 16 is preserved. Target byte verification
supports the resulting instructions and existing offset; donor source supplies
the interpolation semantics. No new identity or class-layout claim is made.
No header, compiler setting, symbol pin or ledger row changed.

## Acceptance and measured improvement

File claims cover hrawanim.cpp and vector3.cpp; the two edited retail callers
were also RVA-claimed. The sources were prepared and checked sequentially:

```
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
# source change
./build.sh Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WWMath/vector3.cpp
```

Both bounded preparations pass 37/37 rows and produce strict reusable receipts
for the same two explicit providers. The edited unit separately passes 27/27
rows (5,313 retail bytes), including both interpolation callers. Literal checks
have no baselined or skipped strings; 16 compiler float literals pass in the
edited unit. These are **self-strict** inputs, not a verified link closure.

The current-object **legacy preview**, against the same index, removes the
Lerp `comdat` and `selected` blockers from HRawAnim: 11 blockers become 9,
with no added blockers. Vector3's blocker list is unchanged. Both previews
return 1 because other blockers remain: 0/2 clean, LINKED 0 -> 0 bytes.
No closed-strict byte gain or real linker placement is claimed.

Additional acceptance: find_declared_unmatched passes for the edited unit;
check_csv passes (87,106 functions, 17,272 symbols, 302 data rows);
converged data check passes for both providers (8 addresses, zero second names
or unjudged rows); git diff --check passes.

## Donor review and handoff

Reviewed BFME1 repairs `d3f9000fe08615a100e844adfff57fa4a39cd615`
(TileData constructor emitter removal) and
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` (compare provider reconciliation).
The incidental-emitter removal principle is applicable; their concrete bodies
and layouts are unrelated and were not imported.

Official master was fetched at `d3c65531b`. Its pointer update is held by a live
foreign `file:reference/open-bfme-1` claim, so the clean verified donor checkout
and old freshness stamp were retained. The comparative full-byte update and
layout/dependency reconciliation remain with that worker.

The remaining census Lerp wrong emitter in decalmsh.cpp, and shattersystem.cpp,
are claimed by another worker. HRawAnim still has duplicated channel/free
providers, WeightInfoStruct's deleting-destructor conflict and selected motion
channel helpers. A fresh census may retire stale duplicate leads. Broader
link measurement remains a maintainer task. New authored C++ coverage is zero;
this commit records a verified competing-definition reduction.
