"""repair_queue: gate-debt and link-cycle repairs carry their check and a machine pass
test; new matches are told which unit they belong in (never a fresh one-function file)."""
import importlib
import os
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def load(tmp_path, layout, ledger, files=()):
    rev = tmp_path / ("targets/game/reverse" if layout == "bfme1" else "reverse")
    rev.mkdir(parents=True)
    src = "game" if layout == "bfme1" else "Code"
    (rev / "functions.csv").write_text(HEADER + "".join(
        f"{n},,0x{r:08X},{s},{src}/{f},matched,\n" for n, r, s, f in ledger), newline="\n")
    for rel, text in files:
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, newline="\n")
    os.environ["REPAIR_ROOT"] = str(tmp_path)
    try:
        import repair_queue
        return importlib.reload(repair_queue), rev, src
    finally:
        del os.environ["REPAIR_ROOT"]


LEDGER = [("?a@Loco@@QAEXXZ", 0x1000, 0x40, "GameEngine/Loco.cpp"),
          ("?b@Loco@@QAEXXZ", 0x1080, 0x40, "GameEngine/Loco.cpp"),
          ("?c@Body@@QAEXXZ", 0x2000, 0x20, "GameEngine/Body.cpp"),
          ("?d_00003000@@YAXXZ", 0x3000, 0x8, "GameEngine/Rva00003000Noop.cpp"),
          ("?g@@YAXXZ", 0x3100, 0x8, "gen_small/uw.cpp")]


@pytest.mark.parametrize("layout", ["bfme1", "bfme2"])
def test_dest_prefers_the_unit_around_the_address(tmp_path, layout):
    rq, _, src = load(tmp_path, layout, LEDGER)
    assert rq.dest_tu(0x1040)["dest"] == f"{src}/GameEngine/Loco.cpp"            # between two Loco rows
    assert "between two rows" in rq.dest_tu(0x1040)["basis"]
    assert rq.dest_tu(0x1F00)["dest"] == f"{src}/GameEngine/Body.cpp"            # nearest, 0x100 away
    got = rq.dest_tu(0x3010)                                                     # only an address-named file
    assert got["dest"] == f"{src}/GameEngine/Body.cpp"                           # and a generated one nearby
    got = rq.dest_tu(0x40000)
    assert got["dest"] is None and "never a new one-function file" in got["basis"]


def test_dest_takes_ea_file_evidence_first(tmp_path):
    rq, rev, src = load(tmp_path, "bfme1", LEDGER, [
        ("game/GameEngine/Source/Snapshot.cpp", "//\n"),
        ("targets/game/reverse/ea_evidence.csv",
         "rva,kind,value,route,basis\n0x00001040,file,GameEngine/Source/Snapshot.cpp,zh,\n")])
    got = rq.dest_tu(0x1040)
    assert got == {"dest": "game/GameEngine/Source/Snapshot.cpp", "basis": "EA source-file evidence (zh)"}


def test_dest_routes_to_the_approved_tu_before_neighbouring_files(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         "0x00001000,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00001040,64,code-unledgered,Code/GameEngine/Locomotor.cpp,approved,C,,\n"
         "0x00001080,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00002000,32,code,Code/GameEngine/Body.cpp,proposed,N,,Code/GameEngine/Body.cpp\n")])
    got = rq.dest_tu(0x1040)                                                     # an unconverted function's row
    assert got["dest"] == "Code/GameEngine/Locomotor.cpp"
    assert got["basis"] == "approved TU in tu_map.csv (by C; the file does not exist yet: create it)"
    assert rq.dest_tu(0x1060)["dest"] == "Code/GameEngine/Locomotor.cpp"         # no row: inside 0x1040's body
    got = rq.dest_tu(0x1F00)                                                     # proposed only: neighbours
    assert got["dest"] == "Code/GameEngine/Body.cpp" and "nearest neighbour" in got["basis"]
    assert got["basis"].startswith("neighbour heuristic, no usable approved TU")


TURRET = [("?a@StateMachine@@QAEXXZ", 0x1000, 16, "GameEngine/Source/Common/StateMachineA.cpp"),
          ("?x@TurretAI@@QAEXXZ", 0x1040, 16, "GameEngine/Source/GameLogic/AI/TurretAI.cpp"),
          ("?b@StateMachine@@QAEXXZ", 0x1080, 16, "GameEngine/Source/Common/StateMachineB.cpp"),
          ("?rva000010C0@Rva000010C0@@QAEXXZ", 0x10C0, 16, "GameEngine/Source/Common/Rva000010C0.cpp"),
          ("?y@TurretAI@@QAEXXZ", 0x1100, 16, "GameEngine/Source/GameLogic/AI/TurretAIY.cpp")]
ZH = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/"
TURRET_AI = "Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp"
STATE_MACHINE = "Code/GameEngine/Source/Common/StateMachine.cpp"


