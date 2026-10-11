# RTS model: players, teams, things and modules {#sub_rts_model}

The RTS model is the bookkeeping underneath a match: who is playing
(players, factions, relationships), how their units are grouped (teams),
what each kind of unit or building is (thing templates, from INI `Object`
blocks), and which C++ class a module name in that data stands for (the
module factory). Objects themselves are simulated in
\ref sub_objects_modules and \ref sub_gamelogic_map. API group:
\ref grp_rts_model.

## Where it lives {#sub_rts_model_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Common/Thing/` | includes `Thing`, `ThingTemplate` and its INI field handlers, `ThingFactory`, `ModuleFactory` (registrations in `ModuleFactoryInit.cpp`), `ModuleInfo`, `Module` |
| `GameEngine/Source/Common/RTS/` | includes `Player`, `PlayerList`, `PlayerTemplate` and its store, `Team`, `TeamPrototype`, `TeamFactory`, the relation maps, `ActionManager`, `ScienceStore`, `SpecialPowerStore`, `ScoreKeeper`, `Handicap`, `Energy`, `ResourceGatheringManager`, `TunnelTracker`, `ProductionPrerequisite`, the shroud manager and the hero revival tracker |
| `GameEngineDevice/Source/W3DDevice/Common/Thing/` | `W3DModuleFactory` |

A class's methods may be spread over several files; search
`reverse/functions.csv` by class name to find them.

## Key classes and singletons {#sub_rts_model_classes}

Definitions, loaded at startup:

- `ThingTemplate`: one INI `Object` definition: its fields (in Zero Hour,
  kind-of flags, costs, weapon and armor sets among them), prerequisites,
  build variations and four module lists.
- `ThingFactory` (`TheThingFactory`) owns every template by name, creates
  templates while INI loads, and creates `Object`s from them.
- `ModuleFactory` (`TheModuleFactory`) maps a module name and type to a
  parser (INI to `ModuleData`), a builder (the module on a `Thing`) and the
  mask of interfaces (update, body, contain, ...) the class implements. A
  template's `ModuleInfo` lists hold its module entries (name, tag, data).
- `Thing`: the common base of `Object` (logic) and `Drawable` (client); both
  BFME 2 constructors build it from the template first. Zero Hour: it holds
  the template, position and orientation.
- `PlayerTemplate`: one block per faction, kept by
  `ThePlayerTemplateStore` and parsed by
  `PlayerTemplateStore::parsePlayerTemplateDefinition`. Its fields include
  the side, production cost, time and veterancy changes and, as
  `Player::newMap` reads them, two starting-object names and a hero list.
  For `ScienceStore` and `SpecialPowerStore` see \ref page_core_frameworks.

Per-match state:

- `PlayerList` (`ThePlayerList`): a fixed array of twenty player slots;
  `PlayerList::update` calls each player's update.
- `Player`: per-player state, including money, sciences, score
  (`ScoreKeeper`), power (`Energy`), handicap, AI, build list, battle-plan
  bonuses, relationship overrides, the default team and the hero revival
  tracker.
- `TeamFactory` (`TheTeamFactory`), `TeamPrototype` and `Team`: a prototype is
  a map-defined team, a team a live instance of one. As in Zero Hour, every
  object belongs to a team and every team to a player.
- `ActionManager` (`TheActionManager`) answers "can this object do that to
  that target" (attack, garrison, repair, dock, special powers); the in-game
  UI, command buttons and AI code all ask it.
- The shroud manager (`TheShroudManager`, created by `GameLogic::init`) keeps
  each player's shroud state per map cell, with twenty per-player entries.
  Zero Hour has no shroud manager: it keeps shroud levels in the
  `PartitionManager`'s cells.

## From an INI definition to an object {#sub_rts_model_flow}

1. `GameEngine::init` creates `TheModuleFactory`. `ModuleFactory::init`
   registers every logic, client-update and client-behavior module, one
   hard-coded call each; `W3DModuleFactory::init` runs it and then adds the
   W3D draw modules. Data stores are created around it; among them, sciences
   come before it, and player templates, then the weapon, locomotor,
   special-power and armor stores, come after; `TheThingFactory` follows
   later (\ref page_startup has the order).
2. `INI::parseObjectDefinition`, `INI::parseObjectReskinDefinition` and
   `INI::parseChildObjectDefinition` read the block's name (for a reskin or
   child, also the original object's name) and pass them to one shared
   `ThingFactory` parser. In BFME 1's source of that parser, the factory
   finds or creates the template, copies the original into a reskin or
   child, and parses the block's fields over it. A new template starts as a
   copy of `DefaultThingTemplate` when one is defined.
3. Each module line (`Behavior`, `Body`, ...) goes to
   `ThingTemplate::parseModuleName`, which looks the name up in the module
   factory, has `ModuleFactory::newModuleDataFromINI` parse the module's
   fields, and stores the result in a `ModuleInfo` under the module's tag.
