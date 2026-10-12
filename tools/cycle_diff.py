#!/usr/bin/env python3
"""Compare the credit of two link_cycle runs and list candidate commits.

link_cycle's credit (receipt series.credit_unique_bytes) is the union of the
retail intervals [retail_rva, retail_rva + size) of link_status.csv rows of
kind `real` that are placed and closed-strict. This tool compares two runs on
that union and never on names: renames are common, and a join by name counts a
renamed body as lost under its old name and gained under its new one.

  1. Inputs: two run directories (receipt.json, link_status.csv and, when
     present, data_fold_list.csv; each plain or .gz), or the files by flag. A
     status CSV must hash to its receipt's series.link_status_sha256 when the
     receipt records one; otherwise it is reported unverified. Each run's
     commit, rules, tool digest and receipt core hash are reported. A change in
     what measures (tool digest, rules, shadow rules, interpreter and decoder
     versions, toolchain, retail image) is flagged MEASUREMENT CHANGED: part of
     the difference may then be the ruler rather than the tree. Submodule
     pointer and ledger input changes are reported.
  2. Credit: each run's union must equal its receipt's credit_unique_bytes, and
     new - old must equal the receipts' difference, exactly; anything else is
     refused (exit 1) with no report. lost = old - new, gained = new - old, in
     unique bytes.
  3. Rows: each lost interval is cut at the boundaries of the rows covering it,
     and each piece is read from the new run's `real` row covering it (the
     witness), preferring the old credited row's own interval, then its start,
     then its name. The witness is the same row (same interval and name), a
     rename (same interval and source, other name) or only a covering row
     (split, merged or moved rows). Every covering row of both runs is listed.
     The categories are a PRECEDENCE PARTITION, not failure totals: each byte is
     counted once, under the first category that holds for its witness, so a
     row failing data-fwd and data-back counts under data-fwd alone.
     Lost, in precedence order:
       quarantine     witness unplaced, `quarantined: ...`
       placement      witness unplaced otherwise: the copy is no longer selected
                      (`not-selected:<kept object>`) or the placement changed
       twin-rejected  witness not self-strict, fails twin-rejected
       data-fwd       witness not self-strict, fails data-fwd
       data-back      witness not self-strict, fails data-back
       shift          witness self-strict, fails the shifted-base check (shift:)
       closure        witness placed, self-strict, empty failure text, not
                      closed-strict: something it reaches failed. link_status.csv
                      records no closure edges, so same-source rows that newly
                      fail are listed as leads, not as the provider
       other          any other failure, an unmeasured row, or no `real` row
                      covering the bytes in the new run (removed, shrunk or
                      re-kinded)
     Gained, read from the old run's rows, in precedence order:
       new row        no `real` row covered the bytes, and none shares the
                      credited row's start or its name and source
       extent growth  newly covered bytes of an existing row: an old `real` row
                      at the credited row's start, or with its name and source,
                      overlaps it but did not cover these bytes
       now placed     witness unplaced
       now self-strict  witness placed and not self-strict
       shift repaired witness self-strict but failed the shifted-base check
       closure regained  witness placed, self-strict, empty failure text, not
                      closed-strict
       other          anything else
     Whenever a witness's failures include data-back, data_fold_list.csv's
     entries for its data-back symbols (retail address, the linked addresses
     reaching it, stubs, data-fold-1 verdict) are attached, from the witness's
     own run. Only a data-back symbol's own entries are attached: a symbol the
     fold list does not name is reported as having no fold entry, and no other
     failure's entry stands in for it.
  4. Candidate commits (--git-range [A..B]; without a value, the receipts'
     commits): the commits in the range that touched each loss's sources (its
     old and new rows', and the kept copy's for a not-selected loss), plus the
     commits touching the measuring tool when its digest changed. They are
     unconfirmed CANDIDATES: a body loses closure through a provider, a header
     or the measuring tool as readily as through its own file. A loss whose own
     sources have no net diff between the endpoints is reported as such (a
     source edited and reverted within the range has commits but no net diff).
     Confirming a cause takes a controlled parent/child or revert run.

compare(old, new, git_range=None) returns the JSON report (schema_version
SCHEMA_VERSION, no timestamps but the receipts') for a publisher, and
dumps(report) is its deterministic text (sorted keys), the bytes --json writes;
old may be None (no predecessor), and each run is a directory or a mapping
{"status", "receipt", "folds"}. A refusal raises CycleDiffError.

  python3 tools/cycle_diff.py build/link_cycle_runs/31d8b0fddd build/link_cycle_runs/275a758e4c
          [--git-range [A..B]] [--top 20] [--gains 10] [--json OUT|-]
  python3 tools/cycle_diff.py --old-status S --old-receipt R --new-status S --new-receipt R
          [--old-folds F] [--new-folds F] ...
  python3 tools/cycle_diff.py --no-predecessor NEW_RUN [--json OUT|-]
"""
import argparse
import bisect
import collections
import csv
import gzip
import hashlib
import io
import itertools
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCHEMA_VERSION = 1
# link_cycle's per-row link_status.csv (not link_census's reverse/link_status.csv)
STATUS_REQUIRED = ("name", "kind", "source", "retail_rva", "size", "placed", "placement_reason", "self_strict",
                   "closed_strict", "failures")
# what measures, not what is measured: a change here changes the ruler
MEASURE_FIELDS = ("tool", "rules", "shadow_rules", "tool_digest", "measure_env", "toolchain_sha256", "retail_sha256",
                  "canon_rules")
