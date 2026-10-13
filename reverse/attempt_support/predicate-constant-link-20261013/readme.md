# Predicate float dependency repair

Source: `Code/GameEngine/Source/Common/Rva005D9CE0.cpp`.
Existing matched row: `?rva005D9CE0@Rva005D9CD5@@UAE_NPAVObject@@@Z`,
RVA `0x005D9CE0`, extent 76 bytes. Preparation base:
`3eb71d7fdf3da80e66740ac6fb89c371f2dafb54`.

The predicate formerly depended on the undefined address-named float
`?g_00C76420@@3MA`. Retail's `fld` operand loads RVA `0x00876420`, containing
`0x3E99999A`, the exact single-precision representation of `0.3f`.
Replacing that extern with the literal leaves all 76 object body bytes and
both call relocations unchanged. Only the data relocation changes, from the
unowned global to MSVC's `__real@3e99999a`. The normal float-reference gate
verifies that compiler literal against retail.

Target evidence is in `objects-before.json`, `objects-after.json` and
`comparison.json`. A full image scan for VA `0x00C76420` finds only the `fld`
operand at RVA `0x005D9D17`. The value sits immediately before the predicate
class's vftable at RVA `0x00876424`. Its treatment as a compiler literal is an
inference from this use and placement, verified bits and compiler emission;
the scan does not establish the absence of indirect writes. Retail's `.rdata`
section has writable PE characteristics `0xC0000040`, so section permissions
are not evidence of immutability. No new identity, layout, pin, data row or
fold exception is claimed.

## Acceptance and measured improvement

The local census index is from `cb660e4d97`, dated `2026-10-13 04:02`, SHA256
`4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
This index is older than the committed link status; all numbers below refer
to the local index and explicit current objects, not that newer status.

- `python3 tools/link_check.py --prepare-current <source>` passes before and
  after: 1/1 matched row, strict reusable compile receipts. These receipts
  establish byte verification, not self-strict or closed-strict LINK closure.
- `./build.sh <source>` passes 1/1 row and one compiler float literal after the
  repair (`byte-after.txt`); no skipped references.
- `python3 tools/link_check.py <source>` changes from one unresolved global
  and 0 linked bytes to `LINKS` and 76 linked bytes (`link-before.txt`,
  `link-after.txt`). This is a **legacy local preview gain of 76 bytes**.
- The unchanged direct call providers are
  `AIUpdateInterface_getCurrentVictim.cpp` and `AISPecialPowerTargetAoE.cpp`.
  Their byte gate passes 12/12 rows, two string literals and ten float
  literals (`callee-byte-gate.txt`). Checking both providers together with
  the consumer gives 2/3 clean units and 23 -> 99 preview bytes
  (`link-callees-after.txt`). The AoE provider still fails its pre-existing
  `??_GRva0026119DFilter@@UAEPAXI@Z` COMDAT: first copy differs, no retail
  address. Thus no closed-strict gain is asserted.
- `data_check.py` reports zero findings; `--converged` reports zero second
  names and zero unjudged rows (`data-after.txt`). Class gate, declared-body
  check, new-COMDAT-variant check and ledger checks pass.
- `place_bodies.py <source>` finds zero additional bodies or pins
  (`placements.txt`). No function ledger growth or newly authored matched
  C++ bytes is claimed.

No full link cycle, census build/measure/history, nightly or boot runner was
started. The index and link status were not changed. Hook checks still run
normally on commit and publication.

## Donor review and handoff

Reviewed BFME 1 linking evidence at verified checkout
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`, including
`0835ab92bef30e3303e729a0ce09cf591368d0cd` (Apt extern ownership repair) and
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` (StringBase compare COMDAT repair).
The former supports investigating unowned dependencies; its data declaration
is not applicable here. The latter's template repair is inapplicable to this
float operand. No donor implementation or layout was copied.

The BFME 1 freshness check is overdue. Official master fetched to
`09f941a50d7cd0815c0dfebc78d704f4c4143c00`, but
`file:reference/open-bfme-1` is actively claimed by `codex-a44d-root`.
The verified checkout/pointer was retained; freshness was not marked complete.
That owner must finish the verified pointer update. Remaining broader closure
work includes the AoE COMDAT above and an authorized fresh census/full link
verification.