def test_dest_never_routes_an_f_turretai_row_to_a_merged_statemachine_tu(tmp_path):
    # Retail interleaves StateMachine.cpp and TurretAI.cpp, and 0x10C0 pushes TurretAI.cpp's
    # __FILE__. The old cluster union renamed every TurretAI row StateMachine.cpp, approved
    # them, and dest said "create StateMachine.cpp" while TurretAI.cpp existed.
    rq, rev, _ = load(tmp_path, "bfme2", TURRET, [
        (TURRET_AI, "//\n"),
        (ZH + "Common/StateMachine.cpp", "void StateMachine::a()\n{\n}\nvoid StateMachine::b()\n{\n}\n"),
        (ZH + "GameLogic/AI/TurretAI.cpp", "void TurretAI::x()\n{\n}\nvoid TurretAI::y()\n{\n}\n"),
        ("reverse/string_xrefs.tsv", "C:\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\TurretAI.cpp\t0x10C4\n")])
    import tu_map
    (rev / "tu_map.csv").write_text(tu_map.render(tu_map.build(tu_map.Layout(tmp_path))), newline="\n")
    got = rq.dest_tu(0x10C0)
    assert got["dest"] == TURRET_AI and got["basis"].startswith("retail __FILE__ string at this address")
    for rva in (0x1040, 0x1048, 0x10C0, 0x10C8, 0x1100):
        assert rq.dest_tu(rva)["dest"] != STATE_MACHINE, hex(rva)


def test_dest_distrusts_a_stale_approval_its_own_anchors_contradict(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        (TURRET_AI, "//\n"),
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         f"0x00001000,64,code,{STATE_MACHINE},approved,Z,Z={STATE_MACHINE},\n"
         f"0x00001040,64,code,{STATE_MACHINE},approved,N,F={TURRET_AI},\n"          # old rules' mislabel
         f"0x00001080,64,code-unledgered,{STATE_MACHINE},approved,C,C=0x00001040..0x000010C0,\n"
         f"0x000010C0,64,code,{STATE_MACHINE},approved,Z,Z={STATE_MACHINE},\n")])
    got = rq.dest_tu(0x1040)                                       # its own __FILE__ string wins
    assert got["dest"] == TURRET_AI and f"contradicted by 0x00001040 F={TURRET_AI}" in got["basis"]
    got = rq.dest_tu(0x1080)                                       # C resting on that row: not trusted either
    assert got["dest"] != STATE_MACHINE and got["basis"].startswith("neighbour heuristic")
    got = rq.dest_tu(0x1000)                                       # an uncontested approval still routes
    assert got["dest"] == STATE_MACHINE and "create it" in got["basis"]


def test_dest_refuses_padding(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/tu_map.csv",
         "rva,size,kind,tu,confidence,by,evidence,source\n"
         "0x00001000,60,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n"
         "0x00001080,64,code,Code/GameEngine/Locomotor.cpp,approved,Z,,Code/GameEngine/Loco.cpp\n")])
    import tu_map

    class Image:
        def read(self, rva, n):
            return bytes(0xCC if 0x103C <= a < 0x1040 else 0x55 for a in range(rva, rva + n))
    rq.tu_routes.cache_clear()
    m = tu_map.load(tmp_path)
    rq.tu_routes = lambda: (tu_map, m, tu_map.code_index(m, Image()))
    assert rq.dest_tu(0x103C) == {"dest": None, "basis": "retail padding (0xCC) inside no known body: "
                                                         "no function starts here"}
    got = rq.dest_tu(0x1040)                                       # where the next body starts
    assert got["dest"] == "Code/GameEngine/Locomotor.cpp" and got["basis"].startswith("approved TU")


def test_bfme2_gate_debt_items_and_pass_test(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "# header\ntail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n")])
    items = rq.repair_items()
    assert [(i["check"], i["source"], i["size"]) for i in items] == [
        ("tail", "Code/GameEngine/Loco.cpp", 0x40), ("strnul", "Code/GameEngine/Body.cpp", 0x20)]
    assert "pass-test 'tail 0x00001000 ?a@Loco@@QAEXXZ'" in items[0]["pass_test"]
    ok, _ = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "raise SystemExit(1)"])
    assert not ok and "tail 0x00001000" in (rev / "gate_baseline.txt").read_text()     # restored
    ok, message = rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ", build_cmd=[sys.executable, "-c", "pass"])
    assert ok and "tail 0x00001000" not in (rev / "gate_baseline.txt").read_text()
    assert "strnul 0x00002000" in (rev / "gate_baseline.txt").read_text()
    assert rq.pass_test("tail 0x00001000 ?a@Loco@@QAEXXZ")[0] is False                  # already gone


def test_bfme1_body_guard_items(tmp_path):
    rq, rev, _ = load(tmp_path, "bfme1", LEDGER, [
        ("targets/game/reverse/body_guard_baseline.csv",
         "check,target_rva,name,detail\nltable,0x00001080,?b@Loco@@QAEXXZ,+12 $L9 wants 0x1 retail 0x2\n"
         "dir32,0x00401942,?g_00401942@@YAXXZ,\"nothing owns 0x00401942, give it a data row\"\n"),
        ("targets/game/reverse/full_gate_baseline.txt", "# full-gate red rows\n")])
    items = rq.repair_items()
    assert items[0]["check"] == "ltable" and items[0]["source"] == "game/GameEngine/Loco.cpp"
    assert items[0]["why"].startswith("+12 $L9")
    assert items[1]["check"] == "dir32" and items[1]["source"].startswith("(git grep")


