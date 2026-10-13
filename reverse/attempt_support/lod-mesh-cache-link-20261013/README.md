# Mesh-cache byte provider binding repair

Base checkout: `ffd77eb65a054743d2f468245d710a6414ad2a1e`.
The restored local census index measures `d753dedd98` at 2026-10-12 22:16;
the committed repair queue measures `f6c432fac6`. Only the former index is
used in the before/after previews. No census, index or status was rewritten.

## Target evidence and repair

GlobalByteGetters.cpp already defines the single unsigned-byte provider
`?LODMeshCacheSetting@@3EA`. Its getter at RVA 0x00171650, the setter at
0x00201D3E and Register_For_Rendering at 0x00173230 each emit one zero-addend
DIR32 operand targeting VA 0x00DEC410. Before this repair the consumers name
undefined `?g_Va00DEC410@@3EA` and `?g_0DEC410@@3EC`, respectively.
GameLODApplyPreset.cpp independently uses the existing LODMeshCacheSetting
provider and invalidates the mesh cache when that byte changes.

The two consumers now declare the owner with its actual nonvolatile type.
The renderer retains its volatile unsigned-byte read through a cast at the
use site, preserving its compiler shape and access qualification. The setter
uses the provider directly. No new datum, alias, pin, row, header, layout,
compiler setting or extent is introduced. The relocation transcripts prove
all three operands and the sole existing definition using self-strict reusable
receipts and object hashes. The existing provider spelling is reused; these
bytes do not establish an original retail source identifier.

## Donor review and freshness

Reviewed the verified BFME 1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` and repair
`908413c254f83e1f402b991541d4cf68db48ea4e`. That repair binds consumers to
an existing provider's exact declaration and casts at use sites. This binding
principle applies; its Apt bodies, addresses and layouts do not. No donor code
or header is imported, and no unchanged donor scan was repeated.

Official BFME 1 master was fetched at
`1ae4927bb` (FETCH_HEAD). Its overdue freshness update is held by
codex-a44d-root's live file:reference/open-bfme-1 claim. The verified clean
checkout, gitlink and prior success stamp remain unchanged pending that
worker's comparative full verification and publication.

## Acceptance and improvement

- Before and after bounded self-strict preparation: three explicit sources,
  24/24 matched code rows exact, normal source/string/float/import gates pass.
  No string, floating literal or import references are skipped or baselined.
- `./build.sh` for the same three units: 24/24 matched, all gates pass.
- Ordinary local link preview: exactly two unresolved references disappear;
  all independent findings remain unchanged. The provider stays LINKS66.
  Both consumers retain other blockers, so the preview stays 1/3 clean and
  66 -> 66 linked bytes and exits 1. This is an accepted binding improvement,
  not a claim that either consumer fully links.
- Enforced converged-data check: three sources, eight addresses, zero second
  names and zero unjudged rows. The shadow data check still expects the stale
  provisional g_Va00DEC410 in reverse/data_ledger.csv; binding the consumers
  to the actual provider raises its total from 14 to 15 and its outside-baseline
  findings from four to six. The provider's existing wrong-name report and
  unrelated LODTextureReduction/DEC3D7 findings are preserved, not baselined.
- The setter unit's hatch count falls 4 -> 2; the provider stays 34 and the
  renderer stays zero under the current counter. No hatch counter grows.
- Frozen-file checks, check_csv (86,940 functions, 17,265 pins, 298 data rows)
  and git diff --check pass.

New authored C++ bytes and new clean-unit linked bytes are both zero. Strict
receipts establish self currency; the link preview uses legacy definitions
outside this explicit cohort. Closed-strict closure and actual full linking
remain unmeasured; no maintainer-only runner was started.

Remaining blockers: the gap unit's g_00DB9448 and duplicate/wrong-selected
Rva000427195 copy constructor; the renderer's two mode gates and the missing
Rva00145C30 and Rva00199FFB helper providers. Stale data-ledger naming needs a
separate evidence-backed reconciliation. These independent blockers were not
retried during this repair.
