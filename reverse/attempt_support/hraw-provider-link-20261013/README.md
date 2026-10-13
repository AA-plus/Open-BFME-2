# HRawAnim channel provider reconciliation, 2026-10-13

Base BFME2 revision: f157490779fbf1c4d2180e6e6ad5ba59ad6345e5.
The supplied local index measured d753dedd98 at 2026-10-12 22:20;
committed link_status instead measures 3906ea7b97. Both supplied leads;
only the bounded current-object before/after preview below is credited.
No census build/history, full link cycle, nightly or boot operation ran.

## Supported change and target evidence

hrawanim.cpp exclusively defined Free, read_channel, add_channel and
add_bit_channel. HRawLoadW3D.cpp already emits interchangeable inline copies.
Claimed both files and all six affected retail extents before editing.
Bounded preparation verifies both units with self-strict reusable receipts.
The loader's channel helper bodies independently reproduce their complete
119/192/25-byte retail rows; the reader's 11-byte unwind funclet and 10-byte
EH handler also verify there using the existing parent EH-state proof.
Existing target evidence and byte gates check the switch table and fade arm;
no identity, layout, boundary or parent is newly inferred from proximity.

Use add_match --replace-existing to move those five existing ledger rows
into the loader, then remove the three duplicate definitions from hrawanim.
Make Free inline: both 50-byte copies retain their byte digest and named
relocations while the animation copy changes from exclusive to SELECT_ANY.
Free remains rowed in hrawanim and used by its unchanged destructor.
The loader source, headers, flags, symbol pins and data names are unchanged.
Object snapshots retain the bodies and relocations before and after.

## Donor review and freshness

Reviewed BFME1 clean verified pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
and fetched official master at 74845d1cb.
The foreign file:reference/open-bfme-1 claim belongs to codex-a44d-root;
the verified clean checkout and pointer were retained, with no success-stamp
advance. Comparative full-byte verification of the update remains outstanding.

Reviewed donor repairs 7fd167234d761efa08836645b8c86b120854be02
(GameAudio duplicate removal and dependent-row rehoming),
ba0053f07627f28a6988e9e0bbd04a3a47a29c22 (Win32BIGFile provider rehoming),
and af633c5de0cf6b64c885828c665a7a6f2aa00e2e (heap incidental emitter removal).
Their provider-reconciliation principle applies; donor bodies and offsets are
not imported. The existing animation and loader implementations carry the
BFME1/ZH semantic provenance; target rows, COFF bytes and relocations supply
independent proof that this local ownership repair preserves retail code.

## Acceptance and improvement

Commands were run sequentially around the edit:

```
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D.cpp
# move rows using verified add_match; edit source
./build.sh Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D.cpp
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/hrawanim.cpp Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D.cpp
```

Both preparations and the scoped normal byte gate pass 32/32 rows:
one string literal, 17 float literals and two imports, zero baselined or
skipped references. Both objects are self-strict current before and after;
this is not a closed-strict link closure. Each relocated row passed its own
add_match gate as well. The frozen-source check passes for both units,
check_csv passes (87,113 functions; 17,272 symbols; 307 data rows),
converged data passes (eight addresses, zero second names or unjudged rows),
and git diff --check passes.

Legacy current-object preview removes four duplicate blockers in each unit,
with no added blockers: hrawanim 9 -> 5, loader 10 -> 6.
Both previews return 1 because unrelated blockers remain; 0/2 clean and
LINKED 0 -> 0. Their combined authored coverage remains 6,341 bytes;
346 existing authored bytes merely change owning unit. No new authored bytes,
closed-strict gain or real link.exe placement is claimed.

HRawAnim still has WeightInfoStruct deleting-destructor and selected
MotionChannel helper conflicts. The loader still has RefCount/Hashable
variants and HAnim/HRawAnim vtable conflicts. A refreshed census and full
link closure require the maintainer lane. This repair leaves those distinct
blockers for subsequent supported work without repeating failed attempts.
