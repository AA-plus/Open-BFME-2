# Native ScriptEngine byte-map update 0x00209811

The target body is 132 bytes at 0x00209811..0x00209895 and ends with RET8.
It finds an AsciiString key in the tree at receiver+0x190D0; an existing node
receives a raw byte at +0x14. On a miss it builds a key/byte pair and inserts it.
The original method name and mapped typedef are unknown. `unsigned char`
expresses the observed byte transfer; its signedness is not a recovered target fact.

The repository's STLport pair/map/tree source supplies the container structure.
Retail establishes the offsets, size, calls, temporary destruction and return ABI.
The natural full expression `insert(make_pair(key,flag))` reproduces the complete
body. In particular, MSVC's hidden-result ABI returns the pair destination in
EAX, which is immediately consumed by the conversion constructor. Earlier opaque
cast reconstructions introduced an extra LEA and treated that EAX reuse as a wall.
The old bank is retired by the normal verified add_match landing.

Native pair constructor0x003004C1/27 and make_pair0x002056C1/27 are renamed from
neutral layout views and rehomed into this existing ScriptEngine unit. Only the
byte half of Rva002056A6Make.cpp is pruned; the integer half is preserved. The
sole retired constructor provider Rva003004C1Pair.cpp is removed. No duplicate
address or new object-symbol alias is introduced.

Three strict ICF pins cover byte-tree find0x001F8437/78, conversion constructor
0x005117F6/27 and unique insertion0x00207A04/151. Whole bodies and every owner
relocation are proved through pin_admission, including recursive insertion148,
node34, placement-copy45 and pair-copy27 bodies and their associated EH data.
All newly used names are kept from the actual home object. The opaque existing
hinted-insertion family and its other consumers remain verified owners.

Retail's existing34-byte node allocator has no allocator cleanup catch path.
The TU's _STLP_NO_EXCEPTIONS setting reproduces that existing node; every prior
body and every prior EH graph in this unit are checked under the same setting.
The integrated file has38 exact ledger rows and14 exact EH rows, with zero
code-identity findings. The seven isolated fold proofs all pass; only the three
names directly needed by the new recovered body's calls are pinned.

Prospective proof files document the isolated checks. The normal live source,
exception, identity, dependency, ledger and commit hooks are mandatory before
publication; no verification runner or publisher is started for this recovery.

The live placement rescan also finds the natural byte-map insertion wrapper
0x00207ECC..0x00207EE0/20. It returns the hidden pair result and ends RET8;
its sole REL32 reaches the proved insert_unique0x00207A04. It is claimed,
verified and banked separately, bringing the home to39 exact ledger rows.
The normal132-byte commit gate checked46 rows across4 affected units,16 EH
graphs and converged data with no new identity findings. The link preview
with the explicitly refreshed Map, NamedBindings, SidesList and integer-tree
providers reports the home LINKS with3,159 bytes before the additional wrapper.
Other listed providers retain their pre-existing census blockers; this preview
does not claim an all-current census or a full link-cycle result.
