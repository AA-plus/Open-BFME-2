# TeamTemplateInfo unit-array construction cleanup

Read the complete TeamTemplateInfoInitFromDict.cpp and both record provider
sources Rva0039EA9CCtor.cpp and Rva0039EAB7Dtor.cpp. Existing target class
identity is supported by the C1AE70 vtable getter and WB EEF600, with the
loader/destructor establishing the Snapshot base and 0x1EC-byte layout.
The constructor comment identifies the donor behavioral guide separately.
No new original identity is assigned to the address-named unit-record class.
Its constructor provider explicitly retains the inferred trailing-member
representation as an inference, rather than a target type fact.

The entire 399-byte constructor at 0x003A26E6 and its complete native
associative exception graph are EXACT. The graph independently owns the
Ghidra-bounded 22-byte cleanup at 0x00781759, compiler label $L1358:

`68b7ea79006a076a188b45f083c00450e8a279eaffc3`

The cleanup destroys seven records, each 24 bytes, starting at the saved
this pointer at EBP-0x10 plus four. The callback is the real record
destructor at 0x0039EAB7 and the call is to the existing CRT EH vector
destructor iterator at 0x00629110. Parent ownership and frame location are
from the verified native exception graph, not adjacency. The existing real
C++ member array naturally emits this cleanup.

verify.py checks the entire parent, native graph, cleanup extent and both
relocations, plus the complete 27-byte record constructor and 54-byte record
destructor with its native exception graph. It also verifies the existing
96-byte CRT iterator from msvcrt.lib, which remains prebuilt provenance and
earns no new C++ recovery credit. Run normal builds of these three source
files and ??_M@YGXPAXIHP6EX0@Z@Z before replaying verify.py.

The whole owning file passes its two original rows, frozen-file inspection
and the before-row identity audit (zero findings). place_bodies finds zero
additional bodies or pins. The old local census at 6963cc017c does not contain
this file, so no new clean linking result is claimed. No source, header,
flags, pin, alias, global or marker changes accompany this admission.

The full graph inventory also identifies already-rowed cleanup siblings.
Ten string cleanups and the base cleanup already have generated C++ rows.
The final 24-byte array cleanup at 0x007817FB belongs to the currently
foreign-claimed EHStateCleanupRange38.asm scope; that work is left intact.
Only the unclaimed 22-byte unit-array cleanup is admitted here.
