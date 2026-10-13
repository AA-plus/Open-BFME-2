# FXListDie provider repair

Starting BFME 2 HEAD: faf8348924. Local comparisons use the restored census
index cb660e4d97, dated 2026-10-13 04:02. The newer committed link_status.csv
measurement at 67e1365aa9 was discovery evidence only. index.json records the
index hash and measurement metadata; no census index or status was rewritten.

FXListDie.cpp's present-unmatched Zero Hour onDie callback tested upgrades and
emitted a strong definition conflicting with the recovered retail callback in
FXListDieOnDie.cpp. Removing it alone previously lost the rowed 22-byte
DieModule::isDieApplicable COMDAT (attempt at re_attempts.log, 0x00486623).
This repair moves that helper's row and readable implementation to the retail
consumer, then removes the incompatible donor callback and its marker.

Donor provenance: retained clean BFME 1 checkout/gitlink
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its inputs/reference/ Zero Hour
GameLogic/Module/DieModule.h defines the helper as a ModuleData predicate on
the owning Object. The two-layer spelling is preserved: the first raw-pointer
spelling changed register/load order, while the donor's layered expression
reproduces the whole retail helper. Target bytes independently prove Object
at this+8, ModuleData at this+4, DieMuxData at data+8 and the REL32 call to the
existing DieMuxData::isDieApplicable owner at 0x004CE588. The callback's
established target identity, ABI and 100-byte boundary are unchanged.

BFME 1 linking repair 5b1e9f1b0 (drop the wrong local Drawable::getIconInfo)
was reviewed as the removal pattern, not target identity proof. The official
master fetched this session was 58b1f1872; the pointer was not advanced.
Freshness remains outstanding: prior comparative full verification required
5882 stale units and was interrupted at the shared compiler lock in
build/seat-current-baseline-full.log. No success stamp was written.

Acceptance:

- Before: both explicit providers passed self-strict preparation, 3/3 rows.
- After: both providers and the unmodified DieMuxDataInit.cpp dependency pass
  self-strict preparation and normal byte gates, 6/6 rows. No skipped/baselined literal,
  float or import references. whole-body-proof.json proves all three repaired
  cohort rows retain complete raw bodies, extents and relocation targets.
- Same-index legacy findings: donor 13 -> 9, retail provider 2 -> 0. The
  conflicting callback duplicate/selection findings disappear from both units;
  donor bitset selection debt also disappears with the retired upgrade checks.
  The local preview reports retail provider LINKS, 0 -> 122 bytes, including
  the moved 22-byte helper. New authored retail bytes: zero. This is not a
  closed-strict, measured census or actual link-cycle gain.
- The donor still has eight UpgradeMux/BehaviorModule unresolved names and
  selected DieModule destructor debt. Full details and before/after object
  hashes/definition inventories are in the JSON records.
- Declared-definition and canonical-class checks pass. Converged-data check:
  eight addresses, zero second names or unjudged rows. Shadow data check:
  zero findings. EH check: no EH-bearing rows or missing objects. CSV and
  whitespace checks pass. Placement resweep: zero bodies, zero pins.

No pins, aliases, headers, compiler settings, baselines or verification code
were changed. Maintainer-only full-link and census measurements remain pending.