def test_link_items_serve_placed_unwired_rows_first(tmp_path):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    status = tmp_path / "link_status.csv"
    status.write_text(
        "name,kind,source,retail_rva,size,linked_rva,placed,placement_reason,self_strict,closed_strict,"
        "closed_strict_pilot_rule,pinned_strict,byte_equal,hardcoded,failure_count,failures\n"
        "?ok@@YAXXZ,real,Code/a.cpp,0x00001000,64,0x00001000,1,,1,1,1,1,1,0,0,\n"
        "?far@@YAXXZ,real,Code/a.cpp,0x00002000,500,0x007BBD80,0,retail start violates section alignment,1,1,1,1,0,0,0,\n"
        "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n"
        "?gen@@YAXXZ,gen-funclet,Code/gen_small/u.cpp,0x00004000,9,,0,not COMDAT,0,0,0,0,0,0,0,\n", newline="\n")
    items, note = rq.link_items(status)
    assert [(i["function"], i["why"]) for i in items] == [
        ("?wire@@YAXXZ", "data-back:g_x"), ("?far@@YAXXZ", "retail start violates section alignment")]
    assert "2 row(s)" in note


# ---- link tier sources: a local link cycle (build product) first, else the committed census

CYCLE_STATUS = (
    "name,kind,source,retail_rva,size,linked_rva,placed,placement_reason,self_strict,closed_strict,"
    "closed_strict_pilot_rule,pinned_strict,byte_equal,hardcoded,failure_count,failures\n"
    "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n")
CENSUS_STATUS = (
    "source,linked,unresolved,duplicates,comdat_losers,addresses,wrong_selected\n"
    "Code/GameEngine/Loco.cpp,no,2,0,1,0,0\n"
    "Code/GameEngine/Body.cpp,no,1,0,0,0,0\n"
    "Code/GameEngine/Rva00003000Noop.cpp,yes,0,0,0,0,0\n")
CENSUS_HISTORY = "date,commit,objects\n2026-09-29 11:03,c4d3910546,9016\n2026-10-07 21:52,086d0a7aaa,19715\n"
CENSUS_FILES = [("reverse/link_status.csv", CENSUS_STATUS), ("reverse/link_census_history.csv", CENSUS_HISTORY)]
CENSUS_TIME = 1791409920                     # 2026-10-07 21:52 UTC, the history row's date


def _cycle(tmp_path, when, commit=None):
    out = tmp_path / "build/link_cycle"
    out.mkdir(parents=True)
    (out / "link_status.csv").write_text(CYCLE_STATUS, newline="\n")
    if commit:
        (out / "receipt.json").write_text('{"commit": "%s", "dirty": false}' % commit)
    os.utime(out / "link_status.csv", (when, when))


def test_link_tier_prefers_a_newer_local_link_cycle(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    _cycle(tmp_path, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, CENSUS_FILES)
    items, note = rq.link_items()
    assert [i["function"] for i in items] == ["?wire@@YAXXZ"]
    assert "local link cycle" in note and "commit f00dfeedbe" in note
    assert rq.main(["link"]) == 0 and "local link cycle" in capsys.readouterr().out


def test_link_tier_falls_back_to_the_committed_census(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER, CENSUS_FILES)
    items, note = rq.link_items()                                        # no local cycle at all
    assert [(i["source"], i["target_rva"], i["size"]) for i in items] == [
        ("Code/GameEngine/Body.cpp", "0x00002000", 0x20),                 # one blocker: nearest to linking
        ("Code/GameEngine/Loco.cpp", "0x00001000", 0x80)]                 # both Loco rows credited
    assert items[1]["why"] == "unit does not link (2 matched row(s)): unresolved 2, comdat_losers 1"
    assert "link_check.py Code/GameEngine/Body.cpp" in items[0]["pass_test"]
    assert "committed link census reverse/link_status.csv" in note and "086d0a7aaa" in note
    assert rq.main(["link"]) == 0 and "measured at commit 086d0a7aaa" in capsys.readouterr().out
    _cycle(tmp_path, CENSUS_TIME - 3600)                                  # a local cycle older than the census
    items, note = rq.link_items()
    assert len(items) == 2 and "not newer" in note and "commit unknown" in note


def test_link_tier_with_no_status_says_so_and_fails(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    items, note = rq.link_items()
    assert items == [] and "no link status" in note
    assert rq.main(["link"]) == 1
    err = capsys.readouterr().err
    assert "run tools/link_cycle.py" in err and "reverse/link_status.csv" in err


def test_next_work_serves_repairs_before_new_matches():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair)[0] == "gate-debt repair"
    assert next_work.selected_queue(None, [], [], [], [], named, repair=[])[1] == named
    assert next_work.selected_queue("named", [], [], [], [], named, repair=repair)[1] == named
    assert next_work.selected_queue("repair", [], [], [], [], named, repair=repair)[1] == repair


def test_a_removed_debt_line_is_reverified(tmp_path):
    import subprocess
    rq, rev, _ = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\nstrnul 0x00002000 ?c@Body@@QAEXXZ\n"),
        ("Code/GameEngine/Loco.cpp", "//\n"), ("Code/GameEngine/Body.cpp", "//\n")])

    def git(*args):
        return subprocess.run(["git", "-C", str(tmp_path), *args], capture_output=True, text=True, check=True)
    git("init", "-q")
    git("add", ".")
    git("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    fail, ok = [sys.executable, "-c", "raise SystemExit(1)"], [sys.executable, "-c", "pass"]
    assert rq.verify_removed(fail) == []                                   # nothing removed
    (rev / "gate_baseline.txt").write_text("strnul 0x00002000 ?c@Body@@QAEXXZ\n", newline="\n")
    git("add", "reverse/gate_baseline.txt")
    got = rq.verify_removed(fail)                                          # credited without a fix
    assert len(got) == 1 and "Code/GameEngine/Loco.cpp" in got[0]
    assert rq.verify_removed(ok) == []                                     # the row really passes
    (tmp_path / "Code/GameEngine/Loco.cpp").write_text("// fixed\n")
    git("add", "Code/GameEngine/Loco.cpp")
    assert rq.verify_removed(fail) == []                                   # staged: the hook builds it


def test_repairs_are_capped_to_one_pick_in_n(tmp_path, monkeypatch):
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    monkeypatch.delenv("BFME_REPAIR_EVERY", raising=False)
    turns = [rq.repair_turn(owner="seat-a") for _ in range(9)]
    assert sum(turns) == 3 and turns[:3].count(True) == 1                 # default: 1 in 3, rotated
    assert sum(rq.repair_turn(4, owner="seat-b") for _ in range(8)) == 2
    assert all(rq.repair_turn(1, owner="x") for _ in range(3))
    assert not any(rq.repair_turn(0, owner="x") for _ in range(3))
    monkeypatch.setenv("BFME_REPAIR_EVERY", "1")
    assert rq.repair_turn(owner="seat-c")


def test_off_turn_picks_skip_repairs_unless_nothing_else():
    import next_work
    repair = [{"function": "r", "target_rva": "0x1", "size": 4}]
    named = [{"function": "n", "target_rva": "0x2", "size": 4}]
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=False)[1] == named
    assert next_work.selected_queue(None, [], [], [], [], [], repair=repair, repair_turn=False)[1] == repair
    assert next_work.selected_queue(None, [], [], [], [], named, repair=repair, repair_turn=True)[1] == repair


