# Preparation recovery, 2026-10-13

Preparation record: phase syncing, previous HEAD e682edc7465df0ffe61a2b7bc85fbddad5a465b0,
upstream b59e5c939e326f2e19c3ba643c1b56a70e2f340a,
backup refs/runner/preparation/1791885554453074732. The record names no stash.
The single replayed commit conflicted only in the two consumer sources.

Upstream already carries the portal repair in e77156e948cf9a274cf6ea52321a03029d9878f2
and the FloatUpdate repair in 72930ba726d102b68875b525847cb4f746a7e297.
Their define-inline/static-inline and immediate undef policy has the same
supported wrapper linkage result as the preserved push_macro/pop_macro version.
Neither file needs a restored functional change. Both were reconciled exactly
to upstream, including upstream's other declarations and bindings. The retained
backup preserves the original versions; it was not deleted or rewritten.

All 16 original evidence files and both original re_log.py records are retained
as historical results. This recovery adds three fresh command outputs and this
accounting. No saved untracked or unstaged changes were present, and no stash
application was requested by the preparation record. Other existing stashes
were left intact. No new task or code/class/RVA claim was taken.

## Reconciled acceptance

At b59e5c939e, link_check.py --prepare-current on the two consumers plus
AptMathCallbacksBFME2.cpp and SlowDeathRandomForceRva0045D636.cpp passes
25/25 matched rows with strict reusable self receipts. ./build.sh on the same
four sources also passes 25/25, one string literal and 13 compiler literals.
These are self-strict checks, not a closed-strict LINK closure.

The local link_check.py preview uses unchanged d753dedd98 census definitions
(measured 2026-10-12 22:20). It reproduces the historical result: both providers
and the portal link cleanly; FloatUpdate retains four blockers (duplicate and
wrong-selected update, Drawable getter COMDAT, selected Matrix3D constructor).
Legacy predicted LINKED is 1790 -> 2195 bytes, including 405 portal bytes;
exit 1 is expected from the still-blocked FloatUpdate unit. There is no new
census gain, new repair gain, actual placement or closed-strict claim from this
recovery. No census, status or history file was changed, and no maintainer-only
verification runner was started.

check_csv.py, find_declared_unmatched.py for both consumers, git diff --check
and the conflict-index check pass. The rebased commit preserves evidence only;
the upstream implementations remain byte-for-byte unchanged.
