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
