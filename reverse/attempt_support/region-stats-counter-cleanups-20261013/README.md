# Region-stats counter member cleanups

Read the complete 182-line Code/GameEngine/Source/Common/Rva005D2EA8Dtor.cpp.
The source's original callback-member class name remains unknown. Its retained
24-byte layout, listener field, rollover byte and command-map member follow
existing target accesses and vtable C75898; no new donor name is asserted.
All nine existing rows and four literals pass the normal whole-file build.

The complete 73-byte destructor at 0x005D2EA8 and 366-byte constructor at
0x005D3398 each have an EXACT complete native associative exception graph.
Those graphs directly own two Ghidra-bounded eleven-byte bodies:

* 0x007A20B4, $L1559: the destructor's saved this at EBP-0x10 plus 0x0C;
  `8b4df083c10ce97f20d8ff`.
* 0x007A2176, $L1687: the constructor's saved this at EBP-0x14 plus 0x0C;
  `8b4dec83c10ce9bd1fd8ff`.

Both jump to the existing AptCommandMapAdder destructor at 0x0052413E.
verify.py independently checks both complete parents and graphs, both entire
cleanups and relocations, and the whole 47-byte C++ provider plus its native
EH graph in BattlePromptConstructorLifetimes.cpp. Its normal build verifies
all three rows. That provider was read in full during the preceding Apt
row-page work and is reverified here with its current inputs. These facts
establish native frame slots and member-destruction relationships; they do
not recover the counter's original class name.

The before-row identity audit reports zero findings (identity-before.json).
No source, header, flag, pin, alias, global or marker is changed. These are
natural cleanups emitted by the real C++ constructor and destructor. Existing
source annotations and class views are retained. place_bodies reports zero
further bodies or pins. No new linking result is claimed. Run normal builds
of this source and BattlePromptConstructorLifetimes.cpp before verify.py.
