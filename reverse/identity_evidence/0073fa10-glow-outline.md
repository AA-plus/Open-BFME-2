# Glow-outline state body at RVA 0x0073FA10

The complete executable boundary is VA 0x00B3FA10 through 0x00B4011F,
1807 bytes, ending in an ordinary `ret`. All 393 instructions were read;
the last return is at 0x00B4011E. This body was unrowed before recovery.

Target facts: ECX is saved as the receiver, then forwarded unchanged to
the matched 213-byte `W3DGlowOutlineMaterialPassClass::UpdateFadeState`
at RVA 0x0073F895. Receiver +0x3C is later uploaded as the first float of
a four-float shader constant. The native path names
`shaders\\unlitnormalextrusion.vso`. It initializes a three-element D3D9
vertex declaration, calls the matched loader at 0x00077C19, uses the
existing resource globals at VA 0x00E1F294 and 0x00E1F298, and updates the
existing DX8Wrapper state and constant caches.

The shader-change mask is 0x8000. Retail's byte OR at VA 0x00B3FAD8
addresses the second byte of render_state_changed at 0x00DEC4F4.
The initial 0x80 reconstruction passed the scoped masked-byte gate but
failed full DIR32 consistency by resolving that name to 0x00DEC4F5.
Correcting the mask gives the emitted relocation its required +1 addend;
the two matrix-identity tests independently establish the +2 byte there.
The final whole-file gate verifies both bodies with this correction.

The native texture settings are COLORARG1 = TFACTOR (state 2, value 3)
and COLOROP = SELECTARG1 (state 1, value 2). The fade result becomes
TEXTUREFACTOR. Device vtable offsets 0x158, 0x15C, 0x170 and 0x178 are
the observed declaration creation/binding, shader binding and float
constant upload operations. The D3D9 interface declarations are reused
from this repository's verified dx8wrapper.cpp view.

WorldBuilder's 15225-byte debug counterpart contains the inline
DXWrapper::Get_Transform and Set_Vertex_Shader_Constant assertions and
calls the independently named glow fade routine. These labels establish
the inline operation leads; they do not establish the enclosing method's
original name. `rva0073FA10` preserves that uncertainty. The extrusion
field's role is inferred from its upload and the shader path; its original
member spelling is unknown.

The matrix sequence follows the complete target: obtain world and view
from the existing transposed cache or identity flags, transpose each,
transpose the applied projection, multiply view by projection and then
world by that product, and transpose the result for constant registers
4 through 7. A plain static four-float array supplies register 8. No
default Vector4 construction is inferred: retail has no initializer
guard for this array. The local ShaderClass initialization does have a
guard and writes the target's 0x00105833 bits.

The existing mapper DX8 header supplies the direct render-state naming
call that retail uses. The home header's dllimport declaration emits an
indirect call and cannot reproduce that site. Empty Matrix4 construction
uses the existing bool-false constructor shape, leaving every field to
the explicit cache/identity paths. No callee pin or alias is introduced.

The complete scratch reconstruction and whole-file draft both reproduce
all 1807 bytes with every direct callee resolved. The whole-file draft
also reproduces the existing fade body's complete 213 bytes. Scratch
evidence is retained under build/resume-20261011-glow-*: probe05,
shape05, home-main and home-fade. Earlier probes retain the rejected
default matrix construction, wrong texture-state interpretation, indirect
state-name call and unnecessary static Vector4 initializer.

Production admission through add_match passed both complete bodies, the
shader-path literal and five floating-point literals. EH verification
reports the new body's exception data EXACT, with no baseline debt.
The frozen-file check reports every definition matched. The enforced
converged-data check reports no second names across eight addresses, and
the new-COMDAT-variant admission check passes.

The commit's shadow checks report two remaining identity debts. The
projection reference uses the existing strong provider
g_mapperProjectionUpload_009EDBF0 in TextureMapperApply.cpp; the data
ledger prefers DX8Wrapper::DeviceProjectionMatrix, which other units
currently map to that provider using alternatename. This recovery reuses
the provider and adds no new datum, but the shadow wrong-name finding
remains. Code identity also reports a divergent emitted Matrix4 assignment
COMDAT. The complete matched routines pass; a clean whole-link selection
for that helper has not been established by these checks.

The ordinary linking preview uses the October 2 census at 6963cc017c.
It reports three unresolved names (the now-rowed shader loader and two
D3DX import thunks) and four selected definitions not matching retail
(StringClass construction/destruction and the two DX state-name helpers).
Those are census-relative blockers, not proof about current linking.
The transient current-ledger preview refused to judge linking because
9,132 objects lack strict current compiler evidence. It changed no census
record. Its log is build/resume-20261011-glow-current-link.log. No whole-tree
linker run or receipt exception was used to turn that refusal into proof.
These checks do not establish linked execution or rendered-game parity.
