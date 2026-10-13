# AI upgrade warning concat link repair

At BFME 2 base `d0ed5122f2564a5419723e705583d9e494b25db5`, the
850-byte `AIPlayer::buildUpgrade` row at RVA `0x004f2c14` compiled calls
to `AsciiString::concat(const char *)`, whose selected definition was
not retail's. The target's eight emitted literal-concat call sites all
call RVA `0x5629`. The already matched provider at that address is
`StringBase<char>::concat(const char *)` in `string_base.cpp`; its own
internal call targets RVA `0x369a0`. `calls-before.json` and
`calls-after.json` record the object relocations and native E8 targets.

The repair binds the twelve warning literal-concat statements through
the existing one-pointer StringBase view. Compiler tail merging leaves
eight emitted literal call sites. Object-overload concat calls retain
their existing identity and target. No new layout, symbol pin, ledger
row, provider body or compiler setting is introduced. Byte verification
establishes the target call relationships; the prior recovered source
remains the basis for the warning behavior and class names.

The donor reviewed was BFME 1 commit
`5f05cce4e52a5f69608af60cc2bfa2a8e78d9187` (StringBase compare COMDAT
binding repair), using checkout `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Its binding principle applies; no compare implementation or donor RVA
is imported. The equivalent BFME 2 concat repairs recorded in
`concat-team-map-base-link-20261013` and `threat-warning-concat-link-20261013`
provide local leads. Official upstream was fetched at
`af21dfbc9e7a2d2bd9402444e8ae7f68f2878ec2`; freshness migration remains
blocked by the live `file:reference/open-bfme-1` claim held by
`codex-a44d-root`. The verified pointer and success timestamp are unchanged.

Acceptance:

- `./build.sh Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp`: 12/12
  rows, all 16 strings, 14 floats and 2 imports pass, with no baseline or
  skipped verification.
- Consumer/provider `link_check.py --prepare-current --paths-from sources.txt`:
  49/49 rows pass before and after; both units have current self-strict
  receipts. `receipts-*.json` preserve object and source hashes.
- Local `link_check.py --paths-from sources.txt`: the selected literal
  AsciiString concat finding disappears, with no new findings. Four
  independent findings remain: unresolved `isSupplySourceAttacked`,
  the unproven first-copy `Rva0026137EFilter` deleting destructor, and
  both COMDAT/selected-definition findings for `getPlayerSuperweaponValue`.
  Provider still links. Legacy preview remains 1/2 units and 1,185 linked
  bytes; AIPlayer's 3,311 authored bytes remain excluded.
- Declaration, ledger and converged-data checks pass; `git diff --check`
  passes.

The before/after local index is the same: census `d753dedd98`,
2026-10-12 22:16, SHA256
`c2225569343ee8bc1bcb7682d9888b572c679ecd7439d88f1142d500a25ad1e0`.
The committed link-status measurement is newer (`2a20912cc9`,
2026-10-13 08:08). This repair claims one fewer local dependency finding,
zero new authored bytes and zero measured linked-byte gain. Self-strict
receipts are not closed-strict evidence. No full link cycle or new census
was run; those remain maintainer/runner work.
