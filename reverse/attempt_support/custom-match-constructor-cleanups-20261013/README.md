# Custom-match constructor subobject cleanups

The complete 305-line AptOnlineCustomMatchCtor.cpp and both destructor-provider
files were read. The entire 1535-byte constructor at 0x005A5BC7 and its full
native associative exception graph are EXACT. Both existing rows and all
15 literals pass the normal whole-file build. The existing address-derived
constructor name and its documented vtable/callback identity witnesses are
preserved; this change introduces no additional original-name claim.

Two Ghidra-bounded eleven-byte bodies are owned directly by that native graph:

* 0x0079E395, $L1835: saved this at EBP-0x10 plus 0x60, the owner interface;
  `8b4df083c160e93261caff`, jumping to destructor 0x004444D2.
* 0x0079E3AB, $L1837: the same receiver plus 0x70, the setup member;
  `8b4df083c170e92b3ecaff`, jumping to destructor 0x004421E1.

verify.py independently checks the complete constructor, full EH graph,
cleanup extents and relocations, plus both complete existing C++ providers:
Rva004444D2Dtor.cpp (25 bytes at 0x004444D2, no EH graph on either side),
and Rva004421E1Dtor.cpp (211 bytes at 0x004421E1, complete native EH graph
EXACT). The normal provider builds pass all 3 and 8 rows respectively.
Target instructions establish frame/offset/callee facts; the retained source's
owner/setup roles are backed by its existing constructor and destructor
relationships. Existing class-view and naming uncertainty is not expanded.

Before either new row, identity-before.json records the one shadow finding
already present in this source: divergent Rva0059EB41 scalar deleting
destructor. That inline view is unchanged; the finding is not hidden or
classified as a false reject. These two cleanup callees use their existing
matched owning names and are independently checked in full.

No source/header/flag/global/pin/alias or marker is added. The cleanups are
natural emissions of the existing real C++ constructor. place_bodies finds
zero further bodies or pins. No new linking result is claimed. Build the
constructor and both provider sources normally before running verify.py.
