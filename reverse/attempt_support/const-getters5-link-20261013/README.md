# Four existing address getters bind their field-table owners

Base commit: `4549ced33d8bc1e6285350c6f927c7e20c1b8646`.
The restored index measures `d753dedd98`, 2026-10-12 22:16. The committed
status CSV reports another measurement; only the local index and explicit
current objects are used below. No index, status or census count was edited.

Replace four image-address returns in `ConstIntGetters5Addr.cpp` with the
addresses of already-defined FieldParse tables. Retain each getter's opaque
identity, integer return ABI, whole six-byte extent and owning source. The
three class declarations contain static data declarations only and assert no
instance layout. No pin, alias, global definition, compiler flag, shared
header or ledger row changes.

| Getter RVA | Native table VA | Existing owner |
| --- | --- | --- |
| 003EE72E | 00DC14C8 | LivingWorldRegionEffectsManager::s_parseTable |
| 002A88C1 | 00BFD7C0 | AIDozerAssignmentFields |
| 00309E24 | 00C08400 | RingEffect::m_fieldParseTable |
| 005B729F | 00C737E8 | CreditsManager::m_creditsFieldParseTable |

Target evidence: every complete native getter is B8/imm32/C3, independently
supplying its table address. Each current object now has exactly one DIR32
at +1 with zero addend to the existing strong definition. `proof.txt` records
native parser references to three tables; the remaining AIDozer table's full
32-byte current definition is independently equal to native RVA 007FD7C0.
These establish the binding without inferring an original getter identity.
The established provider names are retained. This repair does not establish
new table layouts or independently revalidate all other provider data.

Donor review: retained verified BFME1 revision
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; reviewed BFME1 repair
`0a3a4f6052f8c8d25c6c9fbfbf47047a2fe96fdd` (Miles sample empty-string
binding) and prior owner repair `0835ab92bef30e3303e729a0ce09cf591368d0cd`.
Their existing-owner binding principle applies, while their types, layouts
and addresses do not. BFME2's native bytes supply each address here.
The unchanged broader donor sweep was not repeated. Official freshness fetch
found upstream `289f571fb409ae3f2c33efb3fb9e8215cf9596ca`; the foreign
`file:reference/open-bfme-1` claim held by `codex-a44d-root` prevents a pointer
update. Clean verified inputs and overdue success stamp remain unchanged.

Acceptance:

- Normal `./build.sh` on the consumer passes all 50 bodies.
- Before and after, bounded `link_check.py --prepare-current --paths-from
  sources.txt` passes 126/126 bodies, nine strings, eight float literals and
  zero skipped refs. All five providers have strict reusable self receipts;
  their current hashes appear in `proof.txt`. Bounded explicit preparation
  refreshes the changed objects without a whole-tree compile.
- The same ordinary local `link_check.py --paths-from sources.txt` reports
  consumer image-address findings **49 -> 45**, with no new unresolved names.
  The cohort remains **3/5 clean and 2931 -> 2931 linked bytes**. The consumer
  still has 45 literals; ConstIntGettersAddr retains its independent 1128
  literals and unresolved LivingWorldObjectFields. Those are not repaired.
- Declared-definition, class, CSV and whitespace checks pass. Shadow data
  check reports zero findings for the consumer; enforced converged-data check
  reports zero second names and zero unjudged rows across five sources and
  eight addresses. No escape-hatch token is added.

This is a self-strict receipt result and legacy local link preview, with four
fewer literal bindings. New authored C++ bytes and incremental linked bytes
are zero; no closed-strict gain or refreshed census measurement is claimed.
Full link cycles, nightlies and boot verification remain maintainer work.

The earlier FX-list getter lead at 001DFAA0 was released unchanged: its real
provider FXListStoreParse.cpp is newer than this index, so the prescribed local
preview refuses that cohort. Its two-source strict preparation passed 62/62
bodies and one data row; this alone is not link evidence. No workaround or
census rebuild was attempted. Scratch evidence remains under
`build/link-repair-fx-getter-20261013`.
