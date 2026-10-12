#!/usr/bin/env python3
"""Fetch, authenticate, validate and serve published link_cycle bundles (tools/publish_cycle.py).

A link_cycle run on the designated measuring machine is published as one
IMMUTABLE GitHub prerelease. Nothing is committed to master and no release is
ever "Latest". The newest published bundle is the link-cycle figure
contributors read; the committed reverse/link_cycle/receipt.json is history.

IDENTITY. A bundle is one MEASUREMENT, not one result:
    link-cycle/<commit 12>-<measurement end, YYYYMMDDTHHMMSSZ>-<sha256 of receipt.json, 12>
A rerun of the same commit with the same results (the same receipt core) is a
new measurement with its own tag; the core stays in the manifest as the
reproducibility identity.

MEMBERS: receipt.json, link_status.csv.gz, data_fold_list.csv.gz, the producer's
data_back_rank.txt/.json and manifest.json; optionally closure_graph.json.gz
(the graph link_cycle's measure wrote; the receipt names its sha256),
closure_roots.json.gz + closure_blockers.csv.gz (tools/closure_report.py) and
cycle_diff.json (tools/cycle_diff.py). No other file.

TRUST. `validate` proves a directory is SELF-CONSISTENT: every member's size and
SHA-256 is the manifest's; the tag is the one the receipt's bytes name; every
figure the manifest repeats (measurement times, headline credit, submodules,
canonical core, tree) is derived again from the receipt and must agree; the
optional components agree with the members. That is integrity, not authorship.
`fetch` AUTHENTICATES a published release before anything is installed:
  * the release's author is in PUBLISHERS (login and numeric id), below;
  * the release is IMMUTABLE (GitHub's release `immutable` field: tag and assets
    are locked by the platform). A mutable release is refused. The repository
    setting is the maintainer's to enable; --allow-mutable exists only to
    exercise fetch before that, and what it installs is marked NOT
    authenticated: the queues refuse it;
  * the tag itself resolves (annotated tags peeled) to the full commit the
    receipt measured, and the release targets that commit;
  * every downloaded asset hashes to the SHA-256 digest the release API reports
    for it, and those are the manifest's members. Release notes are never read;
  * `gh release verify TAG` (the immutable release's attestation) is run when
    this gh has it; a failed verification refuses, an older gh is recorded.
The evidence is stored beside the bundle (evidence.json), and the queues
re-check it against the files. A directory with no such evidence (a bundle
built locally) is served only on an explicit --local-unpublished, labelled
UNAUTHENTICATED.

THE STORE. fetch installs each bundle into its own immutable directory,
STORE/<id>/{bundle/,evidence.json}, by one rename of a complete directory, then
replaces STORE/current.json (os.replace: atomic). A reader resolves the pointer
ONCE and reads only that immutable directory; no refresh can change or remove
what it reads. Writers are serialized by STORE/.lock. The pointer lists the
installed, authenticated bundles NEWEST MEASUREMENT FIRST (never by publication
time: a backfilled older run does not become current), and gives two answers:
  latest measurement             the newest bundle;
  latest closure-ready bundle    the newest one carrying a closure report.
`repair_queue.py link --closure` reads the second and says so when it is not
the first; a bundle published without a closure report never disables it.

SERVING (serve(): repair_queue.py link --bundle, data_back_rank.py --bundle).
A bundle is served only when it is authenticated, its rules (rules,
shadow_rules, canon_rules) are POSITIVELY this checkout's link_cycle's, and it
was measured at most 24 h ago (the receipt's date; --allow-stale serves an older
one, labelled STALE; it overrides nothing else). Unknown local rules refuse. A
measurement dated in the future is invalid. The link_cycle tool digest is
provenance: a difference under positively equal rules is a warning.

Every refusal carries a REASON, as an exit code and as `[reason=...]`:
  1 corrupt (invalid bundle)   2 unavailable (gh, network, no such directory)
  3 empty (no trusted link-cycle release)   4 stale   5 incompatible-rules
  6 unauthenticated            7 no-closure-report
Only 2 is worth retrying; 4 and 7 end when a newer bundle is published; 1, 5 and
6 need a person. No caller should add --allow-stale on its own.

  python3 tools/cycle_artifacts.py fetch --latest [--store build/cycle_bundles] [--repo OWNER/REPO]
  python3 tools/cycle_artifacts.py fetch --tag link-cycle/<...> [--store DIR]
  python3 tools/cycle_artifacts.py status [STORE]
  python3 tools/cycle_artifacts.py validate STORE_OR_BUNDLE_DIR [--allow-stale] [--local-unpublished]
"""
import argparse
import ast
import calendar
import gzip
import hashlib
import io
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCHEMA = "link-cycle-bundle/2"
STORE_SCHEMA = "link-cycle-store/1"
EVIDENCE_SCHEMA = "link-cycle-evidence/1"
MANIFEST = "manifest.json"
RECEIPT = "receipt.json"
LINK_STATUS = "link_status.csv.gz"
DATA_FOLDS = "data_fold_list.csv.gz"
RANK_TXT = "data_back_rank.txt"
RANK_JSON = "data_back_rank.json"
MEMBERS = (RECEIPT, LINK_STATUS, DATA_FOLDS, RANK_TXT, RANK_JSON)
CLOSURE_GRAPH = "closure_graph.json.gz"
CLOSURE_ROOTS = "closure_roots.json.gz"
CLOSURE_BLOCKERS = "closure_blockers.csv.gz"
CYCLE_DIFF = "cycle_diff.json"
OPTIONAL = (CLOSURE_GRAPH, CLOSURE_ROOTS, CLOSURE_BLOCKERS, CYCLE_DIFF)     # a bundle is valid without them
COMMITTED_RECEIPT = "reverse/link_cycle/receipt.json"
TAG_PREFIX = "link-cycle/"
TAG = re.compile(r"^link-cycle/([0-9a-f]{12})-(\d{8}T\d{6}Z)-([0-9a-f]{12})$")
DEFAULT_REPO = "Open-BFME/Open-BFME-2"
DEFAULT_STORE = ROOT / "build" / "cycle_bundles"
POINTER = "current.json"
EVIDENCE = "evidence.json"
FRESH_HOURS = 24.0
CLOSURE_LOOKBACK = 5                         # older closure-ready releases fetch tries for this checkout's rules
FUTURE_SKEW = 600                            # seconds a measurement may be ahead of this clock
UPSTREAM = "origin/master"

# Who may publish a link-cycle bundle: the GitHub account of the designated measuring
# machine, by login AND numeric id (a login can be renamed and re-registered; the id cannot).
# PLACEHOLDER taken from `gh api user` on bfme-laptop on 2026-10-11: THE MAINTAINER MUST
# CONFIRM THIS LIST before fleets consume a bundle. One tracked place; nothing else is trusted.
PUBLISHERS = ({"login": "Ancalgonn", "id": 1760627},)

EXIT = {"corrupt": 1, "unavailable": 2, "empty": 3, "stale": 4, "incompatible-rules": 5, "unauthenticated": 6,
        "no-closure-report": 7}
EXIT_INVALID, EXIT_UNAVAILABLE, EXIT_EMPTY = EXIT["corrupt"], EXIT["unavailable"], EXIT["empty"]


class Problem(Exception):
    """A bundle that is not served, with a machine-readable reason (EXIT)."""
    reason = "corrupt"


class BundleError(Problem):
    """The bundle (or a published release) is present but not valid."""
    reason = "corrupt"


class Unavailable(Problem):
    """No bundle could be read: gh failed, the release or directory does not exist."""
    reason = "unavailable"


class Empty(Problem):
    """The repository has no trusted, complete link-cycle prerelease at all."""
    reason = "empty"


class Refused(Problem):
    """The bundle is valid but may not be served: stale, incompatible-rules, unauthenticated
    or no-closure-report."""

    def __init__(self, message, reason):
        super().__init__(message)
        assert reason in EXIT, reason
        self.reason = reason


def exit_code(problem):
    return EXIT[problem.reason]


def describe(problem):
    """'refused [reason=stale]: ...': the line a caller prints; the reason is the stable part."""
    kind = ("unavailable" if isinstance(problem, Unavailable) else "empty" if isinstance(problem, Empty)
            else "invalid" if isinstance(problem, BundleError) else "refused")
    return f"{kind} [reason={problem.reason}]: {problem}"


class GhError(Unavailable):
    def __init__(self, args, code, err):
        super().__init__(f"gh {' '.join(args)}: " + (f"exit {code}: " if code is not None else "") + (err or "")[:500])
        self.args_, self.code, self.err = list(args), code, err or ""


