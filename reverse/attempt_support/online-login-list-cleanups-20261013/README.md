# Online-login owned-list cleanups

The complete 1184-line source is
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineLogin.cpp.
verify.py checks all sixteen complete callback bodies over 100 bytes and
their complete native associative exception graphs. In particular the
659-byte cached-login population at 0x005709D1 and 210-byte ping setup at
0x00570C64 directly own these Ghidra-bounded eight-byte bodies:

* 0x0079AAFE, $L15625: cached-email list at EBP-0x1C;
  bytes `8d4de4e902d4a6ff`.
* 0x0079AB26, $L15634: local cached-nickname list at EBP-0x18;
  bytes `8d4de8e9dad3a6ff`.
* 0x0079AB40, $L16092: ping-server list at EBP-0x10;
  bytes `8d4df0e9c0d3a6ff`.

Each tail-jumps to 0x00207F08. The same normally built object emits the
complete five-byte list<AsciiString> destructor there: `e9af6d0f00`, an
unadjusted tail jump to the owned 23-byte _List_base<AsciiString> destructor
at 0x002FECBC. The proof checks this whole emitted wrapper independently,
without masked or unresolved bytes, as well as all three cleanup relocations.
The ledger's existing wrapper recovery name is retained; no alias or pin is
introduced to rename it.

The established source identifies the Apt online-login home and documents
BFME 1 donor 34f59164 for cached-login behavior. The current donor TU
OnlineLoginPopulateCachedLogins0054FF80.cpp was read in full at verified
reference/open-bfme-1 revision cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The ZH WOLLoginMenu.cpp startPings definition was reviewed at that pointer.
These are semantic leads: BFME 2's native local frame offsets, shared cleanup
entry and borrowed nickname-return/copy relationship come from target code.
In particular the local cachedNames list owns its copy even though the
preferences getter returns a borrowed const reference. Original callback
spellings remain address-derived and existing layout uncertainty is preserved.

No source, shared header, compiler setting, pin, alias, global or class marker
changes. These are natural lifetime cleanups from the existing real C++
callbacks. Run the normal whole-source build before verify.py. These checks
do not establish a new link-census result.

The normal hooks expose four pre-existing shadow identity findings elsewhere
in the unchanged unit: the list<int> copy constructor bound at 0x00445E8B
is divergent, MessageBoxOkCancel at 0x0044C146 and rva005AF12F at 0x005AF12F
are unowned, and the emitted char allocator rebind definition is divergent.
None is a finding on these three list cleanups. They remain repair work;
no gate, baseline or identity exception was changed to hide them.
The saved link census 6963cc017c does not include this unit, so link_check
cannot preview its placement.
