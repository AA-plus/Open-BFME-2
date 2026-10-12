"""A link_cycle run for publish_cycle / cycle_artifacts / closure_report tests: a snapshot tree
(marker, reverse/ ledgers) with build/link_cycle/ holding a receipt stamped by link_cycle's own
stamp_cores, link_status.csv and data_fold_list.csv as link_cycle writes them and, on request,
the closure graph as link_cycle.write_closure_graph writes it (named by the receipt) with the
closure report tools/closure_report.py makes of it."""
import csv
import hashlib
import io
import json
import sys
import time
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))
import cycle_artifacts as ca  # noqa: E402
import link_cycle as lc  # noqa: E402

COMMIT = "275a758e4cbb1ce58a9b1b65b447413d9252858f"
OTHER = "31d8b0fddd0123456789abcdef0123456789abcd"
B1 = "9e3be919b10ae956e3c8a13995e0d62f2be1d016"
EMPTY = "??_C@_00CNPNBAHC@?$AA@"
NULLCHR = "?TheNullChr@?1??str@AsciiString@@QBEPBDXZ@4DB"
GD = "?TheWritableGlobalData@@3PAVGlobalData@@A"
STATUS_COLS = ["name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason",
               "self_strict", "closed_strict", "closed_strict_pilot_rule", "pinned_strict", "byte_equal",
               "hardcoded", "failure_count", "failures"]
FOLD_COLS = ["retail_rva", "retail_start", "export_names", "linked", "symbols", "rule", "verdict"]
LEDGER = [["address", "size", "section", "kind", "name", "source", "status", "names", "defs", "refs"],
          ["0x00100000", "1", ".rdata", "string", EMPTY, "", "literal", f"{EMPTY};{NULLCHR}", "1", "10"],
          ["0x00200000", "4", ".data", "global", GD, "Code/G.cpp", "provisional", GD, "1", "6"]]
FUNCTIONS = [["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"],
             ["?ok@@YAXXZ", "", "0x00001000", "64", "Code/a.cpp", "matched", ""],
             ["?wire@@YAXXZ", "", "0x00003000", "40", "Code/b.cpp", "matched", ""],
             ["?far@@YAXXZ", "", "0x00002000", "500", "Code/a.cpp", "matched", ""]]
EXPORTS = [["ordinal", "rva", "target_rva", "section", "kind", "name"]]
STATUS = [["?ok@@YAXXZ", "real", "Code/a.cpp", "0x00001000", 64, "0x00001000", 1, "", 1, 1, 1, 1, 1, 0, 0, ""],
          ["?far@@YAXXZ", "real", "Code/a.cpp", "0x00002000", 500, "0x007BBD80", 0,
           "retail start violates section alignment", 1, 1, 1, 1, 0, 0, 0, ""],
          ["?wire@@YAXXZ", "real", "Code/b.cpp", "0x00003000", 40, "0x00003000", 1, "", 0, 0, 0, 0, 0, 0, 2,
           f"data-back:{EMPTY};data-fwd:{GD}"],
          ["?nul@@YAXXZ", "real", "Code/c.cpp", "0x00004000", 24, "0x00004000", 1, "", 0, 0, 0, 0, 0, 0, 1,
           f"data-back:{NULLCHR}"]]
FOLDS = [["0x00100000", "0x00100000", "0", "0x00100000:1;0x00500000:1", f"{EMPTY};{NULLCHR}", "", "reaches stub"]]
# a self-strict row that is placed and still open: it calls ?wire, which fails its own checks
DEP = ["?dep@@YAXXZ", "real", "Code/d.cpp", "0x00005000", 30, "0x00005000", 1, "", 1, 0, 0, 1, 1, 0, 0, ""]
# and one behind two failed nodes (?wire and ?nul): in no root's gain
BOTH = ["?both@@YAXXZ", "real", "Code/e.cpp", "0x00006000", 16, "0x00006000", 1, "", 1, 0, 0, 1, 1, 0, 0, ""]
CLOSURE_STATUS = STATUS + [DEP, BOTH]
CLOSURE_EDGES = {"?dep@@YAXXZ": ["?wire@@YAXXZ"], "?both@@YAXXZ": ["?wire@@YAXXZ", "?nul@@YAXXZ"]}


def csv_text(rows, lineterminator="\r\n"):
    buf = io.StringIO()
    csv.writer(buf, lineterminator=lineterminator).writerows(rows)
    return buf.getvalue()


def write(path, text, newline="\n"):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline=newline) as f:
        f.write(text)


def recent(hours=1.0):
    """A receipt date_utc HOURS before now: a bundle the queues serve as fresh."""
    return time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(time.time() - hours * 3600))


def graph_doc(status, edges):
    """The closure-graph document (link_cycle.closure_graph_doc's shape) of a graph with one
    unit per link_status row and EDGES by row name."""
    key = {row[0]: f"unit:{n}" for n, row in enumerate(status)}
    nodes = {key[row[0]]: {"kind": "unit", "ok": bool(row[8]), "name": row[0], "rva": int(row[3], 16),
                           "source": row[2], "failures": sorted(f for f in row[15].split(";") if f)}
             for row in status}
    return {"schema": lc.CLOSURE_GRAPH_SCHEMA, "bad_targets": ["fill", "stub"], "nodes": dict(sorted(nodes.items())),
            "edges": {key[a]: sorted(key[b] for b in bs if b in key) for a, bs in sorted(edges.items())
                      if a in key and any(b in key for b in bs)},
            "rows": sorted(([row[0], row[1], row[2], int(row[3], 16), row[4], key[row[0]], int(row[6]), int(row[8])]
                            for row in status), key=lambda r: (r[3], r[0], r[2], r[1], r[4]))}


