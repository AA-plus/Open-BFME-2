"""closure_report: the conditional single-address gain is exactly what link_cycle's own
closure gives when a root's nodes are forced to pass; complete blocker sets are kept up to a
stated cap; fillers and unknown targets are never scored; the analysed graph is the one
link_cycle's measure wrote and its receipt names (equal verdicts do not prove equal edges),
or the report says it is a replay; link_cycle's graph emit reads and changes nothing."""
import copy
import gzip
import json
import random
import sys
import types
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import closure_report as cr  # noqa: E402
import cycle_artifacts as ca  # noqa: E402
import cycle_fixture as cf  # noqa: E402
import link_cycle as lc  # noqa: E402
import publish_cycle as pc  # noqa: E402


def U(n):
    return ("unit", n)


def row(node, rva, size, self_strict=True, placed=True, real=True):
    return {"node": node, "name": f"f{node[1]}_{rva:X}", "source": f"Code/{node[1]}.cpp", "rva": rva, "size": size,
            "real": real, "placed": placed, "self_strict": self_strict}


def describe(n):
    ident = ":".join(str(x) for x in n)
    return {"id": ident, "kind": n[0], "group": GROUPS.get(n, ident), "name": ident, "failures": [f"why-{ident}"]}


GROUPS = {}


def graph():
    """u1 fails alone; u2 and u3 wait only for u1; u4 waits for u1 and the failed datum d;
    u5 waits only for a filler; u6 reaches an unknown target; u7 is closed; u8 fails and
    also reaches the failed datum, so its own row is not gained by fixing u8."""
    d, fill, twin = ("datum", (9, 0x900, 4)), ("fill", 0x700), ("twin", 0x50, 0x100)
    ok = {U(1): False, U(2): True, U(3): True, U(4): True, U(5): True, U(6): True, U(7): True, U(8): False,
          d: False, twin: False}
    edges = {U(2): {U(1)}, U(3): {U(2)}, U(4): {U(1), d}, U(5): {fill}, U(6): {("eh", 0x33)}, U(8): {d},
             U(7): set(), U(1): {twin}}
    rows = [row(U(1), 0x100, 10, self_strict=False), row(U(2), 0x200, 20), row(U(3), 0x300, 30),
            row(U(4), 0x400, 40), row(U(5), 0x500, 50), row(U(6), 0x600, 60), row(U(7), 0x700, 70),
            row(U(8), 0x800, 80, self_strict=False), row(U(3), 0x300, 30, placed=False),
            row(U(7), 0x7F0, 8, placed=False), row(U(2), 0x200, 20, real=False)]
    return ok, edges, rows


def test_gain_is_beneficiaries_plus_own_rows_and_two_roots_score_for_neither():
    GROUPS.clear()
    GROUPS.update({U(1): "0x00000100", ("twin", 0x50, 0x100): "0x00000100"})    # one address, two failed nodes
    ok, edges, rows = graph()
    body, blockers = cr.analyze(ok, edges, rows, describe)
    s = body["summary"]
    assert s["credit_unique_bytes"] == 70
    by_root = {e["root"]: e for e in body["roots"]}
    one = by_root["0x00000100"]
    assert [n["id"] for n in one["nodes"]] == ["twin:80:256", "unit:1"]
    assert (one["beneficiary_rows"], one["beneficiary_bytes"]) == (2, 50)      # u2 and u3; u4 also needs the datum
    assert (one["direct_rows"], one["direct_bytes"]) == (1, 10)
    assert one["conditional_gain_bytes"] == 60 and one["scored"] is True
    assert (one["affected_rows"], one["affected_bytes"]) == (3, 90)            # u4 reaches it too: affected, not gained
    assert one["failures"] == ["why-twin:80:256", "why-unit:1"]
    assert set(by_root) == {"0x00000100"}                                      # u8 and the datum gain nothing alone
    assert [e["root"] for e in body["unscored"]] == ["leaf:eh:51", "leaf:fill:1792"]
    assert body["unscored"][1]["sole_blocked_bytes"] == 50 and body["unscored"][1]["scored"] is False
    assert s["buckets"] == {"closed-strict-unplaced": {"rows": 1, "unique_bytes": 8},
                            "closure-blocked": {"rows": 5, "unique_bytes": 200},
                            "failing": {"rows": 2, "unique_bytes": 90}}
    assert s["closure_blocked_reach"] == {"one scored root": {"rows": 2, "unique_bytes": 50},
                                          "one unscored leaf": {"rows": 2, "unique_bytes": 110},
                                          "two or more": {"rows": 1, "unique_bytes": 40}}
    assert s["closure_blocked_by_blocker_set_size"] == {"1": {"rows": 4, "unique_bytes": 160},
                                                        "2": {"rows": 1, "unique_bytes": 40}, "cap": cr.SET_CAP}
    assert s["roots_with_no_beneficiary"] == 0 and "sum_conditional_gain_bytes" not in s
    table = {r["name"]: r for r in blockers}
    assert table["f3_300"]["witness"] == "unit:3 > unit:2 > unit:1" and table["f3_300"]["roots"] == "0x00000100"
    # the COMPLETE blocker set of a row behind two roots is kept, not collapsed to "2+"
    assert (table["f4_400"]["reach"], table["f4_400"]["roots"], table["f4_400"]["scored"]) == (
        "2", "0x00000100;datum:(9, 2304, 4)", 1)
    assert (table["f5_500"]["reach"], table["f5_500"]["roots"], table["f5_500"]["scored"]) == (
        "1", "leaf:fill:1792", 0)
    assert table["f8_800"]["bucket"] == "failing" and table["f8_800"]["roots"] == "datum:(9, 2304, 4);unit:8"
    assert "f7_700" not in table                                               # credited rows are not blockers


