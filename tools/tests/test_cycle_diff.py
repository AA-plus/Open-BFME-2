"""cycle_diff: interval credit, the exact-net reconciliation, receipt checks, the
row-level explanation and the publisher's compare(), on synthetic link_cycle runs."""
import contextlib
import csv
import gzip
import hashlib
import io
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import cycle_diff as cd  # noqa: E402

COLS = ["name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason", "self_strict",
        "closed_strict", "closed_strict_pilot_rule", "pinned_strict", "byte_equal", "hardcoded", "failure_count",
        "failures"]
FOLD_COLS = ["retail_rva", "retail_start", "export_names", "linked", "symbols", "rule", "verdict"]
OK = (1, "", 1, 1, "")                         # placed, reason, self_strict, closed_strict, failures
SHIFT = "shift:code:hardcoded address"


def row(name, rva, size, state=OK, source=None, kind="real"):
    placed, reason, ss, cs, failures = state
    return (name, kind, source or f"Code/{name}.cpp", rva, size, placed, reason, ss, cs, failures)


def credit_oracle(rows):
    """Unique bytes of real, placed, closed-strict rows, by a byte set (not cd.union)."""
    covered = set()
    for name, kind, source, rva, size, placed, reason, ss, cs, failures in rows:
        if kind == "real" and placed and cs:
            covered.update(range(rva, rva + size))
    return len(covered)


def write_run(directory, rows, commit="a" * 40, tool_digest="d" * 64, submodule="1" * 40, credit_delta=0,
              record_hash=True, gz=False, folds=None):
    """A run directory; gz writes link_status.csv.gz and data_fold_list.csv.gz only."""
    d = Path(directory)
    d.mkdir(parents=True, exist_ok=True)
    text = io.StringIO()
    w = csv.writer(text, lineterminator="\r\n")
    w.writerow(COLS)
    for name, kind, source, rva, size, placed, reason, ss, cs, failures in rows:
        w.writerow([name, kind, source, "0x%08X" % rva, size, "0x%08X" % rva if placed else "", placed, reason, ss,
                    cs, cs, ss, ss, 0, len([f for f in failures.split(";") if f]), failures])
    data = text.getvalue().encode("utf-8")
    if gz:
        (d / "link_status.csv.gz").write_bytes(gzip.compress(data))
    else:
        (d / "link_status.csv").write_bytes(data)
    series = {"credit_unique_bytes": credit_oracle(rows) + credit_delta}
    if record_hash:
        series["link_status_sha256"] = hashlib.sha256(data).hexdigest()
    receipt = {"commit": commit, "submodules": {"reference/open-bfme-1": submodule}, "tool_digest": tool_digest,
               "tool": "link_cycle", "rules": "link-cycle-2", "shadow_rules": ["data-fold-1"],
               "date_utc": "2026-10-11 00:00:00", "authoritative": True, "core_sha256": commit[:1] * 64,
               "series": series}
    (d / "receipt.json").write_text(json.dumps(receipt), encoding="utf-8")
    if folds:
        fold_text = io.StringIO()
        fw = csv.writer(fold_text, lineterminator="\r\n")
        fw.writerow(FOLD_COLS)
        fw.writerows(folds)
        fold_bytes = fold_text.getvalue().encode("utf-8")
        if gz:
            (d / "data_fold_list.csv.gz").write_bytes(gzip.compress(fold_bytes))
        else:
            (d / "data_fold_list.csv").write_bytes(fold_bytes)
    return d


def run_dirs(tmp, old_rows, new_rows, old_kw=None, **new_kw):
    old = write_run(Path(tmp) / "old", old_rows, **(old_kw or {}))
    new = write_run(Path(tmp) / "new", new_rows, **{"commit": "b" * 40, **new_kw})
    return old, new


def runs(tmp, old_rows, new_rows, old_kw=None, **new_kw):
    old, new = run_dirs(tmp, old_rows, new_rows, old_kw, **new_kw)
    return cd.load_run(old, "OLD"), cd.load_run(new, "NEW")


def report_for(old_rows, new_rows, old_kw=None, **new_kw):
    with tempfile.TemporaryDirectory() as tmp:
        old, new = runs(tmp, old_rows, new_rows, old_kw, **new_kw)
        return cd.build_report(old, new)


def refused(fn):
    """The message of a CycleDiffError refusal."""
    try:
        fn()
    except cd.CycleDiffError as exc:
        return str(exc)
    raise AssertionError("not refused")


