# Team and base-template concat link repair

At checkout e328192dce5a373e0cfbea4f545fdeb78afc1e4c, the local census
index is measured at d753dedd98 (2026-10-12 22:16), while the committed
link-status queue is measured at 3906ea7b97 (2026-10-13 05:18). The queue
served discovery; all before/after previews use the same local index. Its
metadata and SHA-256 are in index-meta.json and remained unchanged. No census
or link-status counters were edited, and no per-row data-back ranking was used.

Two owned consumers still bound literal concat calls to the selected,
non-retail AsciiString::concat(const char *) definition. Original object
REL32 positions prove four direct retail calls to 0x00005629: two in the
471-byte Team constructor at 0x003A39A7, and two in the 457-byte
BaseTemplateLibrary::parseBaseTemplateFiles at 0x0041F095. retail-calls.txt
also includes the independently checked, deferred MapCache call.
The existing ledger provider is the 37-byte StringBase<char>::concat(const
char *) in string_base.cpp. Bind the four supported calls directly to that
provider through the canonical one-pointer StringBase view. The AsciiString
object overloads are untouched. Existing source identities and semantics are
preserved; target call destinations and complete byte/relocation verification
justify the repair. No new ABI/layout claim, pin, alias, marker, header,
compiler flag or ledger range is introduced. calls-after.json records the
repaired relocation spellings at the original retail call positions.

Reviewed BFME 1's verified input cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
and donor repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 (direct StringBase
bindings, reported 36/36 gate). Its provider-binding principle applies;
its compare implementation and BFME 1 addresses do not. The releaseBuffer
repair 5fa9bfd662c427a198176b0b727c4c11d0965733 was reviewed but is not a
concat-body import. This continues the verified BFME 2 dependency repair in
../concat-link-20261012/ and ../concat-link-20261013/. Official upstream was
fetched at 207ce65d3217a13728a6275b5b1ce5a7be5145c4. A live foreign
file:reference/open-bfme-1 claim (codex-a44d-root) prevents a pointer update;
the clean, committed verified input was retained and the overdue freshness
success stamp was not advanced. Comparative full verification remains with
the update owner.

Acceptance:

- ./build.sh on both consumers and provider: 47/47 functions, 10 string
  literals, 15 empty-string references and three named imports verified;
  zero baselines/skips. Six existing funclet rows remain verified through
  their parents' EH data after compiler-local label renumbering.
- link_check.py --prepare-current --paths-from sources.txt: three strict
  reusable self-verification receipts, followed by normal byte gates.
  objects-after.json records source/object hashes and strict currency.
- link_check.py --paths-from preview-sources.txt: exactly two selected concat
  dependency findings removed, none added. findings-delta.json records the
  difference. Provider remains LINKS with 1,185 bytes; consumers remain blocked.
  The four-unit preview includes the unchanged MapCache candidate and stays
  1/4, 1,185 -> 1,185 linked bytes. This is a legacy census preview and strict
  self-verification, not a closed-strict closure or actual link.exe gain.
- find_declared_unmatched.py passed for both consumers before and after;
  check_csv.py and git diff --check passed.

Deferred candidate: MapCache::writeCacheINI at 0x00303409, 1,503-byte
ledger extent. Its original REL32 +0xA1 also targets 0x00005629, but the
single cast-only trial changes the later isOfficial/isMultiplayer/isScenarioMP
boolean-to-string instruction shapes and fails byte comparison. The original
source rebuilt 1/1 exact under the same current inputs. Trial patch and gate
output are map-rejected.patch and map-rejected-gate.txt; original acceptance
is map-original-gate.txt. The source is unchanged, the blocked verdict is
recorded, and its RVA/file claims were released. Further compiler-shape work
is independent of the two accepted consumer repairs.

New authored C++ bytes: zero. Team still has an unresolved crc method and
independent container, getName, constructor and scalar-deleting-destructor
findings. Base-template parsing still has the hashtable begin COMDAT and
selected-provider findings. MapCache retains its original nine findings.
No maintainer-only link cycle, census build/measure/history, nightly or boot
operation was started. No closed-strict gain is claimed.