INPUT_FIELDS = ("inputs",)
# tools/link_cycle.py TOOL_FILES: the files its tool_digest covers
TOOL_FILES = ("tools/link_cycle.py", "tools/link_census.py", "tools/build.py")
LOSS_CATEGORIES = (
    ("quarantine", "witness unplaced, quarantined"),
    ("placement", "witness unplaced otherwise: copy no longer selected, or the placement changed"),
    ("twin-rejected", "witness not self-strict, fails twin-rejected"),
    ("data-fwd", "witness not self-strict, fails data-fwd"),
    ("data-back", "witness not self-strict, fails data-back"),
    ("shift", "witness self-strict, fails the shifted-base check"),
    ("closure", "witness placed, self-strict, empty failure text, not closed-strict"),
    ("other", "another failure, an unmeasured row, or no real row covering the bytes"))
GAIN_CATEGORIES = (
    ("new row", "no real row covered the bytes, none shares the credited row's start or name and source"),
    ("extent growth", "newly covered bytes of an existing row"),
    ("now placed", "witness was unplaced"),
    ("now self-strict", "witness was placed and not self-strict"),
    ("shift repaired", "witness was self-strict but failed the shifted-base check"),
    ("closure regained", "witness was placed, self-strict, empty failure text, not closed-strict"),
    ("other", "anything else"))
PARTITION_NOTE = ("a precedence partition, not failure totals: each byte is counted once, under the first category "
                  "(in `order`) that holds for its witness")
FAIL_PRECEDENCE = ("twin-rejected", "data-fwd", "data-back")
# link_cycle writes a repeated failure token once with `x<count>`, count >= 2
REPEAT = re.compile(r"x([2-9]|[1-9]\d+)$")
LEADS = 3


class CycleDiffError(Exception):
    """A refusal: an input that is not what its receipt measured, or a credit that
    does not reconcile with the receipts."""


class Row(collections.namedtuple("Row", "name kind source rva size placed reason self_strict closed_strict "
                                        "failures linked")):
    __slots__ = ()

    @property
    def end(self):
        return self.rva + self.size

    @property
    def span(self):
        return self.rva, self.size

    @property
    def credited(self):
        return self.kind == "real" and self.placed and self.closed_strict

    def as_json(self):
        return {"name": self.name, "kind": self.kind, "source": self.source, "retail_rva": "0x%08X" % self.rva,
                "size": self.size, "linked_rva": self.linked, "placed": int(self.placed),
                "placement_reason": self.reason, "self_strict": int(self.self_strict),
                "closed_strict": int(self.closed_strict), "failures": self.failures}


def fail(message):
    raise CycleDiffError(message)


def flag(text):
    return (text or "").strip() in ("1", "True", "true")


# ---------------------------------------------------------------- intervals
def union(spans):
    """Sorted, merged [start, end) list; touching spans merge."""
    out = []
    for s, e in sorted(spans):
        if e <= s:
            continue
        if out and s <= out[-1][1]:
            out[-1][1] = max(out[-1][1], e)
        else:
            out.append([s, e])
    return [tuple(x) for x in out]


def subtract(a, b):
    """a - b for merged lists."""
    out, j = [], 0
    for s, e in a:
        cur = s
        while j < len(b) and b[j][1] <= cur:
            j += 1
        k = j
        while k < len(b) and b[k][0] < e:
            if b[k][0] > cur:
                out.append((cur, b[k][0]))
            cur = max(cur, b[k][1])
            k += 1
        if cur < e:
            out.append((cur, e))
    return out


def total(spans):
    return sum(e - s for s, e in spans)


class Cover:
    """Rows by retail interval: every row overlapping [s, e)."""

    def __init__(self, rows):
        self.rows = sorted((r for r in rows if r.size > 0), key=lambda r: (r.rva, r.end, r.name, r.source))
        self.starts = [r.rva for r in self.rows]
        self.maxend = list(itertools.accumulate((r.end for r in self.rows), max))

    def over(self, s, e):
        i = bisect.bisect_left(self.starts, e) - 1
        out = []
        while i >= 0 and self.maxend[i] > s:
            if self.rows[i].end > s:
                out.append(self.rows[i])
            i -= 1
        out.reverse()
        return out


# ---------------------------------------------------------------- inputs
def read_bytes(path):
    data = Path(path).read_bytes()
    return gzip.decompress(data) if data[:2] == b"\x1f\x8b" else data


def load_status(path):
    """([Row], sha256 of the CSV bytes). Plain or .gz; the digest is of the CSV."""
    data = read_bytes(path)
    reader = csv.DictReader(io.StringIO(data.decode("utf-8"), newline=""))
    missing = [c for c in STATUS_REQUIRED if c not in (reader.fieldnames or ())]
    if missing:
        fail(f"{path}: not a link_cycle link_status.csv (no column {', '.join(missing)})")
    rows = []
    for r in reader:
        try:
            rva, size = int(r["retail_rva"], 16), int(r["size"])
        except ValueError:
            fail(f"{path}: row {r['name']!r} has retail_rva {r['retail_rva']!r} size {r['size']!r}")
        rows.append(Row(r["name"], r["kind"], r["source"], rva, size, flag(r["placed"]), r["placement_reason"] or "",
                        flag(r["self_strict"]), flag(r["closed_strict"]), r["failures"] or "",
                        r.get("linked_rva") or ""))
    return rows, hashlib.sha256(data).hexdigest()


def load_folds(path):
    """data_fold_list.csv (plain or .gz): {symbol: [entry]} for the data-back witness."""
    out = collections.defaultdict(list)
    if not path or not Path(path).is_file():
        return out
    with io.StringIO(read_bytes(path).decode("utf-8"), newline="") as handle:
        for r in csv.DictReader(handle):
            entry = {"retail_rva": r.get("retail_rva", ""), "linked": r.get("linked", ""),
                     "verdict": r.get("verdict", "")}
            for symbol in filter(None, (r.get("symbols") or "").split(";")):
                out[symbol].append(entry)
    return out