class Gh:
    """The gh CLI. run(args) -> stdout text; json(args) -> parsed stdout. Tests pass a fake
    with the same two methods."""

    def __init__(self, exe=None):
        self.exe = exe or os.environ.get("GH") or "gh"

    def run(self, args):
        try:
            got = subprocess.run([self.exe, *args], capture_output=True, text=True, encoding="utf-8",
                                 errors="replace")
        except OSError as e:
            raise GhError(args, None, str(e)) from None
        if got.returncode:
            raise GhError(args, got.returncode, got.stderr.strip())
        return got.stdout

    def json(self, args):
        text = self.run(args)
        return json.loads(text) if text.strip() else None


# ---------------------------------------------------------------- hashing and time

def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def gunzip_sha256(path):
    """(sha256, size) of a gzip member's decompressed content."""
    h, size = hashlib.sha256(), 0
    try:
        with gzip.open(path, "rb") as f:
            for block in iter(lambda: f.read(1 << 20), b""):
                h.update(block)
                size += len(block)
    except (OSError, EOFError) as e:
        raise BundleError(f"{Path(path).name}: not a readable gzip stream ({e})") from None
    return h.hexdigest(), size


def text_bytes(data):
    """A text file's bytes with CRLF read as LF (link_cycle.text_bytes)."""
    return data.replace(b"\r\n", b"\n")


def text_sha256(path):
    return hashlib.sha256(text_bytes(Path(path).read_bytes())).hexdigest()


def digest_of(value):
    """link_cycle.digest_of: sha256 of the sorted-key JSON."""
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def open_text(path):
    """A CSV/text member, gzip or plain (by its magic bytes), as text."""
    path = Path(path)
    with path.open("rb") as handle:
        gz = handle.read(2) == b"\x1f\x8b"
    if gz:
        return io.TextIOWrapper(gzip.open(path), encoding="utf-8", newline="")
    return path.open(encoding="utf-8", newline="")


def parse_utc(text):
    """Seconds since the epoch of '2026-10-11T16:43:32Z' or '2026-10-11 16:43:32' (UTC)."""
    text = text.strip().rstrip("Z").replace("T", " ")
    return calendar.timegm(time.strptime(text, "%Y-%m-%d %H:%M:%S"))


def iso_utc(seconds):
    return time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(seconds))


# ---------------------------------------------------------------- what the receipt says

def receipt_end(receipt):
    """The measurement's end (epoch seconds): the receipt's date_utc. BundleError when unreadable."""
    try:
        return parse_utc(receipt["date_utc"])
    except (KeyError, TypeError, ValueError, AttributeError):
        raise BundleError(f"the receipt has no readable date_utc ({receipt.get('date_utc')!r})") from None


def measured_of(receipt):
    """manifest.measured, derived from the receipt and nothing else."""
    end = receipt_end(receipt)
    total = (receipt.get("seconds") or {}).get("total")
    if total is not None and (not isinstance(total, int) or isinstance(total, bool) or total < 0):
        raise BundleError(f"the receipt's seconds.total is {total!r}")
    return {"start_utc": iso_utc(end - total) if total is not None else None, "end_utc": iso_utc(end),
            "seconds": total,
            "basis": "end: the receipt's date_utc, stamped when the measure finished (before the end-of-run "
                     "re-proof of the inputs); start: end less the receipt's seconds.total, early by at most that "
                     "re-proof's duration"}


def headline_of(receipt):
    """manifest.headline, derived from the receipt's series and nothing else."""
    series = receipt.get("series") or {}
    real = series.get("real") or {}
    return {"credit_unique_bytes": series.get("credit_unique_bytes"),
            **{f"real_{k}_unique_bytes": (real.get(k) or {}).get("unique_bytes")
               for k in ("placed_closed_strict", "placed_self_strict", "placed")}}


def rules_of(receipt):
    return {"rules": receipt.get("rules"), "shadow_rules": receipt.get("shadow_rules") or [],
            "canon_rules": receipt.get("canon_rules")}


def tag_for(receipt_bytes):
    """The tag of the measurement whose receipt.json has these bytes."""
    try:
        receipt = json.loads(receipt_bytes)
        commit = receipt["commit"]
    except (ValueError, KeyError, TypeError):
        raise BundleError("receipt.json is not a link_cycle receipt") from None
    stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime(receipt_end(receipt)))
    return f"{TAG_PREFIX}{commit[:12]}-{stamp}-{hashlib.sha256(receipt_bytes).hexdigest()[:12]}"


def tag_time(tag):
    """The measurement end a tag names (epoch seconds), or None when it is not a bundle tag."""
    m = TAG.match(tag or "")
    if not m:
        return None
    try:
        return calendar.timegm(time.strptime(m.group(2), "%Y%m%dT%H%M%SZ"))
    except ValueError:
        return None


def bundle_id(tag):
    return tag[len(TAG_PREFIX):]


# ---------------------------------------------------------------- link_cycle identity

def local_tool_digest(root=ROOT):
    """link_cycle.tool_digest() of the checkout at ROOT, without importing it (or the
    build module it imports): TOOL_FILES read from its source. None without one."""
    tools = Path(root) / "tools"
    try:
        source = (tools / "link_cycle.py").read_bytes()
    except OSError:
        return None
    files = None
    for node in ast.parse(source).body:
        if (isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == "TOOL_FILES"
                                                 for t in node.targets)):
            files = ast.literal_eval(node.value)
    if not files:
        return None
    h = hashlib.sha256()
    h.update(b"link_cycle.py\0" + text_bytes(source))
    for name in files[1:]:
        try:
            h.update(name.encode() + b"\0" + text_bytes((tools / name).read_bytes()))
        except OSError:
            return None
    return h.hexdigest()


def local_rules(root=ROOT):
    """{"rules", "shadow_rules", "canon_rules"} of the link_cycle at ROOT, read from its
    source without importing it; None when they cannot all be read (no file, or the
    receipt's `rules=` literal is missing or not one value)."""
    try:
        source = (Path(root) / "tools" / "link_cycle.py").read_text(encoding="utf-8")
        tree = ast.parse(source)
    except (OSError, SyntaxError, ValueError):
        return None
    consts, rules = {}, set()
    for node in tree.body:
        if (isinstance(node, ast.Assign) and len(node.targets) == 1 and isinstance(node.targets[0], ast.Name)
                and node.targets[0].id in ("SHADOW_RULES", "CANON_RULES")):
            try:
                consts[node.targets[0].id] = ast.literal_eval(node.value)
            except ValueError:
                return None
    for node in ast.walk(tree):                  # receipt = dict(..., rules="link-cycle-2", ...)
        if (isinstance(node, ast.keyword) and node.arg == "rules" and isinstance(node.value, ast.Constant)
                and isinstance(node.value.value, str)):
            rules.add(node.value.value)
    if len(rules) != 1 or set(consts) != {"SHADOW_RULES", "CANON_RULES"}:
        return None
    return {"rules": rules.pop(), "shadow_rules": list(consts["SHADOW_RULES"]), "canon_rules": consts["CANON_RULES"]}


def link_cycle_module(root=ROOT):
    tools = str(Path(root) / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)
    import link_cycle
    return link_cycle


def core_check(receipt, root=ROOT):
    """Recompute the receipt's core_sha256 (and core_canon_sha256) with link_cycle's own
    receipt_core when this checkout's link_cycle is the one that wrote it (same tool
    digest). Returns how the core was judged; raises BundleError when it was recomputed
    and differs. A core that is NOT recomputed is unverified here, not verified elsewhere."""
    local = local_tool_digest(root)
    theirs = receipt.get("tool_digest") or ""
    if local is None:
        return "not recomputed: no tools/link_cycle.py in this checkout"
    if local != theirs:
        return (f"not recomputed: this checkout's link_cycle digest {local[:12]} is not the receipt's "
                f"{theirs[:12] or '(none)'}")
    try:
        lc = link_cycle_module(root)
    except Exception as e:                       # noqa: BLE001 - any import failure leaves it unjudged
        return f"not recomputed: link_cycle did not import ({type(e).__name__}: {e})"
    copy = json.loads(json.dumps(receipt))
    lc.stamp_cores(copy)
    for key in ("core_sha256", "core_canon_sha256"):
        if key in receipt and copy.get(key) != receipt[key]:
            raise BundleError(f"receipt {key} {receipt[key][:16]} does not digest its contents "
                              f"({copy.get(key, '')[:16]}): the receipt was edited after link_cycle wrote it")
    return f"recomputed with link_cycle {local[:12]}"


# ---------------------------------------------------------------- validation (integrity)

def read_manifest(directory):
    path = Path(directory) / MANIFEST
    if not path.is_file():
        raise BundleError(f"{directory}: no {MANIFEST}")
    try:
        manifest = json.loads(path.read_text(encoding="utf-8"))
    except ValueError as e:
        raise BundleError(f"{path}: not JSON ({e})") from None
    if not isinstance(manifest, dict) or manifest.get("schema") != SCHEMA:
        raise BundleError(f"{path}: schema {manifest.get('schema') if isinstance(manifest, dict) else None!r}, "
                          f"expected {SCHEMA!r}")
    return manifest


