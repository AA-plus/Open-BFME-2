# AptOnlineLogin response pump at 0x00571C9D

Target evidence is separate from the donor below. The method's original spelling
is unknown, so the row uses `AptOnlineLogin::rva00571C9D`.

## Target

- Complete native boundary: `0x00571C9D..0x00572571`, 2,260 bytes, ending in RET.
  WorldBuilder `0x015090F0` reaches the AptOnlineLogin.cpp path but carries no
  method name. The native receiver uses the same gadget/state/owner offsets as
  this unit's previously verified AptOnlineLogin members.
- The peer queue at `TheGameSpyPeerMessageQueue` gates the body. Pinger slot
  `0x1C` reads a 20-byte response, followed by the existing login checker. Buddy
  and persistent-storage pumps update receiver bytes `0xD1` and `0xDC`; the
  latter invokes the independently named `OnAccountDeleted(true)`.
- One 840-byte PeerResponse is constructed/destructed through the existing
  providers `0x00389F77` / `0x0038A063`. Its type switch handles 0 (login),
  1 (disconnect), and 23 (nickname list). Native uses the nickname string at
  `0x10`, AsciiString vector at `0x100`, reason/profile word at `0x10C`, and IP
  words at `0x130` and `0x134`; other fields remain opaque.
- Native disconnect fetch uses GameText slot `0x38` with a pointer to the
  AsciiString label, while literal fetch uses `0x3C`. MSVC's reversed overload
  grouping reproduces both with a const-reference label overload.
- PersistentStorageThread.cpp independently witnesses the 1,432-byte request
  (stats at `+8`, string fields and flag bytes) and 1,408-byte response whose
  only owning member is the stats at `+8`. Existing stats providers establish
  the 1,352-byte stats record (`0x548`); this body reads only id/locale at
  `+0/+4`. Compile-time checks retain the three aggregate extents.
- When the stored preference locale is outside 1..37, native posts a locale
  update, reconciles an existing cached record, publishes cached stats, and
  queues the resulting response. It snapshots the returned record's locale
  before querying preferences and clears flag `0x581` before `0x580`.
- The posted nickname list is persisted with the entered email, optional
  remembered password, and `01/01/1970`, then cached gadgets are refreshed.
  The existing firewall factory/detector and owned allocation release follow
  login completion. No new provider pin or second global name is introduced. The home unit's
  four old first-word color reads now use the existing `GameSpyColor[0]` owner
  from Chat.cpp/data_ledger.csv instead of the address-derived scalar name;
  their complete bodies remain byte-exact.

## Donor and adaptation

Clean `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginUpdate.cpp`
at verified BFME1 revision `9e3be919b10ae956e3c8a13995e0d62f2be1d016` provides the
semantic spine: ping/login checking, response pumps, Apt enable calls, login and
disconnect flows, locale requests and persistent-storage publication. Its older
record sizes, slots, group-room arm and stats parsing are not target facts.
BFME2's nickname-list arm, current record providers, existing cached-locale
reconciliation and firewall completion were reconstructed from native evidence.

## Verification

The isolated trial initially emitted 2,274 bytes. Correcting the independently
witnessed response extent, const-reference fetch ABI and case number produced
2,258 bytes. Capturing the returned locale before the preference call restored
2,260; retail's two flag-store ordering made all body bytes exact. Source import
was verified by `add_match.py`: 19/19 bodies in the whole unit and all 82 literals,
12 empty-string references and four named imports passed. EH is checked by the
normal commit/push hooks. A rescan placed zero additional bodies or pins.

These are source/byte/layout results; no fresh linking or runtime result is claimed.
