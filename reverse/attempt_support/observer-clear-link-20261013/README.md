# Observer mask clear emitter repair

Starting checkout: ab58faa9fd. Local index: cb660e4d97, 2026-10-13 04:02 UTC.
The committed link status reports a separate measurement at 2a20912cc9;
it was used only for queue discovery. No index or census counters were changed.

Remove the incidental BitFlags<116>::clear definition from
Code/GameEngine/Source/GameClient/GUI/Rva0050DE39Observer.cpp and write its
same memset directly at the four existing observer mask clear sites.
The local masks still occupy seven words and clear 28 bytes, exactly as the
already-matched caller does. This is a scoped existing view, not new proof
of canonical BitFlags layout. No class header, flags, pin, alias, global,
ledger row or function extent changes.

Target evidence: the existing ledger owns the 14-byte clear function at
RVA 00666E80 in SupplyTruckAIUpdate.cpp. Its retail body clears four words
with direct stores. The observer's incidental 14-byte copy instead calls
memset for 28 bytes and is proven wrong as an out-of-line body at that
address. No observer call relocation names clear: its four clear operations
were already inline. After the change that one COMDAT disappears, all 38
remaining whole COMDAT bodies and relocation-name digests are unchanged,
and the undefined reference set is unchanged. object-summary.json includes
native and old clear bytes plus strict current object hashes. Caller bytes
are established by the ordinary full byte and relocation checks, separately
from the ledger-carried method identities.

Acceptance:

- Before and after, bounded link_check.py --prepare-current verifies both
  consumer and unchanged retail provider: 8/8 bodies, 12 data rows, 16 string
  literals, no baselined/skipped references; both have strict self receipts.
- Final ./build.sh on the observer passes its 7/7 ledger bodies, 12 data rows,
  16 string references, and zero float/import references.
- Ordinary local link_check.py on the observer changes from two blockers
  (comdat and selected for clear) to LINKS, exit 0: 0 -> 2364 existing bytes.
  The two-source preview changes 0/2 -> 1/2 clean, 0 -> 2364 linked bytes.
  The provider's independent 37 blockers remain unchanged. The pair command
  exits 1 for that known blocked provider; consumer acceptance exits 0.
- New-variants admission, find_declared_unmatched, class_gate, check_csv and
  git diff --check pass. Enforced converged data check: two sources, eight
  addresses, zero second names and zero unjudged rows.
- Shadow data check still reports the existing RecorderClass spelling of
  TheRecorder at RVA 00A02290. Read-only checks of both object snapshots
  confirm the same finding before and after; data-before-after.json records
  it. It is a separate existing datum binding and was not changed.

This is a legacy local link-preview gain of 2364 existing bytes with strict
self verification. New authored C++ bytes: zero. No closed-strict gain,
refreshed census gain, or executable placement is claimed. No maintainer-only
link cycle, census build, nightly or boot runner was started.

Donor review: retained verified BFME1 gitlink and clean checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed emitter repair
d3f9000fe08615a100e844adfff57fa4a39cd615 and its recorded TileData byte/link
acceptance: its remove-competing-emission principle is applicable, while its
class layout and body are inapplicable here. BFME2's earlier BitFlagsXfer
repair uses the same direct memset approach. The existing broader BFME1
ownership/dependency sweep is recorded in concat-link-20261012 and has not
been repeated without changed relevant inputs. No donor bytes were imported.
The older BitFlagsXfer log's ba7ddda donor citation was inspected: that commit
actually names AptAnimData::createRenderData, so it is not BitFlags evidence.

Official BFME1 master was fetched at a70037880c51ade71fd7b86b8939786b2aa0b818.
The overdue pointer update remains foreign-claimed as file:reference/open-bfme-1
by codex-a44d-root. Retained verified inputs and the old success stamp; no
successful freshness update is claimed. Comparative full-byte update
verification remains with that worker.

The index cohort still has other competing clear emitters in engine-wide
units. Their definitions and calls need independent evidence and claims;
the observer repair does not authorize clearing different mask layouts or
changing the real provider. SupplyTruckAIUpdate still has unresolved engine
methods and competing COMDATs. Broader closed-strict/link-cycle measurement
and the existing TheRecorder data-binding repair remain outstanding.
