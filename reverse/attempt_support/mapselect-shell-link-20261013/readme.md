# MapSelectMenu Shell provider repair

Source base: 7c4f85c5f87afad22d6b543eb8ff6a6c7dfe808f.
The supplied index measures cb660e4d97, 2026-10-13 04:02 UTC. Its hash
and source/object hashes are in object-proof.json. The newer committed
link_status.csv was used for discovery only; no census artifact was changed.

MapSelectMenuInit now calls the existing bool Shell::showShellMap(bool,
bool) provider. Its donor Shell.h declares void showShellMap(bool), so this
TU now declares just the seven out-of-line Shell methods it calls, retaining
every existing method ABI and default argument. The declaration supplies
no fields, constructors or virtual slots; the TU neither creates Shell
objects nor needs their size. Existing separate target field views are
unchanged. No shared header, layout, flags, pins, ledger extent or provider
implementation changes. The obsolete Rva0035C194 class and cast are removed.

Target proof: the E8 operand at offset 55 of the whole 752-byte native
MapSelectMenuInit row (0x0050D2EF..0x0050D5DF) resolves to 0x0035C194.
ShellTop.cpp independently verifies the complete 293-byte provider there,
with the exact thiscall bool(bool,bool) ABI. This resolves the previously
recorded donor-header blocker; it adds no original-name or layout inference.
The other six method declarations retain their prior decorated bindings.

Object comparison proves a single zero-addend REL32 name change. All
non-debug/non-directive section bytes, flags, associations, normalized
relocations and external definitions remain identical. Sixty-four local
compiler label names change numbering, preserving each label's storage
class, section and offset. The provider object is byte-for-byte unchanged.
Scratch snapshots and the reproducible comparison script remain under
build/mapselect-shell-link-20261013; the attached JSON records the proof.

Donor review: the existing dedicated linking sweep and prior Shell repair
review are reused at the unchanged verified BFME1 pointer
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Donor Shell.cpp and its ZH Shell.h
use the one-argument void method; that ABI is inapplicable to this BFME2
call. The prior reviewed donor repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
also replaces non-retail wrapper bindings with proven provider bindings;
its StringBase-specific code is not imported here. Official master was
fetched at 001cf898fa5a0415d9d5c5db631b23b4d530ec3b. The previous full old/new
freshness comparison remains blocked on 5882 stale TUs and the compiler
lock. The verified pointer and old stamp remain preserved, without a new
freshness success claim.

Acceptance:

- Before/after explicit strict preparation and an independent ./build.sh
  pass all 41 rows across caller and provider. All 33 literals, two empty
  references, one float reference and one import pass without baselines or
  skips. Final objects have strict reusable current receipts.
- EH verification: 13/13 EXACT, zero non-exact/baselined/missing rows.
  Declared-body, class gate and git diff --check pass.
- The same-index legacy local preview removes exactly one unresolved
  finding: MapSelectMenu 19 findings become 18 with no added findings.
  ShellTop remains LINKS at 2289 authored bytes; cohort LINKED remains
  2289. Authored-byte growth is zero. Self-strict byte preparation is
  established; self-strict link closure, closed-strict gain and a census
  linked-byte gain are not claimed.

Remaining MapSelectMenu blockers are the map-list provider, five imported
STLport helpers and twelve COMDAT findings. Broader link verification is
maintainer-only. The lane queues remain populated. Prior preparation debt
includes missing build/link_census/census.log for rehome_rows; this repair
does not need it. Unrelated untracked preparation was preserved.
