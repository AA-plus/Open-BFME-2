# Bind dynamic native-buffer pool to its existing data owner

Checkout: 4957533b32b288adb55742d6dc6c42c3541a6fe5.
Census index measurement: cb660e4d97, 2026-10-13 04:02.
No link cycle or census rebuild was run; committed link status was not updated.

## Repair and target evidence

The allocation unit declared bfmeDynamicVBs as BfmeDynamicNativeVB*[15],
while DynamicVBAccessClassDeinit.cpp owns BfmeDynamicVB*[15]. These spellings
produce different linker names. The owner definition and all allocation,
Init and _Deinit DIR32 references identify the same retail VA 0x00DF2A04
(RVA 0x009F2A04). objects-before.json and objects-after.json record each
reference, native operand and compiled object hash. The final consumer
and provider share one linker name, independently recorded in
symbol-owner-proof.json. Native access casts keep the existing layout;
no new datum, pin, alias, fallback or original class-identity claim was added.

The source edit renumbered EH labels, exposing two stale parent spellings.
The complete byte-verified parents at 0x0013AEC0 and 0x0013AA00 have exact
retail EH graphs. These place $L3861 at 0x00765D30 and $L3250 at 0x00765D10
(funclet-parent-proof.json). Corrected only their parent annotations to the
already-rowed current names; left the $L hints, body ranges and ownership
unchanged. Parent identity comes from EH records, not adjacent addresses.

## Acceptance and limits

prepare-current before and after: 45/45 body rows, all string/float/import
checks pass, two self-strict reusable provider receipts. The first edited
byte pass refused only the two stale-parent funclets; correcting their
annotations restored full verification. Converged data check: two sources,
eight converged addresses, no second names or unjudged rows. Frozen-source
check and check_csv pass. No new authored C++ or matched bytes are claimed.

Ordinary legacy link preview before: allocation unit has four findings,
including unresolved ?bfmeDynamicVBs@@3PAPAVBfmeDynamicNativeVB@@A.
After: that unresolved finding is gone. The provider remains clean.
Cohort still has one of two clean units, 254 -> 254 LINKED bytes; no
closed-strict closure, actual executable gain or new census measurement is
claimed. Verified improvement is one resolved data-provider dependency plus
two corrected EH parent annotations; 5,625 allocation-unit bytes remain held
by the other findings.

Remaining findings: existing non-retail Get_Vertex_Count and Convert_Color
COMDATs; address scanner also flags 0x540452u, the FVF bitflag at element 10
of retail table RVA 0x007D2F04 (fvf-table.json), as an image address.
The false-reject is recorded in re_attempts.log for a separate tooling repair;
this commit does not weaken or edit the scanner. The COMDAT repairs need their
own compiler/caller analysis and are not bypassed here.

## Reference review

Reviewed donor pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 and ownership
repair commits 0835ab92bef30e3303e729a0ce09cf591368d0cd (Apt extern spelling)
and 5093777e8373a843f1f1ccfc648601ae78351aaa (Shader destructor provider).
Their rule to reuse an existing owner is applicable and adapted locally;
no donor body or layout was transferred. Target proof is the BFME2 data
references and byte/EH gates above. BFME1 freshness remains another seat's
claimed task, so no pointer/stamp update is claimed here.
