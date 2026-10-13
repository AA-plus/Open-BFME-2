# LivingWorld destructor cleanups

The existing neutral `Rva002B964F` destructor at 0x002B964F matches all 606
native bytes and its complete associative exception graph. The existing source
documents the LivingWorldLogic role and partial member/base views. The graph
independently places these four previously unclaimed compiler-emitted bodies:

| RVA | Whole extent | Native member offset | Existing teardown |
| --- | ---: | --- | --- |
| 0x00776603 | 14 | +0xF0 | UnicodeString list |
| 0x0077663B | 14 | +0x130 | Neutral map view `Rva002B54F9` |
| 0x00776649 | 14 | +0x13C | Neutral multimap view `Rva002B5522` |
| 0x00776665 | 14 | +0x154 | Message vector with opaque pointer-element view |

Each complete body loads the destroying object from `[ebp-0x10]`, adjusts to
its own member, and tail-jumps to the existing teardown. Replay checks every
byte and relocation, the whole 606-byte real parent, and its full exception
graph. Ghidra supplies an independent 14-byte extent for each body. Local
labels locate compiler output and do not introduce callable aliases.

The four bodies add 56 unique C++ exact bytes and are committed separately.
No source reconstruction, synthetic parent, assembly or new pin is used. Member
roles and offsets are retained from the already verified source; this adds no
original class identity, full layout or linker claim.

```
./build.sh Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicDtorRva002B964F.cpp
python3 reverse/attempt_support/living-world-dtor-cleanups-20261013/verify.py
```
