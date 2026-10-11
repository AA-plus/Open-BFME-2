# Native ScriptEngine integer-map siblings and provider repair

## Target evidence

* 0x00208CF0..0x00208DB8 is a complete 200-byte thiscall body (RET 4).
  It resolves the supplied name, constructs the resolved/original string key,
  inserts the integer -1 into the tree at receiver+0x190DC, and returns the
  mapped value address at node+0x18. Native 0x00208E99..0x00208F61 is its
  complete 200-byte sibling: receiver+0x190E8 and initial value zero.
* Native node 0x00206C54 allocates 0x1C bytes and copies the node payload via
  0x00205910. That 45-byte cdecl helper performs placement copy via the
  nested const-key/integer pair copy at 0x0032ACB4. The target establishes
  the ABI, offsets, calls and stored integer. The original application
  method, helper and container typedef names remain unknown.
* TeamsInfoRec::addToIndex 0x0032D103 keeps all 288 bytes and its native call
  closure with the standard less comparator and retail tree insertion
  setting. Its generic find body folds at 0x0032C07C, proved against every
  owner's whole extent and relocations. Its generic insert_unique is
  0x0032C4F3, physically different from TeamLess 0x0020796D; no alias or
  borrowed identity is used between those two bodies.

## Source guide and inferences

STLport's map, nested pair, byte allocator and placement-new copy semantics
guide the C++. The inherited Map donor revision and provenance remain in its
source header. Reference names alone are not target identity evidence.
Container layout is the supported structural reconstruction from the native
tree/payload accesses; neutral RVA method/helper labels preserve uncertainty.
Removing an explicit `if(where)` from placement new restores the compiler's
native null guard and exception-state ordering. No assembly or emit is used.

## Ownership and debt repair

The TeamLess insert wrapper, insertion helper and node allocator move from
the Map TU to the ScriptEngine integer-map home; TeamLess find moves to
ScriptEngineNamedBindings, which already emits its exact copy. These four
names, addresses and body extents do not change.

The synthetic 0x00205910 `object-symbol` row is replaced by the actual typed
C++ placement-copy definition in the home. Its old standalone opaque provider
and unsupported integer _Construct pin at that address are removed. The
existing integer _Construct retains its own 0x0032AF6F address. The named-map
consumer uses the same native placement-copy helper explicitly. One keyed
object-symbol hatch is deleted; the new generic find pin is admitted through
the strict fold-proof tool against its actual kept Map object.

The Map make_pair specialization now has inline linkage while retaining its
noinline code-generation setting. Its whole 27-byte body and caller remain
unchanged; this removes a strong/COMDAT duplicate against the integer home.

## Verification

Normal add_match_batch admitted both 200-byte bodies. All 40 rows in the three
changed units pass complete byte/relocation verification, all 18 EH rows are
exact, and code identity finds zero wrong bindings across all 40 rows. The
two additional units found by lost-name analysis pass all 12 of their rows.
All definitions are declared; ledger and pin-consistency checks pass.
The local census preview reports the expanded integer home LINKS (2,954
bytes) after the duplicate repair. Map retains its pre-existing missing
Dict::getAsciiString/StaticNameKey::key providers in that October 10 index;
NamedBindings is absent from that index. The newer current-ledger preview
refused to judge because 6,571 unrelated providers lack current compiler
receipts. No census status is rewritten, no full link cycle is started and
no whole-tree linking result is claimed.

The accompanying JSON preserves scratch proof; live gates additionally
verified the final tracked source paths. Normal commit and push hooks remain
required. Two new recoveries total 400 bytes; helper reownership adds no bytes.

Elapsed matching/reconciliation approximately 40 minutes; model=gpt-6.
