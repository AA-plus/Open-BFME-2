# Strafe update math-wrapper emission repair

Starting checkout: 68eab7807d. Local census index: cb660e4d97,
2026-10-13 04:02 UTC. Committed link_status instead reports 2a20912cc9;
it was used only for queue discovery. No census/index/status was modified.

The MSVC math.h float overloads inline into StrafeAreaUpdate::update, but
also emit incidental external wrappers. The local preview rejects this
unit solely for ?sin@@YAMM@Z, which differs from the selected definition.
The existing ledger owns that name at RVA 0002FBB0, extent seven bytes,
in AptMathCallbacksBFME2.cpp. This repair does not change that provider.

Apply BFME2's existing Rva00106F82TangentField.cpp header pattern: define
inline as static inline only while including math.h. This keeps the original
MSVC definitions and makes the surplus float wrappers private. The function's
identity remains ledger-carried; the gate proves its existing 948-byte body
and relocations, not new identity or layout. No class, header, flags, pin,
alias, datum, ledger row or extent was changed.

Read-only COFF comparison (object-delta.json) shows removal of precisely
sin(float), sqrt(float), sinf and sqrtf COMDAT definitions. All 21 common
COMDAT digests and lengths are unchanged. Strong definitions, undefined
externals and weak bindings are unchanged. Thus no consumer acquired a new
external dependency and no kept provider or other compiled consumer changed.

Acceptance:

- Before and after --prepare-current verifies 1/1 matched body, four compiler
  float references, zero string/import references, with strict reusable self
  receipts. Final ./build.sh also passes these checks.
- Ordinary local link_check changes from sole sin(float) COMDAT blocker,
  LINKS 0/1 and LINKED 0 bytes, to LINKS 1/1 and LINKED 945 bytes (non-padding
  bytes in the existing 948-byte row) at index cb660e4d97. after-link.log
  records the successful preview.
- New-variants admission, class_gate, find_declared_unmatched, check_csv and
  git diff --check pass. EH check finds no EH rows. Enforced converged data
  check: one source, eight addresses, zero second names/unjudged rows.
  Shadow data check: zero findings.

This is +945 existing bytes in the legacy local link preview, with strict
self verification, and +0 authored C++ bytes. Closed-strict closure, refreshed
census gain and executable placement remain unmeasured. No maintainer-only
link cycle, census build, nightly or boot runner was started.

Donor review retains verified BFME1 gitlink/clean checkout
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Reviewed d3f9000fe08615a100e844adfff57fa4a39cd615:
its suppress-surplus-emission principle applies; its TileData class/body
repair does not apply. Existing broader ownership/dependency scan recorded
in concat-link-20261012 was not repeated without changed relevant inputs.
BFME1's retained Rva000697B0ScanTangentAngle.cpp uses ordinary math.h and is
not a matching wrapper-emission repair. No donor source was imported.

Official BFME1 master fetched at 574de716f6fec638c9ae834f116549b9813d10c2.
The overdue verified-pointer update remains foreign-claimed by codex-a44d-root
as file:reference/open-bfme-1. Retained verified inputs and old success stamp;
no successful freshness update claimed. Comparative full-byte verification
and any update repairs remain with that worker.

Separate PhysicsBehavior::calcFlightPath destructor-emission trials failed:
dllimport removed its COMDAT but changed exception cleanup to an unresolved
import; plain forceinline preserved exact cleanup but retained the conflict.
Both were restored and the original three bodies and EH cleanup reverified.
The blocked verdict is in re_attempts.log; its four claims were released.
Callback/class cleanup reconciliation remains outstanding. Scratch evidence
and original backups remain under build/physics-curve-link-20261013.
