# TacticalBattleResolver allocation cleanups

The existing real Impl constructor at 0x005D1175 matches all 155 native
bytes; the outer constructor at 0x005D1296 matches all 77 bytes. Each
complete associative exception graph matches native data and independently
places a previously unclaimed failed-new-expression cleanup:

| RVA | Whole extent | Parent | Saved allocation pointer |
| --- | ---: | --- | --- |
| 0x007A1D27 | 10 | TacticalBattleResolver::Impl constructor | EBP+0x08 |
| 0x007A1D58 | 10 | Neutral outer Rva005D12E3 constructor | EBP-0x14 |

Each pushes its own saved block pointer, calls the existing operator delete
at 0x0002FD60, pops the argument and returns. Replay verifies all ten bytes,
the named delete relocation, both whole real parents and their complete
native exception graphs. Ghidra independently supplies both ten-byte extents.
Parent relationships come from the native graph, not address adjacency.

The compiler reuses the Impl constructor's incoming argument slot for its
allocation pointer; the outer constructor uses a separate local slot. These
are independent target observations, not an inferred common frame layout.

Both bodies are emitted by existing real C++ new-expressions and add 20
unique C++ exact bytes. They are committed separately. No synthetic parent,
assembly, new pin or callable alias is introduced. Existing WorldBuilder
witnesses identify the family and Impl constructor; exact names of the neutral
state/outer receiver views and unknown fields retain their source-documented
uncertainty. This adds no new type identity or link-census claim.

```
./build.sh Code/GameEngine/Source/GameClient/LivingWorld/InGameUI/StrategicInGameUITacticalBattleResolverStateForward.cpp
python3 reverse/attempt_support/tactical-resolver-allocation-cleanups-20261013/verify.py
```
