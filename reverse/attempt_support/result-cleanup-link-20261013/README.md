# Legacy result cleanup forwarding: blocked

Checkout: 4957533b32b288adb55742d6dc6c42c3541a6fe5.
Local census index: cb660e4d97, 2026-10-13 04:02. No census was rebuilt.

The existing BfmeWideResult teardown owns the complete 34-byte body at
0x0004AA28. Both consumers already read the one-word handle through its
next method at 0x00045623. Their native cleanup REL32 operands also target
0x0004AA28; offsets and pre-edit object hashes are in objects-before.json.
These are target relationships, not recovered original class names.

Tried the forwarding destructor already used in ManTheWallsSpecialPower.cpp:
`__forceinline ~BfmeResultA() { ((BfmeWideResult *)this)->~BfmeWideResult(); }`.
The full byte gates passed 8/8 consumer rows and 9/9 rows with the provider.
The self-strict prepare-current pass issued reusable receipts for all three
units, without changing the index/status or verifying LINK closure.

The ordinary legacy link preview remained 1/3 clean (34 -> 34 bytes).
The EH-enabled consumers still emit a legacy BfmeResultA destructor COMDAT
whose body is not retail's; both COMDAT and selected-definition checks refuse
it. The sibling forwarding pattern therefore cannot be extended to these
EH-enabled units unchanged. No self-strict closure or closed-strict gain is
claimed. Both source edits were reverted and all five claims released.

The BFME1 ownership repairs reviewed at committed donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
were 0835ab92bef30e3303e729a0ce09cf591368d0cd (Apt extern owner spelling)
and 5093777e8373a843f1f1ccfc648601ae78351aaa (Shader destructor provider).
Their ownership principle is applicable; no donor body/layout was imported.
The overdue BFME1 pointer refresh remains owned by another seat, so this
session did not advance its pointer or freshness stamp.

A follow-up needs supported reconciliation of the legacy return-type ABI and
EH destructor provider, rather than retrying this unchanged inline forwarding.
