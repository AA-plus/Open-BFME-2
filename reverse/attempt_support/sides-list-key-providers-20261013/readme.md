# SidesList dictionary-key providers

Base: `3a60dcf23b3144c9a5dc51350b1c570fa31cf467`.
Available census index: `cb660e4d97`, 2026-10-13 04:02 UTC.
The committed link-status measurement `3906ea7b97` supplied queue leads;
no per-row data-back artifact was used for ranking.
Neither index nor link status was rewritten.

The current SidesList addPlayerByTemplate unit had eight unresolved globals
when checked alongside its already-defined playerFaction cache provider.
Reuse the existing const StaticNameKey teamName/teamOwner owners through the
target-proven lazy-cache view, and the existing teamIsSingleton owner.
Define the four missing player caches under the names already referenced by
PlayerListRva002A8008 and GameLogicInit. Define the sixteen-byte Neutral
display string in this consumer. Five data_rows entries verify their ownership.
There are no new function rows, pins, aliases, header changes or compiler flags.

Target evidence: get148F5E reads/writes the key at +0 and reads the string
pointer at +4. Each of the four data cells is independently read as eight
bytes {0, pointer to its complete player key string}. The existing native
addPlayerByTemplate32DE04 passes each cell to that getter before its relevant
Dict setter. Its empty-template branch passes C0DA78 to UnicodeString::set;
the sixteen native bytes encode UTF-16 Neutral including the terminator.
The previous comment calling this display string empty was incorrect.
Compiled sizeof probes, initial bytes and every initializer relocation pass
the data gate. target-and-relocations.txt records all eight renamed code
relocations, unchanged sites/types/addends, and their retail VAs. The complete
527-byte emitted function is identical before and after, including bytes at
relocation sites. The separate EH-handler row passes its own normal byte gate.

Donor facts: the verified BFME1 pointer
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 has the same dictionary-key semantics
and Neutral branch in game/GameEngine/Source/GameLogic/Map/SidesListAddPlayerByTemplate.cpp.
The TheKey names are carried from that ZH/BFME1 source and existing BFME2
declarations; original BFME2 identifier spelling is not independently proved.
SidesListNeutralDisplayName is descriptive. BFME1 linking repair
1926a8216469e2ed59c96901e5f0ba6905f734db was reviewed: naming an existing datum
through a local view is applicable to the two team keys. BFME2 addresses,
layout and bytes were verified independently. Official BFME1 master was
fetched at c54240071; a foreign file:reference/open-bfme-1 claim blocks its
freshness update. The verified checkout pointer and old success stamp remain.

Acceptance: build.sh passes both matched functions and all five data rows.
Bounded link_check --prepare-current passes the repaired unit and existing
playerFaction provider: 11/11 functions, five data rows, four code literals
plus two empty-string references, no baselined or skipped references, and
strict reusable receipts for both explicit units. check_csv, data_rows --check,
data_rows --verify, find_declared_unmatched and git diff --check pass.
The enforced converged-data check reports zero second names or unjudged rows.
The shadow data-name check reports the two existing playerName/playerFaction
aliases and the descriptive Neutral symbol against the old inferred inventory
name g_00C0DA78; its new sixteen-byte ownership row fully verifies. No baseline
or verifier was changed to suppress those findings.

With the same explicit provider cohort and historical census index, the
ordinary local preview changes from 1/2 clean (254 bytes) to 2/2 clean
(781 bytes): 527 existing authored C++ bytes newly link cleanly in this
preview. Additional previews remove three unresolved key names from PlayerList
and four from GameLogicInit; those units retain unrelated unresolved,
duplicate, COMDAT and selected-provider blockers and gain zero clean bytes.
The current explicit objects are self-strict. Other dependencies retain the
historical index's evidence, so this is a legacy preview, not closed-strict
closure or link.exe/data-back placement. A broader link cycle remains a
maintainer-only check. New authored C++ bytes: zero; new verified owned data:
48 bytes.