class Run:
    def __init__(self, label, status, receipt, folds=None):
        self.label = label
        try:
            self.receipt = json.loads(read_bytes(receipt).decode("utf-8"))
        except (OSError, ValueError) as exc:
            fail(f"{label} receipt {receipt}: {exc}")
        try:
            self.rows, self.status_sha256 = load_status(status)
        except OSError as exc:
            fail(f"{label} status {status}: {exc}")
        self.status_file = Path(status).name
        series = self.receipt.get("series") or {}
        want = series.get("link_status_sha256")
        if want is None:
            self.hash_state = "unverified: the receipt records no link_status_sha256"
        elif want != self.status_sha256:
            fail(f"{label} {status}: sha256 {self.status_sha256} is not its receipt's link_status_sha256 {want}: "
                 f"this status CSV is not the one {receipt} measured")
        else:
            self.hash_state = "verified"
        credit = series.get("credit_unique_bytes")
        if credit is None:
            credit = ((series.get("real") or {}).get("placed_closed_strict") or {}).get("unique_bytes")
        if credit is None:
            fail(f"{label} receipt {receipt} records no credit (series.credit_unique_bytes)")
        self.receipt_credit = credit
        self.folds_file = Path(folds).name if folds and Path(folds).is_file() else None
        self.folds = load_folds(folds)
        self.credit = union((r.rva, r.end) for r in self.rows if r.credited)

    @property
    def commit(self):
        return self.receipt.get("commit") or ""

    def identity(self):
        r = self.receipt
        return {"commit": self.commit, "core_sha256": r.get("core_sha256"),
                "core_canon_sha256": r.get("core_canon_sha256"), "tool_digest": r.get("tool_digest"),
                "rules": r.get("rules"), "status_sha256": self.status_sha256}

    def info(self):
        r = self.receipt
        return dict(self.identity(), date_utc=r.get("date_utc"), tool=r.get("tool"), shadow_rules=r.get("shadow_rules"),
                    authoritative=r.get("authoritative"), snapshot=r.get("snapshot"), dirty=r.get("dirty"),
                    submodules=r.get("submodules") or {}, status_file=self.status_file, status_hash=self.hash_state,
                    folds_file=self.folds_file, rows=len(self.rows), credit_unique_bytes=total(self.credit),
                    receipt_credit_unique_bytes=self.receipt_credit)


def pick(directory, name, required=True):
    """directory/name, else directory/name.gz."""
    for candidate in (directory / name, directory / (name + ".gz")):
        if candidate.is_file():
            return candidate
    if required:
        fail(f"{directory}: no {name} or {name}.gz")
    return None


def run_paths(directory):
    d = Path(directory)
    if not d.is_dir():
        fail(f"{directory}: not a run directory")
    return pick(d, "link_status.csv"), pick(d, "receipt.json"), pick(d, "data_fold_list.csv", required=False)


def load_run(spec, label):
    """A run from a directory, or a mapping {"status", "receipt", "folds"}."""
    if isinstance(spec, (str, Path)):
        return Run(label, *run_paths(spec))
    status, receipt, folds = spec.get("status"), spec.get("receipt"), spec.get("folds")
    if not status or not receipt:
        fail(f"{label}: a run needs a directory, or a status CSV and its receipt")
    return Run(label, status, receipt, folds)


# ---------------------------------------------------------------- receipts
def short(value):
    if isinstance(value, str) and re.fullmatch(r"[0-9a-f]{40,64}", value):
        return value[:12]
    return json.dumps(value, sort_keys=True) if isinstance(value, (dict, list)) else str(value)


def receipt_changes(old, new):
    """{"measurement": [(field, old, new)], "submodules": [...], "inputs": [...]}"""
    out = {"measurement": [], "submodules": [], "inputs": []}
    a, b = old.receipt, new.receipt
    for k in MEASURE_FIELDS:
        if isinstance(a.get(k), dict) or isinstance(b.get(k), dict):
            x, y = a.get(k) or {}, b.get(k) or {}
            for sub in sorted(set(x) | set(y)):
                if x.get(sub) != y.get(sub):
                    out["measurement"].append((f"{k}.{sub}", x.get(sub), y.get(sub)))
        elif a.get(k) != b.get(k):
            out["measurement"].append((k, a.get(k), b.get(k)))
    x, y = a.get("submodules") or {}, b.get("submodules") or {}
    for sub in sorted(set(x) | set(y)):
        if x.get(sub) != y.get(sub):
            out["submodules"].append((sub, x.get(sub), y.get(sub)))
    for k in INPUT_FIELDS:
        x, y = a.get(k) or {}, b.get(k) or {}
        for sub in sorted(set(x) | set(y)):
            if x.get(sub) != y.get(sub):
                out["inputs"].append((sub, x.get(sub), y.get(sub)))
    return out


# ---------------------------------------------------------------- explanation
def failure_classes(text):
    out = []
    for token in filter(None, (text or "").split(";")):
        cls, sep, _ = token.partition(":")
        if not sep:
            found = REPEAT.search(cls)
            if found and found.start() > 0:
                cls = cls[:found.start()]
        if cls not in out:
            out.append(cls)
    return out


def failure_symbols(text, cls):
    """Symbols of one failure class, each with its x<N> reading as a fallback."""
    out = []
    for token in filter(None, (text or "").split(";")):
        c, sep, symbol = token.partition(":")
        if sep and c == cls:
            found = REPEAT.search(symbol)
            out.append((symbol, symbol[:found.start()] if found and found.start() > 0 else None))
    return out