def test_tier_c_and_diffexec_findings_feed_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [
        ("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n"),
        ("reverse/match_tiers.csv", "target_rva,target_size,name,source,tier,reasons\n"
         "0x00001000,64,?a@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,C,gate:tail\n"
         "0x00002000,32,?c@Body@@QAEXXZ,Code/GameEngine/Body.cpp,C,identity:wrong\n"
         "0x00001080,64,?b@Loco@@QAEXXZ,Code/GameEngine/Loco.cpp,A,\n")])
    dx = tmp_path / "results.jsonl"
    dx.write_text('{"name":"?d@@YAXXZ","rva":"0x00004000","size":9,"source":"Code/d.cpp","verdict":"binding",'
                  '"reason":"objects: call #0: retail rva:0x1 rebuilt rva:0x2"}\n'
                  '{"name":"?e@@YAXXZ","rva":"0x00005000","size":9,"source":"Code/e.cpp","verdict":"binding",'
                  '"reason":"objects: call #0 (twin bodies)"}\n'
                  '{"name":"?f@@YAXXZ","rva":"0x00006000","size":9,"source":"Code/f.cpp","verdict":"none"}\n')
    rq.DIFFEXEC = str(dx)
    items = rq.all_repair_items()
    assert [(i["check"], i["target_rva"]) for i in items] == [
        ("tail", "0x00001000"), ("tier-C", "0x00002000"), ("diffexec-binding", "0x00004000")]
    assert "diffexec.py --row 0x00004000" in items[2]["pass_test"]


def test_boot_smoke_bisection_feeds_the_repair_queue(tmp_path):
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n")])
    bq = tmp_path / "boot_queue.json"
    bq.write_text('{"tool": "boot_smoke", "items": [{"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", '
                  '"source": "Code/GameEngine/Loco.cpp", "size": 64, "outcome": "crash-at-?b@Loco@@QAEXXZ", '
                  '"why": "boot smoke crash with this row overlaid alone"}, {"target_rva": "0x00001000", '
                  '"name": "?a@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64, "why": "dup"}]}')
    rq.BOOT_QUEUE = str(bq)
    items = rq.all_repair_items()
    assert [(i["check"], i["target_rva"]) for i in items] == [("tail", "0x00001000"), ("boot-crash", "0x00001080")]
    assert "boot_smoke.py --game-dir SANDBOX --overlay rva:0x00001080" in items[1]["pass_test"]
    rq.BOOT_QUEUE = str(tmp_path / "missing.json")
    assert rq.boot_items() == []


