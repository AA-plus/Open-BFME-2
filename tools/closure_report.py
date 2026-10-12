#!/usr/bin/env python3
"""What blocks closed-strict credit: closure roots of one link_cycle run, ranked.

link_cycle credits a row when it is placed, self-strict and CLOSED: its unit
reaches, through the closure graph (units, certified twins, datums, EH thunks),
only nodes that pass. link_status.csv records the verdict and no edge, so a row
that is self-strict and still open shows an empty failure text. This report
names what such rows wait for. It is published in the link-cycle bundle
(tools/publish_cycle.py) and served by `tools/repair_queue.py link --closure`.

WHICH GRAPH. Equal verdicts do not prove equal edges, so the report says where
its graph came from, and the queue repeats it:

  graph   link_cycle's measure() wrote closure_graph.json.gz (the nodes with
          their verdicts, the edges and the rows it judged) and its receipt
          names that file's sha256 (closure_graph_sha256). `graph RUN_DIR`
          refuses a file that is not the one the receipt names, then analyses
          it. Label: "measured graph, bound to the receipt". Runs anywhere.
  replay  for a run measured before link_cycle wrote the graph: rebuild it on
          the measuring machine with the snapshot's own link_cycle. Before AND
          after, the snapshot marker and re-walked tree, the ledger input
          hashes, provenance.json, every object's identity, the quarantine list
          and the retail image must be the receipt's; the link artifacts
          (base.exe, base.map, shft.exe) are hashed before and after (the
          receipt holds no hash for them: recorded, not bound). The rebuilt
          measure must reproduce the receipt's credit and EVERY column this
          tool can derive of every link_status.csv row (name, kind, source,
          address, size, linked address, placed, self_strict, closed_strict,
          hardcoded, failure count and text). Even so the edges are rebuilt, not
          measured. Label: "replayed, graph not receipt-bound".

THE RANKING, narrowly: the CONDITIONAL SINGLE-ADDRESS GAIN of a root.

  A blocker is a node the graph holds as failed, a filler or stub, or an edge
  target the graph does not hold. A ROOT is one retail address with every
  failed unit, twin and datum node at it; fillers, stubs and unknown targets
  are never scored: under link_cycle's closure they close nothing even when
  they pass.

  conditional_gain_bytes(root) = credit(G with the root's nodes passing) - credit(G)

  on the FROZEN graph G of the measured commit: every edge and every other
  verdict unchanged. In unique retail bytes, like the credit. It is the union of
    beneficiaries  placed real rows that are self-strict and open, and whose
                   every reachable blocker belongs to this root; and
    direct rows    the root's own placed real rows that fail their own checks,
                   when nothing else the root reaches is a blocker
  less the bytes already credited.

BLOCKER SETS. closure_blockers.csv keeps, per open or failing placed real row,
the COMPLETE set of roots and leaves it reaches when that set has at most
SET_CAP members (`roots`, ';' joined; `reach` is its size), and `reach` ">N"
with no set beyond the cap: truncated, not unknown to be small. Nothing here
scores a set; the sets are kept so that a reviewed multi-root packet can be
scored on the frozen graph later (joint_gain).

LIMITS (stated in the report and by the queue):
  * conditional, not predicted: a real fix changes code, relocations and edges;
    the figure is not a repair proof and not an expected net credit;
  * "passing" means ALL of the root's own failures are gone (they are listed);
  * single-root scores omit joint-only gains and may overlap: do not add them.
    Most of the closure bucket sits behind two or more roots and is in no
    root's score;
  * a root is where a failure is recorded, not its cause or its repair site;
  * fillers, stubs and unknown targets are listed (`unscored`), never scored;
  * it describes the measured commit, not origin/master;
  * a repair is DONE only when a later authoritative cycle shows the root gone
    and its beneficiaries closed; predicted and observed are reported apart.

  python3 tools/closure_report.py graph RUN_DIR --out DIR [--verify 25]
  python3 tools/closure_report.py replay ~/lcs/<sha10> --out DIR [--verify 25]
        (the measuring machine only: needs the run's base.exe, map and objects)
  python3 tools/closure_report.py show closure_roots.json[.gz] [--limit 10]
"""
import argparse
import bisect
import collections
import csv
import gzip
import hashlib
import io
import json
import os
import sys
import time
from pathlib import Path

SCHEMA = "closure-report/2"
ALGORITHM = "conditional-single-address-gain/1"
GRAPH_SCHEMA = "closure-graph/1"             # link_cycle.CLOSURE_GRAPH_SCHEMA
GRAPH_FILE = "closure_graph.json.gz"         # link_cycle.CLOSURE_GRAPH
ROOTS = "closure_roots.json"
BLOCKERS = "closure_blockers.csv"
FORBIDDEN = ("fill", "stub")                 # link_cycle.greatest_closure's bad_targets
SET_CAP = 6                                  # complete blocker sets are kept up to this size
OVER = None                                  # a blocker set larger than the cap
BLOCKER_COLUMNS = ("name", "source", "retail_rva", "size", "bucket", "reach", "roots", "scored", "witness")
BOUND = "measured graph, bound to the receipt"
REPLAYED = "replayed, graph not receipt-bound"
STATUS_COMPARED = ("name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "self_strict",
                   "closed_strict", "hardcoded", "failure_count", "failures")
