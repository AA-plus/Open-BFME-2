# Apt timeline base and record cleanups

The entire source is
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLineCtor.cpp`.
The complete 540-byte constructor at 0x005202C8 and 224-byte destructor at
0x005204EF both verify EXACT, including their full native associative
exception graphs. The destructor graph directly locates two complete bodies:

* 0x00796102, 8 bytes, $L5805: saved receiver EBP-0x10 tail-jumps to the
  existing 90-byte _bfme_AptGameWindow destructor at 0x005126F5. Complete
  bytes: `8b4df0e9ebc5d7ff`.
* 0x00796126, 14 bytes, $L5808: the same receiver plus 0x2C4 tail-jumps to
  the existing 63-byte Rva0051C0E7 record destructor at 0x0051E471. Complete
  bytes: `8b4df081c1c4020000e93d83d8ff`.

Both Ghidra extents and every byte/REL32 target agree. The proof script checks
both whole parents, both full exception graphs and both complete cleanups;
location is not inferred from adjacency or a masked placement.

The source already identifies the timeline screen from WorldBuilder's
AptTimeLine constructor, image literals and singleton behavior. That existing
identity evidence is retained; the legacy Rva005202C8 spelling is unchanged.
The +0x2C4 member's 48-byte record layout and teardown relationship are already
recorded with its owned constructor/destructor, while its original record name
remains unknown. The two initial cleanup rows preserve the source. A subsequent local repair,
described below, reconciles its vector element extent and destructor provider.

The normal whole-source gate verifies the two STLport constructor folds,
five string literals and one floating literal. Run it before replaying
`verify.py`. The saved census 6963cc017c does not include this source, so the
link preview cannot establish placement. No linking gain is asserted and no
linking runner was started.

The normal hook exposed an older divergent vector-destructor copy and a
shadow binding warning on its folded vector-base constructor. Native
Destroy/fill helpers at 0x005200F4 and 0x00520211 step by 0x50, and the owned
element destructor at 0x0051FB52 uses fields through +0x44. The local element
view now reserves those 80 bytes and declares the already owned vector
destructor at 0x0052012B as an explicit specialization, avoiding the divergent
local definition. All nine rows and both complete parent graphs remain exact;
the existing provider FamilyVectorDtors_new.cpp separately verifies 10/10 rows.
This does not reconcile every private element view in the repository.

The remaining vector-base constructor is independently verified as a complete
29-byte body at 0x00211E58 with resolved allocator-proxy relocation. This proof
is now replayed in verify.py, in addition to the normal gate's fold proof.
The shadow identity detector's binding diagnostic is preserved for tooling
review; no new pin, alias row, baseline exception or suppressed check is used.

The data ledger assigns RVA 0x00A04920 to `?g_Va00E04920@@3IA`,
owned by Rva007B6880Thunks.cpp. The timeline now declares that existing
unsigned global and casts its address to the local vector view at each use.
This removes the second typed data symbol while preserving all nine bodies
and both exception graphs. The ledger owner is provisional; this repair
does not establish the original global type or reconcile other users. A local
reference temporary changed instruction selection and was discarded; direct
casts preserve the complete 224-byte native destructor.
