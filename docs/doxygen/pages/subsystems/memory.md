# Memory: heaps and allocators {#sub_memory}

This subsystem is where the engine's memory comes from. BFME 2 keeps its
memory in a handful of heaps, each an EA `GeneralAllocator`, behind a small
exported API, `namespace MemoryPool`, that picks a heap by a numeric id.
Global `operator new` and `delete`, the C `free` and STLport's byte allocator
reach that API through function pointers; two small wrappers call the
default heap directly. Smaller pool allocators sit in front of it, among them
WWLib's fixed-size object pools and several small-node pools used by
GameLogic, WWLib and WW3D2 code. Apt's DOGMA pools serve small requests from
per-size free lists; the memory behind them comes from the global array
`operator new[]`, which the game installs as Apt's allocation callback.
The subsystem holds no game state: it decides where bytes live, not what they
mean.

Its API group is \ref grp_memory. The engine's startup sequence, from
`WinMain` on, is on \ref page_startup; the heaps are built before that, by a
static initialiser that the C runtime runs before calling `WinMain` (see
\ref sub_memory_lifecycle).

## Where it lives {#sub_memory_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Common/System/memory_pool.cpp` | the `MemoryPool` API and its heap table, plus a partial view of `EA::Allocator::GeneralAllocator` |
| `GameEngine/Source/Common/System/MemoryPoolInit.cpp` | `MemoryPool::_Init`, which builds the heaps |
| `GameEngine/Source/Common/System/GameMemoryFree.cpp`, `MemoryImportFreeAdapters.cpp` | the C `free` replacement and two small free adapters |
| `GameEngine/Source/Common/System/DefaultAllocatorWrappers.cpp` | two default-heap wrappers that bypass the `MemoryPool` API |
| `Libraries/Source/WWVegas/WWLib/mem_ops.cpp` | global `operator new`, `delete`, `new[]` and `delete[]`, and the pointer slots they call through |
| `Libraries/Source/WWVegas/WWLib/stlport_byte_allocator.cpp` | STLport's byte allocator, routed into the game allocator |
| `Libraries/Source/WWVegas/WWLib/ObjectPoolAllocateObjectMemory.cpp` | `ObjectPoolClass`, WWLib's fixed-size object pool; other instantiations are spread across WWLib, WWMath and WW3D2 |
| `GameEngine/Source/GameLogic/Object/Update/FreelistPool*.cpp` | `FreelistPool`, a small-node pool |
| `Libraries/Source/Apt/Dogma*.cpp` | Apt's DOGMA pool allocator (\ref sub_gui_apt) |

Some pieces described below (the export resolver, the heap registration
routine, the current-heap scope guard and many `GeneralAllocator` methods)
are not in the files listed above, and file placement in this area changes
as units are rehomed; find them by function name (see \ref sub_memory_state).

## Key pieces {#sub_memory_pieces}

- `namespace MemoryPool` is retail's own name. `game.dat` exports
  thirteen functions under it, so their names and parameter types are ground
  truth: `_Init`, `_Exit`, `_AddHeap`, `_Allocate`, `_Reallocate`, `_Free`,
  `_GetBlockSize`, `_IsValidBlock`, `_GetBlockHeap`, `_VerifyIntegrity`,
  `_GetHeapAllocator`, `_GetHeapAllocatorByIndex` and `_DumpFragmentation`.
  The lookup functions, `_GetHeapAllocator` and the `_Allocate`,
  `_Reallocate`, `_IsValidBlock` and `_GetBlockSize` calls built on it,
  treat id 0 as "the calling thread's current heap", and use the default
  heap when no named heap matches. `_AddHeap` treats id 0 as the default
  heap itself, and `_GetBlockHeap` returns 0 for a block in the default heap
  (and for an address no heap owns).
- **The heap table** holds a default heap and room for thirty named heaps,
  found by id through a small hash table. Its variable names in the source
  are descriptive names chosen during the recovery, not retail symbols.