LIMITS = (
    "conditional on the frozen graph of the measured commit (every edge and every other verdict unchanged): "
    "not a repair proof and not an expected net credit",
    "a root 'passing' means all of its own listed failures are gone, not one of them",
    "single-root scores omit joint-only gains and may overlap: do not add them; a row behind two or more roots is "
    "in no root's score",
    "fillers, stubs and targets the graph does not hold are listed as unscored and never ranked: they close nothing "
    "even when they pass",
    "a root is the node where a failure is recorded (a failing unit, twin or datum), not its cause or its repair "
    "site: one datum repair that clears data-back in many units at once is ranked by data_back_rank, not here",
    "placed real rows only; closed-strict rows that are not placed are a separate bucket (summary.buckets)",
    "a repair is done only when a later authoritative cycle shows the root gone and its beneficiaries closed",
)


class ReportError(Exception):
    """The report cannot be produced or read."""


# ---------------------------------------------------------------- spans

def merge(spans):
    """Disjoint sorted [start, end) spans covering the union."""
    out = []
    for s, e in sorted(spans):
        if e <= s:
            continue
        if out and s <= out[-1][1]:
            if e > out[-1][1]:
                out[-1][1] = e
        else:
            out.append([s, e])
    return out


def total(merged):
    return sum(e - s for s, e in merged)


def unique_bytes(spans):
    return total(merge(spans))


def uncovered(spans, base, base_starts):
    """Bytes of the union of SPANS outside BASE (merged, with its starts)."""
    gain = 0
    for s, e in merge(spans):
        i = max(bisect.bisect_right(base_starts, s) - 1, 0)
        cur = s
        while i < len(base) and base[i][0] < e:
            bs, be = base[i]
            if be > cur:
                if bs > cur:
                    gain += bs - cur
                cur = max(cur, be)
            i += 1
        if cur < e:
            gain += e - cur
    return gain


# ---------------------------------------------------------------- the graph

def scorable(n, ok, forbidden=FORBIDDEN):
    """A node whose passing can close something: held by the graph, failed, not a filler or stub."""
    return n in ok and not ok[n] and n[0] not in forbidden


def reverse_edges(edges):
    rev = collections.defaultdict(set)
    for n, ts in edges.items():
        for t in ts:
            rev[t].add(n)
    return rev


def blockers_of(ok, edges, forbidden=FORBIDDEN):
    """Every blocker: failed nodes, and edge targets that are forbidden or unknown to the graph.
    A filler or stub that nothing reaches blocks nothing and is not one."""
    out = {n for n, v in ok.items() if not v}
    for ts in edges.values():
        for t in ts:
            if t[0] in forbidden or t not in ok:
                out.add(t)
    return out


def propagate(blockers, rev, group, cap=SET_CAP):
    """{node: frozenset of groups | OVER} for every node that is, or reaches, a blocker: the
    complete set of blocker groups it reaches when that has at most CAP members, else OVER.
    A node absent from the result reaches none: it is closed."""
    state = {n: frozenset((group(n),)) for n in blockers}
    work = collections.deque(state)
    queued = set(state)
    while work:
        n = work.popleft()
        queued.discard(n)
        incoming = state[n]
        for parent in rev.get(n, ()):
            old = state.get(parent, frozenset())
            if old is OVER:
                continue
            new = OVER if incoming is OVER else old | incoming
            if new is not OVER and len(new) > cap:
                new = OVER
            if new is OVER or len(new) != len(old):
                state[parent] = new
                if parent not in queued:
                    work.append(parent)
                    queued.add(parent)
    return state


def reference_closure(ok, edges, bad_targets=FORBIDDEN):
    """link_cycle.greatest_closure, copied so that a report can be checked in a checkout
    whose link_cycle is not the run's: nodes that are ok and reach only ok nodes (cycles
    optimistic); an edge to a filler, a stub or a node the graph does not hold closes nothing.
    tools/tests/test_closure_report.py holds it equal to link_cycle's on random graphs."""
    closed = {n for n in ok if ok[n]}
    for n in list(closed):
        if any(t[0] in bad_targets or t not in ok for t in edges.get(n, ())):
            closed.discard(n)
    rev = reverse_edges(edges)
    work = [n for n in ok if n not in closed]
    while work:
        t = work.pop()
        for n in rev.get(t, ()):
            if n in closed:
                closed.discard(n)
                work.append(n)
    return closed


def distances(blockers, rev):
    """{node: edges on a shortest path to a blocker} for every node that reaches one."""
    dist = {n: 0 for n in blockers}
    work = collections.deque(blockers)
    while work:
        n = work.popleft()
        for parent in rev.get(n, ()):
            if parent not in dist:
                dist[parent] = dist[n] + 1
                work.append(parent)
    return dist


def witness(n, dist, edges, ident, limit=12):
    """The ids along a shortest path from N to its nearest blocker, ' > ' joined; among
    equally near next nodes the one with the smallest id, so two runs agree."""
    ids = [ident(n)]
    while dist[n] and len(ids) <= limit:
        n = min((t for t in edges.get(n, ()) if dist.get(t) == dist[n] - 1), key=ident)
        ids.append(ident(n))
    if dist[n]:
        ids.append("...")
    return " > ".join(ids)


