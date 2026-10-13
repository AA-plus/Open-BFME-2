# Apt row-page member construction cleanups

The entire 175-line AptRowPageCtor_Rva0051066A.cpp was read, together with
both existing cleanup-provider files. The complete 641-byte constructor at
0x0051066A and its complete native associative exception graph are EXACT.
The source retains its address-derived class identity and target-based Apt
row-page description; no new original class name or donor layout is asserted.
Its six command-name/format literals verify in the normal whole-file build.

The graph directly owns two Ghidra-bounded eleven-byte cleanups:

* 0x00794A6C, $L1509: saved this at EBP-0x10 plus 8, the command-map adder;
  `8b4df083c108e9c7f6d8ff`, jumping to 0x0052413E.
* 0x00794A77, $L1510: the same receiver plus 0x14, the external-handler
  adder; `8b4df083c114e92ef7d8ff`, jumping to 0x005241B0.

Both actual callees are existing matched C++ bodies, not opaque new pins.
verify.py also independently compares each entire 47-byte destructor and
its complete native EH graph. Their owning sources are:

* Code/GameEngine/Source/GameClient/GUI/InGame/Strategic/BattlePromptConstructorLifetimes.cpp,
  AptCommandMapAdder::~AptCommandMapAdder, native 0x0052413E.
* Code/Libraries/Source/WWVegas/WWLib/Rva005241B0Dtor.cpp,
  Rva005241B0::~Rva005241B0, native 0x005241B0.

The normal provider builds pass 3/3 and 1/1 rows respectively. The adder
roles and offsets follow the existing target constructor, its command setup
calls and those destructor providers. Existing AptRef/template provenance,
private views and other source annotations are preserved rather than treated
as independently established new facts.

Before either new row, code_identity_gate.check reports zero findings for
this source (identity-before.json). No source/header/flag/global/pin/alias or
marker is added. These are natural emissions from the real C++ constructor.
place_bodies reports zero further bodies or pins. No linking gain is claimed.
Run the normal build for the constructor and both provider files before
running verify.py; that proof only reads their current normal-build objects.