4. Once all data is loaded, `ThingFactory::postProcessLoad` resolves the
   names each template refers to (its prerequisites among them) and checks
   each template's behavior module data (the contain-module check under
   \ref sub_rts_model_modding).
5. During a match `ThingFactory::newObject` may swap the template for one of
   its build variations, has `GameLogic` construct the `Object`, runs every
   create module and initialises the object. The `Object` constructor
   builds one behavior module per entry of the template's first module list
   through `ModuleFactory::newModule`; the `Drawable` constructor builds the
   draw, client-update and client-behavior modules from the other three.
   Zero Hour splits the work the same way, without the client-behavior list.
6. `ThingFactory::reset`, the factory's subsystem reset, deletes the
   override templates and keeps the definitions loaded at startup.

## Players, teams and relationships {#sub_rts_model_players}

- `PlayerList::init` has Zero Hour's body: it resets all twenty slots and
  makes slot 0 the local player until a game sets one. Slot 0 is the
  neutral player, as in Zero Hour; BFME 2's `Object` constructor gives an
  object created without a team the default team of slot 0.
- `PlayerList::newGame` also follows Zero Hour: it re-runs `init`, creates
  a player for each named side in the map's sides list, picks the local
  player, has `TeamFactory::initFromSides` create the teams, then applies
  each side's enemy and ally lists and sets each player's default team.
- A `PlayerList` virtual calls `Player::newMap` on every slot. It creates
  the player's starting object (a game-logic condition whose meaning is not
  established picks one of the template's two names) and runs the AI's
  per-map setup. When one of several global or game-info conditions holds
  (meaning not established), it also seeds the player's hero revival
  tracker. A game-logic mode value, also not identified, chooses the
  source for every player. In one mode the source is the player template's
  hero list, unless a further game-logic check skips it. In the other modes
  only a Living World player is seeded, from its campaign revival data
  (\ref sub_living_world), and other players get no entries.
- Relationships (enemies, neutral or allies, as in Zero Hour) resolve most
  specific first: `Team::getRelationship` checks the team's per-team, then
  per-player overrides, then asks the controlling player
  (`Player::getRelationship`).

## How it connects {#sub_rts_model_connects}

- \ref sub_engine_core creates the factories and stores; \ref sub_ini parses
  their blocks; \ref sub_objects_modules holds the registered module classes
  and `Object`; \ref sub_gamelogic_map constructs objects, loads map
  overrides and creates the shroud manager.
- \ref sub_scripting and \ref sub_ai_pathfinding act on players and teams
  (as in Zero Hour, `ScriptEngine::update` calls
  `PlayerList::updateTeamStates`, which also deletes unneeded empty teams);
  \ref sub_gameclient builds `Drawable`s from the same templates; the in-game
  UI (\ref sub_gui_apt) asks `ActionManager` what a click would do.
- The player list, teams, team prototypes, relation maps, score keepers and
  tunnel trackers are saved through `Xfer` (\ref sub_save_load_crc).

## BFME 2 compared with Zero Hour {#sub_rts_model_zh}

- **Twenty player slots** (Zero Hour: 16). Player masks are 32-bit (Zero
  Hour: 16-bit); the shroud manager's per-player state and the score
  keeper's per-player counters have twenty entries.
- **A fourth module type**, client behavior, with its own interface bit; by
  name, most of its registrations are sound modules. Templates keep four
  module lists; the `Drawable` constructor instantiates the fourth as
  client-behavior (type 3) modules. Some registrations (the horde and
  transport containers, some W3D draw modules) carry a third callback whose
  role is not confirmed.
- **`ChildObject` blocks** (also in BFME 1). **Prerequisites** accept
  `Object`, `Science` and `PlayerUpgrade` (Zero Hour: the first two).
- **Player templates in override files.** When an override file (load type
  2) redefines an existing player template, BFME 2 chains a modified copy
  onto it, like `ThingTemplate` overrides; Zero Hour re-parses the existing
  template in place.
- **Object creation.** `ThingFactory::newObject` returns null for a null
  template (Zero Hour throws) and takes a pointer to a structure whose
  meaning is not confirmed (`CreateMask` in the reconstruction) and a bool
  instead of Zero Hour's status bits. It can log each new object and yields
  with `Sleep(0)` while an unidentified global flag is set.

## Modding notes {#sub_rts_model_modding}

- **Data-driven:** `Object`, `ObjectReskin`, `ChildObject`, `PlayerTemplate`,
  `Science` and `SpecialPower` blocks (\ref sub_ini). `DefaultThingTemplate`
  and `DefaultSpecialPower`, when defined, seed every new definition.
