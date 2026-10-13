# Movie audio concat dependency repair

BFME 2 base: 3120306bc5. Queue discovery used repair_queue.py link and
link_rank.py with the committed link_status measurement at 2a20912cc9,
2026-10-13 08:08. Both before/after local previews use the unchanged census
index at d753dedd98, 2026-10-12 22:16. Its SHA256 and metadata are attached.
No per-row data-back artifact, new census or status edit was used.

The existing 345-byte movie-audio setup at RVA 0x00091763 appends `_Music`
to the supplied name before resolving the companion audio event. The
REL32 operand at body+0x37 targets retail RVA 0x00005629. Its original
AsciiString::concat(const char *) relocation names a selected definition
that the local census proves is not retail's. The existing 37-byte provider
at that RVA is StringBase<char>::concat(const char *) in string_base.cpp;
its length-overload call at +0x1C targets 0x000369A0.

Bind that single append to the existing StringBase provider through the
canonical one-pointer view. Attached call records prove the unchanged native
destinations and changed consumer relocation. Existing recovered source and
its BFME 1 audio lead remain the behavioral guide; this repair introduces
no new identity, layout, pin, alias, global, compiler setting or ledger row.
No decoder implementation or third-party decoder source was read.

Reviewed BFME 1 linking repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
at verified checkout cee35b7d8ca077d7255f1c39cb69e9fd9627aa85: its direct
StringBase binding principle applies, while its compare implementation and
addresses are not imported. The equivalent local concat-link-20261013 and
ai-upgrade-concat-link-20261013 repairs supply BFME 2 leads. Official BFME 1
master was fetched at 2aa1f01b6a9201ce4026594eea916605e31f7b64. The live
foreign file:reference/open-bfme-1 claim held by codex-a44d-root blocks the
freshness pointer update. Retained the clean verified pointer and unchanged
success stamp; comparative update verification remains with the update owner.

Acceptance:

- Consumer/provider ./build.sh before and after: 38/38 matched rows, five
  literals, 15 empty-string references and three named imports; zero
  baselined or skipped references.
- Ordinary local link_check.py on both current objects: exactly the selected
  literal-concat finding disappears, no new findings. Consumer changes from
  does-not-link to LINKS, 0 -> 345 authored bytes. Provider remains LINKS,
  1,185 bytes. Cohort 1/2 -> 2/2, 1,185 -> 1,530 bytes.
- Declaration check, check_csv.py, converged-data check and git diff --check
  pass. Source/object hashes and unchanged index hashes are attached.

This is a legacy census-preview improvement of 345 existing authored bytes,
with zero new authored C++ bytes. Bounded prepare-current excludes VP6-named
paths; it was not invoked or bypassed. No self-strict, closed-strict or actual
link.exe gain is claimed. Full dependency closure and a current whole-game
measurement remain runner/maintainer work. No full link cycle, census
build/measure/history, nightly or boot operation was started.