def write_closure(run, dest=None, replayed=False, edges=None, status=None):
    """closure_roots.json and closure_blockers.csv for RUN, by tools/closure_report.py: from
    the run's receipt-bound graph (closure_report.from_graph) or, REPLAYED, from a rebuilt
    graph labelled as a replay. Returns the roots document."""
    import closure_report as cr
    run = Path(run)
    if replayed:
        receipt = json.loads((run / "receipt.json").read_text(encoding="utf-8"))
        doc = graph_doc(status or CLOSURE_STATUS, CLOSURE_EDGES if edges is None else edges)
        roots, table, _ = cr.report(
            cr.graph_from_doc(doc), receipt, cr.status_rows(run / "link_status.csv"),
            {"source": "replay", "graph": {"bound": False, "label": cr.REPLAYED, "sha256": "0" * 64},
             "row_columns": ("name", "kind", "source", "retail_rva", "size", "placed", "self_strict",
                             "closed_strict")})
    else:
        roots, table, _ = cr.from_graph(run)
    dest = Path(dest or run)
    dest.mkdir(parents=True, exist_ok=True)
    (dest / cr.ROOTS).write_bytes(roots)
    (dest / cr.BLOCKERS).write_bytes(table)
    return json.loads(roots)


def make_run(base, *, commit=COMMIT, date_utc="2026-10-11 16:43:32", total=8795, status=None, ledger=None,
             snapshot=True, rank_files=False, tool_digest=None, authoritative=True, credit=64,
             rules="link-cycle-2", closure=False, edges=None):
    """The run directory (snapshot/<sha10>/build/link_cycle) of a stamped, authoritative
    receipt. CLOSURE: True writes the closure graph, names it in the receipt and writes the
    report made from it; "graph" writes and names the graph only; "replay" writes a report
    labelled as a replay for a receipt that names no graph."""
    snap = Path(base) / commit[:10]
    write(snap / "reverse/data_ledger.csv", csv_text(ledger or LEDGER, "\n"))
    write(snap / "reverse/functions.csv", csv_text(FUNCTIONS, "\n"))
    write(snap / "reverse/exports.csv", csv_text(EXPORTS, "\n"))
    write(snap / "tools/README", "a tree file\n")
    run = snap / "build" / "link_cycle"
    run.mkdir(parents=True)
    rows = status or STATUS
    # link_cycle's csv.writer keeps the module default \r\n line ends; the receipt hashes those bytes
    write(run / "link_status.csv", csv_text([STATUS_COLS] + rows), newline="")
    write(run / "data_fold_list.csv", csv_text([FOLD_COLS] + FOLDS), newline="")
    if rank_files:
        write(run / "data_back_rank.txt", "the producer's own report\n")
        write(run / "data_back_rank.json", json.dumps({"mode": "status", "addresses": []}) + "\n")
    tree = lc.tree_manifest(snap)
    if snapshot:
        write(snap / "SNAPSHOT.json", json.dumps({"commit": commit, "submodules": {"reference/open-bfme-1": B1},
                                                  "tree_manifest": tree}))
    unique = {"rows": 1, "bytes": credit, "unique_bytes": credit, "pct_text": 0.0}
    receipt = {"commit": commit, "submodules": {"reference/open-bfme-1": B1}, "snapshot": True,
               "tree_manifest": tree, "tool_digest": tool_digest or lc.tool_digest(),
               "measure_env": {"python": "3.14.7"}, "inputs": {"functions_csv": ca.text_sha256(
                   snap / "reverse/functions.csv")},
               "tool": "link_cycle", "rules": rules, "shadow_rules": ["data-fold-1"],
               "date_utc": date_utc, "objects": 4, "canon_rules": "coff-canon-1",
               "objects_canon_digest": "c" * 64, "provenance_canon_sha256": "d" * 64,
               "series": {"real": {"placed": unique, "placed_self_strict": unique, "placed_closed_strict": unique},
                          "credit_unique_bytes": credit,
                          "link_status_sha256": hashlib.sha256((run / "link_status.csv").read_bytes()).hexdigest()},
               "authoritative": authoritative, "seconds": {"total": total}}
    if closure in (True, "graph"):
        lc.write_closure_graph(run / lc.CLOSURE_GRAPH, graph_doc(rows, CLOSURE_EDGES if edges is None else edges))
        receipt["closure_graph_sha256"] = lc.sha256(run / lc.CLOSURE_GRAPH)
    lc.stamp_cores(receipt)
    write(run / "receipt.json", json.dumps(receipt, indent=1))
    if closure is True:
        write_closure(run)
    elif closure == "replay":
        write_closure(run, replayed=True, edges=edges, status=rows)
    return run


def bundle(run, out, producer="x", **kw):
    """publish_cycle.make_bundle for RUN, created one minute after the run's measurement ended
    (not at the wall clock: a fixture measured "in the future" is still bundled after it)."""
    import publish_cycle as pc
    receipt = json.loads((Path(run) / "receipt.json").read_text(encoding="utf-8"))
    kw.setdefault("now", ca.parse_utc(receipt["date_utc"]) + 60)
    return pc.make_bundle(run, out, producer, **kw)