def by_start(items):
    return {it["start"]: it for it in items}


def bytes_by_category(section):
    return {c: v["bytes"] for c, v in section["categories"].items() if v["bytes"]}


class Intervals(unittest.TestCase):
    def test_union_merges_overlaps_and_touching(self):
        self.assertEqual(cd.union([(0, 10), (5, 20), (30, 31), (0, 4), (20, 25), (40, 40)]), [(0, 25), (30, 31)])
        self.assertEqual(cd.total(cd.union([(0, 10), (5, 20)])), 20)
        self.assertEqual(cd.union([]), [])

    def test_subtract(self):
        a = [(0, 100), (200, 300)]
        self.assertEqual(cd.subtract(a, [(10, 20), (50, 250)]), [(0, 10), (20, 50), (250, 300)])
        self.assertEqual(cd.subtract(a, []), a)
        self.assertEqual(cd.subtract(a, [(0, 300)]), [])

    def test_cover_finds_long_rows_behind_short_ones(self):
        rows = [cd.Row("big", "real", "s", 0, 1000, True, "", True, True, "", ""),
                cd.Row("small", "real", "s", 10, 5, True, "", True, True, "", ""),
                cd.Row("far", "real", "s", 2000, 5, True, "", True, True, "", "")]
        self.assertEqual([r.name for r in cd.Cover(rows).over(500, 501)], ["big"])
        self.assertEqual([r.name for r in cd.Cover(rows).over(12, 13)], ["big", "small"])
        self.assertEqual(cd.Cover(rows).over(1000, 2000), [])

    def test_failure_classes(self):
        self.assertEqual(cd.failure_classes("ehx2;data-back:_gx2;shift:code:hardcoded address;data-back:_h"),
                         ["eh", "data-back", "shift"])
        self.assertEqual(cd.failure_symbols("data-back:_gx2;data-fwd:_k", "data-back"), [("_gx2", "_g")])


