# LivingWorld constructor member cleanups

The existing real 355-byte constructor at 0x00213EEF builds the subsystem
assigned to `TheLivingWorldManager`. Its neutral receiver spelling remains
`Rva0022B12DSubsystem`; no original constructor name or complete member type is
inferred. The whole source and complete associative exception graph match
retail, independently locating these five previously unclaimed bodies:

| RVA | Whole extent | Native member offset | Existing teardown spelling |
| --- | ---: | --- | --- |
| 0x0076DE7C | 14 | +0x204 | `Rva002130CA` |
| 0x0076DE8A | 14 | +0x218 | `Rva00212379` |
| 0x0076DEFA | 14 | +0x294 | `Rva002130CA` |
| 0x0076DF08 | 14 | +0x2A8 | `Rva0021397C` |
| 0x0076DF16 | 14 | +0x2B4 | `Rva00211FA3` |

Each complete body loads the constructing object from `[ebp-0x14]`, adds
its own member offset, and tail-jumps to the existing teardown. The replay
verifies every byte and relocation against the normally built object, the
whole parent and its full exception graph. Ghidra independently supplies each
14-byte extent. Local `$L` labels are locators; none is a new callable alias.
There is no synthetic parent, assembly, new callee pin or source reconstruction.
The already existing genuine constructor emits all five bodies.

These cleanups total 70 new unique C++ exact bytes and are banked separately.
The hash/vector/map roles and partial views are carried from the existing
verified source. This adds no original application type, hidden member layout
or link-census claim.

The normal identity check remains in shadow mode and reports unowned existing
constructor/teardown bindings at 0x00212AEF, 0x002130CA and 0x00212379.
These declarations and bindings predate this ledger addition; no new source
definition, pin, baseline exemption or verifier change suppresses them.
Exact parent/cleanup bytes and exception data do not settle those callee
identity or linking debts.

Replay after the normal whole-source build:

```
./build.sh Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCtor.cpp
python3 reverse/attempt_support/living-world-ctor-cleanups-20261013/verify.py
python3 reverse/attempt_support/living-world-ctor-cleanups-20261013/verify.py --rva 0x0076DE7C
```
