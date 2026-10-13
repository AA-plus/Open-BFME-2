# ScriptAction UI-text exception cleanups

Read the complete ScriptActionGetUiText.cpp. Its existing ZH Scripts.cpp
provenance and BFME2 target-specific warning/disabled state, twelve parameter
slots, string calls and layout remain unchanged. No additional original-name
or layout inference is claimed.

The whole 285-byte getUiText method at 0x003B54DC and complete native
associative EH graph are EXACT. The graph identifies the 19-byte cleanup
0x007823E9 ($L1232) for twelve four-byte AsciiString locals at EBP-0x54.
The full bytes are 6839ba88006a0c6a048d45ac50e8156deaffc3. Its destructor
0x0048BA39 and CRT vector iterator 0x00629110 relocations resolve exactly.
This complete parent evidence supersedes the old unproven-parent verdict.

The same graph identifies the existing 25-byte MASM extent 0x00782404
($L1234), emitted by the actual C++ return-value lifetime. It tests and clears
bit 0 at EBP-0x24 and destroys the return object through EBP+8. Full bytes:
8b45dc83e0010f840c0000008365dcfe8b4d08e91d96d0ffc3. Its conditional target
$L1236 is the final RET at 0x0078241C, inside this existing 25-byte extent;
no extra overlapping row is claimed. The MASM source remains untouched.

Other graph siblings 0x007823E1 and 0x007823FC already have generated C++
rows. The installed 10-byte handler 0x0078241D is already owned here.
verify.py independently checks the full parent, full graph, both cleanup
extents and all relocations, the 5-byte AsciiString destructor, the complete
133-byte narrow StringBase releaseBuffer and its existing folded destructor
with native EH graphs, and the complete 96-byte CRT archive member.
These existing providers add no new coverage.

Normal builds verify the owning source, both string provider units and CRT
member. Frozen-file inspection passes; before/after code identity audits
must remain empty. No source, header, compiler flags, pins, aliases or
identity baseline changed. This is compiler-emitted C++ recovery; no fresh
linking result is claimed. Run normal build.sh on those inputs before replay.
