# HTree motion-channel provider reconciliation

BFME2 base: 08433cfedd8193ce63663310fd8a4ca9a7e09b65.
Local index: d753dedd98, measured 2026-10-12 22:20 UTC.
The committed link-status snapshot measures 3906ea7b97; it served discovery
only. No index, census status/history, or per-row data-back artifact changed.
No census build, full link cycle, nightly, boot or scheduler operation ran.

## Target evidence and change

The index and current strict objects show three competing channel helpers:
HTree's ZH header emits wrong bodies using Data/FirstFrame/LastFrame at
+0x18/+0x1C/+0x20, while HRawAnim's existing rowed providers at 0x0015FFD0,
0x00160010 and 0x001600A0 use the target's +0x14/+0x18/+0x1C layout.
The existing bfmehrawanim/motchan.h documents independent target access and
allocation evidence: read_channel allocates 0x20 bytes, and Get_Orientation
reads the unpooled channel fields at those offsets. This repair carries that
existing layout evidence; it does not newly infer HTree's unmatched methods.

Add a declaration-only opt-in around those three existing inline definitions.
The ordinary declarations have no inline specifier; the default definitions
remain WWINLINE. HTree includes that existing shim by its anchored path with
the opt-in, so its reads bind to the rowed HRawAnim providers without emitting
competing COMDATs. The provider's default behavior and source are unchanged.
There is no new pin, alias, private class copy, compiler flag, ledger row,
boundary, or recovered identity. File and class claims preceded the edit.

A first bounded trial selected the correct layout but retained inline
bodies; all five HTree rows passed, yet its /O1 63/122/100-byte helpers still
lost to the rowed 64/130/110-byte providers. The declaration-only change
resolves that supported compiler difference. The wrong bodies are removed,
rather than assigned another address or excused by a gate exception.

## Donor review and freshness

Reviewed clean verified BFME1 pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
and repairs 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 (compare-provider
reconciliation) and d3f9000fe08615a100e844adfff57fa4a39cd615 (incidental
constructor emitter removal). Their provider-selection principle applies;
neither donor body nor layout is imported. Original ZH semantic provenance
and the target-backed existing BFME channel shim remain the code's basis.

Official BFME1 master fetched as 1d28b4a25bc1aba695e0ef571836cf7e4f2b7732.
Its overdue pointer/freshness update remains foreign-claimed by codex-a44d-root
as file:reference/open-bfme-1. Retained the verified clean checkout/gitlink
and did not advance the success stamp. Comparative full-byte verification
and pointer publication remain with that owner.

## Acceptance and improvement

Before and after, prepare-current was bounded to htree.cpp and hrawanim.cpp:
27/27 rows exact, 19 float literals verified, zero baselined or skipped string
references. Both objects have self-strict reusable receipts. Only these two
current dependency manifests include the touched header. The ordinary byte
gate also passes 27/27; preparation runs the normal gates independently.
Object snapshots retain complete helper bytes and named relocations.
The HRawAnim providers' digests remain e0784f33d47e / 58da3d5dc3fa /
0b3fafa2fac1. HTree emits none of those helpers after the repair.

Ordinary local link_check on both current objects against the same index:
HTree 27 -> 21 blockers (three COMDAT and three selected removed);
HRawAnim 5 -> 2 blockers (three selected removed). No blockers added.
This is a **legacy current-object preview**, supported by self-strict inputs,
not a closed-strict link closure. Both previews return 1: 0/2 units clean,
LINKED 0 -> 0 bytes. Existing authored coverage is unchanged (867 + 4,967).
No new authored bytes, closed-strict gain, or actual link placement is claimed.

find_declared_unmatched accepts HTree before and after, retaining the existing
13 unclaimed definitions; check_csv passes 87,179 functions, 17,268 symbols,
307 data rows. Enforced converged-data check passes both sources: eight
addresses, zero second names and zero unjudged rows. git diff --check passes.
The normal commit/push hooks still must run, including their full header gate.

Remaining HRawAnim blocker: WeightInfoStruct vector-deleting-destructor
COMDAT/selected conflict. HTree retains independent unmatched-animation,
Pivot, WeightInfo, matrix/interpolation and animation-combo provider conflicts.
Their layouts and bodies need separate evidence-backed repairs; the three
motion helpers should not be retried. Broader placement measurement remains
a maintainer-lane operation.
