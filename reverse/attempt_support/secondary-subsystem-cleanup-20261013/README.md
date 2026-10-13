# Secondary SubsystemInterface destructor cleanup

Read the whole Rva002DAB18Finish.cpp. Its existing target evidence describes
70-byte constructor 0x002DAB18, 79-byte destructor 0x002DAB6C, both vtables,
the secondary base at +4 and the AsciiString member at +0x10. Preserve the
address-derived owning class name and the existing primary-base shaping view;
exact bytes do not supply an original class identity.

Both whole parents and both complete native associative exception graphs are
EXACT. The destructor graph owns the 20-byte Ghidra extent at 0x00777C37,
compiler-local label $L1234:

    8b4df08b45f083c004f7d91bc923c8e929d2a3ff

It reads the saved this pointer at EBP-0x10, computes a nullable +4 secondary
base adjustment with NEG/SBB/AND, and tail-jumps to the real SubsystemInterface
destructor 0x001B4E74. The sole REL32 relocation starts at offset 16. This is
naturally emitted from the real C++ base destruction; graph ownership and
layout establish its relationship, not proximity to another function.

The complete 14-byte SubsystemInterface provider is also strictly compared,
including its vtable and AsciiString destruction references. The provider has
no EH graph on either side. Its normal owning-file build passes 368/368 rows.
The provider's old BFME1 introductory addresses are donor context, not new
BFME2 facts. This recovery changes no source, header, pin, alias or layout.

Normal owning-file build passes the six original rows; frozen-file inspection
and the before-row identity audit pass. Constructor cleanup 0x00777C1D and
destructor sibling 0x00777C2F already have generated C++ rows. Both installed
handlers are already rowed. place_bodies finds no incidental bodies or pins.
The old local census 6963cc017c has no entry for this file, so no linking gain
is claimed.

Run normal build.sh on Rva002DAB18Finish.cpp and SubsystemInterface.cpp before
verify.py. The replay checks both full parent bodies/graphs, the complete
cleanup bytes/relocation and the complete provider body.
