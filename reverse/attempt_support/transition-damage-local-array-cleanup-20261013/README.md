# Transition-damage local coordinate array cleanup

Read the complete TransitionDamageFXParse.cpp, including all parse methods,
the local-effect position helper and its actual damage-state-change caller.
The source distinguishes BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d's
behavioral guide from target evidence: Ghidra extent, WB12472F0 callgraph,
source-path/line339, field accesses, callbacks and caller register convention.
The original point/location typedefs remain unknown. Rva004B9C4DPoint is an
already-rowed scoped lifetime adapter over canonical coordinate data; no new
original point identity or layout is asserted.

The full313B helper at0x004B9C4D and complete native associative EH graph are
EXACT. The graph owns Ghidra's22B cleanup0x0078F342, compiler label$L2132:

`68d03f4b006a206a0c8d8568feffff50e8b99de9ffc3`

It destroys32 local coordinates of stride12 at EBP-0x198, passing native
callback0x000B3FD0 to the existing96B CRT iterator0x00629110. Its parent is
proven by the whole native exception graph, resolving the historical
unknown-parent blocker without adjacency inference. The existing real C++
local array emits the cleanup naturally.

verify.py independently checks the full parent/graph, cleanup extent and both
relocations. It checks the three-byte adapter constructor and one-byte
adapter destructor against the existing Coord3D providers at their shared
retail addresses, including absence of EH data on both sides. These are
existing ledger fold-proof rows; no pin, alias or extra identity is added.
The full96B CRT iterator is also checked and retains prebuilt provenance,
not new C++ credit. Run normal builds of this source, coord3d.cpp and
??_M@YGXPAXIHP6EX0@Z@Z before replaying verify.py.

All12 owning rows pass normal verification, with15 literals, two empty-string
references and four named imports. Frozen-file inspection passes. The full
source graph inventory has two other cleanup bodies, already rowed at78F330
and78F379; the latter label is independently relocated by its parent's graph.
place_bodies returns zero new bodies/pins.

The before-row identity snapshot records an existing divergent
ParticleSystem::getSystemID definition. Source is unchanged; identity-after.json confirms the exact same finding
before and after adding the row. The normal shadow hook calls this one new
finding relative to its repository baseline; it was not introduced by this
change. No identity baseline was changed. The old local census6963cc017c
reports five unresolved names (bfmeUseFDE, ObjectCreationList::create,
createParticleSystem, destroyParticleSystemByID and rva004B9DA9), the
getSystemID COMDAT mismatch and a non-retail selected convertBonePosToWorldPos.
No clean linking gain is claimed. No source, headers, flags, markers,
globals, pins or aliases are changed.
