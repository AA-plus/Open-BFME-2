# Tree buffer comparison provider repair

Source base: 0630ec128d. The runner index measures cb660e4d97 at
2026-10-13 04:02 UTC; object-proof.json records the index SHA256. The newer
committed link queue was used only for discovery. No census, status/history,
full link cycle or data-back artifact was created or changed.

W3DTreeBuffer::rva000ECF79 previously referenced the AsciiString comparison
spelling whose selected definition is not retail's. Both native REL32 operands,
at complete-body offsets 0x44 and 0x53, target 0x00006A00. That address already
belongs to the matched 42-byte StringBase<char>::compareNoCase(const StringBase&)
provider in string_base.cpp. Include the existing canonical BFME2 AsciiString
header and call this provider through its one-pointer StringBase view. The
algorithm, layout, compiler flags and ledger row remain unchanged.

Target bytes establish both call destinations and the complete 1284-byte
consumer identity. The pre-existing donor record supplies the tree-type
behavior and relationships. Reviewed BFME1 linking repairs
6906e0cddbf9dd70263e1a475665fb2afa5852a3 and
6ffd3f498c98872efbb0ad242c3afea4640e4ef5. Their direct base-provider spelling
is applicable; emitting a donor comparator is unnecessary and inapplicable
because BFME2 already has a matched provider. No donor source was imported.

Acceptance:

- Bounded strict-current preparation before/after and build.sh: 38/38 complete
  rows, six literals, 15 empty-string references, three compiler float literals
  and three named imports; none skipped or baselined. Both receipts are current.
- All 14 consumer COMDAT raw bodies/extents are unchanged; 13 normalized
  digests are unchanged. The sole changed digest contains exactly the two
  native-proven comparison bindings. Provider object is byte-identical.
- Other ordinary sections are unchanged. The canonical header contributes
  seven existing /alternatename directives: each exact mapping already exists
  in the census, and none of those alias names is referenced by this object.
  No new global alias mapping or used alias is introduced. Source escape-hatch
  counts are unchanged. The object has no applicable EH row graphs.
- Same-index local legacy preview removes one selected comparison finding,
  with no finding added: consumer findings 2 -> 1. The provider remains LINKS;
  combined local LINKED bytes remain 1185, consumer remains zero.
- Declared-definition, class, new-variants admission, CSV, whitespace,
  converged-data and ordinary shadow data checks pass.

Self-strict byte/object evidence and a local blocker reduction are verified.
New authored C++ bytes are zero. No closed-strict, actual link.exe placement
or measured census gain is claimed. Backups/proof script remain in ignored
build/tree-compare-link-20261013; object-proof.json records source/object hashes.

The remaining independent consumer finding is Vector3::operator*=(float),
which differs from the first copy in link order and has no retail address
in this index. Canonical provider reconciliation is still needed; no speculative
operator or identity change was made.

Official BFME1 master was fetched as 49e35f6636748b0e1116265ce543de2f7aca0d39;
verified checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The prior old/new full-gate freshness comparison remains incomplete after
full-build lock/5337 stale TU preparation; no newer baseline is available.
Verified donor inputs and the success stamp were retained. This local repair
uses the existing canonical BFME2 header and imports no updated donor inputs.
Unrelated untracked dumps and ZH sweep preparation are preserved.
