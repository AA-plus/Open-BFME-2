# Peer room-statistics temporary cleanups

The existing real PeerThreadClass::pushStatsToRoom at 0x0038AF29
matches all 658 native bytes and its complete associative exception graph.
WorldBuilder F665D0 independently supplies the method identity; the existing
BFME 1 room-statistics source supplies its semantic guide. Target record,
vslot and buffer adaptations remain as documented in the owning source.

That exact graph independently places two unclaimed 11-byte bodies:

| RVA | Native local | Existing destructor |
| --- | --- | --- |
| 0x0078060D | Strategic record temporary at EBP-0x3C4 | Rva0038454E at 0x0038454E |
| 0x0078062E | Open-play record temporary at EBP-0x554 | Rva003844D7 at 0x003844D7 |

Each forms its own local address and tail-jumps to the already rowed real
destructor. Replay verifies every byte and relocation, the complete parent
and its full native exception graph. Ghidra independently supplies both
11-byte extents. Adjacent graph cleanups already owned by this file are
preserved and are not claimed again.

These two compiler-emitted bodies add 22 unique C++ exact bytes and are
committed separately. They come from existing real C++ locals: no synthetic
parent, assembly, new pin or callable alias is introduced. The address-derived
record names and opaque payloads retain their existing uncertainty. This is
no new application-type or link-census claim.

```
./build.sh Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp
python3 reverse/attempt_support/peer-room-statistics-cleanups-20261013/verify.py
```
