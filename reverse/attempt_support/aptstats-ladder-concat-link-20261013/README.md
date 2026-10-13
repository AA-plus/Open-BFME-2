# AptStats and LadderDefs literal concat provider repair

Base BFME 2 commit: a4c9d1b54136175daaebc467fa427bafc922f33c.
Local link index: d753dedd98, measured 2026-10-12 22:16; its SHA256 is in
index-meta.json. This is older than the committed link-status snapshot; no
new census or per-row data-back measurement is claimed.

## Target evidence and change

Retail InitializeFactionVariables (0x005DD2D3, 441 bytes) calls 0x00005629
at REL32 operand +0x113. Retail checkLadder (0x0054E2FB, 299 bytes) calls
the same address at +0x73. The existing 37-byte StringBase<char>::concat
provider at 0x00005629 calls its text/length overload at 0x000369A0.
The call inventories record these target facts separately from source names.

Both consumer objects previously referenced AsciiString::concat(char const*),
whose kept definition was not retail's. Calling through the existing
StringBase<char> view selects the actual provider without changing the verified
caller bodies. The byte gate proves this view preserves these two callers'
retail behavior; this repair introduces no class layout claim, header, pin,
ledger row, compiler setting, provider edit or extent change.

BFME 1 donor principle reviewed: commit
5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 replaced AsciiString comparison
wrappers with the direct StringBase provider in its portrait thunk and related
consumers. The direct-provider repair principle is applicable here; BFME 2's
own call targets and gates supply the address/body proof. The verified donor
pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Upstream fetched
1644b0fdd1833b84f94fd47fe4aea72c3751fd82; the reference file-scope claim is
held by another worker, so this seat neither advanced it nor marked freshness
verification successful.

## Acceptance and bounded improvement

- Ordinary byte gates: AptStats 19/19 rows; LadderDefs 11/11 rows.
- Explicit consumer/provider preparation: 67/67 rows across both consumers
  and unchanged string_base.cpp, 61 literals and 18 empty references, one
  float literal and seven imports. All three objects have self-strict current
  reusable receipts; hashes are recorded in receipts-final.json.
- LadderDefs' existing funclet label was renumbered by MSVC; its parent EH
  data independently verified the same retail placement at 0x00798468.
- find_declared_unmatched accepts both edited units; check_csv is clean.
  Converged-data check: three sources, eight addresses, no second names or
  unjudged bindings.
- Legacy local link previews remove exactly the selected AsciiString literal
  concat finding from each consumer, with no added findings: AptStats 22 to
  21, LadderDefs 20 to 19. Full before/after inventories and delta.json are
  attached. The unchanged provider links in the preview (1,185 bytes).
- Consumer LINKED totals stay zero; aggregate including provider stays 1,185.
  New authored C++ coverage is zero. These are dependency findings removed,
  not closed-strict or actual-link gains. Closure was not checked; no
  maintainer-only verification runner was started.

## Remaining blockers

AptStats still needs rankPoints, rankValues and rva00559AF9 providers and has
18 STL allocation/vector COMDAT or selected-definition findings. LadderDefs
still needs PlayerTemplateStore::getAllSideStrings and
FileSystem::getFileListInDirectory and has 17 string/list/tree COMDAT or
selected-definition findings. The complete local inventories identify each
remaining symbol. Further repair requires independent provider/ABI evidence.
