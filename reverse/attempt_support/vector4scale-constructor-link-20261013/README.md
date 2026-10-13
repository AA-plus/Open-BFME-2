# Vector4ScaleO1 constructor emitter repair

Base: c9fcd1ea0a. Local census/index: cb660e4d97, 2026-10-13 04:02 UTC.
The committed link status measures 3906ea7b97; neither artifact was rewritten.

Use the existing bfme_vp_math/vector4.h scoped view instead of the donor's
unmodified vector4.h. Its inline-only four-float constructor keeps the donor
assignments without emitting an SSE COMDAT. The target constructor at
0x006D8A30 is the 32-byte integer-move body owned by matrix3d.cpp; the old
48-byte SSE copy (digest 18082c74ab69) is rejected by RetailTruth. Native
constructor bytes and whole emitted bodies/relocations are in the snapshots.
All other emitted bodies, including the matched scalar-first multiplication
at 0x00308182 (69 bytes, digest 0bd7f425f343), remain identical. No new identity,
layout, pin, header, compiler setting or ledger row is claimed.

The existing scoped header records BFME1 provenance at
9cbfb551fe20dae985f91f2319d8997287b6a705; the retained reference checkout is
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed donor repair
d3f9000fe08615a100e844adfff57fa4a39cd615 (TileData incidental constructor
emission). Its suppression principle applies; its body and layout were not
imported. Target bytes prove the operator preservation and rejected constructor
copy; the donor supplies the existing component arithmetic semantics.

## Acceptance

The file and 0x00308182 were claimed. Both original and final sources pass:

```
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WWMath/Vector4ScaleO1.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWMath/Vector4ScaleO1.cpp
```

Each bounded preparation verifies 1/1 matched rows with a strict reusable
receipt. The final source also passes ./build.sh, new-variants admission,
find_declared_unmatched, converged data checking (8 addresses, no second names
or unjudged rows), check_csv (87120 functions, 17269 symbols, 307 data rows),
and git diff --check. The receipt snapshots are self-strict evidence.

The legacy local link preview removes the constructor COMDAT blocker: two
blockers become one, with no added blocker. Both previews exit 1 because the
vector-first operator copy remains wrong. LINKED stays 0 -> 0 bytes; no real
link placement, closed-strict improvement or new authored C++ bytes is claimed.
No full link cycle, census measurement, nightly or boot runner was started.

## Handoff

The vector-first multiplication helper still needs its own supported codegen
reconciliation. Its body was not retried. Other Lerp emitters have foreign
claims. The reference-pointer update has a foreign submodule claim; fetching
official master found ff33c963a, but the verified pointer and freshness stamp
were retained. Its comparative full byte gate remains with that worker.

Other lane probes: repair_queue.py link and link_rank.py supplied current leads;
name_globals.py --dry-run kept zero replacements. rehome_rows.py --limit 12
cannot run without build/link_census/census.log; no census was rebuilt to work
around the missing runner artifact.
