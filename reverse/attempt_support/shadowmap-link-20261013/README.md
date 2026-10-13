# ShadowMap configuration ownership repair, 2026-10-13

`Rva0007BA35Method.cpp` previously declared two 12-byte configuration
snapshots and a field-parse table without definitions. It now owns all three,
with matching data rows. Existing executable bodies and symbol spellings stay
the same. No pin, alias, private class layout change or protected baseline
change is needed.

Base commit: `2a2870b05ec3907d6535aecb2ec3fff46636ba91`. The restored census
index measures `d753dedd98`, dated 2026-10-12 22:16, as recorded in
`index-meta.json`. The committed status CSV has a different measurement;
the comparisons below use the restored index and current explicit objects.

Target evidence establishes the ownership and layout:

- Guard method RVA `0x0007BA35` and parser RVA `0x0007BE1E` copy exactly
  12 bytes between VAs `0x00DB4470` and `0x00DB447C`. Both initial records
  contain words `1024, 0x447A0000, 0`. The next independent registration
  begins at VA `0x00DB4488`. The established `Db12` dword storage view and
  existing provisional owner names are retained; original identifiers remain
  unknown.
- Parser `parseShadowMapBlock` passes table VA `0x00BC6BA8`. Its complete
  64-byte extent contains three 16-byte entries and a zero sentinel; the next
  word, at `0x00BC6BE8`, is a separate float constant. Tokens and callbacks
  independently prove `MapSize` is an integer at offset zero, and
  `MaxViewDistance` and `MinShadowedTerrainHeight` are reals at offsets four
  and eight. Their defaults decode to 1000.0f and 0.0f. Native callbacks are
  the existing `INI::parseInt` RVA `0x0002EF56` and `INI::parseReal`
  RVA `0x0002EFC0`, with their established cdecl signatures.
- The original source class names are not inferred from byte equality.
  `FieldParse` follows the already-established four-field parser ABI, with
  the target table independently supplying every token, callback and offset.

Donor review: verified BFME1 pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; reviewed dependency repair
`0835ab92bef30e3303e729a0ce09cf591368d0cd` binds externs to existing
owner-typed definitions. That repair is inapplicable here because no provider
exists for these three symbols. The local initialized definitions instead
come entirely from target evidence; no donor source, type or address is
imported. Official BFME1 master was fetched, but its newer checkout update
remains held by `codex-a44d-root` under `file:reference/open-bfme-1`. The
verified pointer and overdue success stamp are preserved, without claiming
a successful freshness update.

Acceptance and measured improvement:

- Before, bounded `link_check.py --prepare-current` verifies all three
  executable rows of the changed unit with a strict reusable receipt.
  Ordinary local `link_check.py` reports exactly the three unresolved data
  symbols and zero linked C++ bytes (`link-before.txt`).
- `./build.sh` verifies all three executable rows and all three new data
  rows. `data_rows.py --verify` separately passes the 12/12/64-byte rows,
  including the field table's string and function relocations.
- After, bounded preparation of the owner and both callback providers passes
  five executable rows and three data rows with 3/3 strict reusable
  self receipts. `proof.txt` records their object SHA256 values, strong
  definitions, target data bytes and matched code DIR32 operands.
- The same single-unit local check now reports `LINKS`, zero blockers and
  `LINKED 0 -> 298 bytes` (`link-unit-after.txt`). Including the unchanged
  callback providers reports 3/3 clean units and `55 -> 353` legacy linked
  C++ bytes (`link-after.txt`). The improvement is three fewer unresolved
  bindings and 298 additional locally linkable existing C++ bytes, with
  zero newly authored executable C++ bytes and 88 new verified data bytes.
- CSV integrity, declared-definition, whitespace and case checks pass.
  Data shadow checks report zero findings; enforced converged-data checks
  report zero second names and zero unjudged rows. Hatch occurrences remain
  zero in the changed source.

These are self-strict receipt results and a local legacy link preview;
external providers retain the restored census's authority. No closed-strict
gain, refreshed census measurement or full executable link is claimed.
Broader link cycles, nightlies and boot verification remain maintainer work.
