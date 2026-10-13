# Shell map caller bindings

BFME2 source base: 0752325bd75fa1b3e5e0491bbba3326ff2e9aae7.
The supplied census index is cb660e4d97, 2026-10-13 04:02 UTC; its SHA256
is recorded in object-proof.json. The newer committed link-status report
at 67e1365aa9 was discovery only. No index, status or history was rewritten.

Three callers now name the existing verified bool Shell::showShellMap(bool,
bool) provider instead of the private Rva0035C194 address-derived class.
GameClientDrawableTOC.cpp and GameLogicRva00376E92.cpp extend their existing
Shell method declarations; VslotSmallBodiesAE.cpp replaces the address view
and pointer reinterpretation with Shell and TheShell. No fields, offsets,
compiler flags, shared headers, pins, ledger ownership or extents change.
GameLODApplyPreset.cpp already names the provider and needs no repair.

Target evidence: direct E8 calls in existing rows 0x0051483C (60B),
0x00239122 (136B), and 0x00376E92 (466B) independently resolve to
0x0035C194 at operand offsets 33, 94 and 237 respectively. The provider's
293B body in ShellTop.cpp is independently byte-verified and defines
?showShellMap@Shell@@QAE_N_N0@Z. The declaration preserves thiscall,
bool return and two bool arguments. This adds no new identity/layout claim.

Object proof: exactly three external zero-addend REL32 symbol bindings
change. Every non-debug/non-directive section's bytes, flags, association
and normalized relocation targets remain identical, as do all external
definitions. Removing the private declaration renumbers 105 local compiler
label references; each retains the same storage class, target section and
section offset. EH data and funclets remain exact. The provider object
is byte-for-byte unchanged. The attached JSON records source/object hashes,
all retail call targets and each local label rename.

Donor review: the clean verified BFME1 pointer remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its Shell.cpp and ZH Shell.h
use a one-argument void showShellMap, unlike BFME2's independently verified
ABI. Donor linking repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
supplies the general supported direct-provider binding technique; no donor
body, target offset or one-argument signature is imported. Official master
was fetched at 001cf898fa5a0415d9d5c5db631b23b4d530ec3b. Freshness remains
unverified: the prior full old/new baseline comparison required 5882 stale
TUs and stopped at the shared compiler lock. The verified pointer and stamp
were preserved; this session does not claim the freshness update completed.

Acceptance:

- Before/after bounded strict preparation and an independent ./build.sh pass
  108/108 rows across all three callers and their provider. String references
  pass with 32 literals and 3 empty references, no baseline/skipped entries;
  both float references and all 4 imports pass.
- Final objects have strict current reusable receipts. EH verification reports
  18/18 EXACT, zero non-exact, baselined or missing-object rows. Declared-body
  checks, class gate and git diff --check pass.
- Same-index legacy local previews remove exactly three unresolved findings,
  one per caller. The callers retain other unresolved/COMDAT/selected-provider
  blockers. ShellTop remains linked at 2289 authored bytes; aggregate linked
  bytes remain 2289. No new authored bytes, net linked-byte gain, self-strict
  link closure, closed-strict gain or full-link measurement is claimed.
- Raw outputs and JSON proof are attached. Scratch snapshots and reproducible
  proof script are in build/shell-binding-link-20261013. Normal hooks apply.

Remaining same-cause consumer: MapSelectMenuInit, 0x0050D2EF (752B), still
uses Rva0035C194. Its donor Shell.h declares void showShellMap(bool), so the
verified BFME2 bool(bool,bool) call needs a supported TU-local header/ABI
reconciliation. Changing the private class name alone cannot name the real
provider alongside that included Shell definition. No header or source trial
was made there, and its blocker is recorded separately. Broader link closure
remains maintainer-only. The discovery queue is populated; name_globals
--dry-run found zero supported rewrites. rehome_rows --limit 12 fails on
missing build/link_census/census.log, which is preparation debt, not an empty
lane. Unrelated untracked preparation remains preserved.
