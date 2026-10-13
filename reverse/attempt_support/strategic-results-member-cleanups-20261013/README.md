# Strategic-results implementation member cleanups

The whole source is Code/GameEngine/Source/Common/Rva005EB8D6Dtor.cpp.
Its complete 127-byte destructor at 0x005EB8D6 and full native associative
exception graph verify EXACT. The graph directly owns these complete
Ghidra-bounded eleven-byte bodies, both loading saved this from EBP-0x10:

* 0x007A4431, $L393, adds 0x38, bytes `8b4df083c138e9ff85a8ff`.
* 0x007A443C, $L394, adds 0x44, bytes `8b4df083c144e9f485a8ff`.

Both tail-jump to 0x0022CA3B. That whole five-byte native thunk is
`e9d2fbffff`, an unadjusted tail jump to the owned 56-byte nonvirtual
container destructor at 0x0022C612. The proof checks the entire parent,
its complete exception graph, both cleanup bytes/relocations and the thunk.
The thunk provider Rva0022C612Dtor.cpp was read in full; its existing
cleanup-forward recovery name and original-type uncertainty are retained.
The source still names the forwarded destructor at these cleanup call sites,
so wrapper identity reconciliation remains separate repair work.

The complete StrategicConflictResultsImplCtor.cpp was also read. Its existing
WorldBuilder StrategicConflictResults::Impl constructor witness and native
642-byte constructor at 0x005EB9F2 corroborate this destructor's home, the
50-byte object and two twelve-byte member views at +0x38/+0x44. These cleanup
rows preserve the existing source layout rather than declaring a new original
map type or canonical class. The Apt-manager relationship remains inferred as
stated in the original destructor source.

No source, header, flag, global, pin, alias or marker is added. The cleanups
are natural emissions from the real C++ destructor. Run the normal whole-file
build before verify.py. Byte and exception-graph proof is not a new linking
result; the existing private-view and wrapper-name debt is not hidden.
