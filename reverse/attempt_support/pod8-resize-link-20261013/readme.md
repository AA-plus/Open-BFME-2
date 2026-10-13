# Remove MapUtil's duplicate Pod8 resize definition

Base: `689da8b3245a5b2adacdf00e18c70290793bda69`.
Local link index: `d753dedd98`, measured 2026-10-12 22:16.
Committed link status was measured at `e956901d31`; it is not the index used
for this experiment, and neither status nor index was rewritten.

The two claimed units are listed in `sources.txt`. MapUtil's force-inlined
one-argument `BfmePod8Vector::resize` also emits a standalone definition.
The ledger already owns that name at 0x000B0857 (23 bytes) in
`stlport_pod8_resize_byvalue.cpp`. Both current copies have identical bytes
and relocations, but the local link check reports a duplicate definition
against the exclusive native provider. MapUtil's matched caller already
inlines the wrapper and calls the by-value overload.

Remove the incidental inline definition and express its two statements at
the MapUtil call site. The POD fill remains uninitialized, exactly as in
the original wrapper. No layout, global, compiler flag, or provider changes
are involved. `resize-before.json` and `resize-after.json` show that the
MapUtil one-argument definition disappears and both provider definitions
retain their bytes and relocations. MapUtil still imports the by-value
overload.

## Acceptance evidence

- `byte-after.txt`: `./build.sh` on both units passes all five matched rows
  (164 MapUtil bytes and 124 provider bytes), string, float and import checks.
- `prepare-after.txt` / `prepare-final.txt`: bounded
  `link_check.py --prepare-current --paths-from sources.txt` verifies both
  owned units and creates strict reusable compiler receipts. These are
  strict self byte checks, not a closed-strict link measurement.
- `link-before.txt` / `link-after.txt`: the ordinary local legacy link
  preview removes the `?resize@BfmePod8Vector@@QAEXI@Z` duplicate finding
  from **both** units. All other reported blockers are unchanged. Both runs
  exit 1 because neither unit yet links cleanly. Linked bytes remain 0;
  new authored C++ bytes are 0. No closed-strict gain is claimed.
- `data-before.txt` / `data-after.txt`: the shadow data check has the same
  two findings before and after: `_m_boundaries` is a duplicate definition
  and wrong name for 0x009FF134. The original source was restored and
  byte-verified to confirm this comparison, then the repair was restored
  and strictly prepared again.
- `converged-after.txt`: enforced converged-data check passes, with eight
  converged addresses, no second names and no unjudged rows.
- `find_declared_unmatched.py` passes before and after; `check_csv.py`
  passes (87064 functions, 17272 symbols, 300 data rows); `git diff --check`
  passes. No ledger, pin, whitelist or verifier baseline is changed.

## Remaining blockers and donor review

MapUtil retains two list-node allocator COMDAT conflicts and a selected
list constructor that is not retail's. The provider retains retail-wrong
`_Construct<BfmePod8>`, `_M_fill_insert` and `_M_insert_overflow` definitions
and selections. A full link cycle and closed-strict measurement remain
outside this seat's authorization. The duplicate repair does not establish
that the private class views are otherwise reconciled.

Reviewed BFME 1 repairs `5093777e8373a843f1f1ccfc648601ae78351aaa`
(ShareBufferClass destructor) and
`d3f9000fe08615a100e844adfff57fa4a39cd615` (TileData constructor).
Their applicable lead is removing incidental definitions in favor of the
verified native owner. They do not establish BFME 2 identities or layouts;
the current BFME 2 objects, native ledger row and byte gates establish this
repair's ownership and code preservation. No donor implementation was copied.

The checked-out verified BFME 1 pointer remains
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`. Freshness fetch found upstream
`cb3b366a9708ad1d4499fb8a0557c08428d2ea8b`, but another worker holds the
submodule file claim. The checkout, committed pointer and freshness stamp
were preserved; comparative full verification and the pointer update remain
outstanding with that owner.

Two stale queue leads were rejected before editing: current PartitionFilter
destructor copies already agree and its two tested consumers link; current
MapUtil and AptMyHero Pod8 destructor copies also agree. No improvement is
attributed to either refresh. AptMyHero's claim was released; the strategic
Pod8 consumer has a foreign live claim and was not modified or prepared.
