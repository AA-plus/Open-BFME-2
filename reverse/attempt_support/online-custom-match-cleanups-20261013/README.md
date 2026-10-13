# Online custom-match destructor cleanups

Read the whole AptOnlineCustomMatchDtor.cpp and the three external destructor
provider files. Existing target vtable slots, callers and callback strings
establish the owning AptOnlineCustomMatch identity; body access and destructor
calls establish its base/member relationships. Address-derived base names and
remaining layout-view uncertainty are preserved. Upstream has already named
the +0x70 member AptMpGameSetup; this change introduces no identity rename.

The entire 195-byte destructor at 0x005A0009 and complete native associative
exception graph are EXACT. All four selected Ghidra-bounded cleanups compare
strictly over every byte and relocation, with no unresolved names:

- 0x0079DC53, 8 bytes, $L1346: saved EBP-0x10 pointer to the 11-byte
  screen-base destructor at 0x0056DC6B.
- 0x0079DC83, 11 bytes, $L1349: member +0x70 to the 211-byte
  AptMpGameSetup destructor at 0x004421E1.
- 0x0079DC5B, 20 bytes, $L1347: nullable +0x60 secondary-base adjustment
  using NEG/SBB/AND, to the 25-byte destructor at 0x004444D2.
- 0x0079DC6F, 20 bytes, $L1348: nullable +0x6C secondary-base adjustment,
  to the 7-byte inline-interface destructor at 0x0059EB3A.

The latter two bodies were MASM ledger rows. The 0x0079DC5B row is repointed
to the owning C++ source with add_match --replace-existing; its orphaned MASM
text is untouched. The 0x0079DC6F row remains MASM for the blocker below. Their native parent and base relationships are now proved
through the whole graph. No naked function, asm, emit, new pin or alias is used.
The existing folded Rva0059EB41 destructor pin already cites its constructor
unit as fold proof; the current destructor object independently emits the full
7-byte vtable-store/return twin. This adds no second owner at that address.

All four provider bodies compare strictly; AptMpGameSetup's complete native
EH graph is also EXACT, while the three other providers have no EH graph.
Normal external provider builds pass 2/2, 8/8 and 3/3 rows respectively.
The before/after identity audit retains one pre-existing divergent deleting
destructor finding for Rva0059EB41; the three accepted rows introduce none. Do not claim
identity-clean linking. The old local census has no entry for the owning file.

Three other 14-byte graph siblings (0x0079DC8E, 0x0079DC9C, 0x0079DCAA)
already have generated C++ rows. The 10-byte installed handler at 0x0079DCB8
is already rowed. Frozen-file inspection passes and place_bodies finds no
incidental ordinary bodies or pins. No source, header, layout or flag changes.

Before verify.py, run normal build.sh on the owning source and the three
provider sources named in the replay. The three accepted bodies are banked
as separate commits.

The fourth body (0x0079DC6F) is NOT banked as C++. Its attempted row exposes
an additional wrong/unknown binding for Rva0059EB41 destruction at 0x0059EB3A.
The existing fold pin names the constructor object, while the identity tool
keeps the destructor object. Testing an updated proof against the actual kept
object through pin_admission.fold_proof_problems refuses it: only three
non-relocation bytes, below the fold-proof minimum, with no tail-jump callee.
Whole 7-byte equality is therefore insufficient admission evidence under the
current rules. Keep the native body and diagnostic replay, withdraw the row
and its hatch grant, and require proper owner/type reconciliation or a
separately justified tooling change. No name, alias or check workaround is
introduced. The pre-existing deleting-destructor divergence also remains.
