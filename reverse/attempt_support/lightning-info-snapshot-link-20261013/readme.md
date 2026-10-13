# LightningDrawModuleInfo Snapshot dependency repair

BFME2 base: 5d1e88bf440c5ec5c1fb8491882d570fb121df5f.
Legacy census measurement: cb660e4d97, 2026-10-13 04:02.

Both constructor and xfer views now inherit the existing canonical BFME2
Snapshot declaration instead of a private cleanup-only base. The field offsets
(+4, +0x10, +0x1c, +0x28, +0x2c) are unchanged. No body, pin or global is added.

Donor lead: Open-BFME-1 commit 1b3b6dc65aa24e3c3c88dbf89ae4cf3628d7cfab
replaced LightningDrawModuleInfo's private cleanup base with Snapshot. Its
relationship is a lead; BFME2 proof is the exact cleanup/EH graph and existing
Snapshot ABI. BFME1 ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd's MaterialInfo
vtable binding repair is already inherited by BFME2. The reference pointer
remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85: another seat holds the
reference pointer claim, so the overdue freshness update was not attempted and
its success stamp was not advanced.

Target evidence: constructor RVA 0x0056142E (171 bytes), EH handler RVA
0x00799BAF (10 bytes). Cleanup at 0x00799BA7 tail-jumps to 0x0049B47C;
the compiled cleanup relocation names ??1Snapshot@@UAE@XZ. eh-after.json
reports the complete associative EH section EXACT, without baseline use.
Native Lightning table VA 0x00C1BD80 is four slots: deleting destructor,
loadPostProcess, GetSnapshotName and xfer. The limited constructor view still
inherits an abstract loadPostProcess. Full vtable/deleting-destructor class
reconciliation with the kept FXParticleSystem owner is outstanding.

Acceptance: ./build.sh on the two consumers passed 3/3 rows; the bounded
link_check.py --prepare-current on those plus Common/System/Snapshot.cpp
refreshed explicit objects and verified 7/7 rows with self-strict reusable
receipts. class_gate.py and find_declared_unmatched.py passed the two consumers;
data_check.py --converged passed all three sources (8 addresses, no second
names or unjudged data). No full link cycle or census rebuild was run.

The local legacy link preview removes the unresolved private-base destructor
from the constructor (3 blockers to 2). Its two COMDAT conflicts remain.
The xfer and Snapshot provider remain clean: 2/3 units, 110 -> 110 linked
bytes. This is a verified dependency repair, with zero new authored C++ bytes
and no claimed linked-byte or closed-strict gain. The attached before/after
reports identify the affected consumers, provider, measurement and receipts.
