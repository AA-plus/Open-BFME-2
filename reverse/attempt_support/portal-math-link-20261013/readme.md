# Fake pathfinding portal math-wrapper linking repair

Starting BFME2 revision: 6de149d1402cc4ad3ce5fa4d4ab05a748ff35bd5. The available local census index measures
cb660e4d97, 2026-10-13 04:02 UTC. Committed link_status.csv instead measures
2a20912cc9 and served only queue discovery. Neither record was changed.

The current portal unit failed the local link preview solely because its
MSVC math.h sin(float) and cos(float) COMDATs differed from the selected
copies. Apply the already verified scoped static-inline inclusion used by
Rva00106F82TangentField.cpp and StrafeAreaUpdateRva003A4FDA.cpp. The original
MSVC overload definitions and compiler settings remain the source of the
inlined math operations. No class, ABI, field, pin, alias, datum, flag, ledger
row or extent changed. The existing portal identity and layout are carried
from its ledger evidence; this repair establishes byte preservation only.

Before/after COFF facts remove precisely sin(float), cos(float), sinf, cosf.
All five retained COMDAT names, body-and-relocation digests and lengths are
unchanged; strong definitions, undefined externals and weak bindings are
unchanged. No other compiled consumer or external provider is modified.
The existing sin/cos provider in AptMathCallbacksBFME2.cpp is checked with
the consumer and remains exact and locally linkable.

Acceptance evidence:

- Before/after strict reusable self receipts: portal 1/1, complete 406-byte
  body and one compiler float literal exact. Ordinary ./build.sh also passes.
- Unchanged provider strict reusable self verification: 20/20 bodies and
  three compiler float literals exact.
- Same legacy local census preview: portal 0/1 -> 1/1 clean, LINKED 0 -> 405
  existing bytes (padding excluded). Consumer plus provider final 2/2 clean,
  LINKED 1332 -> 1737 bytes. The provider remains 1332 bytes and unchanged.
- New-variants admission, class gate, declared-definition check, CSV check
  and diff whitespace check pass. EH check has zero applicable rows.
- Enforced converged-data check: one source, eight addresses, zero second
  names and zero unjudged rows. Shadow data check: zero findings.

This is +405 existing bytes in the legacy local preview and +0 authored
C++ bytes. Strict self verification is proven; closed-strict closure, actual
link.exe placement and a new measured census gain are not claimed. No full
link cycle, census build, nightly or boot runner was started.

Donor review: retained clean BFME1 checkout/gitlink cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Reviewed newer linking repair d2e21369067f2f2c762c1c7ec2792c75f1ecf53d:
its suppression of surplus non-retail inline emitters supports the same
ownership principle, while its BfmeStrVKI constructor/pin solution is
inapplicable to this math unit. No donor source or pin was imported. Existing
broader donor scan in concat-link-20261012 and the strafe repair is retained;
no unchanged blocked donor work repeated.

Official BFME1 origin/master fetched at 1f208555ffd3c0feb6aeac4bd6b20603f5e5ef5e.
Freshness update remains under the live foreign file:reference/open-bfme-1
claim held by codex-a44d-root. Kept verified inputs and the existing success
stamp; the comparative full-byte update is outstanding with that worker.

Scope probes also checked current CylindricalEmissionVelocityModuleSample,
Rva004E5372CloudArcs, AIGateUpdateTrigger and RandomTextureMapperCalculate:
all four already LINKS. They were neither claimed nor edited. Ranked
Rva001E46E1Ratios and Rva003FA781 files are foreign-claimed and were skipped.
