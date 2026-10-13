# Code-address setter link repair

Session base: 6911349f2e. The available runner census index measures
`d753dedd98` at 2026-10-12 22:16. The committed status snapshot at
2a20912cc9 serves discovery only; no matching per-row data-back artifact
was used. No census/index/status was changed.

## Target evidence and change

The existing 11-byte setter row at 0x0028576D stores VA 0x006D7B50 at
this+0x9C, then returns. Its before object is identical to all retail
bytes, with no relocations. That VA is the entry of the existing matched
27-byte `rva002D7B50(int, int)` provider at RVA 0x002D7B50 in
VslotSmallBodiesAG.cpp. The provider checks TheDisplay and forwards its
arguments to virtual slot 82. This change declares that existing free
cdecl function and stores its address as an unsigned int. The owner's
identity and slot's purpose remain unknown; no new class layout or
semantic identity is inferred.

The after object preserves every byte except the four-byte address slot,
which now carries a zero-addend DIR32 relocation at +6 to exactly
?rva002D7B50@@YAXHH@Z. Its ledger entry supplies the same retail address.
The provider's complete bytes and TheDisplay relocation are unchanged.
No pin, alias, fallback, global or escape hatch is added. The source-wide
hard-coded address count drops from one to zero. No other code uses the
same literal after a tracked-source search; only this source is edited.
The current listener-walk unit from the address ranking already links,
so no redundant repair was attempted there.

## Donor review and freshness

Reviewed BFME 1 donor repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d:
it removes non-retail local string constructor wrappers and declares the
existing provider. Also reviewed d456456cd56156428c28a2f7cad49e396cc4d916,
which removes a wrong local terrain helper. Their dependency reconciliation
principle is relevant; their string/terrain names, bodies, ABI and layouts
are inapplicable to this setter. This repair rests on BFME 2 target bytes
and its own matched provider, and imports no donor code.

Official BFME 1 master was fetched to d456456cd56156428c28a2f7cad49e396cc4d916.
The clean verified pointer remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The overdue comparative freshness update is held by codex-a44d-root's
file:reference/open-bfme-1 claim. No pointer or freshness stamp changed.

## Acceptance and remaining blockers

- Consumer and provider before/after explicit strict preparation: 28/28
  bodies pass ordinary source, full-byte, string, float and import gates,
  with reusable strict-current compiler receipts. These prove compiler
  currency and byte identity, not self-strict or closed-strict link closure.
- ./build.sh for both full units passes 28/28 after the change. Object
  assertions prove the relocation, zero addend and unchanged provider.
- Same two-source ordinary local legacy preview: 0/2 files and 0 bytes
  before; 1/2 files and 11 bytes after. The consumer alone passes exit 0.
  The provider still reports nine unresolved names, unchanged. Its 705
  authored bytes do not gain acceptance. Full transcripts name the nine
  unresolved provider dependencies.
- Declared-definition, ledger and converged data checks pass. No tests
  were added for this address binding. Ordinary data shadow findings,
  if any, are retained in checks.txt; none is a new reference from the
  consumer.

There are zero new authored C++ bytes and an 11-byte local legacy link
preview improvement at the named old census. A new runner census and
maintainer-authorized full link cycle remain outstanding; no measured
closed-strict gain is claimed. All unrelated untracked source dumps and
ZH sweep preparation were preserved.
