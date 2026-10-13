# Font CRT emitter and optimization-hatch repair

Source base: 3582bb2501. Supplied index measurement: cb660e4d97,
2026-10-13 04:02 UTC. The newer committed link status served discovery only;
no index, census, status, history or data-back ranking was regenerated.

Create_GDI_Font's existing complete 488B target body at 0x00154630 uses
inlined CRT operations. Include the unchanged math.h with TU-local static
inline linkage, replacing its two optimization overrides. Compiler flags,
font behavior, layout, GDI calls, data owner and ledger claims are unchanged.

Object comparison proves exactly two unused external COMDAT copies removed:
floor(float) and floorf, 18B each. All eight retained COMDATs preserve complete
raw bytes, extents, relocation tuples and digests. All ordinary non-debug
sections, strong definitions, external references and weak bindings are
identical. The live hatch scanner counts two optimization pragmas before and
zero after; this file has no corresponding baseline entries to shrink.
Source/object/index hashes and the checked facts are in object-proof.json;
snapshots and reproducible proof remain under build/font-math-link-20261013.

Acceptance: strict reusable self preparation passes before and after (1/1).
The ordinary build passes the complete 488B row, two strings, four float
literals and six imports, with no skipped or baselined references. Definition,
class, shadow data, converged-data and CSV checks pass. Same-index local legacy
preview stays LINKS, 486 -> 486 authored non-padding bytes for the current
before/after objects; its printed historical census comparison is 0 -> 486.
This repair claims two removed hatches and two fewer unused emitted copies,
zero new authored bytes and zero new legacy linked bytes. Closed-strict
closure, actual link placement and measured census gains remain unmeasured.
No maintainer-only runner was started.

Provenance: existing ledger and source preserve the BFME2-specific GDI variant
and ZH semantic lead; no donor identity or layout fact is newly asserted.
Retained verified BFME1 checkout/gitlink: cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Reviewed BFME1 repair d3f9000fe08615a100e844adfff57fa4a39cd615 supports suppressing
extra emitters while retaining existing bodies; its TileData layout is unrelated.
Prior shared-math repairs supply the tested scoped-header mechanism. Official
master was fetched as 49e35f6636748b0e1116265ce543de2f7aca0d39. The overdue pointer
update remains blocked on the previously recorded comparative full-gate/cache
preparation; verified inputs and the old success stamp were preserved.

Other trials this session: frustum scalar-helper variants preserved four
matched rows but rescheduled an unrowed body; bridge scalar-helper replacement
changed both matched bodies. Both sources were restored, evidence recorded in
re_attempts.log and claims released. Independent class/provider blockers need
separate supported repairs. Sidehash, locomotor ratios, listener walks and
small math queues already contain upstream repairs and were not retried.
