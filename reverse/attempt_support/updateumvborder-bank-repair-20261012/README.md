# Complete border-extension bank restored

`reverse/attempts/0x001b96a0.cpp` restores the complete Y/U/V implementation
from commit `6b26b8a1c5`. Commit `434ccb3e3b` had replaced it with a Y-only
implementation and reduced the bank score from 0.8 to 0.3.

The reviewed clean-room spec is `reverse/vp6_cleanroom/specs/001b96a0.md`.
Retail establishes the two cdecl arguments, fields, inlined fills/copies and
complete 1,047-byte boundary `0x001B96A0..0x001B9AB7`. The recovered C++
compiles to 1,055 bytes under its original O2/G6 settings. Register allocation
and instruction scheduling still differ. This is a partial bank, not a
matched recovery; no production source, ledger row or pin is added.

`emulation.json` records the committed bank's source and compiled-code hashes.
The separate `verify.py` oracle implements the reviewed plane-extension
behavior. Twelve positive-dimension frame layouts exercise all three planes,
different widths/heights and borders 8/16/32. Retail and the bank produce
identical complete frame bytes and agree with the oracle. Both return normally,
preserve the callee-saved registers and context, and leave the cdecl arguments
on the caller's stack. These cases establish behavioral evidence for the
restored bank, not byte identity or exhaustive correctness.

Reproduce from the repository root with the configured Python dependencies:

```sh
python3 tools/explain_mismatch.py _UpdateUMVBorder --rva 0x001B96A0 --size 1047 --source reverse/attempts/0x001b96a0.cpp --context 16
python3 reverse/attempt_support/updateumvborder-bank-repair-20261012/verify.py
```

The first command compiles through the normal dependency cache. The second
reads that compiled object and emits an ignored report under `build/`.
No external VP6 decoder source was consulted.
