# AptLoadMovieFrame construction cleanups

Read the complete AptLoadMovieFrame.cpp and both complete callee units,
BattlePromptConstructorLifetimes.cpp and mem_ops.cpp. The existing class name
comes from WorldBuilder; source comments separately record native caller,
vtable, member, and allocation evidence. No new donor name or member type is
inferred. The source retains the BFME2 matched-sibling delegate/concat lifetime
pattern and its existing uncertainty about address-derived provider identities.

The whole 213-byte Impl constructor at 0x0057C3C4, 73-byte frame constructor
at 0x0057C499, and 96-byte OnContentLoaded callback at 0x0057C26C are EXACT.
Their entire native associative exception graphs are EXACT. The constructor
graphs uniquely own these Ghidra-bounded bodies:

* 0x0079C105, 11 bytes, $L1485: `8b4df083c108e92e80d8ff`.
  Impl saved this at EBP-0x10 plus member offset 8; jumps to the
  AptCommandMapAdder destructor at 0x0052413E.
* 0x0079C135, 10 bytes, $L1537: `ff75f0e8233c89ff59c3`.
  Pushes the frame constructor's pending allocation at EBP-0x10, calls
  scalar operator delete at 0x0002FD60, pops the argument and returns.

verify.py checks all three whole parents, complete exception graphs, both
entire cleanups and relocations, the complete 47-byte command-map destructor
and its exception graph, and the complete 21-byte operator delete. The latter
has no exception graph on either side and calls the existing runtime free
function pointer with scalar memory class 1. The C++ allocation expression and
its verified exception graph establish the pending allocation's lifetime;
no adjacency inference is used.

Normal builds pass all six original owning rows, the three command-map
provider rows, and four mem_ops rows. The before-row identity audit reports
zero findings (identity-before.json). No source, header, flags, pin, alias,
global or marker is edited. These are natural compiler-emitted cleanups from
the real C++ constructors. place_bodies finds zero further bodies or pins.
The old local census (6963cc017c, 2026-10-02) lacks this file, so link_check
cannot preview it; no new linking result is claimed. Run normal builds of
all three sources before replaying verify.py.