def read_member(path):
    """A member's content, gunzipped when it is gzip."""
    data = Path(path).read_bytes()
    try:
        return gzip.decompress(data) if data[:2] == b"\x1f\x8b" else data
    except (OSError, EOFError) as e:
        raise BundleError(f"{Path(path).name}: not a readable gzip stream ({e})") from None


def validate(directory, *, root=ROOT, recompute_core=True):
    """The manifest of a self-consistent bundle at DIRECTORY; BundleError naming the first
    fault. Unavailable when there is no such directory. Integrity only: who published it is
    fetch's question (authenticate_local)."""
    d = Path(directory)
    if not d.is_dir():
        raise Unavailable(f"no bundle at {d}")
    manifest = read_manifest(d)
    members = manifest.get("members")
    if not isinstance(members, dict):
        raise BundleError(f"{MANIFEST}: no members table")
    missing = [m for m in MEMBERS if m not in members]
    if missing:
        raise BundleError(f"{MANIFEST}: lists no {', '.join(missing)}")
    for name, meta in sorted(members.items()):
        if name not in MEMBERS + OPTIONAL:
            raise BundleError(f"{MANIFEST}: bad member name {name!r} (a {SCHEMA} bundle holds "
                              f"{', '.join(MEMBERS + OPTIONAL)})")
        if not isinstance(meta, dict):
            raise BundleError(f"{MANIFEST}: member {name} has no size and sha256")
        path = d / name
        if not path.is_file():
            raise BundleError(f"member {name} is missing")
        size = path.stat().st_size
        if size != meta.get("size"):
            raise BundleError(f"member {name}: {size} bytes, the manifest says {meta.get('size')}")
        got = sha256_file(path)
        if got != meta.get("sha256"):
            raise BundleError(f"member {name}: sha256 {got[:16]}, the manifest says {str(meta.get('sha256'))[:16]}")
        if meta.get("content_sha256"):
            content, csize = gunzip_sha256(path)
            if content != meta["content_sha256"] or csize != meta.get("content_size"):
                raise BundleError(f"member {name}: decompressed content {content[:16]} ({csize} bytes) is not "
                                  f"the manifest's {meta['content_sha256'][:16]} ({meta.get('content_size')} bytes)")
    extra = sorted(p.name for p in d.iterdir() if p.name != MANIFEST and p.name not in members)
    if extra:
        raise BundleError(f"unlisted file(s) in the bundle: {', '.join(extra)}")
    raw = (d / RECEIPT).read_bytes()
    try:
        receipt = json.loads(raw)
    except ValueError as e:
        raise BundleError(f"{RECEIPT}: not JSON ({e})") from None
    if not isinstance(receipt, dict):
        raise BundleError(f"{RECEIPT}: not a receipt")
    want = manifest.get("receipt") or {}
    commit = manifest.get("commit") or ""
    if len(commit) != 40 or receipt.get("commit") != commit:
        raise BundleError(f"the receipt measures {receipt.get('commit')!r}, the manifest names {commit!r}")
    if not receipt.get("core_sha256") or receipt.get("core_sha256") != want.get("core_sha256"):
        raise BundleError(f"the receipt's core {str(receipt.get('core_sha256'))[:16]} is not the manifest's "
                          f"{str(want.get('core_sha256'))[:16]}")
    if receipt.get("authoritative") is not True:
        raise BundleError("the receipt is not authoritative")
    status_sha = (receipt.get("series") or {}).get("link_status_sha256")
    if not status_sha or status_sha != want.get("link_status_sha256"):
        raise BundleError("the receipt's link_status_sha256 is not the manifest's")
    if members[LINK_STATUS].get("content_sha256") != status_sha:
        raise BundleError(f"{LINK_STATUS} decompresses to {str(members[LINK_STATUS].get('content_sha256'))[:16]}, "
                          f"the receipt measured {status_sha[:16]}")
    tag = tag_for(raw)
    if manifest.get("tag") != tag:
        raise BundleError(f"tag {manifest.get('tag')!r} is not {tag!r}, the tag this receipt's bytes name")
    check_repeats(manifest, receipt, raw)
    said = manifest.get("rules") or {}
    rules = rules_of(receipt)
    if {k: said.get(k) for k in rules} != rules or said.get("digest") != digest_of(rules):
        raise BundleError(f"the manifest's rules {said.get('rules')!r} (digest {str(said.get('digest'))[:12]}) are "
                          f"not the receipt's {rules['rules']!r} ({digest_of(rules)[:12]})")
    if manifest.get("tool_digest") != receipt.get("tool_digest"):
        raise BundleError("the manifest's tool_digest is not the receipt's")
    check_closure(d, manifest, receipt)
    check_cycle_diff(d, manifest, receipt)
    if recompute_core:
        core_check(receipt, root)
    return manifest


def check_repeats(manifest, receipt, raw):
    """Everything the manifest repeats from the receipt is derived again and must agree: a
    manifest edit cannot move the measurement's time, its headline or its identity."""
    def same(what, said, derived):
        if said != derived and isinstance(said, dict) and isinstance(derived, dict):
            keys = sorted(k for k in set(said) | set(derived) if said.get(k) != derived.get(k))
            said, derived = {k: said.get(k) for k in keys}, {k: derived.get(k) for k in keys}
        if said != derived:
            raise BundleError(f"the manifest's {what} ({json.dumps(said, sort_keys=True)[:120]}) is not what the "
                              f"receipt says ({json.dumps(derived, sort_keys=True)[:120]})")
    measured = measured_of(receipt)
    same("measured", manifest.get("measured"), measured)
    same("headline", manifest.get("headline"), headline_of(receipt))
    same("instance", manifest.get("instance"), {"measured_end_utc": measured["end_utc"],
                                               "receipt_sha256": hashlib.sha256(raw).hexdigest()})
    same("submodules", manifest.get("submodules"), receipt.get("submodules") or {})
    same("bfme1_pointer", manifest.get("bfme1_pointer"), (receipt.get("submodules") or {}).get("reference/open-bfme-1"))
    want = manifest.get("receipt") or {}
    same("receipt.core_canon_sha256", want.get("core_canon_sha256"), receipt.get("core_canon_sha256"))
    same("receipt.tree_manifest", want.get("tree_manifest"), receipt.get("tree_manifest"))
    same("receipt.closure_graph_sha256", want.get("closure_graph_sha256"), receipt.get("closure_graph_sha256"))
    if not str(manifest.get("producer") or "").strip():
        raise BundleError("the manifest names no producer")
    try:
        created = parse_utc(manifest["created_utc"])
    except (KeyError, TypeError, ValueError, AttributeError):
        raise BundleError(f"the manifest's created_utc is unreadable ({manifest.get('created_utc')!r})") from None
    if created + FUTURE_SKEW < receipt_end(receipt):
        raise BundleError(f"the bundle was created ({manifest['created_utc']}) before its measurement ended "
                          f"({measured['end_utc']})")