def witness(had, now):
    """The row of the other run that explains a piece: a `real` row, the old
    credited row's own interval first, then its start, then its name."""
    real = [r for r in now if r.kind == "real"]
    if not real:
        return None
    spans, starts, names = {r.span for r in had}, {r.rva for r in had}, {r.name for r in had}
    return min(real, key=lambda r: (r.span not in spans, r.rva not in starts, r.name not in names, r.rva, r.size,
                                    r.name, r.source))


def relation(had, w):
    """How the witness corresponds to the credited rows: the same row (interval
    and name), a rename (interval and source, another name), or only a row
    covering the bytes (split, merged or moved rows: no correspondence shown)."""
    if w is None:
        return None
    if any(h.span == w.span and h.name == w.name for h in had):
        return "same row"
    if any(h.span == w.span and h.source == w.source for h in had):
        return "renamed"
    return "covering row"


def counterparts(had, other):
    """`real` rows of the other run overlapping a credited row and sharing its
    start, or its name and source: the same row at another extent."""
    out = []
    for h in had:
        for r in other.over(h.rva, h.end):
            if r.kind == "real" and (r.rva == h.rva or (r.name, r.source) == (h.name, h.source)) and r not in out:
                out.append(r)
    return out


def extent(rows):
    return ", ".join(f"{r.name} 0x{r.rva:08X}+{r.size}" for r in rows)


def loss_category(w, now, had, other):
    if w is None:
        shrunk = counterparts(had, other)
        if shrunk:
            return "other", f"extent shrank: NEW {extent(shrunk)} no longer covers these bytes"
        kinds = sorted({r.kind for r in now})
        return "other", "no real row covers these bytes" + (f" (now {', '.join(kinds)})" if kinds else
                                                            " (row removed, shrunk or moved)")
    if not w.placed:
        why = w.reason or "unplaced"
        kept = failure_symbols(w.failures, "not-selected")
        if kept:
            why += f" (kept: {kept[0][0]})"
        return ("quarantine" if why.startswith("quarantined") else "placement"), why
    classes = failure_classes(w.failures)
    if not w.self_strict:
        for c in FAIL_PRECEDENCE:
            if c in classes:
                return c, w.failures
        return "other", w.failures or "placed, not self-strict, no failure recorded (unmeasured)"
    if "shift" in classes:
        return "shift", w.failures
    if classes:
        return "other", w.failures
    if not w.closed_strict:
        return "closure", "placed, self-strict, empty failure text, not closed-strict"
    return "other", "witness is credited (inconsistent status CSV)"


def gain_category(w, now, had, other):
    if w is None:
        grown = counterparts(had, other)
        if grown:
            return "extent growth", f"newly covered bytes of an existing row: OLD {extent(grown)}"
        kinds = sorted({r.kind for r in now})
        return "new row", "no real row covered these bytes" + (f" (was {', '.join(kinds)})" if kinds else "")
    if not w.placed:
        return "now placed", w.reason or "unplaced"
    classes = failure_classes(w.failures)
    if not w.self_strict:
        return "now self-strict", w.failures or "was placed, not self-strict, no failure recorded (unmeasured)"
    if "shift" in classes:
        return "shift repaired", w.failures
    if classes:
        return "other", w.failures
    if not w.closed_strict:
        return "closure regained", "was placed, self-strict, empty failure text, not closed-strict"
    return "other", "witness was credited (inconsistent status CSV)"


def explain(intervals, had_cover, now_cover, categorize):
    """Pieces of `intervals` merged into items: each with its credited rows on
    the side that has the credit, the other side's covering rows and witness."""
    items = []
    for s, e in intervals:
        had_rows, now_rows = had_cover.over(s, e), now_cover.over(s, e)
        cuts = sorted({s, e} | {x for r in had_rows + now_rows for x in (r.rva, r.end) if s < x < e})
        for lo, hi in zip(cuts, cuts[1:]):
            had = [r for r in had_rows if r.rva <= lo and r.end >= hi]
            now = [r for r in now_rows if r.rva <= lo and r.end >= hi]
            w = witness(had, now)
            category, detail = categorize(w, now, had, now_cover)
            key = (category, detail, tuple(had), w)
            last = items[-1] if items else None
            if last and last["end"] == lo and last["key"] == key:
                last["end"] = hi
                last["now"] = list(dict.fromkeys(last["now"] + now))
                continue
            items.append({"start": lo, "end": hi, "category": category, "detail": detail, "had": had, "now": now,
                          "witness": w, "relation": relation(had, w), "key": key})
    for item in items:
        item["bytes"] = item["end"] - item["start"]
        del item["key"]
    return items


def tally(items, categories):
    out = {c: {"rows": set(), "bytes": 0} for c, _ in categories}
    for it in items:
        slot = out.setdefault(it["category"], {"rows": set(), "bytes": 0})
        slot["bytes"] += it["bytes"]
        slot["rows"] |= set(it["had"])
    return {c: {"rows": len(v["rows"]), "bytes": v["bytes"]} for c, v in out.items()}


def object_name(source):
    """tools/build.py obj_path's file name for a plain source."""
    stem = "_".join(Path(source).with_suffix("").parts)
    return "".join(("^" + c.lower()) if c.isupper() else c for c in stem) + ".obj"


