# SimpleScene constructor provider repair

BFME2 base: 22f30565df159762453b6334f45257235111cca2.
Local link index: d753dedd98, measured 2026-10-12 22:20 UTC.
The committed link-status snapshot at 2a20912cc9 served discovery only.
No census index, status, history or data-back measurement was changed.

## Supported change

Remove scene.cpp's unmatched donor SimpleSceneClass constructor, which
initializes the older Visibility_Checked layout and competes with the rowed
retail constructor at 0x00142960/563B. Keep the existing target provider in
SimpleSceneClassConstructorBFME2.cpp. Its existing evidence records the native
BD33D0 vtable, Scene base size 0x34, spatial member 0x34, lists 0x5C..0xEC and
stamp 0x104. This repair carries that evidence; it makes no new layout claim.

Removing the donor constructor stops emitting MultiListNodeClass's ledgered
19B constructor at 0x00065802. The retained target provider already emits the
same complete body without relocations, so add_match --replace-existing
rehomes that row there and verifies it. No body, pin, alias, class view,
compiler setting or boundary is added. Delete only the removed constructor's
present-unmatched key from the hatch register; other baseline keys stay intact.
Both files and the affected RVAs were claimed before edits.

Reviewed BFME1 repair 08ecd21f09b7c4672e3314ce18953c41ce4ead10 at the clean
verified pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its removal of six
competing unmatched definitions supplies the provider-removal approach;
no donor body, address or layout is imported. Existing source provenance stays.
Official master fetched as 207ce65d3217a13728a6275b5b1ce5a7be5145c4.
The overdue freshness/pointer update remains foreign-claimed by codex-a44d-root.
Retain the verified checkout/gitlink and leave the success stamp unchanged.

## Acceptance and measured improvement

Before and after, link_check --prepare-current is bounded to the two claimed
units: 17/17 rows exact, five float literals verified, zero baselined or skipped
string references. Both objects have self-strict reusable receipts. The ordinary
scene byte gate passes 14/14; add_match verifies the provider's three rows.
The snapshots retain all 17 identical raw row bodies. Sixteen named relocation
lists are unchanged; Load's local switch-table label changes from $L24669 to
$L24640, with its mapping verified by the ordinary byte gate.

The ordinary local link_check refreshes both explicit current objects against
the same legacy index. scene.cpp drops from 19 to 12 blocker instances;
the constructor provider drops from 18 to 15. No blockers are added.
The constructor's duplicate and wrong-selected conflicts disappear in both
units, along with its scene COMDAT conflict and incidental list/vtable conflicts.
blocker-delta.json lists each removed instance. Both checks still return 1:
0/2 units link cleanly and LINKED remains 0 -> 0 bytes. This is a legacy
current-object preview with self-strict inputs, not closed-strict closure proof.
No new authored bytes or closed-strict gain is claimed.

find_declared_unmatched accepts scene.cpp (14 matched rows, six existing
unclaimed definitions). check_csv passes 87,194 functions, 17,268 symbols,
307 data rows. Enforced converged-data checking passes both units: eight
addresses, zero second names, zero unjudged rows. git diff --check passes.
Normal commit and push hooks remain required. No maintainer-only runner ran.

## Remaining work

A first trial also removed the competing Customized_Render definition.
The byte gate refused the missing MultiListNode constructor and the sole
emitted Get_Render_Hook helper at 0x003EFCA4/7B. The list helper can be rehomed
as above, but the getter has no other emitter in the index. Restore the render
definition and record this specific deferred removal before releasing its claim.
A supported getter provider is needed before retrying that removal.

Remaining independent conflicts include SceneClass's constructor,
Customized_Render, Remove_All_Render_Objects, RefCount, GenericMultiList,
fog-range, camera and vtable providers. They need separate evidence-backed
repairs. Broader closure and placement measurement remain outstanding.
