# Shadow parameter-vector cleanup at 0x0075F3B7

The complete real C++ `Rva0007DA23ResourceManager::ReAcquireResources`
matches native 0x0007DA23 over all 478 bytes. Its exact associative exception
graph independently locates the eight-byte cleanup at 0x0075F3B7, which also
has an eight-byte Ghidra boundary. It takes the address of the local parameter
vector at `[ebp-0x28]` and jumps to native 0x0007C632, the existing unadjusted
destructor thunk to the rowed vector destructor at 0x0007C5D5.

The normal parent object emits all eight bytes and the correct destructor
relocation. Its compiler-local label is an object locator, with identity
supplied by the whole parent and exception graph. No synthetic parent, assembly,
new callee pin, or callable alias is introduced. The existing neutral receiver
spelling and measured parameter storage remain unchanged; the WorldBuilder
`ReAcquireResources` name is recorded as supporting provenance.

The body was unclaimed. This adds eight unique C++ exact bytes through a real
parent, with no link-census or game-authored-byte gain asserted.

The shadow identity checker reports a wrong binding for the compiler's vector
destructor spelling at 0x0007C632. That existing row is an unadjusted five-byte
tail jump to the full destructor at 0x0007C5D5. The replay checks that complete
jump and the resolver's existing candidate address; no new pin is substituted
to suppress the finding. The normal byte and exception checks pass.

Replay after a normal build:

```
./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapManagerUpdateShadowMap.cpp
python3 reverse/attempt_support/shadow-parameter-vector-cleanup-20261013/verify.py
```