def fold_witness(folds, failures):
    """(entries, missing) for a row's data-back failures: data_fold_list.csv's
    entries for each data-back symbol, and the data-back symbols the fold list
    does not name. A symbol is looked up as written and, when it ends in
    link_cycle's repeat count x<N>, without it; a missing one is reported without
    the count. No other failure's symbol is looked up for it."""
    entries, missing = {}, []
    for symbol, fallback in failure_symbols(failures, "data-back"):
        hit = symbol if symbol in folds else fallback if fallback in folds else None
        if hit is None:
            name = fallback or symbol
            if name not in missing:
                missing.append(name)
            continue
        for entry in folds[hit]:
            entries.setdefault((entry["retail_rva"], hit), dict(entry, symbol=hit))
    return list(entries.values()), missing


def attach_witness_info(items, run, by_span_other, objects):
    """kept: the source of the copy the link kept instead (not-selected). folds
    and folds_missing: whenever the witness fails data-back (whatever its
    category) and its run has a fold list, the fold-list entries of its data-back
    symbols and the data-back symbols with none (fold_witness). leads, for a closure
    loss: same-source rows of `run` that are placed and newly not self-strict
    (placed and self-strict at the same interval in the other run), nearest first."""
    by_source = collections.defaultdict(list)
    for r in run.rows:
        by_source[r.source].append(r)
    for it in items:
        w = it["witness"]
        it["kept"], it["folds"], it["folds_missing"], it["leads"] = [], [], [], []
        if w is None:
            continue
        it["kept"] = [objects.get(obj, obj) for obj, _ in failure_symbols(w.failures, "not-selected")]
        if run.folds_file:
            it["folds"], it["folds_missing"] = fold_witness(run.folds, w.failures)
        if it["category"] == "closure":
            leads = [r for r in by_source.get(w.source, ()) if r is not w and r.placed and not r.self_strict
                     and any(b.placed and b.self_strict for b in by_span_other.get(r.span, ()))]
            it["leads"] = sorted(leads, key=lambda r: (abs(r.rva - w.rva), r.rva, r.name))[:LEADS]


def renames(old, new):
    """Intervals credited in both runs under different names: with a common source
    (renames) or not (re-homed under another name); and what a join by name would
    call lost."""
    a, b = collections.defaultdict(set), collections.defaultdict(set)
    for r in old.rows:
        if r.credited:
            a[r.span].add((r.name, r.source))
    for r in new.rows:
        if r.credited:
            b[r.span].add((r.name, r.source))
    renamed, rehomed = [], []
    for span in a:
        if span in b and not {n for n, _ in a[span]} & {n for n, _ in b[span]}:
            same_source = {s for _, s in a[span]} & {s for _, s in b[span]}
            (renamed if same_source else rehomed).append(span)
    names_new = {n for v in b.values() for n, _ in v}
    join = union((r.rva, r.end) for r in old.rows if r.credited and r.name not in names_new)
    measure = lambda spans: {"rows": len(spans), "bytes": total(union((s, s + n) for s, n in spans))}
    return {"renamed": measure(renamed), "other_name_and_source": measure(rehomed),
            "name_join_lost_bytes": total(join)}


# ---------------------------------------------------------------- candidates
def git(*args):
    res = subprocess.run(["git", "-C", str(ROOT), *args], capture_output=True, text=True, encoding="utf-8",
                         errors="replace")
    if res.returncode:
        fail(f"git {' '.join(args)}: {res.stderr.strip()}")
    return res.stdout


def range_index(rng):
    a, sep, b = rng.partition("..")
    if not sep or not a or not b or b.startswith("."):
        fail(f"--git-range {rng!r}: expected OLD..NEW")
    for rev in (a, b):
        git("rev-parse", "--verify", "--quiet", rev + "^{commit}")
    touched, commits, sha = collections.defaultdict(list), 0, None
    for line in git("log", "--no-renames", "--format=%x01%H%x09%s", "--name-only", rng).splitlines():
        if line.startswith("\x01"):
            sha, _, subject = line[1:].partition("\t")
            commits += 1
        elif line.strip() and sha:
            touched[line.strip().lower()].append((sha, subject))
    changed = {p.strip().lower() for p in git("diff", "--no-renames", "--name-only", a, b).splitlines() if p.strip()}
    return {"range": rng, "commits": commits, "touched": touched, "changed": changed}


def attach_candidates(items, index):
    for it in items:
        own = list(dict.fromkeys([r.source for r in it["had"]] + ([it["witness"].source] if it["witness"] else [])))
        sources = {}
        for src in list(dict.fromkeys(own + it["kept"])):
            key = src.lower()
            sources[src] = {"role": "own" if src in own else "kept copy",
                            "net_diff": key in index["changed"],
                            "commits": [{"sha": s, "subject": t} for s, t in index["touched"].get(key, ())]}
        it["candidates"] = sources
        it["net_source_diff"] = any(v["net_diff"] for v in sources.values() if v["role"] == "own")


# ---------------------------------------------------------------- report
def schema():
    return {"partition": PARTITION_NOTE,
            "lost": {"order": [c for c, _ in LOSS_CATEGORIES], "definitions": dict(LOSS_CATEGORIES)},
            "gained": {"order": [c for c, _ in GAIN_CATEGORIES], "definitions": dict(GAIN_CATEGORIES)},
            "items": "credited_rows: the rows credited on the side holding the bytes (OLD for lost, NEW for gained); "
                     "other_rows: the other run's rows covering them; witness: the other run's row read for the "
                     "category; relation: same row | renamed (same interval and source) | covering row",
            "folds": "folds: data_fold_list.csv entries of the witness's data-back symbols, from the witness's run; "
                     "folds_missing: its data-back symbols that fold list does not name (both empty when that run "
                     "has no fold list: see folds_file). No other failure's entry is attached",
            "candidates": "commits in the range touching a loss's sources: unconfirmed candidates, never causes; "
                          "net_diff: the source differs between the range's endpoints"}


