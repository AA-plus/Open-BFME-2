# Default frame-constructor provider reconciliation

Local checkout: 0f06f00127, following the preceding GameInfo copy repair.
Available census index: d753dedd98, 2026-10-12 22:16. The committed status
at e956901d31 was used for discovery only. No census, status, closed-strict
artifact or maintainer-only full link measurement was changed or produced.

## Evidence and change

Rva0053FDE6Init.cpp and Rva00540B48.cpp both emitted the entire 68-byte
default constructor in NODUPLICATES COMDATs. Before snapshots prove
identical bytes and both DIR32 relocations: +45 to g_Va00BBB8D8 and +58
to g_Va00BC74F0. The existing ledger's target is 0x0053FDE6. Source flags,
whole bodies and relocations are preserved; no new symbol pin is needed.

A declaration-only consumer trial failed its matched 101-byte reader:
retail preserves ECX through the constructor and directly reuses it for
readData; an opaque declaration adds lea ecx,[ebp-0x24]. That trial was
reverted. The final change retains the existing constructor definition in
the consumer and removes it from the former owner. The 16-byte default
outer constructor at 0x0054000B also moves to the consumer, because it
needs the same compiler knowledge. add_match --replace-existing verifies
and repoints both existing rows without increasing authored coverage.
The former owner's 27- and 29-byte copy constructors remain exact.

The consumer's formerly opaque 40-byte outer record now declares the
verified owner's int at +0 and 36-byte inner record at +4. The constructor
bytes and existing owner supply the layout basis, and the consumer's whole
reader remains exact. Names remain address-derived; no semantic class
identity is newly asserted. Two unused address-global declarations are
removed from the former owner.

BFME 1 donor linking repair 35bf0d0b18da30aefe812143de4a8add3ea21565,
reviewed in this session, demonstrates rehoming an owner to a supported
existing provider while removing a competing definition. Its mesh code
and ABI are inapplicable. BFME 2's whole-body/relocation twins and caller
register behavior support this local reconciliation. No corresponding
address-derived donor files were found at the verified BFME 1 pointer;
that is not a claim that the donor's broader linking lane is exhausted.
The verified pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85;
the overdue freshness update is owned by another worker, as recorded in
the preceding GameInfo evidence.

## Checks and result

- Explicit self-strict preparation before/after: two current providers,
  five matched bodies, ordinary source, literal, float and import gates
  pass. Provider preparation alone does not establish closure.
- Both add_match replacements pass their own byte verification;
  ./build.sh on both complete units passes 5/5 bodies. The final strict
  preparation recompiles after removal of the unused declarations and
  again passes 5/5.
- Ordinary local legacy link preview, both current objects together:
  0/2 clean files and 0 linked bytes before; 1/2 and 56 bytes after. The
  command exits 1 because the consumer still has three unresolved names:
  Rva00540B48Vector::erase, Rva00540B48Vector::reserve, and
  Rva0053FDE6::readData. No duplicate-constructor finding remains.
  The accepted owner alone passes link_check with exit 0.
- check_csv and find_declared_unmatched pass. Converged data check:
  two sources, eight addresses, no second names or unjudged rows;
  ordinary shadow data check has no findings.
- The former owner's hatch count falls 4 -> 0; the consumer stays 4.
  No baseline, hook or verifier code was edited.

There are zero new authored C++ bytes. The 56-byte gain is a local legacy
preview at the named older census, not a closed-strict or full-link-cycle
measurement. Broader maintainer verification and the consumer's unrelated
helper providers remain outstanding.

Transcripts: sources.txt, strict-before.txt, strict-after.txt, byte-after.txt,
preview-before.txt, preview-after.txt, accepted-owner.txt, rehome-inner.txt,
rehome-outer.txt, declaration-only-failed.txt, data-after.txt,
data-converged-after.txt. Object snapshots record before twins and the
single remaining provider after the repair.
