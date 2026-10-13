# Collision singleton binding repair, 2026-10-13

Four consumers now bind retail RVA `0x009FE754` (VA `0x00DFE754`) to the
existing data-row owner `?TheCollisionManager@@3PAVCollisionManager@@A`
in SubsystemSingletonPointers.cpp. CritterEmitterUpdate's duplicate
`void *g_Va00DFE754` definition is removed. Object unregistration and
GameState initialization replace that spelling with the owner-typed extern;
GameLogic::getCRC replaces `g_00DFE754` with the same owner. Local access
views and Snapshot base adjustments remain unchanged.

Base: `b38bbfa35b743cc2cd603dbad24283131d315fbc`. The actual restored census
index measures `d753dedd98`, dated 2026-10-12 22:16. The committed link-status
measurement differs, so gains below use the same eight-object local preview
before and after, including all seven collision-slot consumers and the
unchanged singleton provider. `sources.txt` names the four changed sources;
`cohort.txt` names the complete witnessed cohort.

Target evidence: the existing matched data row identifies the slot and its
owner; GameLogic initialization constructs and registers it under
`TheCollisionManager`, and GameState registers it as `CHUNK_Collision`.
The relocation transcripts enumerate all 14 matched executable DIR32
operands reaching VA `0x00DFE754`, with zero addends, before and after.
Every operand now binds the canonical decoration. The witnessed objects
previously defined two separate data symbols for this native slot; only
the existing canonical provider remains. The transcripts include object
SHA256 values. The byte gate independently establishes unchanged bodies;
this change makes no new class-layout or original-source-name claim.

Donor review: verified BFME1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Repair `0835ab92bef30e3303e729a0ce09cf591368d0cd` respells Apt pool externs
to the existing data-row owner and casts to local access views. That binding
pattern applies; its Apt types, addresses and layout do not. BFME1's
`game/GameEngine/Source/Common/System/SaveGame/GameStateInit.cpp` also
registers collision snapshots through `TheCollisionManager`; target
registration and base adjustments were checked independently. No donor
body or layout is imported. Official BFME1 master was fetched at
`f21f46187659e887a9cf5aac93a2392d93734c44`, newer than the verified pointer,
but `file:reference/open-bfme-1` is held by `codex-a44d-root`. Verified inputs
and the success timestamp are preserved; pointer-update verification remains
with that worker.

Acceptance and improvement:

- `link_check.py --prepare-current --paths-from cohort.txt` before and after:
  102/102 matched code rows and 14 data rows pass ordinary byte gates with
  strict reusable self receipts for all eight units. All 117 literals, nine
  empty-string references, three floating literals and eight named imports
  pass, with no baselined or skipped literal references. Renumbered local
  funclets resolve through verified parent EH data.
- `./build.sh` on the eight explicit sources passes the ordinary byte gate;
  `byte-gate.txt` records its output.
- Ordinary `link_check.py --paths-from cohort.txt` removes exactly one
  unresolved reference (`?g_00DFE754@@3PAVCollisionManager@@A`), adds no
  blocker, and preserves all other results. The preview remains 3/8 clean,
  2,174 -> 2,174 linked C++ bytes; its exit 1 is expected for remaining
  independent blockers.
- `data_check.py` on the four sources: six -> two shadow findings,
  four -> one outside the baseline. All collision-slot findings disappear.
  `data_check.py --converged` checks all eight units against eight registered
  addresses: zero second names and zero unjudged rows.
- Hatch occurrence counts in the four files fall 26 -> 18; no counter grows.
  Declared-definition, CSV, case-collision and whitespace checks pass.

The verified repair improves data binding and removes an unresolved reference
without new authored C++ bytes or clean-unit linked bytes. The receipt proof
is self-strict; the local link preview uses legacy census definitions outside
this cohort. No closed-strict gain, new census measurement, full link cycle,
nightly or boot result is claimed. No ledger, pin, protected baseline, header
or gate code changes are included.

Remaining blockers: GameLogic::getCRC needs `g_00E02D81`; Object unregistration
needs the Lua/AI helper providers `rva00333F37` and `rva002A8F56`. The unchanged
GameLogic initialization/destructor and ObjectRva0028DCC4 retain their other
helper, key-global, duplicate and COMDAT blockers listed in both link logs.
The remaining two data findings concern the CRC debug slot `0x00A02D87`.
Broader link/data-back verification still requires a maintainer runner.
