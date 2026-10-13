# Tactical AI registry ownership repair

Base: `5568dbd5a8b0b5d6b45eba8af3bb34e64d14f95f`.
Scope: the two consumers in `sources.txt`; the third path is the unchanged
data provider, claimed and verified with them.

Both consumers declared `g_tacticalAIRegistry`, but the existing sole data-row
owner at VA `0x00DFEEF8` is `?g_00DFEEF8@@3PAVRva002A8F24@@A` in
`Code/GameEngine/Source/Common/Rva005EEA20Find.cpp`. Reuse that owner's exact
declaration and symbol. No new global, alias, pin, data row or layout is added.
The semantic registry label comes from the existing consumer reconstruction;
this repair establishes ownership from target operands and the data row, without
claiming an independently recovered retail global name.

Target evidence in `objects-before.json` and `objects-after.json`:

- Build-facility body `0x0033AA1F`: DIR32 operands at offsets 471 and 486
  have zero object addends and native VA `0x00DFEEF8`.
- Enemy-search body `0x002FF07B`: operands at offsets 451, 540 and 737
  have the same zero addends and native address.
- Provider body `0x005EEA20`: operand at offset 6 loads the same address;
  its object defines the existing data-row symbol.
- Every complete matched row retains its body hash and extent. All relocation
  tuples are identical after substituting only the registry symbol. The
  provider's entire object hash is unchanged.

## Acceptance and limits

`python3 tools/link_check.py --prepare-current --paths-from sources.txt`
(using this directory's full path) passed before and after: three explicitly
claimed providers, one data row, 8/8 functions, two string literals, ten float
literals and two imports. All objects have strict reusable compiler receipts.
These receipts establish current byte-verified inputs; they do not establish
self-strict or closed-strict link closure.

`./build.sh` on both touched paths passed 7/7 functions plus all literal and
import checks. Converged-data enforcement passed with no second names or
unjudged rows. Class and declared-definition checks passed; `git diff --check`
passed. `place_bodies.py` on both touched units returned zero bodies and pins.
The shadow data checker retains one pre-existing enemy-search static-local
wrong-name finding at RVA `0x009FF108`. Comparing captured relocations with
identical body bytes removes exactly the two registry wrong-name findings and
adds none; see `shadow-data-comparison.txt`. No baseline is changed.

The plain local `link_check.py --paths-from sources.txt` preview changes from
1/3 accepted units (166 bytes) to 2/3 (833 bytes): **667 existing authored bytes
newly accepted in this legacy preview**. Both registry unresolved findings are
removed; enemy search retains eight unresolved names and three COMDAT findings.
Its full remaining list is in `link-after.txt`. The preview exits 1 because
that unit remains blocked, with no new findings. The index measurement is
`cb660e4d97`, 2026-10-13 04:02, SHA256
`4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
Committed status was a different, later measurement (`e181b4b6c5`); it is not
used to manufacture a gain or ranking. No census/status artifacts are edited.
New authored C++ bytes: zero. Self-strict and closed-strict gains: unmeasured.
Full link-cycle and runtime validation remain maintainer-only follow-up.

## Reference review and freshness handoff

Reviewed BFME 1 repair `0835ab92bef30e3303e729a0ce09cf591368d0cd`
(typed string-pool owner bindings): the existing-owner reuse principle applies,
while BFME 2 addresses and types are established locally above. No donor source
or headers are changed. Also reviewed the compare-COMDAT binding repair
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` while checking other ranked leads;
it is not needed for this repair.

The verified BFME 1 checkout remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Fetch found official upstream
`476ccf2c4b32c6f2ff170ec06aac4a4c2cc42fcc`; updating the pointer is currently
claimed by `codex-a44d-root` (`file:reference/open-bfme-1`). Preserve the
verified inputs and leave the overdue freshness timestamp unchanged. The owning
seat must complete and verify that update; this seat does not duplicate it.