def check_closure(d, manifest, receipt):
    """The optional closure components against the members, the receipt and each other.
    closure_graph.json.gz is the file the receipt names; the report is both files or
    neither, as components.closure_report declares, and names this run and where its graph
    came from: bound to the receipt's graph, or labelled a replay."""
    members = manifest["members"]
    said = (manifest.get("components") or {}).get("closure_report") or {}
    bound = receipt.get("closure_graph_sha256")
    if CLOSURE_GRAPH in members:
        if not bound or members[CLOSURE_GRAPH].get("sha256") != bound:
            raise BundleError(f"{CLOSURE_GRAPH} is not the graph the receipt names "
                              f"(closure_graph_sha256 {str(bound)[:16]})")
    have = [m for m in (CLOSURE_ROOTS, CLOSURE_BLOCKERS) if m in members]
    if len(have) == 1:
        raise BundleError(f"{have[0]} without its companion: the closure report is both files or neither")
    if bool(said.get("included")) != bool(have):
        raise BundleError(f"{MANIFEST}: components.closure_report.included is {said.get('included')!r} but the "
                          f"bundle holds {'both' if have else 'neither'} of its files")
    if not have:
        if not str(said.get("why") or "").strip():
            raise BundleError(f"{MANIFEST}: no closure report and no reason given (components.closure_report.why)")
        return
    try:
        doc = json.loads(read_member(d / CLOSURE_ROOTS).decode("utf-8"))
    except ValueError as e:
        raise BundleError(f"{CLOSURE_ROOTS}: not JSON ({e})") from None
    if not isinstance(doc, dict) or not str(doc.get("schema", "")).startswith("closure-report/"):
        raise BundleError(f"{CLOSURE_ROOTS}: schema {doc.get('schema') if isinstance(doc, dict) else None!r}")
    for key in ("schema", "algorithm"):
        if said.get(key) != doc.get(key):
            raise BundleError(f"{MANIFEST}: components.closure_report.{key} {said.get(key)!r} is not "
                              f"{CLOSURE_ROOTS}'s {doc.get(key)!r}")
    for key, want in (("commit", receipt["commit"]), ("receipt_core_sha256", receipt["core_sha256"]),
                      ("link_status_sha256", receipt["series"]["link_status_sha256"])):
        if doc.get(key) != want:
            raise BundleError(f"{CLOSURE_ROOTS}: {key} {str(doc.get(key))[:16]} is not this run's {want[:16]}: the "
                              "closure report describes another run")
    if (doc.get("blockers") or {}).get("sha256") != members[CLOSURE_BLOCKERS].get("content_sha256"):
        raise BundleError(f"{CLOSURE_BLOCKERS} is not the table {CLOSURE_ROOTS} names")
    credit = (receipt.get("series") or {}).get("credit_unique_bytes")
    if (doc.get("summary") or {}).get("credit_unique_bytes") != credit:
        raise BundleError(f"{CLOSURE_ROOTS}: its graph credits "
                          f"{(doc.get('summary') or {}).get('credit_unique_bytes')}, the receipt {credit}")
    graph = doc.get("graph") or {}
    if graph.get("bound"):
        if not bound or graph.get("sha256") != bound:
            raise BundleError(f"{CLOSURE_ROOTS} says its graph is bound to the receipt, but its graph "
                              f"{str(graph.get('sha256'))[:16]} is not the receipt's closure_graph_sha256 "
                              f"{str(bound)[:16]}")
    elif bound:
        raise BundleError(f"{CLOSURE_ROOTS} is a replay, but this run's receipt names a measured graph: analyse "
                          "that graph (tools/closure_report.py graph)")
    if said.get("graph") != graph.get("label"):
        raise BundleError(f"{MANIFEST}: components.closure_report.graph {said.get('graph')!r} is not the report's "
                          f"{graph.get('label')!r}")


def check_cycle_diff(d, manifest, receipt):
    """The optional credit comparison: a cycle_diff report whose NEW run is this one, and
    whose OLD run is the predecessor the manifest names (none: a report without a comparison)."""
    said = (manifest.get("components") or {}).get("cycle_diff") or {}
    if CYCLE_DIFF not in manifest["members"]:
        if said.get("included"):
            raise BundleError(f"{MANIFEST} says {CYCLE_DIFF} is included; it is not a member")
        if not str(said.get("why") or "").strip():
            raise BundleError(f"{MANIFEST}: no {CYCLE_DIFF} and no reason given (components.cycle_diff.why)")
        return
    try:
        doc = json.loads((d / CYCLE_DIFF).read_text(encoding="utf-8"))
    except ValueError as e:
        raise BundleError(f"{CYCLE_DIFF}: not JSON ({e})") from None
    if not isinstance(doc, dict) or not isinstance(doc.get("schema_version"), int):
        raise BundleError(f"{CYCLE_DIFF}: no schema_version")
    ident = doc.get("identity") or {}
    new, old = ident.get("new") or {}, ident.get("old")
    if new.get("commit") != receipt["commit"] or new.get("core_sha256") != receipt["core_sha256"]:
        raise BundleError(f"{CYCLE_DIFF}: its NEW run {str(new.get('commit'))[:12]} is not this bundle's")
    if not said.get("included") or said.get("schema_version") != doc["schema_version"]:
        raise BundleError(f"{MANIFEST}: components.cycle_diff does not describe {CYCLE_DIFF}")
    pred = said.get("predecessor")
    if bool(doc.get("comparison")) != (pred is not None) or (old is None) != (pred is None):
        raise BundleError(f"{CYCLE_DIFF}: comparison={doc.get('comparison')!r} but the manifest's predecessor is "
                          f"{'named' if pred else 'none'}")
    if pred and (old.get("commit") != pred.get("commit") or old.get("core_sha256") != pred.get("core_sha256")):
        raise BundleError(f"{CYCLE_DIFF}: its OLD run {str(old.get('commit'))[:12]} is not the manifest's predecessor "
                          f"{str(pred.get('commit'))[:12]}")
    if pred and (tag_time(pred.get("tag")) is None or not pred.get("receipt_sha256")
                 or not pred["tag"].endswith(pred["receipt_sha256"][:12])):
        raise BundleError(f"{MANIFEST}: the predecessor is not named by its measurement ({pred.get('tag')!r})")


class Bundle:
    """A validated bundle: dir, manifest, receipt, tag, commit and paths by member name;
    `evidence` (how it was authenticated, or None: local and unpublished) and `notes`
    (which bundle of a store was chosen, and why) are set by serve()."""

    def __init__(self, directory, manifest, receipt, core="not checked"):
        self.dir = Path(directory)
        self.manifest = manifest
        self.receipt = receipt
        self.core_check = core
        self.tag = manifest["tag"]
        self.commit = manifest["commit"]
        self.paths = {name: self.dir / name for name in manifest["members"]}
        self.paths[MANIFEST] = self.dir / MANIFEST
        self.evidence = None
        self.notes = []

    link_status = property(lambda self: self.paths[LINK_STATUS])
    data_fold_list = property(lambda self: self.paths[DATA_FOLDS])
    rank_txt = property(lambda self: self.paths[RANK_TXT])
    rank_json = property(lambda self: self.paths[RANK_JSON])
    closure_graph = property(lambda self: self.paths.get(CLOSURE_GRAPH))        # None: not in this bundle
    closure_roots = property(lambda self: self.paths.get(CLOSURE_ROOTS))
    closure_blockers = property(lambda self: self.paths.get(CLOSURE_BLOCKERS))
    cycle_diff = property(lambda self: self.paths.get(CYCLE_DIFF))

    def diagnostic(self, rel):
        """The measured commit's text_sha256 of a diagnostic input (reverse/data_ledger.csv), or None."""
        return ((self.manifest.get("diagnostic_inputs") or {}).get("files") or {}).get(rel, {}).get("text_sha256")

    def freshness(self, now=None, root=ROOT, ref=UPSTREAM, max_age_hours=FRESH_HOURS):
        return freshness(self.receipt, now=now, root=root, ref=ref, max_age_hours=max_age_hours)


def load_bundle(directory, *, root=ROOT):
    """Bundle at DIRECTORY, validated, its receipt core recomputed when this checkout's
    link_cycle wrote it. Raises Unavailable (no directory) or BundleError (invalid)."""
    manifest = validate(directory, root=root, recompute_core=False)
    receipt = json.loads((Path(directory) / RECEIPT).read_text(encoding="utf-8"))
    return Bundle(directory, manifest, receipt, core_check(receipt, root))


# ---------------------------------------------------------------- freshness and compatibility

def _git(root, *args):
    try:
        return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True)
    except OSError:
        return None


def ancestry(commit, root=ROOT, ref=UPSTREAM):
    """(is_ancestor True/False/None, commits behind or None, note). ROOT must itself be the
    top of a git checkout: a directory that merely sits inside one is not asked about it."""
    top = _git(root, "rev-parse", "--show-toplevel")
    try:
        is_top = top is not None and top.returncode == 0 and Path(top.stdout.strip()).resolve() == Path(root).resolve()
    except OSError:
        is_top = False
    if not is_top:
        return None, None, f"ancestry unknown: {root} is not a git checkout"
    have = _git(root, "rev-parse", "--verify", "--quiet", ref + "^{commit}")
    if have is None or have.returncode:
        return None, None, f"ancestry unknown: no local {ref} here"
    known = _git(root, "cat-file", "-e", commit + "^{commit}")
    if known is None or known.returncode:
        return None, None, f"ancestry unknown: {commit[:12]} is not in this clone (git fetch origin)"
    got = _git(root, "merge-base", "--is-ancestor", commit, ref)
    if got is None or got.returncode not in (0, 1):
        return None, None, "ancestry unknown: git merge-base failed" + (f" ({got.stderr.strip()[:200]})" if got else "")
    if got.returncode == 1:
        return False, None, (f"the measured commit is NOT an ancestor of local {ref} (another line, or a "
                             f"{ref} older than the run: git fetch origin)")
    count = _git(root, "rev-list", "--count", f"{commit}..{ref}")
    behind = int(count.stdout.strip()) if count.returncode == 0 and count.stdout.strip().isdigit() else None
    return True, behind, (f"the measured commit is an ancestor of local {ref}, "
                          + (f"{behind} commit(s) behind it" if behind is not None else "distance unknown")
                          + " (information only; git fetch origin for a current count)")


