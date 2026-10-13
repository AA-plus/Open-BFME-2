# SimpleScene RemoveAll provider repair

BFME2 base: 5c5f13ece9ba1243cd6f19c1ba3952b884422425.
Local link index: d753dedd98, measured 2026-10-12 22:20 UTC.
The committed link-status snapshot at 2a20912cc9 served discovery only.
No census index, status, history or data-back measurement was changed.

## Supported change

Remove scene.cpp's competing donor Remove_All_Render_Objects definition.
It removes a head before calling the base removal and releasing the reference.
Keep the existing verified SceneOwnership.cpp provider at 0x00141370/39B:
it peeks the owning list and invokes the virtual removal path. That provider's
existing target evidence anchors concrete vtable slot26, the render list at
receiver+0x5C and removal slot3. This repair carries that evidence and makes
no new class, layout or original-name claim.

Deleting the donor loop stops emitting the ledgered 16B RefMultiList<RenderObj>
Remove_Head at 0x00176960. The existing static_sort_list.cpp Render_And_Clear
uses the same helper; its census copy is retail-exact. add_match
--replace-existing verifies and rehomes the row there. The helper's whole
body and sole REL32 relocation are identical in the strict before/after
snapshots. No new body, pin, alias, compiler setting or range is added.
All three file scopes and both affected RVAs were claimed before edits.

Reviewed BFME1 repair 08ecd21f09b7c4672e3314ce18953c41ce4ead10 at the clean
committed input cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. Its removal of
competing unmatched definitions supplies the provider-removal approach;
no donor body, address or ABI is imported. This continues the independently
verified constructor repair in ../scene-constructor-provider-link-20261013/.
Official master fetched as 8ef3c1cb51edaa88d5cf48c80396bebcf75dfba9.
The overdue freshness/pointer update remains foreign-claimed by codex-a44d-root.
The verified checkout/gitlink and the freshness success stamp were retained.

## Acceptance and measured improvement

Before and after, link_check --prepare-current is bounded to the three claimed
units: 35/35 rows exact, seven float literals, zero baselined/skipped string
references. All three objects have self-strict reusable receipts.
./build.sh on all three passes 35/35; add_match passes the destination's 10/10.
EH verification passes 2/2, zero baseline or missing-object results.
The ordinary gates resolve the static sort constructor's renamed funclet from
its parent EH data. All 35 raw row bodies are unchanged. All named relocation
lists are unchanged except Load's switch-table local $L24640 -> $L24625;
the ordinary gate verifies that table's case mappings against retail.

Local link_check refreshes the three explicit current objects in memory
against the same legacy index. scene.cpp drops from 12 to 8 blocker instances;
SceneOwnership.cpp drops from 11 to 9; static_sort_list.cpp remains at 8.
No blockers are added. Both duplicate/selected conflicts for RemoveAll
disappear, as do scene's wrong RemoveAll and incidental Release_Ref COMDATs.
blocker-delta.json lists each removed instance. Both previews return 1:
0/3 units link cleanly and LINKED remains 0 -> 0 bytes. This is a legacy
current-object preview with self-strict inputs, not closed-strict closure proof.
No new authored bytes or closed-strict gain is claimed.

find_declared_unmatched accepts all three sources. check_csv passes 87,229
functions, 17,268 symbols and 307 data rows. Enforced converged-data checking
passes three units, eight addresses, zero second names and zero unjudged rows.
git diff --check passes. Normal commit and push hooks remain required.
No maintainer-only runner ran.

## Remaining work

Scene constructor, Customized_Render, RefCount, fog-range, camera, list and
LineSeg providers still block these units. The prior Customized_Render removal
remains deferred on its sole Get_Render_Hook emitter; it was not retried.
Each remaining provider needs separate target-supported repair evidence.
Broader closure and actual placement measurement remain outstanding.
