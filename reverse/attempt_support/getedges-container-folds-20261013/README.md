# Native GetEdges container dependencies

The existing `RvaMapIndexGenP12pod00928690.cpp` owns the byte-exact three-integer
key-map operator at native 0x0016E330. The saved 1,692-byte `GetEdges` candidate
uses that same key shape while welding positions and pairing directed edges.
This repair emits the real container helper instantiations in that existing
unit. It preserves every existing matched body in the unit (4/4 verified).

The official `tools/pin_admission.py --add` admitted four genuine folds:

| Native RVA | Complete extent | Instantiation |
| --- | ---: | --- |
| 0x0016DE80 | 56 | `map<Gen_p12pod, int>` constructor |
| 0x0016CB50 | 51 | The same key-map tree's recursive `_M_erase` |
| 0x0016DAA0 | 121 | The same key-map tree's destructor |
| 0x0016D610 | 86 | Directed-edge pair-key hashtable `clear` |

Admission proves whole bodies and every existing owner's relocations, checks
that each new name has no independent address, recursively proves unnamed
callees, and checks the tree destructor's complete associative exception graph.
No owner row is renamed or duplicated. The allocator shim and /EHs settings
come from the already matched container siblings; the original operator still
matches at /O2 /G7. The hash/equality types have declaration-only operators:
cleanup needs their measured container ABI and does not claim original names
or a recovered hash implementation.

This resolves all three formerly unresolved calls in the full saved consumer.
It does **not** land `GetEdges`: the current consumer still emits 1,644 bytes
against native 1,692, with a 0x6C frame against native 0x68. Its `vector<int>`
push helper also has an independent existing address (0x00688940), whereas
native calls 0x004DFCB0, whose growth call is 0x002DFCF6. Do not repin that
already named integer helper, or change an inferred element type merely to
force a fold. The saved body remains in `reverse/attempts/0x0016e450.cpp`.

There are no new unique retail bytes in this dependency repair. Native control
flow and diagnostics establish the GetEdges relationship; the source's opaque
key/hash labels remain target-layout views, not original source identities.

Replay the normal unit verification and the formal outgoing-range check:

```
./build.sh Code/Libraries/Source/WWVegas/WWLib/RvaMapIndexGenP12pod00928690.cpp
python3 tools/pin_admission.py --range <repair-commit-parent> <repair-commit>
python3 tools/pin_consistency.py --check
```