def freshness(receipt, now=None, root=ROOT, ref=UPSTREAM, max_age_hours=FRESH_HOURS):
    """How old the measurement is (from the RECEIPT's date), where its commit stands and
    whether its rules are this checkout's."""
    now = time.time() if now is None else now
    end = receipt_end(receipt)
    age = (now - end) / 3600.0
    anc, behind, note = ancestry(receipt["commit"], root, ref)
    local = local_tool_digest(root)
    theirs = receipt.get("tool_digest")
    mine = local_rules(root)
    said = rules_of(receipt)
    return {"rules": said["rules"], "bundle_rules": said, "local_rules": mine,
            "rules_match": None if mine is None else mine == said,
            "measured_end_utc": iso_utc(end), "age_hours": round(age, 2), "future": now + FUTURE_SKEW < end,
            "max_age_hours": max_age_hours, "stale": age > max_age_hours,
            "ref": ref, "ancestor": anc, "behind": behind, "ancestry": note,
            "tool_digest": theirs,
            "tool_digest_matches": None if local is None or not theirs else local == theirs,
            "local_tool_digest": local}


def rules_text(rules):
    return (f"{rules.get('rules')} (shadow {', '.join(rules.get('shadow_rules') or ()) or 'none'}; "
            f"{rules.get('canon_rules')})")


def format_freshness(bundle, fr):
    """Report lines; a STALE line starts with 'STALE', a rules problem with 'RULES'."""
    m = measured_of(bundle.receipt)
    lines = [f"bundle {bundle.tag}: commit {bundle.commit[:12]}, measured {m['start_utc'] or '?'} .. {m['end_utc']} "
             f"by {bundle.manifest.get('producer')}"]
    if fr["stale"]:
        lines.append(f"STALE: measured {fr['age_hours']:.1f} h ago, over the {fr['max_age_hours']:g} h "
                     f"window; its verdicts may no longer describe {fr['ref']}")
    else:
        lines.append(f"age {fr['age_hours']:.1f} h, within the {fr['max_age_hours']:g} h window")
    lines.append(fr["ancestry"])
    if fr["rules_match"] is False:
        lines.append(f"RULES MISMATCH: measured under {rules_text(fr['bundle_rules'])}; this checkout's "
                     f"link_cycle measures {rules_text(fr['local_rules'])}")
    elif fr["rules_match"] is None:
        lines.append(f"RULES UNKNOWN: measured under {fr['rules']}; this checkout's tools/link_cycle.py rules "
                     "cannot be read, so compatibility is not established")
    else:
        lines.append(f"rules {fr['rules']}: this checkout's")
        if fr["tool_digest_matches"] is True:
            lines.append("link_cycle tool digest: this checkout's")
        elif fr["tool_digest_matches"] is False:
            lines.append(f"link_cycle tool digest {str(fr['tool_digest'])[:12]} is not this checkout's "
                         f"{fr['local_tool_digest'][:12]}: equal rules, another build of the tool (a warning: equal "
                         "rules do not prove a changed tool cannot change a verdict)")
    return lines


def refusal(fr, allow_stale=False):
    """(reason, text) why a consumer may not serve a bundle of freshness FR, or None.
    Compatibility must be established; --allow-stale overrides age and nothing else."""
    if fr["rules_match"] is False:
        return ("incompatible-rules",
                f"RULES MISMATCH: measured under {fr['rules']}, not this checkout's link_cycle rules "
                f"{rules_text(fr['local_rules'])}: its verdicts answer another question (update the checkout, or "
                "wait for a bundle measured under these rules); there is no override")
    if fr["rules_match"] is None:
        return ("incompatible-rules",
                f"RULES UNKNOWN: measured under {fr['rules']}, and this checkout's tools/link_cycle.py rules cannot "
                "be read: compatibility is not established (run from a checkout with link_cycle.py); there is no "
                "override")
    if fr["stale"] and not allow_stale:
        return ("stale",
                f"STALE: measured {fr['age_hours']:.1f} h ago, over the {fr['max_age_hours']:g} h window (fetch a "
                "newer bundle: python3 tools/cycle_artifacts.py fetch --latest; or pass --allow-stale to be served "
                "it, labelled)")
    return None


# ---------------------------------------------------------------- authentication

def publisher_ok(author):
    return any(isinstance(author, dict) and author.get("login") == p["login"] and author.get("id") == p["id"]
               for p in PUBLISHERS)


def publishers_text():
    return ", ".join(f"{p['login']} (id {p['id']})" for p in PUBLISHERS)


def release_trust(release, allow_mutable=False):
    """Why RELEASE is not a trusted publication, or None: its author is a designated
    publisher and GitHub reports it immutable."""
    author = release.get("author") or {}
    if not publisher_ok(author):
        return (f"author {author.get('login')!r} (id {author.get('id')!r}) is not a designated publisher "
                f"({publishers_text()})")
    if release.get("immutable") is not True and not allow_mutable:
        return ("the release is not immutable (GitHub reports immutable="
                f"{release.get('immutable')!r}): its assets and tag can be replaced. The maintainer enables "
                "immutable releases in the repository settings; --allow-mutable only exercises fetch")
    return None


def tag_commit(gh, repo, tag):
    """The commit TAG resolves to on REPO, annotated tags peeled; Refused when there is none."""
    try:
        ref = gh.json(["api", f"repos/{repo}/git/ref/tags/{tag}"]) or {}
        obj = ref.get("object") or {}
        for _ in range(4):
            if obj.get("type") != "tag":
                break
            obj = (gh.json(["api", f"repos/{repo}/git/tags/{obj.get('sha')}"]) or {}).get("object") or {}
    except GhError as e:
        raise Refused(f"the tag {tag} cannot be resolved on {repo} ({e.err.strip()[:200]})", "unauthenticated") from None
    if obj.get("type") != "commit" or not obj.get("sha"):
        raise Refused(f"the tag {tag} does not resolve to a commit ({obj.get('type')!r})", "unauthenticated")
    return obj["sha"]


def attest(gh, repo, tag):
    """`gh release verify TAG`: 'verified', or 'not run: ...' when this gh has no such
    command; Refused when the verification itself fails."""
    try:
        gh.run(["release", "verify", tag, "--repo", repo])
    except GhError as e:
        if e.code is None or "unknown command" in e.err or "unknown flag" in e.err:
            return "not run: this gh has no `release verify` (gh 2.81 or newer)"
        raise Refused(f"`gh release verify {tag}` failed ({e.err.strip()[:300]})", "unauthenticated") from None
    return "verified"


def authenticate_local(bundle, root=ROOT):
    """The evidence fetch stored beside BUNDLE (its directory's sibling evidence.json),
    re-checked against the files; Refused(unauthenticated) when there is none, it is not this
    bundle's, or it records a release that was not immutable."""
    path = bundle.dir.parent / EVIDENCE
    try:
        ev = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        raise Refused(f"bundle {bundle.tag} at {bundle.dir} has no fetch evidence ({path.name}): it is a local "
                      "directory, not an authenticated publication (python3 tools/cycle_artifacts.py fetch; a "
                      "producer inspecting its own unpublished bundle passes --local-unpublished)",
                      "unauthenticated") from None
    if ev.get("schema") != EVIDENCE_SCHEMA or ev.get("tag") != bundle.tag:
        raise Refused(f"{path} is not the evidence of {bundle.tag}", "unauthenticated")
    if ev.get("manifest_sha256") != sha256_file(bundle.dir / MANIFEST):
        raise Refused(f"{bundle.dir / MANIFEST} is not the manifest that was authenticated", "unauthenticated")
    for name in list(bundle.manifest["members"]) + [MANIFEST]:
        want = ((ev.get("assets") or {}).get(name) or {}).get("sha256")
        if not want or want != sha256_file(bundle.dir / name):
            raise Refused(f"{name} is not the asset that was authenticated", "unauthenticated")
    if not publisher_ok(ev.get("author")):
        raise Refused(f"bundle {bundle.tag} was published by {(ev.get('author') or {}).get('login')!r}, who is not a "
                      f"designated publisher ({publishers_text()})", "unauthenticated")
    if ev.get("tag_commit") != bundle.commit:
        raise Refused(f"the tag of {bundle.tag} resolved to {str(ev.get('tag_commit'))[:12]}, not the measured commit",
                      "unauthenticated")
    if ev.get("immutable") is not True:
        raise Refused(f"bundle {bundle.tag} was fetched with --allow-mutable from a release that is NOT immutable: "
                      "it is not authenticated and is not served", "unauthenticated")
    return ev


# ---------------------------------------------------------------- the store

