# AutoResolve factory ownership repair, 2026-10-13

Session base: `b97825ba0b`. The runner-provided census index measures
`cb660e4d97` at 2026-10-13 04:02 UTC. The committed link-status snapshot
measures a different revision and supplies queue leads only. No per-row
data-back artifact or derived ranking was used.

Move the existing 27-byte factory row at `0x004F6A1A` from
Rva004F6A1AEntryFactory.cpp to LivingWorldAutoResolveBattle.cpp, which already
emits its exact retail COMDAT and calls it from the matched 220-byte
`rva004F9C8E` consumer. Delete the split source. It contributed a conflicting
exclusive factory and a non-retail entry-destructor COMDAT. The retained home
emits the retail factory and destructor. `object-proof.txt` records whole-body
bytes, strict compiler currency, historical providers and sole row ownership.

The separate 29-byte entry constructor already links and stays in place.
The actual destructor provider Rva004F69C3Dtor.cpp also stays in place. Target
constructor accesses and the existing consumer's EH lifetime establish the
eight-byte pair and owning holder; the original type and factory names remain
unknown. No new identity, layout, pin, alias, global or escape hatch is added.
Authored C++ coverage is unchanged.

Reviewed BFME 1 repair `63955ed0f3d52748d67c899cfa5e60d72848300e`: keeping
helpers in their real caller units and retiring competing definitions applies
here; its FVF code, names and layouts do not. No donor body was imported.
The clean verified reference pointer remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Fetching official master succeeded
to `d3c65531b08be9cee475074a2f7c556061a68a97`; the overdue pointer update
remains held by `codex-a44d-root`'s `file:reference/open-bfme-1` claim. The
checkout and successful freshness stamp were preserved.

Acceptance:

- Read-only `rehome_rows.py --limit 8` proved the exact home placement; the
  broader scan was interrupted after finding this supported repair.
- `add_match.py --replace-existing`: home byte gate **15/15**, row verified.
- `link_check.py --prepare-current` on home, retained constructor and actual
  destructor provider: **18/18**, strict reusable compiler receipts, zero
  skipped/baselined references. This establishes byte identity and compiler
  currency, not self-strict or closed-strict link closure.
- Ordinary local link checks are retained before and after. The before set
  contains home, constructor and removed factory; the after set contains home,
  constructor and actual destructor. The two retained providers link in the
  after preview. These different sets do not establish a linked-byte delta.
  The home remains blocked, and the index still includes the deleted factory.
  No adjusted index, census/status edit or linked-byte gain is claimed.
- Declared-definition check, converged data check (three sources, eight
  addresses, zero second names/unjudged rows), ledger check and diff check pass.

The home retains STL copy/destroy strong duplicates, iterator/comparator and
vector insertion COMDAT disagreements, and wrong-selected copy/range-insert
providers. The next runner census must measure the removed factory provider.
No full link cycle, census build/history, nightly or boot runner was started.
