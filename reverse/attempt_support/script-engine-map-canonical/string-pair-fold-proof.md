# Existing string-pair aliases

The nonconst `pair<AsciiString, AsciiString>` constructor at 0x0002C4FD
(57 bytes) and destructor at 0x0002C0C0 (53 bytes) retain their existing
names and addresses. Their previous notes recorded call-site evidence;
this repair adds formal `fold-proof` evidence without adding a pin.

`tools/pin_admission.py` proved each complete body and every owner row's
relocations, including the associative exception-handling graph. The
constructor proof uses the kept copy in ScriptEngineRva0020881A.cpp;
the destructor proof uses the kept copy in StringRecordInlineCopyBFME2.cpp.
Using a different byte-identical copy is insufficient evidence for the
kept definition's exception-handling bindings.

These proofs reconcile existing template identities. They do not establish
the target's original typedefs or repair the separate TeamLess insert_unique
conflict in the banked team-alias recovery at 0x00208BCD. No source, calling
convention, address, retail extent, or pin count changes here.
