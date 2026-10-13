# Thing-side holder member cleanups

The whole source is Code/GameEngine/Source/Common/Thing/Rva0033DDA1Dtor.cpp.
Its existing 713-byte destructor at 0x0033DDA1 and complete native associative
exception graph verify EXACT. That graph directly locates these complete
Ghidra-bounded 14-byte bodies, both loading the saved receiver at EBP-0x10:

* 0x0077C7D6, $L649, adds 0x2E4 and tail-jumps to 0x0033CF2F.
  Whole bytes: `8b4df081c1e4020000e94b07bcff`.
* 0x0077C87E, $L661, adds 0x388 and tail-jumps to 0x0025753F.
  Whole bytes: `8b4df081c188030000e9b3acadff`.

The proof replays every parent byte, the full exception graph, both complete
cleanup bodies and all relocations. It also checks the complete native
five-byte unadjusted tail wrappers: 0x0033CF2F -> 0x0033CD02 and
0x0025753F -> 0x0025742C. These are real C++ member lifetime cleanups emitted
by the existing destructor, not standalone callable functions or lifted dumps.
No source, pin, global, class view or identity is added by these two rows.

The existing ThingTemplate-side relationship, vtable and member layout
witnesses are retained. Original member type names remain uncertain; the
Rva spellings and neutral layout views are not new original-name claims.
The source's older declared destructor names describe the forwarded base
bodies. They do not reconcile the distinct native wrapper identities, and
that source-level binding debt remains visible to the shadow identity check.
The existing 0x0025753F provider uses the shared record-tree view; the local
holder view is not thereby proven to be the canonical C++ class definition.
No additional alias or baseline exemption is used to conceal this debt.

Run the normal whole-source build before verify.py. The saved census
6963cc017c has no entry for this source; link_check cannot preview placement.
No new linking result is asserted and no linking runner was started.
