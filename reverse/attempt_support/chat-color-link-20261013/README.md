# GameSpy colour-table consumer reconciliation

Base checkout 7bfa489c57eb1aba511b992d890a534459a74f9d. Local census index:
d753dedd98, 2026-10-12 22:20. repair_queue serves the newer committed status
at 3906ea7b97 (2026-10-13 05:18), which is only a lead for this older index.
No per-row data-back artifact was available or used to manufacture rankings.

Four active consumers declared an undefined scalar ?g_00DB9198@@3HA.
They now declare the existing Chat.cpp array ?GameSpyColor@@3PAHA and read
index 0 (max-ping, clan list, owner message) or index 8 (buddy message).
No provider, array initializer, header, class, pin, extent or compiler flag
changed. The unused declaration in AptOnlineCustomMatchPlayerTooltip was
left alone and its claim released. AptOnlineQuickMatchOptions is foreign
claimed and remains an outstanding active consumer of the old name.

Target evidence: each consumer's full matched native body proves DIR32
VA 0x00DB9198 with addend 0 or 32. The independent complete native parser
0x001EF471 passes the same base using Chat.cpp's defined GameSpyColor.
The data ledger records that provider and address. Six relocation witnesses
(one parser operand, five consumer operands) retain their source, body,
offset, type and addend before and after. The two JSON snapshots also record
object hashes and strict compiler-receipt currency. The array name/type is
carried from the existing ZH-derived provider; this repair introduces no new
original-name, whole-array layout or initialized-data verification claim.

BFME 1 review: verified checkout/gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
retains the ZH Chat.cpp provider. Linking repair
908413c254f83e1f402b991541d4cf68db48ea4e reconciles three Apt consumers to
an existing data provider. That name/type reconciliation applies here; Apt
addresses, layouts and code do not. No donor code was imported. Official
master fetched at c54240071; its overdue freshness update remains held by
codex-a44d-root's live file:reference/open-bfme-1 claim. The verified inputs
and successful-check stamp were preserved pending comparative verification.

Acceptance: bounded self-strict preparation before/after verifies all five
explicit sources and strict reusable receipts; ./build.sh verifies 67/67
matched bodies, 57 string literals plus 17 empty refs and four named imports,
zero baselined/skipped references. find_declared_unmatched and check_csv pass.
Ordinary data_check reports zero findings. Enforced converged check: five
sources, eight addresses, zero second names or unjudged rows.

Local legacy preview checks provider and consumers together against the same
index, refreshing the five explicit current objects in memory. Four unresolved
colour-table blockers disappear. The automated comparison confirms every
other unresolved, COMDAT and selected-definition finding is unchanged. Both
previews exit 1: zero of five units clean, zero linked bytes, zero new authored
C++ bytes. This is a verified blocker reduction, not a closed-strict gain or
a full-link placement result. No broad --refresh census compilation was run.

Remaining blockers: max-ping's g_00E0654C; clan list's rva0057F5ED; BuddyDefs'
rva00517CC9 and string/constructor COMDATs; custom-match's independent calls,
globals and STL COMDATs; Chat's AudioEventRTS/STL imports and COMDATs. Detailed
before/after transcripts are adjacent. These were not retried. Whole-array
initialized-data repair and maintainer-only full linking remain separate work.
