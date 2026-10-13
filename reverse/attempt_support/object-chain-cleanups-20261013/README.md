# Destructor-chain base and member cleanups

The entire source is `Code/GameEngine/Source/GameLogic/Object/Rva001FB94FDtor.cpp`.
`verify.py` checks all five complete real destructor bodies: four 59-byte
bodies at 0x001FB94F, 0x001FBAEE, 0x001FBCA1 and 0x001FC0B6, plus the 136-byte
virtual destructor at 0x001FC0F1. Each full body and its entire native
associative exception graph independently verify EXACT.

The final destructor's native graph owns two cleanups:

* 0x0076B889, 8 bytes, $L505: load saved this from EBP-0x10 and tail-jump to
  the already rowed 159-byte base destructor at 0x001F4C67. Complete bytes:
  `8b4df0e9d693a8ff`.
* 0x0076B891, 14 bytes, $L506: load the same saved receiver, add 0x94 and
  tail-jump to the same-unit 59-byte destructor at 0x001FC0B6. Complete bytes:
  `8b4df081c194000000e91708a9ff`.

Ghidra independently supplies both complete unwind extents. The proof checks
all cleanup bytes and REL32 destinations, with ownership supplied by the
complete native graph rather than byte shape or adjacency. The earlier blocked
attempt for 0x0076B891 lacked that ownership evidence; this proof supplies it.

The source's existing chain model, receiver offsets, refcount accesses and
address-derived names are retained. Native vtable and call relationships
support the current body ownership; these rows do not establish the original
application class names or inheritance declarations. No source, pin, global,
header or marker is changed. The existing honest present-unmatched annotation
on the inline first-base destructor remains untouched.

Run the normal whole-source build before replaying `verify.py`. The saved
census 6963cc017c does not include this unit, so link_check cannot preview its
placement. No linking gain is claimed and no linking runner was started.
