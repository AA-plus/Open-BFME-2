# Online NAT singleton binding repair, 2026-10-13

Seven online/Apt consumers replace the unowned
`?g_Va00E063F8@@3PAVRva005A6D47@@A` with the existing data-row owner
`?TheNAT@@3PAUNAT@@A` at retail VA `0x00E063F8` (RVA `0x00A063F8`).
The owner remains `NATProcessGlobalMessage.cpp`; consumers declare
`struct NAT; extern NAT *TheNAT` and cast to their existing access views.
Three existing NAT declarations change from class to struct to match the
owner's decoration, keeping their explicit public access and members.
No new datum, layout, alias, pin or ledger claim is introduced.

Base: `ad4e667c4e931128f4cf94bd8144fb5d9626e259`. The actual restored census
index measures `d753dedd98`, dated 2026-10-12 22:16 (`index-meta.json`).
The committed link-status measurement differs; comparisons here use the
same eleven explicitly witnessed units before and after. `sources.txt`
names the seven changed files, and `cohort.txt` includes the unchanged
provider and three existing canonical consumers.

Target evidence: the matched data row owns this pointer under `TheNAT`.
NATProcessGlobalMessage loads this slot before attachSlotList; the existing
OnlineCustomMatch and QuickMatch constructors construct the negotiator and
store it through that owner. Existing canonical consumers independently use
the same slot with local access casts. The relocation transcripts enumerate
all 43 matched executable DIR32 operands reaching VA `0x00E063F8`, before
and after, with zero addends. Every operand now binds the canonical key;
the existing provider is the only strong data definition in the cohort.
Object SHA256 values are included. These observations support datum binding;
the unchanged byte gate establishes body equivalence. No new original-source
identity or class-layout inference is claimed.

Donor review: verified BFME1 `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Repair `0835ab92bef30e3303e729a0ce09cf591368d0cd` binds Apt pool consumers
to the existing owner-typed extern and casts at use sites; the related
repair `908413c254f83e1f402b991541d4cf68db48ea4e` was also reviewed.
The binding principle applies; donor types, addresses and layouts do not.
Official BFME1 master was fetched at
`dbd5156f9e5c22ae7fc5047994fdb2143c08a83f`, newer than the verified pointer,
but `file:reference/open-bfme-1` is held by `codex-a44d-root`. The verified
pointer and prior success timestamp remain unchanged; update verification
remains with that worker. No donor source or header is imported.

Acceptance and improvement:

- Before: `link_check.py --prepare-current` on the seven consumers and four
  peers verifies 84/84 code rows and one data row with strict reusable self
  receipts. After: the same preparation on all eleven units verifies the
  final objects (`prepare-after.txt`).
- `./build.sh` on the eleven explicit sources passes: 84/84 code rows, one
  data row, 150 literals, 31 empty-string references, three floating literals
  and 18 named imports. There are no baselined or skipped literal references.
  Three renumbered funclets are resolved through verified parent EH data.
- The relocation and receipt assertions in `proof-summary.txt` verify all
  43 canonical operands, one owner, and 11/11 current strict full-gate
  receipts with `allow_fresh=False`.
- Ordinary `link_check.py --paths-from cohort.txt` removes exactly seven
  unresolved NAT references and adds no blocker; all independent blockers
  remain unchanged (`link-delta.txt`). The local legacy preview stays 2/11
  clean and 1,998 -> 1,998 linked C++ bytes. Its exit 1 reflects the remaining
  blockers, not failure of this binding repair.
- `data_check.py` on the changed sources falls from 15 to eight shadow
  findings, all outside the baseline: the seven NAT findings disappear.
  Enforced `--converged` on the whole cohort checks eight registered
  addresses with zero second names and zero unjudged rows.
- Hatch occurrences in the changed files fall 69 -> 17, with no counter
  growth. Declared-definition, CSV, case-collision and whitespace checks pass.

The improvement is verified data binding and seven fewer unresolved symbols,
with zero new authored C++ bytes and zero additional clean-unit linked bytes.
The receipts establish self-strict currency. Definitions outside the explicit
cohort still come from the restored legacy census; no closed-strict gain or
new census measurement is claimed. Full link cycles, nightlies and boot
verification remain maintainer work.

Remaining blockers are listed in both link transcripts: STL string/list/map
COMDAT disagreements and wrong selected definitions, listener/vtable helpers,
the NAT helper methods, tooltip text/rank globals, and independent GameSpy,
ladder, message-stream and Apt globals. The eight remaining data findings
concern those independent globals. No protected baseline or gate code changes
are included.
