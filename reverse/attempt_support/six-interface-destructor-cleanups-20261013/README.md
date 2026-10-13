# Six-interface destructor cleanups

The existing real `Rva00574CC1` destructor at 0x00574CC1 matches all 333
native bytes and its complete associative exception graph. That graph
independently places four previously unclaimed compiler-emitted bodies:

| RVA | Whole extent | Cleanup |
| --- | ---: | --- |
| 0x0079B08E | 20 | Conditional adjustment to the sixth interface at +0x14 |
| 0x0079B0A2 | 11 | Owning member at +0x28 |
| 0x0079B0AD | 11 | Owning member at +0x48 |
| 0x0079B0C3 | 11 | Owning member at +0x5C |

The 20-byte body preserves its null-adjustment calculation and tail jump.
Every complete body and existing destructor relocation matches the normal
object. Ghidra independently supplies each complete extent. Local labels only
locate emitted code: the real parent and full exception graph supply native
identity, with no adjacency-based attribution.

The four bodies total 53 new unique C++ exact bytes and are banked separately.
No synthetic parent, assembly, new callee pin or callable alias is introduced.
The existing source already emits every body. Its partial six-interface view,
neutral destructor spellings and unknown original application identities remain
unchanged; no new full-layout or link-census result is claimed.

The +0x48 cleanup's native callee 0x00574338 is an existing five-byte
unadjusted tail jump to the rowed destructor 0x005CB8D4. Replay checks that
whole native thunk. Normal shadow identity checking still reports the
pre-existing Gen_uwm_005fed52 binding and duplicate Rva00574338 destructor
definition; no source, pin, baseline or verifier change hides those findings.

```
./build.sh Code/GameEngine/Source/Common/Rva00574CC1Dtor.cpp
python3 reverse/attempt_support/six-interface-destructor-cleanups-20261013/verify.py
```
