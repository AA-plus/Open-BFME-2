# INI: data definition loading {#sub_ini}

This subsystem turns the game's text data into C++ objects. Almost every
tunable value in BFME 2 comes from an INI file: objects and their modules,
weapons, armor, locomotors, FX lists, upgrades, sciences, command buttons
and sets, audio events, the Living World campaign data and many global
settings. The `INI` class reads a file a line at a time. A block keyword at
the start of a line selects a block parser, which reads the block's fields
until the block-end line (`End`), usually by walking a table that maps each
field name to a small parse function and a member offset. The results land
in the template stores that the rest of the engine reads.

Its API group is \ref grp_ini, and the class page \ref INI covers the
parse-function signatures and the reference and duration parsers. Startup
order is on \ref page_startup, and \ref page_modding covers editing game
data in general.

## Where it lives {#sub_ini_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Common/System/INI_*.cpp` | the reader core, mostly one function per file: constructor, file and directory loading, line reader, tokenizer, the `scan*` value readers and the generic field parsers |
| `GameEngine/Source/Common/System/` (other files) | the subsystem legend's `LoadSubsystem` block parser and the legend loader |
| `GameEngine/Source/Common/INI/` | block dispatch, the field-table walk, `INIException` and many block parsers |
| `Libraries/Source/subsystem/SubsystemInterface.cpp` | `SubsystemInterfaceList::initSubsystem` |
| `GameEngine/Source/Common/GameEngineInit.cpp` | `GameEngine::init`, which drives the startup loads |
| `GameEngine/Source/GameLogic/System/GameLogicInit.cpp` | the per-map INI loader |

Block parsers also sit beside the subsystem they fill, for example
`INI::parseMouseDefinition` in `GameClient/Input/Mouse.cpp`. Many core files
are split units that `reverse/tu_map.csv` assigns to an original
`Common/INI/INI.cpp`, so search by function name rather than by file
(\ref page_reading_code).

## Key pieces {#sub_ini_pieces}

- **`INI`** is a short-lived reader, usually a local in the function that
  loads. Among its state are the line buffer, the separator strings (space,
  tab, CR, LF and `=`, plus variants for percent signs, colons and quoted
  strings), the block-end token `END` (matched without regard to case, so
  data files write `End`), the current block's keyword (the first token of
  the block's opening line), which field and end-of-file errors report as
  the block, and a list of token strings that each new line clears.
- **Block parsers** have the signature `void (*)(INI *)`. Each registered
  block is a static node holding the next node, the keyword and the parser;
  static initialisers link the nodes into one list as the program starts.
  `INI::parseLine` takes a line's first token, walks the list with a
  case-sensitive compare and calls the match.
- **`FieldParse`** rows hold a field name, a parse function, a `userData`
  pointer and a member offset. `INI::initFromINI` wraps one table in a
  `MultiIniFieldParse`, which holds up to 16 tables, each with an extra
  offset; module data classes build theirs in a static `buildFieldParse`.
  `INI::initFromINIMulti` reads lines until the block-end token, finds each
  field name (case-sensitively) in the tables in order and calls the
  field's parser on the object address plus the offsets. The tables
  therefore double as class layouts.
- **Field parsers** have the signature
  `void (*)(INI *, void *instance, void *store, const void *userData)`. The
  generic ones are `INI` statics: `INI::parseInt`, `INI::parseBool`,
  `INI::parsePercentToReal`, `INI::parseDurationUnsignedInt` and others.
  Those that name another definition look it up in its store, for example
  `INI::parseWeaponTemplate` and `INI::parseFXList`.
