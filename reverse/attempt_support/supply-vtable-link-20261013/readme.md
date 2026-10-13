# Supply draw ModuleData vtable dependency repair

BFME2 source base: 46854a32f7. The supplied census index was measured at
cb660e4d97, 2026-10-13 04:02 UTC; object-proof.json records its SHA256.
The committed link-status report at 67e1365aa9 was used only for discovery.
No census, status, history or per-row measurement artifact was regenerated.

W3DSupplyDrawModuleDataCtor.cpp now refers directly to the existing decorated
??_7W3DSupplyDrawModuleData@@6B@ symbol instead of vtbl_00BCC0D0 plus an
/alternatename directive. Its unchanged provider is
W3DSupplyDrawModuleDataDtor.cpp. One actual alias hatch and its keyed baseline
entry are removed. No implementation, header, flags, extent, pin or ledger
ownership changes. A repository search found no other consumer of this alias.

Target identity and layout are inherited from the existing constructor and
destructor evidence: constructor 0x000CAF17 stores vtable VA 0x00BCC0D0,
destructor 0x000CAF30 restores it, and deleting destructor 0x000CAF8A supplies
its slot. The provider object defines this exact decorated table symbol.
This repair establishes no additional class-layout or source-identity facts.

The already reviewed BFME1 repair ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd
supplies the direct-name technique; BFME2 addresses and declarations are
verified independently. Official BFME1 master was fetched and remains
001cf898fa5a0415d9d5c5db631b23b4d530ec3b. Donor linking commit b870d563b7f4e8b58f433635a39783fb0d7d55cb
was already reviewed by the preceding session and is inapplicable here.
The clean checkout and verified gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
are preserved. Freshness remains overdue: the preceding baseline full gate
needed 5882 stale TUs and was interrupted at the shared compiler lock. The
required old/new full-byte comparison remains outstanding; the freshness
stamp and donor inputs have not changed.

Acceptance:

- Bounded strict reusable preparation before and after passes all four rows
  across consumer and provider. The independent normal byte gate passes 4/4
  with zero baselined or skipped string, float or import references.
- EH verification reports one EXACT parent, zero baseline entries.
- object-proof.json compares every non-debug/non-directive section's raw
  bytes, flags, association and normalized relocations. They are identical,
  as are every external definition. Exactly one zero-addend DIR32 reference
  changes from the alias to its existing target. The provider object is
  byte-for-byte unchanged. Both objects have strict-current receipts.
  Reproducible scratch proof and snapshots: build/supply-vtable-link-20261013.
- Same-index legacy local link previews retain 100 linked bytes from the
  provider and zero from the consumer. The consumer's remaining blocker is
  wrong_selected ??0W3DModelDrawModuleData@@QAE@XZ. This is a verified
  escape-hatch reduction with self-strict byte evidence; no self-strict link
  closure, closed-strict gain, new authored bytes or full-link gain is claimed.
- Declared-definition and class checks and git diff --check pass. Commit
  hooks also enforce ledger, data, converged-data and hatch-baseline checks.

The blocked constructor verdict records the remaining dependency in
reverse/re_attempts.log; it is not a nonmatching reconstruction. Broader link
verification remains maintainer-only. Permitted fallback discovery:
name_globals.py --dry-run reports zero supported rewrites; rehome_rows.py
--limit 12 cannot run because build/link_census/census.log is missing. That
failure is missing preparation, not queue exhaustion. repair_queue.py link
and link_rank.py remain populated. Unrelated untracked preparation is retained.
