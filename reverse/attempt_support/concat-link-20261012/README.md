# Literal concat provider repair, 2026-10-12

At BFME 2 checkout `58b8d20f86225fc78ccbfd3009bc3be748d11fd9`, the local
census index measured at `d753dedd98` (2026-10-12 22:20) reports
`?concat@AsciiString@@QAEXPBD@Z` as the sole selected-definition blocker of the
five consumers in `sources.txt`. The committed link-status snapshot is older
(`b3f2efabf3`); it was used only for initial queue discovery. No per-row data-back
artifact was used and no census counters were edited.

## Target evidence and change

The existing ledger owns the 37-byte retail function at RVA `0x00005629` as
`?concat@?$StringBase@D@@QAEXPBD@Z`, in
`Code/Libraries/Source/WWVegas/WWLib/string_base.cpp`. Retail calls from the six
edited bodies go directly to that RVA; see `retail-calls.txt`. The selected
AsciiString COMDAT in
`ScriptEngine_appendMessage_Rva00341350AdjustVariableForwarder.cpp` instead
adds a forwarding wrapper. Its machine body is not the retail callee. An existing
alternatename cannot override that real definition.

Bind the literal-argument calls in five consumer units directly to the existing
StringBase<char> provider, using their existing one-pointer AsciiString view.
No new type layout is asserted: this cast follows the established canonical
AsciiString/StringBase relationship. Independent target proof is the retail
call destination and the complete byte/relocation gate for both callers and
provider. String-object overloads retain their existing bindings. No new pin,
alias, header shim, global or ledger range is introduced.

Edited body boundaries already recorded in the target ledger:

| Consumer body | RVA | Extent |
| --- | --- | --- |
| AptPlayer::AddLevel | 0x00224710 | 264 |
| AptPlayer::WinCreate | 0x00223263 | 323 |
| GameLogic::bfmePopulateGameReport | 0x00247378 | 1463 |
| ScriptEngine::evaluateAndProgressAllSequentialScripts | 0x0020C83F | 1379 |
| gogoMessageBox | 0x002C263A | 1214 |
| GameInfo::setMap | 0x00400126 | 1030 |

## Reference review

Reviewed committed BFME 1 input
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`, including these linking repairs:

- `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`: AsciiString compare consumers
  bind the actual StringBase compare provider. Applicable direct-provider
  principle; the compare specialization itself is not needed here.
- `deeae989b713ba5f8b0eaba98d5cd7406257acda`: PartitionFilter calls bind its
  real owner rather than a private inline alias. Applicable relationship
  principle; no PartitionFilter repair imported.
- `111dce8c7451589eb5414c0f647bb680e1da4371`: direct WideAllocPtr ownership.
  Applicable provider principle, different target dependency.
- `07f3e53eb83b4ff95d5138c4eb2bd8221e8509d0`: named datum repairs. Inapplicable
  to this code-only blocker.

These donor repairs are leads, not target ABI proof. The local adaptation above
is justified by BFME 2 retail and gates, rather than donor bytes. Freshness fetch
found official BFME 1 master at
`6b56fcc9d3cfa1df71567f2c3f20e72f8a324462`. Updating the submodule was blocked by
the live foreign `file:reference/open-bfme-1` claim (`codex-a44d-root`); retained
the committed verified input, did not change the pointer or freshness success
stamp. The pending update still needs its full comparative byte verification.

## Acceptance and measurement

`./build.sh` for the six sources in `sources.txt` passed: 79/79 rows, 67 string
literals plus 29 empty-string references (zero baseline/skips), and five named
imports. AptPlayer's two funclet labels were renumbered; the gate proved their
parent EH placement without changing the ledger pins. See `byte-gate.txt`.

`python3 tools/link_check.py --prepare-current` for the same six sources passed
on the final edits, producing six strict reusable self-verification receipts.
See `strict-prepare.txt`. This checks the providers' own bytes; it does not prove
closed-strict dependency closure.

Ordinary `python3 tools/link_check.py --paths-from .../sources.txt` before and
after the changes is a **legacy census preview**, not a closed-strict or actual
link.exe measurement. All five consumers change from blocked to LINKS with the
provider checked alongside them. Aggregate preview: 1/6 and 1,185 bytes before;
6/6 and 9,065 bytes after, a gain of **7,880 existing authored bytes**. Per-unit
consumer gains: AptPlayer 2,726; PopulateGameReport 1,458; sequential scripts
1,375; message box 1,205; GameInfoSetMap 1,116. See `before-link.txt` and
`after-link.txt`. New authored C++ bytes: zero. No closed-strict gain is claimed.

All five source files passed find_declared_unmatched before and after edits.
The batch retains all existing rows and markers. Ledger validation and normal
commit/push hooks remain required. No maintainer-only full link cycle, census
build, nightly or boot verification was started.

## Remaining work

The ranked cohort has more consumers of the same selected wrapper. Highest
remaining sole-blocker leads include ControlBarScheme_setControlBarSchemeByPlayerTemplate,
Rva000A9F48FileOpen, ControlBarInitSpecialPowerShortcut, W3DShrubBufferAddTreeType,
and W3DTreeBufferAddTreeType. Recheck live claims/current objects and prove each
retail call before applying the same repair. The forwarding definition remains
for other consumers; this batch changes only the five checked units. Broader
closed-strict/link-cycle measurement and the claimed BFME 1 freshness update
remain outstanding.
