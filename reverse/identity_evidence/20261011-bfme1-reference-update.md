# BFME 1 input comparison on October 11

At the same BFME 2 revision bf8f333b41, compare the previously committed
BFME 1 pointer 575ba2b04743f190f069805fbdc59936123c45da with the fetched
official-master revision 9e3be919b10ae956e3c8a13995e0d62f2be1d016.
The donor checkout was clean before changing its detached revision.

Both normal full gates pass all 76,563 function rows across 22,054 sources,
192 data rows and the no-op patch. Both pass the literal, floating-point,
import, DIR32, pin, module and source-claim checks without new debt.
The baseline rebuilt 2,208 units; the update rebuilt 159. No baseline
failure or update regression was observed. Ignored logs are
build/resume-20261011-reference-baseline-gate.log and
build/resume-20261011-reference-updated-gate.log.

The existing layout resolver was retained. Physical game, reference,
toolchain, baseline, vendor and reverse directories were checked, along
with the resolved include directories and representative source/header
inputs. All intended directories exist; no missing include path was
silently substituted. The old and new audits are retained under
build/resume-20261011-reference-layout-{old,new}.log.

BFME 1 scan, ranked, near and lifted-body leads were refreshed at the
updated revision. ZH objects were force-regenerated after the dependency
change, then exact placements and near packets were refreshed. There
were 919 successful ZH units and 68 compile failures; the latter remain
failed leads and are not counted as verified reference coverage. No
unclaimed unique exact ZH placement was found. Lifted bodies and donor
placements remain leads, not C++ recovery or target-identity proof.

The updated pointer is included with the independently reconstructed
glow-outline body. That body's complete byte and EH admission is recorded
separately in 0073fa10-glow-outline.md. This reference comparison preceded
the new production source and ledger changes.
