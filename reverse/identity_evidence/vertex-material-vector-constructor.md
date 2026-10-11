# Vertex-material vector constructor

The existing `MaterialCollectorDestructor.cpp` emits
`DynamicVectorClass<VertexMaterialClass*>::DynamicVectorClass(unsigned,
VertexMaterialClass* const*)` at RVA `0x0016F5B0`, exactly 94 retail bytes.
Its implementation comes from the licensed `vector.h` included from the
BFME 1 reference at revision `9e3be919b10ae956e3c8a13995e0d62f2be1d016`.
The existing translation unit, dependencies and region compiler settings
are retained; no source reconstruction, pin or alias is added.

The refreshed drift report assigns six template names to this address after
masking relocations. That placement alone does not identify the type. Retail
instead installs the base vtable at VA `0x00BD4628` and the derived vtable at
`0x00BD4658`. The existing data ledger identifies these as
`VectorClass<VertexMaterialClass*>` and
`DynamicVectorClass<VertexMaterialClass*>`. This unit's object has exactly
those two named DIR32 relocations, at offsets `0x0B` and `0x46`; its allocation
call at `0x36` resolves to the retail array allocator at RVA `0x0002FDE0`.
The differently typed candidates cannot inherit this identity from masked
bytes or a shared assertion string. Earlier HAnimComboData attempts were
correctly rejected for their different vtables.

The target accesses establish the vector layout used here: array pointer
at `+4`, capacity at `+8`, flags at `+0x0C/+0x0D`, active count at `+0x10`
and growth step at `+0x14`. It uses a supplied array when non-null, otherwise
allocates four bytes per element, then initializes count to zero and growth
step to ten. These accesses agree with the included template. The names
and intended field roles come from that reference and the existing data
identities; the access offsets and control flow come from retail.

The Ghidra inventory has no entry for this body. Its boundaries are established
directly: the preceding destructor ends at `0x0016F5AC`, followed by three
INT3 bytes; the constructor starts at `0x0016F5B0`, returns with `ret 8` at
`0x0016F60B`, and has two INT3 bytes before the next row at `0x0016F610`.
No named direct caller was found by the existing call-graph tool. Full byte,
relocation, data and unit verification remain the admission evidence;
linking and gameplay parity are not established by this match.

The admission hook's ownership shadow names `matinfo.cpp` as the preferred
translation unit. This recovery uses the existing split unit that already
owns the matching destructor and related vector methods. Its code-identity
shadow also reports a divergent existing `??_EBfmeHandleCX@@QAEPAXI@Z` helper.
The available local link index is dated October 2 and reports duplicate
collector definitions and conflicting inline copies. Neither that old index
nor this additional exact constructor proves that the unit currently links.
