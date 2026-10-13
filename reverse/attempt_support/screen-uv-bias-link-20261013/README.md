# Screen UV bias data binding repair, 2026-10-13

Base BFME 2 checkout: `bd27e8dbf37916dd4f2e11cbb624d7a6a7ed1474`.
The restored local census index measures `d753dedd98` (2026-10-12 22:16);
committed link status at `f6c432fac6` was used only for queue discovery.
Both local previews use the same three explicit sources listed in sources.txt.
No census/index/status/history or per-row data-back artifact was changed.

## Target evidence and repair

Retail's getter at RVA 0x00110094 and Set_Coordinate_Range at 0x001188C0
both read VA 0x00DEC3D7 with zero-addend DIR32 operands. ww3d.cpp already
provides the private static bool `?IsScreenUVBiased@WW3D@@0_NA`, initialized
false. The existing data ledger selects it provisionally, and the matched
GapBodiesGE25 setter independently already uses this exact private member.
GlobalByteGetters nevertheless defined a second byte as g_Va00DEC3D7, and
render2d's coordinate code read that second datum.

Remove that duplicate definition and its extern. The getter uses a minimal
static-only WW3D declaration with a friend for the existing getter, preserving
the provider's private-member decoration. render2d already includes ww3d.h;
its coordinate method uses the existing inline Is_Screen_UV_Biased accessor,
as its other coordinate methods already do. All three witnessed symbol tables
now lack the old datum, and exactly one canonical strong definition remains,
in the unchanged provider. Both matched DIR32 operands bind to it. Full bytes
prove the unsigned-char getter and bool accessor retain the native read shapes.

The existing provider name is reused; no new original retail class-layout or
source-name claim is made. No pin, alias, row, header, flags, marker, baseline
or extent changed. No other old-name consumer remains in Code. Hatch counts
in this cohort fall 133 -> 128 (getter 34 -> 31, renderer 51 -> 49,
provider 48 unchanged), as recorded alongside the relocation evidence.

## Donor review and freshness

Reviewed verified BFME 1 pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
and donor repair 908413c254f83e1f402b991541d4cf68db48ea4e. Its pool externs
bind the single owned datum while retaining local access views. That provider
binding principle applies here; its Apt code, addresses and layouts do not.
No donor body or header was imported.

Official upstream freshness fetch reached
1d8a12f21352c5d4893b7b5caf4caaf06bcb4ff0. Another worker, codex-a44d-root,
holds file:reference/open-bfme-1. Preserved the clean verified pointer and the
overdue success stamp; comparative full verification/update remains with that
owner. No unverified donor input was substituted.

## Acceptance and limits

- Edited sources pass ./build.sh: 14/14 rows exact, ten float literals,
  zero skipped/baselined strings or imports.
- Bounded link_check.py --prepare-current --paths-from sources.txt passes
  before and after: 33/33 rows, three strings, fourteen compiler floats and
  two named imports, fresh reusable self-strict receipts for all three units.
- Relocation proof records two exact native operands, zero addends and one
  canonical definition; unchanged provider object hash is retained.
- Data shadow findings fall 23 -> 20; outside-baseline findings fall 4 -> 1.
  The duplicate-def and two wrong-name findings at 0x009EC3D7 disappear.
  The remaining outside finding is the pre-existing provisional ledger name
  for LODMeshCacheSetting at 0x009EC410, not changed here.
- Enforced converged-data check: three sources, eight addresses, zero second
  names and zero unjudged rows. Declared-definition, CSV, case and whitespace
  checks pass. Renderer/provider retain their existing unclaimed-definition
  notices, which do not refuse these edits.
- Ordinary local link preview: 1/3 units clean before and after, LINKED
  66 -> 66 bytes. The getter still links; renderer/provider retain independent
  unresolved methods and COMDAT/selected-definition blockers (full transcripts
  included). No additional blocker was introduced by this repair.

This is a verified shared-data binding and escape-hatch repair: zero new
authored C++ bytes and zero legacy linked-byte growth. Self-strict receipts
prove each witnessed unit's own bytes. The restored census supplies other
providers for the legacy preview; no transitive closed-strict gain, actual
link, data-back, full link cycle, nightly or boot result is claimed.
