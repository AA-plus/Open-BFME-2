# Geometry and eye-tower math linkage repair

Source base: `fed26bb1ad697dee775d4c37b5d520277a9b2797`.
Local link index: measurement `cb660e4d97`, 2026-10-13 04:02;
SHA256 `4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
The committed link_status measurement is newer (`2a20912cc9`); this repair
uses the available index for a paired local legacy preview, not that census.

## Problem and change

The MSVC 7.1 math header emitted surplus external float COMDAT wrappers in
two consumers. Scope its inline definitions to each translation unit.
In LivingWorldEyeTowerAim.cpp rename only the header's atan2f helper while
retaining the explicit external atan2f declaration used by the matched body.
No shared headers, pins, ledger rows, class layouts or baselines change.

Target evidence: the eye-tower body's three native REL32 calls at operand
RVAs 0x003F9695, 0x003F97A0 and 0x003F9832 target 0x000422CD. Its unchanged
provider, Common/Rva000422A0.cpp, emits the 25-byte retail atan2f adapter.
The consumer previously emitted a wrong 27-byte wrapper calling double atan2.
The geometry parent already inlines its sqrt operation.

Donor lead: BFME 1 checkout and committed pointer
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`, reviewed linking repair
`d2e21369067f2f2c762c1c7ec2792c75f1ecf53d`: suppress surplus inline wrappers.
Its string constructor/pin repair is inapplicable here. Also reviewed
`564215e0c787ced3a9ca1da3d00a5cfd3c3b7d7a` (terrain vector delete[] repair),
inapplicable to this math cause. No donor identity or layout inference is added.
Freshness fetch found upstream `7fbed69e46153928a20329704ec6e8aec2782f40`;
the reference update is foreign-claimed by codex-a44d-root. Last verified
inputs and freshness stamp were preserved; comparative update verification
remains with that owner.

## Paired result

| Consumer | External COMDATs removed | Legacy findings before / after |
| --- | --- | --- |
| Common/Rva009F66F0.cpp | sqrtf, float sqrt overload | 4 / 2 |
| LivingWorld/LivingWorldEyeTowerAim.cpp | atan2f, cosf, sinf | 4 / 3 |

All 23 retained consumer COMDATs have identical bytes, size, relocation
records, digests and census verdicts. Geometry's two associative EH sections
are identical. Strong and weak binding facts do not change. Geometry's
undefined bindings do not change; eye-tower replaces only the wrapper's
undefined atan2 with atan2f. The provider source, object and facts are unchanged.
Full snapshots and aggregate assertions are in the adjacent JSON files.

Local legacy link_check removes exactly three findings, adds none, and keeps
1/3 sources clean and LINKED 70 -> 70 bytes. Consumer closure remains 0 bytes:
GeometryInfo::bfmeIntersects unresolved plus the selected GeometryInfo
constructor; eye-tower's Matrix3 constructor and two Z-rotation factories.
Self-strict byte verification is current for all three sources. Closed-strict,
full-census and actual-link gains are unmeasured. New authored C++ bytes: zero.
No maintainer-only verification runner was started.

## Acceptance

Commands used with the three paths in sources.txt:

- `python3 tools/link_check.py --prepare-current <three paths>` before and after:
  seven matched rows, seven compiler float literals, one named import;
  strict reusable receipts, no census/index/status mutation.
- `./build.sh <three paths>`: 7/7 exact, same literal/import results,
  zero baselines and unverified/skipped string references.
- `python3 tools/link_check.py --paths-from <sources.txt>` before and after:
  paired legacy findings 8 -> 5, no additions, LINKED 70 -> 70.
- `python3 tools/eh_verify.py --sources-from <sources.txt>`: one EH parent,
  EXACT 1, no not-exact, baseline or missing results.
- `python3 tools/find_declared_unmatched.py <two consumers>`: passes.
- `python3 tools/class_gate.py <two consumers>`: passes.
- `python3 tools/link_check.py --new-variants <two consumers>`: passes.
- `python3 tools/data_check.py --converged <two consumers>`: eight converged
  addresses, zero second names or unjudged results.
- `python3 tools/data_check.py <two consumers>`: one existing baseline finding,
  zero outside the baseline; no baseline edits.
- `python3 tools/check_csv.py`: passes.
- `git diff --check`: passes.

The snapshots are evidence only. Compiler receipts and object backups stay
under build/. Neither link_status nor any global census result is rewritten.
