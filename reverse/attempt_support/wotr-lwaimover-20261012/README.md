# lwaimover seat, 2026-10-12

Branch: `wotr/lwaimover`.
Worktree: `C:/Users/Jonathan/Desktop/reverse bfme 2/.claude/worktrees/wotr-lwaimover`.
Base: `564a159710`. No push; publication belongs to the orchestrator.
Model: `gpt-6.1-sol`.

## Verified local commits

- `1162393deb` — Recover the Living World help callback return ABI.
  `0x0059E098`, **41 new retail bytes**. The earlier integer-return bank was
  wrong: the native method returns the counted `RvaF6Ret` help handle by value.
  Its nontrivial lifetime naturally emits the return flag stack slot. No
  artificial volatile/unread local and no added callee pin.
- `092ae73f2d` — Recover the Living World army type tally provider.
  `0x0059D7C4`, **225 new retail bytes**, prerequisite of `0x0059DD3F`.
  Two stride-20 record vectors hold tree headers at record+4. The native
  helper accumulates their key/value pairs into eight output counts. A
  by-value inline player lookup closes the first six missing instruction bytes.

Total: **266 new matched bytes**. Both commits ran normal hooks. The final
`./build.sh` invocation passed **6/6 rows across five files**, including the
existing auto-resolve constructor, destructor, and DefendHomeTerritory;
see `final-byte-check.txt`. `check_csv` passed with 79,313 function rows.
The placement sweep of the two new units found zero additional bodies/pins.

## Lane map and verdicts

Names below that describe behavior are inferences from retail/WorldBuilder;
they are not recovered original method names.

- **0x0059BE1F, 497B:** partial, **0.93166**;
  `reverse/attempts/0x0059be1f.cpp`, complete **495B** candidate. Collection
  helper walks distance-indexed regions, classifies armies by owner relation,
  applies the difficulty/random filter to enemies, and deduplicates players.
  Native RET0x20. Original list/element/method spellings remain unknown.
- **0x002BC971, 843B:** partial, **0.7996**;
  `reverse/attempts/0x002bc971.cpp`. Existing SetUpAutoResolveBattle bank retained;
  96 isolated permutation trials over six minutes produced no improvement.
  Native RET0x18, six stack arguments; older `RET24` notation means decimal
  24 bytes. This bank still carries its earlier global-ownership/type caveats.
- **0x0059C15B, 1238B:** blocked on **0x0059BE1F, 0x002BC971**.
  WinTestBattle identity comes from the WB14FBC60 name and native call graph.
  The earlier four-provider verdict is stale: constructor **0x004FA3C9, 495B**
  and destructor **0x004FA2E2, 231B** were already matched before this seat,
  and both passed the fresh scoped gate. Every other distinct direct target
  has a matched row; see `wintest-provider-rows.json`.
- **0x0059C631, 779B:** blocked on **0x0059C15B**. Strategic region/objective
  scoring and movement candidate pass; complete WB14FCAD0 and native body read.
- **0x0059C93C, 1348B:** blocked on **0x0059C631, 0x0059C15B**. Main movement
  order pass calls DefendHomeTerritory, the strategic helper, and WinTestBattle.
  Complete WB14FAE80 and native body read. No parent reconstruction or pin was
  admitted while those substantive providers remain unrowed.
- **0x0059DD3F, 545B:** partial, **0.80941**;
  `reverse/attempts/0x0059dd3f.cpp`, complete **550B** candidate. Weighted
  eight-type deficits, optional region threat sorting, then recruitment/unit
  picker calls. Its missing 225B tally provider is now matched locally.
  This diagnostic compares the requested 545B window; the longer COFF body
  is explicitly not acceptable. Enum-vector spelling is a provider view,
  not a claim about the original region-ID enum.
- **0x0059DF60, 155B:** partial, **0.93421**;
  `reverse/attempts/0x0059df60.cpp`, complete **154B** candidate. UI audio
  callback, vtable C70F88 slot1; WB14D9B70. Updated existing bank.
