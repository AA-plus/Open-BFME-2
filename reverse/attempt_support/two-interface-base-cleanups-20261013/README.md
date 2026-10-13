# Two-interface base cleanups

The existing real destructor at 0x005F8CB0 matches all 79 bytes; the
constructor at 0x005F8D5C matches all 139 bytes. Each complete associative
exception graph also matches native data and independently places a cleanup:

| RVA | Whole extent | Parent | Receiver |
| --- | ---: | --- | --- |
| 0x007A5A35 | 20 | Destructor | Saved EBP-0x10 receiver; conditional +8 base adjustment |
| 0x007A5A77 | 11 | Constructor | Saved EBP-0x14 receiver; +8 base adjustment |

Both tail-jump to the existing secondary-base destructor at 0x005E12D1.
Replay checks complete bodies and relocations, both whole real parents and
both entire native exception graphs. Ghidra independently supplies the
20-byte and 11-byte extents. The adjacent 0x007A5A82 cleanup already belongs
to this real source and is not claimed again.

These two previously unclaimed bodies add 31 unique C++ exact bytes and
are committed separately. No synthetic parent, assembly, new pin or callable
alias is introduced. The existing source's neutral application identity,
layout evidence and reconstructed base relationship remain unchanged.
No new link-census result is claimed.

```
./build.sh Code/GameEngine/Source/Common/Rva005F8CB0Dtor.cpp
python3 reverse/attempt_support/two-interface-base-cleanups-20261013/verify.py
```