def test_game_smoke_desync_and_static_findings_feed_the_repair_queue(tmp_path):
    import json
    rq, rev, src = load(tmp_path, "bfme2", LEDGER, [("reverse/gate_baseline.txt", "tail 0x00001000 ?a@Loco@@QAEXXZ\n")])
    (tmp_path / "build" / "game").mkdir(parents=True)
    (tmp_path / "build" / "boot").mkdir(parents=True)
    # the default paths: what game_smoke.py bisect and boot_relayout.py findings write
    desync = {"tool": "game_smoke", "items": [
        {"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64,
         "outcome": "desync", "check": "desync", "why": "game_smoke determinism desync with this row alone",
         "pass_test": "python3 tools/game_smoke.py determinism --image one"}]}
    static = {"tool": "boot_relayout findings", "items": [
        {"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp", "size": 64,
         "check": "inline-data", "why": "dup of the desync row", "pass_test": "x"},
        {"target_rva": "0x00002000", "name": "?c@Body@@QAEXXZ", "source": "Code/GameEngine/Body.cpp", "size": 32,
         "check": "truncated-table", "why": "its object defines ??_7Body@@6B@ as 4 byte(s)",
         "pass_test": "python3 tools/boot_relayout.py findings --overlay rva:0x00002000 --only truncated-table"},
        {"target_rva": "0x00003000", "name": "?d_00003000@@YAXXZ", "source": "Code/GameEngine/Rva00003000Noop.cpp",
         "size": 8, "check": "inline-data", "why": "reads retail .text past its extent"}]}
    boot = {"tool": "boot_smoke", "items": [
        {"target_rva": "0x00003100", "name": "?g@@YAXXZ", "source": "Code/gen_small/uw.cpp", "size": 8,
         "outcome": "crash-at-x", "why": "boot smoke crash"}]}
    (tmp_path / "build/game/desync_queue.json").write_text(json.dumps(desync))
    (tmp_path / "build/boot/static_queue.json").write_text(json.dumps(static))
    (tmp_path / "build/boot/boot_queue.json").write_text(json.dumps(boot))
    items = rq.all_repair_items()
    # static findings come after run failures, whatever their size; a row once (the desync wins)
    assert [(i["check"], i["target_rva"]) for i in items] == [
        ("tail", "0x00001000"), ("desync", "0x00001080"), ("boot-crash", "0x00003100"),
        ("truncated-table", "0x00002000"), ("inline-data", "0x00003000")]
    assert items[1]["pass_test"].startswith("python3 tools/game_smoke.py determinism")
    assert "--only truncated-table" in items[3]["pass_test"]
    assert "boot_smoke.py --game-dir SANDBOX --overlay rva:0x00003100" in items[2]["pass_test"]
    assert items[1]["queue"].endswith("desync_queue.json")
    # one path: that queue alone
    assert [i["check"] for i in rq.boot_items(tmp_path / "build/game/desync_queue.json")] == ["desync"]


def test_game_smoke_queue_items_round_trip(tmp_path):
    """What game_smoke.desync_items writes is what repair_queue serves."""
    import json
    pytest.importorskip("capstone")
    try:
        import game_smoke
    except (ImportError, SystemExit) as e:
        pytest.skip(f"game_smoke not importable: {e}")
    rq, rev, src = load(tmp_path, "bfme2", LEDGER)
    rows = [{"target_rva": "0x00001080", "name": "?b@Loco@@QAEXXZ", "source": "Code/GameEngine/Loco.cpp",
             "target_size": "64"}]
    path = tmp_path / "desync_queue.json"
    path.write_text(json.dumps({"tool": "game_smoke", "items": game_smoke.desync_items(rows, "desync", "--overlay closed --relayout")}))
    rq.DESYNC_QUEUE = str(path)
    (item,) = rq.boot_items()
    assert (item["check"], item["function"], item["size"]) == ("desync", "?b@Loco@@QAEXXZ", 64)
    assert "game_smoke.py determinism --image one" in item["pass_test"]


# ---- link-cycle bundles (tools/cycle_artifacts.py) and gzip status files

RICH_STATUS = (CYCLE_STATUS.splitlines(True)[0] +
               "?ok@@YAXXZ,real,Code/a.cpp,0x00001000,64,0x00001000,1,,1,1,1,1,1,0,0,\n"
               "?far@@YAXXZ,real,Code/a.cpp,0x00002000,500,0x007BBD80,0,retail start violates section alignment,"
               "1,1,1,1,0,0,0,\n"
               "?wire@@YAXXZ,real,Code/b.cpp,0x00003000,40,0x00003000,1,,0,0,0,0,0,0,1,data-back:g_x\n"
               "?big@@YAXXZ,real,Code/c.cpp,0x00005000,90,0x00005000,1,,0,0,0,0,0,0,2,data-fwd:g_y;eh\n"
               "?gen@@YAXXZ,gen-funclet,Code/gen_small/u.cpp,0x00004000,9,,0,not COMDAT,0,0,0,0,0,0,0,\n")
GOLDEN = {  # tools/repair_queue.py at 9897d8f693 (before --bundle), on these fixtures
    'cycle': (0,
        '1 row(s) from the local link cycle <root>/build/link_cycle/link_status.csv (commit f00dfeedbe, written <when>)\n'
        '      40B  0x00003000 ?wire@@YAXXZ\n'
        '         Code/b.cpp: data-back:g_x\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n',
        ''),
    'census': (0,
        '2 unit(s) that do not link, from the committed link census reverse/link_status.csv (measured at commit '
        '086d0a7aaa, 2026-10-07 21:52 UTC)\n'
        '      32B  0x00002000 ?c@Body@@QAEXXZ\n'
        '         Code/GameEngine/Body.cpp: unit does not link (1 matched row(s)): unresolved 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Body.cpp: LINKS (the next census: linked=yes)\n'
        '     128B  0x00001000 ?a@Loco@@QAEXXZ\n'
        '         Code/GameEngine/Loco.cpp: unit does not link (2 matched row(s)): unresolved 2, comdat_losers 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Loco.cpp: LINKS (the next census: linked=yes)\n',
        ''),
    'census_limit': (0,
        '2 unit(s) that do not link, from the committed link census reverse/link_status.csv (measured at commit '
        '086d0a7aaa, 2026-10-07 21:52 UTC)\n'
        '      32B  0x00002000 ?c@Body@@QAEXXZ\n'
        '         Code/GameEngine/Body.cpp: unit does not link (1 matched row(s)): unresolved 1\n'
        '         pass test: python3 tools/link_check.py Code/GameEngine/Body.cpp: LINKS (the next census: linked=yes)\n',
        ''),
    'named': (0,
        '3 row(s) from the local link cycle <root>/s/link_status.csv (commit unknown (no receipt.json), written <when>)\n'
        '      90B  0x00005000 ?big@@YAXXZ\n'
        '         Code/c.cpp: data-fwd:g_y;eh\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n'
        '      40B  0x00003000 ?wire@@YAXXZ\n'
        '         Code/b.cpp: data-back:g_x\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n'
        '     500B  0x00002000 ?far@@YAXXZ\n'
        '         Code/a.cpp: retail start violates section alignment\n'
        '         pass test: python3 tools/link_cycle.py --measure-only: this row placed=1 self_strict=1\n',
        ''),
    'repair': (0,
        '2 baseline line(s), plus tier C / diffexec / boot, game and static queues\n'
        '      64B tail 0x00001000 ?a@Loco@@QAEXXZ\n'
        "         Code/GameEngine/Loco.cpp: compiled bytes past the row's extent differ from retail; fix the tail (or "
        "the extent)\n"
        "         pass test: python3 tools/repair_queue.py pass-test 'tail 0x00001000 ?a@Loco@@QAEXXZ'\n"
        '      32B ltable 0x00002000 ?c@Body@@QAEXXZ\n'
        '         Code/GameEngine/Body.cpp: a jump-table entry or same-section pointer lands on the wrong case; fix the '
        'case mapping\n'
        "         pass test: python3 tools/repair_queue.py pass-test 'ltable 0x00002000 ?c@Body@@QAEXXZ'\n",
        ''),
    'none': (1,
        '',
        'repair_queue: no link status: no link-cycle status at <root>/build/link_cycle/link_status.csv (run '
        'tools/link_cycle.py) and no committed census at reverse/link_status.csv with a '
        'reverse/link_census_history.csv row\n'),
}


