# AI exit flag ownership repair

Base: `f05ed084e933d2b3d2bd057519f28df71fec5afa`.
The three claimed units in `sources.txt` all referenced the undefined
`?g_00E03624@@3_NA`. Define one `BfmeAIExitDoorFlag` bool in
AIExitStateMethods.cpp, record its one-byte retail storage in data_rows.csv,
and bind all three units to it. This is a descriptive identifier; the original
retail name is unknown. Existing function identities and state layouts remain
as established in the matched rows.

Target evidence in retail-operands.txt and the object snapshots:

- AIExitState::update at 0x00341B4E publishes its saved byte immediately
  around exitObjectViaDoor and then clears the global.
- AIHordeExitState::update at 0x003462E1 performs the same publication/clear
  at two exit paths; the setter at 0x0033F9AA writes one byte there.
- All seven DIR32 sites have zero object addends and retail VA 0x00E03624.
- This address is in the virtual zero-fill part of retail .data: section RVA
  0x009A4000, raw length 0x0003A008, virtual length 0x0007F314, flag offset
  0x0005F624. Its initial mapped byte is zero. The data gate independently
  proves compiled bool sizeof1 and initial bytes. Adjacent storage is not claimed.

Acceptance and limits:

- `link_check.py --prepare-current --paths-from sources.txt` passed before
  and after for all three explicitly owned units: 112/112 matched functions,
  ten float literals, and after the change one verified data row. Both sets
  of objects have strict reusable compiler receipts.
- `./build.sh` on each source passed 112/112 functions in total, all literal
  and import checks, and the data row. comparison.txt proves every complete
  body hash/extent is unchanged and every relocation is unchanged except
  the seven flag symbol spellings. No new C++ code coverage is claimed.
- `place_bodies.py` rescanned all three affected units and found no new
  bodies or pins (placements-after.txt).
- Local `link_check.py --paths-from sources.txt` removes exactly one undefined
  flag finding in each of the three units, with no new link findings.
  This uses current scoped objects and refreshes their definitions in memory.
  It is a legacy preview against the unchanged index at `cb660e4d97`,
  2026-10-13 04:02; hash in comparison.txt. Committed link_status was measured
  at `e181b4b6c5`, 2026-10-13 11:22, and is used only for discovery.
  The three-unit preview stays 0/3 accepted and LINKED 0 -> 0 bytes.
  Strict self byte verification is proven; self-strict LINK closure and
  closed-strict gains are unmeasured. No actual link.exe gain is asserted.
- Enforced converged-data check: three sources, eight addresses, zero second
  names and zero unjudged rows. Declared-definition, class, CSV integrity
  and diff whitespace checks pass. No compiler setting, alias, pin, private
  class, marker, baseline or verifier code is added. Current hatch counters
  report no count growth (their pattern does not count the old g_00E03624).
- The shadow checker uses the older inferred data_ledger.csv, whose flag row
  is still the unowned old name with zero definitions. It now prints three
  expected wrong-name findings for the new byte-verified owner, plus two
  unrelated pre-existing GapBodiesSeat1B findings. The reconstructed before
  comparison and the exact limitation are in shadow-data-comparison.txt.
  No baseline is extended or generated inventory hand-edited.

Remaining link findings are preserved in link-after.txt: AIExitState has
getID/getCurrentStateID COMDAT copies; AIHordeCowerStateSlots has the missing
AICowerState::onEnter and getGoalPosition COMDAT; GapBodiesSeat1B has two
unresolved methods and a selected non-retail BitFlags::countIntersection.
These are independent of the flag ownership repair. No full link cycle,
census build/measure/history, nightly or boot operation was started.

Reference review: retained verified BFME1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; reviewed ownership repair
`0835ab92bef30e3303e729a0ce09cf591368d0cd` and provider-view repair
`1926a8216469e2ed59c96901e5f0ba6905f734db`. Their single-owner principle
applies; donor types, addresses and bodies are not imported. The new storage,
size and usage are established from BFME2 retail and current objects.
Official BFME1 master fetched as `61eff927bb71d52854f461c9eeba2a731d679b1e`.
The overdue pointer update remains foreign-claimed by codex-a44d-root
(file:reference/open-bfme-1); verified inputs and the success stamp are retained.
