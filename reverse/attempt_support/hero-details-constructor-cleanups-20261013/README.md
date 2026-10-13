# Hero-details constructor cleanups

The existing real neutral Rva005E6F9D constructor at 0x005E6ED6 matches
all 191 native bytes and its complete associative exception graph.
The owning source records independent constructor/destructor vtable,
base-lifetime and WorldBuilder initializer evidence. The panel's original
class name and unknown fields remain unresolved.

The complete native graph independently places three unclaimed bodies:

| RVA | Whole extent | Native cleanup |
| --- | ---: | --- |
| 0x007A3C3B | 8 | Saved receiver at EBP-0x14; primary-base destructor 0x005F64F5 |
| 0x007A3C43 | 11 | Saved receiver at EBP-0x14 plus 0x20; biased secondary-base destructor 0x005E5018 |
| 0x007A3C4E | 10 | Failed-new block pointer in EBP+0x14; operator delete 0x0002FD60, pop and return |

The second cleanup's +0x20 adjustment is the complete object's +0x0C
secondary base plus that base's +0x14 virtual-base destructor bias. It is
not the owned listener field at +0x20. This distinction follows the real
constructor graph and independently rowed base destructor contract.

Replay verifies the complete parent, its entire native exception data,
all three full cleanup bodies and every existing callee relocation.
Ghidra independently supplies all three whole extents. Relationships are
not inferred from adjacent addresses or compiler label numbers.

The three bodies add 29 unique C++ exact bytes and are committed separately.
They are emitted by existing real C++ base and new-expression lifetimes.
No synthetic parent, assembly, new pin or callable alias is introduced.
Existing neutral identities and partial layout evidence are preserved;
this adds no original type or link-census claim.

Normal shadow identity checking still reports the existing unowned listener
constructor binding at 0x005E6DAA and divergent scalar-deleting wrappers for
Rva0007DF07 and Rva005CC5E5. This ledger addition changes none of their
source definitions or bindings and adds no baseline exemption. Complete
cleanup/parent byte and exception-data matches do not resolve those debts.

```
./build.sh Code/GameEngine/Source/Common/Rva005E4F6DConstructor.cpp
python3 reverse/attempt_support/hero-details-constructor-cleanups-20261013/verify.py
```