def _main(rq, argv, capsys, root, when=None):
    code = rq.main(argv)
    got = capsys.readouterr()

    def norm(text):
        text = text.replace(str(root), "<root>").replace("\\", "/")
        return text.replace(when, "<when>") if when else text
    return code, norm(got.out), norm(got.err)


def test_link_and_repair_output_without_a_bundle_is_unchanged(tmp_path, monkeypatch, capsys):
    """The --bundle path changes nothing when it is not used: these fixtures give, byte for
    byte, the output the tool gave before it existed (GOLDEN)."""
    import time
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "a"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    assert _main(rq, ["link"], capsys, root, time.ctime(CENSUS_TIME + 3600)) == GOLDEN["cycle"]
    root = tmp_path / "b"
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    assert _main(rq, ["link"], capsys, root) == GOLDEN["census"]
    assert _main(rq, ["link", "--limit", "1"], capsys, root) == GOLDEN["census_limit"]
    root = tmp_path / "c"
    (root / "s").mkdir(parents=True)
    (root / "s/link_status.csv").write_text(RICH_STATUS, newline="\n")
    monkeypatch.setenv("REPAIR_LINK_STATUS", str(root / "s/link_status.csv"))
    rq, _, _ = load(root, "bfme2", LEDGER, [("reverse/gate_baseline.txt",
                                             "tail 0x00001000 ?a@Loco@@QAEXXZ\nltable 0x00002000 ?c@Body@@QAEXXZ\n")])
    monkeypatch.delenv("REPAIR_LINK_STATUS")
    when = time.ctime((root / "s/link_status.csv").stat().st_mtime)
    assert _main(rq, ["link", "--limit", "3"], capsys, root, when) == GOLDEN["named"]
    assert _main(rq, ["repair"], capsys, root) == GOLDEN["repair"]
    root = tmp_path / "d"
    rq, _, _ = load(root, "bfme2", LEDGER)
    assert _main(rq, ["link"], capsys, root) == GOLDEN["none"]


def test_link_items_read_a_gzip_status(tmp_path, monkeypatch, capsys):
    import gzip
    rq, _, _ = load(tmp_path, "bfme2", LEDGER)
    plain, packed = tmp_path / "link_status.csv", tmp_path / "link_status.csv.gz"
    plain.write_text(RICH_STATUS, newline="\n")
    with gzip.open(packed, "wb") as f:
        f.write(plain.read_bytes())
    items, _ = rq.link_items(plain)
    assert [i["function"] for i in items] == ["?big@@YAXXZ", "?wire@@YAXXZ", "?far@@YAXXZ"]
    assert rq.link_items(packed)[0] == items
    monkeypatch.setenv("REPAIR_LINK_STATUS", str(packed))
    rq, _, _ = load(tmp_path / "named", "bfme2", LEDGER)
    monkeypatch.delenv("REPAIR_LINK_STATUS")
    assert rq.main(["link"]) == 0 and "3 row(s) from the local link cycle" in capsys.readouterr().out


def _fixtures():
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import cycle_artifacts as ca
    import cycle_fixture as cf
    import test_cycle_artifacts as tc
    return ca, cf, tc


def _checkout(root):
    """ROOT measures link-cycle-2: the rules a served bundle must positively match."""
    (root / "tools").mkdir(parents=True, exist_ok=True)
    (root / "tools/link_cycle.py").write_text('SHADOW_RULES = ["data-fold-1"]\nCANON_RULES = "coff-canon-1"\n'
                                              'receipt = dict(tool="link_cycle", rules="link-cycle-2")\n')


def _bundle(tmp_path, date_utc=None, **kw):
    ca, cf, _ = _fixtures()
    out = tmp_path / "bundle"
    kw.setdefault("rank_files", True)
    cf.bundle(cf.make_run(tmp_path / "snaps", date_utc=date_utc or cf.recent(), **kw), out, "laptop/watchdog")
    return out