class Credit(unittest.TestCase):
    def test_overlapping_rows_count_once_and_net_is_exact(self):
        old = [row("a", 0x100, 0x60), row("b", 0x140, 0x40), row("c", 0x300, 0x10)]   # a and b overlap
        new = [row("a", 0x100, 0x60), row("b", 0x140, 0x40, (1, "", 0, 0, "data-fwd:_x")),
               row("c", 0x300, 0x10), row("d", 0x400, 0x20)]
        rep = report_for(old, new)
        self.assertEqual(rep["old"]["credit_unique_bytes"], 0x90)                 # [0x100,0x180) + 0x10
        self.assertEqual(rep["totals"]["lost"], 0x20)                              # [0x160,0x180)
        self.assertEqual(rep["totals"]["gained"], 0x20)
        self.assertEqual(rep["totals"]["net"], 0)
        (it,) = rep["lost"]["items"]
        self.assertEqual((it["start"], it["end"], it["category"]), (0x160, 0x180, "data-fwd"))
        self.assertEqual([r.name for r in it["had"]], ["b"])                       # a no longer covers it
        self.assertEqual(it["relation"], "same row")

    def test_rename_is_not_a_loss(self):
        old = [row("?old@@YAXXZ", 0x100, 0x40), row("?was@@YAXXZ", 0x180, 0x20, source="Code/Same.cpp"),
               row("keep", 0x200, 0x10)]
        new = [row("?new@@YAXXZ", 0x100, 0x40, source="Code/Moved.cpp"),
               row("?now@@YAXXZ", 0x180, 0x20, source="Code/Same.cpp"), row("keep", 0x200, 0x10)]
        rep = report_for(old, new)
        self.assertEqual((rep["totals"]["lost"], rep["totals"]["gained"]), (0, 0))
        self.assertEqual(rep["renames"], {"renamed": {"rows": 1, "bytes": 0x20},
                                          "other_name_and_source": {"rows": 1, "bytes": 0x40},
                                          "name_join_lost_bytes": 0x60})

    def test_split_row_loses_only_its_failing_half_and_is_no_rename(self):
        old = [row("whole", 0x100, 0x100)]
        new = [row("front", 0x100, 0x80, source="Code/whole.cpp"),
               row("back", 0x180, 0x80, (1, "", 0, 0, "twin-rejected:extent differs"), source="Code/whole.cpp")]
        rep = report_for(old, new)
        (it,) = rep["lost"]["items"]
        self.assertEqual((it["start"], it["end"], it["category"]), (0x180, 0x200, "twin-rejected"))
        self.assertEqual(it["witness"].name, "back")
        self.assertEqual(it["relation"], "covering row")              # another interval: not shown as a rename
        self.assertEqual([r.name for r in it["had"]], ["whole"])
        text = io.StringIO()
        cd.render(rep, 5, 5, out=text)
        self.assertIn("NEW covering row: back 0x00000180+128", text.getvalue())
        self.assertNotIn("renamed", text.getvalue().split("top 1 losses")[1])

    def test_same_interval_and_source_under_another_name_is_a_rename(self):
        old = [row("?a@@YAXXZ", 0x100, 0x40, source="Code/U.cpp")]
        new = [row("?b@@YAXXZ", 0x100, 0x40, (1, "", 0, 0, "eh"), source="Code/U.cpp")]
        (it,) = report_for(old, new)["lost"]["items"]
        self.assertEqual((it["relation"], it["witness"].name), ("renamed", "?b@@YAXXZ"))

    def test_witness_is_the_old_rows_own_interval(self):
        # an earlier-starting row and a smaller same-start row also cover the bytes; neither is the witness
        old = [row("x", 0x100, 0x100)]
        new = [row("outer", 0x80, 0x200, (1, "", 0, 0, "eh")), row("small", 0x100, 0x40, (1, "", 0, 0, "eh")),
               row("x", 0x100, 0x100, (0, "overlaps previous unit", 1, 1, ""))]
        rep = report_for(old, new)
        (it,) = rep["lost"]["items"]
        self.assertEqual((it["start"], it["end"], it["category"], it["witness"].name), (0x100, 0x200, "placement", "x"))
        self.assertEqual([r.name for r in it["now"]], ["outer", "small", "x"])

    def test_merged_rows_explain_each_old_body(self):
        old = [row("one", 0x100, 0x80), row("two", 0x180, 0x80)]
        new = [row("both", 0x100, 0x100, (1, "", 0, 0, "data-back:_g"))]
        rep = report_for(old, new)
        items = rep["lost"]["items"]
        self.assertEqual([(i["start"], i["end"], i["category"], i["relation"]) for i in items],
                         [(0x100, 0x180, "data-back", "covering row"), (0x180, 0x200, "data-back", "covering row")])
        self.assertEqual(rep["lost"]["categories"]["data-back"], {"rows": 2, "bytes": 0x100})

    def test_extent_growth_and_shrink_are_not_new_or_removed_rows(self):
        old = [row("f", 0x100, 0x40), row("h", 0x300, 0x80)]
        new = [row("f", 0x100, 0x80), row("h", 0x300, 0x40), row("g", 0x500, 0x10)]
        rep = report_for(old, new)
        self.assertEqual(bytes_by_category(rep["gained"]), {"extent growth": 0x40, "new row": 0x10})
        grown = by_start(rep["gained"]["items"])[0x140]
        self.assertIn("newly covered bytes of an existing row: OLD f 0x00000100+64", grown["detail"])
        (shrunk,) = rep["lost"]["items"]
        self.assertEqual((shrunk["start"], shrunk["category"]), (0x340, "other"))
        self.assertIn("extent shrank: NEW h 0x00000300+64", shrunk["detail"])

    def test_categories_partition_the_loss(self):
        kept = row("kept", 0x900, 0x10, source="Code/GameEngine/Kept.cpp")
        old = [row("twin", 0x100, 0x10), row("clos", 0x200, 0x20), row("sel", 0x300, 0x30),
               row("moved", 0x340, 0x8), row("fwd", 0x400, 0x40), row("back", 0x500, 0x50),
               row("quar", 0x600, 0x6), row("eh", 0x700, 0x70), row("gone", 0x800, 0x80),
               row("alias", 0x880, 0x8), row("shift", 0x980, 0x9), kept]
        new = [row("twin", 0x100, 0x10, (1, "", 0, 0, "twin-rejected:calls a rejected twin")),
               row("clos", 0x200, 0x20, (1, "", 1, 0, "")),
               row("sel", 0x300, 0x30, (0, "copy not selected", 0, 0, "not-selected:^code_^game^engine_^kept.obj")),
               row("moved", 0x340, 0x8, (0, "overlaps previous unit", 1, 1, "")),
               row("fwd", 0x400, 0x40, (1, "", 0, 0, "data-fwd:_a;data-back:_b")),      # data-fwd first
               row("back", 0x500, 0x50, (1, "", 0, 0, "data-back:_b")),
               row("quar", 0x600, 0x6, (0, "quarantined: linked footprint != retail extent", 1, 1, "")),
               row("eh", 0x700, 0x70, (1, "", 0, 0, "eh")),
               row("alias", 0x880, 0x8, kind="gen-alias"),
               row("shift", 0x980, 0x9, (1, "", 1, 0, SHIFT)), kept]                   # self-strict, shift only
        rep = report_for(old, new)
        cats = rep["lost"]["categories"]
        self.assertEqual(bytes_by_category(rep["lost"]),
                         {"twin-rejected": 0x10, "closure": 0x20, "placement": 0x38, "data-fwd": 0x40,
                          "data-back": 0x50, "quarantine": 0x6, "shift": 0x9, "other": 0x70 + 0x80 + 0x8})
        self.assertEqual(sum(v["bytes"] for v in cats.values()), rep["totals"]["lost"])
        items = by_start(rep["lost"]["items"])
        self.assertEqual(items[0x300]["kept"], ["Code/GameEngine/Kept.cpp"])        # decoded kept object
        self.assertIn("no real row covers", items[0x800]["detail"])
        self.assertIn("gen-alias", items[0x880]["detail"])
        self.assertEqual(items[0x700]["detail"], "eh")

    def test_closure_loss_lists_newly_failing_same_source_rows_as_leads(self):
        src = "Code/Unit.cpp"
        old = [row("dtor", 0x100, 0x40, source=src), row("cleanup", 0x140, 0x5, source=src),
               row("still", 0x180, 0x10, (1, "", 0, 0, "eh"), source=src)]
        new = [row("dtor", 0x100, 0x40, (1, "", 0, 0, "twin-rejected:extent differs"), source=src),
               row("cleanup", 0x140, 0x5, (1, "", 1, 0, ""), source=src),
               row("still", 0x180, 0x10, (1, "", 0, 0, "eh"), source=src)]           # failed before too: no lead
        rep = report_for(old, new)
        it = by_start(rep["lost"]["items"])[0x140]
        self.assertEqual(it["category"], "closure")
        self.assertEqual([r.name for r in it["leads"]], ["dtor"])

    def test_data_back_carries_the_fold_list_entry(self):
        sym = "?ShaderOverbrightEnabled@@3_NA"
        old = [row("getter", 0x100, 0x17)]
        new = [row("getter", 0x100, 0x17, (1, "", 0, 0, f"data-back:{sym}"))]
        folds = [["0x009B5F84", "0x009B5F84", "0", "0x00E61579:1;0x00ECE224:stub", sym, "", "reaches stub"]]
        rep = report_for(old, new, folds=folds)
        (it,) = rep["lost"]["items"]
        self.assertEqual(it["folds"], [{"retail_rva": "0x009B5F84", "linked": "0x00E61579:1;0x00ECE224:stub",
                                        "verdict": "reaches stub", "symbol": sym}])
        self.assertEqual(it["folds_missing"], [])

    def test_mixed_data_fwd_and_back_reports_its_own_data_back_fold_evidence(self):
        # regression, the real 75 B ??1Rva0060061A dtor: it fails data-fwd and data-back (x2), so its category is
        # data-fwd; its data-back fold evidence must still be reported. 275a's fold list names the datums reaching
        # 0x00A06E54 (G00A06E54 and TheArchiveFileSystem, the data-fwd symbol), not the data-back symbol
        # TheLocalFileSystem: that is a missing entry, and the data-fwd symbol's entry is no evidence for it
        local = "?TheLocalFileSystem@@3PAVLocalFileSystem@@A"
        archive = "?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A"
        old = [row("??1Rva0060061A@@UAE@XZ", 0x60061A, 75)]
        new = [row("??1Rva0060061A@@UAE@XZ", 0x60061A, 75, (1, "", 0, 0, f"data-fwd:{archive}x2;data-back:{local}x2"))]
        folds = [["0x00A06E54", "0x00A06E54", "0", "0x00EADE50:4;0x00EADE54:4",
                  f"?G00A06E54@@3PAVRva0060061AHelper@@A;{archive}", "", "retail extent not in .rdata"]]
        rep = report_for(old, new, folds=folds)
        (it,) = rep["lost"]["items"]
        self.assertEqual(it["category"], "data-fwd")
        self.assertEqual((it["folds"], it["folds_missing"]), ([], [local]))
        text = io.StringIO()
        cd.render(rep, 5, 5, out=text)
        self.assertIn(f"no fold entry for the data-back symbol {local} (NEW fold list)", text.getvalue())
        self.assertNotIn("TheArchiveFileSystem@@3PAVArchiveFileSystem@@A retail", text.getvalue())
        # a data-back symbol the fold list does name is matched directly (through its x2 repeat count)
        direct = folds + [["0x00A06E60", "0x00A06E60", "0", "0x00E00010:4;0x00E00020:4", local, "", "reaches stub"]]
        (it,) = report_for(old, new, folds=direct)["lost"]["items"]
        self.assertEqual(([(f["symbol"], f["retail_rva"]) for f in it["folds"]], it["folds_missing"]),
                         ([(local, "0x00A06E60")], []))
        # no data-back failure: no fold evidence and nothing missing, though the fold list names the data-fwd symbol
        only_fwd = [row("??1Rva0060061A@@UAE@XZ", 0x60061A, 75, (1, "", 0, 0, f"data-fwd:{archive}"))]
        (it,) = report_for(old, only_fwd, folds=folds)["lost"]["items"]
        self.assertEqual((it["folds"], it["folds_missing"]), ([], []))

    def test_fold_evidence_is_tracked_per_data_back_symbol(self):
        # two data-back symbols, one in the fold list and one not: the match is kept, the other reported missing
        old = [row("f", 0x100, 0x40)]
        new = [row("f", 0x100, 0x40, (1, "", 0, 0, "data-back:_has;data-fwd:_fwd;data-back:_lacksx3;data-back:_has"))]
        folds = [["0x00700000", "0x00700000", "0", "0x00C00000:4;0x00C00004:stub", "_has", "", "reaches stub"],
                 ["0x00700010", "0x00700010", "0", "0x00C00010:4;0x00C00014:4", "_fwd", "", "datums differ"]]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, old, new, folds=folds)
            rep = cd.compare(o, n)
            (it,) = rep["lost"]["items"]
            self.assertEqual(([f["symbol"] for f in it["folds"]], it["folds_missing"]), (["_has"], ["_lacks"]))
            # a run without a fold list says nothing about its symbols: neither evidence nor a missing entry
            (n / "data_fold_list.csv").unlink()
            rep = cd.compare(o, n)
        (it,) = rep["lost"]["items"]
        self.assertIsNone(rep["new"]["folds_file"])
        self.assertEqual((it["folds"], it["folds_missing"]), ([], []))

    def test_gains_carry_the_old_runs_fold_witness(self):
        sym = "??_C@_02DPKJAMEF@?$CFd?$AA@"
        old = [row("_gpiSetInfos", 0x733C00, 0x594, (1, "", 0, 0, f"data-back:{sym}x6"))]
        new = [row("_gpiSetInfos", 0x733C00, 0x594)]
        folds = [["0x007C0000", "0x007C0000", "0", "0x00C00000:3;0x00C00010:3", sym, "", "datums differ"]]
        rep = report_for(old, new, old_kw={"folds": folds})
        (it,) = rep["gained"]["items"]
        self.assertEqual((it["category"], [f["symbol"] for f in it["folds"]], it["folds_missing"]),
                         ("now self-strict", [sym], []))

    def test_gain_categories_follow_the_flags(self):
        old = [row("placed", 0x100, 0x10, (0, "overlaps previous unit", 1, 1, "")),
               row("fixed", 0x200, 0x20, (1, "", 0, 0, "data-back:_g")),
               row("closed", 0x300, 0x30, (1, "", 1, 0, "")),
               row("shifted", 0x400, 0x40, (1, "", 1, 0, SHIFT)),          # self-strict: a shift repair
               row("unmeasured", 0x500, 0x50, (1, "", 0, 0, ""))]          # not self-strict, no failure text
        new = [row("placed", 0x100, 0x10), row("fixed", 0x200, 0x20), row("closed", 0x300, 0x30),
               row("shifted", 0x400, 0x40), row("unmeasured", 0x500, 0x50), row("fresh", 0x600, 0x60)]
        rep = report_for(old, new)
        self.assertEqual(bytes_by_category(rep["gained"]),
                         {"now placed": 0x10, "now self-strict": 0x20 + 0x50, "closure regained": 0x30,
                          "shift repaired": 0x40, "new row": 0x60})


