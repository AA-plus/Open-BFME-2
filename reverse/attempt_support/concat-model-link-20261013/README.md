# Model-name concat provider repair, 2026-10-13

At BFME 2 base `04ede9e904049c83a9a7adc08676328e2f98aaa2`, the local census
index measures `d753dedd98` (2026-10-12 22:16). The initial local preview
reports the selected `?concat@AsciiString@@QAEXPBD@Z` as the only blocker of
`Rva00562BF7SelectModelName.cpp`, holding out its existing 484 authored bytes.
`link-before.txt` transcribes that initial pre-edit preview. The committed
link-status snapshot at `f6c432fac6` served queue discovery; it is not this
before/after measurement. No per-row data-back artifact or census/status
counter was changed.

## Target and donor evidence

Retail's four emitted concat call operands in the 484-byte selector all target
RVA `0x00005629`, the existing 37-byte `StringBase<char>::concat(const char *)`
provider in `Code/Libraries/Source/WWVegas/WWLib/string_base.cpp`. The three
source branches share generated code. Replace their suffix and `.w3d` calls
with the actual provider through the canonical one-pointer AsciiString view;
remove the local inline specialization so the calls retain retail's out-of-line
shape. `relocation-proof.txt` checks both current strict receipts and every
concat REL32 relocation against its retail destination. The full byte gate
independently confirms caller behavior and extent.

This completes the selector lead deferred in `../concat-link-20261013/`.
Reviewed verified BFME 1 pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`
and donor repair `5f05cce4e52a5f69608af60cc2bfa2a8e78d9187`: its compare callers
bind the StringBase provider directly, with casts for non-derived views. That
provider-selection principle is applicable; no compare code or donor layout
claim is imported. Existing selector identity/provenance remains unchanged.
No new pin, alias, global, header, row, range or compiler setting is introduced.

The official freshness fetch found BFME 1 master at
`f5030840ed26958b52d721f05c408a6e6637f13a`. Its overdue update remains claimed
by `codex-a44d-root` as `file:reference/open-bfme-1`. Retained the verified clean
checkout and did not advance the freshness success stamp. Comparative full
verification and pointer publication remain that owner's pending work.

## Acceptance

- First `./build.sh` attempt: selector 1/1 matched; five literals, seven float
  literals and three imports verified, no baselined or skipped string refs.
- Bounded `link_check.py --prepare-current --paths-from sources.txt`: both
  explicit units accepted with self-strict current receipts and normal gates,
  38/38 matched rows, nine literals, 15 empty-string refs, seven float literals
  and six imports verified. Census/index/status unchanged.
- Ordinary local `link_check.py --paths-from sources.txt`: both units LINKS;
  **legacy census preview 1,185 -> 1,669 bytes, +484 existing authored bytes**.
  The unchanged provider contributes 1,185 bytes in both previews.
- Frozen-file checks accept the edited selector before and after. The unchanged
  provider reports its existing one unclaimed definition without refusing.
- `data_check.py --converged`: two sources, eight addresses, zero second names
  and zero unjudged rows. `check_csv.py` accepts 86,880 functions, 17,258 symbols
  and 298 data rows. `git diff --check` passes.

New authored C++ bytes are zero. Self-strict receipts support this local legacy
preview; closed-strict closure and an actual link are unmeasured. No full link
cycle, census build, nightly or boot run was started. Normal commit/push hooks
remain required. Other inspected leads retain independent unresolved providers,
vtable-address debt, or previously recorded blockers; they were not retried.
