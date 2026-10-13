# Bridge damage-state string-array cleanups

The real 593-byte `BridgeBehavior::onBodyDamageStateChange` at 0x00456C1F
and its entire associative exception graph match native bytes. The existing
source records its Zero Hour semantic provenance and target-specific bridge,
audio and interface-layout adaptations. That exact graph independently places:

| RVA | Whole extent | Native local |
| --- | ---: | --- |
| 0x0078A047 | 19 | Three four-byte strings at EBP-0x3C |
| 0x0078A05A | 19 | Three four-byte strings at EBP-0x30 |

Both bodies call the destructor iterator with their own local address, count
three, stride four and the existing AsciiString destructor callback. Replay
checks all 19 bytes, both callback/iterator relocations, the whole real handler
and full native exception graph. Ghidra independently provides both extents.

The two previously unclaimed bodies add 38 unique C++ exact bytes and are
committed separately. They come from the existing real handler's two local
string arrays. No synthetic parent, assembly, new pin or callable alias is
introduced, and no parent is inferred from nearby addresses. Existing target
identity, layout evidence and donor provenance remain unchanged; there is no
new link-census claim.

```
./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnBodyDamageStateChange.cpp
python3 reverse/attempt_support/bridge-string-array-cleanups-20261013/verify.py
```
