# MaterialInfo vector vtable alias repair

At BFME2 base `65fb6caf5b0397a21da82b44381cffe47e9213fe`, replace the
MaterialInfo destructor's `_VectorClassVertexMaterialPtrVtable` declaration and
linker alternatename with a direct reference to the existing decorated
`VectorClass<VertexMaterialClass*>` vtable. Remove its one baseline alias entry.
This is an escape-hatch debt repair: authored C++ bytes and locally linked bytes
both grow by zero; the alias count falls from one to zero.

The structural change follows BFME1 repair
`ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd`, reviewed from fetched upstream
`778c9a8e2239e462f693396406eceadede0059b0`. The target's vtable identity and
VA `0x00BD4628` are supported independently by the existing
`reverse/identity_evidence/vertex-material-vector-constructor.md` and the full
byte/relocation gate. The donor establishes the direct-name technique; it does
not supply BFME2 addresses or prove BFME2 link closure.

The only affected consumer is
`Code/Libraries/Source/WWVegas/WW3D2/MaterialInfoDtor.cpp`. Its unchanged provider,
`MaterialCollectorDestructor.cpp`, defines the decorated vtable symbol.
`object-symbols.json` records a strict-current receipt for both objects, the
consumer's direct undefined reference and the provider's definition. The old
alias spelling is absent from the new consumer object. No provider source,
pin, ledger extent, compiler settings or census artifact is changed.

Before and after bounded `link_check.py --prepare-current` checks pass for the
consumer with strict reusable receipts and all six ledger rows byte-exact
(245 bytes including unwind and EH rows). `./build.sh` independently passes.
These are self-strict byte checks, not closed-strict LINK measurements.

The legacy local `link_check.py` preview uses the available index measured at
`d753dedd98`, 2026-10-12 22:16; it reports 215 own bytes and LINKED 0 -> 0 both
before and after. Duplicate `MaterialInfoClass` destructors, a nonretail
`RefCountPtr<TextureClass>` vector deleting destructor, a differing
`RefCountClass` scalar deleting destructor and the wrong selected MaterialInfo
destructor remain. The committed link-status snapshot belongs to a different
measurement and is not used to claim gains. No per-row data-back artifact or
closed-strict measurement is available. A maintainer-only link cycle remains
outside this seat's authorization.

BFME1 freshness was checked by fetching official upstream. The clean verified
pointer stays at `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`: another live owner
holds `file:reference/open-bfme-1` (`codex-a44d-root`). Its freshness timestamp is
not advanced. The upstream update and its full verification remain that owner's
work; this source repair compiles with the existing verified inputs.

Attached transcripts preserve the bounded strict checks, byte gate, local link
previews, object symbols and before/after hatch counts. Ledger consistency and
the undeclared-definition check also pass.
