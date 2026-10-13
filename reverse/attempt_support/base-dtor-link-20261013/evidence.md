# Rva005B253F destructor link repair

Checkout measured locally: 2c3c6532e5. The available census index describes
2026-10-12 22:16 at d753dedd98; repair_queue's committed status describes a
different revision, f6c432fac6. The latter is a lead only. No census, status,
closed-strict artifact or full linker measurement was changed or produced.

## Evidence and scope

The owner RvaSmallVtableCtors.cpp emitted ??1Rva005B253F@@UAE@XZ in a
NODUPLICATES COMDAT (selection 1). Rva005B4A46Dtor.cpp and
Rva005B5CF4Dtor.cpp each emitted the same symbol in select-any COMDATs
(selection 2). The before/after object snapshots show the whole seven-byte
body c70100000000c3 and the same DIR32 relocation at offset 2 to
??_7Rva005B253F@@6B@ in every copy. All objects have strict reusable receipts.
The ledger's constructor at 0x005B253F, destructor at 0x005B2551 and scalar
deleting destructor at 0x005B2558 remain byte verified. This establishes the
supported link-selection repair, not a recovered class identity or shared
class layout. Consumer views and target offsets were not changed.

The owner destructor is now inline. An explicit qualified call in the existing
inline_depth(0) anchor block retains its standalone ledger body without
changing its deleting destructor. The added anchor is compiler support,
absent from retail. An initial inline-only trial failed because MSVC omitted
the standalone symbol; the call anchor repaired that emission failure.

BFME 1's verified checkout/gitlink remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed donor linking repair
5093777e8373a843f1f1ccfc648601ae78351aaa (ShareBufferClass<ShaderClass>
destructor copies) supports reconciling competing inline providers; its body
and layout are inapplicable and were not copied. BFME 2's actual body,
relocation and COFF selection evidence above support this local adaptation.
The overdue donor freshness update is held by codex-a44d-root's live
file:reference/open-bfme-1 claim. Official upstream was fetched at
4e574b634437a59b3a568889323c72f28b76b8bb; the verified checkout, pointer and
freshness stamp were preserved pending that worker's comparative verification.

## Checks and result

- Explicit self-strict preparation before and after: three owned sources,
  202/202 matched bodies, strict reusable receipts; sources, strings, floats
  and imports pass. This prepares providers; it does not establish LINK closure.
- ./build.sh on all three sources: 202/202 exact; 30 literals and 8 imports
  pass. Standalone and deleting destructor rows both remain present.
- Ordinary link_check local legacy preview on the three current objects:
  0/3 and 0 linked bytes before; 2/3 and 2,900 linked bytes after.
  RvaSmallVtableCtors.cpp contributes 2,629 and Rva005B5CF4Dtor.cpp 271.
  The three-source command exits 1 both times because the other consumer
  retains unrelated blockers. The accepted owner/consumer pair exits 0.
- Rva005B4A46Dtor.cpp loses the duplicate-destructor blocker but retains
  StringBase<unsigned short>::isEmpty (retail-wrong COMDAT) and its derived
  vftable (differs from the first copy; no retail address). No clean-file
  improvement is attributed to that consumer.
- check_csv and find_declared_unmatched pass. Converged data check:
  3 sources, 8 addresses, zero second names and zero unjudged rows.
  Ordinary data check passes in shadow mode (see data-after.txt).

There are zero new authored C++ bytes. The 2,900-byte gain is a local legacy
preview against the named older census, not a closed-strict gain or an actual
link-cycle result. Maintainer-only full linking remains outstanding.

Transcripts: sources.txt, strict-before.txt, strict-after.txt, byte-after.txt,
preview-before.txt, preview-after.txt, accepted-pair.txt, data-after.txt.
objects-before.json and objects-after.json record the emitted copies.