def store_lock(store, wait=120.0, stale=900.0):
    """Take STORE/.lock (exclusive create); a lock older than STALE seconds is a dead
    writer's and is broken. Returns the path to remove."""
    store = Path(store)
    store.mkdir(parents=True, exist_ok=True)
    lock = store / ".lock"
    deadline = time.monotonic() + wait
    while True:
        try:
            fd = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, f"{os.getpid()} {iso_utc(time.time())}\n".encode())
            os.close(fd)
            return lock
        except FileExistsError:
            try:
                if time.time() - lock.stat().st_mtime > stale:
                    lock.unlink()
                    continue
            except OSError:
                continue
            if time.monotonic() > deadline:
                raise Unavailable(f"{lock} is held by another fetch") from None
            time.sleep(0.2)


def installed(store, root=ROOT):
    """[pointer entry] of every bundle installed in STORE with evidence, newest MEASUREMENT
    first (the receipt's date; ties by id)."""
    out = []
    for d in sorted(Path(store).iterdir()) if Path(store).is_dir() else ():
        if d.name.startswith(".") or not (d / EVIDENCE).is_file() or not (d / "bundle" / MANIFEST).is_file():
            continue
        try:
            manifest = read_manifest(d / "bundle")
            ev = json.loads((d / EVIDENCE).read_text(encoding="utf-8"))
        except (BundleError, ValueError, OSError):
            continue
        comp = (manifest.get("components") or {}).get("closure_report") or {}
        out.append({"id": d.name, "tag": manifest.get("tag"),
                    "measured_end_utc": (manifest.get("measured") or {}).get("end_utc"),
                    "commit": manifest.get("commit"), "rules": (manifest.get("rules") or {}).get("rules"),
                    "rules_tuple": rules_of(manifest.get("rules") or {}),
                    "closure_report": bool(comp.get("included")), "closure_graph": comp.get("graph"),
                    "why_no_closure_report": None if comp.get("included") else comp.get("why"),
                    "authenticated": ev.get("immutable") is True})
    out.sort(key=lambda e: (e["measured_end_utc"] or "", e["id"]), reverse=True)
    return out


def write_pointer(store, now=None):
    """Replace STORE/current.json atomically with the installed bundles, newest measurement first."""
    store = Path(store)
    entries = installed(store)
    trusted = [e for e in entries if e["authenticated"]]
    doc = {"schema": STORE_SCHEMA, "written_utc": iso_utc(time.time() if now is None else now),
           "order": "newest measurement first (the receipt's date), never publication time",
           "latest_measurement": trusted[0]["id"] if trusted else None,
           "latest_closure_ready": next((e["id"] for e in trusted if e["closure_report"]), None),
           "bundles": entries}
    fd, tmp = tempfile.mkstemp(prefix=".current-", suffix=".json", dir=store)
    with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(doc, indent=1, sort_keys=True) + "\n")
    os.replace(tmp, store / POINTER)
    return doc


def read_pointer(store):
    """STORE/current.json, read once; Unavailable when the store has none."""
    path = Path(store) / POINTER
    try:
        doc = json.loads(path.read_text(encoding="utf-8"))
    except OSError:
        raise Unavailable(f"no bundle store at {store} (python3 tools/cycle_artifacts.py fetch --latest)") from None
    except ValueError as e:
        raise BundleError(f"{path}: not JSON ({e})") from None
    if not isinstance(doc, dict) or doc.get("schema") != STORE_SCHEMA:
        raise BundleError(f"{path}: not a {STORE_SCHEMA} pointer")
    return doc


def closure_choice(doc, root=ROOT):
    """(id, compatible) of the bundle the closure queue serves from pointer DOC: the newest
    authenticated closure-ready bundle measured under exactly this checkout's rules (rules,
    shadow rules and canon rules together). When this checkout's rules cannot be read, or
    no such bundle is installed, the newest authenticated closure-ready bundle with
    compatible False, which serve() then refuses by its rules; (None, False) when the
    store holds none. resolve() and status() both ask here, so what status names is what a
    queue is served."""
    mine = local_rules(root)
    ready = [e for e in doc.get("bundles") or () if e.get("authenticated") and e.get("closure_report")]
    if mine is not None:
        for e in ready:
            if e.get("rules_tuple") == mine:
                return e["id"], True
    return (ready[0]["id"] if ready else None), False


def resolve(path, need_closure=False, root=ROOT):
    """(bundle directory, notes) for PATH: a bundle directory itself, or a store, whose
    pointer is read ONCE and names an immutable directory. With NEED_CLOSURE the bundle
    closure_choice() names; the notes say when that is not the newest measurement."""
    path = Path(path)
    if (path / MANIFEST).is_file():
        return path, []
    if not path.is_dir():
        raise Unavailable(f"no bundle at {path}")
    doc = read_pointer(path)
    entries = {e["id"]: e for e in doc.get("bundles") or ()}
    latest = doc.get("latest_measurement")
    if latest is None:
        raise Empty(f"the store at {path} holds no authenticated bundle")
    chosen = latest
    notes = []
    if need_closure:
        chosen, _ = closure_choice(doc, root)
        if chosen is None:
            why = entries.get(latest, {}).get("why_no_closure_report") or "not recorded"
            raise Refused(f"no bundle in the store at {path} carries a closure report (the newest measurement, "
                          f"{entries.get(latest, {}).get('tag')}: {why}); nothing else is served in its place",
                          "no-closure-report")
        if chosen != latest:
            new, old = entries[latest], entries[chosen]
            why = (f"carries one measured under other link_cycle rules "
                   f"({rules_text(new.get('rules_tuple') or {'rules': new.get('rules')})})"
                   if new.get("closure_report") else f"was published without one ({new['why_no_closure_report']})")
            notes.append(f"NOT THE NEWEST MEASUREMENT: serving {old['tag']} (measured {old['measured_end_utc']}), the "
                         f"newest bundle with a closure report; the newer {new['tag']} (measured "
                         f"{new['measured_end_utc']}) {why}")
    return path / chosen / "bundle", notes


def serve(path, *, allow_stale=False, now=None, root=ROOT, need_closure=False, local_unpublished=False):
    """(bundle, freshness, report lines) of the bundle a queue may serve from PATH (a store
    or a bundle directory): validated; authenticated by its stored fetch evidence unless
    LOCAL_UNPUBLISHED (then labelled); of positively this checkout's rules; and fresh, or
    ALLOW_STALE. Raises a Problem with its reason; a consumer never falls back."""
    directory, notes = resolve(path, need_closure, root)
    bundle = load_bundle(directory, root=root)
    bundle.notes = notes
    if local_unpublished:
        bundle.notes.append("UNAUTHENTICATED LOCAL BUNDLE (--local-unpublished): a directory on this machine, not a "
                            "published measurement; do not steer shared work by it")
    else:
        bundle.evidence = authenticate_local(bundle, root)
    fr = bundle.freshness(now=now, root=root)
    if fr["future"]:
        raise BundleError(f"bundle {bundle.tag}: measured {fr['measured_end_utc']}, {-fr['age_hours']:.1f} h in the "
                          "future of this clock: not a measurement that has happened")
    why = refusal(fr, allow_stale)
    if why:
        raise Refused(f"bundle {bundle.tag}: {why[1]}", why[0])
    if need_closure and bundle.closure_roots is None:
        said = ((bundle.manifest.get("components") or {}).get("closure_report") or {}).get("why") or "not recorded"
        raise Refused(f"bundle {bundle.tag} carries no closure report ({said}); nothing else is served in its place",
                      "no-closure-report")
    return bundle, fr, format_freshness(bundle, fr) + bundle.notes


def history_note(root=ROOT):
    """One line placing the committed receipt (reverse/link_cycle/receipt.json) as history
    beside a published bundle; None when the checkout has none."""
    try:
        r = json.loads((Path(root) / COMMITTED_RECEIPT).read_text(encoding="utf-8"))
        credit = (r.get("series") or {}).get("credit_unique_bytes")
        return (f"history: the committed {COMMITTED_RECEIPT} (commit {str(r.get('commit'))[:12]}, "
                f"{r.get('date_utc')} UTC, credit {credit:,} B) is an earlier measurement, no longer updated; the "
                "newest published bundle is the current figure")
    except (OSError, ValueError, TypeError):
        return None


def headline(bundle):
    """The bundle's figures, read from its validated receipt."""
    h = headline_of(bundle.receipt)
    num = (lambda v: f"{v:,} B" if isinstance(v, int) else "?")
    return (f"link-cycle figure of this bundle: credit {num(h.get('credit_unique_bytes'))} (placed closed-strict "
            f"real unique bytes); self-strict {num(h.get('real_placed_self_strict_unique_bytes'))}; placed "
            f"{num(h.get('real_placed_unique_bytes'))}")


# ---------------------------------------------------------------- GitHub releases

