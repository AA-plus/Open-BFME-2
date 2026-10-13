# LOD selector consumer link repair

Base checkout: `70d03c01b7655879ba5e565709414ce4b3820534`.
The restored local census index measures `d753dedd98` at 2026-10-12 22:16;
repair_queue's committed status measures `f6c432fac6` instead. Queue status is
only a lead. Both previews use the same explicit three current objects over
the restored index; no census, status, history or measurement artifact changed.

## Target evidence and change

GlobalGetterSingles.cpp already provides the single integer
`?LODTextureReduction@@3HA`, initialized to 2. Its getter at RVA 0x0006E16F,
the setter at 0x00201D34 and updateFixedLightEnvironments at 0x0006E716 all
have zero-addend DIR32 operands targeting VA 0x00DB5FA0. Before this repair,
the latter two reference the undefined old name `?g_Va00DB5FA0@@3HA`.

Both remaining old-name consumers now declare and use LODTextureReduction.
The existing provider and the body's behavior, layouts, compiler flags,
identities and extents are unchanged. No new global, alias, pin, ledger row,
header or escape hatch was introduced. `relocations-before.txt` and
`relocations-after.txt` record each operand, receipt and object hash.
The existing name is also used by GameLODApplyPreset and fxshadersetup;
this repair does not newly infer an original retail source spelling.

## BFME 1 review

The verified donor checkout/gitlink remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Reviewed donor repair
`908413c254f83e1f402b991541d4cf68db48ea4e`, which reconciles Apt pool externs
with their single existing provider. That name/type reconciliation applies;
its Apt body, address and layout do not. No donor code was imported.

Official upstream was fetched at
`cad8b7c5926ae06e9ed769454a6af23d3818ef4b`. The overdue freshness update
remains held by codex-a44d-root's live file:reference/open-bfme-1 claim.
The verified pointer, checkout and success stamp were preserved pending that
owner's comparative verification. No updated donor headers were substituted.

## Acceptance and result

- Bounded self-strict preparation before and after: all three explicit sources,
  36/36 matched bodies and one data row byte-verified with strict reusable
  receipts. Three compiler float literals verified; zero string or import
  references skipped or baselined. Self-strict is receipt evidence, not closure.
- `./build.sh` on the same three sources: 36/36 exact, data/source/float gates
  pass (byte-gate.txt). Frozen-file checks pass before and after.
- Ordinary local legacy link preview: **1/3 and 136 bytes before; 2/3 and
  1,463 bytes after**, a gain of **1,327 existing authored bytes** from the
  scene unit. The provider remains LINKS136. GapBodiesGE53 loses the selector
  unresolved blocker but retains g_00DB9448, g_Va00DEC410 and duplicate plus
  wrong-selected Rva000427195 copy-constructor findings; it receives no gain.
  The three-source preview exits 1 both times because that unit still fails.
- The accepted provider/scene pair exits 0 (accepted-pair.txt).
- Enforced converged-data check: three sources, eight addresses, zero second
  names and zero unjudged rows. Ordinary data_check remains shadow: the data
  ledger still names this slot g_Va00DB5FA0 although its existing provider was
  already renamed. It reports LODTextureReduction wrong-name in all three
  units, plus the provider's unrelated existing animation-clock name. This
  stale ledger naming was not hidden or baselined (data-check.txt).
- check_csv accepts 86,932 function rows, 17,263 pins and 298 data rows.
  git diff --check passes.

New authored C++ bytes: zero. The 1,327-byte gain is a local legacy preview
against the named older index. No closed-strict gain, refreshed global census
or actual full-link success is claimed. Maintainer-only full linking remains
outstanding. The gap unit's four independent blockers remain for other repairs.
