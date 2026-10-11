# Common services: files, archives, strings, name keys, debug {#sub_common_services}

The services every other subsystem stands on: opening files from disk or
from `.big` archives, reading chunk-structured binary files such as maps,
the engine's reference-counted string classes, name keys (strings interned
as small integers), the function lexicon, and EA's debug and profiling
libraries. None of them is game logic; all of them are used everywhere.
\ref grp_common_services is the subsystem's reference group; its
subgroups include \ref grp_w1_debug_lib "the EA debug library" and
\ref grp_w2_string_encoding "the string encoding helpers".

Facts marked "Zero Hour:" come from the ancestor source; this page does
not claim them for BFME 2.

## Where it lives {#sub_common_services_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Common/System/` | among others `File`, `LocalFile`, `RAMFile`, `StreamingArchiveFile`, `MemoryReadFile`, `MemoryWriteFile`, `CDManager`, `FunctionLexicon` and the `DataChunk*` readers. The directory is also a large staging area: many files hold one function, and many belong to other subsystems (INI parsing, `Xfer`, upgrades, radar) |
| `GameEngine/Source/GameClient/GUI/FileSystem*.cpp` | `FileSystem::openFile`, `doesFileExist` and `getFileInfo`: split units filed by where they were first found, not by subsystem |
| `GameEngine/Source/Common/NameKeyGenerator*.cpp` | `NameKeyGenerator` |
| `Libraries/Source/WWVegas/WWLib/string_base*.cpp`, `string_inline.cpp` | the `StringBase` template behind `AsciiString` and `UnicodeString` |
| `reference/shims/bfme2_ascii/` (outside `Code/`) | the shared headers `string_base.h`, `ascii_string.h`, `unicode_string.h` |
| `Libraries/Source/debug/`, `Libraries/Source/WWVegas/WWDebug/` | EA's debug library: the `Debug` class, its output streams, exception filter and crash dialog |
| `Libraries/Source/profile/` | EA's profiling library: `Profile`, `ProfileFuncLevel`, `ProfileHighLevel` |

Split units can be merged back into their original translation units
(`reverse/tu_map.csv` maps functions to units), so search for a function by
name rather than by file.

## Files and archives {#sub_common_services_files}

- `File` is the abstract open file (`open`, `read`, `write`, `seek`,
  `size`, `readEntireAndClose`). Its subclasses include `LocalFile`, which
  reads from disk, `RAMFile`, which holds a whole file in memory,
  `StreamingArchiveFile`, which reads a file's slice of an archive on
  demand, `MemoryReadFile`, which reads a buffer already in memory, and
  `MemoryWriteFile`, which writes into a memory buffer that grows as
  needed.
- `FileSystem` (`TheFileSystem`) is the main entry point: callers open a
  file (`openFile`), test whether one exists (`doesFileExist`) or get its
  size and last-write time (`getFileInfo`). Callers such as
  `INI::loadDirectory` also ask it for directory listings, through the
  member Zero Hour calls `getFileListInDirectory`.
- Behind it sit two back ends, one for loose files on disk and one for
  `.big` archives. The loose-file back end works on UTF-16 paths: its
  narrow entry points convert the path from UTF-8 and call a wide twin, it
  tests existence with the C runtime's wide access check, and it reads
  directories and file info with the wide Win32 find calls. Zero Hour,
  and BFME 1's reconstructed sources, call the back ends
  `Win32LocalFileSystem` and `Win32BIGFileSystem`; the ledger notes give
  the evidence behind the names BFME 2's rows use.

