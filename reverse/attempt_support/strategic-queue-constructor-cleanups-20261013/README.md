# Strategic HUD build-queue constructor cleanups

The real constructor at 0x005F7F21 matches all 1,001 bytes and its full
18-state associative exception graph. The existing source preserves its neutral
receiver/five borrowed argument spelling while recording the WorldBuilder
`StrategicHUD::BuildQueueDetailsMovieClip::Impl` relationship. That exact graph
independently places these previously unclaimed compiler-emitted cleanups:

| RVA | Whole extent | Cleanup |
| --- | ---: | --- |
| 0x007A58D7 | 11 | Image-name list at +0x20 |
| 0x007A58E2 | 11 | Custom-render list at +0x2C |
| 0x007A58ED | 10 | Failed allocation saved at EBP+0x0C, including pop/return |
| 0x007A5902 | 22 | Destructor iterator over seven four-byte queued slots at +0x3C |

Every body and existing teardown relocation matches the normally built object.
The array callback and iterator relocations are both verified, separately from
the constructor's already rowed default-argument closure. Ghidra independently
provides each complete extent. No parent is inferred from adjacency.

These 54 new unique C++ bytes are banked in separate commits. No synthetic
parent, assembly, new pin or callable alias is introduced. The source already
emits all four bodies; its original generic pointer-slot type and callback
argument identities remain unresolved. This establishes no new layout or
link-census result.

```
./build.sh Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/StrategicHUDBuildQueueDetailsImplCtor.cpp
python3 reverse/attempt_support/strategic-queue-constructor-cleanups-20261013/verify.py
```