- **0x0059DFFB, 148B:** partial, **0.91503**;
  `reverse/attempts/0x0059dffb.cpp`, complete **147B** candidate. Adjacent UI
  audio callback; WB14D9CB0. Direct adjacent reference fields replace the
  earlier illegal-union/C2622 attempt. Nine padding bytes follow this body.
- **0x0059E098, 41B:** matched locally, first commit above. Help callback;
  WB14D9DE0. Its old wrong-ABI bank was removed by add_match.
- **0x0059D7C4, 225B:** matched locally, second commit above. Additional
  prerequisite claimed during the 545B caller sweep.

The three UI bodies had earlier attempts despite the seat brief describing
this gap as never attempted. They are not army-mover methods.

## Hard walls and starting points

1. **Collection helper code generation.** The final reviewed 495B bank now
   reproduces the native 0x18 frame and conditional EBX save. The remaining
   difference includes the compiler hoisting the enemy army owner+0x54 load
   ahead of random/push calls; native loads it after the enemy push. Branch
   and scheduling differences remain. 1,455 bounded permutation trials over
   eight minutes improved 0.88712 to 0.93166, never exact. The final bank
   restores the source owner-load order after random/push; the experimental
   best is separate evidence, not a recovery. All real call names resolve.
2. **Battle setup frame/register/SSE shape.** Native frame0x5C versus bank0x60,
   player/output index register choices, iterator lifetime, and five SSE
   multiplication shapes remain. Four subsystem globals and the original
   member/record types still need the ownership proof described by the prior
   bank. No manual target map or new pin was admitted.
3. **Independent caller/audio shapes.** The 545B caller emits 550B with
   frame0x4C versus native0x48, a this spill, and sorting lifetime/register
   differences. The two audio callbacks share a narrower cause: compiler
   `add eax,0x10/0x14; cmp [eax],0` versus native `cmp [eax+offset],0` and a
   later address addition. Position forms, getters, pointer/word/range views,
   G5/G6/Op/Ob1/Ob2/Oi variants did not close it; O2 was worse.

Raw COFF listings retain symbolic relocation records separately. Relocated
diagnostic disassembly can contain misleading copied DIR32 values when the
instruction shape differs; use the raw listings and relocation JSON.
`59be1f-compiled-raw.txt` is the earlier 496B trial;
`59be1f-final-compiled-raw.txt` is the final reviewed 495B bank.

## Evidence and practical limits

The configured shared MCP endpoint `127.0.0.1:8000/mcp` refused connection.
A private Ghidra project inside this worktree was seeded from the committed
inventory and retail ranges, then accessed through GhidraSQL MCP at port18370.
Ghidra was used for decompilation and call graphs, not as byte-match proof.
The captured MCP envelope names retail game.dat SHA256
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
The temporary Q drive alias avoids Ghidra's refusal of `.claude` project paths.

**LINKED status is unconfirmed.** Ordinary link_check refuses both new sources
because their link positions are absent from census `2c46f084e1`.
Scoped strict receipt preparation passed; it explicitly does not establish
LINK closure or update the census/index/status. New-variant admission did not
refuse them. No link_cycle, nightly, boot-smoke, or publisher runner was started.

BFME1 donor pointer `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85` was initialized
in the isolated submodule. It contains no LivingWorldAIArmyMover or
LivingWorldAISupport source. The required lift lane ran (221 lifted bodies).
Official master was fetched at `69f906eb2122c0d83e0d23e65a87a75b5033ee84`;
the relevant LivingWorld directory, STLport/toolchain inputs, and lift tool
have no changes between those revisions. The pinned revision was preserved:
no full reference-update gate or last-check success was claimed. Any pointer
update belongs in the orchestrator's separately verified update batch.

All verdicts were appended through re_log. Partial/blocked claims were
released. Claims for the two verified local rows remain queued for publication
under `BFME_CLAIM_OWNER=wotr-lwaimover-20261012`. No nonmatching source remains
in Code, and the main checkout's working tree was not edited.
