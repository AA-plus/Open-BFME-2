# Ladder-definition list cleanups

Read the complete 521-line Code/GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp.
The existing real C++ reproduces all eleven prior ledger rows, 33 literals,
three empty-string references and two imports. All five complete parents and
native associative exception graphs verify EXACT: LadderInfo construction at
0x0054D858 (128 bytes), parseLadder at 0x0054DA41 (2234), checkLadder at
0x0054E2FB (299), loadLocalLadders at 0x0054E426 (288), and LadderList
construction at 0x0054E546 (592). verify.py independently checks all five.

Their complete native EH graphs bind three whole Ghidra-bounded cleanups:

* 0x007983C7, 11 bytes, current $L44155: LadderInfo's saved this at EBP-0x14
  plus 0x1C, the validMaps list; `8b4dec83c11ce936fba6ff`.
* 0x007984E2, 8 bytes, current $L44453: parser local AsciiString list at
  EBP-0x30; `8d4dd0e91efaa6ff`.
* 0x00798502, 8 bytes, current $L44443: parser local AsciiString list at
  EBP-0x20; `8d4de0e9fef9a6ff`.

All three tail-jump to the existing list<AsciiString> destructor at 0x00207F08.
This unit's entire emitted five-byte destructor is also independently exact,
including its relocation, with no masked or unresolved bytes: `e9af6d0f00`,
a tail jump to the existing list-base destructor at 0x002FECBC. Labels are
resolved from the verified parent graph rather than the stale inventory.
The two parser frame slots are not assigned extra source-variable names.

The file preserves its original donor revision
6d9434269164392c5ba62aaa7c15a86b5b020d76 and Generals-era parser provenance.
The currently retained reference is cee35b7d8ca077d7255f1c39cb69e9fd9627aa85;
both complete Generals and Zero Hour LadderDefs.h definitions were reviewed.
Those establish the donor's two list<AsciiString> members and field order;
the target's whole constructor, parser and native EH graphs independently
prove these target offsets, frames, callee bindings and cleanup ownership.
The existing BFME2 File/FileSystem/GameSpy interface adaptations and native
America/China/GLA fallback remain unchanged.

No source, header, flag, pin, alias, global or marker is added. These are
natural cleanups emitted by the real C++ bodies. place_bodies reports zero
additional bodies or pins. Byte proof does not assert a new linking result.
Run the normal whole-file build before verify.py.

Normal commit hooks finish at 14/14 verified rows and five EXACT EH graphs.
The shadow identity pass reports 17 existing findings in the unchanged source;
none names the three new cleanup rows. Eleven are bindings: AsciiString
destructors at 0x0002FD60/0x00036410 (five occurrences), AsciiString list-base
construction at 0x004EC36C (two), LadderInfo destruction at 0x0054D8D8 (two),
getFileListInDirectory at 0x00600FC9 and getAllSideStrings at 0x001FDD7D.
Six concern emitted definitions: wide-character allocator rebind, the
AsciiString const-list-iterator converting constructor, the no-case AsciiString
tree destructor and erase, list-iterator equality, and AsciiString scalar
deletion. These are retained diagnostics, not suppressed or declared false
rejects. Existing source/interface debt needs separate evidence-led repairs.
The saved local census at 6963cc017c does not contain this source, so
link_check cannot preview it; no linking gain is asserted.