class Receipts(unittest.TestCase):
    def test_status_csv_must_match_the_receipt_hash(self):
        with tempfile.TemporaryDirectory() as tmp:
            d = write_run(Path(tmp) / "r", [row("a", 0x100, 0x10)])
            status = d / "link_status.csv"
            status.write_bytes(status.read_bytes().replace(b"0x00000100,16", b"0x00000100,17"))
            self.assertIn("link_status_sha256", refused(lambda: cd.load_run(d, "OLD")))

    def test_receipt_without_a_hash_is_reported_unverified(self):
        with tempfile.TemporaryDirectory() as tmp:
            d = write_run(Path(tmp) / "r", [row("a", 0x100, 0x10)], record_hash=False)
            self.assertTrue(cd.load_run(d, "OLD").info()["status_hash"].startswith("unverified"))

    def test_gz_only_directories_work(self):
        sym = "_g"
        old = [row("a", 0x100, 0x10)]
        new = [row("a", 0x100, 0x10, (1, "", 0, 0, f"data-back:{sym}"))]
        folds = [["0x00700000", "0x00700000", "0", "0x00C00000:4;0x00C00004:stub", sym, "", "reaches stub"]]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, old, new, {"gz": True}, gz=True, folds=folds)
            self.assertEqual(sorted(p.name for p in n.iterdir()),
                             ["data_fold_list.csv.gz", "link_status.csv.gz", "receipt.json"])
            rep = cd.compare(o, n)
        self.assertEqual((rep["new"]["status_hash"], rep["new"]["status_file"], rep["new"]["folds_file"]),
                         ("verified", "link_status.csv.gz", "data_fold_list.csv.gz"))
        (it,) = rep["lost"]["items"]
        self.assertEqual(it["folds"][0]["retail_rva"], "0x00700000")

    def test_a_directory_without_a_status_is_refused(self):
        with tempfile.TemporaryDirectory() as tmp:
            self.assertIn("no link_status.csv", refused(lambda: cd.compare(None, tmp)))

    def test_not_a_link_cycle_status_is_refused(self):
        with tempfile.TemporaryDirectory() as tmp:
            d = write_run(Path(tmp) / "r", [row("a", 0x100, 0x10)])
            (d / "census.csv").write_text("name,source,status\nx,y,linked\n", encoding="utf-8")
            spec = {"status": d / "census.csv", "receipt": d / "receipt.json"}
            self.assertIn("not a link_cycle", refused(lambda: cd.load_run(spec, "OLD")))

    def test_net_must_equal_the_receipts_difference(self):
        old, new = [row("a", 0x100, 0x10)], [row("a", 0x100, 0x10), row("b", 0x200, 0x8)]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = runs(tmp, old, new, credit_delta=1)
            self.assertIn("is not the receipts' credit_unique_bytes difference",
                          refused(lambda: cd.build_report(o, n)))

    def test_each_run_must_reconcile_even_when_offsets_cancel(self):
        old, new = [row("a", 0x100, 0x10)], [row("a", 0x100, 0x10), row("b", 0x200, 0x8)]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = runs(tmp, old, new, {"credit_delta": 5}, credit_delta=5)
            self.assertIn("this tool's credit is not link_cycle's", refused(lambda: cd.build_report(o, n)))

    def test_measurement_and_submodule_changes(self):
        rows = [row("a", 0x100, 0x10)]
        same = report_for(rows, rows)
        self.assertFalse(same["measurement_changed"])
        self.assertEqual(same["changes"]["submodules"], [])
        moved = report_for(rows, rows, tool_digest="e" * 64, submodule="2" * 40)
        self.assertTrue(moved["measurement_changed"])
        self.assertEqual(moved["changes"]["measurement"], [("tool_digest", "d" * 64, "e" * 64)])
        self.assertEqual(moved["changes"]["submodules"], [("reference/open-bfme-1", "1" * 40, "2" * 40)])