def analyze(ok, edges, rows, describe, *, forbidden=FORBIDDEN, affected=True, cap=SET_CAP):
    """(body, blocker_rows) of the closure report.

    ok, edges   link_cycle.closure_graph's.
    rows        [{"node", "name", "source", "rva", "size", "real", "placed", "self_strict"}], one per ledger row.
    describe    node -> {"id", "kind", "group", ...}: a deterministic id, and the retail-address group the
                node's failure is repaired at; further keys are copied into the report.
    """
    cache = {}

    def desc(n):
        if n not in cache:
            cache[n] = describe(n)
        return cache[n]

    def ident(n):
        return desc(n)["id"]

    def group(n):
        return desc(n)["group"] if scorable(n, ok, forbidden) else "leaf:" + desc(n)["id"]

    rev = reverse_edges(edges)
    blockers = blockers_of(ok, edges, forbidden)
    state = propagate(blockers, rev, group, cap)
    single = propagate(blockers, rev, lambda n: n, 1)
    dist = distances(blockers, rev)
    members = collections.defaultdict(list)
    for n in blockers:
        members[group(n)].append(n)

    live = [r for r in rows if r["real"] and r["placed"]]
    span = (lambda r: (r["rva"], r["rva"] + r["size"]))
    credited = merge(span(r) for r in live if r["self_strict"] and r["node"] not in state)
    starts = [s for s, _ in credited]
    credit = total(credited)
    gain_rows = collections.defaultdict(lambda: {"beneficiary": [], "direct": []})
    out_rows = []
    buckets = collections.defaultdict(list)
    reach_spans = collections.defaultdict(list)
    by_size = collections.defaultdict(list)
    for r in live:
        if r["self_strict"] and r["node"] not in state:
            continue
        st = state[r["node"]]
        bucket = "closure-blocked" if r["self_strict"] else "failing"
        buckets[bucket].append(span(r))
        one = next(iter(st)) if st is not OVER and len(st) == 1 else None
        scored = one is not None and not one.startswith("leaf:")
        if one is not None:                       # a failing row of a unit that reaches nothing else: its own root
            gain_rows[one]["beneficiary" if r["self_strict"] else "direct"].append(r)
        reach = f">{cap}" if st is OVER else str(len(st))
        if r["self_strict"]:
            reach_spans["one scored root" if scored else "one unscored leaf" if one is not None
                        else "two or more"].append(span(r))
            by_size[reach].append(span(r))
        out_rows.append({"name": r["name"], "source": r["source"], "retail_rva": "0x%08X" % r["rva"],
                         "size": r["size"], "bucket": bucket, "reach": reach,
                         "roots": "" if st is OVER else ";".join(sorted(st)),
                         "scored": "" if st is OVER else int(not any(g.startswith("leaf:") for g in st)),
                         "witness": witness(r["node"], dist, edges, ident)})
    out_rows.sort(key=lambda r: (r["retail_rva"], r["name"], r["source"], r["size"]))
    buckets["closed-strict-unplaced"] = [span(r) for r in rows if r["real"] and not r["placed"] and r["self_strict"]
                                         and r["node"] not in state]

    aff = {}
    if affected:                                  # self-strict open rows that reach the root at all
        open_by_node = collections.defaultdict(list)
        for r in live:
            if r["self_strict"] and r["node"] in state:
                open_by_node[r["node"]].append(r)
        for g in gain_rows:
            if g.startswith("leaf:"):
                continue
            seen = set(members[g])
            work = list(seen)
            while work:
                for parent in rev.get(work.pop(), ()):
                    if parent not in seen:
                        seen.add(parent)
                        work.append(parent)
            hit = [r for n in seen for r in open_by_node.get(n, ())]
            aff[g] = (len(hit), unique_bytes(span(r) for r in hit))

    roots, unscored = [], []
    for g, rs in gain_rows.items():
        ben, direct = rs["beneficiary"], rs["direct"]
        nodes = sorted((dict(desc(n)) for n in members[g]), key=lambda d: d["id"])
        for d in nodes:
            d.pop("group", None)
        entry = {"root": g, "nodes": nodes,
                 "beneficiary_rows": len(ben), "beneficiary_bytes": unique_bytes(span(r) for r in ben)}
        if g.startswith("leaf:"):
            entry.update(scored=False, sole_blocked_bytes=entry.pop("beneficiary_bytes"),
                         sole_blocked_rows=entry.pop("beneficiary_rows"))
            if entry["sole_blocked_rows"]:
                unscored.append(entry)
            continue
        entry.update(scored=True, direct_rows=len(direct), direct_bytes=unique_bytes(span(r) for r in direct),
                     conditional_gain_bytes=uncovered([span(r) for r in ben + direct], credited, starts),
                     failures=sorted({f for d in nodes for f in d.get("failures", ())}),
                     verified=None)
        if g in aff:
            entry["affected_rows"], entry["affected_bytes"] = aff[g]
        if entry["conditional_gain_bytes"]:
            roots.append(entry)
    roots.sort(key=lambda e: (-e["conditional_gain_bytes"], e["root"]))
    unscored.sort(key=lambda e: (-e["sole_blocked_bytes"], e["root"]))

    by_kind = collections.defaultdict(list)       # node-level cross-check: one failed NODE, no grouping
    for r in live:
        st = single.get(r["node"])
        if r["self_strict"] and st:
            (n,) = st
            by_kind[n[0]].append((n, span(r)))
    cross = {k: {"roots": len({n for n, _ in v}), "sole_blocked_bytes": unique_bytes(s for _, s in v)}
             for k, v in sorted(by_kind.items())}
    scored_groups = {g for g in members if not g.startswith("leaf:")}
    count = (lambda table: {k: {"rows": len(v), "unique_bytes": unique_bytes(v)} for k, v in sorted(table.items())})
    body = {
        "summary": {
            "credit_unique_bytes": credit,
            "buckets": count(buckets),
            "closure_blocked_reach": count(reach_spans),
            "closure_blocked_by_blocker_set_size": dict(count(by_size), cap=cap),
            "blockers": len(blockers), "scored_roots": len(scored_groups),
            "scored_roots_with_gain": len(roots),
            "roots_with_no_beneficiary": sum(1 for e in roots if not e["beneficiary_rows"]),
            "unscored_leaves_solely_blocking": len(unscored),
            "single_node_cross_check": cross,
        },
        "roots": roots,
        "unscored": unscored,
    }
    return body, out_rows


