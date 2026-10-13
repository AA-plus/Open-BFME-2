# Chat close callback IME global binding

BFME 2 base: 7739b008efc83b7b9beebdc6631d268442db762b. Discovery used
repair_queue.py link and link_rank.py. Committed link status was measured at
e181b4b6c5, 2026-10-13 11:22 UTC. The unchanged available local index is
cb660e4d97, 2026-10-13 04:02 UTC; its SHA256 is recorded in both object
proofs. No per-row data-back artifact, census update or full link cycle was
used.

## Target evidence and repair

AptInGameChatRva004E8620.cpp declared TheIMEManager as IMEManagerInterface *,
which emitted an unresolved global different from WinMain.cpp's owned
IMEManager * global. The callback's complete 80-byte body has a zero-addend
DIR32 operand at +62 reaching native VA 0x00DFE728. WinMain's rowed WndProc
operands at +70 and +105 independently reach the same address through
?TheIMEManager@@3PAVIMEManager@@A. That symbol is a strong definition in
WinMain's current object and is the owned data-ledger name at RVA 0x009FE728.

Declare the canonical opaque class pointer and cast it to the existing
callback view only for its slot-15 virtual call. No new datum, class body,
layout claim, pin, alias, fallback, compiler flag or ledger range is added.
The callback's entire COMDAT bytes and extent are unchanged; its single
changed relocation is the global name. WinMain's entire object is unchanged.
objects-before.json and objects-after.json contain hashes, native operands,
symbol definitions and relocation comparisons. No other tracked consumer
declares TheIMEManager with the rejected IMEManagerInterface pointer type.

The callback's established vtable/receiver evidence and address-derived
method identity remain as documented in its source and ledger. The global
binding proves no new semantic method identity or instance layout.

## Donor review and freshness

Reviewed BFME 1 ownership repair 0835ab92bef30e3303e729a0ce09cf591368d0cd:
reuse the provider's existing typed global while retaining a consumer access
view. That principle is applicable and adapted locally; its Apt bodies,
addresses and layouts are inapplicable and were not imported.

The clean verified BFME 1 checkout remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Official master was fetched to
a167c5ebc52054d7cd12de68d3c6094a45dfc60d. The foreign
file:reference/open-bfme-1 claim held by codex-a44d-root prevents this
seat's overdue pointer update. Keep the verified inputs and existing stamp;
comparative full gates remain with the freshness-update owner.

## Acceptance and limits

- Normal consumer byte gate: 1/1 exact complete body.
- Explicit provider/consumer preparation before and after: 10/10 exact
  bodies, 12 literals and one empty-string reference, 51 named imports,
  zero float literals. Both objects have strict reusable compiler receipts.
  These prove object currency and byte identity, not self-strict link closure.
- Enforced converged-data check: two sources, eight protected addresses,
  zero second names and zero unjudged rows. Consumer data shadow: zero findings.
  Declared-definition, canonical-class, ledger and diff checks pass.
- Same-index legacy preview before: callback unresolved global, 0 accepted
  bytes; provider clean, 3,150 accepted bytes. After: both clean, 3,230 bytes.
  Thus the repair adds 80 locally accepted legacy bytes, removes one finding,
  and adds none. Transcript LINKED arrows use the historical census baseline;
  the actual prepared before/after cohort is 3,150 -> 3,230.
- Placement resweep: zero bodies, zero pins. Zero new authored C++ bytes.

No self-strict or closed-strict LINK gain, measured census gain, executable
placement or boot success is claimed. The current callback has no local
preview blockers. A fresh runner census and maintainer-authorized full link
cycle remain outstanding. Existing unrelated untracked dumps and ZH sweep
preparation were preserved.
