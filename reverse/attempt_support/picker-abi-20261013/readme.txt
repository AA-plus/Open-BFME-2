0x005CBB4A caller and screen-picker ABI repair evidence, W6-SOL2 round2.

The banked caller emits the full331 native bytes exactly when proposal.patch
is applied. The patch changes the existing5CBB0A/2C00E0 wrappers to return
void* and to forward a pointer-shaped first argument; it updates the2C025A
consumer and the existing owner/EH rows, and removes three obsolete pins.
Native5CBB4A tests EAX and accesses result+10. Native2C025A forwards EAX.
The provider scope verifies5/5 bodies and2/2 EH maps. The caller uses named
lookup-result locals before virtual callback calls to postpone vtable loads.

The normal git commit was not completed: name_dependents conservatively
listed20189 units after the compiler EH names changed (bare_identifier returns
None and current cached objects were unavailable). No check refused the
repair before the seat timebox. The commit process was stopped; all live
provider/ledger/pin changes were restored. This is evidence only, no new byte
credit and no verification exemption. Never apply/commit it without normal
hooks. Refresh the patch against current owners and inputs before use.

The original class and method names for the caller remain unproven; the WB
LivingWorldThingPicker operator() is a relationship lead, not a target name.
The native receiver, slot8 category queries, classifier layout, switch cases,
selected record+10, child+38, and fallback callbacks are target evidence.