**Start-up.** Before it creates the file system, `GameEngine::init`
copies the language name from the registry (`GetRegistryLanguage`) into
the buffer the file system uses for its language paths; the buffer holds
`English` until then. It then calls `GameEngine::createFileSystem` and a
set-up routine on the new object. That routine constructs both back ends,
calls the init of each, and turns on "loose files first" when the loose
back end finds no `shaders.big`. The archive back end's init mounts
`lang\<language>*.big` (with `lang\EnglishAudio.big` as a fallback when
`lang\<language>Audio.big` is missing), then `*.big` in the game folder
and in `apt\`; \ref page_modding_files gives the exact order
and Zero Hour's rule for which archive wins. The command line, including
`-mod`, is parsed only after this, so archives it adds are mounted after
the game's own.

**Search order.** `FileSystem::openFile` searches:

| Mode | Order |
|---|---|
| default | the archives, then loose files |
| loose files first | loose files (under an optional extra directory, then under `lang\<language>\`, then the plain path), then the archives |

The extra directory is empty by default. A small routine copies a path
into it, turns on loose files first and mounts every `*.BIG` in that
directory with the same flag as the first archive group in
\ref page_modding_files (the `lang\<language>*.big` archives; the
fallback and the other groups do not get it). Its one call site is in
the function `GameEngine::init` calls as `parseCommandLine` (identified by
that call). Read from the retail instructions of that function: after the
arguments are parsed, it hands a `-mod` `.big` file to a virtual method of
the archive back end, and passes this routine the folder `parseMod`
records for `-mod`. So the extra directory is the `-mod` folder. BFME 1's
`parseCommandLine` consumes the two settings at the same point: it mounts
the `-mod` `.big` file, then mounts the `-mod` folder's archives with the
replace flag and records the folder as a path prefix. This rests on
reading retail instructions rather than a reconstructed body, so treat it
as a strong lead; check `reverse/functions.csv` for `parseCommandLine`
before relying on it.

A request with the access bit Zero Hour calls `CREATE` skips the
restricted-file check below and never goes to the archives, so it always
opens a loose file at its plain path. How the archive back end handles
other write requests is not established here (Zero Hour copies the
archived file to disk and returns that copy).

**Restricted-file list.** `FileSystem::initialiseRestrictedFilelist` reads
a text file whose first line is `#INCLUSION` or `#EXCLUSION`, followed by
path lines grouped under `+name` lines. Once a list is loaded, `openFile`
refuses what it rejects: an inclusion list lets through only listed paths,
an exclusion list refuses listed ones. Create requests, paths with a drive
letter and paths ending in `.big` always pass. Retail contains no direct
call to the loader, so whether it ever loads a list is not known.

\warning The globals that hold the back ends were given Zero Hour's names
provisionally, and as of October 2026 the names were swapped: the one
spelled `TheLocalFileSystem` held the archive back end and
`TheArchiveFileSystem` the loose one. Before trusting either name, for
example when reading `FileSystem::openFile`, check which object the set-up
routine called right after `createFileSystem` stores in each.
`TheFileSystem` is supported by Zero Hour and by `GameEngine::init`; check
`reverse/data_ledger.csv` for the current status of all three names.

## Chunk files {#sub_common_services_datachunk}

`DataChunkOutput` writes and `DataChunkInput` reads EA's chunked binary
format. Each chunk has a label, a version and a size, and chunks nest.
Labels are stored once, in a `DataChunkTableOfContents` that maps each name
to a small id. The reader offers typed reads (integers, reals, bytes,
`AsciiString`, `UnicodeString`, name keys, `Dict`).
`DataChunkInput::registerParser` binds a label, optionally under a parent
label, to a callback; `DataChunkInput::parse` walks the chunks, hands each
one with its version to the matching callback, and skips chunks that no
callback claims. Maps use this format: `TerrainLogic::loadMap`, for
example, registers a parser for the `WaypointsList` chunk, and the map
script classes carry chunk writers (\ref sub_gamelogic_map,
\ref sub_scripting).

## Strings {#sub_common_services_strings}

`StringBase<T>` is Zero Hour's `AsciiString` turned into a template, and
both string classes are built on it (retail exports members of both
`StringBase<char>` and `StringBase<unsigned short>`). In the shared headers
`UnicodeString` (UTF-16) derives from `StringBase<unsigned short>`, while
`AsciiString` is a wrapper with the same one-pointer layout over a
`StringBase<char>` buffer, not a subclass; the comment in `ascii_string.h`
explains why. Copies share one heap buffer: a header holds a reference
count, a 16-bit length and a 16-bit capacity, and the characters follow. A
copy only bumps the count, and a write first makes the buffer unique. An
empty string has no buffer, and `str` then returns a static empty string.
`translate` converts between the two classes through UTF-8, so an
`AsciiString` made from a `UnicodeString` holds UTF-8 text; some other
code converts with the system code page instead
(\ref grp_w2_string_encoding).

