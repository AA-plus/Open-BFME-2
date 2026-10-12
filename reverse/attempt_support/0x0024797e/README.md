# ObjectID interface repair evidence

Base: 58b8d20f86225fc78ccbfd3009bc3be748d11fd9. This patch is a coordinated
provider/caller repair attempt, not recovered coverage. Do not apply it without
resolving its shared-header regression and rerunning current gates.
The patch has zero context; use `git apply --unidiff-zero` on its recorded base.

Native GameLogic::DoXfer (0x0024797E, 2195 bytes) passes a full transferred
ObjectID at 0x00247D2A to ThingFactory::newObject (0x002D0A23, 275 bytes).
Object::Object (0x00298EA9) takes that enum; zero allocates a new ID. The current
factory and GameLogic::friend_createObject (0x0023CAE7, 69 bytes) instead expose
bool and reinterpret the complete bool argument slot. The patch reconciles those
two existing owner signatures and all 38 four-argument factory declaration
units, removes their obsolete bool pins, shares ObjectID, and uses canonical
GameLogic. No new body or pin is claimed. Existing donor provenance is retained;
these full-ID ABI facts are independently established from native instructions.

Verification of the patched 38 source units: 226/226 bodies, 51,511 bytes;
82 literals plus 23 empty-string references, 111 float literals and 10 imports
exact. Declaration, class and pin checks passed. The local October 2 census
lacks 36 edited units, so linking is not proven. A surviving address-derived
preset-ID factory pin used by GameLogicInit was not reconciled by this attempt.

The normal shared-header commit hook selected 418 dependent source paths and
verified 1,590 matched rows across 185 selected units. One existing body failed:
PlaceEventTranslator::translateGameMessage, 0x0043218A, 1,701 bytes. Its build
and builderObj pointer locals exchange stack slots [ebp-0x1c]/[ebp-0x20]. The
same unchanged consumer passes 1/1 with the original header, proving an introduced
regression. Removing unused new declaration parameter names or moving the new
forward declarations next to GameLogic did not repair it; these failed variants
are not the banked patch. The dependent body had a live foreign claim, so it was
not edited. The complete source attempt was restored and own claims released.

Next: reconcile the dependent consumer when available, or find a supported
shared declaration arrangement that preserves all dependent bodies. Rerun the
whole affected scope before landing. The GameLogic::DoXfer caller itself has not
been reconstructed or recovered. No gate was weakened or bypassed.