def list_releases(gh, repo):
    """Every release of REPO (drafts too when the token may see them), REST order."""
    pages = gh.json(["api", "--paginate", "--slurp", f"repos/{repo}/releases?per_page=100"]) or []
    out = []
    for page in pages:
        out.extend(page if isinstance(page, list) else [page])
    return out


def release_problem(release):
    """Why RELEASE is not a complete link-cycle prerelease, or None."""
    if tag_time(release.get("tag_name")) is None:
        return "not a link-cycle measurement tag"
    if release.get("draft"):
        return "draft (not published)"
    if not release.get("prerelease"):
        return "not a prerelease"
    state = {a.get("name"): a.get("state") for a in release.get("assets") or ()}
    missing = [m for m in (MANIFEST,) + MEMBERS if state.get(m) != "uploaded"]
    missing += [m for m in OPTIONAL if m in state and state[m] != "uploaded"]
    if missing:
        return "incomplete: no uploaded " + ", ".join(missing)
    extra = sorted(set(state) - set((MANIFEST,) + MEMBERS + OPTIONAL))
    if extra:
        return "holds assets that are not bundle members: " + ", ".join(extra)
    return None


def candidates(releases, tag=None, allow_mutable=False):
    """([trusted complete link-cycle prereleases, newest MEASUREMENT first], [(tag, why skipped)])."""
    link = [r for r in releases if str(r.get("tag_name", "")).startswith(TAG_PREFIX)]
    if tag is not None:
        link = [r for r in link if r.get("tag_name") == tag]
    good, skipped = [], []
    for r in link:
        why = release_problem(r)
        if why is None:
            why = release_trust(r, allow_mutable)
            why = why and "UNTRUSTED: " + why
        if why:
            skipped.append((r.get("tag_name"), why))
        else:
            good.append(r)
    good.sort(key=lambda r: (tag_time(r["tag_name"]), r["tag_name"]), reverse=True)
    return good, skipped


def has_closure(release):
    names = {a.get("name") for a in release.get("assets") or ()}
    return CLOSURE_ROOTS in names and CLOSURE_BLOCKERS in names


def install(gh, repo, release, store, *, root=ROOT, allow_mutable=False, now=None):
    """Download RELEASE into a temporary directory inside STORE, authenticate and validate
    it, write its evidence, and rename the complete directory to STORE/<id>. An id already
    installed from the same release is kept as it is (bundles are immutable). On any
    failure the store is unchanged. Returns the manifest."""
    store = Path(store)
    tag = release["tag_name"]
    final = store / bundle_id(tag)
    why = release_trust(release, allow_mutable)
    if why:
        raise Refused(f"{tag}: {why}", "unauthenticated")
    if final.is_dir():
        try:
            ev = json.loads((final / EVIDENCE).read_text(encoding="utf-8"))
        except (OSError, ValueError):
            ev = {}
        if ev.get("release_id") == release.get("id") and (ev.get("immutable") is True or allow_mutable):
            return validate(final / "bundle", root=root)
        raise BundleError(f"{final} is already installed from another release (id {ev.get('release_id')}) than "
                          f"{release.get('id')}: a published bundle is never replaced; inspect both")
    store.mkdir(parents=True, exist_ok=True)
    tmp = Path(tempfile.mkdtemp(prefix=".partial-", dir=store))
    try:
        down = tmp / "bundle"
        down.mkdir()
        gh.run(["release", "download", tag, "--repo", repo, "--dir", str(down)])
        assets = {a["name"]: a for a in release.get("assets") or ()}
        got = {p.name for p in down.iterdir()}
        if got != set(assets):
            raise BundleError(f"{tag}: downloaded {sorted(got)}, the release lists {sorted(assets)}")
        hashes = {}
        for name, a in sorted(assets.items()):
            digest = str(a.get("digest") or "")
            hashes[name] = sha256_file(down / name)
            if not digest.startswith("sha256:"):
                raise Refused(f"{tag}: the release API reports no SHA-256 digest for {name}: its bytes are not "
                              "bound by the platform", "unauthenticated")
            if digest[7:] != hashes[name]:
                raise BundleError(f"{tag}: {name} downloads as {hashes[name][:16]}, the release API says "
                                  f"{digest[7:23]}")
        manifest = validate(down, root=root)
        if manifest["tag"] != tag:
            raise BundleError(f"release {tag} carries the manifest of {manifest['tag']}")
        commit = tag_commit(gh, repo, tag)
        if commit != manifest["commit"]:
            raise Refused(f"the tag {tag} resolves to {commit[:12]}, not the measured commit "
                          f"{manifest['commit'][:12]}", "unauthenticated")
        if release.get("target_commitish") != manifest["commit"]:
            raise Refused(f"release {tag} targets {str(release.get('target_commitish'))[:40]!r}, not the measured "
                          f"commit {manifest['commit']}", "unauthenticated")
        immutable = release.get("immutable") is True
        evidence = {"schema": EVIDENCE_SCHEMA, "repo": repo, "release_id": release.get("id"), "tag": tag,
                    "author": {k: (release.get("author") or {}).get(k) for k in ("login", "id")},
                    "immutable": immutable, "tag_commit": commit, "target_commitish": release.get("target_commitish"),
                    "published_at": release.get("published_at"),
                    "assets": {n: {"sha256": h, "size": (down / n).stat().st_size} for n, h in hashes.items()},
                    "manifest_sha256": hashes[MANIFEST],
                    "attestation": attest(gh, repo, tag) if immutable else "not run: the release is not immutable",
                    "fetched_utc": iso_utc(time.time() if now is None else now),
                    "note": None if immutable else "FETCHED WITH --allow-mutable: NOT AUTHENTICATED, not served"}
        (tmp / EVIDENCE).write_text(json.dumps(evidence, indent=1, sort_keys=True) + "\n", encoding="utf-8",
                                    newline="\n")
        os.chmod(tmp, 0o755)                     # mkdtemp's 0700 would follow the rename
        os.rename(tmp, final)                    # one rename of a complete directory; nothing is replaced
    except BaseException:
        shutil.rmtree(tmp, ignore_errors=True)
        raise
    return manifest


def fetch(repo, store, *, tag=None, gh=None, root=ROOT, warn=None, allow_mutable=False, now=None):
    """(manifest, notes, pointer): install into STORE the newest trusted measurement (or
    --tag exactly) and, when that one has no closure report, the newest that has; then
    replace the pointer. A newer release that fails authentication or validation is named in
    a warning and the next older one is tried. Raises Unavailable, Empty, Refused or
    BundleError; the store is unchanged then."""
    gh = gh or Gh()
    warn = warn or (lambda line: print(f"cycle_artifacts: {line}", file=sys.stderr))
    try:
        releases = list_releases(gh, repo)
    except GhError as e:
        raise Unavailable(f"cannot list the releases of {repo}: {e}") from None
    good, skipped = candidates(releases, tag, allow_mutable)
    untrusted = [(t, w) for t, w in skipped if w.startswith("UNTRUSTED")]
    for t, w in untrusted:
        warn(f"WARNING: {t} {w}")
    if tag is not None and not good:
        if untrusted:
            raise Refused(f"release {tag} on {repo}: {untrusted[0][1]}", "unauthenticated")
        if skipped:
            raise BundleError(f"release {tag} on {repo} is not servable: {skipped[0][1]}")
        raise Unavailable(f"no release {tag} on {repo}")
    if not good:
        text = (f" ({len(skipped)} skipped: " + "; ".join(f"{t} {w}" for t, w in skipped[:5]) + ")") if skipped else ""
        if untrusted and len(untrusted) == len([s for s in skipped if not s[1].startswith("draft")]):
            raise Refused(f"{repo} has no TRUSTED link-cycle prerelease{text}", "unauthenticated")
        raise Empty(f"{repo} has no complete link-cycle prerelease{text}")
    lock = store_lock(store)
    try:
        refused, served, manifest = [], None, None
        for release in good:
            try:
                manifest = install(gh, repo, release, store, root=root, allow_mutable=allow_mutable, now=now)
            except (BundleError, Refused) as e:
                if tag is not None:
                    raise
                refused.append((release["tag_name"], e))
                warn(f"WARNING: {release['tag_name']} refused ({e}); trying the next older measurement")
                continue
            served = release
            break
        if served is None:
            first = refused[0][1]
            text = f"no link-cycle release on {repo} could be installed: " + "; ".join(f"{t}: {e}" for t, e in refused)
            raise Refused(text, first.reason) if isinstance(first, Refused) else BundleError(text)
        notes = [f"{t} skipped: {w}" for t, w in skipped]
        if refused:
            notes.insert(0, f"WARNING: serving {served['tag_name']}, not the newest: "
                            + "; ".join(f"{t} refused ({e})" for t, e in refused))
        mine = local_rules(root)
        fits = (lambda m: mine is None or rules_of(m.get("rules") or {}) == mine)
        if tag is None and not (has_closure(served) and fits(manifest)):
            # The closure queue serves the newest closure report of THIS checkout's rules
            # (closure_choice). A release's rules are known only from its manifest, so older
            # closure-ready releases are installed until one fits, at most CLOSURE_LOOKBACK.
            bare = not has_closure(served)
            lacks = "has no closure report" if bare else "was measured under other link_cycle rules"
            older = [r for r in good[good.index(served) + 1:] if has_closure(r)][:CLOSURE_LOOKBACK]
            for release in older:
                try:
                    other = install(gh, repo, release, store, root=root, allow_mutable=allow_mutable, now=now)
                except (BundleError, Refused) as e:
                    warn(f"WARNING: {release['tag_name']} refused ({e})")
                    continue
                if fits(other):
                    notes.append(f"{served['tag_name']} {lacks}: also installed {release['tag_name']}, the newest "
                                 + ("that has" if bare else "closure report of this checkout's rules")
                                 + ", for the closure queue")
                    break
            else:
                if older:
                    notes.append(f"{served['tag_name']} {lacks}, and none of the {len(older)} older closure-ready "
                                 "release(s) tried is of this checkout's rules: the closure queue has nothing "
                                 "to serve")
        pointer = write_pointer(store, now)
    finally:
        try:
            lock.unlink()
        except OSError:
            pass
    return manifest, notes, pointer