def build_report(old, new, rng=None):
    net, receipt_net = total(new.credit) - total(old.credit), new.receipt_credit - old.receipt_credit
    if net != receipt_net:
        fail(f"net {net:+,} B is not the receipts' credit_unique_bytes difference {receipt_net:+,} B "
             f"(OLD union {total(old.credit):,} vs receipt {old.receipt_credit:,}, NEW union "
             f"{total(new.credit):,} vs receipt {new.receipt_credit:,})")
    for run in (old, new):        # equal offsets cancel in the net; each run must reconcile on its own too
        if total(run.credit) != run.receipt_credit:
            fail(f"{run.label}: the union of real placed closed-strict intervals is {total(run.credit):,} B, its "
                 f"receipt's credit_unique_bytes is {run.receipt_credit:,} B: this tool's credit is not "
                 f"link_cycle's")
    lost, gained = subtract(old.credit, new.credit), subtract(new.credit, old.credit)
    if total(gained) - total(lost) != net:
        fail(f"gained {total(gained):,} - lost {total(lost):,} != net {net:,}")
    old_cover, new_cover = Cover(old.rows), Cover(new.rows)
    losses = explain(lost, Cover([r for r in old.rows if r.credited]), new_cover, loss_category)
    gains = explain(gained, Cover([r for r in new.rows if r.credited]), old_cover, gain_category)
    for items, want in ((losses, lost), (gains, gained)):
        if sum(i["bytes"] for i in items) != total(want):
            fail("the explained pieces do not partition the intervals")
    by_span = lambda run: {k: list(g) for k, g in itertools.groupby(sorted(run.rows, key=lambda r: r.span),
                                                                       key=lambda r: r.span)}
    objects = {object_name(r.source): r.source for run in (old, new) for r in run.rows}
    attach_witness_info(losses, new, by_span(old), objects)
    attach_witness_info(gains, old, by_span(new), objects)
    changes = receipt_changes(old, new)
    report = {"schema_version": SCHEMA_VERSION, "comparison": True, "schema": schema(),
              "identity": {"old": old.identity(), "new": new.identity()},
              "old": old.info(), "new": new.info(), "changes": changes,
              "measurement_changed": bool(changes["measurement"]),
              "totals": {"gained": total(gained), "gained_intervals": len(gained), "lost": total(lost),
                         "lost_intervals": len(lost), "net": net, "receipt_net": receipt_net, "reconciles": True},
              "lost": {"rows": len({r for i in losses for r in i["had"]}),
                       "categories": tally(losses, LOSS_CATEGORIES), "items": losses},
              "gained": {"rows": len({r for i in gains for r in i["had"]}),
                         "categories": tally(gains, GAIN_CATEGORIES), "items": gains},
              "renames": renames(old, new), "candidates": None}
    if rng:
        index = range_index(rng)
        attach_candidates(losses, index)
        quiet = [i for i in losses if not i["net_source_diff"]]
        tool_commits = []
        for path in TOOL_FILES:
            tool_commits += [{"sha": s, "subject": t, "path": path} for s, t in index["touched"].get(path.lower(), ())]
        report["candidates"] = {"range": rng, "commits": index["commits"],
                                "no_net_source_diff": {"items": len(quiet),
                                                       "rows": len({r for i in quiet for r in i["had"]}),
                                                       "bytes": sum(i["bytes"] for i in quiet)},
                                "tool_commits": tool_commits}
    return report


def first_report(new):
    """No predecessor: the run's identity and credit, and no comparison."""
    if total(new.credit) != new.receipt_credit:
        fail(f"{new.label}: the union of real placed closed-strict intervals is {total(new.credit):,} B, its "
             f"receipt's credit_unique_bytes is {new.receipt_credit:,} B: this tool's credit is not link_cycle's")
    return {"schema_version": SCHEMA_VERSION, "comparison": False, "schema": schema(),
            "note": "no predecessor run: nothing to compare",
            "identity": {"old": None, "new": new.identity()}, "old": None, "new": new.info(), "changes": None,
            "measurement_changed": None, "totals": None, "lost": None, "gained": None, "renames": None,
            "candidates": None}


def to_json(report):
    """The report as plain JSON values (rows as objects, tuples as lists). A
    report that already is (compare()'s result) comes back equal."""
    if not report["comparison"]:
        return report

    def item(it):
        if "credited_rows" in it:
            return it
        out = {k: v for k, v in it.items() if k not in ("had", "now", "witness", "leads")}
        out["start"], out["end"] = "0x%08X" % it["start"], "0x%08X" % it["end"]
        out["credited_rows"] = [r.as_json() for r in it["had"]]
        out["other_rows"] = [r.as_json() for r in it["now"]]
        out["witness"] = it["witness"].as_json() if it["witness"] else None
        out["leads"] = [r.as_json() for r in it.get("leads", ())]
        return out
    out = dict(report)
    out["changes"] = {k: [list(x) for x in v] for k, v in report["changes"].items()}
    for side in ("lost", "gained"):
        out[side] = dict(report[side], items=[item(i) for i in report[side]["items"]])
    return out


def dumps(report):
    """Deterministic JSON text of a report, compare()'s result or the internal
    one: sorted keys, ASCII; the only dates are the receipts'. --json writes it."""
    return json.dumps(to_json(report), indent=1, sort_keys=True) + "\n"


