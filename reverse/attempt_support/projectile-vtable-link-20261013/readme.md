# Projectile-stream module-data vtable binding repair

BFME2 source base: 16eb7529964f876dc0bf03e1d7e7ae667b14d708.
The supplied census index was measured at cb660e4d97, 2026-10-13 04:02 UTC.
Its hash and the source base are recorded in index-meta.json. The newer
committed link-status report at 67e1365aa9 was used for discovery only.
No census, link status, history or per-row measurement was regenerated.

The constructor now references the existing decorated vtable symbol directly,
instead of declaring vtbl_00BCDF18 and using /alternatename to redirect it.
The matched destructor unit already defines that symbol; its source and object
are unchanged. One keyed alternatename grant is deleted from the hatch baseline.
No function implementation, ABI, compiler flags, headers, pins or rows change.

Target evidence: the constructor's existing 84-byte row at 0x000D11D2 stores
retail VA 0x00BCDF18. Object proof checks the corresponding zero-addend DIR32
reference, the real undefined consumer symbol and its defined provider.
Every non-debug/non-directive section's bytes, flags and indexed relocation
targets are identical after substituting that one symbol name. The old alias
symbol is absent. This adds no identity or layout inference.

Donor review: verified BFME1 gitlink and clean checkout remain
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master was fetched at
339b31084dfc5b2e33be3b0b336f42e97c2e0dda. Its
game/Libraries/Source/WWVegas/WW3D2/MaterialInfoDtor.cpp uses the same direct
__identifier vtable binding technique. This is applicable as a technique;
BFME2's address and provider proof are independent. No donor code is imported.
Retrieval of an older repair commit was stopped when it unexpectedly requested
a large history pack. The BFME1 freshness update remains blocked by the prior
unfinished same-revision full-byte old/new comparison (5882 stale TUs and a
shared compiler lock). The verified pointer and absent freshness stamp were
preserved; the update was not marked successful.

Acceptance:

- Bounded strict preparation passes before and after: 6/6 matched rows across
  constructor and destructor units, with zero baseline/skipped string, float
  or import references. Independent ./build.sh also passes 6/6.
- Both objects have self-strict current reusable compiler receipts.
  EH verification reports EXACT 2, zero baseline/non-exact/missing objects.
  Data checking reports zero findings. Declared-definition and class checks
  pass. Object hashes and relocation proof are attached.
- Same-index ordinary legacy local link previews are unchanged: destructor
  links with 92 authored bytes; constructor retains the sole unresolved
  ??1UpdateModuleData@@QAE@XZ and its 111 authored bytes remain unlinked.
  This repair removes one escape hatch; it claims zero new authored bytes,
  zero linked-byte gain, no self-strict closure and no closed-strict gain.
  Full link verification remains maintainer-only.

Discovery checked repair_queue.py link and link_rank.py; both are populated.
The name_globals dry runs on WinMain and Rva004FA738ListenerWalks found no
supported rewrites. ScriptActions is claimed by another worker; AptPlayer
already links locally. The unchanged WinMain false rejection and byte-blocked
PeerDefsGameOptions/PeerThread repairs were not retried. Rehoming discovery
cannot run because build/link_census/census.log is missing, not because its
queue is empty. The remaining constructor destructor-provider blocker is
recorded in the repair verdict; this small verified repair is complete.