def _closure_bundle(tmp_path, **kw):
    _, cf, _ = _fixtures()
    kw.setdefault("closure", True)
    return _bundle(tmp_path, status=cf.CLOSURE_STATUS, **kw)


def _store(tmp_path, *bundles):
    """BUNDLES published on a fake GitHub (in the order given) and fetched into a store."""
    ca, _, tc = _fixtures()
    gh = tc.FakeGitHub()
    for n, b in enumerate(bundles):
        tc.released(gh, b, "2026-10-12T00:%02d:00Z" % n)
    store = tmp_path / "store"
    ca.fetch(tc.REPO, store, gh=gh)
    return store


def test_link_tier_reads_a_published_bundle_from_the_store(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _bundle(tmp_path))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census: unused
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store)]) == 0
    got = capsys.readouterr()
    head, *rows = got.out.splitlines()
    assert head.startswith("3 row(s) from link-cycle bundle link-cycle/275a758e4cbb-")
    assert "1.0 h ago; authenticated publication; ancestry unknown" in head and "STALE" not in head
    assert "census" not in got.out and "local link cycle" not in got.out and got.err == ""
    assert [r.split()[2] for r in rows if r.lstrip()[0].isdigit()] == ["?wire@@YAXXZ", "?nul@@YAXXZ", "?far@@YAXXZ"]


def test_a_stale_bundle_is_refused_with_its_reason_unless_allowed(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _bundle(tmp_path, "2026-01-01 00:00:00"))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store)]) == 4                  # stale: refused, nothing served
    got = capsys.readouterr()
    assert got.out == "" and "link-cycle bundle refused [reason=stale]:" in got.err and "--allow-stale" in got.err
    assert rq.main(["link", "--bundle", str(store), "--allow-stale"]) == 0
    got = capsys.readouterr()
    head = got.out.splitlines()[0]
    assert "measured 2026-01-01T00:00:00Z UTC" in head and ", STALE;" in head
    assert "repair_queue: STALE: measured" in got.err
    ca, _, _ = _fixtures()
    items, note, warnings = rq.bundle_link_items(store, now=ca.parse_utc("2026-01-01 01:00:00"))
    assert len(items) == 3 and warnings == [] and "1.0 h ago" in note and "STALE" not in note


def test_every_bundle_refusal_exits_with_its_own_reason_and_never_falls_back(tmp_path, monkeypatch, capsys):
    """An orchestrator routes on the exit code or on `[reason=...]`, not on prose."""
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census exist
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)

    def refused(argv, code, reason, text):
        assert rq.main(["link", *argv]) == code
        got = capsys.readouterr()
        assert got.out == "" and f"[reason={reason}]" in got.err and text in got.err, got.err
    fresh = _bundle(tmp_path / "fresh")
    # this checkout's rules cannot be read: compatibility is not established, whatever is allowed
    for extra in ([], ["--allow-stale"]):
        refused(["--bundle", str(fresh), "--local-unpublished", *extra], 5, "incompatible-rules", "RULES UNKNOWN")
    _checkout(root)
    refused(["--bundle", str(tmp_path / "missing")], 2, "unavailable", "no bundle at")
    refused(["--bundle", str(fresh)], 6, "unauthenticated", "has no fetch evidence")
    rules = _bundle(tmp_path / "rules", rules="link-cycle-3")
    for extra in ([], ["--allow-stale"], ["--closure"]):
        refused(["--bundle", str(rules), "--local-unpublished", *extra], 5, "incompatible-rules",
                "RULES MISMATCH: measured under link-cycle-3")
    stale = _bundle(tmp_path / "stale", "2026-01-01 00:00:00")
    refused(["--bundle", str(stale), "--local-unpublished"], 4, "stale", "STALE: measured")
    refused(["--bundle", str(fresh), "--local-unpublished", "--closure"], 7, "no-closure-report",
            "carries no closure report (published diagnostic-only")
    (fresh / "link_status.csv.gz").write_bytes(b"not the measured rows")
    refused(["--bundle", str(fresh), "--local-unpublished"], 1, "corrupt", "invalid [reason=corrupt]: member "
                                                                          "link_status.csv.gz")
    assert rq.main(["link", "--closure"]) == 1                             # no bundle: no local or census fallback
    got = capsys.readouterr()
    assert got.out == "" and "need --bundle STORE" in got.err


def test_a_local_unpublished_bundle_is_served_only_on_request_and_labelled(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    bundle = _bundle(tmp_path)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(bundle), "--local-unpublished"]) == 0
    got = capsys.readouterr()
    assert "; UNAUTHENTICATED LOCAL BUNDLE; " in got.out.splitlines()[0]
    assert "repair_queue: UNAUTHENTICATED LOCAL BUNDLE (--local-unpublished)" in got.err


# ---- closure roots from a bundle (tools/closure_report.py): link --closure