def closed_nodes(ok, edges, forbidden=FORBIDDEN):
    """The nodes this module holds closed: must equal link_cycle.greatest_closure(ok, edges)."""
    state = propagate(blockers_of(ok, edges, forbidden), reverse_edges(edges), lambda n: n, 1)
    return {n for n, v in ok.items() if v and not any(t in state for t in edges.get(n, ()))}


def credit_of(ok, edges, rows, forced=(), closure=reference_closure):
    """The credit of the graph with the FORCED nodes passing, by CLOSURE."""
    forced = set(forced)
    table = dict(ok)
    table.update((n, True) for n in forced)
    closed = closure(table, edges)
    return unique_bytes((r["rva"], r["rva"] + r["size"]) for r in rows
                        if r["real"] and r["placed"] and r["node"] in closed
                        and (r["self_strict"] or r["node"] in forced))


def forced_gain(ok, edges, rows, nodes, closure=reference_closure):
    """credit(graph with NODES passing) - credit(graph), by CLOSURE run twice: the
    independent check of a root's conditional_gain_bytes, and the joint gain of several
    roots' nodes (joint_gain)."""
    return credit_of(ok, edges, rows, nodes, closure) - credit_of(ok, edges, rows, (), closure)


def joint_gain(graph, roots):
    """The exact gain on the frozen GRAPH (load_graph) of every failed node at ROOTS (retail
    address groups, as closure_blockers.csv spells them) passing together. For scoring a
    reviewed packet; nothing in this tool enumerates or ranks sets."""
    ok, edges, rows, describe = graph
    want = set(roots)
    nodes = [n for n in ok if scorable(n, ok) and describe(n)["group"] in want]
    return forced_gain(ok, edges, rows, nodes)


# ---------------------------------------------------------------- the measured graph

def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def read_bytes(path):
    data = Path(path).read_bytes()
    return gzip.decompress(data) if data[:2] == b"\x1f\x8b" else data


def graph_from_doc(doc):
    """(ok, edges, rows, describe) of a closure-graph document (link_cycle.closure_graph_doc)."""
    if not isinstance(doc, dict) or doc.get("schema") != GRAPH_SCHEMA:
        raise ReportError(f"closure graph schema {doc.get('schema') if isinstance(doc, dict) else None!r}, expected "
                          f"{GRAPH_SCHEMA!r}")
    if tuple(doc.get("bad_targets") or ()) != FORBIDDEN:
        raise ReportError(f"closure graph bad_targets {doc.get('bad_targets')!r}: not this tool's closure rule")
    info = doc["nodes"]

    def node(key):
        return (info[key]["kind"] if key in info else key.split(":", 1)[0], key)
    ok = {node(k): bool(v["ok"]) for k, v in info.items()}
    edges = {node(k): {node(t) for t in ts} for k, ts in doc["edges"].items()}
    rows = [{"name": name, "kind": kind, "source": source, "rva": rva, "size": size, "node": node(key),
             "real": kind == "real", "placed": bool(placed), "self_strict": bool(strict)}
            for name, kind, source, rva, size, key, placed, strict in doc["rows"]]

    def describe(n):
        d = info.get(n[1])
        if d is None:                             # an edge target the graph does not hold
            parts = n[1].split(":")
            ident = parts[0] + ":" + ":".join(("0x%08X" % int(p)) if p.lstrip("-").isdigit() else p for p in parts[1:])
            return {"id": ident, "kind": n[0], "group": ident}
        rva = d.get("rva")
        where = None if rva is None else ("0x%08X" % rva if rva >= 0 else "-0x%08X" % -rva)
        if n[0] == "unit":
            ident = f"unit:{where}:{d['name']}"
        elif n[0] == "twin":
            ident = "twin:%s:%s@0x%08X" % (where, d.get("name") or "?", d["linked"])
        elif n[0] == "datum":
            ident = "datum:%s:%d:%s@0x%08X" % (where, d["size"], d["name"], d["linked"])
        else:
            ident = n[0] + ":" + ":".join("0x%08X" % int(p) for p in n[1].split(":")[1:])
        out = {"id": ident, "kind": n[0], "group": where if rva is not None and rva >= 0 else ident,
               "failures": list(d.get("failures") or ())}
        for key in ("name", "source", "object", "size"):
            if d.get(key) not in (None, ""):
                out[key] = d[key]
        if where is not None:
            out["retail_rva"] = where
        return out
    return ok, edges, rows, describe


def load_graph(path, want_sha256=None):
    """(ok, edges, rows, describe) of closure_graph.json.gz; with WANT_SHA256 the file must
    be the one a receipt names (closure_graph_sha256)."""
    try:
        raw = Path(path).read_bytes()
    except OSError as e:
        raise ReportError(f"{path}: no closure graph ({e})") from None
    if want_sha256 is not None and sha256_bytes(raw) != want_sha256:
        raise ReportError(f"{path}: sha256 {sha256_bytes(raw)[:16]} is not the receipt's closure_graph_sha256 "
                          f"{str(want_sha256)[:16]}: not the graph that run measured")
    try:
        doc = json.loads(gzip.decompress(raw) if raw[:2] == b"\x1f\x8b" else raw)
    except (OSError, EOFError, ValueError) as e:
        raise ReportError(f"{path}: not a readable closure graph ({e})") from None
    return graph_from_doc(doc)