class Candidates(unittest.TestCase):
    def git(self, repo, *args):
        return subprocess.run(["git", "-C", str(repo), *args], check=True, capture_output=True,
                              text=True).stdout.strip()

    def test_candidates_net_diffs_and_an_edit_reverted_within_the_range(self):
        with tempfile.TemporaryDirectory() as tmp:
            repo = Path(tmp) / "repo"
            (repo / "Code").mkdir(parents=True)
            self.git(repo, "init", "-q")
            self.git(repo, "config", "user.email", "t@example.com")
            self.git(repo, "config", "user.name", "t")
            for name in ("A.cpp", "B.cpp", "C.cpp", "Kept.cpp"):
                (repo / "Code" / name).write_text("// 0\n", encoding="utf-8")
            self.git(repo, "add", "-A")
            self.git(repo, "commit", "-q", "-m", "base")
            base = self.git(repo, "rev-parse", "HEAD")
            (repo / "Code" / "A.cpp").write_text("// 1\n", encoding="utf-8")
            (repo / "Code" / "Kept.cpp").write_text("// 1\n", encoding="utf-8")
            self.git(repo, "commit", "-q", "-am", "edit A and Kept")
            edit_a = self.git(repo, "rev-parse", "HEAD")
            (repo / "Code" / "C.cpp").write_text("// 1\n", encoding="utf-8")
            self.git(repo, "commit", "-q", "-am", "edit C")
            edit_c = self.git(repo, "rev-parse", "HEAD")
            self.git(repo, "revert", "--no-edit", edit_c)                # C: touched twice, no net diff
            tip = self.git(repo, "rev-parse", "HEAD")
            kept = row("kept", 0x900, 0x10, source="Code/Kept.cpp")
            old = [row("a", 0x100, 0x10, source="Code/A.cpp"), row("b", 0x200, 0x20, source="Code/B.cpp"),
                   row("c", 0x300, 0x30, source="Code/C.cpp"), kept]
            new = [row("a", 0x100, 0x10, (1, "", 0, 0, "eh"), source="Code/A.cpp"),
                   row("b", 0x200, 0x20, (0, "copy not selected", 0, 0, "not-selected:^code_^kept.obj"),
                       source="Code/B.cpp"),
                   row("c", 0x300, 0x30, (1, "", 0, 0, "eh"), source="Code/C.cpp"), kept]
            with tempfile.TemporaryDirectory() as runs_tmp:
                o, n = runs(runs_tmp, old, new)
                saved, cd.ROOT = cd.ROOT, repo
                try:
                    rep = cd.build_report(o, n, f"{base}..{tip}")
                finally:
                    cd.ROOT = saved
        items = by_start(rep["lost"]["items"])
        a, b, c = (items[x]["candidates"] for x in (0x100, 0x200, 0x300))
        self.assertEqual(([x["sha"] for x in a["Code/A.cpp"]["commits"]], a["Code/A.cpp"]["net_diff"]),
                         ([edit_a], True))
        self.assertEqual((b["Code/B.cpp"]["commits"], b["Code/B.cpp"]["net_diff"]), ([], False))
        self.assertEqual((b["Code/Kept.cpp"]["role"], b["Code/Kept.cpp"]["net_diff"]), ("kept copy", True))
        self.assertFalse(items[0x200]["net_source_diff"])      # a kept copy's diff is not the row's own
        self.assertEqual(([x["sha"] for x in c["Code/C.cpp"]["commits"]], c["Code/C.cpp"]["net_diff"]),
                         ([tip, edit_c], False))
        self.assertFalse(items[0x300]["net_source_diff"])
        self.assertEqual(rep["candidates"]["no_net_source_diff"], {"items": 2, "rows": 2, "bytes": 0x20 + 0x30})
        text = io.StringIO()
        cd.render(rep, 5, 0, out=text)
        self.assertIn("2 commits touched it", text.getvalue())
        self.assertIn("no net source diff between endpoints", text.getvalue())
        self.assertNotIn("caused by", text.getvalue().lower())

    def test_range_must_be_old_dot_dot_new(self):
        self.assertIn("expected OLD..NEW", refused(lambda: cd.range_index("abc")))