def test_link_closure_serves_roots_by_conditional_gain_with_their_limits(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _closure_bundle(tmp_path))
    root = tmp_path / "root"
    _cycle(root, CENSUS_TIME + 3600, commit="f00dfeedbeef0123")           # a local cycle and a census: unused
    rq, _, _ = load(root, "bfme2", LEDGER, CENSUS_FILES)
    _checkout(root)
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    got = capsys.readouterr()
    lines = got.out.splitlines()
    assert lines[0].startswith("2 closure root(s) with a gain from link-cycle bundle link-cycle/275a758e4cbb-")
    assert "authenticated publication" in lines[0]
    assert lines[1] == "  graph: measured graph, bound to the receipt"
    assert "credit 64 B" in lines[2] and "64 B fail their own checks" in lines[2]
    assert "46 B are self-strict but closure-blocked; closed-strict but not placed: 500 B" in lines[2]
    assert lines[3].startswith("  COVERAGE: single roots cover only 30 B of the 46 B closure bucket (65.2%); 16 B sit "
                               "behind two or more roots and 0 B behind one filler or unknown target")
    assert lines[3].endswith("1 of the 2 roots unblock only their own failing rows.")
    assert "CONDITIONAL single-address gain = credit(graph with every failed node at that retail address passing) " \
           "- credit(graph)" in lines[4]
    assert lines[5].startswith("  limits: conditional on the frozen graph") and "not a repair proof" in lines[5]
    assert "do not add them" in lines[5] and "never ranked" in lines[5] and "not its cause or its repair site" in lines[5]
    assert lines[6].split() == ["70B", "closure", "0x00003000", "?wire@@YAXXZ"]
    assert lines[7].strip().startswith("Code/b.cpp: beneficiaries 1 row(s) 30 B + own failing rows 1 / 40 B; 1 "
                                       "failed node(s) at this address; 2 failure(s) to clear: data-back:")
    assert "no longer lists root 0x00003000 and its rows are closed_strict=1" in lines[8]
    assert len(lines) == 9 and "census" not in got.out and "local link cycle" not in got.out
    items, notes, _ = rq.closure_items(store)
    assert [(i["target_rva"], i["size"]) for i in items] == [("0x00003000", 70), ("0x00004000", 24)]


def test_the_closure_queue_says_when_its_graph_is_a_replay(tmp_path, monkeypatch, capsys):
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    store = _store(tmp_path, _closure_bundle(tmp_path, closure="replay"))
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    assert capsys.readouterr().out.splitlines()[1] == (
        "  graph: replayed, graph not receipt-bound: the edges were rebuilt after the run, not written by its measure")


def test_the_closure_queue_keeps_its_last_bundle_when_a_newer_one_has_no_report(tmp_path, monkeypatch, capsys):
    """A measurement published without a closure report does not silently disable the queue:
    it serves the newest bundle that has one, and says which and why."""
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    ca, cf, _ = _fixtures()
    ready = _closure_bundle(tmp_path / "ready", date_utc=cf.recent(6), commit=cf.OTHER)
    bare = _bundle(tmp_path / "bare", cf.recent(1))
    store = _store(tmp_path, ready, bare)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    assert rq.main(["link", "--bundle", str(store), "--limit", "0"]) == 0
    assert "link-cycle bundle link-cycle/275a758e4cbb-" in capsys.readouterr().out      # the newest measurement
    assert rq.main(["link", "--closure", "--bundle", str(store), "--limit", "1"]) == 0
    got = capsys.readouterr()
    assert "link-cycle bundle link-cycle/31d8b0fddd01-" in got.out.splitlines()[0] and "6.0 h ago" in got.out
    assert "repair_queue: NOT THE NEWEST MEASUREMENT: serving link-cycle/31d8b0fddd01-" in got.err
    assert "was published without one (published diagnostic-only" in got.err
    lone = _store(tmp_path / "lone", bare)
    assert rq.main(["link", "--closure", "--bundle", str(lone)]) == 7
    got = capsys.readouterr()
    assert got.out == "" and "[reason=no-closure-report]" in got.err and "nothing else is served in its place" in got.err


def test_a_corrupted_closure_report_and_one_of_another_algorithm_are_refused(tmp_path, monkeypatch, capsys):
    import gzip
    import hashlib
    import json
    monkeypatch.delenv("REPAIR_LINK_STATUS", raising=False)
    root = tmp_path / "root"
    rq, _, _ = load(root, "bfme2", LEDGER)
    _checkout(root)
    corrupt = _closure_bundle(tmp_path / "corrupt")
    data = bytearray((corrupt / "closure_roots.json.gz").read_bytes())
    data[len(data) // 2] ^= 1
    (corrupt / "closure_roots.json.gz").write_bytes(bytes(data))
    assert rq.main(["link", "--closure", "--bundle", str(corrupt), "--local-unpublished"]) == 1
    got = capsys.readouterr()
    assert got.out == "" and "invalid [reason=corrupt]: member closure_roots.json.gz: sha256" in got.err
    bundle = _closure_bundle(tmp_path / "algo")
    path = bundle / "closure_roots.json.gz"
    doc = json.loads(gzip.decompress(path.read_bytes()))
    doc["algorithm"] = "affected-bytes/1"
    raw = json.dumps(doc).encode()
    path.write_bytes(gzip.compress(raw))
    manifest = json.loads((bundle / "manifest.json").read_text())
    manifest["members"][path.name].update(sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                                          size=path.stat().st_size,
                                          content_sha256=hashlib.sha256(raw).hexdigest(), content_size=len(raw))
    manifest["components"]["closure_report"]["algorithm"] = "affected-bytes/1"     # a self-consistent other ranking
    (bundle / "manifest.json").write_text(json.dumps(manifest))
    assert rq.main(["link", "--closure", "--bundle", str(bundle), "--local-unpublished"]) == 5
    got = capsys.readouterr()
    assert got.out == "" and "[reason=incompatible-rules]" in got.err and "algorithm 'affected-bytes/1'" in got.err
