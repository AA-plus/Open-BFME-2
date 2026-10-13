# Weather override global tag repair

Base: `3e6478074e`. Supplied census index: `d753dedd98`,
2026-10-12 22:16. Committed link status is a separate measurement at
`67e1365aa9`, 2026-10-13 16:47. Neither artifact was rewritten.

W3DSnowStateTransition.cpp declared OVERRIDE as a struct, producing
`?TheWeatherSetting@@3U?$OVERRIDE@VWeatherSetting@@@@A`. The byte-verified
Snow.cpp owner and matched data row use the class-tagged symbol
`?TheWeatherSetting@@3V?$OVERRIDE@VWeatherSetting@@@@A` at RVA 0x009FE118.
Use a class with the same public single pointer in the consumer. This
adds no global, alias, pin, ledger row, layout offset or compiler setting.
The other weather consumers already use the class tag.

Target evidence: the two DIR32 operands at offsets 1 and 95 in the
189-byte row at 0x00094652 both read retail VA 0x00DFE118. Both emitted
addends are zero. The entire emitted body and extent are unchanged;
only these two relocation symbol names change. Provider object and
receipt hashes are unchanged. Before/after JSON records the complete
body, relocations, object/receipt hashes and census identity.

The unknown transition method identity is preserved. Weather enabled
and duration offsets and the private receiver view are existing claims,
not newly established by this repair. Snow.cpp remains the data owner.

## Acceptance

Both files and the consumer RVA were claimed. Commands:

```
./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnowStateTransition.cpp Code/GameEngine/Source/GameClient/Snow.cpp
python3 tools/link_check.py --prepare-current --paths-from build/weather-tag-link-20261013/sources.txt
python3 tools/link_check.py --paths-from build/weather-tag-link-20261013/sources.txt
```

The bounded before/after preparation and final byte gate pass 10/10
function rows and the owner's matched data row. Both explicit objects
have self-strict current reusable dependency receipts. No verified
closed link closure or actual linker placement was measured.

Against the same supplied index, the legacy current-object preview
removes exactly the struct-tag weather unresolved finding: the consumer
has 2 -> 1 blockers, the provider 7 -> 7, total 9 -> 8 with no additions.
Both previews exit 1, 0/2 sources clean, LINKED 0 -> 0 bytes. This is
verified dependency repair with zero authored C++ coverage increase,
not a closed-strict linked-byte gain. comparison.json checks these facts.

Other checks pass: find_declared_unmatched on both files; class_gate;
converged data check (8 addresses, no second names or unjudged rows);
shadow data check (zero findings); check_csv (87977 functions, 17165
symbols, 330 data rows); git diff --check. Consumer placement rescan
finds zero incidental bodies or pins.

## Donor review and handoff

BFME1 repair 0835ab92bef30e3303e729a0ce09cf591368d0cd (owned pool
extern respelling) was reviewed, including its verification account.
Its ownership principle applies; its Apt layouts and symbols do not.
BFME1 StringBase ownership repairs 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
and d2e21369067f2f2c762c1c7ec2792c75f1ecf53d were also reviewed as leads.
This fix is established independently by BFME2 relocations and data row.

The consumer still needs rva00093B5B, the complete 360-byte method whose
unchanged bank is blocked on null-path layout and override walk ordering.
No retry was made. Snow.cpp still needs targetSlot15 through targetSlot21.
Their complete local findings are in after-link.txt. Ranked literal
concat/global leads were already repaired, unchanged deferred, or lacked
matched-body applicability; those unchanged failures were not retried.

Official BFME1 master was fetched to e1382cda45c4e30d5cbbb142d18a824570017ca9.
The clean verified pointer cee35b7d8ca077d7255f1c39cb69e9fd9627aa85
was preserved. The comparative freshness baseline ./build.sh waited on
the shared full-compiler lock with no compiler child or output and was
terminated before compilation. The update claim was released, and no
success stamp or pointer update was written. Full comparative freshness
verification remains outstanding. No full link cycle, census, nightly
or boot runner ran.