class Publisher(unittest.TestCase):
    def test_compare_is_deterministic_versioned_and_names_both_runs(self):
        old = [row("a", 0x100, 0x10), row("b", 0x200, 0x20)]
        new = [row("a", 0x100, 0x10, (1, "", 0, 0, "twin-rejected:extent differs")), row("b", 0x200, 0x20)]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, old, new)
            first, second = cd.compare(o, n), cd.compare(str(o), {"status": n / "link_status.csv",
                                                                  "receipt": n / "receipt.json"})
            out = Path(tmp) / "cli.json"
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(cd.main([str(o), str(n), "--json", str(out)]), 0)
            cli = out.read_text(encoding="utf-8")
        self.assertEqual(first, second)
        self.assertEqual(json.loads(cli), first)
        self.assertEqual(cli, json.dumps(json.loads(cli), indent=1, sort_keys=True) + "\n")     # sorted keys
        self.assertNotIn(Path(tmp).name, cli)                                                  # no local paths
        self.assertEqual(first["schema_version"], cd.SCHEMA_VERSION)
        self.assertEqual(first["identity"]["old"], {"commit": "a" * 40, "core_sha256": "a" * 64,
                                                    "core_canon_sha256": None, "tool_digest": "d" * 64,
                                                    "rules": "link-cycle-2",
                                                    "status_sha256": first["old"]["status_sha256"]})
        self.assertEqual(first["identity"]["new"]["commit"], "b" * 40)
        self.assertIn("precedence partition", first["schema"]["partition"])
        self.assertEqual(first["schema"]["lost"]["order"][:2], ["quarantine", "placement"])

    def test_dumps_serializes_what_compare_returns(self):
        # regression: dumps(compare(...)) raised TypeError on a report with losses or gains (already plain JSON)
        old = [row("a", 0x100, 0x10), row("b", 0x200, 0x20)]
        new = [row("a", 0x100, 0x10, (1, "", 0, 0, "twin-rejected:extent differs")), row("b", 0x200, 0x20),
               row("c", 0x300, 0x30)]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, old, new)
            out, first = Path(tmp) / "cli.json", Path(tmp) / "first.json"
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(cd.main([str(o), str(n), "--json", str(out)]), 0)
                self.assertEqual(cd.main(["--no-predecessor", str(n), "--json", str(first)]), 0)
            rep, alone = cd.compare(o, n), cd.compare(None, n)
            cli, cli_first = out.read_bytes(), first.read_bytes()
        self.assertEqual((len(rep["lost"]["items"]), len(rep["gained"]["items"])), (1, 1))
        self.assertEqual(cd.dumps(rep).encode("utf-8"), cli)
        self.assertEqual(cd.dumps(json.loads(cd.dumps(rep))), cd.dumps(rep))
        self.assertEqual(cd.dumps(alone).encode("utf-8"), cli_first)

    def test_no_predecessor(self):
        with tempfile.TemporaryDirectory() as tmp:
            n = write_run(Path(tmp) / "new", [row("a", 0x100, 0x10), row("b", 0x200, 0x8, (1, "", 0, 0, "eh"))])
            rep = cd.compare(None, n)
            text = io.StringIO()
            with contextlib.redirect_stdout(text):
                self.assertEqual(cd.main(["--no-predecessor", str(n)]), 0)
        self.assertFalse(rep["comparison"])
        self.assertEqual(rep["note"], "no predecessor run: nothing to compare")
        self.assertIsNone(rep["identity"]["old"])
        self.assertEqual(rep["new"]["credit_unique_bytes"], 0x10)
        self.assertIsNone(rep["lost"])
        self.assertIn("no predecessor run", text.getvalue())


