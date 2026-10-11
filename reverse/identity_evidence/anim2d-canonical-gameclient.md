# Anim2D canonical GameClient provider

The complete 901-line Anim2D.cpp was reviewed before this repair. Its old
`g_anim2DGameClient` C symbol used an `/alternatename` to the historical
ClientFrameSubsystem spelling of TheGameClient. The current data ledger
prefers `?TheGameClient@@3PAVGameClient@@A` at RVA 0x009FE77C, provided by
Code/GameEngine/Source/GameClient/GameClient.cpp. The already included
GameClient.h declares that global.

Use that declaration directly and cast its value to the existing measured
frame-slot view. The receiver and virtual offset 0x7C remain unchanged in
setCurrentFrame and tryNextFrame. No new datum, provider or pin is added.
All 22 matched rows in the unit remain exact, including four literals and
two empty strings; the data checker reports zero findings. The three
honestly declared unclaimed definitions remain unchanged.

The alternate-name occurrence is removed and its single keyed counter row
is deleted after verification. This lowers escape-hatch debt by one; it
adds no retail byte coverage and does not establish full link or runtime
parity. The data ledger's provider classification remains provisional.

The commit's code-identity shadow check also reports a duplicate
`GameMakeColor` definition. Colour-provider reconciliation is separate
remaining debt; the canonical-global repair does not claim the unit links.
