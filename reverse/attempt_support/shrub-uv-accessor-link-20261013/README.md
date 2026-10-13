# Shrub UV accessor ownership repair

Measurement index: `cb660e4d97`, 2026-10-13 04:02 UTC; starting checkout
`a59b508f4e1e97830a6e57821e4344ad477245af`. Index identity and relevant
original blockers are in `index-meta.json`. The index/status were not changed.

The shrub unit emitted a 41-byte, retail-wrong COMDAT named
`MeshMatDescClass::Get_UV_Array_By_Index(int,bool)`. It ignored the create
argument, retaining only the existing-buffer path its caller needs. The named
125-byte provider at RVA 0x000D1F40 implements both paths. The target shrub body
at 0x000E7DF3 only requests index zero without creation; its 1394-byte extent
is unchanged and byte-verifies (1388 counted authored bytes excluding padding).

Give this shortcut its own `Get_Existing_UV_Array_By_Index(int)` helper name.
The emitted canonical accessor definition and all references to that name are
now absent from the consumer, as shown by the before/after object symbol facts.
Keep its nested inline shape: directly moving the shortcut into the model
wrapper changed two address-mode bytes (commuted index/base registers) and was
reverted. The final change passes the byte gate without that codegen change.
No target identity, layout, ledger address, pin or reference header changed.

Acceptance: the three explicit owned providers have self-strict reusable
compiler receipts and pass the ordinary source/body/string/float/import gates.
The consumer plus its Get_UV_Array fallback provider pass the local link check
(2/2). The three-unit legacy preview improves from 1/3 to 2/3 and from 38 to
1426 existing authored bytes: the consumer contributes the 1388-byte gain.
The full accessor provider remains blocked by the selected UVBufferClass
constructor and other wrong accessor copies; its bytes and blockers are
unchanged. These are local legacy preview results with self-strict touched
objects, not a closed-strict census gain or proof of a full linked executable.
No maintainer-only runner was used. New authored C++ bytes: zero.

Donor review: BFME 1 checkout/gitlink
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`; reviewed donor ownership repairs
`5093777e8373a843f1f1ccfc648601ae78351aaa` (Shader destructor) and
`d3f9000fe08615a100e844adfff57fa4a39cd615` (TileData constructor), and its
meshmatdesc.h accessor. Removing an incomplete competing provider is the
applicable repair principle. BFME 2 layout, fallback and exact shrub codegen
come from this checkout and target byte verification; no donor body was copied.
Official BFME 1 master fetched as `cb3b366a9708ad1d4499fb8a0557c08428d2ea8b`.
The overdue pointer verification is held by another worker's live
`file:reference/open-bfme-1` claim; checkout/pointer/check stamp were preserved.

Files: `prepare-*.txt` are self-strict preparation plus normal byte gates;
`objects-*.json` record canonical COMDAT/symbol removal; `link-*.txt` are the
three-source legacy previews; `acceptance-link.txt` is the successful consumer
and fallback check; `verified-inputs.json` fingerprints final sources/objects.
The converged data check, ordinary data check, ledger check, frozen-file check
and whitespace check passed, recorded in `checks.txt`.