- **Value readers.** `INI::scanInt`, `INI::scanUnsignedInt` and
  `INI::scanReal` first pass the token through a macro-expansion step
  (BFME 1's reconstruction provisionally names it `INI::preprocessMacro`).
  In BFME 1 it replaces a macro name with its value, and BFME 2's readers list a
  predefined macro among the accepted values in their error text; this
  page does not describe BFME 2's version of the step. A token that then
  starts with `#` is a math expression: `#ADD(` and `#MULTIPLY(` take any
  number of operands up to `)`, `#SUBTRACT(` and `#DIVIDE(` exactly two.
  Operands go back through the same reader.
- **`INIException`** carries a numeric code and a printf-style formatted
  message. The field-table walk adds the field, block, file and line to a
  field error; the block dispatch adds the block and file. `INI::loadFile`
  rethrows a copy without adding anything.
- **`SubsystemLegend`** holds the parsed `LoadSubsystem` blocks of
  `Data\INI\Default\SubsystemLegend.ini`: for engine subsystems, by name,
  INI files and directories to load (\ref sub_ini_legend). It is
  a subsystem itself, the first one `GameEngine::init` creates through
  `initSubsystem`; the file system and name-key generator already exist by
  then.

## How a load runs {#sub_ini_flow}

1. **Open.** `INI::loadFile` sets the floating-point mode with `setFPMode`,
   records the optional `Xfer` and prepares the file. BFME 1 reads the file
   into a table of lines here, and BFME 2's line reader has the same shape.
   How BFME 2's preparation step (BFME 1: `prepFile`) treats comments and
   macro definitions is not covered here.
2. **Read.** `INI::readLine` copies the next line into the buffer, cut to
   1,027 characters, and passes the line text and its length to the
   installed `Xfer` when there is one. In Zero Hour this is `xferUser` on the
   CRC `Xfer`, which is how a load is hashed into the data CRC; BFME 2's call
   has the same shape, but which `Xfer` method it reaches is not established
   here.
3. **Dispatch.** `INI::parseLine` looks up the block keyword
   (case-sensitively) and calls its parser. An unknown keyword throws.
4. **Fill.** The block parser finds or creates its object, usually in a
   store, and calls `INI::initFromINI` or `INI::initFromINIMulti`. An
   unknown field name throws, unless the table ends with a catch-all row
   (no name, but a parser), which receives any unlisted field name as its
   key (\ref INI); in such a table a misspelt name is silently taken as a
   new key. Zero Hour's per-object `UnitSpecificFX` and `UnitSpecificSounds`
   lists end with catch-all rows, and BFME 2 keeps the FX list's catch-all
   parser. End of file before the block-end token also throws.
5. **Close.** The file is released. `INI::loadFile` returns 0 only when the
   file could not be prepared. `INI::loadDirectory` loads the `*.ini` files
   in a directory from a sorted list: top-level files first, then files in
   subdirectories when its `subdirs` flag is set. In that second pass an
   optional list of path prefixes, compared without regard to case, skips
   matching files. The legend loader passes its exclusion list; the
   fallback in `SubsystemInterfaceList::initSubsystem` passes none.

The load type says what a block does to an existing definition (Zero Hour's
header): `INI_LOAD_OVERWRITE` loads over it, `INI_LOAD_CREATE_OVERRIDES`
loads into a new override, as map files do, and `INI_LOAD_MULTIFILE`
continues one definition across files. Each block parser decides how to
honour it: BFME 2's `Weather` block copies its settings into an override
when loaded with `INI_LOAD_CREATE_OVERRIDES` (as `map.ini` and `solo.ini`
are) and rejects a second definition otherwise. Some BFME 2 parsers, the
`CommandButton` parser among them, also test a further value, a reload mode
that Zero Hour lacks (\ref page_core_frameworks_reload); the legend loader
is one place that selects it.

## The subsystem legend {#sub_ini_legend}

A `LoadSubsystem` block names a subsystem and lists its data. BFME 2's
block reads `InitFile` (files), `InitPath` (directories), `Extension`,
`Loader`, `ExcludePath`, `IncludePathCinematics` and `InitFileDebug`.
`SubsystemInterface::loadIniFilesFromLegend` is a virtual that
`initSubsystem` calls for each subsystem it creates; other code calls it
too, for example `GameClient::init` for the font library and the game-data
reload in `GlobalData`. It finds the entry with the subsystem's name and:

- builds an exclusion list from the entry's `ExcludePath` values, plus its
  `IncludePathCinematics` values unless a global switch is set. Writers of
  that switch include the Create-a-Hero screen's teardown, which restores a
  saved value into it, and a helper that sets it and also stores the path
  `Mods\cinematics` in the global data; what triggers that helper is not
  established;
- loads each `InitFile` whose path does not start with an excluded path
  (compared without regard to case), then each `InitPath` directory with
  subdirectories, passing the exclusion list as the directory filter;
- passes each load the subsystem list's current `Xfer`. During
  `GameEngine::init` that is the CRC writer, so legend loads made while it
  runs count toward the INI CRC. `GameEngine::init` removes the writer before it
  stores the CRC, so later calls load without one. One such caller is
  `GlobalData`'s reload handler: it reloads the game data through this
  loader and, when that succeeds, shows a "GameData reloaded" message in
  the in-game UI;
- loads with `INI_LOAD_OVERWRITE`, or with the reload load type when a flag
  in the subsystem object is set; the base constructor clears that flag,
  and what sets it is not established;
- returns true only when at least one load reports success. Without an
  entry it returns false, and `initSubsystem` then tries the caller's paths.

It does not read `Extension`, `Loader` or `InitFileDebug`, and
`INI::loadDirectory` always lists `*.ini` files. Before the lookup it also
passes `CopyProtect::setVerified` whether a file named `mithriledition.txt`
exists. That setter keeps only the first verdict it receives, and the
launcher's verdict always arrives first: `WinMain` sets it from the launcher
handshake before it calls `GameMain`, so before any subsystem loads
(\ref page_startup). In the normal startup path this check therefore does
not change the verdict.

## Entry points {#sub_ini_entry}

- **Startup.** `GameEngine::init` creates the legend subsystem and then
  loads `SubsystemLegend.ini` into it, without a CRC. It then creates the
  other subsystems through `SubsystemInterfaceList::initSubsystem`, which
  calls the subsystem's `init` and then the legend loader above, and falls
  back to paths from the caller only when the legend loader returns false.
  BFME 2's `GameEngine::init` passes no paths. It also loads `Water.ini`,
  `Fire.ini` and `Environment.ini` directly (a `Data\INI\Default` base
  file, then the `Data\INI` file of the same name) and `CommandMap.ini`.
- **Per map.** When a game starts, a GameLogic routine (Zero Hour and
  BFME 1: `loadMapINI`) loads `map.ini` and then `solo.ini` from the map's
  folder as overrides, without a CRC, and hands `map.str` to the string
  table. As in Zero Hour, a saved copy of a map is redirected to the
  original map's folder.
- **Named block files.** Some blocks are not found by keyword lookup.
  `InGameUI::init`, for example, has a helper load the `InitFile` entries
  the legend lists under one name, with `INI::parseInGameUIDefinition` as
  the parser for every block, `INI_LOAD_OVERWRITE` and no CRC writer. The
  helper catches every error itself. The first bad line ends the load
  silently: the rest of that file and any later files in the list are
  skipped, what was parsed before the error stays loaded, and the helper
  only returns false. `InGameUI::init` ignores that result, so a bad line
  silently truncates the load.

## How it connects {#sub_ini_connects}

- Engine core (\ref sub_engine_core) runs the startup loads. Common
  services provide `TheFileSystem` (\ref sub_common_services), which the
  reader uses for directory listings and existence checks and, in Zero Hour
  and BFME 1, to open files. When the file system opens a file, whether a
  loose file or a BIG archive copy wins depends on a runtime setting in its
  open path, not on the INI reader. The data CRC is an `Xfer`
  (\ref sub_save_load_crc).
- The stores it fills: things, modules and the module factory
  (\ref sub_rts_model, \ref sub_objects_modules), weapons, armor, upgrades,
  command sets and buttons (\ref page_core_frameworks), audio events
  (\ref sub_audio), Apt UI data (\ref sub_gui_apt), terrain, water and roads
  (\ref sub_w3d_rendering), the Living World (\ref sub_living_world) and AI
  data (\ref sub_ai_pathfinding).
- Network (\ref sub_network): game-join requests carry the data CRC.

## BFME 2 and Zero Hour {#sub_ini_zh}

The reader descends from Zero Hour's `Common/INI/INI.cpp`, through BFME 1.

- **Block registry.** Zero Hour: a static array of keyword and parser pairs
  in `INI.cpp`. BFME 2, like BFME 1, links registration nodes into a list.
- **File lists.** Zero Hour: `GameEngine::init` passes each subsystem its
  file paths. BFME 2 takes them from `SubsystemLegend.ini`, which BFME 1
  introduced. BFME 1's legend loader always loads with
  `INI_LOAD_OVERWRITE`, has no exclusions (its block has no `ExcludePath`
  or `IncludePathCinematics` list) and reports success whenever the entry
  lists anything. BFME 2's adds the exclusion list, the reload load type,
  the `mithriledition.txt` check and a result based on what loaded.
- **Values.** Zero Hour has neither macros nor `#` math expressions. BFME 1
  has macros; the math expressions are new in BFME 2.
- **Errors.** Zero Hour's `INIException` is built from a finished message
  string. BFME 2's, like BFME 1's, adds a numeric code and a printf-style
  constructor; the file and line are still part of the message text, as
  they were in Zero Hour's field errors. BFME 2's `INI::parseFXList` throws
  on an unknown FXList name, where Zero Hour only asserts in debug builds.
- **Logic rate.** Durations (milliseconds), velocities and angular
  velocities (per second; angular ones in degrees, stored as radians) and
  accelerations (per second squared) are converted to logic-frame units as
  they are parsed: 5 frames per second in BFME 2, 30 in Zero Hour.
- **Results.** BFME 2's loaders report whether anything loaded, and
  `INI::loadDirectory` honours its subdirectory flag; Zero Hour's do neither.
- **Block keywords not in Zero Hour's table**, among others: the Living
  World and AutoResolve families, `CreateAHeroSystem`, `EmotionNugget`,
  `LargeGroupAudioMap`, `FXParticleSystem`, `StrategicHUD`,
  `AptButtonTooltipMap`, `StanceTemplate` and `SkirmishAIData`. Some, such as
  the Living World blocks, already exist in BFME 1.

## Modding notes {#sub_ini_modding}

- **Data-driven:** which files and directories load for subsystems that take
  their lists from the legend (including its exclusions), every registered
  block and every field in its table, and per-map overrides in `map.ini`
  and `solo.ini`. Fields read through `INI::scanInt`,
  `INI::scanUnsignedInt` or `INI::scanReal`, including those of
  `INI::parseInt`, `INI::parseReal`, `INI::parseDurationReal`,
  `INI::parseDurationUnsignedInt` and `INI::parseVelocityReal`, also accept
  math expressions (`#ADD(` and the others above) and macro names; where
  BFME 2 defines its macros is not covered here. Some parsers read numbers
  directly and accept neither: `CrateTemplate::parseCrateCreationEntry`,
  for example, converts a crate's chance with a plain float scan and throws
  a load error when that scan fails.
- **Hard-coded:** the block keywords and field names, except in tables
  that end with a catch-all row; a new one needs code. Both are
  case-sensitive; the block-end token is not. Flag and enum names
  come from fixed tables in the executable: `INI::parseDamageTypeFlags`, for
  example, reads names through `INI::scanIndexList` into a 32-bit mask, so
  INI cannot add a damage type. Lines are cut at 1,027 characters.
- **Fixed file paths** include the legend's own path, the `Water.ini`,
  `Fire.ini`, `Environment.ini` and `CommandMap.ini` loads in
  `GameEngine::init`, the per-map file names `map.ini`, `solo.ini` and
  `map.str`, and files that some managers' and subsystems' own `init`
  functions load by fixed path (for example `GameLOD.ini`, `Eva.ini` and
  `Video.ini`). A legend
  directory load reads only `*.ini` files, and the exclusions apply to
  files in its subdirectories, not to files directly in the listed
  directory.
- **Errors:** an unknown field stops the load with an error naming the
  field, block, file and line, unless its table ends with a catch-all row:
  there (Zero Hour's `UnitSpecificFX` list, for example) a misspelt name is
  silently taken as a new key. An unknown block keyword names the block and
  file only. The block named in these messages is the block keyword, such
  as `Object`, not the definition's name; use the file and line to find it. Files loaded through the legend helper with a fixed parser
  (InGameUI's, for example) fail silently instead: the first error skips the
  rest of that file and any later listed files, and no message names the
  problem.
- **Missing references:** a field read with `INI::parseFXList` throws on an
  unknown FXList name. Other FXList readers do not throw: the per-unit FX
  catch-all parser stores a null entry and reports nothing, and the FX-list
  vector field parser stores a null entry and names the missing list only
  through a debug-crash report behind a runtime check (what enables that
  check is not established). A typo in a per-unit FX entry is therefore not
  caught. The generic field parsers `INI::parseWeaponTemplate`,
  `INI::parseObjectCreationList`, `INI::parseUpgradeTemplate` and
  `INI::parseParticleSystemTemplate` store a null reference for an unknown
  name without any error (the upgrade parser stores nothing at all while no
  upgrade center exists). Other readers of the same types can differ: those
  that throw an `INIException` on an unknown upgrade name include an
  upgrade-mask field parser and the Create-a-Hero sub-class and bling
  parsers. Check the reader a field uses (\ref INI) before relying on either
  behaviour.
- **Durations:** integer durations round up to whole logic frames, in effect
  to multiples of 200 milliseconds.
- **Multiplayer:** during startup `GameEngine::init` installs a CRC writer
  on the subsystem list and removes it before storing the result. While it
  is installed, the legend loader passes it to every file and directory it
  loads, and `Water.ini`, `Fire.ini` and `Environment.ini` are passed it
  directly. Files loaded without it include `SubsystemLegend.ini`,
  `CommandMap.ini`, `map.ini`, `solo.ini`, `GameLOD.ini`, `Eva.ini` and the
  files the legend helper loads with a fixed parser. `GameEngine::init`
  stores the result, plus a CRC from the Create-a-Hero manager, as the INI
  CRC, and `LANAPI::RequestGameJoin`
  sends that value with a join request. In Zero Hour the CRC covers the
  text of each line the reader returns; BFME 2's line reader makes a call
  of the same shape. Logic data must still be identical on every machine in
  a game, or the lockstep simulation diverges (\ref sub_save_load_crc,
  \ref sub_network).

## Remastering notes {#sub_ini_remaster}

- `setFPMode` uses the MSVC runtime's x87 control-word calls (`_fpreset`,
  `_statusfp`, `_controlfp`) to set single (24-bit) precision and
  round-to-nearest before parsing. Every load entry point calls it, so a
  64-bit or SSE-only port must reproduce that mode.
- Directory listing (`INI::loadDirectory`) and the existence checks in the
  legend and per-map loaders go through `TheFileSystem`
  (\ref sub_common_services). In Zero Hour and BFME 1 the file-preparation
  step also opens the file through it; this page does not verify BFME 2's
  preparation step, so BFME 2's open path is taken from those donors.
- One direct platform dependency is verified: the preparation step calls a
  helper that reads the file's modification time with the C runtime's
  `_stat` and `localtime` directly on the path and compares it, year down to
  second, with a stored date. Which load types reach that check is not
  established by verified code (see \ref sub_ini_state for how to check).
- A window-message handler can also apply a single INI field edit read
  from a named Win32 shared-memory block: it finds a named target, feeds the
  block's tokens to a temporary `INI` and runs that one field's parser,
  ignoring errors. Its purpose (inferred: a development tweak hook) is not
  established. Its only caller is the main window procedure, so data
  loading does not depend on it.
- The copy-protection verdict is set once, by `WinMain` from the launcher
  handshake, before the engine starts. The legend loader's
  `mithriledition.txt` check calls the same set-once setter later, so in the
  normal startup path the file's presence does not change the verdict
  (\ref sub_ini_legend).
- Numbers are parsed with the C runtime's `sscanf` under the x87 mode that
  `setFPMode` sets. Values parsed here feed GameLogic, so a port must
  produce bit-identical floats to stay in lockstep with retail clients.
- The logic rate is baked into parsing: two scale values in the
  executable's data, read at parse time, turn milliseconds and per-second
  rates into 5 Hz frames. A different logic rate needs both values changed,
  but that is not enough on its own: other systems read their own logic-rate
  value, and any change breaks play with unmodified clients
  (\ref page_frame_loop). Plain integer parsers apply no logic-rate scale:
  what unit such a value holds depends on the code that reads it, and a
  time field read with one does not follow a change to the scale values.

## Checking the current state {#sub_ini_state}

This page describes behaviour, not progress. Which INI functions are
matched, named or address-named changes daily, so ask the ledger:
`rg ',Code/GameEngine/Source/Common/(INI/|System/INI)' reverse/functions.csv`
lists the rows of the two INI directories, and each row's last column says
what supports it. To learn whether a name was recovered from BFME 2
evidence or carried from a donor such as BFME 1, read the row's note; for a
name pinned in `reverse/symbols.csv` without a ledger row, read the pin's
note there.

## Reading list {#sub_ini_reading}

- Zero Hour: `Code/GameEngine/Source/Common/INI/INI.cpp` and
  `Code/GameEngine/Include/Common/INI.h` under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/`.
- BFME 1: `reference/open-bfme-1/docs/ini_schema.md`, BFME 1's block
  keywords, field names and offsets read from its executable; the nearest
  documented analogue for BFME 2.
- \ref INI, the class page: field-parser signatures and how each reference
  parser treats a name it cannot find.
