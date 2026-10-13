# Army constructor cleanups

The real constructors at 0x0031A257 (283 bytes) and 0x0031A372
(543 bytes) match their whole native bodies and complete associative exception
graphs. Those graphs independently locate these six previously unclaimed
compiler-generated bodies, each also bounded by the Ghidra inventory:

| RVA | Extent | Parent | Cleanup |
| --- | ---: | --- | --- |
| 0x0077AA4A | 11 | Default constructor | Record vector at +0x7C, this at EBP-0x14 |
| 0x0077AA55 | 14 | Default constructor | Audio member at +0x90, this at EBP-0x14 |
| 0x0077AA63 | 10 | Default constructor | Failed new-expression block at EBP-0x18 |
| 0x0077AAE2 | 11 | Argument constructor | Record vector at +0x7C, this at EBP-0x10 |
| 0x0077AAED | 14 | Argument constructor | Audio member at +0x90, this at EBP-0x10 |
| 0x0077AAFB | 10 | Argument constructor | Failed new-expression block at EBP+0x0C |

The normal object emits all 70 bytes and the correct existing destructor or
operator-delete relocation for every body. The failure cleanups include their
stack adjustment and final return. The saved-allocation frame slots differ
between constructors and are proved separately, not inferred from adjacency.

Each body is banked in its own commit. The local `$L` names are object locators
whose native identity comes from their real parent and exception graph. No
synthetic parent, assembly, new pin or callable alias is introduced. The existing
army roles and measured member offsets are retained. The original isolated
receiver was neutral; upstream commit 2f6344cc5e replaced it with the canonical
LivingWorldArmy owner using independent WorldBuilder constructor/destructor
witnesses and reconciled base lifetimes. After rebase, these six rows were
reverified and rehomed to that exact owner. Record payload and audio member
types remain unproven. This cleanup addition claims no new type identity or
link-census progress beyond the upstream evidence.

The original isolated source's normal identity check reported three divergent vector/base
specializations and six duplicate existing definitions: KillSummaryEntry,
TakeUnitFromArmy_Internal, UseArmySummary, XferOwningLivingWorldArmyVec,
rva00319EA3 and rva00319EF9. Upstream's canonical owner replaces that deleted
source; its own remaining findings must be reported independently. The old
private source is not restored, and no verification rule is weakened.
Full native parent/cleanup and exception-data matches are not proof that
the whole unit links correctly.

Replay after the normal whole-file build:

```
./build.sh Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldArmy.cpp
python3 reverse/attempt_support/army-constructor-cleanups-20261013/verify.py
python3 reverse/attempt_support/army-constructor-cleanups-20261013/verify.py --rva 0x0077AA63
```
