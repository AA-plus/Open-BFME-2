# NetPacket folded setter link repair

At BFME2 `7637b24870`, the local census index measured at `d753dedd98`
(2026-10-12 22:20 UTC) reports one NetPacket blocker:
`?setCurrentTask@DozerAIUpdate@@UAEXW4DozerTask@@@Z` is unresolved.
The committed historical link status has a different measurement commit,
`b3f2efabf3`; the before/after acceptance below uses the actual local index.

Target facts: the complete 143-byte factory at RVA `0058DFB8` allocates
0x24 bytes, calls the rowed `Rva004D580E` constructor, copies one byte and
one dword from the packet, and calls RVA `00317B9B` at `0058E032`.
The complete ten-byte callee moves its dword argument to receiver +0x20
and returns with RET 4. The ledger owns that body as
`BFMENetInformPlayerLeaveFrameCommandMsg::setLeavingPlayerID` in
`NetCommandMsg_ctors.cpp`. NetPacket already declares and calls that owner
for its other +0x20 message fields. Its former Dozer spelling establishes
neither a Dozer receiver nor an enum payload.

Change: bind this call to that existing setter provider, keep the unsigned
dword payload as `voteFrame`, and remove the unused private Dozer declaration
and enum. No new definition, pin, alias, class layout, global, flags or extent
is introduced. The signed parameter cast preserves all payload bits under
the target MSVC ABI, as verified across the entire caller.

Donor review: committed BFME1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
contains `game/GameEngine/Source/GameNetwork/NetPacket.cpp`'s
`readDisconnectVoteMessage`: byte slot followed by unsigned vote frame.
This supplies the payload meaning; BFME2's existing type-27 constructor
and `DisconnectManager::sendVoteCommand` row independently support the
relationship. It does not establish an original name for the factory.
BFME1 repair `ea2b7600f0bcf1b1543851be0f1ae12a23125849` likewise removes
a private alias spelling in favor of an already matched member provider;
the direct-provider repair principle applies, while its ThingFactory ABI
does not apply to this message.

Acceptance:

- `./build.sh NetPacket.cpp NetCommandMsg_ctors.cpp` with the full paths:
  152/152 rows exact, source claims, STLport fold, strings, floats and imports
  pass. This includes all 150 NetPacket rows and both setter-provider rows.
- `link_check.py --prepare-current` for both full paths passes the same
  ordinary gates using strict reusable receipts. A separate
  `object_current(..., allow_fresh=False)` check is true for each unit.
- Ordinary local `link_check.py` checks provider and consumer together.
  Before: NetPacket unresolved, provider LINKS. After: both LINKS;
  NetPacket's preview changes from 0 to 27,978 real bytes and the provider
  remains 27 bytes, for combined 27 -> 28,005. The attached logs preserve
  the actual commands' results.
- `find_declared_unmatched.py NetPacket.cpp` accepts every definition;
  `check_csv.py` and `git diff --check` pass.

The objects are self-strict. The link result is a local preview against the
legacy census index; strict transitive closure and a new census or full link
cycle were not measured. No closed-strict gain or tracked LINKED counter
change is claimed. No maintainer-only runner was started.

Reference freshness: official BFME1 master was fetched at
`776b7ccef030f6345c97861dbd35f5319184ba15`. The clean committed `cee35b7d8`
inputs remain in use because `file:reference/open-bfme-1` is held by
`codex-a44d-root`. No pointer update or successful freshness stamp was made.
