# Radar/planning singleton link repair, 2026-10-13

Base: `80bcbb5a078ff6009a2e9d8fea9d16c0fde455f7`. The restored census index
measures `d753dedd98` at 2026-10-12 22:16. Its recorded state is older than
this checkout; the same explicit ten-source local preview is used before and
after. No census/status/history or full link cycle was run.

## Target evidence and change

The data ledger assigns RVA `0x009FF028` (VA `0x00DFF028`) to
`?theRadarWindowOverrideSource@@3PAVRadarWindowOverrideSource@@A`.
`UiCallbackFirers.cpp` provided that datum as `TheRva002D3627Host`, while
ScriptActions referenced it as `ThePalantir`, ScriptGlue as `g_00DFF028`,
and BfmeConv485 as `g_bfmeSinkBLD`. Two canonical-name linker aliases and
one BfmeSink alias bridged some consumers; the other two names remained
unresolved. These are spellings for the same target slot, not separate data.

The provider and all executable uses of those four old spellings now use the
ledger's one global and its exact class-pointer decoration. Existing per-unit
views are retained at use sites with casts. The audio unit's existing radar
view uses `class` with public members rather than `struct` so its global has
the canonical class-pointer decoration. Its layout and access stay unchanged.
The three aliases are removed. No pins, ledger rows, baseline entries or
shared headers are added or altered.

Retail DIR32 operands and object addends are recorded in `relocations.txt`.
They establish the shared target address; byte verification establishes the
unchanged bodies. The existing ScriptActions evidence identifies the planning
operation from WorldBuilder assertions, while the factory writes the same
singleton and GameState snapshots it as CHUNK_Palantir. The canonical global
name comes from the existing data ledger; this repair does not claim a new
retail class layout or original source-level spelling.

## Donor review

The verified BFME 1 pointer reviewed is
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Donor repairs
`0835ab92bef30e3303e729a0ce09cf591368d0cd` and
`908413c254f83e1f402b991541d4cf68db48ea4e` respell Apt pool externs to
one owned data-row type. That approach applies here; their Apt addresses,
types and function bodies do not. No donor body or donor layout is imported.
`5093777e8373a843f1f1ccfc648601ae78351aaa` concerns a ShareBufferClass
shader-destructor repair and is inapplicable to this singleton.

The overdue upstream freshness check fetched official BFME 1 master at
`0204cb9c941f0152bf17a89a0a4185363d6239d8`, but another worker holds
`file:reference/open-bfme-1` (`codex-a44d-root`). The checkout and verified
pointer were preserved and the success timestamp was not advanced. Pointer
verification/update remains with that owner; no unverified headers were used.

## Acceptance and limits

Before preparation: 74/74 matched rows in ten explicit sources passed the
normal byte gate with strict reusable self receipts, including 96 literals,
four empty-string references, four compiler floats and three named imports;
no literal baseline, skip or unverified reference was used.

Before local legacy preview: 6/10 units, 3,202 existing C++ bytes link cleanly.
ScriptActions' sole blocker is the unmatched ThePalantir datum. ScriptGlue
has that same slot under another name plus an unrelated GameLogic method.

After: 74/74 rows again byte-match, including every string, float and import
reference; both groups have fresh strict reusable receipts. The legacy local
preview now reports 7/10 units and 6,504 linking bytes, a gain of 3,302 existing
C++ bytes entirely in ScriptActions. ScriptGlue loses its singleton unresolved
reference but retains its independent GameLogic blocker. The other consumers'
LINKS verdicts and independent blockers remain unchanged. Exit 1 from the
cohort link preview is expected because those three units still fail.

Data-name shadow findings shrink from 11 to two: all nine singleton findings
are removed, leaving only the two pre-existing GameStateInit findings. The
converged-address enforced check passes (eight registered addresses, zero
second names and zero unjudged rows). The new singleton is not added to that
protected list. Relocation inspection proves 17 canonical DIR32 references,
all with zero addends and retail VA 0x00DFF028, exactly one strong canonical
definition in the witnessed objects, and no old spelling in their symbol
tables. Escape-hatch counts in these sources fall 20 to 17 (three aliases);
no counter grows. CSV, declared-definition, case-collision and whitespace
checks pass. No new authored bytes or measured census gain is claimed.

The first ten-source byte-gate invocation was stopped while still waiting on
the host full-build lock, before compiling. Sequential groups of five then
completed the normal gates; no parallel or duplicate build was started.

Reproduce with the paths in `sources.txt`: `./build.sh` on each five-source
group; `tools/link_check.py --prepare-current` on each group;
`tools/link_check.py --paths-from sources.txt` for the cohort preview;
`tools/data_check.py` and `tools/data_check.py --converged` on those sources.
Before/after transcripts and index metadata accompany this record.
Strict receipts establish the touched units' own byte proof (self-strict).
The local link preview uses the restored census for other definitions
(legacy), and does not establish transitive provider closure (closed-strict).
No closed-strict gain or full-link/data-back result is claimed.

Remaining independent blockers in this cohort: Object::setDisabledUntil and
hard-coded VA 0x00E01DB0 in ScriptActionsRva003BAAD6; GameLogic::rva0023D68E
in ScriptGlue; Rva001D96ECLeaField::get and four STL COMDAT conflicts in the
audio unit. GameStateInit also retains pre-existing data-name findings at
RVA 0x009FE750 and 0x009FE754. These need separate repairs and are not retried
as part of this singleton change.
