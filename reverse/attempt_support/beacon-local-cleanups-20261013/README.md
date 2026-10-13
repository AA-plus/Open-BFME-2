# Beacon local-handle cleanups

The existing real createParticleSystem helper (0x004C9674, 355 bytes),
BeaconClientUpdate::hideBeacon (0x004C97D7, 216 bytes) and clientUpdate
(0x004C98AF, 225 bytes) match their complete native bodies and entire
associative exception graphs. The source records its Zero Hour and BFME 1
cee35b7d8 semantic provenance and independently measured target adaptations.
The same-TU helper's compiler-private Drawable-in-ESI ABI remains intact.

The complete native graphs independently place these four unclaimed bodies:

| RVA | Whole extent | Parent | Native handle local |
| --- | ---: | --- | --- |
| 0x0079050A | 8 | createParticleSystem | EBP-0x1C |
| 0x00790524 | 8 | hideBeacon | EBP-0x18 |
| 0x0079052C | 8 | hideBeacon | EBP-0x24 |
| 0x0079053E | 8 | clientUpdate | EBP-0x1C |

Each forms its own handle address and tail-jumps to native 0x002115C5.
Replay also verifies that the source's inline handle destructor reproduces
the whole eleven-byte conditional-destroy body there, including its existing
unlink relocation to 0x0004CBC0 and final return. The address already has
its neutral owner and an admitted RvaSmartPtr12 twin; neither row nor pin is
changed. This proves the operation without assigning an original template
or type identity to the source's BfmeParticleSystemHandle view.

Replay checks all complete parents, their complete native exception data,
every full cleanup body and relocation, and the existing inline provider.
Ghidra independently supplies each eight-byte extent. Local compiler labels
are locators; no parent comes from adjacency.

The four bodies add 32 unique C++ exact bytes and are committed separately.
No synthetic parent, assembly, new pin or callable alias is introduced.
Existing reference and target evidence, partial layouts and neutral setter
names retain their documented uncertainty. No link-census gain is claimed.

```
./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdate.cpp
python3 reverse/attempt_support/beacon-local-cleanups-20261013/verify.py
```