def compare(old, new, git_range=None):
    """The JSON report comparing two runs (each a directory or a mapping
    {"status", "receipt", "folds"}); old None: no predecessor. git_range:
    None, "receipts" (the receipts' commits) or "A..B". Raises CycleDiffError."""
    if new is None:
        fail("compare needs a NEW run")
    new_run = load_run(new, "NEW")
    if old is None:
        return json.loads(dumps(first_report(new_run)))
    old_run = load_run(old, "OLD")
    return json.loads(dumps(build_report(old_run, new_run, resolve_range(git_range, old_run, new_run))))


def resolve_range(rng, old, new):
    if rng != "receipts":
        return rng
    if not old.commit or not new.commit:
        fail("--git-range without a value needs both receipts' commits")
    return f"{old.commit}..{new.commit}"


# ---------------------------------------------------------------- text
def describe(r):
    if r is None:
        return "-"
    state = "placed" if r.placed else f"unplaced ({r.reason or '?'})"
    return f"{state}, self {int(r.self_strict)}, closed {int(r.closed_strict)}" + (f"; {r.failures}" if r.failures
                                                                                    else "")


def clip(text, width=96):
    return text if len(text) <= width else text[:width - 3] + "..."


def render(report, top, gains_top, out=None):
    p = lambda *a: print(*a, file=out or sys.stdout)
    n = report["new"]
    if not report["comparison"]:
        p(f"cycle_diff: no predecessor run; NEW {n['commit'][:10]} {n['date_utc']} {n['rules']} tool "
          f"{short(n['tool_digest'])} core {short(n['core_sha256'])} status {n['status_hash']}: credit "
          f"{n['credit_unique_bytes']:,} B. Nothing to compare.")
        return
    o = report["old"]
    p(f"cycle_diff: {o['commit'][:10]} -> {n['commit'][:10]}")
    for tag, r in (("OLD", o), ("NEW", n)):
        subs = " ".join(f"{k}@{v[:10]}" for k, v in sorted(r["submodules"].items()))
        p(f"  {tag} {r['commit'][:10]} {r['date_utc']}  {r['tool']} {r['rules']}  tool {short(r['tool_digest'])}  "
          f"core {short(r['core_sha256'])}  status {r['status_hash']}"
          + ("" if r["authoritative"] else "  NOT AUTHORITATIVE") + ("  DIRTY TREE" if r["dirty"] else "")
          + (f"  {subs}" if subs else ""))
    ch = report["changes"]
    if ch["measurement"]:
        p("")
        p("  !! MEASUREMENT CHANGED: the two runs were not measured by the same ruler; part of this difference may")
        p("  !! be the measuring tool or its environment rather than the tree:")
        for k, a, b in ch["measurement"]:
            p(f"  !!   {k}: {short(a)} -> {short(b)}")
    for k, a, b in ch["submodules"]:
        p(f"  submodule {k}: {short(a)[:10] if a else '-'} -> {short(b)[:10] if b else '-'}")
    if ch["inputs"]:
        p("  ledger inputs changed: " + ", ".join(k for k, _, _ in ch["inputs"]))
    t = report["totals"]
    p("")
    p("credit: unique retail bytes of real, placed, closed-strict rows (intervals, not names)")
    p(f"  OLD {o['credit_unique_bytes']:,}  NEW {n['credit_unique_bytes']:,}")
    p(f"  gained +{t['gained']:,} ({t['gained_intervals']} intervals), lost -{t['lost']:,} "
      f"({t['lost_intervals']} intervals), net {t['net']:+,} = the receipts' credit_unique_bytes delta")
    p("")
    p("categories below are a precedence partition, not failure totals: each byte is counted once, under the")
    p("first category (in the order listed) that holds for its witness row")
    for side, categories, sign in (("lost", LOSS_CATEGORIES, "-"), ("gained", GAIN_CATEGORIES, "+")):
        sec = report[side]
        p("")
        p(f"{side} by category ({sec['rows']} rows credited in {'OLD' if side == 'lost' else 'NEW'})")
        p(f"  {'category':<17} {'rows':>5} {'bytes':>9}  definition")
        cats = sec["categories"]
        for c, definition in categories:
            if cats.get(c, {}).get("bytes"):
                p(f"  {c:<17} {cats[c]['rows']:>5} {sign}{cats[c]['bytes']:>8,}  {definition}")
    rn = report["renames"]
    p("")
    p(f"renames: {rn['renamed']['rows']} rows / {rn['renamed']['bytes']:,} B are credited in both runs at one "
      f"interval and source under another name, {rn['other_name_and_source']['rows']} rows / "
      f"{rn['other_name_and_source']['bytes']:,} B")
    p(f"  at one interval under another name and source; a join by name would call "
      f"{rn['name_join_lost_bytes']:,} B lost, not {t['lost']:,}")
    cand = report["candidates"]
    if cand:
        q = cand["no_net_source_diff"]
        p("")
        p(f"candidate commits: {cand['range']} ({cand['commits']} commits). Unconfirmed CANDIDATES: a commit "
          f"touching a loss's")
        p("  source is not shown to have changed its verdict; providers, headers and the measuring tool are not "
          "traced.")
        p(f"  losses whose own sources have no net source diff between endpoints: {q['rows']} rows / "
          f"{q['bytes']:,} B ({q['items']} items)")
        if report["measurement_changed"] and cand["tool_commits"]:
            p("  commits touching the measuring tool's digested files:")
            for c in cand["tool_commits"]:
                p(f"    {c['sha'][:10]} {c['path']}: {c['subject'][:90]}")
    losses = sorted(report["lost"]["items"], key=lambda i: (-i["bytes"], i["start"]))
    p("")
    p(f"top {min(top, len(losses))} losses by bytes")
    for it in losses[:top]:
        render_item(p, it, "-", "NEW")
    gains = sorted(report["gained"]["items"], key=lambda i: (-i["bytes"], i["start"]))
    if gains_top:
        p("")
        p(f"top {min(gains_top, len(gains))} gains by bytes")
        for it in gains[:gains_top]:
            render_item(p, it, "+", "OLD")


