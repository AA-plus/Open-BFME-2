# Returned string cleanup at 0x007836E8

The real C++ `BitRange::rva003ED4E5` at 0x003ED4E5 builds and returns an
`AsciiString`. Its whole 192-byte body and associative exception graph match
retail. That graph identifies the 25-byte cleanup at 0x007836E8 independently
of neighboring addresses. MSVC tests ownership bit 0 at `[ebp-0x18]`, clears it,
and destroys the hidden return object at `[ebp+8]`, or returns without cleanup.

The normal parent object emits all 25 bytes, including the conditional branch,
final return, and exact destructor relocation to 0x0048BA39. The compiler-local
label is only an object locator; the parent graph supplies its native identity.
No synthetic parent, inline assembly, new callee pin, or callable alias is added.
The parent receiver's original application name remains unknown; the earlier
BFME 1 audio-key donor remains semantic provenance rather than target naming
proof. The assembly dump is left intact as an orphan after its row is repointed.

Run the normal build and then the read-only proof:

```
./build.sh Code/GameEngine/Source/Common/Rva003ED498Count.cpp
python3 reverse/attempt_support/audio-key-return-cleanup-20261013/verify.py
```