The three headers in `reference/shims/bfme2_ascii/` are the registered
shared declarations (`reverse/canonical_classes.csv`); the class gate
refuses new private copies of these classes.

## Name keys and the function lexicon {#sub_common_services_namekeys}

`NameKeyGenerator` (`TheNameKeyGenerator`) turns a name into a
`NameKeyType`. `nameToKey` hashes the string into a fixed number of
buckets, compares names case-sensitively, and hands out the next id the
first time it sees a name; `nameToLowercaseKey` is the case-insensitive
form, and `keyToName` maps back. Ids are not reused until `reset` restarts
the count. INI fields parsed with
`NameKeyGenerator::parseStringAsNameKeyType` store keys.

`FunctionLexicon` (registered as the subsystem `TheFunctionLexicon`) maps
name keys to native function pointers in typed tables. Data that names a
callback, for example a window layout's init function
(`FunctionLexicon::winLayoutInitFunc`), is resolved through it.

## Debug and profile {#sub_common_services_debug}

- `Debug` is EA's debug library object: output streams, an exception
  filter, the assert and crash dialogs and debug commands
  (\ref grp_w1_debug_lib covers it in detail). `WinMain` hands it the
  version string, the build GUID (`Version::getBuildGuid`) and the build
  time through `Debug::SetBuildInfo`. `GameEngine::init` reports INI
  exceptions and unknown exceptions that escape start-up through the debug
  library's crash path. A Direct3D failure instead shows a localised
  message box and exits when the game text is loaded, and takes the crash
  path when it is not; other engine error codes are caught without a
  report.
- The profile library is EA's profiler: `Profile` (named ranges and their
  results), `ProfileHighLevel` (named values and timed blocks) and
  `ProfileFuncLevel` (the function-level profiler).

## How it fits {#sub_common_services_fit}

- \ref sub_engine_core creates the file system and the name key generator
  early in `GameEngine::init`, before the INI-backed subsystems are
  registered, and the function lexicon later as an ordinary subsystem.
- \ref sub_ini asks `TheFileSystem` for every `*.ini` in a folder
  (`INI::loadDirectory`); Zero Hour's INI also opens each file through it.
  Names in INI become keys through
  `NameKeyGenerator::parseStringAsNameKeyType`.
- \ref sub_gamelogic_map and \ref sub_scripting read and write maps as
  chunk files. \ref sub_save_load_crc saves through `Xfer` instead; its
  string and name-key transfers live in `Common/System/` but belong there.
- The archive back end mounts `apt\*.big`, and falls back to
  `lang\EnglishAudio.big` by name when `lang\<language>Audio.big` is not
  on disk; that their contents belong to \ref sub_gui_apt and
  \ref sub_audio is inferred from the names. The GUI resolves window
  callbacks through the function lexicon.
- \ref sub_wwlib_thirdparty holds the rest of WWLib, which shares the
  string classes.

## BFME 2 vs Zero Hour {#sub_common_services_zh}

- **Search order.** Zero Hour: `FileSystem::openFile` tries loose files
  first, then the archives. BFME 2 tries the archives first unless the
  loose-files flag is set, and adds the language-folder lookups.
- **Back ends.** Zero Hour creates them through virtual factory methods
  that its Win32 engine class implements, and registers them as
  subsystems. In BFME 2 one set-up routine constructs both and initialises
  them itself.
- **Text.** Zero Hour's `translate` casts each character, which only works
  for 7-bit ASCII; BFME 2 converts through UTF-8. BFME 2's loose-file back
  end and its `-mod` handler work on UTF-16 paths.
- **Strings.** Zero Hour has two separate classes; BFME 2 (like BFME 1)
  builds both on one `StringBase<T>` template. Retail compiled some members
  for size and others for speed, which is why they are split between
  `string_base.cpp` and `string_base_inline.cpp`.
- **Name keys.** BFME 2 keeps Zero Hour's buckets but adds a reverse map
  from key to bucket, which `keyToName` uses instead of scanning every
  bucket, and a critical section around the lookups.
- **Files.** BFME 2's `File` has lock and unlock virtuals, and
  `MemoryReadFile` and `MemoryWriteFile` come from BFME 1; Zero Hour has
  none of these.
