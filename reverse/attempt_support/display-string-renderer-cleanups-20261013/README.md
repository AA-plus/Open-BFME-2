# Display-string renderer cleanups

The existing real W3DDisplayString destructor at 0x00106162 matches all
92 native bytes and its complete associative exception graph. The owning
source records the donor family evidence and independently measured target
member offsets; BFME 2's renderer positions differ from the BFME 1 donor.

The native graph independently places two previously unclaimed bodies:

| RVA | Whole extent | Native member |
| --- | ---: | --- |
| 0x00764442 | 11 | Text renderer at +0x14 |
| 0x0076444D | 14 | Hotkey text renderer at +0xD8 |

Each loads the saved destroying receiver at EBP-0x10, adds its own member
offset and tail-jumps to the existing Render2DSentenceClass destructor
at 0x00157C70. Replay verifies both full bodies and every relocation,
the complete parent and all native exception data. Ghidra independently
provides both complete extents. The adjacent base cleanup is already owned
by this real file and is preserved.

These two naturally emitted C++ cleanups add 25 unique C++ exact bytes
and are committed separately. No synthetic parent, assembly, new pin or
callable alias is introduced. Existing partial class/member declarations,
donor provenance and target evidence remain unchanged; no additional full
class contract or link-census result is claimed.

```
./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringDtor.cpp
python3 reverse/attempt_support/display-string-renderer-cleanups-20261013/verify.py
```
