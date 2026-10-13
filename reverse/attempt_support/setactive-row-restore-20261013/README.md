# Restore sole SetActiveBattleID ledger owner after rebase

Preserved cleanup commit 772dc3f042 rebased as a04486a493 against e6dfd607e9.
Its former duplicate-row deletion then removed the only remaining SetActiveBattleID
row at 0x20E63F. The source definition and three callers remained. Publication's
byte gate correctly refused three unresolved references; no hook was bypassed.

add_match.py restored the existing whole 110-byte owner through the normal gate.
The source was not changed and no pin or new identity was introduced. Existing
source documents WB identity and target extent20E63F..20E6AD RET8. Verification
passed all 123 rows in the owner and two dependent units, with string, float and
import references exact. Eight existing renumbered funclet pins and two complete
STLport constructor folds passed their ordinary gates.

The local link preview at cb660e4d97 reports owner and small battle-start consumer
clean; the broad LivingWorldLogic unit still has independent unresolved, duplicate
and selected-definition blockers. No link gain is claimed for this restoration,
and the legacy totals are not comparable to the newer committed census. This
restores coverage already on origin/master, adding zero session recovery bytes.
