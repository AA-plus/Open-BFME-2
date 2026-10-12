# Subtitle parser exception bank repair

The complete partial bank for RVA `0x00688B10` previously declared
`INIException` without its destructor and with reversed member roles.
It now includes the existing canonical `Common/INIException.h` shim.
The matched constructor writes the message pointer at offset zero and the
argument count at offset four; the existing destructor deletes that pointer.
Retail ThrowInfo at VA `0x00CFE2FC` names the destructor at `0x0002BD30`.
The old bank instead emitted a zero cleanup pointer.

The isolated baseline and canonical-exception versions compile to the same
1,547 parser bytes and the same relocations, against retail's 1,578 bytes.
A subsequent trial follows retail's later label lifetime, inline zero
initialization and word-at-offset-four empty check. That retained bank emits
1,559 bytes; its first mismatch is now the filename temporary's stack home
at offset `0x22`. The parser is still nonexact.
The prior 0.75 score is retained as an estimate rather than a measured exact
byte fraction. No matched row, pin or game-source body is added.

`verify.py` reads the normal mismatch verifier's object and proves the
ThrowInfo cleanup, catchable-type array, pointer-adjustment fields, eight-byte
object size, copy-constructor owner and RTTI class name against retail.
Its receipt is `metadata.json`. The type_info vtable placement, remaining
function EH data, remaining parser instructions and callee semantics, literals and runtime behavior are
unverified. Those still require separate reconciliation before landing.

Reproduce from the repository root:

```sh
python3 tools/explain_mismatch.py '?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z' --rva 0x00688B10 --size 1578 --source reverse/attempts/0x00688b10.cpp --context 16
python3 reverse/attempt_support/subtitle-exception-bank-repair-20261012/verify.py
```

The reproducer writes its receipt under ignored `build/` by default and
does not compile or change the ledger.
