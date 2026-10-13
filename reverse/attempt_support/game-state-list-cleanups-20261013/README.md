# GameState list-member cleanups

The existing real GameState destructor at 0x002DE58D matches all 180
native bytes and its complete associative exception graph. Its existing
vtable/deleting-destructor and related member-access witnesses establish
the receiver identity and member relationships, as documented in the source.

The graph independently places two unclaimed fourteen-byte bodies:

| RVA | Whole extent | Native member |
| --- | ---: | --- |
| 0x00778390 | 14 | Integer-list view at +0xE0C |
| 0x0077839E | 14 | Integer-list view at +0xE10 |

Each loads the saved receiver at EBP-0x10, adds its own offset and
tail-jumps to the existing list-base destructor at 0x00200667. Replay
verifies every byte and callee relocation, the whole parent and its entire
native exception graph. Ghidra independently supplies both complete extents.
Compiler-local labels only locate code; no parent comes from adjacency.

The two bodies add 28 unique C++ exact bytes and are committed separately.
The existing real destructor emits them. No synthetic parent, assembly,
new pin or callable alias is introduced. Existing partial member/base views
and their identity uncertainties remain unchanged. Complete cleanup matches
are not a new link-census result.

Native 0x00200667 is an existing five-byte unadjusted tail jump to the
list-base body at 0x004EC395; replay checks that entire native thunk.
Normal shadow identity checking still reports the source's existing camera
list destructor binding at 0x00295983 and the integer-list-base spelling
bound to 0x00200667. The two new cleanup rows expose that existing integer
binding too. No source definition, pin, baseline or verifier is changed to
hide these findings, and complete native cleanup bytes do not settle them.

```
./build.sh Code/GameEngine/Source/Common/System/SaveGame/GameStateDtor.cpp
python3 reverse/attempt_support/game-state-list-cleanups-20261013/verify.py
```
