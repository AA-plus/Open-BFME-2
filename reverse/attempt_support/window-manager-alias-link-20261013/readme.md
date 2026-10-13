# Window manager owner binding repair

Source base: 4ae264eb945b803e087716c1854ab4af565cced8.
The supplied census index measures cb660e4d97 at 2026-10-13 04:02;
proof.json records its unchanged SHA256. Committed link_status.csv
(67e1365aa9, 2026-10-13 16:47) was used for queue discovery only.
No census, index, link status/history, or data-back measurement was changed.

Rva0045EF90Dtor.cpp declared a private-view global and two identical
/alternatename directives for the same retail datum. It now declares
class GameWindowManager; extern GameWindowManager *TheWindowManager;
and casts to its existing evidenced slot view only at the use site.
GameWindowManager.cpp already defines the real global and is unchanged.
This removes two alias hatches and one resolved wrong-name data debt key.
No ledger row, pin, header, compiler setting, layout or virtual call changes.

Target evidence: the complete 110-byte destructor at 0x00410421 reads
VA 0x00DFEF1C at its +25 DIR32 operand with zero addend. The owner's
matched callbacks at 0x002C09DF (+23) and 0x002C0978 (+79) independently
bind TheWindowManager to that same retail datum. Its static type/name are
carried from the existing provider/reference; this does not establish a
new identity for the Rva0045EF90Object or its private manager slot view.
Reviewed BFME1 0835ab92bef30e3303e729a0ce09cf591368d0cd (Apt real data-owner
extern repair): applicable owner-binding principle, no donor layout/body
imported. Reviewed 5093777e8373a843f1f1ccfc648601ae78351aaa (Shader destructor
provider reconciliation): unrelated dependency, inapplicable here.

Official BFME1 master was fetched at 24656f4d3e8ea20887e256aef9a0dfaaa7ad6aae.
The clean committed checkout remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
No pointer/stamp update or successful freshness check is claimed. The prior
documented build-lock/5337-stale-TU old/new full-gate comparison remains
incomplete; see ../tree-scale-link-20261013/readme.md. This bounded repair
uses the retained verified inputs rather than silently replacing headers.

Acceptance:

- Bounded link_check.py --prepare-current for the consumer and actual provider,
  before and after: six complete rows exact, no skipped/baselined literals,
  current strict reusable self-verification receipts for both objects.
- ./build.sh Code/GameEngine/Source/Common/Rva0045EF90Dtor.cpp: four rows exact,
  including the 110-byte destructor and both deleting bodies/handler extents.
- eh_verify.py on the consumer before and after: EXACT 1, zero missing objects,
  nonexact or baseline rows. All four matched raw bodies stay unchanged.
  The only external relocation change is the +25 global owner binding.
  The handler's +1 compiler-local label changes $T419 to $T421; EH data remains
  exact on both sides. The provider's source and object hashes are unchanged.
- proof.json compares saved-before and current-after objects using
  link_check.refresh in memory for these same two providers, RetailTruth,
  check_object and object_current(..., allow_fresh=False). Both versions have
  exactly the same findings. Consumer: one selected StringBase<char>
  destructor. Provider: 20 unresolved GUI methods/callbacks plus selected
  registerTabList. No introduced unresolved, duplicate, COMDAT or address
  finding. Ordinary local link_check.py exits 1 for those existing blockers.
- Converged-data: eight addresses, zero second names or unjudged rows.
  Ordinary shadow-data: zero findings. Baselines only shrink for this consumer.
- CSV, declared-definition, staged class, staged hatch and whitespace checks pass.

Authored C++ bytes: +0. Legacy linked bytes: 0 -> 0. This is verified data-name
and escape-hatch debt repair, not a link-clean unit, closed-strict closure gain,
measured census gain or actual link.exe placement. Self-strict byte/object
receipts are distinct from link closure. No maintainer-only runner was started.
Existing StringBase destructor and GUI dependency/provider blockers remain;
unchanged prior failed destructor/concat attempts were not retried.
Unrelated untracked dumps and ZH preparation are preserved.
