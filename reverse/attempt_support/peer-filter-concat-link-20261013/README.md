# PeerThread concat repair deferred

At base 772dc3f042 and local census cb660e4d97, native Thread_Function's operands
+0xff9, +0x1007 and +0x1014 reach canonical StringBase<char>::concat at RVA 0x5629.
The provider's inner call reaches the length overload at 0x369a0. Target call
relationships are in calls-before.json. BFME 1 binding repair
5f05cce4e52a5f69608af60cc2bfa2a8e78d9187 was reviewed as a donor lead.

The combined caller/provider strict baseline passed 146/146. Binding the three
filter literal calls to StringBase preserved the 4,914-byte parent extent but
changed heartbeat ADD/CMP register bytes at +0x121a and +0x121c. A second careful
trial swapping the commutative heartbeat sum operands still failed those bytes.
Neither trial was accepted. These are byte-gate refusals, not false rejects.

The full source was restored from its preparation backup. Restored ./build.sh
passed all 109 caller rows and all string/import references; compiler-local
funclet label renumbering was checked. Both caller and provider claims were
released. No source, ledger or link gain is claimed. The blocked record is in
reverse/re_attempts.log. Do not retry without evidence resolving this codegen
shape. Preparation backups and the rejected trial remain under
build/peer-filter-concat-link-20261013 in this checkout.
