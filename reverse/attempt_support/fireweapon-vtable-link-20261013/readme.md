# FireWeaponUpdate direct vtable bindings

Source base: 5ad1c7246ff1ebabccca2e41ab6a343344eb304c (verified checkout after the initial pull). Supplied census
index: cb660e4d97, 2026-10-13 04:02 UTC. The newer committed link-status
measurement served discovery only. No census, status, history or per-row
artifact was regenerated.

FireWeaponUpdateCtor and FireWeaponUpdateBehaviorDtor replace three address-named
extern vtable references and /alternatename directives with the existing real
decorated names via __identifier. The destructor emits the primary FireWeaponUpdate
table; AIGateUpdateCtor emits the folded BehaviorModuleOther table. The current
provider was verified read-only. No type, layout, flags, body extent, pin, alias,
header or donor implementation was added. Three matching hatch-baseline lines
are deleted.

Identity and table ownership are inherited evidence: the destructor's primary
vptr store and named compiler table bind VA C4C198, with its xfer slot documented
in symbols.csv; the constructor's existing alias identifies the folded table
BEFF90 with AIGateUpdate's BehaviorModuleOther table. The independent matched
AIGate constructor installs that table at +0xC. This change makes those existing
bindings direct; it introduces no new donor identity or layout assertion.

Strict reusable preparation passes 6/6 rows in the two consumers and provider,
before and after. The standalone ordinary byte/reference gate also passes 6/6,
378 ledger bytes; zero baselined or skipped literal references. EH check reports
two EXACT parents, zero baseline entries. Declared-definition, class, CSV,
shadow-data and enforced converged-data checks pass (zero data findings).

object-proof.json compares all non-debug/non-directive sections: every raw byte,
section flag, association and normalized relocation tuple is identical. All
external definitions stay unchanged. Exactly three zero-addend DIR32 operands
switch from the old aliases to their existing named targets. Both provider names
are defined in strict-current objects; the read-only AIGate object is identical.
Source and object hashes and the supplied measurement are recorded. Scratch
snapshots and the reproducible proof remain under build/fireweapon-vtable-link-20261013.

The same three-unit legacy local link preview reports the same blockers before
and after, zero linked bytes gained. Both FireWeapon consumers retain the literal
secondary UpdateModuleInterface table address C4C18C, whose update body is banked
partial. AIGate retains unused@BehaviorModuleBase and update@UpdateModule unresolved.
No self-strict link closure, closed-strict gain, new authored bytes, measured
census gain or full executable placement is claimed. The verified improvement
is removal of three linkage hatches. No maintainer-only runner was started.

Donor review reuses the unchanged dedicated linking scan and BFME1 repair
ac2f5d9fd32492fe7e92a399246f6ff7b0b025dd (MaterialInfo direct vtable naming).
Its direct-name technique applies; donor layouts and addresses do not. Retained
verified donor checkout/gitlink is cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Official master fetched this session is 84bc8e173cd20f710f84d6b25bce48b03b4bd774. It differs from
that retained pointer. The overdue update still needs comparative full-byte
verification; the prior session records the baseline/cache preparation blocker.
Verified donor inputs and the old success stamp were retained, and no freshness
success is asserted. Unrelated untracked dumps and ZH preparation were preserved.
