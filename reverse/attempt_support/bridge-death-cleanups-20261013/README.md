# Bridge death polygon and query-result cleanups

The complete source is
Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp.
The whole 448-byte BridgeBehavior::handleObjectsOnBridgeOnDie at 0x00457577
and its complete native associative exception graph verify EXACT. The graph
locates these complete Ghidra-bounded bodies:

* 0x0078A108, 19 bytes, $L572: destroys the four 12-byte Coord3D elements
  starting at EBP-0x50. It pushes the existing Coord3D destructor at
  0x000B3FD0, count 4, stride 12 and the local array address, then calls
  the existing EH vector destructor iterator at 0x00629110 and returns.
  Whole bytes: `68d03f4b006a046a0c8d45b050e8f6efe9ffc3`.
* 0x0078A11B, 8 bytes, $L573: passes the local query-result handle at
  EBP-0x14 to the existing 34-byte BfmeWideResult destructor at 0x0004AA28.
  Whole bytes: `8d4dece905098cff`.

verify.py checks every parent byte, the complete exception graph, both full
cleanup bodies and their DIR32 and REL32 targets. The rows are natural
emissions from this existing real C++ body, not standalone callable functions.
No source, pin, alias, global, class view or compiler setting changes.

Existing target identity comes from the sole BridgeBehavior::onDie caller
at 0x004581FD and the native algorithm, member accesses and call graph.
The Zero Hour BridgeBehavior.cpp function provides the established semantic
reference; its four-coordinate polygon lifetime agrees, while its iterator
is an ObjectIterator plus MemoryPoolObjectHolder. BFME 2 instead returns the
native four-byte refcounted BfmeWideResult by value. That name is a recovery
name, not an assertion that the Zero Hour type has the same target identity.
The donor was reviewed under reference/open-bfme-1 revision
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 at
inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp.
The source's existing Coord3D canonical-header exception is unchanged.

Run the normal whole-source build before replaying verify.py. These byte and
exception-graph checks do not establish a new link-census result.
