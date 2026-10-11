# Call-local object path lookup

Windows profiling of the converged data audit attributed 6.8 of 10.0 seconds
to resolving object paths for 3,034 rows in eight already-built units. These
lookups repeatedly traversed the same source path components.

The byte, literal, import and DIR32 checks now reuse each source/member mapping
within one verification pass and freshly resolve every used mapping before
reporting success. No mapping survives into another pass. Library members stay
distinct. The converged data audit also rechecks mappings and rejects every row
of a remapped source/object; its existing uncached content fingerprints, object
receipts, command/dependency checks, environment checks and final movement
checks remain in place. Body extent and byte comparison code is unchanged.

Paired read-only trials on 13,379 rows in 320 existing units returned identical
facts, unread rows and literal-verification summaries:

| Check | Existing check | Reused paths |
| --- | ---: | ---: |
| Converged data | 42.5 / 41.7 seconds | 15.8 / 14.7 seconds |
| Float literals | 33.0 / 34.0 seconds | 5.4 / 4.4 seconds |

These are bounded samples, not a claim about the whole build's elapsed time.
The live affected regression suites passed 109 tests, with one existing skip.
New cases cover library member separation, fresh lookups in subsequent passes,
path remapping after exact function bytes, final checks in every reference gate,
and refusal of all converged-data rows when their object mapping changes.
Every existing gate-exploit case retains its verdict. Normal commit and push
hooks still perform their complete required verification scopes.


## Avoid rebuilding the full provider scope twice

An unbounded dependency change already requires the ordinary full build. The
push hook previously passed every explicitly selected provider to scoped builds
again after that full build, even when the full gate had just verified it. A
driver change can select all 22,100 current source files, creating dozens of
redundant chunk builds before EH and data checks can begin.

The hook now uses the existing pushed-ledger scope classifier for unbounded
changes as well. Matched C, C++ and assembly providers in functions.csv and
data_rows.csv are covered by the ordinary full gate. Every other selector stays
explicit, including rowless sources and library-member paths. Bounded partial
scopes still build every selector in chunks. Nothing reuses a previous verdict;
the full gate, all outgoing EH checks, all converged-data checks and worktree
equality checks still run in the current push. A failed or malformed scope proof
refuses publication before a build can report success.

Nine added regressions exercise unbounded complete and partial scopes, data-only
and assembly providers, retained rowless and library selectors, and malformed
provider ledgers. Together with the existing coverage and failure controls, the
isolated push-scope suite passed 33 cases.
The live push-scope, fail-closed hook and gate-exploit suites passed 84 tests,
with one existing skip.

## Keep full reference checks independent and run them concurrently

Large ordinary full gates now run the existing string, float, import and DIR32
checks in at most BUILD_POOL independent processes. Every process receives the
entire matched row scope, so cross-source DIR32 disagreements remain visible.
Their functions and input/path rechecks are unchanged. Output is reported in
the previous order, every SystemExit refusal remains a full-gate failure, later
checks still run, and worker or transport errors abort loudly. Workers compile
and write nothing. Small gates and BUILD_POOL=1 keep the serial path.

Parsed COFF layouts now also carry the first positive-section definition index
for each name. This replaces two linear scans for each body read while keeping
the original records and relocation indices. Sectionless/aux entries, repeated
locals, code-only refusals, ambiguous anonymous namespaces and initializer-size
fallbacks retain their previous decisions. The index shares the parsed layout's
existing path/mtime/size key and lifetime; it stores no byte-match verdict.

The include-ownership improvement from ae09418d1868e8a0f844fea2fda419db3252d5fe
is reconciled into the current driver. A freshly read flag directive classifies
its source once; explicit submodule paths do not need that classification.
Every directory decision and the next command's classification remain fresh.
All 22,096 current command/environment pairs were identical in a read-only
comparison (interleaved command construction: 24.0 versus 17.4 seconds).

Paired read-only checks of 13,379 rows in 320 sources returned identical complete
outputs for all four reference gates. Serial execution took 9.2/8.3 seconds;
indexed concurrent execution took 2.4/2.3 seconds. These are bounded samples,
not a full-push timing claim. The isolated affected suite passed 180 tests with
one existing skip, including every gate-exploit case. New cases cover definition
and relocation identity, fresh ownership/directory choices, complete scopes,
each propagated reference refusal and fatal worker errors.


## Overlap independent final push audits

After an unbounded dependency change has passed its complete byte gate, the
push hook now runs the unchanged outgoing EH audit and unchanged enforced
all-source converged-data audit concurrently. Both only read verified objects;
neither compiles, writes a baseline or reuses a verification verdict. The EH
source list preserves every selected path and its order; data still receives
the pushed revision, remote base and entire source scope. Bounded pushes retain
their existing serial audits.

Both processes are joined before publication can proceed. Either nonzero exit,
including process termination, refuses the push; diagnostics retain the earlier
EH-then-data order. Missing source lists, bad counts, temporary-file failures
and unreadable output also refuse it. Empty outgoing scopes still audit all
data without inventing an EH scope. The final worktree equality check remains
before either audit, and the data audit retains its fresh input/currency checks.

Thirteen new regressions prove overlap without timing assumptions, complete
scopes and output, both independent refusals, process termination, joined
workers, empty scope and orchestration failures. Existing push-scope,
fail-closed hook and every gate-exploit case retain their checks. No full-push
timing saving is claimed until the normal hook is measured on a complete push.
