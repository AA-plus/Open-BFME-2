# AI corner-picker array and query-result cleanups

The whole source is
Code/GameEngine/Source/GameLogic/SkirmishAI/AISpecialPowers/AISpecialPowerPickers.cpp.
All ten complete native picker bodies and their full associative exception
graphs are checked by verify.py, in addition to the normal whole-file gate.
The existing 603-byte parent at 0x005D9721 directly owns these complete
Ghidra-bounded bodies:

* 0x007A2932, 19 bytes, $L1325: destroys four 12-byte Coord3D corners at
  EBP-0x80. It pushes the existing destructor 0x000B3FD0, count 4, stride 12
  and local address, calls the native EH vector destructor iterator at
  0x00629110, and returns. Bytes: `68d03f4b006a046a0c8d458050e8cc67e8ffc3`.
* 0x007A2955, 8 bytes, $L1328: destroys the local BfmeWideResult at
  EBP-0x18 through the existing 34-byte destructor at 0x0004AA28.
  Bytes: `8d4de8e9cb808aff`.

The proof requires complete byte equality, resolved DIR32/REL32 targets and
native parent-graph ownership. These bodies are compiler emissions from the
existing C++ corner scan, not standalone callable functions or lifted dumps.
Their exact local offsets come from target instructions, not donor layouts.

The existing source documents picker vtables, partition-filter behavior and
its neutral address-derived class views. Those witnesses and uncertainties
are retained: the selected parent is an allied-object corner scan, but no
new original special-power name or full class hierarchy is asserted. The
four-byte range-result handle is the established BFME-specific recovery view.
No source, header, pin, alias, global, compiler setting or class marker changes.
In particular, the pre-existing getPlayerMask alternatename is not added or
endorsed as a new identity claim by these cleanup rows.

Run the normal whole-source build before replaying verify.py. Byte and
exception-graph evidence does not establish a new link-census result.