- `EA::Allocator::GeneralAllocator` is the heap type named by the export
  signatures. A few of its methods carry names taken from the symbol file of
  another EA game built on the same allocator library (EA's PPMalloc); those
  names are donor identities, not symbols found in BFME 2. Source files may
  declare only the members they use, so read a method's callers before
  trusting one file's view of the class (\ref page_reading_code).
- **Heap ids** are short codes of up to four ASCII characters packed into a
  32-bit value, such as `init`, `asst` and `str`. The source writes them
  either as multi-character constants or in hex. A small scope object sets
  the thread's current heap id in a TLS slot and restores the previous id
  when it goes out of scope. A caller can also pass an id with a single
  allocation, as the string classes do through the extra argument of
  STLport's byte allocator and a tagged array `new`.
- **Allocation type.** `_Allocate`, `_Reallocate` and `_Free` take an
  allocation-type argument, an enum named `AllocType` inside
  `namespace MemoryPool`. The enum's name comes from the export
  signatures; its value names do not appear there. `operator new` and `delete`
  pass 1, the array forms 2, and `free` and STLport's byte allocator 3; two
  small free adapters pass 0. BFME 2's `_Allocate` and `_Free` accept the
  value but ignore it.
- `ObjectPoolClass<T, BLOCK_SIZE>` (WWLib) hands out fixed-size objects from
  blocks of `BLOCK_SIZE`, growing one block at a time, behind a one-word
  test-and-set lock that yields to other threads while it waits.
- `FreelistPool` carves blocks into small fixed-size nodes and hands them
  out from a free list. The name is descriptive, given by the recovery.
  There are several global `FreelistPool` objects. Their users include
  STLport list-base constructors and node creators for more than one list
  instantiation, and a shared initialiser called from constructors that
  include several behaviour and update modules, `Player` and an STLport
  `list` copy constructor. Each user pops a node from one of the global
  pools, and the initialisers link the node to itself to start a circular
  list. That fits the node being the sentinel of an STL list, but it is an
  inference: the original names are unknown. The constructor defaults the
  pool's allocate and free callbacks to the two default-heap wrappers, which
  call the default heap's `GeneralAllocator` directly rather than going
  through `MemoryPool`; the global pools are initialised statically with the
  same callbacks. A long strip of identical static initialisers registers
  exit-time cleanups for the behaviour pool and its sibling pools.
- **Apt's DOGMA pools** serve the Apt UI runtime. The class names
  `_DOGMA_MemPool` and `DOGMA_PoolManager` come from the symbols of another
  Apt build; BFME 2's own asserts name the source file `DogmaAllocator.cpp`
  and the `CanFitBytes` check. Any request up to the pool's maximum is
  rounded up to a multiple of four bytes (with a per-pool minimum) and
  served from a free list for that size, or carved from a pool with room.
  Oversized requests, and the memory for new pools, come from Apt's
  host-supplied allocation callback (`gAptFuncs.pfnMemAlloc`). The game's
  Apt host setup fills the allocation and free callbacks with the global
  array `operator new[]` and `operator delete[]`, so DOGMA memory comes from
  `MemoryPool::_Allocate` (type 2, the current heap) through the pointer
  table. Oversized frees go through a separate sized-free callback in the
  same table. The host setup leaves that one empty, so Apt installs its own
  default, which passes the pointer on to the free callback.

## Lifecycle {#sub_memory_lifecycle}

1. **Resolve.** A small static initialiser, one of the entries in the
   table of C++ static initialisers that the C runtime's startup code runs
   before calling `WinMain`, calls the export resolver. The resolver looks
   up each exported `MemoryPool` function in the running executable by its
   mangled name (`GetModuleHandle` and `GetProcAddress`) and stores it in a
   pointer table. In the retail code nothing else calls the exports
   directly: the API's own lookups call `_GetHeapAllocator`, and every other
   caller goes through the pointer table. To find the initialiser, look
   for the only direct call to the resolver in the executable;
   `tools/callers_of.py` lists only named callers.
2. **Initialise.** The same initialiser then registers the resolved `_Exit`
   with `atexit` and jumps to `_Init` through the table.
   `MemoryPool::_Init` is reference-counted; only the first call does work.
   It runs the heap registration routine, which is the only time `_AddHeap`
   is honoured, creates a private Win32 heap to hold the allocator objects,
   builds the default heap and one `GeneralAllocator` per registered heap,
   installs an empty assertion callback and allocates the TLS slot for the
   current heap id.
3. **Register.** During `_Init`, `_AddHeap` with id 0 sets the default
   heap's size; any other id adds a named heap, or updates the size of one
   already registered. Once thirty named heaps exist, further registrations
   are ignored.
4. **Allocate and free.** `_Allocate` and `_Reallocate` use the heap chosen
   by id. `_Free` instead asks each heap in turn whether it owns the address
   and frees it there; an address no heap owns is ignored, and once a
   shutdown flag is set every free is ignored.
5. **Check.** `_VerifyIntegrity` validates every heap; `_IsValidBlock` and
   `_GetBlockSize` ask the heap chosen by id; `_GetBlockHeap` returns the id
   of the heap that owns an address.
6. **Exit.** `_Exit` runs at process exit, through the `atexit`
   registration above. It is reference-counted too. The last call walks each
   heap's block report but does nothing with the entries, so it produces no
   report; it does not tear the heaps down.

## Heaps in use {#sub_memory_heaps}

The registration routine makes four registrations, with sizes fixed in code:
the default heap's size and three named heaps. What
the allocator does with a size (an initial reservation or a limit) is not yet
established. The default heap's size starts at 8 MiB in the executable's
data; the registration replaces it.

| Heap | Size passed | Selected by |
|---|---|---|
| default (id 0) | 256 MiB | everything that names no other heap |
| `init` | 48 MiB | `GameEngine::init`, around creating and initialising `TheThingFactory` |
| `asst` | 256 MiB | the asset manager's background worker thread and part of its loading code |
| `str` | 48 MiB | string buffers, including `StringBase` storage, WWLib's `StringClass` and `nstrdup`, chosen per allocation |

## How it connects {#sub_memory_connects}

- **Most allocation ends here.** Global `operator new` and `delete`, the C
  `free` replacement and STLport's default byte allocator all call the
  `MemoryPool` API through the pointer table. `FreelistPool` and the other
  small-node pools of its shape use the default heap directly, through the
  two wrappers.
- Engine core (\ref sub_engine_core): `GameEngine::init` builds the thing
  factory with `init` as the current heap.
- Common services (\ref sub_common_services): `StringBase` buffers come
  from `str`.
- Rendering (\ref sub_w3d_rendering): the asset manager's worker thread and
  part of its loading code run with `asst` as the current heap.
- Apt (\ref sub_gui_apt) runs its own DOGMA pools. The game fills Apt's
  allocation and free callbacks with the global array `operator new[]` and
  `operator delete[]`, so the pools' memory, and oversized requests, come
  from the `MemoryPool` heaps.
- WWLib and third-party code (\ref sub_wwlib_thirdparty): `ObjectPoolClass`,
  and the vendored STLport, whose byte allocator is routed into the game's
  allocator.

## BFME 2 compared with Zero Hour and BFME 1 {#sub_memory_zh}

- **Zero Hour** has a different design in `GameMemory.cpp` and
  `MemoryInit.cpp`: a `MemoryPoolFactory` (`TheMemoryPoolFactory`) owns
  named `MemoryPool` objects of fixed-size blocks, usually one per class and
  attached with the `MEMORY_POOL_GLUE` macros, and a `DynamicMemoryAllocator`
  serves variable-size requests, including global `operator new`.
- Zero Hour: pool sizes come from a table in `MemoryInit.cpp`, which
  `Data\INI\MemoryPools.ini` can override at startup. The name
  `MemoryPools` does not appear anywhere in BFME 2's executable.
- In BFME 2 the exported heaps take that role: global `operator new` ends
  in `MemoryPool::_Allocate`, where Zero Hour's goes to
  `TheDynamicMemoryAllocator`. Whether any per-class pool layer survives
  above the heaps is not yet established. Zero Hour's
  `TheMemoryPoolFactory` has no confirmed BFME 2 counterpart. Zero Hour:
  the `MEMORY_POOL_GLUE` macro and its create variants give a class a
  `getClassMemoryPool` that finds or creates its pool through the factory.
  No retail BFME 2 body is confirmed as that glue, so it is part of the
  same open question.
- **BFME 1** already has the exported `namespace MemoryPool` and the
  resolver that loads it by name, with eight exports and no heap ids. BFME 2
  adds the heap id parameter, `_AddHeap`, `_GetBlockHeap`, the two heap
  allocator queries and `_DumpFragmentation`. Its export signatures name
  the heap type, `EA::Allocator::GeneralAllocator`; BFME 1's name none.
- `ObjectPoolClass`: Zero Hour takes each block from the global
  `operator new`; BFME 2 takes it from STLport's byte allocator, which ends
  in `MemoryPool::_Allocate` with type 3. Both guard the pool with the same
  kind of one-word test-and-set lock, which yields to other threads while it
  waits.

## Modding notes {#sub_memory_modding}

- **Heap layout is code, not data.** No INI or other data file sets heap
  sizes or limits: the four heap sizes are constants in the registration
  routine, the table has room for thirty named heaps, and a registration
  outside `_Init` is ignored.
- **No `MemoryPools.ini`.** Zero Hour reads `Data\INI\MemoryPools.ini` to
  resize its pools; BFME 2 does not reference that file, so adding one does
  nothing.
- **Command-line options read at startup:** `-zerofillmemory`, in any case
  but not as `--zerofillmemory`, switches `_Allocate` to the allocator's
  calloc-like entry (count, size), which presumably returns zeroed memory;
  the clearing itself has not been confirmed from the allocator's code.
  `-startPaused`, matched case-sensitively, shows a "Waiting..." message box
  before the heaps are built. The routine also tests for `-poolbigblocks`
  and `-bigmemorysentinals` but discards the result, so those options do
  nothing in retail.

## Remastering notes {#sub_memory_remastering}

- **The main seam is the pointer table.** Global `new` and `delete`, `free`
  and the STLport byte allocator call through pointers filled from the
  executable's own exports. A replacement allocator plugs in by filling
  those pointers, and must accept a free of any address it handed out from
  any heap, since `_Free` finds the owner by address.
- **Not every path uses the table.** The two default-heap wrappers in
  `DefaultAllocatorWrappers.cpp` call the default heap's `GeneralAllocator`
  directly. Several node pools with `FreelistPool`'s shape (8-, 16- and
  24-byte nodes, in GameLogic, WWLib and WW3D2 code) use them as their
  callbacks. Some are built by `FreelistPool`'s constructor or by two other
  constructor-like initialisers (one in WWLib, one in GameLogic AI code);
  others are initialised statically in the data section. Their users
  include node allocations for some STLport `list` and `map`
  instantiations. A replacement backend has to cover those too, or keep a
  compatible default heap.