def status_rows(path):
    """link_status.csv rows (plain or gzip) as dicts."""
    text = read_bytes(path).decode("utf-8")
    return list(csv.DictReader(io.StringIO(text, newline="")))


def check_rows(rows, closed, status, columns=("name", "kind", "source", "retail_rva", "size", "placed", "self_strict",
                                               "closed_strict")):
    """Every row of the graph against link_status.csv on COLUMNS, as multisets; ReportError
    naming how many differ. `rows` may carry further link_status columns (the replay's)."""
    def mine(r):
        full = {"name": r["name"], "kind": r["kind"], "source": r["source"], "retail_rva": "0x%08X" % r["rva"],
                "size": str(r["size"]), "placed": str(int(r["placed"])), "self_strict": str(int(r["self_strict"])),
                "closed_strict": str(int(r["self_strict"] and r["node"] in closed))}
        full.update(r.get("status") or {})
        return tuple(full[c] for c in columns)
    got = collections.Counter(mine(r) for r in rows)
    want = collections.Counter(tuple(r[c] for c in columns) for r in status)
    if got != want:
        off = sum(((got - want) + (want - got)).values())
        some = sorted((got - want).elements())[:2] + sorted((want - got).elements())[:2]
        raise ReportError(f"{off} row record(s) differ from link_status.csv on {', '.join(columns)} (e.g. "
                          f"{some}): an unreproduced graph is not attributed")
    return len(status)


def report(graph, receipt, status, binding, verify=25, log=None):
    """(roots bytes, blockers bytes, facts): check GRAPH against the receipt's credit and
    every row of STATUS, analyse it, and re-prove the top VERIFY roots by a forced closure."""
    ok, edges, rows, describe = graph
    closed = reference_closure(ok, edges)
    if closed_nodes(ok, edges) != closed:
        raise ReportError("this module's one-pass closure is not the reference closure")
    credit = unique_bytes((r["rva"], r["rva"] + r["size"]) for r in rows
                          if r["real"] and r["placed"] and r["self_strict"] and r["node"] in closed)
    want = (receipt.get("series") or {}).get("credit_unique_bytes")
    if credit != want:
        raise ReportError(f"the graph credits {credit}, the receipt {want}: an unreproduced graph is not attributed")
    compared = check_rows(rows, closed, status, binding.pop("row_columns"))
    body, blocker_rows = analyze(ok, edges, rows, describe)
    if body["summary"]["credit_unique_bytes"] != credit:
        raise ReportError("the report's credit is not the graph's")
    by_group = collections.defaultdict(list)
    for n in ok:
        if scorable(n, ok):
            by_group[describe(n)["group"]].append(n)
    checked = 0
    for e in body["roots"][:max(verify, 0)]:
        got = forced_gain(ok, edges, rows, by_group[e["root"]])
        if got != e["conditional_gain_bytes"]:
            raise ReportError(f"root {e['root']}: gain {e['conditional_gain_bytes']} but forcing its nodes to pass "
                              f"and re-running the closure gives {got}")
        e["verified"] = "forced-closure"
        checked += 1
    if log:
        log(f"credit {credit} and {compared} link_status rows reproduced; {checked} root(s) re-proved by a forced "
            "closure")
    binding = dict(binding, commit=receipt["commit"], receipt_core_sha256=receipt.get("core_sha256"),
                   link_status_sha256=(receipt.get("series") or {}).get("link_status_sha256"),
                   link_cycle_tool_digest=receipt.get("tool_digest"), rules=receipt.get("rules"),
                   tool={"path": "tools/closure_report.py",
                         "text_sha256": sha256_bytes(Path(__file__).read_bytes().replace(b"\r\n", b"\n"))})
    binding["checks"] = dict(binding.get("checks") or {}, credit_reproduced=credit,
                             link_status_rows_reproduced=compared, roots_verified_by_forced_closure=checked,
                             graph_nodes=len(ok), graph_edges=sum(len(v) for v in edges.values()))
    roots, table = document(body, blocker_rows, binding)
    return roots, table, {"credit": credit, "roots": len(body["roots"])}


def from_graph(run_dir, verify=25, log=None):
    """The report of a run whose measure wrote the graph: RUN_DIR holds receipt.json,
    link_status.csv and closure_graph.json.gz, and the receipt names the graph's sha256."""
    run = Path(run_dir)
    try:
        receipt = json.loads((run / "receipt.json").read_text(encoding="utf-8"))
    except (OSError, ValueError) as e:
        raise ReportError(f"{run}: no readable receipt.json ({e})") from None
    want = receipt.get("closure_graph_sha256")
    if not want:
        raise ReportError(f"{run / 'receipt.json'} names no closure_graph_sha256: this run was measured before "
                          "link_cycle wrote its graph (use `replay` on the measuring machine; its report is "
                          f"labelled '{REPLAYED}')")
    status_path = run / "link_status.csv"
    if sha256_bytes(status_path.read_bytes()) != (receipt.get("series") or {}).get("link_status_sha256"):
        raise ReportError(f"{status_path} is not the file the receipt hashed")
    graph = load_graph(run / GRAPH_FILE, want)
    return report(graph, receipt, status_rows(status_path),
                  {"source": "graph", "graph": {"bound": True, "label": BOUND, "sha256": want},
                   "row_columns": ("name", "kind", "source", "retail_rva", "size", "placed", "self_strict",
                                   "closed_strict")}, verify, log)


# ---------------------------------------------------------------- files

