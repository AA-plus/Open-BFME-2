# Audio preferences comparison provider repair

Source base: a7c044d929. The available runner index measures cb660e4d97,
2026-10-13 04:02 UTC; object-proof.json records its SHA256. The committed
link_status.csv measures e181b4b6c5 and was used for discovery only. No
census, history, full link cycle or other maintainer runner was started.

The existing 163-byte MilesAudioManager::rva006AD9B0 body at 0x00059646
references an unresolved AsciiString::compareNoCase(const char *) name.
Both native REL32 calls, at body offsets 0x5c and 0x6d, target 0x00037980,
owned by the matched 91-byte StringBase<char>::compareNoCase(const char *)
in string_base_inline.cpp. Call that provider directly through the unit's
existing private one-pointer base view. Remove the unused AsciiString
declaration and expose only the needed base declaration. No layout, algorithm,
compiler setting, header, pin, alias, ledger range or global changes.

Target evidence establishes the two call destinations and complete body
identity. The pre-existing donor supplies the preferences behavior and base
relationship; no new donor identity or layout claim is imported. Reviewed
BFME1 repairs 6906e0cddbf9dd70263e1a475665fb2afa5852a3 and
b870d563b7f4e8b58f433635a39783fb0d7d55cb. Direct provider spelling from the
former is applicable; the latter's locally emitted comparator is unnecessary
because BFME2 already has a matched provider. It was not copied. The existing
donor revision and provenance comment are preserved.

Official BFME1 master was fetched at 49e35f6636748b0e1116265ce543de2f7aca0d39.
The verified checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Foreign file:reference/open-bfme-1 claim codex-a44d-root still owns the overdue
comparative update. The verified inputs and successful-check stamp are retained;
that update remains outstanding with its owner.

Acceptance and before/after evidence:

- Strict reusable self preparation passes for consumer and provider both before
  and after: 53/53 complete rows, three literals, 12 empty-string references,
  16 named imports, zero baseline or skipped references.
- All 11 consumer COMDAT raw bodies and extents are identical. Ten digests
  are unchanged; the only changes in the remaining body's relocation tuples
  are the two proven provider spellings. Two normalized EH sections preserve
  bytes and relocation targets, values and kinds; compiler-local numbered
  labels are normalized. eh_verify.py proves the applicable graph EXACT.
- Paired ordinary link_check.py is a legacy same-index preview: consumer
  findings 2 -> 1, exactly the comparison unresolved name removed, no new
  finding. The unchanged provider LINKS. Combined LINKED remains 3011 bytes;
  the consumer remains at zero.
- Declared-definition, class, new-variants admission, converged-data, ordinary
  shadow data, CSV and whitespace checks pass.

Authored C++ bytes grow by zero. Self-strict byte verification and a verified
local blocker reduction are established; no closed-strict, measured census
or actual link.exe gain is claimed. Full source/object backups and the proof
script remain in ignored build/audio-compare-link-20261013/.

The remaining consumer blocker is
?find@PreferenceMap@@QBEPAUPreferenceNode@@ABVAsciiString@@@Z. Its existing
pin leads to 0x001F8437, recorded as an _Rb_tree<AsciiString> _M_find fold;
repair requires independent canonical map/provider and ABI evidence. That
separate dependency was not reconstructed or given another alias here.
