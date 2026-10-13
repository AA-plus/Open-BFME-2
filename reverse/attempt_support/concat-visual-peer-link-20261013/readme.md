# Particle visual initializer concat provider repair

Base checkout: `7b67da84acce05ea970a46ae25d0bfa0406a923e`.
Local census measurement: `d753dedd98`, 2026-10-12 22:16; exact index
hash is in `index-meta.json`. The committed repair queue's newer measurement
`2a20912cc9` was used for discovery, not as the local preview's measurement.

## Accepted change

`ParticleControlCtorFamily.cpp`, initializer at RVA `0x003fd849`, extent
346, binds its literal concat directly to the existing `StringBase<char>`
provider. Retail REL32 at body offset `0xdf` reaches `0x00005629`;
the unchanged string-object overload at `0xe8` reaches `0x00006987`.
The before/after call inventories preserve these distinct retail targets.
This changes a linker symbol binding, with no new identity, layout, pin,
header, flags, alias or function-row claim.

Provider/consumer verification:

- `./build.sh Code/GameEngine/Source/Common/System/ParticleControlCtorFamily.cpp`:
  13/13 rows pass, including two compiler-renumbered funclets verified from
  parent EH data. See `visual-gate.txt`.
- `python3 tools/link_check.py --prepare-current
  Code/GameEngine/Source/Common/System/ParticleControlCtorFamily.cpp
  Code/Libraries/Source/WWVegas/WWLib/string_base.cpp`: 50/50 rows pass;
  final objects have self-strict reusable receipts. See
  `visual-provider-final-gate.txt` and `final-receipts.json`.
- Local `link_check.py` on the same two explicit sources: 10 findings before,
  9 after. Only the selected literal `AsciiString::concat` finding disappears;
  no findings are added. The provider remains LINKS at 1,185 bytes; the consumer
  remains blocked at 0 linked bytes. See before/after logs and `link-delta.json`.
- `find_declared_unmatched.py` accepts the consumer. `check_csv.py` passes
  (87,203 function rows, 17,268 symbols, 307 data rows).
  `data_check.py --converged` accepts both sources: 8 addresses, no second
  names or unjudged rows. `git diff --check` passes.

The link result is a legacy local preview against the stated census with
self-strict consumer/provider objects, not a closed-strict result. No census,
link-status or index is changed. New authored C++ bytes and linked-byte gain
are both zero. Remaining consumer findings are three missing virtuals, two
Matrix3 Rotate_Z copies, three STL vector/allocator copies and the selected
Matrix3D copy constructor. A full link cycle was not run.

## Donor lead and freshness

Reviewed BFME 1 donor commit `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`
(portrait compare provider binding, 36/36 verification). Its direct-provider
approach is applicable; BFME 2 call bytes and the existing provider independently
establish this repair. No donor compare body or offset is imported.

BFME 1's committed clean pointer is `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Official master was fetched at `61a7c39c3dd2b0e327fc71e28d22f37c02d9f2ce`.
The overdue pointer update is held by another worker's live
`file:reference/open-bfme-1` claim (`codex-a44d-root`); verified inputs were
preserved and the success stamp was not advanced.

## Rejected GameSpy consumer

`GameSpyInfo::setGameOptions`, RVA `0x00386501`, extent 1,658:
retail literal concat targets at `0x38a`, `0x47a`, `0x4ca`, `0x5bb`, `0x5c8`
also reach `0x00005629`. Five direct bindings nevertheless change four
non-relocation bytes at `0x165`, `0x168`, `0x258`, `0x25b`, swapping wins/losses
stack homes and their later register loads. A second trial reversing their
declaration order has the same mismatch. Both ordinary byte gates refuse it;
the trial patches and gate reports are retained here only as evidence.

The entire trial was restored from the original source backup, and the restored
ordinary gate passes 1/1 (`peer-restored-gate.txt`). A blocked attempt was
recorded using `re_log.py`; the file and RVA claims were released. There is no
GameSpy source change in this repair. Resume only with evidence addressing the
stack-slot/codegen dependency, rather than repeating the two shapes.