def render_item(p, it, sign, other):
    w = it["witness"]
    names = list(dict.fromkeys(r.name for r in it["had"])) or ["?"]
    p(f"  {sign}{it['bytes']:<6,} 0x{it['start']:08X}..0x{it['end']:08X}  {it['category']:<16} {clip(names[0])}"
      + (f" (+{len(names) - 1} more)" if len(names) > 1 else ""))
    srcs = list(dict.fromkeys(r.source for r in it["had"]))
    p(f"          source {', '.join(srcs)}")
    if it["relation"] == "renamed":
        p(f"          {other} row renamed (same interval and source): {clip(w.name)}")
    elif it["relation"] == "covering row":
        p(f"          {other} covering row: {clip(w.name)} 0x{w.rva:08X}+{w.size} ({w.source})")
    elif w is not None and w.source not in srcs:
        p(f"          {other} row source: {w.source}")
    p(f"          {other}: {describe(w) if w else it['detail']}")
    for src in it.get("kept", ()):
        p(f"          kept copy: {src}")
    extra = [r for r in it["now"] if r is not w]
    if extra:
        p(f"          also covering in {other}: " + "; ".join(f"{r.kind} {clip(r.name, 50)} 0x{r.rva:08X}+{r.size}"
                                                         for r in extra[:3]))
    for f in it.get("folds", ())[:3]:
        p(f"          fold list ({other}, data-back symbol): {clip(f['symbol'], 60)} retail {f['retail_rva']} reached "
          f"from {f['linked']}; {f['verdict']}")
    for symbol in it.get("folds_missing", ())[:3]:
        p(f"          no fold entry for the data-back symbol {clip(symbol, 60)} ({other} fold list)")
    for r in it.get("leads", ()):
        p(f"          lead (same source, newly failing; not a closure edge): {clip(r.name, 60)} 0x{r.rva:08X} "
          f"{describe(r)}")
    if "candidates" in it:
        for src, c in it["candidates"].items():
            k = len(c["commits"])
            shas = ", ".join(x["sha"][:10] for x in c["commits"][:6]) + (" ..." if k > 6 else "")
            state = f"{k} commit{'s' * (k != 1)} touched it: {shas}" if k else "no commit touched it"
            p(f"          candidates ({c['role']} {src}): {state}"
              + ("" if c["net_diff"] else "; no net source diff between endpoints"))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("old", nargs="?", help="OLD run directory (receipt.json, link_status.csv; plain or .gz)")
    ap.add_argument("new", nargs="?", help="NEW run directory")
    for side in ("old", "new"):
        ap.add_argument(f"--{side}-status", help=f"{side.upper()} link_status.csv (plain or .gz)")
        ap.add_argument(f"--{side}-receipt", help=f"{side.upper()} receipt.json")
        ap.add_argument(f"--{side}-folds", help=f"{side.upper()} data_fold_list.csv (optional witness)")
    ap.add_argument("--no-predecessor", action="store_true",
                    help="report one run with nothing to compare; its directory is the only positional")
    ap.add_argument("--git-range", nargs="?", const="receipts", metavar="OLD..NEW",
                    help="list candidate commits; without a value, the receipts' commits")
    ap.add_argument("--top", type=int, default=20, help="losses to detail (default 20)")
    ap.add_argument("--gains", type=int, default=10, help="gains to detail (default 10)")
    ap.add_argument("--json", metavar="OUT", help="write the full report as JSON (`-`: stdout, no text report)")
    args = ap.parse_args(argv)
    dirs = {"old": args.old, "new": args.new}
    if args.no_predecessor:
        if args.new or args.old_status or args.old_receipt:
            ap.error("--no-predecessor takes one run: a directory or --new-status/--new-receipt")
        dirs = {"old": None, "new": args.old}
    specs = {}
    for side in ("old", "new") if not args.no_predecessor else ("new",):
        flags = {k: getattr(args, f"{side}_{k}") for k in ("status", "receipt", "folds")}
        if dirs[side] and not any(flags.values()):
            specs[side] = dirs[side]
            continue
        try:
            base = dict(zip(("status", "receipt", "folds"), run_paths(dirs[side]))) if dirs[side] else {}
        except CycleDiffError as exc:
            print(f"cycle_diff: FAIL: {exc}", file=sys.stderr)
            return 1
        specs[side] = {k: flags[k] or base.get(k) for k in ("status", "receipt", "folds")}
        if not specs[side]["status"] or not specs[side]["receipt"]:
            ap.error(f"{side.upper()}: give a run directory or --{side}-status and --{side}-receipt")
    try:
        new = load_run(specs["new"], "NEW")
        if args.no_predecessor:
            report = first_report(new)
        else:
            old = load_run(specs["old"], "OLD")
            report = build_report(old, new, resolve_range(args.git_range, old, new))
    except CycleDiffError as exc:
        print(f"cycle_diff: FAIL: {exc}", file=sys.stderr)
        return 1
    if args.json != "-":
        render(report, args.top, args.gains)
    if args.json:
        if args.json == "-":
            sys.stdout.write(dumps(report))
        else:
            Path(args.json).write_bytes(dumps(report).encode("utf-8"))     # LF on every platform
    return 0


if __name__ == "__main__":
    sys.exit(main())