class Cli(unittest.TestCase):
    def test_text_report(self):
        old = [row("a", 0x100, 0x10), row("b", 0x200, 0x20)]
        new = [row("a", 0x100, 0x10, (1, "", 0, 0, "twin-rejected:extent differs")), row("b", 0x200, 0x20),
               row("c", 0x300, 0x30)]
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, old, new, tool_digest="e" * 64)
            text = io.StringIO()
            with contextlib.redirect_stdout(text):
                self.assertEqual(cd.main([str(o), str(n)]), 0)
        shown = text.getvalue()
        self.assertIn("MEASUREMENT CHANGED", shown)
        self.assertIn("part of this difference may", shown)
        self.assertIn("precedence partition, not failure totals", shown)
        self.assertNotIn("caused by", shown.lower())

    def test_a_refusal_exits_1(self):
        with tempfile.TemporaryDirectory() as tmp:
            o, n = run_dirs(tmp, [row("a", 0x100, 0x10)], [row("a", 0x100, 0x10)], credit_delta=1)
            err = io.StringIO()
            with contextlib.redirect_stderr(err), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(cd.main([str(o), str(n)]), 1)
        self.assertIn("cycle_diff: FAIL: net", err.getvalue())

    def test_files_mode_needs_both_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            d = write_run(Path(tmp) / "r", [row("a", 0x100, 0x10)])
            with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as exc:
                cd.main(["--old-status", str(d / "link_status.csv"), "--new-status", str(d / "link_status.csv"),
                         "--new-receipt", str(d / "receipt.json")])
            self.assertEqual(exc.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
