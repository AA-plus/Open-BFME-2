# Threat-finder warning concat link repair

BFME 2 base: 36bce8d6f52aaf381de86d1531595b7dbd81f2b9. The discovery
queue is committed link_status measured at 2a20912cc9, 2026-10-13 08:08.
Both local before/after previews use the same older census index at
d753dedd98, 2026-10-12 22:16; meta-before/after.json record its unchanged
SHA256. No census status, measurement, baseline, pin or ledger row changed.

## Target evidence and repair

The 267-byte doSetCounterToThreatFinderThreat body at 0x003C5E10 calls
AsciiString's object concat at REL32 operand +0xCD (retail destination
0x00006987) and literal concat at +0xDA (retail destination 0x00005629).
The existing string_base.cpp provider at 0x00005629 is the 37-byte
StringBase<char>::concat(const char *) body, with its length-overload
call at +0x1C targeting 0x000369A0. calls-before/after.json preserve these
target facts and the caller's original/repaired relocation spellings.

Bind the warning's trailing period directly to that StringBase provider
through the existing canonical one-pointer view. The object concat keeps
its original binding. This removes the reference to the kept non-retail
AsciiString literal-concat wrapper. No new layout or identity is inferred:
the existing source's established warning behavior and complete verified
bytes/relocations justify the provider change.

BFME 1 repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 was reviewed:
its direct-StringBase binding principle is applicable, while its compare
body and BFME 1 addresses are not imported. This continues the successful
BFME 2 repairs in concat-team-map-base-link-20261013 and
aptstats-ladder-concat-link-20261013. The verified donor remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master was fetched at
9778a932c11c43066d2674eafc0ce24b7cdcd517. The foreign
file:reference/open-bfme-1 claim held by codex-a44d-root prevents this
seat's pointer update; retained verified inputs and did not advance the
overdue successful-check stamp. Comparative full verification remains
with that update owner.

## Acceptance and result

- Baseline and repaired consumer/provider preparation: 41/41 matched
  rows, eight string literals, 15 empty references and three imports;
  zero baselined or skipped references. Both objects have reusable
  self-strict current receipts; source/object hashes are attached.
- Ordinary ./build.sh on the edited unit: 4/4 matched rows and all four
  literals verified. All 752 ledger bytes retain their exact code and
  relocations; progress excludes four retail 0xCC padding bytes.
- Local legacy preview removes exactly the selected literal-concat
  finding, with no added blockers. The consumer changes from does-not-link
  to LINKS, LINKED 0 -> 748 real bytes. The unchanged provider remains
  LINKS, 1,185 bytes; cohort 1/2 -> 2/2, 1,185 -> 1,933 bytes.
- find_declared_unmatched, check_csv, converged-data checks and
  git diff --check pass. No new authored C++ bytes are claimed.

This is a legacy census-preview gain with strict self-verification,
not a closed-strict dependency closure or an actual link.exe measurement.
No maintainer-only runner or census build/measure/history was started.
The consumer has no remaining local preview finding. Full dependency
closure and a current whole-game measurement remain outstanding.