def test_blocker_sets_are_complete_up_to_the_cap_and_marked_truncated_beyond_it():
    GROUPS.clear()
    bad = [U(n) for n in range(1, 9)]
    ok = dict.fromkeys(bad, False)
    ok.update({U(20): True, U(21): True, U(22): True})
    edges = {U(20): set(bad[:cr.SET_CAP]), U(21): set(bad[:cr.SET_CAP + 1]), U(22): {U(21), U(20)}}
    rows = [row(U(20), 0x2000, 8), row(U(21), 0x2100, 8), row(U(22), 0x2200, 8)]
    body, blockers = cr.analyze(ok, edges, rows, describe)
    table = {r["name"]: r for r in blockers}
    assert table["f20_2000"]["reach"] == str(cr.SET_CAP)
    assert table["f20_2000"]["roots"].split(";") == [f"unit:{n}" for n in range(1, cr.SET_CAP + 1)]
    for name in ("f21_2100", "f22_2200"):                                      # truncated: said so, never guessed
        assert (table[name]["reach"], table[name]["roots"], table[name]["scored"]) == (f">{cr.SET_CAP}", "", "")
    assert body["summary"]["closure_blocked_by_blocker_set_size"][f">{cr.SET_CAP}"] == {"rows": 2, "unique_bytes": 16}
    assert cr.blockers_csv(blockers).decode().splitlines()[0] == ",".join(cr.BLOCKER_COLUMNS)


def test_single_root_scores_omit_joint_gains_and_may_overlap():
    """Astra: two zero-gain roots can jointly unlock a row; two gains over overlapping bytes
    do not add. joint_gain scores a chosen set exactly; nothing here ranks sets."""
    GROUPS.clear()
    ok = {U(1): False, U(2): False, U(3): True}
    edges = {U(3): {U(1), U(2)}}
    rows = [row(U(3), 0x300, 100)]
    body, blockers = cr.analyze(ok, edges, rows, describe)
    assert body["roots"] == [] and blockers[0]["roots"] == "unit:1;unit:2"
    g = (ok, edges, rows, describe)
    assert cr.joint_gain(g, ["unit:1"]) == 0 == cr.joint_gain(g, ["unit:2"])
    assert cr.joint_gain(g, blockers[0]["roots"].split(";")) == 100
    ok = {U(1): False, U(2): False}
    rows = [row(U(1), 0x100, 16, self_strict=False), row(U(2), 0x108, 16, self_strict=False)]
    body, _ = cr.analyze(ok, {}, rows, describe)
    assert [e["conditional_gain_bytes"] for e in body["roots"]] == [16, 16]
    assert cr.joint_gain((ok, {}, rows, describe), ["unit:1", "unit:2"]) == 24
    assert "do not add them" in " ".join(cr.LIMITS)


def test_gain_subtracts_bytes_already_credited():
    GROUPS.clear()
    ok = {U(1): False, U(2): True, U(3): True}
    rows = [row(U(1), 0x100, 16, self_strict=False), row(U(2), 0x108, 16), row(U(3), 0x100, 12)]
    body, _ = cr.analyze(ok, {U(2): {U(1)}}, rows, describe)
    (e,) = body["roots"]
    assert (e["direct_bytes"], e["beneficiary_bytes"]) == (16, 16)
    assert e["conditional_gain_bytes"] == 12                                   # [0x100,0x118) less [0x100,0x10C)
    assert cr.forced_gain(ok, {U(2): {U(1)}}, rows, [U(1)], lc.greatest_closure) == 12