def blockers_csv(rows):
    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\n")
    w.writerow(BLOCKER_COLUMNS)
    for r in rows:
        w.writerow([r[c] for c in BLOCKER_COLUMNS])
    return buf.getvalue().encode("utf-8")


def document(body, blocker_rows, binding):
    """(closure_roots.json bytes, closure_blockers.csv bytes): the roots file binds the run
    (BINDING: commit, receipt core, link_status hash, where the graph came from) and the
    blockers file's hash."""
    table = blockers_csv(blocker_rows)
    doc = {"schema": SCHEMA, "algorithm": ALGORITHM,
           "definition": "conditional_gain_bytes(root) = credit(graph with every failed node at the root's retail "
                         "address passing) - credit(graph), in unique retail bytes, on the frozen closure graph of "
                         "the measured commit: beneficiaries (placed real self-strict open rows whose every "
                         "reachable blocker is this root) plus the root's own failing placed real rows when the root "
                         "reaches no other blocker, less bytes already credited",
           "limits": list(LIMITS),
           "blockers": {"file": BLOCKERS, "sha256": sha256_bytes(table), "rows": len(blocker_rows),
                        "columns": list(BLOCKER_COLUMNS), "set_cap": SET_CAP,
                        "roots_column": f"the complete set of roots and leaves the row reaches, ';' joined, when it "
                                        f"has at most {SET_CAP} members; empty with reach '>{SET_CAP}' beyond that "
                                        "(truncated)"},
           **binding, **body}
    return (json.dumps(doc, indent=1, sort_keys=True) + "\n").encode("utf-8"), table


def load_roots(path):
    """The roots document (plain or gzip); ReportError when it is not one this code reads."""
    try:
        doc = json.loads(read_bytes(path).decode("utf-8"))
    except (OSError, ValueError, EOFError) as e:
        raise ReportError(f"{path}: not a readable closure report ({e})") from None
    if not isinstance(doc, dict) or doc.get("schema") != SCHEMA or doc.get("algorithm") != ALGORITHM:
        raise ReportError(f"{path}: schema {doc.get('schema') if isinstance(doc, dict) else None!r}, algorithm "
                          f"{doc.get('algorithm') if isinstance(doc, dict) else None!r}; this checkout reads "
                          f"{SCHEMA!r}, {ALGORITHM!r}")
    graph = doc.get("graph") or {}
    if graph.get("label") not in (BOUND, REPLAYED) or bool(graph.get("bound")) != (graph.get("label") == BOUND):
        raise ReportError(f"{path}: does not say where its graph came from ({graph.get('label')!r})")
    return doc


def root_line(e):
    """(name, source) a root is best known by: its first unit node, else its first node."""
    nodes = e.get("nodes") or [{}]
    best = next((d for d in nodes if d.get("kind") == "unit"), nodes[0])
    return best.get("name") or best.get("id") or e["root"], best.get("source") or ""


def render(doc, limit=10, out=None):
    out = out or sys.stdout
    s = doc["summary"]
    print(f"closure roots of {doc.get('commit', '?')[:12]} (credit {s['credit_unique_bytes']:,} B): "
          f"{s['scored_roots_with_gain']} scored root(s) with a gain, {s['roots_with_no_beneficiary']} of them with "
          f"no beneficiary; graph: {doc['graph']['label']}", file=out)
    for k, v in s["buckets"].items():
        print(f"  bucket {k}: {v['rows']} rows, {v['unique_bytes']:,} B", file=out)
    for k, v in s["closure_blocked_reach"].items():
        print(f"  closure-blocked rows behind {k}: {v['rows']} rows, {v['unique_bytes']:,} B", file=out)
    sizes = {k: v for k, v in s["closure_blocked_by_blocker_set_size"].items() if k != "cap"}
    print("  closure-blocked bytes by blocker-set size: "
          + ", ".join(f"{k}: {v['unique_bytes']:,}" for k, v in sorted(sizes.items(), key=lambda kv: (len(kv[0]), kv[0]))),
          file=out)
    for e in doc["roots"][:limit]:
        name, source = root_line(e)
        print(f"  {e['conditional_gain_bytes']:>7}B {e['root']} {name[:80]}", file=out)
        print(f"         {source or '(no unit)'}: {len(e['failures'])} failure(s) {'; '.join(e['failures'])[:150]}",
              file=out)
        print(f"         beneficiaries {e['beneficiary_rows']} rows {e['beneficiary_bytes']} B; direct "
              f"{e['direct_rows']} rows {e['direct_bytes']} B; {len(e['nodes'])} node(s)"
              + (f"; verified {e['verified']}" if e.get("verified") else ""), file=out)


# ---------------------------------------------------------------- replay (the measuring machine, older runs)