# ---------------------------------------------------------------- CLI

def report(bundle, now=None, out=None, err=None, root=ROOT):
    """Print the bundle's figure, freshness, authentication and components; returns its freshness."""
    out, err = out or sys.stdout, err or sys.stderr
    fr = bundle.freshness(now=now, root=root)
    lines = format_freshness(bundle, fr)
    lines.insert(1, headline(bundle))
    note = history_note(root)
    if note:
        lines.insert(2, note)
    ev = bundle.evidence
    if ev:
        lines.append(f"authenticated: published by {ev['author']['login']} (id {ev['author']['id']}), immutable "
                     f"release {ev['release_id']}, tag at {ev['tag_commit'][:12]}, {len(ev['assets'])} asset digests "
                     f"from the release API; attestation {ev['attestation']}")
    comp = bundle.manifest.get("components") or {}
    for name, key in ((CLOSURE_ROOTS, "closure_report"), (CYCLE_DIFF, "cycle_diff")):
        c = comp.get(key) or {}
        lines.append(f"{key}: " + (("included" + (f" ({c['graph']})" if c.get("graph") else ""))
                                   if name in bundle.manifest["members"]
                                   else f"not in this bundle ({c.get('why') or 'not recorded'})"))
    lines += bundle.notes
    for line in lines:
        print(line, file=out)
    for line in lines:
        if line.startswith(("STALE", "RULES", "UNAUTHENTICATED", "NOT THE NEWEST")):
            print(f"cycle_artifacts: {line}", file=err)
    return fr


def status(store, now=None, root=ROOT, out=None):
    """The store's two answers, each with tag and age: the latest measurement, and the
    latest closure-ready bundle of this checkout's rules (closure_choice). Then what each
    queue is served right now, asked of serve() itself: the measurement's authenticated
    figure and age, or the refusal a queue would get. Nothing is promised here that
    serve() would refuse."""
    out = out or sys.stdout
    doc = read_pointer(store)
    entries = {e["id"]: e for e in doc["bundles"]}
    now = time.time() if now is None else now
    mine = local_rules(root)
    served = {}
    for need in (False, True):
        try:
            served[need] = serve(store, now=now, root=root, need_closure=need)
        except Problem as e:
            served[need] = e

    def line(label, ident, extra=""):
        if ident is None:
            print(f"{label}: none", file=out)
            return
        e = entries[ident]
        age = (now - parse_utc(e["measured_end_utc"])) / 3600.0
        theirs = e.get("rules_tuple") or {"rules": e["rules"]}
        flags = [f"{age:.1f} h old" + (", STALE" if age > FRESH_HOURS else ""),
                 f"rules {e['rules']}" if theirs == mine else
                 f"rules {rules_text(theirs)} (NOT this checkout's {rules_text(mine) if mine else 'unreadable rules'})",
                 ("closure report: " + (e["closure_graph"] or "included")) if e["closure_report"]
                 else f"no closure report ({e['why_no_closure_report']})"]
        print(f"{label}: {e['tag']} measured {e['measured_end_utc']}; " + "; ".join(flags) + extra, file=out)
    line("latest measurement", doc.get("latest_measurement"))
    chosen, compatible = closure_choice(doc, root)
    ready = chosen if compatible else None
    got = served[True]
    line("latest compatible closure-ready bundle", ready,
         "  <- the closure queue serves THIS one"
         if ready is not None and ready != doc.get("latest_measurement") and not isinstance(got, Problem)
         and bundle_id(got[0].tag) == ready else "")
    for label, need in (("measurement queue", False), ("closure queue", True)):
        got = served[need]
        if isinstance(got, Problem):
            print(f"{label}: NOT SERVED: {describe(got)}", file=out)
        else:
            bundle, fr, _ = got
            print(f"{label}: serves {bundle.tag}, measured {fr['measured_end_utc']}, {fr['age_hours']:.1f} h ago"
                  + ("" if need else f"; {headline(bundle)}"), file=out)
    untrusted = [e["tag"] for e in doc["bundles"] if not e["authenticated"]]
    if untrusted:
        print("installed but NOT authenticated (--allow-mutable), never served: " + ", ".join(untrusted), file=out)
    return doc


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("fetch", help="download, authenticate and install a published bundle")
    which = f.add_mutually_exclusive_group(required=True)
    which.add_argument("--latest", action="store_true", help="the newest trusted measurement")
    which.add_argument("--tag", help="exactly this release tag")
    f.add_argument("--store", default=str(DEFAULT_STORE), help="bundle store (default build/cycle_bundles)")
    f.add_argument("--repo", default=DEFAULT_REPO)
    f.add_argument("--allow-mutable", action="store_true",
                   help="TEST ONLY: install from a release GitHub does not report immutable. What it installs is "
                        "marked NOT authenticated and no queue serves it")
    s = sub.add_parser("status", help="the store's latest measurement and latest closure-ready bundle")
    s.add_argument("store", nargs="?", default=str(DEFAULT_STORE))
    v = sub.add_parser("validate", help="validate a store's current bundle (or a bundle directory) as a queue would")
    v.add_argument("dir")
    v.add_argument("--allow-stale", action="store_true",
                   help="a bundle past the 24 h window is accepted (exit 0), still labelled STALE")
    v.add_argument("--local-unpublished", action="store_true",
                   help="a locally built bundle with no fetch evidence: integrity only, labelled UNAUTHENTICATED")
    args = ap.parse_args(argv)
    try:
        if args.cmd == "fetch":
            if args.allow_mutable:
                print("cycle_artifacts: --allow-mutable: TEST ONLY. A release that is not immutable is NOT "
                      "authenticated; nothing installed this way is served by a queue.", file=sys.stderr)
            manifest, notes, _ = fetch(args.repo, args.store, tag=args.tag, allow_mutable=args.allow_mutable)
            for line in notes:
                print(f"cycle_artifacts: {line}", file=sys.stderr if line.startswith("WARNING") else sys.stdout)
            print(f"fetched {manifest['tag']} into {Path(args.store) / bundle_id(manifest['tag'])}: "
                  f"{len(manifest['members']) + 1} assets, valid")
            status(args.store)
            return 0
        if args.cmd == "status":
            status(args.store)
            return 0
        directory, notes = resolve(args.dir)
        bundle = load_bundle(directory)
        bundle.notes = notes
        print(f"valid: {bundle.tag} ({len(bundle.manifest['members']) + 1} files; receipt core "
              f"{bundle.manifest['receipt']['core_sha256'][:16]}, {bundle.core_check})")
        problem = None
        if args.local_unpublished:
            bundle.notes.append("UNAUTHENTICATED LOCAL BUNDLE (--local-unpublished): integrity only")
        else:
            try:
                bundle.evidence = authenticate_local(bundle)
            except Refused as e:
                problem = e
        fr = report(bundle)
        if fr["future"]:
            raise BundleError(f"bundle {bundle.tag}: measured {fr['measured_end_utc']}, in the future of this clock")
        why = refusal(fr, args.allow_stale)
        if problem is None and why:
            problem = Refused(f"bundle {bundle.tag}: {why[1]}", why[0])
        if problem:
            raise problem
        return 0
    except Problem as e:
        print(f"cycle_artifacts: {describe(e)}", file=sys.stderr)
        return exit_code(e)


if __name__ == "__main__":
    sys.exit(main())
