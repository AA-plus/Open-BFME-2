# ProgressIndicator head ownership repair

Base: `35abcca2aeebaef5977a6d006d2342214f17017c`.
The three claimed units in sources.txt reference the undefined
`?g_00E01E1C@@3PAVProgressIndicator@@A`. Bfme5TinyTen.cpp now owns one
`BfmeProgressIndicatorHead` pointer, with four-byte verified storage in
data_rows.csv. All consumers use that symbol, including the destructor that
previously dereferenced an absolute-address macro. The identifier describes
the observed behavior; retail's original global name is unknown.

Target evidence and verification:

- The base constructor at RVA 355C60 saves the old head at this+4 and publishes
  this. The destructor at 355C77 restores this+4 only when this is the head.
  The terrain body at 0E10C0 reads the head and calls its virtual slot +4.
  The before/after snapshots record every head DIR32 site, zero object addends,
  and native VA E01E1C. Renaming adds two destructor relocations without
  changing its resolved bytes. There is one definition and no old-name source
  consumer left.
- The four initial bytes at RVA A01E1C are loader zeros in .data. The section
  starts at 9A4000, raw length 3A008, virtual length 7F314; this slot lies in
  the zero-filled tail. The data-row gate independently verifies the pointer's
  compiled size and initial bytes; adjacent storage is not claimed.
- `./build.sh` on the three units passes all five matched rows and one data
  row, plus float, string and import checks. `link_check.py --prepare-current`
  passes before and after, establishing strict reusable receipts for the three
  explicitly owned providers. comparison.json covers 295 bytes of row extents
  (294 non-padding bytes). Bound body bytes are unchanged; no new C++ coverage
  is claimed. Declared-definition, CSV, class and converged-data checks pass.
  The placement rescan finds no incidental bodies or pins; hatch counts have
  no growth (placements-after.txt and hatches.json).
- Local `link_check.py` removes one unresolved head finding from each unit and
  one hard-coded-address finding from Bfme5TinyTen. This is a legacy preview
  using current scoped objects against the unchanged census index measured at
  d753dedd98, 2026-10-12 22:16; its hash is in comparison.json. Committed status
  at 67e1365aa9 is discovery evidence only. The preview remains 0/3 accepted,
  LINKED 0 -> 0. Strict self byte verification is proven; self-strict link
  closure and closed-strict gains are unmeasured. No link.exe gain is asserted.
- The shadow data checker retains an older unowned inventory name typed as
  Gen_004902A0. It reports two wrong-name findings for the new verified owner.
  No baseline is extended and no generated inventory is hand-edited. Enforced
  converged-data checking reports zero second names and zero unjudged rows.

Remaining blockers and rejected follow-up:

Both constructor units still define `??0ProgressIndicator@@QAE@XZ`.
Removing the derived unit's local definition changes MSVC's this preservation
from retail EDX to saved ESI, immediately failing its 24-byte row. The attempt
was restored and recorded through re_log.py; duplicate-removal-refusal.txt has
the actual bytes. Do not repeat that removal without new compiler evidence.
The terrain unit still needs rva00115044. These independent findings are in
link-after.txt. No full link cycle, census build/measure/history, nightly or
boot operation was run.

Reference review: retained verified BFME1 pointer
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 and reviewed ownership repair
0835ab92bef30e3303e729a0ce09cf591368d0cd. The single-owner principle applies;
donor types, addresses and implementations are not imported. Storage and head
behavior come from BFME2 retail. Official master fetched as
30d89568c2b073871d220bf00a1ecf03731ed502. The overdue pointer update is
foreign-claimed by yasinschroeder-codex (file:reference/open-bfme-1); verified
inputs and the freshness stamp are preserved.
