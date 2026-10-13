# Listener callback binding repair, 2026-10-13

Base: `8b9d45781999452d266235f30b52007420025020`.
The restored local index measures `d753dedd98`, 2026-10-12 22:16;
the committed status CSV measures a different revision. Results below
use this local index and explicitly checked current objects.

`Rva004FA738ListenerWalks.cpp` previously stored two literal code addresses
in its member-call records. Bind these to existing whole-body forwarder
owners using member-pointer casts. Mirror the providers' declarations,
including virtual slots, without introducing definitions, pins, aliases,
shared headers or new layout claims.

Target evidence:

- The complete 208-byte caller at RVA `004FA9B1` passes VA `009CB260`
  at operand +180; the complete 201-byte caller at RVA `004FAEAA`
  passes VA `009CC208` at operand +105. The record retains its receiver
  and both arguments when the existing `004FA7A5` walk invokes it.
- These are executable forwarding thunks, not runtime-filled data tables:
  complete five-byte bodies are `8b01ff6004` and `8b01ff6008`, respectively
  (load receiver vptr and tail-jump through slot 1 or slot 2). They do
  not touch the argument stack or return value. `proof.txt` records
  the bodies and the newly named DIR32 operands with zero addends.
- Existing providers are `Rva005CB260::rva005CB260` and the already-rowed
  whole-body twin `Rva0042C0DBDelegate::invokeMessage`. The member-pointer
  casts carry those code addresses into the listener's own call-record
  signature; no GameMessage or other provider-specific payload meaning
  is inferred for these listeners. Their original identities remain unknown.

Donor review reuses the prior dedicated linking sweep at verified BFME1
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` and repair
`0835ab92bef30e3303e729a0ce09cf591368d0cd`: bind a consumer to an existing
owner instead of an unowned spelling. That ownership principle applies;
the Apt data types, layouts and addresses do not. No donor C++ or layout
is imported; the callback choice is independently proved by target bytes.
The unchanged broader donor scan was not repeated. Official master was
fetched at `96e5cebc8c93bc60f65abd43461b9a1763a87a58`; pointer-update work
is held by `codex-a44d-root`'s `file:reference/open-bfme-1` claim. Retain
verified inputs and the overdue timestamp; no freshness success is claimed.

Acceptance:

- Normal `./build.sh` passes all 14 rows in the changed unit, strings,
  floats and imports. Two renamed compiler-local funclets still resolve
  through verified parent EH data.
- Bounded `link_check.py --prepare-current` on the changed unit and both
  forwarder providers passes all 19 code rows and produces three strict
  reusable self receipts. `proof.txt` independently verifies
  `object_current(..., allow_fresh=False)` and records object SHA256s.
- Ordinary `link_check.py` before reports precisely two address blockers
  and 0 locally linked bytes for the changed unit. After, all three
  explicitly checked units report LINKS: consumer 0 -> 853 real bytes;
  providers remain 5 and 220 bytes; cohort 225 -> 1078 bytes.
  This repairs two link blockers and unlocks 853 existing authored bytes,
  with zero newly authored executable C++ bytes.
- Declared-definition, CSV, class, case and whitespace checks pass.
  Data shadow check: zero findings. Enforced converged-data check:
  zero second names and zero unjudged rows across eight addresses.
  No escape-hatch occurrence is added to the changed source.

This is a self-strict receipt result and a local legacy link preview;
providers outside the explicit cohort retain the restored index's authority.
No closed-strict gain, updated census, full link cycle, nightly or boot
result is claimed. Broader linked-image validation remains maintainer work.
