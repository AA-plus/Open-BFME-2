# Rehome the R3 constructor beside its caller

Base commit: df0f870670b78aa8c6013699b4f1340df05c57a5.
The local census index used for both previews is d753dedd98, measured
2026-10-12 22:16. Committed link_status.csv instead reports measurement
3906ea7b97 (2026-10-13 05:18); it is not the index used here. Neither artifact
was rewritten, and no per-row data-back ranking was inferred.

The two claimed files in sources.txt both emitted a strong definition of
??0Rva00352900@@QAE@XZ. The existing ledger assigned the 27-byte retail body
at 0x003B40DF to R3ScalarFieldConstructors1.cpp. constructor-before.json shows
that both current copies have the same entire bytes and the same DIR32
relocation at offset 12 to Gen00C1F470. The latter global's sole definition
and value remain in R3ScalarFieldConstructors1.cpp.

Remove the redundant constructor definition from that provider and repoint
its existing row to ScriptListSubrecordAddRva003B7EC2.cpp with add_match.py
--replace-existing. The surviving definition stays ahead of its caller:
VC7.1 needs that register-use summary to preserve EDX across construction.
The caller source, layouts, ABI, globals and flags are unchanged. No new
identity is claimed: Rva00352900 remains the donor's address-derived class
name. The established donor provenance is retained in the row.

## Acceptance

* byte-after.txt: all six rows in the provider/consumer cohort pass the byte,
  string, float and import gates. Total real authored coverage stays 249 bytes.
* prepare-before.txt, prepare-after.txt and prepare-final.txt: both explicit
  owned units have strict reusable receipts and pass all six self byte checks.
  These are self-strict results, not closed-strict link measurements.
* link-before.txt / link-after.txt: the ordinary local legacy preview removes
  the constructor duplicate from both units. The provider now links its
  remaining 91 real bytes; the consumer still reports only the unresolved
  rva003B7C47 lookup. The local preview rises from 0 to 91 linked bytes.
  Its after command exits 1 because the consumer remains blocked.
* constructor-after.json: the redundant definition disappears while the
  surviving body and relocation remain identical to both original copies.
* Shadow data_check has zero findings. Enforced converged data_check passes
  with eight addresses, no second names and no unjudged rows.
* find_declared_unmatched.py, check_csv.py and git diff --check pass.

No authored bytes grow, no pin or alias is added, and no baseline, verifier,
link census or status file changes. Full linking and a closed-strict gain
remain unmeasured and outside this seat's authorization.

## Donor review and outstanding work

BFME 1 repairs reviewed at fetched upstream revision
8ac733e929f7aacb6b4a3238a91284300226a1a2:
04efff0e093927f2c12bd554af342e7d96142669 (remove W3DBridge destructor
competitor) and 35bf0d0b18da30aefe812143de4a8add3ea21565 (MeshGeometry
provider reconciliation/rehome). Their applicable principle is retaining one
verified provider and checking consumers together. BFME 2 object bytes and
normal gates establish this repair; no donor implementation or layout was
copied. Anim2D repair 5fa9bfd662c427a198176b0b727c4c11d0965733 was also
reviewed for canonical cleanup bindings; it needs separate evidence here.

The verified BFME 1 pointer stays cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Upstream differs, but file:reference/open-bfme-1 is held by codex-a44d-root.
The clean checkout, committed pointer and old freshness stamp were preserved.
Comparative full verification and pointer update remain with that owner.

A previous subobject-visibility repair trial is recorded under subobject/.
Its record-destructor COMDAT forwards to StringBase releaseBuffer, while the
first allocator copy forwards to AsciiString's destructor. A dllimport
forceinline destructor trial preserved all 86 cohort rows and strict self
checks, but EH cleanup still imported an unresolved destructor, so it did not
repair linking. Source was restored and both owned file claims released.
The first allocator provider has a foreign live claim (w6-mp2); do not repeat
this trial until its provider relationship changes. No code from that attempt
is retained and no link gain is credited to it.
