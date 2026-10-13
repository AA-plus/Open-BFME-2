# Unit-timings benchmark data providers

Base `8472f81ad50476d406a60831e0c5377a31c4fa93`.
Available census index: `d753dedd98`, 2026-10-12 22:20 UTC. The newer
committed link status at `3906ea7b97` serves leads only; no per-row artifact
was used to rank data-back gains. Neither census artifact was changed.

The current unit had exactly two unresolved globals. Define them in its
existing owner and replace the address-derived declarations with descriptive
names: BfmeUnitTimingSavedViewValue and BfmeUnitTimingDisplayStats. No other
consumer or provider of the previous names exists in Code/. No code row,
symbol pin, compiler flag, class layout, or header changed.

Target evidence: the complete native 0x002431CB..0x00243B48 body stores a
view-slot result at VA 0x00DBA6D0 and later reloads it for restoration. Its
four retail initial bytes encode 100.0f. It passes VA 0x00DFE948 to Display
slot 0x178, divides the three consecutive dwords by 100, and prints all three
together. All twelve initial bytes are zero. The committed retail xref
inventory lists only this benchmark for these four addresses (bases plus
the array's +4/+8 entries). Compiler sizeof and full data verification prove
the 4-byte scalar and 12-byte array; before/after relocation transcripts
prove every reference still binds to the same target address and addend.
The descriptive identifiers do not claim recovery of original names.

Donor review: BFME1 verified pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
contains the ZH-derived unitTimings algorithm, a semantic lead already used
by this matched body. BFME1 linking repair 07f3e53eb83b4ff95d5138c4eb2bd8221e8509d0
provides the applicable principle of defining independently verified data
cells beside their consumers. Its names, addresses and layouts were not
imported. Official master was fetched at 6a18725a5dbb2f61f8c0f971fdda7cc5b75d7d7c;
the live foreign file:reference/open-bfme-1 claim blocks the freshness update.
The verified pointer and successful-check stamp were retained.

Acceptance before and after: bounded link_check --prepare-current passes the
one explicit provider with strict reusable receipts. The normal byte gate
preserves the full 2,429-byte function, 12 string literals plus one empty
reference, 16 compiler float literals and three imports, with no baselined
or skipped references. After the repair both new data rows also verify.
find_declared_unmatched, check_csv and git diff --check pass; data_check
reports zero findings and the enforced converged check finds no second name
at eight converged addresses.

The ordinary local link preview changes from 0/1 clean and 0 bytes to 1/1
clean and 2,423 existing authored bytes (retail 0xCC bytes excluded). This is
a legacy preview against the same index with a self-strict current object,
not a closed-strict closure or a real link.exe placement measurement. New
authored C++ bytes: zero. New verified owned data: sixteen bytes. A broader
link cycle remains a maintainer-lane check.
