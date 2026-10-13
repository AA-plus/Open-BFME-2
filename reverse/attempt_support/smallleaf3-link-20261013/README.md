# SmallLeafBodies3 competing-provider repair

Measured checkout: 1d21a3da40, with the three-line source removal below.
Available census: 2026-10-12 22:16 at d753dedd98. The committed link status
(e956901d31, 2026-10-13 02:58) was used only for discovery; it is a different
measurement. No census, link status, or full-link artifact was modified.

## Target and object evidence

SmallLeafBodies3.cpp emitted strong, NODUPLICATES (selection 1) definitions
for three names also owned by SmallLeafBodies3_BlockMemcpyAssign.cpp:

| Name stem | Retail RVA | Extent | Wrong competing body | Retained exact body |
| --- | --- | ---: | ---: | ---: |
| Rva00299790BlockAssign::set | 0x0029A23E | 17 | 26 | 17 |
| Rva003A1030BlockAssign::set | 0x00311493 | 20 | 29 | 20 |
| Rva004094A0BlockAssign::set | 0x0036246B | 17 | 26 | 17 |

The object snapshots contain whole bytes, relocations, COFF selections and
retail verdicts. All six definitions were receipt-current under strict checks.
The competing scalar-load/store bodies were retail-wrong. The existing exact
owners use three movsd instructions and have no relocations. Removing the
three macro instantiations in the wrong emitter leaves those exact owners
unchanged; no row, pin, data name, type, ABI or compiler flag was changed.
Both source files are consumers checked together. The remaining eight rows
in SmallLeafBodies3.cpp retain exact bodies.

The names and views originate in the BFME 1 donor and remain address-derived;
this repair does not recover original identities or prove an original class
layout. Reviewed donor repair d3f9000fe08615a100e844adfff57fa4a39cd615
(TileData deleting-destructor emitter removal) supports the general repair
of dropping an incorrect competing emitter; its class and body were not
transferred. The local whole-body evidence establishes applicability here.
Donor repair 5093777e8373a843f1f1ccfc648601ae78351aaa was also reviewed for
provider reconciliation; inline merging is unnecessary for these wrong copies.

The verified BFME 1 gitlink/checkout remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The overdue freshness check fetched
official master at 22b5bf2509820d95df1cf0bef71e4196606e80fa; another worker
held file:reference/open-bfme-1 (codex-a44d-root), so its clean checkout,
committed pointer and success stamp were preserved for that worker's update
and comparative verification. This session does not claim update success.

## Acceptance checks

- Self-strict preparation before and after: two explicit providers, strict
  reusable receipts, 11/11 byte-exact rows. This is provider preparation,
  not proof of link closure.
- Normal ./build.sh: 11/11 exact; source claims, strings, floats and imports
  pass. No literals or imports are introduced.
- Ordinary local link_check against the named census: 0/2 sources and 0 linked
  bytes before; 2/2 sources and 226 linked bytes after (172 + 54), exit 0.
  The removed duplicate, wrong-COMDAT and wrong-selected blockers disappear.
- check_csv and find_declared_unmatched pass.
- Enforced converged data check: two sources, eight addresses, zero second
  names, zero unjudged rows. Ordinary shadow data check: zero findings.

There are zero new authored C++ bytes. The 226-byte gain is a local legacy
preview, not a closed-strict result or full link-cycle measurement. Broader
linking remains a maintainer-only check. Transcripts and object snapshots
are stored beside this record.