- **Map overrides:** when it loads a map, the game logic reads the map
  folder's `map.ini` and `solo.ini` as override files and its `map.str` as
  extra strings; the INI files are read without the CRC `Xfer`. In BFME 1
  and Zero Hour, an override `Object` block for an existing template chains
  a modified copy onto it. A `Prerequisites` block in an override file
  replaces the template's list instead of adding to it (BFME 2 and Zero
  Hour). `ThingFactory::reset` deletes the override templates again.
- **Module names are a fixed vocabulary**: only names registered in code are
  valid, the module type must match the field, and a new module class needs
  code. `reverse/module_factory_registrations.csv` lists the
  `ModuleFactory::init` registrations (logic, client-update, client-behavior)
  with type and interface mask; `W3DModuleFactory::init` registers the W3D
  draw modules (see `W3DModuleFactoryInit.cpp`).
- **Module line rules** (`ThingTemplate::parseModuleName`): every module needs
  a tag; `Body` takes only body modules and the other module fields refuse
  them; in override files, a module line must sit inside an `AddModule` or
  `ReplaceModule` block, and a plain or `InheritableModule` line is refused
  (the error text mentions only `AddModule`); `ReplaceModule` needs a
  replacement with the same module name and a new tag. Outside override files,
  declaring a module first removes, from all four lists, inherited entries
  that implement any of the same interfaces, except those declared under
  `InheritableModule`. BFME 2 tests only that overlap and two per-entry flags
  (by layout, Zero Hour's copied-from-default and inheritable flags); Zero
  Hour adds special cases. Under load type 4, which BFME 1 uses for
  `ChildObject` blocks, nothing is removed. Unlike Zero Hour, where the text
  is debug-only, these errors throw `INIException` with a message.
- **Post-load check:** `ThingFactory::postProcessLoad` stops loading with
  "ENTRY MISSING: ObjectStatusOfContained entry required within
  ContainModule" when a template's behavior module data fails a check; by
  the message, a contain module without that entry (the fields it tests are
  not established). BFME 1 and 2 have it; Zero Hour does not.
- **Starting objects:** if the name a player template gives for its starting
  object matches no `Object` definition, `Player::newMap` returns early and
  skips the AI's per-map setup and the hero setup for that player.
- **Hard-coded:** twenty player slots, fixed in class layouts, and 16-bit
  template ids (as in Zero Hour). When one global setting (purpose not
  identified) is 1 or 2, the `PlayerTemplate` parser adds only templates
  whose side is literally `Dwarves` or `Wild` to the playable set.
- **Multiplayer:** players, teams and objects' behavior modules are
  logic-side state, and build variations use the logic random generator.
  Draw, client-update and client-behavior modules belong to `Drawable`s
  (\ref sub_rts_model_remastering) but are declared in the same `Object`
  blocks, so they still count toward the INI CRC. The thing factory and the
  player-template, science and special-power stores load through the CRC
  `Xfer`, so their INI data is part of the INI CRC that multiplayer
  compares.
- **Saves:** the classes under \ref sub_rts_model_connects use versioned
  `Xfer`. Zero Hour: a saved `Object` keys each behavior module's state by
  module tag and matches by tag on load, so tags are part of the save format.

## Remastering notes {#sub_rts_model_remastering}

- **Renderer seam.** `GameEngine::init` obtains the module factory through
  the engine's `createModuleFactory` virtual (\ref sub_engine_core); Zero
  Hour's `Win32GameEngine` override returns a `W3DModuleFactory`. In both
  games `W3DModuleFactory::init` registers the draw modules after the logic
  and client ones, so a different renderer would register its own draw
  modules in its own factory.
- **Logic and client split.** Behavior modules are simulation state. BFME
  2's `Drawable` constructor builds the draw, client-update and
  client-behavior modules (types 1, 2 and 3) and the `Object` constructor
  only behavior modules (\ref sub_rts_model_flow, step 5), so client
  behaviors sit on the client side. Editing any of them still changes the
  INI CRC, like other object data.

## Following the reconstruction {#sub_rts_model_state}

This page describes behaviour, not progress. To see which functions here
are matched, how they are named and whether their files link, search
`reverse/functions.csv` by class name and `reverse/link_status.csv` by
directory, or run `tools/link_rank.py --file` on a source file.
Address-named functions and files are placeholders (\ref page_reading_code)
and are not described here.

## Reading list {#sub_rts_model_reading}

- Zero Hour (`GeneralsMD/Code/GameEngine/` in the reference tree):
  `Include/Common/Module.h`, `Source/Common/Thing/` (`ModuleFactory.cpp`,
  `ThingFactory.cpp`, `ThingTemplate.cpp`), `Source/Common/RTS/`
  (`Player.cpp`, `PlayerList.cpp`, `Team.cpp`, `ActionManager.cpp`).
- BFME 1 (`game/GameEngine/Source/Common/Thing/`): `ModuleFactory.cpp` and
  `INIParseObjectDefinition.cpp` (the shared parser for the three object
  blocks).
- `reverse/module_factory_registrations.csv`, `tools/check_module_registry.py`.