- **Not in Zero Hour.** The language-folder lookups, the flag that picks
  archives-first or loose-first, the restricted-file list, and an asset
  manager library in `Libraries/Source/assetmanager/` (not covered here).
  The first two and the asset manager library already exist in BFME 1.

## Modding notes {#sub_common_services_modding}

- **Archives win by default.** A loose file does not replace the same path
  inside a `.big` unless loose files come first. Known ways to turn that
  on: `-mod`, `-preferLocalFiles`, and running without `shaders.big` on
  disk. \ref page_modding_files gives the archive order and what `-mod`
  records.
- **Loose-file lookup.** With loose files first, a loose copy in the
  extra directory (the `-mod` folder, see above) is tried first, then one
  under `lang\<language>\`, then the plain path, and all of them win over
  the archives. The language comes from the registry; English is only the
  initial value.
- **Map chunks.** A chunk whose label has no registered parser is skipped,
  and each parser receives its chunk's version.
- **Hard limits.** A string's length and capacity are 16-bit fields. Name
  key ids are handed out in first-use order, so a name's id depends on what
  was loaded before it. Some save code stores the name rather than the id
  and looks the key up again on load (`ExperienceTracker::xfer` is one
  caller of that helper). Zero Hour defines `NAMEKEY_MAX` as 2 to the
  23rd, with a note that some code relies on keys fitting in 24 bits, but
  neither Zero Hour's nor BFME 2's `nameToKey` checks that bound.

## Remastering notes {#sub_common_services_remastering}

- **File access** goes through `FileSystem` and its two back ends. A port
  replaces the set-up routine that constructs them and the loose-file back
  end, which uses wide Win32 paths and the C runtime's wide file calls. The
  archive back end lists directories and tests for files through the loose
  back end, so it relies on that interface; whether its archive reader is
  itself platform-neutral is not established here.
- **Paths.** The built-in paths (`lang\`, `apt\`, and the separator that
  joins a folder to a file name) use backslashes; the `-mod` handler also
  accepts forward slashes. The loose-file back end reads narrow paths as
  UTF-8.
- **Text** in `UnicodeString` is UTF-16 in 16-bit units, the same size as
  Windows `wchar_t`. Where `wchar_t` is 32-bit the two are not
  interchangeable.
- **Debug output** uses Win32 dialogs, the clipboard and an
  unhandled-exception filter; \ref grp_w1_debug_lib lists its other
  platform assumptions.
- **Profiling.** The profile library reads the x86 time-stamp counter with
  inline assembly, calibrates it with `timeGetTime` and
  `QueryPerformanceCounter`, uses the debug library (pattern matching, the
  command interface) and writes its results to files, so it is x86 and
  Win32 specific as written.

## State of the reconstruction {#sub_common_services_state}

How much of each class is reconstructed, and under which names, changes
daily, so this page does not record it. To check, filter
`reverse/functions.csv` with `rg` on a class name, and
`reverse/link_status.csv` on the source path. The `-mod` hand-off under
"Search order" is read from the retail instructions of `parseCommandLine`
and its callers; check its row before relying on that paragraph. The
profile library was the pilot for the subsystem conversion process
(`docs/subsystem_template.md`). Some `Common/System/` sources hold a
single function split out of a larger file; \ref page_reading_code
explains split units.

## Reading list {#sub_common_services_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/`:
  `GameEngine/Include/Common/` (`FileSystem.h`, `file.h`, `DataChunk.h`,
  `AsciiString.h`, `NameKeyGenerator.h`, `FunctionLexicon.h`),
  `GameEngineDevice/Source/Win32Device/Common/` (the two back ends) and
  `Libraries/Source/debug/` and `profile/`.
- BFME 1: `game/GameEngine/Source/Common/System/FileSystem_openFile.cpp`
  in the reference checkout, for the language lookups and the order flag,
  and `game/GameEngine/Source/Common/ParseCommandLine.cpp`, for how BFME 1
  consumes the `-mod` settings.
- `docs/subsystem_template.md`: the subsystem conversion process, with the
  profile library as its pilot.
- \ref page_reading_code for placeholder names and split units.
