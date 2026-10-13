# List-box image helper link repair, 2026-10-13

BFME 2 base `77d609523c` uses a local legacy census index measured at
`d753dedd98` (2026-10-12 22:16). The committed status serving the repair
queue instead measures `e956901d31`; it is discovery evidence, not the
before/after measurement below. No census/status or data-back artifact changed.

The system callback's sole current blocker was an unresolved addImageEntry.
The ledger already owned its complete 270-byte body at `00324D84..00324E92`,
but the separate Rva00324D84Permuted.cpp defined it static and used a
synthetic forceAIE wrapper to emit it. Move that existing static body beside
its actual GadgetListBoxSystem caller; delete the obsolete unit and wrapper.
The complete 3111-byte callback (including its switch table) and helper
remain exact under the consumer's existing flags. No new pin, alias, header,
compiler setting, function boundary or instance-layout claim is introduced.

Target facts: the callback REL32 relocation at +674 reaches RVA 00324D84.
The helper's zero-addend DIR32 sites +10/+B5 bind the existing canonical
GlobalData and DisplayStringManager pointers at DFE758/DFEAD8. It reads
resolution at +30/+34 and uses the consumer's existing 28-byte cell layout;
only the local unknown04 spelling is reconciled. Relocation proof and full
byte gates independently confirm the target addresses and complete bodies.

Donor review: verified BFME 1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
keeps addImageEntry static in game/GameEngine/Source/GameClient/GUI/Gadget/
GadgetListBox.cpp (lines 554..602). Static linkage and the helper's purpose
are applicable; donor resolution +2C/+30 is inapplicable and remains replaced
by target evidence. Existing target provenance is retained. Reviewed donor
canonical-data repair `0835ab92bef30e3303e729a0ce09cf591368d0cd`: its naming
principle applies to the GlobalData access view; its Apt pool types do not.
The official freshness fetch advanced remote master to 40514c612; the clean
verified checkout remains cee35b7d8 because another worker holds
file:reference/open-bfme-1. No freshness-success timestamp was advanced.

Acceptance:

- add_match --replace-existing repointed the existing helper row only after
  the consumer's full byte gate passed 2/2 rows on the first attempt.
- Bounded prepare-current checks accept the consumer and unchanged direct
  GameWindow_winGetUserData and GadgetListBoxComputeTotalHeight providers:
  5/5 rows byte-exact, strict reusable receipts. Both changed bodies also
  satisfy object_current(..., allow_fresh=False). Sources remain tracked.
- Local link_check checks the consumer and both providers together: all LINKS.
  Before, helper 270 + consumer 0 + unchanged providers 302 = 572 bytes;
  after, consumer including helper 3377 + providers 302 = 3679 bytes.
  **Legacy preview gain: 3107 existing authored bytes**, accounting for the
  helper moving between units. New authored C++ bytes: zero.
- Frozen-file check accepts the consumer before and after; converged-data
  check: three sources, eight addresses, zero second names/unjudged rows.
  check_csv and git diff --check pass. Normal commit and push hooks required.

The scoped objects are self-strict. Transitive closed-strict closure and an
actual link cycle remain unmeasured; no strict linked-counter gain is claimed.
No full census, link cycle, nightly or boot runner was started. Terrain's
independent unresolved 2158-byte rectangular helper remains out of this repair.