def test_every_gain_and_every_blocker_set_equals_link_cycles_closure():
    """600 random graphs (failed, unknown and filler nodes, shared addresses, overlapping
    rows): each gain equals link_cycle.greatest_closure run with the root's nodes passing;
    the closed set, the credit and this module's reference closure are link_cycle's; and each
    row's blocker set is exactly the blockers it reaches (or is marked beyond the cap)."""
    rng = random.Random(7)
    positive = sets = 0
    for _ in range(600):
        nodes = [(rng.choice(["unit"] * 6 + ["datum", "twin", "fill"]), i) for i in range(rng.randint(3, 30))]
        ok = {n: rng.random() < 0.7 for n in nodes if n[0] != "fill" and rng.random() < 0.95}
        edges = {n: {rng.choice(nodes) for _ in range(rng.randint(0, 3))} for n in nodes if n in ok}
        rows = []
        for n in nodes:
            if n[0] == "unit" and n in ok:
                for _ in range(rng.randint(1, 2)):
                    rows.append({"node": n, "name": f"r{len(rows)}", "source": "s", "rva": rng.randint(0, 60) * 4,
                                 "size": rng.randint(1, 12), "real": rng.random() < 0.9,
                                 "placed": rng.random() < 0.85, "self_strict": ok[n] or rng.random() < 0.5})

        def group(n):
            return "g%d" % (n[1] // 2)

        def desc(n):
            return {"id": "%s:%03d" % n, "kind": n[0], "group": group(n)}
        cap = rng.randint(1, 4)
        body, table = cr.analyze(ok, edges, rows, desc, cap=cap)
        closed = lc.greatest_closure(ok, edges)
        assert cr.closed_nodes(ok, edges) == closed == cr.reference_closure(ok, edges)
        assert body["summary"]["credit_unique_bytes"] == lc.unique_bytes(
            [(r["rva"], r["rva"] + r["size"]) for r in rows
             if r["real"] and r["placed"] and r["self_strict"] and r["node"] in closed])
        got = {e["root"]: e["conditional_gain_bytes"] for e in body["roots"]}
        groups = {}
        for n in ok:
            if cr.scorable(n, ok):
                groups.setdefault(group(n), []).append(n)
        assert set(got) <= set(groups)
        for g, members in groups.items():
            want = cr.forced_gain(ok, edges, rows, members, lc.greatest_closure)
            assert got.get(g, 0) == want
            positive += want > 0
        blockers = cr.blockers_of(ok, edges)
        by_name = {r["name"]: r for r in table}
        for r in rows:
            if r["name"] not in by_name:
                continue
            seen, work = {r["node"]}, [r["node"]]
            while work:
                for t in edges.get(work.pop(), ()):
                    if t not in seen:
                        seen.add(t)
                        work.append(t)
            reach = sorted({group(n) if cr.scorable(n, ok) else "leaf:" + desc(n)["id"] for n in seen & blockers})
            out = by_name[r["name"]]
            if len(reach) > cap:
                assert (out["reach"], out["roots"]) == (f">{cap}", "")
            else:
                assert (out["reach"], out["roots"]) == (str(len(reach)), ";".join(reach))
                sets += len(reach) > 1
    assert positive > 300 and sets > 300


# ---------------------------------------------------------------- the measured graph (Sol 3, Astra 5)

def test_equal_verdicts_do_not_prove_equal_edges_so_the_graph_is_bound_by_the_receipt(tmp_path):
    """Sol's counterexample: P reaches failed A; add an edge from P to failed B. Every
    placed / self-strict / closed flag and the credit are unchanged, and A's gain halves.
    The analysed graph must therefore be the file the receipt names."""
    A, B, P, C = [["?A@@YAXXZ", "real", "Code/a.cpp", "0x00001000", 20, "0x00001000", 1, "", 0, 0, 0, 0, 0, 0, 1, "eh"],
                  ["?B@@YAXXZ", "real", "Code/b.cpp", "0x00002000", 10, "0x00002000", 1, "", 0, 0, 0, 0, 0, 0, 1, "eh"],
                  ["?P@@YAXXZ", "real", "Code/p.cpp", "0x00003000", 10, "0x00003000", 1, "", 1, 0, 0, 1, 1, 0, 0, ""],
                  ["?C@@YAXXZ", "real", "Code/c.cpp", "0x00004000", 10, "0x00004000", 1, "", 1, 1, 1, 1, 1, 0, 0, ""]]
    status = [A, B, P, C]
    run = cf.make_run(tmp_path / "measured", status=status, closure="graph", edges={"?P@@YAXXZ": ["?A@@YAXXZ"]},
                      credit=10)
    roots, _, _ = cr.from_graph(run)
    doc = json.loads(roots)
    assert {e["root"]: e["conditional_gain_bytes"] for e in doc["roots"]} == {"0x00001000": 30, "0x00002000": 10}
    assert doc["graph"] == {"bound": True, "label": cr.BOUND,
                            "sha256": json.loads((run / "receipt.json").read_text())["closure_graph_sha256"]}
    assert doc["source"] == "graph" and doc["checks"]["link_status_rows_reproduced"] == 4
    # the drifted graph: same verdicts, same credit, another edge
    drifted = cf.graph_doc(status, {"?P@@YAXXZ": ["?A@@YAXXZ", "?B@@YAXXZ"]})
    g0, g1 = cr.load_graph(run / cr.GRAPH_FILE), cr.graph_from_doc(drifted)
    verdicts = [[(r["name"], r["placed"], r["self_strict"], r["node"] in cr.reference_closure(g[0], g[1]))
                 for r in g[2]] for g in (g0, g1)]
    assert verdicts[0] == verdicts[1]
    assert {e["root"]: e["conditional_gain_bytes"] for e in cr.analyze(*g1)[0]["roots"]} == {
        "0x00001000": 20, "0x00002000": 10}                                   # a different ranking
    lc.write_closure_graph(run / cr.GRAPH_FILE, drifted)                       # put it where the measured one was
    with pytest.raises(cr.ReportError, match="is not the receipt's closure_graph_sha256 .* not the graph that run "
                                             "measured"):
        cr.from_graph(run)
    assert cr.main(["graph", str(run), "--out", str(tmp_path / "out")]) == 1 and not (tmp_path / "out").exists()


def test_a_run_measured_before_the_graph_was_written_is_not_analysed_as_if_it_had_one(tmp_path):
    run = cf.make_run(tmp_path / "old", status=cf.CLOSURE_STATUS)
    with pytest.raises(cr.ReportError, match="names no closure_graph_sha256.*use `replay`.*replayed, graph not "
                                             "receipt-bound"):
        cr.from_graph(run)


def test_a_graph_whose_rows_are_not_the_runs_is_refused(tmp_path):
    """Sol's ledger-drift repro, in small: one row's size differs (15 -> 14). Credit and
    every verdict still agree; the complete row comparison does not."""
    run = cf.make_run(tmp_path / "r", status=cf.CLOSURE_STATUS, closure="graph")
    receipt = json.loads((run / "receipt.json").read_text())
    doc = cf.graph_doc(cf.CLOSURE_STATUS, cf.CLOSURE_EDGES)
    target = next(r for r in doc["rows"] if r[0] == "?wire@@YAXXZ")
    target[4] -= 1                                                             # 40 -> 39: not a credited row
    with pytest.raises(cr.ReportError, match="2 row record\\(s\\) differ from link_status.csv .*size"):
        cr.report(cr.graph_from_doc(doc), receipt, cr.status_rows(run / "link_status.csv"),
                  {"source": "replay", "graph": {"bound": False, "label": cr.REPLAYED, "sha256": "0" * 64},
                   "row_columns": cr.STATUS_COMPARED[:5] + ("placed", "self_strict", "closed_strict")})
    doc = cf.graph_doc(cf.CLOSURE_STATUS, {})                                  # and a graph crediting more
    with pytest.raises(cr.ReportError, match="the graph credits 110, the receipt 64"):
        cr.report(cr.graph_from_doc(doc), receipt, cr.status_rows(run / "link_status.csv"),
                  {"source": "replay", "graph": {"bound": False, "label": cr.REPLAYED, "sha256": "0" * 64},
                   "row_columns": ("name",)})


def _measure_state():
    """A finished measure, as link_cycle.closure_graph leaves it: two units (one failing, one
    with a hard-coded row), a certified and a rejected twin, three datums, an EH thunk."""
    units = [{"id": 0, "head": "?a@@YAXXZ"}, {"id": 1, "head": None}, {"id": 2, "head": "?c@@YAXXZ"}]
    recs = [{"row": {"name": "?a@@YAXXZ", "kind": "real", "source": "Code/a.cpp", "rva": 0x1000, "size": 16},
             "unit": units[0], "measured": True, "fails": [], "placed": 1},
            {"row": {"name": "?a2@@YAXXZ", "kind": "real", "source": "Code/a.cpp", "rva": 0x0F00, "size": 8},
             "unit": units[0], "measured": True, "fails": ["data-back:_g", "data-back:_g"], "placed": 1},
            {"row": {"name": "?b@@YAXXZ", "kind": "gen-funclet", "source": "Code/b.cpp", "rva": 0x2000, "size": 4},
             "unit": units[1], "measured": False, "fails": [], "placed": 0},
            {"row": {"name": "?c@@YAXXZ", "kind": "real", "source": "Code/c.cpp", "rva": 0x3000, "size": 32},
             "unit": units[2], "measured": True, "fails": [], "placed": 1}]
    hard = {id(recs[3]): "hardcoded address"}
    d1, d2, d3 = (0x9000, 0x8000, 4), (0x9100, -0x10, 8), (0x9200, 0x8200, 4)
    m = types.SimpleNamespace(
        twins={(0x500, 0x1000): (True, "certified"), (0x600, 0x3000): (False, "bytes"), (0x700, 0x4000): (True, "ok")},
        twin_fails={(0x600, 0x3000): ["bytes", "extent differs"]},
        dnodes={d1: {"name": "_g", "fails": ["data-content"]}, d2: {"name": "_h", "fails": []},
                d3: {"name": "_k", "fails": []}},
        sym_at=lambda a: (a, f"_sym{a:X}", "o.obj", a + 1) if a != 0x700 else None)
    ok = {("unit", 0): False, ("unit", 1): False, ("unit", 2): False, ("twin", 0x500, 0x1000): True,
          ("twin", 0x600, 0x3000): False, ("twin", 0x700, 0x4000): False, ("datum", d1): False, ("datum", d2): False,
          ("datum", d3): True, ("eh", 0x77): False, ("eh", 0x78): True}
    edges = {("unit", 0): {("datum", d1), ("twin", 0x500, 0x1000), ("fill", 0x5000)}, ("unit", 2): {("eh", 0x77)},
             ("twin", 0x500, 0x1000): {("datum", d2), ("stub",)}, ("unit", 1): set()}
    return m, recs, hard, ok, edges


def test_link_cycles_graph_emit_reads_the_measure_and_changes_nothing(tmp_path):
    m, recs, hard, ok, edges = _measure_state()
    before = copy.deepcopy((recs, ok, edges, m.twins, m.twin_fails, m.dnodes)), dict(hard)
    doc = lc.closure_graph_doc(m, recs, hard, ok, edges)
    assert (copy.deepcopy((recs, ok, edges, m.twins, m.twin_fails, m.dnodes)), dict(hard)) == before   # read only
    assert doc == cr._graph_doc(m, recs, hard, ok, edges)                      # the replay's copy is the same
    assert doc["schema"] == lc.CLOSURE_GRAPH_SCHEMA == cr.GRAPH_SCHEMA and lc.CLOSURE_GRAPH == cr.GRAPH_FILE
    n = doc["nodes"]
    assert n["unit:0"] == {"kind": "unit", "ok": False, "name": "?a@@YAXXZ", "rva": 0x0F00, "source": "Code/a.cpp",
                           "failures": ["data-back:_g"]}
    assert n["unit:1"]["failures"] == ["unmeasured"] and n["unit:1"]["name"] == "?b@@YAXXZ"
    assert n["unit:2"]["failures"] == ["shift:hardcoded address"]
    assert n["twin:1536:12288"]["failures"] == ["bytes", "extent differs"]
    assert n["twin:1792:16384"] == {"kind": "twin", "ok": False, "failures": ["shift"], "rva": 0x4000,
                                    "linked": 0x700, "name": "", "object": ""}   # certified, failed its shift check
    assert n["twin:1280:4096"]["failures"] == [] and n["twin:1280:4096"]["name"] == "_sym500"
    assert n["datum:36864:32768:4"]["failures"] == ["data-content"]             # its shift check was never asked
    assert n["datum:37120:-16:8"]["failures"] == ["shift"] and n["eh:119"]["failures"] == ["shift"]
    assert n["eh:120"] == {"kind": "eh", "ok": True, "failures": []}
    assert doc["edges"] == {"twin:1280:4096": ["datum:37120:-16:8", "stub"],
                            "unit:0": ["datum:36864:32768:4", "fill:20480", "twin:1280:4096"], "unit:2": ["eh:119"]}
    assert doc["rows"][0] == ["?a2@@YAXXZ", "real", "Code/a.cpp", 0x0F00, 8, "unit:0", 1, 0]
    assert [r[7] for r in doc["rows"]] == [0, 1, 0, 1] and doc["rows"][2][6] == 0
    # the same measure writes the same bytes, whatever order its dicts and sets happen to have
    shuffled = dict(reversed(list(ok.items()))), {k: set(sorted(v, key=str, reverse=True)) for k, v in
                                                  reversed(list(edges.items()))}
    lc.write_closure_graph(tmp_path / "a.gz", doc)
    lc.write_closure_graph(tmp_path / "b.gz", lc.closure_graph_doc(m, list(reversed(recs)), hard, *shuffled))
    assert (tmp_path / "a.gz").read_bytes() == (tmp_path / "b.gz").read_bytes()
    # and tools/closure_report.py reads it back as link_cycle's own closure
    g_ok, g_edges, rows, describe_node = cr.load_graph(tmp_path / "a.gz", lc.sha256(tmp_path / "a.gz"))
    assert {k[1] for k in cr.reference_closure(g_ok, g_edges)} == {lc.node_key(k) for k in
                                                                    lc.greatest_closure(ok, edges)}
    assert describe_node(("unit", "unit:0"))["group"] == "0x00000F00"
    assert describe_node(("datum", "datum:37120:-16:8"))["group"].startswith("datum:-0x00000010")   # no address
    assert describe_node(("fill", "fill:20480")) == {"id": "fill:0x00005000", "kind": "fill",
                                                    "group": "fill:0x00005000"}


def test_the_graphs_digest_is_bound_by_the_receipt_outside_its_core(tmp_path):
    """The receipt names the graph (closure_graph_sha256) and its core does not move: the
    same inputs keep the same core_sha256 and core_canon_sha256 as before the graph existed."""
    run = cf.make_run(tmp_path / "plain")
    receipt = json.loads((run / "receipt.json").read_text())
    with_graph = dict(receipt, closure_graph_sha256="ab" * 32)
    lc.stamp_cores(with_graph)
    assert (with_graph["core_sha256"], with_graph["core_canon_sha256"]) == (receipt["core_sha256"],
                                                                            receipt["core_canon_sha256"])
    assert "closure_graph_sha256" not in lc.receipt_core(with_graph)
    assert "closure_graph_sha256" not in json.dumps(receipt["series"])        # and the series is untouched
    src = (TOOLS / "link_cycle.py").read_text(encoding="utf-8")
    assert src.count("write_closure_graph(out / CLOSURE_GRAPH, closure_graph_doc(m, recs, hard, ok, edges))") == 1
    emit, ret = src.index("write_closure_graph(out / CLOSURE_GRAPH"), src.index('res["link_status_sha256"] = sha256(status)')
    assert ret < emit < src.index("\ndef closure_graph(m, recs, hard, sh, ledger_starts):")   # last, after `res` is final


def test_document_binds_the_blockers_table_and_is_deterministic(tmp_path):
    GROUPS.clear()
    ok, edges, rows = graph()
    binding = {"commit": "c" * 40, "receipt_core_sha256": "d" * 64, "link_status_sha256": "e" * 64,
               "graph": {"bound": False, "label": cr.REPLAYED, "sha256": "f" * 64}}
    a = cr.document(*cr.analyze(ok, edges, rows, describe), binding)
    b = cr.document(*cr.analyze(ok, edges, list(reversed(rows)), describe), binding)
    assert a == b
    doc = json.loads(a[0])
    assert doc["schema"] == cr.SCHEMA and doc["algorithm"] == cr.ALGORITHM and doc["commit"] == "c" * 40
    assert doc["blockers"]["sha256"] == cr.sha256_bytes(a[1]) and doc["limits"] == list(cr.LIMITS)
    assert doc["blockers"]["set_cap"] == cr.SET_CAP and "truncated" in doc["blockers"]["roots_column"]
    (tmp_path / "r.json.gz").write_bytes(gzip.compress(a[0]))
    assert cr.load_roots(tmp_path / "r.json.gz") == doc
    (tmp_path / "other.json").write_text(json.dumps(dict(doc, algorithm="some-other-ranking/9")))
    with pytest.raises(cr.ReportError, match="this checkout reads"):
        cr.load_roots(tmp_path / "other.json")
    (tmp_path / "anon.json").write_text(json.dumps(dict(doc, graph={"bound": True, "label": cr.REPLAYED})))
    with pytest.raises(cr.ReportError, match="does not say where its graph came from"):
        cr.load_roots(tmp_path / "anon.json")


# ---------------------------------------------------------------- in the bundle

@pytest.fixture
def closure_bundle(tmp_path):
    run = cf.make_run(tmp_path / "snaps", status=cf.CLOSURE_STATUS, rank_files=True, closure=True,
                      date_utc=cf.recent())
    out = tmp_path / "bundle"
    return run, out, cf.bundle(run, out, "laptop/watchdog", require_closure=True)


def test_the_bundle_carries_the_measured_graph_and_the_report_bound_to_it(closure_bundle):
    run, out, m = closure_bundle
    assert {ca.CLOSURE_GRAPH, ca.CLOSURE_ROOTS, ca.CLOSURE_BLOCKERS} <= set(m["members"])
    c = m["components"]["closure_report"]
    assert c["included"] and c["schema"] == cr.SCHEMA and c["algorithm"] == cr.ALGORITHM and c["graph"] == cr.BOUND
    b = ca.load_bundle(out)
    doc = cr.load_roots(b.closure_roots)
    assert doc["commit"] == cf.COMMIT and doc["receipt_core_sha256"] == m["receipt"]["core_sha256"]
    assert doc["graph"]["sha256"] == b.receipt["closure_graph_sha256"] == ca.sha256_file(b.closure_graph)
    assert b.closure_graph.read_bytes() == (run / lc.CLOSURE_GRAPH).read_bytes()
    assert [(e["root"], e["conditional_gain_bytes"]) for e in doc["roots"]] == [("0x00003000", 70), ("0x00004000", 24)]
    with gzip.open(b.closure_blockers, "rb") as f:
        table = f.read()
    assert cr.sha256_bytes(table) == doc["blockers"]["sha256"] == m["members"][ca.CLOSURE_BLOCKERS]["content_sha256"]
    both = next(line for line in table.decode().splitlines() if line.startswith("?both@@YAXXZ"))
    assert ",2,0x00003000;0x00004000,1," in both                               # the complete set, for a later packet
    assert cr.joint_gain(cr.load_graph(b.closure_graph), ["0x00003000", "0x00004000"]) == 110   # 70 + 24 + ?both's 16


def test_a_replayed_report_is_labelled_and_only_fits_a_receipt_that_names_no_graph(tmp_path):
    run = cf.make_run(tmp_path / "old", status=cf.CLOSURE_STATUS, rank_files=True, closure="replay")
    m = cf.bundle(run, tmp_path / "bundle", "x", require_closure=True)
    assert m["components"]["closure_report"]["graph"] == cr.REPLAYED and ca.CLOSURE_GRAPH not in m["members"]
    assert cr.load_roots(ca.load_bundle(tmp_path / "bundle").closure_roots)["graph"]["bound"] is False
    # a run that DID write its graph cannot be published with a replay in its place
    run2 = cf.make_run(tmp_path / "new", status=cf.CLOSURE_STATUS, rank_files=True, closure="graph")
    cf.write_closure(run2, replayed=True)
    with pytest.raises(ca.BundleError, match="is a replay, but this run's receipt names a measured graph"):
        cf.bundle(run2, tmp_path / "bundle2", "x")
    assert not (tmp_path / "bundle2").exists()


def _regz(path, edit):
    doc = json.loads(gzip.decompress(path.read_bytes()))
    edit(doc)
    path.write_bytes(gzip.compress(json.dumps(doc).encode()))


def _rebind(bundle, name):
    """Make the manifest agree with an edited member: only the member's own binding is left to catch it."""
    m = json.loads((bundle / "manifest.json").read_text())
    data = (bundle / name).read_bytes()
    m["members"][name].update(sha256=cr.sha256_bytes(data), size=len(data))
    if "content_sha256" in m["members"][name]:
        raw = gzip.decompress(data)
        m["members"][name].update(content_sha256=cr.sha256_bytes(raw), content_size=len(raw))
    (bundle / "manifest.json").write_text(json.dumps(m))


def _manifest(bundle, edit):
    m = json.loads((bundle / "manifest.json").read_text())
    edit(m)
    (bundle / "manifest.json").write_text(json.dumps(m))


def _drop(bundle, *names):
    for n in names:
        (bundle / n).unlink()
    _manifest(bundle, lambda m: [m["members"].pop(n) for n in names])


@pytest.mark.parametrize("damage, message", [
    (lambda b: (_regz(b / ca.CLOSURE_ROOTS, lambda d: d.update(commit=cf.OTHER)), _rebind(b, ca.CLOSURE_ROOTS)),
     "describes another run"),
    (lambda b: (_regz(b / ca.CLOSURE_ROOTS, lambda d: d["summary"].update(credit_unique_bytes=1)),
                _rebind(b, ca.CLOSURE_ROOTS)), "its graph credits 1"),
    (lambda b: ((b / ca.CLOSURE_BLOCKERS).write_bytes(gzip.compress(b"name\n")), _rebind(b, ca.CLOSURE_BLOCKERS)),
     "is not the table"),
    (lambda b: _drop(b, ca.CLOSURE_BLOCKERS), "without its companion"),
    (lambda b: (b / ca.CLOSURE_ROOTS).write_bytes((b / ca.CLOSURE_ROOTS).read_bytes()[:-9] + b"corrupted"),
     "closure_roots.json.gz: sha256"),
    # Sol 4: both files and both member entries removed, the component still declared included
    (lambda b: _drop(b, ca.CLOSURE_ROOTS, ca.CLOSURE_BLOCKERS), "included is True but the bundle holds neither"),
    (lambda b: _manifest(b, lambda m: m["components"]["closure_report"].update(included=False, why="x")),
     "included is False but the bundle holds both"),
    (lambda b: _manifest(b, lambda m: m["components"]["closure_report"].update(algorithm="affected-bytes/1")),
     "components.closure_report.algorithm 'affected-bytes/1' is not"),
    (lambda b: _manifest(b, lambda m: m["components"]["closure_report"].update(schema="closure-report/1")),
     "components.closure_report.schema"),
    (lambda b: _manifest(b, lambda m: m["components"]["closure_report"].update(graph=cr.REPLAYED)),
     "components.closure_report.graph"),
    # the graph and the report's claim to be bound to it
    (lambda b: ((b / ca.CLOSURE_GRAPH).write_bytes(gzip.compress(b"{}", mtime=0)), _rebind(b, ca.CLOSURE_GRAPH)),
     "is not the graph the receipt names"),
    (lambda b: (_regz(b / ca.CLOSURE_ROOTS, lambda d: d["graph"].update(sha256="0" * 64)),
                _rebind(b, ca.CLOSURE_ROOTS)), "says its graph is bound to the receipt, but"),
    (lambda b: (_regz(b / ca.CLOSURE_ROOTS, lambda d: d["graph"].update(bound=False, label=cr.REPLAYED)),
                _rebind(b, ca.CLOSURE_ROOTS)), "is a replay, but this run's receipt names a measured graph"),
])
def test_closure_components_that_do_not_agree_are_refused(closure_bundle, damage, message):
    _, out, _ = closure_bundle
    damage(out)
    with pytest.raises(ca.BundleError, match=message):
        ca.validate(out)


def test_a_bundle_without_a_closure_report_is_valid_and_says_why(tmp_path):
    run = cf.make_run(tmp_path / "snaps", rank_files=True, date_utc=cf.recent())
    m = cf.bundle(run, tmp_path / "bundle", "x")
    assert sorted(m["members"]) == sorted(ca.MEMBERS)
    assert m["components"]["closure_report"] == {
        "included": False, "status": "diagnostic-only",
        "why": "published diagnostic-only: the run directory holds no closure_roots.json and closure_blockers.csv "
               "(tools/closure_report.py replay)"}
    assert ca.load_bundle(tmp_path / "bundle").closure_roots is None
    with pytest.raises(pc.RunError, match="--closure"):
        cf.bundle(run, tmp_path / "b2", "x", closure=tmp_path / "nowhere")


def test_a_closure_report_of_another_run_is_not_bundled(tmp_path):
    run = cf.make_run(tmp_path / "snaps", status=cf.CLOSURE_STATUS, rank_files=True, closure="graph")
    other = cf.make_run(tmp_path / "other", status=cf.CLOSURE_STATUS, rank_files=True, commit=cf.OTHER,
                        closure="graph")
    cf.write_closure(other, dest=tmp_path / "theirs")
    with pytest.raises(ca.BundleError, match="describes another run"):
        cf.bundle(run, tmp_path / "bundle", "x", closure=tmp_path / "theirs")
    assert not (tmp_path / "bundle").exists()
