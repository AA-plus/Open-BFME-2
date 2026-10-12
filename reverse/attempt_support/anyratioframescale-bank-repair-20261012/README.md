# AnyRatioFrameScale bank repair

The bank at `reverse/attempts/0x001baf30.cpp` again preserves the complete
606-byte clean-room reconstruction previously recorded with score 0.96.
Commit `434ccb3e3b` replaced it with a weaker 604-byte reconstruction;
this repair recovers the stronger body from `0830ca4bca` and changes its
obsolete helper declaration to the existing C-linkage `AnyRatio_2D_Scale`
provider. No decoder source was consulted. The behavioral specification is
`reverse/vp6_cleanroom/specs/001baf30.md`; the target body is 606 bytes at
RVA `0x001BAF30`.

The normal mismatch verifier emits 606 bytes, with the first difference at
offset `0xB`. Early field loads, local stores and multiply scheduling still
differ from retail. Four isolated local-store variants failed to resolve
that difference. The retained score is the earlier bank's estimate, not a
measured fraction of identical bytes. This bank is evidence, not recovered
coverage; no matched row or symbol pin was added.

`verify.py` compares the normal compiled bank with retail in an x86 emulator
using the same instrumented stub for all three calls to `AnyRatio_2D_Scale`.
An independent positive-dimension specification oracle checks the call
arguments and output padding. The 64 cases cover two destination layouts,
four horizontal and four vertical scale/ratio pairs, and both zero and
nonzero luma results. They compare the full destination buffers, return
value, untouched context/config/frame, cdecl stack and saved registers.
The stub deliberately clobbers caller-saved registers. These checks establish
caller behavior for those inputs; they do not test the callee implementation,
invalid inputs, full decoder operation or byte exactness.

Reproduce from the repository root:

```sh
python3 tools/explain_mismatch.py _AnyRatioFrameScale --rva 0x001BAF30 --size 606 --source reverse/attempts/0x001baf30.cpp --context 16
python3 reverse/attempt_support/anyratioframescale-bank-repair-20261012/verify.py
```

The script reads the normal verifier's compiled object and writes its receipt
under ignored `build/` by default. `emulation.json` records the bank and object
hashes, the three canonical callee relocations and the 64 successful cases.
