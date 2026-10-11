# Native destructor forwarding wrapper at 0x004C74D4

The complete native body is nine bytes: load the pointer at [esp+4] into
ECX and tail-jump to the already rowed, whole 15-byte destructor at 0x000796BC.
The preceding 91-byte sort at 0x004C7479 ends with RET at 0x004C74D3; the next
74-byte sort begins at 0x004C74DD. The wrapper occupies their entire intervening
range. No direct call, tail-jump or address-taken reference to this wrapper was
found by the independent image scan; this is not evidence of a particular
original template specialization.

The complete existing Rva004C7542DestroyPairs.cpp home was read. Its same
callee-owner LocoPair call view permits an ordinary C++ pointer destructor
forwarder with exactly the observed ABI and operation. The new function has a
neutral RVA-derived name. No original wrapper name or original argument type
is claimed; LocoPair is only the compatible existing callee view. No new pin,
alias, assembly or emitted bytes was introduced. The existing pair specialization
now explicitly retains its const-key/vector members and declares the complete
destructor out of line; a sizeof assertion preserves its 16-byte call view.
The compiler emits no default allocator cleanup from this declaration.

A read-only rescan of the existing hero integer/vector family with minimum
size five found the same nine-byte shape under _STL::_Destroy<pair<const int,
vector<unsigned int> > >. That donor specialization was deliberately not
claimed: matching bytes and a shared folded destructor do not establish it.
The source body's purpose and ABI derive directly from target instructions;
the compatible type view comes from the existing 0x000796BC ledger owner.

Normal add_match verification passed all three home rows and all scoped
reference checks. byte-verification.txt records the whole-body exact result.
Donor dependencies remain at verified BFME 1 revision
9e3be919b10ae956e3c8a13995e0d62f2be1d016. Neither the donor pointer nor a
verification baseline was changed.

Provider verification: the home unit's generated scalar-deleting destructor
matches the already owned whole28-byte retail body at 0x00079715. The normal
link preview against the available 2026-10-10 19:06 census removes all its
previous unresolved/default-allocator COMDAT blockers. It still reports the
existing early AIUpdate provider of that scalar destructor as wrong-selected:
that provider is30 bytes, using ADD ESP,4 where retail has POP ECX. This is
pre-existing provider debt, so this is a byte-exact recovery and local provider
repair, not a claim that the current full link closure is complete.

Read-only isolated repairs of AIUpdate were rejected without editing that
source: /G6 did not fix the scalar cleanup and regressed its13-byte empty
predicate; /Os fixed the scalar cleanup but regressed three matched bodies.
All ten existing AIUpdate rows were compared during each setting trial. The
tracked compiler settings and AIUpdate provider were left unchanged.
