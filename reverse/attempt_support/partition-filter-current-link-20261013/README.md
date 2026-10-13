# Partition-filter current-provider acceptance, 2026-10-13

Source revision: `1a3e876e12` (full ID in receipts.json).
Local index measurement: `cb660e4d97`, 2026-10-13 04:02 UTC.
Committed link status instead measures `e956901d31`; it supplied leads only.
The index, link status and census history were not rewritten.

## Result

The ranked queue serves ten consumers whose sole indexed blocker is
`??_GRva0026119DFilter@@UAEPAXI@Z`. Nine still own matched rows; the former
Rva005EEBF6Tally.cpp path has been removed and was excluded after preparation
correctly refused it as an unowned provider. Its file claim was released.

Bounded strict preparation of PartitionFilterCtorCopies.cpp and those nine
current consumers recompiles five units and reuses five. The provider's
current deleting destructor is the same 28-byte call-based copy as the nine
consumers. Its indexed copy was a 29-byte inline-vptr-reset variant. The
current ordinary destructor is seven bytes, resetting the base vptr. These
are object and relocation facts, not a new recovered destructor identity:
the derived deleting-destructor name has no retail address in the index.

No production source edit was needed. This commit records fresh acceptance
evidence rather than changing code solely to reproduce already-current
compiler output. It adds no function, pin, alias, class view, marker, compiler
flag, baseline or verifier exception. New authored C++ bytes are zero.

## Checks and limits

All ten files were claimed before strict preparation. Commands:

```
python3 tools/link_check.py --prepare-current --paths-from sources.txt
python3 tools/link_check.py --paths-from sources.txt
python3 tools/link_check.py --census-only --paths-from sources.txt
python3 tools/data_check.py --converged <the ten sources in sources.txt>
python3 tools/find_declared_unmatched.py <constructor provider> <AoE consumer>
python3 tools/check_csv.py
```

The preparation transcript proves **57/57 rows** across ten sources, eleven
string literals, 25 float literals and zero skipped/baselined string or import
references. All ten inputs have self-strict reusable receipts; receipts.json
binds their source, object and receipt hashes to this source revision and
index. object-current.txt inventories both destructor bodies and every
relocation for each unit.

The census-only preview is **0/10 clean, zero bytes**. The current-object
preview against that same index is **9/10 clean, 6,098 existing authored
bytes**. Both commands exit 1 because the constructor provider still has
thirteen unresolved allow methods; their complete names are in the transcript.
This is a **legacy census preview** with self-strict input evidence, not a
closed-strict gain or actual link.exe placement. No broader gain among the
other filter consumers is counted. The nine units are listed individually
with their byte counts in link-before-current.txt.

The converged-data check accepts ten sources and eight addresses, with zero
second names or unjudged rows. The declared-definition check accepts the
provider and AoE consumer; the provider retains its existing 27 unclaimed
anchor definitions. check_csv accepts 87,056 functions, 17,278 symbols and
300 data rows. Normal commit hooks remain required.

## Donor review and handoff

Reviewed clean verified BFME 1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`: its clean-room
PartitionFilterFlammable destructor/deleting-destructor units separate the
base-vptr reset from the call-based deletion wrapper. The GeneralsMD
PartitionFilterAlive declaration supports the no-member derived-filter
semantics. BFME 2 object relationships and compiler bytes above remain
independent target evidence; no donor layout or identity was imported.
Reviewed donor repair `d3f9000fe08615a100e844adfff57fa4a39cd615` (suppress an
incidental TileData constructor): its emitter principle is applicable as a
lead, but fresh compilation removes the need for a source adaptation here.
Donor `0a3a4f6052f8c8d25c6c9fbfbf47047a2fe96fdd` (Miles empty string) is
inapplicable to this filter conflict.

The official freshness fetch reached
`6119f6921` (Open-BFME/Open-BFME-1 master). The overdue comparative update
remains foreign-claimed as file:reference/open-bfme-1 by codex-a44d-root.
Preserved the verified pointer, clean submodule and old freshness stamp.

Remaining work: the constructor provider's thirteen allow definitions,
the frame-pointer-sensitive Rva005EE816Rva005D7C3E filter variants,
ActionManagerSpecialPowerChecks' other filter emitter, and ObjectBroadcastEvent's
relationship-filter deleting destructor. These are independent blockers; this
receipt does not claim them repaired. NetPacket, WinMain, ScriptActions,
part_ldr and the listener-walk queue leads already pass local previews and
need refreshed measurement rather than another source edit. The existing
RvaF6Ret identity-collision deferral was not retried without new evidence.
No full link cycle, census build/measure/history, nightly, boot or scheduler
operation was started. All session claims are released at handoff; unrelated
untracked reverse/zh_sweep work is preserved.