def _graph_doc(m, recs, hard, ok, edges):
    """link_cycle.closure_graph_doc, for a snapshot whose link_cycle predates it
    (tools/tests/test_closure_report.py holds the two equal)."""
    def key(n):
        def flat(v):
            for x in v:
                if isinstance(x, tuple):
                    yield from flat(x)
                else:
                    yield str(x)
        return ":".join(flat(n))
    nodes, rows = {}, []
    for rec in recs:
        r, u = rec["row"], rec["unit"]
        n = ("unit", u["id"])
        d = nodes.setdefault(key(n), {"kind": "unit", "ok": bool(ok[n]), "name": u.get("head") or r["name"],
                                      "rva": r["rva"], "source": r["source"], "failures": set()})
        d["rva"] = min(d["rva"], r["rva"])
        d["failures"].update(rec["fails"])
        if id(rec) in hard:
            d["failures"].add(f"shift:{hard[id(rec)]}")
        if not rec["measured"]:
            d["failures"].add("unmeasured")
        rows.append([r["name"], r["kind"], r["source"], r["rva"], r["size"], key(n), int(bool(rec["placed"])),
                     int(bool(rec["measured"] and not rec["fails"]))])
    for n, v in ok.items():
        kind = n[0]
        if kind == "unit":
            continue
        d = nodes[key(n)] = {"kind": kind, "ok": bool(v), "failures": set()}
        if kind == "twin":
            good, why = m.twins[(n[1], n[2])]
            sym = m.sym_at(n[1])
            d.update(rva=n[2], linked=n[1], name=sym[1] if sym else "", object=sym[2] if sym else "")
            d["failures"].update((m.twin_fails.get((n[1], n[2])) or [why]) if not good else ([] if v else ["shift"]))
        elif kind == "datum":
            node = m.dnodes[n[1]]
            d.update(rva=n[1][1], linked=n[1][0], size=n[1][2], name=node["name"])
            d["failures"].update(node["fails"] or ([] if v else ["shift"]))
        elif not v:
            d["failures"].add("shift")
    for d in nodes.values():
        d["failures"] = sorted(d["failures"])
    return {"schema": GRAPH_SCHEMA, "bad_targets": list(FORBIDDEN), "nodes": dict(sorted(nodes.items())),
            "edges": {key(n): sorted(key(t) for t in ts) for n, ts in sorted(edges.items(), key=lambda kv: key(kv[0]))
                      if ts},
            "rows": sorted(rows, key=lambda r: (r[3], r[0], r[2], r[1], r[4]))}


def file_sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def prove_inputs(lc, snap, out, receipt, when):
    """The receipt-bound inputs of a finished run, re-proved (WHEN: before or after the
    replay); ReportError naming the first that is not the receipt's. Returns what was
    proved and the hashes of the link artifacts the receipt does not bind."""
    def need(what, got, want):
        if got != want:
            raise ReportError(f"{when} the replay, {what} is not the receipt's ({str(got)[:16]} vs "
                              f"{str(want)[:16]}): the run directory no longer holds the measured inputs")
    mark = snap / lc.SNAPSHOT_MARK
    try:
        meta = json.loads(mark.read_text(encoding="utf-8"))
    except (OSError, ValueError) as e:
        raise ReportError(f"{mark}: no readable snapshot marker ({e})") from None
    need("the snapshot marker's commit", meta.get("commit"), receipt["commit"])
    need("the snapshot marker's tree manifest", meta.get("tree_manifest"), receipt.get("tree_manifest"))
    need("the re-walked snapshot tree", lc.tree_manifest(snap), receipt.get("tree_manifest"))
    for key, rel in (("functions_csv", "reverse/functions.csv"), ("symbols_csv", "reverse/symbols.csv"),
                     ("ghidra_functions_csv", "reverse/ghidra_functions.csv")):
        if key in (receipt.get("inputs") or {}):
            need(rel, lc.text_sha256(snap / rel), receipt["inputs"][key])
    need("the retail image", lc.sha256(lc.build.EXE), receipt.get("retail_sha256"))
    need("provenance.json", lc.sha256(out / "provenance.json"), receipt.get("provenance_sha256"))
    prov = json.loads((out / "provenance.json").read_text(encoding="utf-8"))
    present = [snap / p for p in prov]
    objs = lc.Objects(present)
    need("the objects' identities", lc.objects_digest(objs, present), receipt.get("objects_digest"))
    q = json.loads((out / "quarantine.json").read_text())
    quarantine = sorted(q["value"] if isinstance(q, dict) else q)
    need("the quarantine list", lc.digest_of(quarantine), receipt.get("quarantine_sha256"))
    need("the link_cycle tool", lc.tool_digest(), receipt.get("tool_digest"))
    need("link_status.csv", lc.sha256(out / "link_status.csv"), (receipt.get("series") or {}).get("link_status_sha256"))
    artifacts = {name: file_sha256(out / name) for name in (lc.BASE_TAG + ".exe", "base.map", lc.SHIFT_TAG + ".exe")
                 if (out / name).is_file()}
    return {"receipt_bound": ["snapshot marker commit and tree manifest", "re-walked snapshot tree",
                              "ledger input hashes", "retail image", "provenance.json", "object identities",
                              "quarantine list", "link_cycle tool digest", "link_status.csv"],
            "recorded_not_receipt_bound": artifacts}, objs, set(quarantine)