- **Apt is covered by the table.** Apt's allocation and free callbacks are
  the global array `operator new[]` and `operator delete[]`, so DOGMA memory
  follows the pointer table. Its oversized frees go through Apt's default
  sized-free callback, which passes the pointer on to the free callback; a
  remaster that changes Apt's callbacks should check that path separately.
- **Win32 dependencies include** `HeapCreate` for the allocator objects,
  `TlsAlloc` and the TLS calls for the current heap, `VirtualAlloc` for the
  heaps' core memory and `VirtualFree` when a heap returns it, critical
  sections for heap locks, and `GetModuleHandle` and `GetProcAddress` for
  the resolver. The allocator code also calls `VirtualQuery` and
  `GetSystemInfo`, at sites whose roles this page does not establish.
- **32-bit assumptions:** heap ids, sizes and block sizes are 32-bit values.
  The registered sizes add up to 608 MiB; how much of that a heap claims up
  front is not yet established.
- **Threads:** the current heap is per thread, and the asset manager's worker
  thread allocates from its own heap, so the allocator is used from more than
  one thread.

## Following the reconstruction {#sub_memory_state}

Names, placeholder rows and file homes in this area change as the work
continues, so this page does not list them. To see the current picture,
search `reverse/functions.csv` (with `rg`, never by loading it whole) for
`MemoryPool`, `GeneralAllocator`, `FreelistPool` and the files above;
`tools/callers_of.py` walks a function's callers, and `tools/link_rank.py
--file` shows whether a unit links yet.

## Reading list {#sub_memory_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/`:
  `GameEngine/Source/Common/System/GameMemory.cpp`, `MemoryInit.cpp`,
  `GameEngine/Include/Common/GameMemory.h` and
  `Libraries/Source/WWVegas/WWLib/mempool.h`.
- BFME 1, in Open-BFME-1's `game/` tree:
  `GameEngine/Source/Common/System/memory_pool.cpp` and `memory_pool.h`.
