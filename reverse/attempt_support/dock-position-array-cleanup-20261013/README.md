# Dock-position local array cleanup

Read the complete DockUpdateLoadDockPositions.cpp. Its source already records
BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705 and the ZH semantic
relationship. Dock bone literals and adjusted callers establish the target
identity; the matched constructor supplies the independently measured layout.
This work preserves that provenance and adds no original class identity for
the lifetime adapter over canonical Coord3D.

The full 270-byte DockUpdate::loadDockPositions at 0x005897FB and its entire
native associative exception graph are EXACT. The graph owns the Ghidra-bounded
22-byte body at 0x0079CC0F ($L4498), resolving the old attempt's unknown-parent
blocker. It is the array unwind cleanup, not the GameClient destructor guessed
in that earlier attempt. Its full bytes are:

`68d03f4b006a0a6a0c8d857cffffff50e8ecc4e8ffc3`

The native body passes the one-byte empty destructor at 0x000B3FD0, count 10,
stride 12, and array address EBP-0x84 to the existing exception-aware vector
destructor iterator at 0x00629110. The real C++ approachBones[10] array has
that canonical coordinate layout. verify.py independently proves the entire
parent and exception graph, cleanup extent and both relocations, the emitted
three-byte constructor callback at 0x0047A6A9, the one-byte destructor callback,
and the entire 96-byte iterator from the existing msvcrt.lib ehvecdtr.obj
member. Both adapter callbacks are relocation-free byte twins; no new pins
or alias rows are added. The CRT body is existing prebuilt provenance, not new
C++ recovery. Only this 22-byte natural C++ cleanup earns new coverage.

Normal owning verification passes the original parent and all four literals.
The before-row identity audit reports one inherited divergent vector<Coord3D>
operator[] definition (identity-before.json); it is documented, not suppressed.
No source, header, compiler flags, globals, pins, aliases or markers change.
place_bodies reports zero further bodies or pins. The old local census cannot
establish a new clean linking result; no linking gain is claimed.

Before replaying verify.py, run normal build.sh for the owning file and the
symbol ??_M@YGXPAXIHP6EX0@Z@Z. The latter extracts and verifies the committed
CRT member through the normal build entry point. The proof does not compile
or replace shared objects itself.