def replay(snapshot, verify=25, log=None):
    """(roots bytes, blockers bytes, facts) for a finished run in SNAPSHOT/build/link_cycle
    whose measure did not write its graph. Read only; see the module text for what is
    re-proved. The report is labelled REPLAYED."""
    log = log or (lambda line: print(f"closure_report: {line}", file=sys.stderr, flush=True))
    snap = Path(snapshot).resolve()
    out = snap / "build" / "link_cycle"
    receipt = json.loads((out / "receipt.json").read_text(encoding="utf-8"))
    if receipt.get("authoritative") is not True:
        raise ReportError(f"{out / 'receipt.json'}: not an authoritative receipt")
    os.environ["LINK_CYCLE_ROOT"] = str(snap)
    sys.dont_write_bytecode = True
    sys.path.insert(0, str(snap / "tools"))
    import link_cycle as lc
    if Path(lc.__file__).resolve().parent != snap / "tools":
        raise ReportError(f"link_cycle was imported from {lc.__file__}, not the snapshot")
    t0 = time.monotonic()
    proved, objs, quarantine = prove_inputs(lc, snap, out, receipt, "before")
    log(f"inputs re-proved against the receipt ({time.monotonic() - t0:.0f} s)")
    units, _ = lc.analyze(lc.census.ledger(), objs)
    _, R, rsecs, rimp = lc.pe_view(lc.build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = lc.load_pins()
    with (snap / "reverse/ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    placed, _, _ = lc.plan_order(units, quarantine, text0, textsz)
    chunks = lc.filler_chunks(placed, [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz],
                              text0, textsz)
    _, I, isecs, limp = lc.pe_view(out / (lc.BASE_TAG + ".exe"))
    names, modified = lc.zz_names(out)
    mapped = lc.read_map((out / "base.map").read_text(encoding="latin-1"), lc.BASE, names)
    ledger_starts = {}
    for u in units:
        for r in u["rows"]:
            ledger_starts[r["rva"]] = max(ledger_starts.get(r["rva"], 0), r["size"])
    for name in modified:
        objs.by_base[names[name]] = out / "zzobj" / name
    m = lc.Measure(units, chunks, mapped, I, R, isecs, rimp, limp, pins, objs, ledger_starts)
    recs = m.run()
    log(f"measure replayed: {len(recs)} rows, {len(units)} units, {time.monotonic() - t0:.0f} s")
    sites, _ = lc.retail_reloc_sites()
    shift = (receipt.get("series") or {}).get("shift") or {}
    sh = lc.Shifted(out, I, isecs, rsecs, True, lc.BASE + shift["delta"] if shift.get("delta") else lc.SHIFT_BASE,
                    {lc.BASE + r["row"]["rva"] for r in recs}, sites)
    hard = {}
    for rec in recs:
        if rec["measured"]:
            why = sh.code(rec["linked"], rec["row"]["size"], rec["masked"], rec["rels"], rec["row"]["rva"])
            if why:
                hard[id(rec)] = why
    ok, edges = lc.closure_graph(m, recs, hard, sh, ledger_starts)
    if reference_closure(ok, edges) != lc.greatest_closure(ok, edges):
        raise ReportError("this module's reference closure is not the snapshot's link_cycle.greatest_closure")
    doc = getattr(lc, "closure_graph_doc", _graph_doc)(m, recs, hard, ok, edges)
    graph = graph_from_doc(json.loads(json.dumps(doc)))
    extra = {}                                    # the further link_status columns, per (row identity)
    for rec in recs:
        r = rec["row"]
        fails = rec["fails"] + ([f"shift:{hard[id(rec)]}"] if id(rec) in hard else [])
        extra.setdefault((r["name"], r["kind"], r["source"], r["rva"], r["size"]), []).append({
            "linked_rva": "" if rec["linked"] is None else "0x%08X" % rec["linked"],
            "hardcoded": str(int(id(rec) in hard)), "failure_count": str(len(fails)),
            "failures": ";".join(f"{k}x{v}" if v > 1 else k for k, v in collections.Counter(fails).items())})
    for row in graph[2]:
        row["status"] = extra[(row["name"], row["kind"], row["source"], row["rva"], row["size"])].pop()
    roots, table, facts = report(
        graph, receipt, status_rows(out / "link_status.csv"),
        {"source": "replay", "graph": {"bound": False, "label": REPLAYED,
                                       "sha256": sha256_bytes(json.dumps(doc, sort_keys=True,
                                                                         separators=(",", ":")).encode())},
         "row_columns": STATUS_COMPARED, "checks": {"inputs": proved}}, verify, log)
    again, _, _ = prove_inputs(lc, snap, out, receipt, "after")
    if again != proved:
        raise ReportError("the link artifacts changed during the replay")
    log(f"inputs re-proved again after the replay ({time.monotonic() - t0:.0f} s)")
    return roots, table, dict(facts, seconds=round(time.monotonic() - t0))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("graph", help="the report of a run whose measure wrote closure_graph.json.gz")
    g.add_argument("run_dir", help="holds receipt.json, link_status.csv and closure_graph.json.gz")
    r = sub.add_parser("replay", help="the report of an older finished run, rebuilt (measuring machine)")
    r.add_argument("snapshot", help="the link_cycle snapshot (holds build/link_cycle)")
    for p in (g, r):
        p.add_argument("--out", required=True, help="directory for closure_roots.json and closure_blockers.csv")
        p.add_argument("--verify", type=int, default=25, help="roots re-proved by a forced closure (default 25)")
    s = sub.add_parser("show", help="print a closure_roots.json")
    s.add_argument("roots")
    s.add_argument("--limit", type=int, default=10)
    args = ap.parse_args(argv)
    log = (lambda line: print(f"closure_report: {line}", file=sys.stderr, flush=True))
    try:
        if args.cmd == "show":
            render(load_roots(args.roots), args.limit)
            return 0
        roots, table, facts = (from_graph(args.run_dir, args.verify, log) if args.cmd == "graph"
                               else replay(args.snapshot, args.verify, log))
        out = Path(args.out)
        out.mkdir(parents=True, exist_ok=True)
        for name, data in ((BLOCKERS, table), (ROOTS, roots)):
            tmp = out / (name + ".partial")
            tmp.write_bytes(data)
            os.replace(tmp, out / name)
        label = BOUND if args.cmd == "graph" else REPLAYED
        print(f"closure report of credit {facts['credit']} ({label}): {facts['roots']} scored root(s) with a gain; "
              f"wrote {out / ROOTS} and {out / BLOCKERS}")
        return 0
    except ReportError as e:
        print(f"closure_report: refused: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
