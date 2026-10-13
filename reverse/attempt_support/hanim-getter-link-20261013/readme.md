# Animation getter provider repair, 2026-10-13

BFME 2 base: `19e6bde293206ab2a3f2b2d6522599abdeffcc45`.
The supplied local index measures `d753dedd98`, 2026-10-12 22:16 UTC.
The committed status/history instead measures `67e1365aa9`, 2026-10-13 16:47;
it supplied queue leads, not this before/after measurement. No per-row
data-back artifact was used. File claims cover both checked units; RVA claims
cover `0x00196670` and `0x00196740`.

## Evidence and change

The existing ledger owns HAnimComboClass::Get_Motion (23 bytes, 0x00196670)
and Get_Pivot_Weight_Map (27 bytes, 0x00196740) in
HAnimComboClassGetMotion.cpp. Its complete bodies, including the final RET 4,
equal retail with zero relocations. Both use ADD for the refcount increment.
The otherwise matched hanim.cpp additionally emitted 22- and 26-byte bodies
with INC instead. Its existing split-provider comment explains the compiler
difference: the getter provider uses /G7, while hanim.cpp's matched Set_HAnim
requires the INC-producing settings. Changing the whole unit's flags would
invalidate that established match.

Remove those two unrowed competing definitions and their present-unmatched
annotations from hanim.cpp. Preserve the established getter provider and all
compiler settings. The changed object defines neither getter; its existing
Normalize_Weights implementation now references Get_Pivot_Weight_Map. No
matched definition was deleted. Target facts here are the complete native
instruction sequences and the existing row ownership; class names and donor
semantics are inherited from the previous recoveries. No new layout or identity
claim is made.

An additional read-only object inspection finds a byte-exact inline copy of
Get_Pivot_Weight_Map in HAnimComboBFME1.cpp. That object is not self-strict
current, so this inspection is only a follow-up lead, not accepted closure
evidence. It still accounts for the getter provider's remaining duplicate in
the supplied index. Removing its inline body needs separate investigation:
the unit's matched normalization code uses it.

## Donor review and freshness

Retain the clean verified BFME 1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Reviewed donor repair
`5fa9bfd662c427a198176b0b727c4c11d0965733` (Anim2D lookup cleanup bound to
canonical string release): its existing-provider reconciliation principle
applies here, while its string implementation and layout do not. Also reviewed
`0835ab92bef30e3303e729a0ce09cf591368d0cd` (Apt string-pool data ownership);
its data-specific change is inapplicable. Inspected the retained hanim source
and the already ported split getters; imported no new donor implementation.

The required official BFME 1 freshness fetch failed with HTTPS authentication
(`could not read Username`, terminal prompts disabled). Preserve the verified
pointer and overdue success stamp. The previous comparative-update verification
remains outstanding. BFME 2's initial pull succeeds with recursive submodule
fetching disabled locally; claims likewise use the upstream BFME 2 remote.

## Acceptance and limits

- Ordinary byte gate: **27/27** rows exact across the changed emitter and owned
  getter provider, including hanim.cpp's EH handler and funclet. The funclet's
  local label renumbering is verified from its parent's EH data by the normal
  gate.
- Bounded strict preparation before and after: both explicit sources have
  current reusable strict receipts and pass the ordinary byte/reference gates.
  These are **self-strict** witnesses, not closed-strict closure.
- Local preview checks emitter and provider together against the same supplied
  index. hanim.cpp findings: duplicates **24 -> 22**, wrong COMDAT copies
  **40 -> 38**, wrong selected providers **38 -> 36**. Getter-provider findings:
  duplicates **2 -> 1**, wrong selected providers **3 -> 1**; its two other
  COMDAT findings remain. **Nine findings removed**, zero added. Both preview
  commands return 1 because independent blockers remain.
- Legacy LINKED remains **0 -> 0** for the two units; they retain **964 existing
  authored bytes**. Authored C++ byte growth is zero. The change removes two
  present-unmatched annotations without introducing a new escape hatch.
- Converged-data audit: two sources, eight addresses, zero second names and
  zero unjudged rows. An audit concurrent with strict recompilation reported
  moved objects; the final sequential audit is the accepted result.
- Declared-definition check, ledger check and git diff whitespace check pass.
  Source and complete before/after acceptance outputs accompany this record.

Remaining blockers include the inline pivot getter copy, RefCountClass::Add_Ref
and WeightInfoStruct teardown COMDATs, and the shared animation unit's other
duplicate providers and compiler-shape differences. Census/index/status were
not rewritten. No full link cycle, census build/history, nightly or boot runner
was started; broader linked-byte gains require current closure evidence.
