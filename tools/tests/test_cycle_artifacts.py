"""publish_cycle / cycle_artifacts: one link_cycle MEASUREMENT becomes one immutable prerelease
bundle whose manifest binds every member and repeats nothing the receipt does not say;
publication drafts first, verifies the upload and never overwrites; fetch authenticates the
release (designated publisher, immutable, tag at the measured commit, asset digests from the
release API) before installing it into an immutable directory behind an atomic pointer; the
queues serve only an authenticated, compatible, fresh bundle and say why not otherwise.

GitHub is a fake (FakeGitHub): these tests never call gh."""
import gzip
import hashlib
import json
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import cycle_artifacts as ca  # noqa: E402
import cycle_fixture as cf  # noqa: E402
import link_cycle as lc  # noqa: E402
import publish_cycle as pc  # noqa: E402

REPO = "Open-BFME/Open-BFME-2"
END = ca.parse_utc("2026-10-11 16:43:32")
PUBLISHER = dict(ca.PUBLISHERS[0])
STRANGER = {"login": "unauthorized-push-user", "id": 123456}


class FakeGitHub:
    """The gh commands publish_cycle and cycle_artifacts issue, against an in-memory
    repository: releases (drafts included) with their author, immutability, target and
    asset digests, git tags, commits, the immutable-releases setting. Every call is recorded."""

    def __init__(self, commits=(cf.COMMIT, cf.OTHER), user=None, immutable=True):
        self.commits = set(commits)
        self.user = dict(user or PUBLISHER)
        self.immutable_enabled = immutable
        self.releases, self.tags, self.annotated, self.calls = [], {}, {}, []
        self.next_id, self.clock = 100, 0
        self.corrupt_upload = None           # an asset name whose stored bytes get one byte flipped
        self.fail_download_after = None      # files written before a download fails
        self.fail_list = False
        self.fail_verify = None              # stderr of a failing `gh release verify`
        self.undraft = None                  # "lost": published, then the call fails; "fail": fails first

    # -- helpers
    def _stamp(self):
        self.clock += 1
        return "2026-10-12T00:%02d:00Z" % self.clock

    def add_release(self, tag, files, *, draft=False, prerelease=True, published_at=None, target=cf.COMMIT,
                    author=None, immutable=None, tag_at=None):
        self.next_id += 1
        r = {"id": self.next_id, "tag_name": tag, "draft": draft, "prerelease": prerelease, "target": target,
             "created_at": published_at or self._stamp(), "published_at": None if draft else published_at,
             "author": dict(author or PUBLISHER),
             "immutable": (self.immutable_enabled if immutable is None else immutable) and not draft,
             "assets": [{"name": n, "data": d} for n, d in files.items()], "flags": []}
        self.releases.append(r)
        if not draft:
            self.tags.setdefault(tag, tag_at or target)
        return r

    def _find(self, tag):
        pub = [r for r in self.releases if r["tag_name"] == tag and not r["draft"]]
        drafts = [r for r in self.releases if r["tag_name"] == tag and r["draft"]]
        if not pub + drafts:
            raise ca.GhError(["release", tag], 1, "release not found")
        return (pub + drafts)[0]

    @staticmethod
    def _opt(rest, name):
        return rest[rest.index(name) + 1] if name in rest else None

    def _rest_view(self, r):
        return {"id": r["id"], "tag_name": r["tag_name"], "draft": r["draft"], "prerelease": r["prerelease"],
                "created_at": r["created_at"], "published_at": r["published_at"], "author": r["author"],
                "immutable": r["immutable"], "target_commitish": r["target"], "body": r.get("notes", ""),
                "assets": [{"name": a["name"], "size": len(a["data"]), "state": "uploaded",
                            "digest": a.get("digest", "sha256:" + hashlib.sha256(a["data"]).hexdigest())}
                           for a in r["assets"]]}

    # -- the gh surface
    def json(self, args):
        text = self.run(args)
        return json.loads(text) if text.strip() else None

    def run(self, args):
        self.calls.append(list(args))
        if args[0] == "api":
            return self._api(args[1:])
        assert args[0] == "release", args
        assert self._opt(args, "--repo") == REPO, args
        return getattr(self, "_" + args[1])(args[2:])

    def _api(self, rest):
        if rest == ["user"]:
            return json.dumps(self.user)
        if rest[:2] == ["--paginate", "--slurp"]:
            if self.fail_list:
                raise ca.GhError(rest, 1, "error connecting to api.github.com")
            assert rest[2] == f"repos/{REPO}/releases?per_page=100"
            return json.dumps([[self._rest_view(r) for r in reversed(self.releases)]])
        if rest[:2] == ["-X", "DELETE"]:
            rid = int(rest[2].rsplit("/", 1)[1])
            r = next(r for r in self.releases if r["id"] == rid)
            assert r["draft"], "only a draft may be deleted"
            self.releases.remove(r)
            return ""
        path = rest[0]
        base = f"repos/{REPO}/"
        assert path.startswith(base), path
        path = path[len(base):]
        if path == "immutable-releases":
            return json.dumps({"enabled": self.immutable_enabled, "enforced_by_owner": False})
        if path.startswith("git/matching-refs/tags/"):
            prefix = path[len("git/matching-refs/tags/"):]
            return json.dumps([{"ref": f"refs/tags/{t}", "object": {"sha": s, "type": "commit"}}
                               for t, s in sorted(self.tags.items()) if t.startswith(prefix)])
        if path.startswith("git/ref/tags/"):
            tag = path[len("git/ref/tags/"):]
            if tag not in self.tags:
                raise ca.GhError(rest, 1, "gh: Not Found (HTTP 404)")
            sha = self.tags[tag]
            return json.dumps({"ref": f"refs/tags/{tag}",
                               "object": {"sha": sha, "type": "tag" if sha in self.annotated else "commit"}})
        if path.startswith("git/tags/"):
            return json.dumps({"object": {"sha": self.annotated[path[len("git/tags/"):]], "type": "commit"}})
        if path.startswith("commits/"):
            sha = path[len("commits/"):]
            if sha not in self.commits:
                raise ca.GhError(rest, 1, "gh: No commit found for SHA (HTTP 422)")
            return json.dumps({"sha": sha})
        raise AssertionError(rest)

    def _create(self, rest):
        tag = rest[0]
        notes = Path(self._opt(rest, "--notes-file"))
        assert notes.is_file()
        self.next_id += 1
        r = {"id": self.next_id, "tag_name": tag, "draft": "--draft" in rest, "prerelease": "--prerelease" in rest,
             "target": self._opt(rest, "--target"), "created_at": self._stamp(), "published_at": None,
             "author": dict(self.user), "immutable": False,
             "assets": [], "flags": list(rest), "notes": notes.read_text(encoding="utf-8")}
        assert r["draft"], "publish_cycle creates drafts only"
        self.releases.append(r)
        return f"https://github.com/{REPO}/releases/tag/untagged-{r['id']}\n"

    def _view(self, rest):
        r = self._find(rest[0])
        return json.dumps({"databaseId": r["id"], "tagName": r["tag_name"], "isDraft": r["draft"],
                           "isPrerelease": r["prerelease"], "targetCommitish": r["target"],
                           "assets": [{"name": a["name"], "size": len(a["data"]), "state": "uploaded"}
                                      for a in r["assets"]]})

    def _upload(self, rest):
        assert "--clobber" not in rest
        r = self._find(rest[0])
        files = [a for a in rest[1:] if a not in ("--repo", REPO)]
        for f in files:
            name = Path(f).name
            if any(a["name"] == name for a in r["assets"]):
                raise ca.GhError(rest, 1, f"asset under the same name already exists: {name}")
            data = Path(f).read_bytes()
            if name == self.corrupt_upload:
                data = bytes([data[0] ^ 1]) + data[1:]
            r["assets"].append({"name": name, "data": data})
        return ""

    def _download(self, rest):
        r = self._find(rest[0])
        d = Path(self._opt(rest, "--dir"))
        for n, a in enumerate(r["assets"]):
            if self.fail_download_after is not None and n == self.fail_download_after:
                raise ca.GhError(rest, 1, "read: connection reset by peer")
            target = d / a["name"]
            assert not target.exists(), "gh refuses to overwrite without --clobber"
            target.write_bytes(a["data"])
        return ""

    def _verify(self, rest):
        self._find(rest[0])
        if self.fail_verify:
            raise ca.GhError(["release", "verify", *rest], 1, self.fail_verify)
        return "verified\n"

    def _edit(self, rest):
        r = self._find(rest[0])
        if "--draft=false" in rest and self.undraft == "fail":
            raise ca.GhError(["release", "edit", *rest], 1, "HTTP 500")
        r["flags"] += list(rest)
        if "--draft=false" in rest:
            r["draft"] = False
            r["published_at"] = self._stamp()
            r["immutable"] = self.immutable_enabled
            self.tags.setdefault(r["tag_name"], r["target"])
        r["prerelease"] = "--prerelease" in rest or r["prerelease"]
        if "--draft=false" in rest and self.undraft == "lost":
            raise ca.GhError(["release", "edit", *rest], 1, "HTTP 504: Gateway Timeout")
        return ""

    def verbs(self):
        return [" ".join(c[:2]) if c[0] == "release" else "api " + (c[1] if c[1] != "-X" else "DELETE")
                for c in self.calls]


# ---------------------------------------------------------------- fixtures

@pytest.fixture
def run(tmp_path):
    return cf.make_run(tmp_path / "snaps")


@pytest.fixture
def bundle(tmp_path, run):
    out = tmp_path / "bundle"
    cf.bundle(run, out, "laptop/watchdog", rank="generate")
    return out


def files_of(directory):
    return {p.name: p.read_bytes() for p in Path(directory).iterdir()}


def quick_bundle(tmp_path, name, **kw):
    """A bundle with the run directory's own data_back_rank (no subprocess)."""
    run = cf.make_run(tmp_path / f"snaps-{name}", rank_files=True, **kw)
    out = tmp_path / name
    cf.bundle(run, out, f"producer-{name}")
    return out


def closure_quick(tmp_path, name, **kw):
    return quick_bundle(tmp_path, name, status=cf.CLOSURE_STATUS, closure=True, **kw)


def released(gh, bundle, published_at, **kw):
    """BUNDLE as a published release of the fake repository."""
    m = ca.read_manifest(bundle)
    kw.setdefault("target", m["commit"])
    return gh.add_release(m["tag"], files_of(bundle), published_at=published_at, **kw)


def installed_dir(store, manifest):
    return Path(store) / ca.bundle_id(manifest["tag"]) / "bundle"


def _rewrite_manifest(bundle, edit):
    m = json.loads((bundle / "manifest.json").read_text())
    edit(m)
    (bundle / "manifest.json").write_text(json.dumps(m))


# ---------------------------------------------------------------- run validation

def test_local_tool_digest_is_link_cycles_own():
    assert ca.local_tool_digest(TOOLS.parent) == lc.tool_digest()


def test_validate_run_reports_commit_tool_rules_pointer_and_times(run):
    f = pc.validate_run(run)
    assert f["commit"] == cf.COMMIT and f["bfme1_pointer"] == cf.B1
    assert f["tool_digest"] == lc.tool_digest() and f["rules"] == "link-cycle-2"
    assert f["shadow_rules"] == ["data-fold-1"]
    assert f["core_check"].startswith("recomputed with link_cycle")
    assert f["measured"]["end_utc"] == "2026-10-11T16:43:32Z"
    assert f["measured"]["start_utc"] == ca.iso_utc(END - 8795)
    assert pc.main(["validate", str(run)]) == 0


def _restamp(run, **changes):
    r = json.loads((run / "receipt.json").read_text())
    r.update(changes)
    lc.stamp_cores(r)
    (run / "receipt.json").write_text(json.dumps(r))


@pytest.mark.parametrize("damage, message", [
    (lambda run: _restamp(run, authoritative=False), "not authoritative"),
    (lambda run: _restamp(run, snapshot=False), "not a snapshot run"),
    (lambda run: (run / "link_status.csv").write_bytes((run / "link_status.csv").read_bytes() + b"x,\r\n"),
     "not the receipt's link_status_sha256"),
    (lambda run: (run / "receipt.json").write_text(
        (run / "receipt.json").read_text().replace('"objects": 4', '"objects": 5')), "does not digest its contents"),
    (lambda run: ((run / "receipt.rejected.json").write_text("{}"),
                  os.utime(run / "receipt.json", (time.time() - 60, time.time() - 60))), "later run here was rejected"),
    (lambda run: (run / "data_fold_list.csv").unlink(), "no data_fold_list.csv"),
    (lambda run: (run / "receipt.json").unlink(), "no receipt.json"),
    (lambda run: _restamp(run, date_utc="yesterday"), "no readable date_utc"),
    (lambda run: _restamp(run, closure_graph_sha256="0" * 64), "not the closure graph the receipt names"),
])
def test_validate_run_refuses(run, damage, message):
    damage(run)
    with pytest.raises(pc.RunError, match=message):
        pc.validate_run(run)
    assert pc.main(["validate", str(run)]) == 1


# ---------------------------------------------------------------- bundle and manifest

def test_manifest_round_trip(run, bundle):
    b = ca.load_bundle(bundle)
    m = b.manifest
    assert m == json.loads((bundle / "manifest.json").read_text(encoding="utf-8"))
    raw = (run / "receipt.json").read_bytes()
    receipt = json.loads(raw)
    assert m["schema"] == ca.SCHEMA and m["commit"] == cf.COMMIT and m["producer"] == "laptop/watchdog"
    assert m["tag"] == f"link-cycle/{cf.COMMIT[:12]}-20261011T164332Z-{hashlib.sha256(raw).hexdigest()[:12]}" == b.tag
    assert ca.tag_time(m["tag"]) == END and ca.TAG.match(m["tag"])
    assert m["instance"] == {"measured_end_utc": "2026-10-11T16:43:32Z",
                             "receipt_sha256": hashlib.sha256(raw).hexdigest()}
    assert m["receipt"]["core_sha256"] == receipt["core_sha256"]
    assert m["tool_digest"] == receipt["tool_digest"] and m["bfme1_pointer"] == cf.B1
    assert m["rules"]["rules"] == "link-cycle-2" and len(m["rules"]["digest"]) == 64
    assert len(m["analysis"]["digest"]) == 64
    assert (m["measured"]["start_utc"], m["measured"]["end_utc"]) == (ca.iso_utc(END - 8795), "2026-10-11T16:43:32Z")
    assert m["headline"] == ca.headline_of(receipt) and m["headline"]["credit_unique_bytes"] == 64
    assert sorted(m["members"]) == sorted(ca.MEMBERS)
    assert sorted(p.name for p in bundle.iterdir()) == sorted(ca.MEMBERS + (ca.MANIFEST,))
    for name, meta in m["members"].items():
        assert meta["sha256"] == ca.sha256_file(bundle / name) and meta["size"] == (bundle / name).stat().st_size
    with gzip.open(bundle / ca.LINK_STATUS, "rb") as f:
        assert f.read() == (run / "link_status.csv").read_bytes()
    with gzip.open(bundle / ca.DATA_FOLDS, "rb") as f:
        assert f.read() == (run / "data_fold_list.csv").read_bytes()
    assert (bundle / ca.RECEIPT).read_bytes() == raw
    ledger = m["diagnostic_inputs"]["files"]["reverse/data_ledger.csv"]
    assert ledger["text_sha256"] == ca.text_sha256(run.parent.parent / "reverse/data_ledger.csv")
    assert b.diagnostic("reverse/data_ledger.csv") == ledger["text_sha256"]
    assert m["diagnostic_inputs"]["basis"].startswith("snapshot")
    rank = m["analysis"]["data_back_rank"]
    assert rank["source"] == "generated" and rank["inputs"] == "snapshot"
    assert "<measured>/reverse/data_ledger.csv" in rank["argv"] and "--no-objects" in rank["argv"]
    report = json.loads((bundle / ca.RANK_JSON).read_text(encoding="utf-8"))
    assert report["mode"] == "status" and report["status"] == "link_status.csv"
    assert [a["address"] for a in report["addresses"]] == ["0x00100000"]
    assert (bundle / ca.RANK_TXT).read_text(encoding="utf-8").startswith("data-back: 2 placed real rows")
    assert b.core_check.startswith("recomputed")
    assert m["components"]["closure_report"]["status"] == "diagnostic-only"


def test_gzip_members_are_reproducible(tmp_path, run):
    a, b = tmp_path / "a", tmp_path / "b"
    cf.bundle(run, a, "x", rank="generate")
    cf.bundle(run, b, "x", rank="generate")
    for name in (ca.LINK_STATUS, ca.DATA_FOLDS, ca.RECEIPT, ca.RANK_TXT):
        assert (a / name).read_bytes() == (b / name).read_bytes()


def test_rank_taken_from_the_run_directory_says_so(tmp_path):
    run = cf.make_run(tmp_path / "snaps", rank_files=True)
    out = tmp_path / "bundle"
    m = cf.bundle(run, out, "x")
    assert m["analysis"]["data_back_rank"]["source"] == "run_dir"
    assert (out / ca.RANK_TXT).read_text() == "the producer's own report\n"
    with pytest.raises(pc.RunError, match="has no data_back_rank"):
        cf.bundle(cf.make_run(tmp_path / "other"), tmp_path / "b2", "x", rank="run-dir")


def _git(repo, *args):
    return subprocess.run(["git", "-C", str(repo), *args], capture_output=True, text=True, check=True).stdout.strip()


def test_inputs_come_from_git_at_the_measured_commit_without_a_snapshot(tmp_path):
    repo = tmp_path / "repo"
    for rel, rows in (("reverse/data_ledger.csv", cf.LEDGER), ("reverse/functions.csv", cf.FUNCTIONS),
                      ("reverse/exports.csv", cf.EXPORTS)):
        cf.write(repo / rel, cf.csv_text(rows, "\n"))
    _git(repo.parent, "init", "-q", str(repo))
    _git(repo, "add", "reverse")
    _git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "ledgers")
    sha = _git(repo, "rev-parse", "HEAD")
    run = cf.make_run(tmp_path / "snaps", commit=sha, snapshot=False)
    m = cf.bundle(run, tmp_path / "bundle", "x", root=repo)
    assert m["diagnostic_inputs"]["basis"].startswith(f"git show {sha[:12]}")
    assert m["analysis"]["data_back_rank"]["inputs"] == "git"
    assert m["receipt"]["core_check"].startswith("not recomputed")        # no link_cycle in that checkout
    # a ledger that is not the one the receipt measured is refused, never ranked
    cf.write(repo / "reverse/functions.csv", cf.csv_text(cf.FUNCTIONS[:2], "\n"))
    _git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-am", "moved")
    run2 = cf.make_run(tmp_path / "snaps2", commit=_git(repo, "rev-parse", "HEAD"), snapshot=False)
    (repo / "reverse/functions.csv").write_text("changed after the run\n")
    receipt = json.loads((run2 / "receipt.json").read_text())
    receipt["inputs"]["functions_csv"] = "0" * 64
    lc.stamp_cores(receipt)
    (run2 / "receipt.json").write_text(json.dumps(receipt))
    with pytest.raises(pc.RunError, match="not the one the receipt measured"):
        cf.bundle(run2, tmp_path / "bundle2", "x", root=repo)
    assert not (tmp_path / "bundle2").exists()


def test_a_snapshot_written_since_the_run_is_not_its_inputs(tmp_path, run):
    (run.parent.parent / "reverse/data_ledger.csv").write_text("edited after the run\n")
    with pytest.raises(pc.RunError, match="changed since the run"):
        cf.bundle(run, tmp_path / "bundle", "x", snapshot_root=run.parent.parent)


def test_an_existing_bundle_directory_is_never_overwritten(tmp_path, run, bundle):
    before = files_of(bundle)
    with pytest.raises(pc.RunError, match="immutable"):
        cf.bundle(run, bundle, "x")
    assert files_of(bundle) == before
    assert not [p for p in tmp_path.iterdir() if ".partial-" in p.name]


# ---------------------------------------------------------------- identity: a measurement, not a result (Astra 1)

def test_a_rerun_with_the_same_core_is_another_measurement_with_its_own_tag(tmp_path):
    a = ca.read_manifest(quick_bundle(tmp_path, "a"))
    b = ca.read_manifest(quick_bundle(tmp_path, "b", date_utc="2026-10-12 16:43:32", total=8796))
    assert a["receipt"]["core_sha256"] == b["receipt"]["core_sha256"]          # the same reproducible result
    assert a["tag"] != b["tag"] and ca.tag_time(b["tag"]) - ca.tag_time(a["tag"]) == 86400
    assert a["instance"]["receipt_sha256"] != b["instance"]["receipt_sha256"]
    # both publish: the rerun refreshes an ageing bundle instead of colliding with it
    gh = FakeGitHub()
    pc.publish(tmp_path / "a", REPO, gh=gh)
    pc.publish(tmp_path / "b", REPO, gh=gh)
    assert sorted(r["tag_name"] for r in gh.releases) == sorted([a["tag"], b["tag"]])
    manifest, _, pointer = ca.fetch(REPO, tmp_path / "store", gh=gh)
    assert manifest["tag"] == b["tag"] and pointer["latest_measurement"] == ca.bundle_id(b["tag"])


# ---------------------------------------------------------------- bundle validation (integrity)

def _flip(path):
    data = bytearray(path.read_bytes())
    data[len(data) // 2] ^= 0x01
    path.write_bytes(bytes(data))


@pytest.mark.parametrize("damage, message", [
    (lambda b: _flip(b / ca.LINK_STATUS), "link_status.csv.gz: sha256"),
    (lambda b: (b / ca.RANK_TXT).write_text("tampered\n"), "data_back_rank.txt"),
    (lambda b: (b / "extra.csv").write_text("x"), "unlisted"),
    (lambda b: (b / ca.DATA_FOLDS).unlink(), "missing"),
    (lambda b: _rewrite_manifest(b, lambda m: m["members"][ca.RECEIPT].update(size=1)), "manifest says 1"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(tag="link-cycle/x")), "tag"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(commit=cf.OTHER)), "the manifest names"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(schema="link-cycle-bundle/0")), "schema"),
    (lambda b: _rewrite_manifest(b, lambda m: m["members"].pop(ca.RANK_JSON)), "lists no"),
    # everything the manifest repeats from the receipt must be what the receipt says (Sol 2, Astra 2)
    (lambda b: _rewrite_manifest(b, lambda m: m["measured"].update(end_utc="2026-10-13T16:43:32Z")),
     "manifest's measured .* is not what the receipt says"),
    (lambda b: _rewrite_manifest(b, lambda m: m["measured"].update(start_utc="2026-10-11T16:00:00Z")),
     "manifest's measured"),
    (lambda b: _rewrite_manifest(b, lambda m: m["headline"].update(credit_unique_bytes=999999999)),
     "manifest's headline .*999999999.* is not what the receipt says"),
    (lambda b: _rewrite_manifest(b, lambda m: m["instance"].update(measured_end_utc="2026-10-13T16:43:32Z")),
     "manifest's instance"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(bfme1_pointer="0" * 40)), "manifest's bfme1_pointer"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(submodules={})), "manifest's submodules"),
    (lambda b: _rewrite_manifest(b, lambda m: m["receipt"].update(core_canon_sha256="0" * 64)), "core_canon_sha256"),
    (lambda b: _rewrite_manifest(b, lambda m: m["receipt"].update(tree_manifest="0" * 64)), "tree_manifest"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(producer=" ")), "names no producer"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(created_utc="2026-10-11T16:00:00Z")),
     "created .* before its measurement ended"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(created_utc="soon")), "created_utc is unreadable"),
    (lambda b: _rewrite_manifest(b, lambda m: m["rules"].update(rules="link-cycle-9")), "are not the receipt's"),
    (lambda b: _rewrite_manifest(b, lambda m: m.update(tool_digest="0" * 64)), "tool_digest is not the receipt's"),
    (lambda b: _rewrite_manifest(b, lambda m: m["components"]["closure_report"].update(included=True)),
     "included is True but the bundle holds neither"),
    (lambda b: _rewrite_manifest(b, lambda m: m["components"]["closure_report"].pop("why")), "no reason given"),
    (lambda b: _rewrite_manifest(b, lambda m: m["components"]["cycle_diff"].update(included=True)),
     "is included; it is not a member"),
])
def test_validate_refuses_a_damaged_bundle(bundle, damage, message):
    damage(bundle)
    with pytest.raises(ca.BundleError, match=message) as e:
        ca.validate(bundle)
    assert e.value.reason == "corrupt"
    assert ca.main(["validate", str(bundle), "--local-unpublished"]) == ca.EXIT["corrupt"]


def test_a_manifest_only_edit_cannot_make_an_old_run_fresh_or_change_its_headline(tmp_path):
    """The reviewers' repro: nothing but manifest.json is touched; no member, no checksum."""
    old = quick_bundle(tmp_path, "old", date_utc="2026-10-10 20:16:22")
    now = ca.parse_utc("2026-10-11T22:00:00Z")
    with pytest.raises(ca.Refused, match="STALE: measured 25.7 h ago"):
        ca.serve(old, now=now, local_unpublished=True)
    _rewrite_manifest(old, lambda m: m["measured"].update(end_utc="2026-10-11T21:59:00Z"))
    with pytest.raises(ca.BundleError, match="measured"):
        ca.serve(old, now=now, local_unpublished=True)
    fresh = quick_bundle(tmp_path, "fresh")
    b, fr, _ = ca.serve(fresh, now=END + 3600, local_unpublished=True)
    assert fr["age_hours"] == 1.0 and "credit 64 B" in ca.headline(b)          # both read from the receipt
    _rewrite_manifest(fresh, lambda m: m["headline"].update(credit_unique_bytes=999999999))
    with pytest.raises(ca.BundleError, match="headline"):
        ca.serve(fresh, now=END + 3600, local_unpublished=True)


def test_a_measurement_dated_in_the_future_is_invalid_not_fresh(tmp_path):
    b = quick_bundle(tmp_path, "later", date_utc="2026-10-12 16:43:32")
    for allow in (False, True):
        with pytest.raises(ca.BundleError, match="in the\\s+future of this clock"):
            ca.serve(b, now=END, local_unpublished=True, allow_stale=allow)
    ca.serve(b, now=END + 86400 - 300, local_unpublished=True)                 # five minutes of clock skew: served
    assert ca.serve(b, now=END + 86400 + 60, local_unpublished=True)[1]["age_hours"] == 0.02


def test_a_receipt_swapped_with_consistent_hashes_is_still_refused(bundle):
    """Member hashes rewritten to match an edited receipt: the receipt's own bytes name another tag."""
    r = json.loads((bundle / ca.RECEIPT).read_text())
    r["series"]["credit_unique_bytes"] = 10 ** 9
    (bundle / ca.RECEIPT).write_text(json.dumps(r))
    _rewrite_manifest(bundle, lambda m: m["members"][ca.RECEIPT].update(
        sha256=ca.sha256_file(bundle / ca.RECEIPT), size=(bundle / ca.RECEIPT).stat().st_size))
    with pytest.raises(ca.BundleError, match="is not .* the tag this receipt's bytes name"):
        ca.validate(bundle)


def test_a_missing_directory_is_unavailable_not_invalid(tmp_path):
    with pytest.raises(ca.Unavailable):
        ca.load_bundle(tmp_path / "nowhere")
    assert ca.main(["validate", str(tmp_path / "nowhere")]) == ca.EXIT["unavailable"]


def test_a_member_outside_the_fixed_set_is_refused(bundle):
    (bundle / "notes.txt").write_text("x")
    _rewrite_manifest(bundle, lambda m: m["members"].update({"notes.txt": {
        "sha256": ca.sha256_file(bundle / "notes.txt"), "size": 1}}))
    with pytest.raises(ca.BundleError, match="bad member name 'notes.txt'"):
        ca.validate(bundle)


# ---------------------------------------------------------------- publish

def test_publish_drafts_uploads_verifies_then_undrafts(bundle, capsys):
    gh = FakeGitHub()
    m = ca.validate(bundle)
    got = pc.publish(bundle, REPO, gh=gh)
    verbs = gh.verbs()
    order = [verbs.index(v) for v in ("release create", "release upload", "release download", "release edit")]
    assert order == sorted(order), verbs
    create = next(c for c in gh.calls if c[:2] == ["release", "create"])
    assert create[2] == m["tag"]
    for flag in ("--draft", "--prerelease", "--latest=false"):
        assert flag in create
    assert create[create.index("--target") + 1] == cf.COMMIT
    edit = next(c for c in gh.calls if c[:2] == ["release", "edit"])
    assert "--draft=false" in edit and "--latest=false" in edit and "--prerelease" in edit
    assert not any("--clobber" in c for c in gh.calls)
    # the download that verified the assets ran while the release was still a draft
    assert verbs.index("release download") < verbs.index("release edit")
    (release,) = gh.releases
    assert not release["draft"] and release["prerelease"] and gh.tags[m["tag"]] == cf.COMMIT
    assert {a["name"]: a["data"] for a in release["assets"]} == files_of(bundle)
    assert m["tag"] in release["notes"] and "never this repository's Latest" in release["notes"]
    assert "sha256 `" + m["instance"]["receipt_sha256"][:16] in release["notes"]
    assert "manifest.json sha256" not in release["notes"]             # nothing a consumer could be asked to trust
    assert got["release_id"] == release["id"] and not got["dry_run"]
    assert "prerelease, immutable, not Latest" in capsys.readouterr().out


def test_publish_is_refused_from_an_account_that_is_not_a_designated_publisher(bundle):
    gh = FakeGitHub(user=STRANGER)
    with pytest.raises(pc.PublishError, match="'unauthorized-push-user' .* is not a designated publisher"):
        pc.publish(bundle, REPO, gh=gh)
    assert not [c for c in gh.calls if c[0] == "release"] and gh.releases == []


def test_publish_is_refused_while_the_repository_does_not_enforce_immutable_releases(bundle, capsys):
    gh = FakeGitHub(immutable=False)
    with pytest.raises(pc.PublishError, match="does not enforce immutable releases"):
        pc.publish(bundle, REPO, gh=gh)
    assert gh.releases == []
    with pytest.raises(pc.PublishError, match="only with --dry-run"):          # no override for a real publish
        pc.publish(bundle, REPO, gh=gh, allow_mutable=True)
    assert pc.main(["publish", str(bundle), "--allow-mutable"]) == 1
    capsys.readouterr()
    with pytest.raises(pc.PublishError, match="does not enforce"):             # a dry run refuses too...
        pc.publish(bundle, REPO, gh=gh, dry_run=True)
    got = pc.publish(bundle, REPO, gh=gh, dry_run=True, allow_mutable=True)    # ...unless told to go on, loudly
    out = capsys.readouterr().out
    assert "!! --allow-mutable (DRY RUN ONLY): A REAL PUBLISH WOULD BE REFUSED" in out
    assert "immutable releases on Open-BFME/Open-BFME-2: OFF" in out and gh.releases == []
    shutil.rmtree(Path(got["notes"]).parent)


@pytest.mark.parametrize("held", ["tag", "release", "draft"])
def test_publish_never_overwrites_an_existing_tag_or_release(bundle, held):
    gh = FakeGitHub()
    tag = ca.validate(bundle)["tag"]
    if held == "tag":
        gh.tags[tag] = cf.OTHER
    else:
        gh.add_release(tag, {"manifest.json": b"{}"}, draft=held == "draft", published_at="2026-10-11T00:00:00Z")
    before = json.dumps(gh.releases, default=str), dict(gh.tags)
    with pytest.raises(pc.PublishError, match="never overwritten"):
        pc.publish(bundle, REPO, gh=gh)
    assert not [c for c in gh.calls if c[0] == "release"]          # nothing created, uploaded or edited
    assert (json.dumps(gh.releases, default=str), dict(gh.tags)) == before


def test_a_retry_of_a_published_bundle_is_reported_and_changes_nothing(bundle, capsys):
    gh = FakeGitHub()
    first = pc.publish(bundle, REPO, gh=gh)
    before = json.dumps(gh.releases, default=str), dict(gh.tags)
    calls = len(gh.calls)
    again = pc.publish(bundle, REPO, gh=gh)                         # the same bytes: nothing to do
    assert again["already_published"] and again["release_id"] == first["release_id"] and again["commands"] == []
    assert "ALREADY PUBLISHED" in capsys.readouterr().out
    assert not [c for c in gh.calls[calls:] if c[0] == "release" or "-X" in c]
    assert (json.dumps(gh.releases, default=str), dict(gh.tags)) == before


def test_an_undraft_whose_response_is_lost_is_inspected_never_deleted(bundle, capsys):
    """A timeout after the server accepted the un-draft is ambiguous success."""
    gh = FakeGitHub()
    gh.undraft = "lost"
    got = pc.publish(bundle, REPO, gh=gh)
    assert "ambiguous success, resolved by inspection" in capsys.readouterr().err
    (release,) = gh.releases
    assert not release["draft"] and got["release_id"] == release["id"] and "api DELETE" not in gh.verbs()
    gh.undraft = None
    assert pc.publish(bundle, REPO, gh=gh)["already_published"]     # and a blind retry is harmless


def test_an_undraft_that_really_failed_removes_only_its_own_draft(bundle, capsys):
    gh = FakeGitHub()
    gh.undraft = "fail"
    with pytest.raises(ca.GhError, match="HTTP 500"):
        pc.publish(bundle, REPO, gh=gh)
    assert gh.releases == [] and gh.tags == {} and "deleted this run's draft" in capsys.readouterr().err


def test_an_interrupted_publish_leaves_a_draft_that_a_retry_names_and_replaces_on_request(bundle, capsys):
    gh = FakeGitHub()

    def view_fails(rest):
        raise ca.GhError(["release", "view", *rest], 1, "HTTP 502: Bad Gateway")
    real, gh._view = gh._view, view_fails
    with pytest.raises(ca.GhError, match="502"):
        pc.publish(bundle, REPO, gh=gh)
    assert "may remain" in capsys.readouterr().err
    assert "release upload" not in gh.verbs() and "release edit" not in gh.verbs()
    (orphan,) = gh.releases
    assert orphan["draft"]                                           # left a draft, never published
    gh._view = real
    with pytest.raises(pc.PublishError, match=f"held by draft release\\(s\\) \\[{orphan['id']}\\].*--replace-draft"):
        pc.publish(bundle, REPO, gh=gh)                              # an orphan draft does not block silently
    with pytest.raises(pc.PublishError, match="held by draft"):
        pc.publish(bundle, REPO, gh=gh, replace_draft=orphan["id"] + 50)
    got = pc.publish(bundle, REPO, gh=gh, replace_draft=orphan["id"])
    (release,) = gh.releases
    assert release["id"] == got["release_id"] != orphan["id"] and not release["draft"]


def test_publish_refuses_a_commit_the_repository_lacks(bundle):
    gh = FakeGitHub(commits=())
    with pytest.raises(pc.PublishError, match="push it first"):
        pc.publish(bundle, REPO, gh=gh)
    assert not [c for c in gh.calls if c[0] == "release"]


def test_a_draft_that_does_not_target_the_measured_commit_is_never_published(bundle):
    gh = FakeGitHub()
    create = gh._create

    def branch_target(rest):
        out = create(rest)
        gh.releases[-1]["target"] = "master"                         # gh fell back to the default branch
        return out
    gh._create = branch_target
    with pytest.raises(pc.PublishError, match="the draft targets 'master', not the measured commit"):
        pc.publish(bundle, REPO, gh=gh)
    assert "release upload" not in gh.verbs() and gh.releases == [] and gh.tags == {}


def test_a_failed_verification_deletes_the_draft_and_publishes_nothing(bundle):
    gh = FakeGitHub()
    gh.corrupt_upload = ca.LINK_STATUS
    with pytest.raises(pc.PublishError, match="does not hash"):
        pc.publish(bundle, REPO, gh=gh)
    verbs = gh.verbs()
    assert "release edit" not in verbs and "api DELETE" in verbs
    assert gh.releases == [] and gh.tags == {}


def test_a_tag_created_while_drafting_stops_publication(bundle):
    gh = FakeGitHub()
    tag = ca.validate(bundle)["tag"]
    real = gh._download

    def download_then_race(rest):
        out = real(rest)
        gh.tags[tag] = cf.OTHER                                     # someone pushes the tag meanwhile
        return out
    gh._download = download_then_race
    with pytest.raises(pc.PublishError, match="appeared"):
        pc.publish(bundle, REPO, gh=gh)
    assert "release edit" not in gh.verbs() and gh.releases == [] and gh.tags[tag] == cf.OTHER


def test_a_release_published_but_not_immutable_is_reported_and_left_alone(bundle, capsys):
    gh = FakeGitHub()
    edit = gh._edit

    def setting_turned_off(rest):
        gh.immutable_enabled = False                                # between the pre-check and the un-draft
        return edit(rest)
    gh._edit = setting_turned_off
    with pytest.raises(pc.PublishError, match="IS PUBLISHED BUT NOT IMMUTABLE.*Do not delete"):
        pc.publish(bundle, REPO, gh=gh)
    (release,) = gh.releases
    assert not release["draft"] and "api DELETE" not in gh.verbs()   # published stays published


def test_dry_run_checks_read_only_and_prints_members_manifest_and_commands(bundle, capsys):
    gh = FakeGitHub()
    got = pc.publish(bundle, REPO, gh=gh, dry_run=True)
    assert all(c[0] == "api" and "-X" not in c for c in gh.calls), gh.calls
    assert gh.releases == [] and gh.tags == {}
    out = capsys.readouterr().out
    assert "DRY RUN" in out and "account Ancalgonn (id 1760627): a designated publisher" in out
    assert "immutable releases on Open-BFME/Open-BFME-2: enforced" in out
    m = ca.validate(bundle)
    for name, meta in m["members"].items():
        assert f"{meta['sha256']}  {name}" in out
    assert '    |  "schema": "link-cycle-bundle/2",' in out
    create = got["commands"][0]
    assert create.startswith("gh release create link-cycle/") and "--draft --prerelease --latest=false" in create
    assert f"--target {cf.COMMIT}" in create
    assert any(c.startswith("gh release edit") and "--draft=false" in c for c in got["commands"])
    assert all("--clobber" not in c for c in got["commands"])
    notes = Path(got["notes"])
    assert notes.is_file() and m["tag"] in notes.read_text(encoding="utf-8")
    shutil.rmtree(notes.parent)
    # from another account the dry run still prints, and says a real publish would be refused
    got = pc.publish(bundle, REPO, gh=FakeGitHub(user=STRANGER), dry_run=True)
    assert "!! A REAL PUBLISH FROM HERE WOULD BE REFUSED" in capsys.readouterr().out and got["warnings"]
    shutil.rmtree(Path(got["notes"]).parent)


def test_dry_run_survives_an_unreachable_gh_and_a_real_publish_does_not(bundle, capsys):
    gh = FakeGitHub()
    gh.fail_list = True
    got = pc.publish(bundle, REPO, gh=gh, dry_run=True)
    out = capsys.readouterr().out
    assert got["remote_checked"] is False and "REMOTE CHECKS NOT RUN" in out
    assert gh.releases == [] and all(c[0] == "api" for c in gh.calls)
    shutil.rmtree(Path(got["notes"]).parent)
    with pytest.raises(ca.Unavailable):                                       # a real publish never proceeds blind
        pc.publish(bundle, REPO, gh=gh)
    assert gh.releases == []


# ---------------------------------------------------------------- fetch: authentication (Sol 1)

@pytest.fixture
def two(tmp_path):
    """Two valid bundles of different runs: old (10-09) and new (10-10)."""
    old = quick_bundle(tmp_path, "old", commit=cf.OTHER, date_utc="2026-10-09 10:00:00")
    new = quick_bundle(tmp_path, "new", date_utc="2026-10-10 10:00:00")
    return old, new


def test_fetch_authenticates_and_installs_with_its_evidence(tmp_path, two):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    rel = released(gh, new, "2026-10-10T12:00:00Z")
    store = tmp_path / "store"
    manifest, notes, pointer = ca.fetch(REPO, store, gh=gh, now=END)
    assert manifest["tag"] == ca.read_manifest(new)["tag"]
    assert files_of(installed_dir(store, manifest)) == files_of(new)
    ev = json.loads((installed_dir(store, manifest).parent / ca.EVIDENCE).read_text())
    assert ev["author"] == PUBLISHER and ev["immutable"] is True and ev["release_id"] == rel["id"]
    assert ev["tag_commit"] == cf.COMMIT == ev["target_commitish"] and ev["attestation"] == "verified"
    assert ev["manifest_sha256"] == ca.sha256_file(new / ca.MANIFEST)
    assert set(ev["assets"]) == set(files_of(new))
    assert ["release", "verify", manifest["tag"]] == [c for c in gh.calls if c[1] == "verify"][0][:3]
    assert pointer["latest_measurement"] == ca.bundle_id(manifest["tag"]) and len(pointer["bundles"]) == 1
    b, fr, lines = ca.serve(store, now=ca.parse_utc("2026-10-10 11:00:00"))
    assert b.tag == manifest["tag"] and b.evidence == ev and b.dir == installed_dir(store, manifest)
    assert not [p for p in store.iterdir() if p.name.startswith(".partial")] and not (store / ".lock").exists()


def test_an_edited_release_by_another_author_on_a_tag_at_another_commit_is_not_fetched(tmp_path):
    """Sol's repro: a correct-looking tag whose ranking was edited to 999,999,999 B, published
    by an account that is not the publisher, mutable, its tag at another commit."""
    d = closure_quick(tmp_path, "edited", date_utc=cf.recent())
    doc = json.loads(gzip.decompress((d / ca.CLOSURE_ROOTS).read_bytes()))
    doc["roots"][0]["conditional_gain_bytes"] = 999999999
    raw = (json.dumps(doc, sort_keys=True) + "\n").encode()
    (d / ca.CLOSURE_ROOTS).write_bytes(gzip.compress(raw, mtime=0))
    _rewrite_manifest(d, lambda m: m["members"][ca.CLOSURE_ROOTS].update(
        size=(d / ca.CLOSURE_ROOTS).stat().st_size, sha256=ca.sha256_file(d / ca.CLOSURE_ROOTS),
        content_size=len(raw), content_sha256=hashlib.sha256(raw).hexdigest()))
    ca.validate(d)                                                    # self-consistent: integrity is not authorship
    store = tmp_path / "store"
    for kw, why in (({"author": STRANGER}, "is not a designated publisher"),
                    ({"immutable": False}, "is not immutable"),
                    ({"tag_at": "f" * 40}, "resolves to ffffffffffff, not the measured commit"),
                    ({"target": "f" * 40, "tag_at": cf.COMMIT}, "targets 'ffff")):
        gh = FakeGitHub()
        r = released(gh, d, "2026-10-11T21:59:00Z", **kw)
        r["notes"] = "manifest.json sha256 `" + "0" * 64 + "`"       # notes are never read, whatever they say
        warned = []
        with pytest.raises(ca.Refused, match=why) as e:
            ca.fetch(REPO, store, gh=gh, warn=warned.append)
        assert e.value.reason == "unauthenticated" and not store.exists() or not any(store.iterdir())
        with pytest.raises(ca.Refused):                               # --tag is no way round it
            ca.fetch(REPO, store, gh=gh, tag=r["tag_name"], warn=warned.append)


def test_an_asset_that_is_not_the_one_the_release_api_digests_is_refused(tmp_path, two):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    bad = released(gh, new, "2026-10-10T12:00:00Z")
    a = next(a for a in bad["assets"] if a["name"] == ca.RANK_TXT)
    a["digest"] = "sha256:" + hashlib.sha256(a["data"]).hexdigest()   # what the platform bound at upload
    a["data"] = b"served by something between GitHub and here\n"
    warned = []
    store = tmp_path / "store"
    manifest, notes, _ = ca.fetch(REPO, store, gh=gh, warn=warned.append)
    assert manifest["tag"] == ca.read_manifest(old)["tag"]            # the next older measurement, loudly
    assert "the release API says" in warned[0] and ca.read_manifest(new)["tag"] in warned[0]
    assert notes[0].startswith("WARNING: serving") and "not the newest" in notes[0]
    with pytest.raises(ca.BundleError, match="the release API says"):  # --tag never falls back
        ca.fetch(REPO, tmp_path / "store2", gh=gh, tag=ca.read_manifest(new)["tag"])
    del a["digest"]
    a["data"] = files_of(new)[ca.RANK_TXT]
    for asset in bad["assets"]:
        asset["digest"] = ""                                         # an API that reports no digest binds nothing
    with pytest.raises(ca.Refused, match="reports no SHA-256 digest"):
        ca.fetch(REPO, tmp_path / "store3", gh=gh, tag=ca.read_manifest(new)["tag"])


def test_an_annotated_tag_is_peeled_and_a_failed_attestation_refuses(tmp_path, two):
    _, new = two
    gh = FakeGitHub()
    released(gh, new, "2026-10-10T12:00:00Z", tag_at="a" * 40)
    gh.annotated["a" * 40] = cf.COMMIT                                # a tag object pointing at the commit
    manifest, _, _ = ca.fetch(REPO, tmp_path / "store", gh=gh)
    assert manifest["commit"] == cf.COMMIT
    gh.fail_verify = "attestation not found"
    with pytest.raises(ca.Refused, match="gh release verify .* failed"):
        ca.fetch(REPO, tmp_path / "store2", gh=gh)
    gh.fail_verify = 'unknown command "verify" for "gh release"'      # an older gh: recorded, not refused
    ca.fetch(REPO, tmp_path / "store3", gh=gh)
    ev = json.loads((installed_dir(tmp_path / "store3", manifest).parent / ca.EVIDENCE).read_text())
    assert ev["attestation"].startswith("not run: this gh has no `release verify`")


def test_allow_mutable_installs_for_inspection_and_nothing_serves_it(tmp_path, two, capsys):
    _, new = two
    gh = FakeGitHub(immutable=False)
    released(gh, new, "2026-10-10T12:00:00Z")
    store = tmp_path / "store"
    with pytest.raises(ca.Refused, match="no TRUSTED link-cycle prerelease") as e:
        ca.fetch(REPO, store, gh=gh, warn=lambda line: None)
    assert e.value.reason == "unauthenticated"
    manifest, _, pointer = ca.fetch(REPO, store, gh=gh, allow_mutable=True)
    assert pointer["latest_measurement"] is None and pointer["bundles"][0]["authenticated"] is False
    with pytest.raises(ca.Empty, match="holds no authenticated bundle"):
        ca.serve(store, now=ca.parse_utc("2026-10-10 11:00:00"))
    with pytest.raises(ca.Refused, match="--allow-mutable from a release that is NOT immutable") as e:
        ca.serve(installed_dir(store, manifest), now=ca.parse_utc("2026-10-10 11:00:00"))
    assert e.value.reason == "unauthenticated"
    ca.status(store, now=END)
    assert "NOT authenticated (--allow-mutable), never served" in capsys.readouterr().out


def test_a_local_directory_is_not_an_authenticated_publication(tmp_path, two):
    _, new = two
    now = ca.parse_utc("2026-10-10 11:00:00")
    with pytest.raises(ca.Refused, match="has no fetch evidence") as e:
        ca.serve(new, now=now)
    assert e.value.reason == "unauthenticated"
    b, _, lines = ca.serve(new, now=now, local_unpublished=True)
    assert b.evidence is None and any(line.startswith("UNAUTHENTICATED LOCAL BUNDLE") for line in lines)
    # evidence is re-checked against the files: a member swapped after the fetch is not served
    gh = FakeGitHub()
    released(gh, new, "2026-10-10T12:00:00Z")
    store = tmp_path / "store"
    manifest, _, _ = ca.fetch(REPO, store, gh=gh)
    d = installed_dir(store, manifest)
    ev = d.parent / ca.EVIDENCE
    saved = ev.read_text()
    for edit, why in ((lambda e: e.update(author=STRANGER), "not a\\s+designated publisher"),
                      (lambda e: e.update(tag_commit="f" * 40), "not the measured commit"),
                      (lambda e: e.update(manifest_sha256="0" * 64), "not the manifest that was authenticated"),
                      (lambda e: e["assets"][ca.RECEIPT].update(sha256="0" * 64), "not the asset that was"),
                      (lambda e: e.update(tag="link-cycle/other"), "is not the evidence of")):
        doc = json.loads(saved)
        edit(doc)
        ev.write_text(json.dumps(doc))
        with pytest.raises(ca.Refused, match=why):
            ca.serve(d, now=now)
    ev.write_text(saved)
    ca.serve(d, now=now)


# ---------------------------------------------------------------- fetch: which release (Sol choice 3, Astra 4)

def test_fetch_picks_the_newest_complete_prerelease_and_skips_drafts(tmp_path, two):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    released(gh, new, "2026-10-10T12:00:00Z")
    incomplete = dict(files_of(new))
    del incomplete[ca.RANK_JSON]
    gh.add_release("link-cycle/aaaaaaaaaaaa-20261011T120000Z-111111111111", incomplete,
                   published_at="2026-10-11T12:00:00Z")
    gh.add_release("link-cycle/bbbbbbbbbbbb-20261011T130000Z-222222222222", files_of(new), draft=True)
    gh.add_release("link-cycle/cccccccccccc-20261011T140000Z-333333333333", files_of(new), prerelease=False,
                   published_at="2026-10-12T12:00:00Z")
    gh.add_release("link-cycle/275a758e4cbb-7566f388", files_of(new), published_at="2026-10-12T13:00:00Z")
    gh.add_release("v1.0", {"x.zip": b"x"}, prerelease=False, published_at="2026-10-13T12:00:00Z")
    store = tmp_path / "fetched"
    manifest, notes, _ = ca.fetch(REPO, store, gh=gh)
    assert manifest["tag"] == ca.read_manifest(new)["tag"]
    assert files_of(installed_dir(store, manifest)) == files_of(new)
    joined = "\n".join(notes)
    assert "111111111111 skipped: incomplete" in joined
    assert "222222222222 skipped: draft" in joined
    assert "333333333333 skipped: not a prerelease" in joined
    assert "link-cycle/275a758e4cbb-7566f388 skipped: not a link-cycle measurement tag" in joined
    assert ["release", "download", manifest["tag"]] == [c for c in gh.calls if c[1] == "download"][0][:3]


def test_latest_is_the_newest_measurement_not_the_newest_publication(tmp_path, two, capsys):
    """Sol's backfill repro: the older run is published AFTER the newer one."""
    old, new = two
    gh = FakeGitHub()
    released(gh, new, "2026-10-10T12:00:00Z")
    released(gh, old, "2026-10-10T13:00:00Z")                         # backfilled later
    store = tmp_path / "store"
    manifest, _, pointer = ca.fetch(REPO, store, gh=gh)
    assert manifest["tag"] == ca.read_manifest(new)["tag"]
    assert pointer["latest_measurement"] == ca.bundle_id(manifest["tag"])
    assert "newest measurement first" in pointer["order"]
    b, _, _ = ca.serve(store, now=ca.parse_utc("2026-10-10 11:00:00"))  # and the queue is not refused as stale
    assert b.commit == cf.COMMIT
    # installing the backfill too does not move the pointer back
    ca.fetch(REPO, store, gh=gh, tag=ca.read_manifest(old)["tag"])
    assert ca.read_pointer(store)["latest_measurement"] == ca.bundle_id(manifest["tag"])
    assert [e["commit"][:10] for e in ca.read_pointer(store)["bundles"]] == [cf.COMMIT[:10], cf.OTHER[:10]]


def test_a_bundle_published_without_a_closure_report_does_not_disable_the_closure_queue(tmp_path, capsys):
    """Astra 4: two explicit answers, latest measurement and latest closure-ready bundle."""
    ready = closure_quick(tmp_path, "ready", commit=cf.OTHER, date_utc="2026-10-10 10:00:00")
    bare = quick_bundle(tmp_path, "bare", date_utc="2026-10-10 20:00:00")       # newer, diagnostic-only
    gh = FakeGitHub()
    released(gh, ready, "2026-10-10T12:00:00Z")
    released(gh, bare, "2026-10-10T21:00:00Z")
    store = tmp_path / "store"
    manifest, notes, pointer = ca.fetch(REPO, store, gh=gh)
    bare_tag, ready_tag = ca.read_manifest(bare)["tag"], ca.read_manifest(ready)["tag"]
    assert manifest["tag"] == bare_tag
    assert pointer["latest_measurement"] == ca.bundle_id(bare_tag)
    assert pointer["latest_closure_ready"] == ca.bundle_id(ready_tag)
    assert any("has no closure report: also installed" in n and ready_tag in n for n in notes)
    now = ca.parse_utc("2026-10-10 22:00:00")
    assert ca.serve(store, now=now)[0].tag == bare_tag                           # the measurement queue: newest
    b, fr, lines = ca.serve(store, now=now, need_closure=True)                   # the closure queue: newest WITH one
    assert b.tag == ready_tag and fr["age_hours"] == 12.0
    (note,) = b.notes
    assert note.startswith(f"NOT THE NEWEST MEASUREMENT: serving {ready_tag}") and bare_tag in note
    assert "published without one (published diagnostic-only" in note and note in lines
    capsys.readouterr()
    ca.status(store, now=now)
    out = capsys.readouterr().out.splitlines()
    assert out[0].startswith(f"latest measurement: {bare_tag} measured 2026-10-10T20:00:00Z; 2.0 h old; rules "
                             "link-cycle-2; no closure report (")
    assert out[1].startswith(f"latest compatible closure-ready bundle: {ready_tag} measured 2026-10-10T10:00:00Z; "
                             "12.0 h old; rules link-cycle-2; closure report: measured graph, bound to the receipt")
    assert out[1].endswith("<- the closure queue serves THIS one")
    # with no closure-ready bundle at all the reason is its own
    lone = tmp_path / "lone"
    gh2 = FakeGitHub()
    released(gh2, bare, "2026-10-10T21:00:00Z")
    ca.fetch(REPO, lone, gh=gh2)
    with pytest.raises(ca.Refused, match="no bundle in the store .* carries a closure report") as e:
        ca.serve(lone, now=now, need_closure=True)
    assert e.value.reason == "no-closure-report" and ca.exit_code(e.value) == 7


def test_fetch_tag_exact_draft_and_missing(tmp_path, two):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    released(gh, new, "2026-10-10T12:00:00Z")
    draft = "link-cycle/dddddddddddd-20261011T120000Z-444444444444"
    gh.add_release(draft, files_of(new), draft=True)
    manifest, _, _ = ca.fetch(REPO, tmp_path / "o", gh=gh, tag=ca.read_manifest(old)["tag"])
    assert manifest["tag"] == ca.read_manifest(old)["tag"]
    with pytest.raises(ca.BundleError, match="draft"):
        ca.fetch(REPO, tmp_path / "d", gh=gh, tag=draft)
    with pytest.raises(ca.Unavailable, match="no release"):
        ca.fetch(REPO, tmp_path / "m", gh=gh, tag="link-cycle/eeeeeeeeeeee-20261011T120000Z-555555555555")


def test_empty_and_unavailable_are_distinct(tmp_path, monkeypatch, capsys):
    gh = FakeGitHub()
    gh.add_release("link-cycle/bbbbbbbbbbbb-20261011T130000Z-222222222222", {"manifest.json": b"{}"}, draft=True)
    with pytest.raises(ca.Empty, match="no complete link-cycle prerelease"):
        ca.fetch(REPO, tmp_path / "o", gh=gh)
    gh.fail_list = True
    with pytest.raises(ca.Unavailable, match="cannot list"):
        ca.fetch(REPO, tmp_path / "o", gh=gh)
    monkeypatch.setattr(ca, "Gh", lambda: gh)
    assert ca.main(["fetch", "--latest", "--repo", REPO, "--store", str(tmp_path / "o")]) == ca.EXIT["unavailable"]
    assert "unavailable [reason=unavailable]" in capsys.readouterr().err
    gh.fail_list = False
    assert ca.main(["fetch", "--latest", "--repo", REPO, "--store", str(tmp_path / "o")]) == ca.EXIT["empty"]
    assert "empty [reason=empty]" in capsys.readouterr().err
    assert not (tmp_path / "o" / ca.POINTER).exists()


# ---------------------------------------------------------------- the store: immutable directories, one pointer (Astra 3)

def test_a_failed_download_leaves_the_store_as_it_was(tmp_path, two):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    store = tmp_path / "out"
    first, _, _ = ca.fetch(REPO, store, gh=gh)
    before = files_of(installed_dir(store, first))
    pointer = (store / ca.POINTER).read_bytes()
    released(gh, new, "2026-10-10T12:00:00Z")
    gh.fail_download_after = 2                                       # two files land, then the network fails
    with pytest.raises(ca.Unavailable, match="connection reset"):
        ca.fetch(REPO, store, gh=gh)
    assert (store / ca.POINTER).read_bytes() == pointer and files_of(installed_dir(store, first)) == before
    assert sorted(p.name for p in store.iterdir()) == sorted([ca.POINTER, ca.bundle_id(first["tag"])])
    gh.fail_download_after = None
    second, _, _ = ca.fetch(REPO, store, gh=gh)
    assert files_of(installed_dir(store, second)) == files_of(new)
    assert files_of(installed_dir(store, first)) == before          # the older bundle is still there, untouched
    fresh = tmp_path / "never"
    gh.fail_download_after = 1
    with pytest.raises(ca.Unavailable):
        ca.fetch(REPO, fresh, gh=gh)
    assert not (fresh / ca.POINTER).exists() and not [p for p in fresh.iterdir() if p.name != ".lock"]


def test_a_reader_during_a_refresh_always_reads_one_whole_bundle(tmp_path, two, monkeypatch):
    """A reader that resolved the pointer before a refresh keeps reading the same immutable
    directory; a reader arriving at ANY step of the refresh finds a complete bundle."""
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    store = tmp_path / "store"
    ca.fetch(REPO, store, gh=gh)
    now = ca.parse_utc("2026-10-10 11:00:00")
    early, _, _ = ca.serve(store, now=now, allow_stale=True)
    early_files = files_of(early.dir)
    released(gh, new, "2026-10-10T12:00:00Z")
    seen = []

    def observe(step):
        b, _, _ = ca.serve(store, now=now, allow_stale=True)        # a new reader, at this very step
        assert files_of(b.dir) in (files_of(old), files_of(new))
        assert ca.validate(b.dir)["tag"] == b.tag
        assert files_of(early.dir) == early_files                    # the earlier reader's bundle is untouched
        seen.append((step, b.commit[:10]))
    rename, replace, download = os.rename, os.replace, gh._download
    monkeypatch.setattr(ca.os, "rename", lambda a, b: (observe("before rename"), rename(a, b), observe("after rename"))[1])
    monkeypatch.setattr(ca.os, "replace", lambda a, b: (observe("before replace"), replace(a, b),
                                                        observe("after replace"))[1])
    gh._download = lambda rest: (observe("before download"), download(rest), observe("after download"))[1]
    ca.fetch(REPO, store, gh=gh)
    monkeypatch.undo()
    assert [s for s, _ in seen] == ["before download", "after download", "before rename", "after rename",
                                    "before replace", "after replace"]
    assert [c for _, c in seen] == [cf.OTHER[:10]] * 5 + [cf.COMMIT[:10]]     # one atomic switch, at the pointer
    assert files_of(early.dir) == early_files == files_of(old)
    assert ca.serve(store, now=now)[0].commit == cf.COMMIT


def test_a_crash_between_install_and_pointer_keeps_the_old_bundle_current(tmp_path, two, monkeypatch):
    old, new = two
    gh = FakeGitHub()
    released(gh, old, "2026-10-09T12:00:00Z")
    store = tmp_path / "store"
    ca.fetch(REPO, store, gh=gh)
    released(gh, new, "2026-10-10T12:00:00Z")

    def crash(*a, **k):
        raise KeyboardInterrupt
    monkeypatch.setattr(ca, "write_pointer", crash)
    with pytest.raises(KeyboardInterrupt):
        ca.fetch(REPO, store, gh=gh)
    monkeypatch.undo()
    now = ca.parse_utc("2026-10-10 11:00:00")
    assert ca.serve(store, now=now, allow_stale=True)[0].commit == cf.OTHER   # still served, whole
    assert not (store / ".lock").exists()                                    # and no writer is locked out
    downloads = len([c for c in gh.calls if c[1] == "download"])
    ca.fetch(REPO, store, gh=gh)                                             # the installed directory is kept as is
    assert len([c for c in gh.calls if c[1] == "download"]) == downloads
    assert ca.serve(store, now=now)[0].commit == cf.COMMIT


def test_writers_are_serialized_and_a_dead_writers_lock_is_broken(tmp_path):
    store = tmp_path / "store"
    lock = ca.store_lock(store)
    with pytest.raises(ca.Unavailable, match="held by another fetch"):
        ca.store_lock(store, wait=0.3)
    os.utime(lock, (time.time() - 3600, time.time() - 3600))                 # its writer died an hour ago
    assert ca.store_lock(store, wait=0.3) == lock
    lock.unlink()


def test_an_installed_bundle_is_never_replaced_by_another_release_of_its_tag(tmp_path, two):
    _, new = two
    gh = FakeGitHub()
    rel = released(gh, new, "2026-10-10T12:00:00Z")
    store = tmp_path / "store"
    manifest, _, _ = ca.fetch(REPO, store, gh=gh)
    rel["id"] += 1000                                                        # the tag now names another release
    with pytest.raises(ca.BundleError, match="already installed from another release"):
        ca.fetch(REPO, store, gh=gh, tag=manifest["tag"])


# ---------------------------------------------------------------- serving: age, rules, reasons

def test_serve_refuses_a_stale_bundle_and_one_of_other_rules(tmp_path, bundle):
    b, fr, lines = ca.serve(bundle, now=END + 3600, local_unpublished=True)
    assert b.tag.startswith("link-cycle/") and not fr["stale"] and fr["rules_match"] is True
    assert "rules link-cycle-2: this checkout's" in lines
    with pytest.raises(ca.Refused, match=r"STALE: measured 25.0 h ago, over the 24 h window .*--allow-stale") as e:
        ca.serve(bundle, now=END + 25 * 3600, local_unpublished=True)
    assert e.value.reason == "stale" and ca.exit_code(e.value) == 4
    b, fr, lines = ca.serve(bundle, now=END + 25 * 3600, allow_stale=True, local_unpublished=True)
    assert fr["stale"] and any(line.startswith("STALE") for line in lines)
    other = quick_bundle(tmp_path, "other-rules", rules="link-cycle-3")
    assert ca.validate(other)["rules"]["rules"] == "link-cycle-3"            # intact: integrity is not the question
    for allow in (False, True):                                               # and there is no override
        with pytest.raises(ca.Refused, match="RULES MISMATCH: measured under link-cycle-3") as e:
            ca.serve(other, now=END + 3600, allow_stale=allow, local_unpublished=True)
        assert e.value.reason == "incompatible-rules" and ca.exit_code(e.value) == 5
    assert ca.main(["validate", str(other), "--allow-stale", "--local-unpublished"]) == 5


def test_unknown_local_rules_refuse_whatever_else_is_allowed(tmp_path, bundle):
    """Sol 5 / Astra 2: a checkout whose link_cycle rules cannot be read has not established
    compatibility. The tool digest is only compared once the rules positively match."""
    assert ca.local_rules(TOOLS.parent) == {"rules": "link-cycle-2", "shadow_rules": lc.SHADOW_RULES,
                                            "canon_rules": lc.CANON_RULES}
    assert ca.local_rules(tmp_path) is None
    for allow in (False, True):
        with pytest.raises(ca.Refused, match="RULES UNKNOWN: .* compatibility is not established") as e:
            ca.serve(bundle, now=END + 3600, root=tmp_path, allow_stale=allow, local_unpublished=True)
        assert e.value.reason == "incompatible-rules"
    refactored = tmp_path / "refactored"                                      # a rules declaration this reader misses
    cf.write(refactored / "tools/link_cycle.py", 'RULES = "link-cycle-2"\nreceipt = dict(rules=RULES)\n')
    assert ca.local_rules(refactored) is None
    b = ca.load_bundle(bundle)
    fr = b.freshness(now=END + 3600, root=tmp_path)
    text = "\n".join(ca.format_freshness(b, fr))
    assert "RULES UNKNOWN" in text and "tool digest" not in text


def test_a_tool_digest_difference_under_equal_rules_is_a_warning(tmp_path):
    other = quick_bundle(tmp_path, "tool", tool_digest="ab" * 32)
    b, fr, lines = ca.serve(other, now=END + 3600, local_unpublished=True)
    assert fr["rules_match"] is True and fr["tool_digest_matches"] is False
    (line,) = [x for x in lines if x.startswith("link_cycle tool digest")]
    assert "equal rules, another build of the tool (a warning" in line
    assert b.core_check.startswith("not recomputed")


def test_every_refusal_has_its_own_reason_and_exit_code(tmp_path, two, capsys):
    """Astra (outages): an orchestrator tells stale from incompatible from corrupt from
    unauthenticated from unavailable without parsing prose."""
    _, new = two
    stale = quick_bundle(tmp_path, "stale", date_utc="2026-01-01 00:00:00")
    rules = quick_bundle(tmp_path, "rules", rules="link-cycle-3", date_utc=cf.recent())
    corrupt = quick_bundle(tmp_path, "corrupt", date_utc=cf.recent())
    (corrupt / ca.RANK_TXT).write_text("x")
    fresh = quick_bundle(tmp_path, "fresh", date_utc=cf.recent())
    seen = {}
    for name, argv in (("stale", [str(stale), "--local-unpublished"]),
                       ("incompatible-rules", [str(rules), "--local-unpublished"]),
                       ("corrupt", [str(corrupt), "--local-unpublished"]),
                       ("unauthenticated", [str(fresh)]),
                       ("unavailable", [str(tmp_path / "nowhere")])):
        seen[name] = ca.main(["validate", *argv])
        assert f"[reason={name}]" in capsys.readouterr().err
    assert seen == {k: ca.EXIT[k] for k in seen} and len(set(seen.values())) == 5
    assert ca.main(["validate", str(fresh), "--local-unpublished"]) == 0
    assert ca.main(["validate", str(stale), "--local-unpublished", "--allow-stale"]) == 0


def test_staleness_is_reported_never_silent(tmp_path, bundle, capsys):
    b = ca.load_bundle(bundle)
    fresh = b.freshness(now=END + 3600, root=tmp_path)
    assert not fresh["stale"] and fresh["age_hours"] == 1.0
    assert not any(line.startswith("STALE") for line in ca.format_freshness(b, fresh))
    stale = b.freshness(now=END + 25 * 3600, root=tmp_path)
    assert stale["stale"] and stale["age_hours"] == 25.0
    lines = ca.format_freshness(b, stale)
    assert lines[1].startswith("STALE: measured 25.0 h ago, over the 24 h window")
    assert "ancestry unknown" in lines[2]                            # tmp_path is no checkout, wherever it sits
    aged = quick_bundle(tmp_path, "aged", date_utc="2026-01-01 00:00:00")
    capsys.readouterr()
    assert ca.main(["validate", str(aged), "--local-unpublished"]) == ca.EXIT["stale"]
    got = capsys.readouterr()
    assert got.out.startswith("valid: ") and "STALE: measured" in got.out
    assert "cycle_artifacts: refused [reason=stale]: bundle link-cycle/" in got.err and "--allow-stale" in got.err
    assert ca.main(["validate", str(aged), "--allow-stale", "--local-unpublished"]) == 0
    got = capsys.readouterr()
    assert "STALE: measured" in got.err and "STALE: measured" in got.out


def test_ancestry_asks_only_a_directory_that_is_itself_a_checkout(tmp_path):
    """Location independence (Astra): a scratch directory INSIDE a repository is not that
    repository; without this the answer depended on where pytest kept its temp files."""
    repo = tmp_path / "r"
    _git(tmp_path, "init", "-q", str(repo))
    shas = []
    for n in range(3):
        (repo / "f").write_text(str(n))
        _git(repo, "add", "f")
        _git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", str(n))
        shas.append(_git(repo, "rev-parse", "HEAD"))
    assert ca.ancestry(shas[0], repo)[2].startswith("ancestry unknown: no local origin/master")
    _git(repo, "update-ref", "refs/remotes/origin/master", shas[2])
    assert ca.ancestry(shas[0], repo)[:2] == (True, 2)
    inside = repo / "build" / "scratch"
    inside.mkdir(parents=True)
    anc, behind, note = ca.ancestry(shas[0], inside)                         # sits in the repository; is not it
    assert (anc, behind) == (None, None) and note == f"ancestry unknown: {inside} is not a git checkout"
    _git(repo, "checkout", "-q", "-b", "side", shas[0])
    (repo / "g").write_text("side")
    _git(repo, "add", "g")
    _git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "side")
    anc, behind, note = ca.ancestry(_git(repo, "rev-parse", "HEAD"), repo)
    assert (anc, behind) == (False, None) and "NOT an ancestor" in note
    assert ca.ancestry("f" * 40, repo)[2].startswith("ancestry unknown: ffffffffffff is not in this clone")


def test_the_committed_receipt_is_labelled_history(tmp_path, bundle, capsys):
    cf.write(tmp_path / "reverse/link_cycle/receipt.json", json.dumps(
        {"commit": cf.OTHER, "date_utc": "2026-10-10 09:43:00", "series": {"credit_unique_bytes": 1103526}}))
    note = ca.history_note(tmp_path)
    assert note.startswith("history: the committed reverse/link_cycle/receipt.json (commit 31d8b0fddd01, "
                           "2026-10-10 09:43:00 UTC, credit 1,103,526 B) is an earlier measurement")
    assert ca.history_note(tmp_path / "none") is None
    ca.report(ca.load_bundle(bundle), now=END + 3600, root=tmp_path)
    out = capsys.readouterr().out.splitlines()
    assert out[1].startswith("link-cycle figure of this bundle: credit 64 B") and out[2] == note
    assert "closure_report: not in this bundle (published diagnostic-only" in "\n".join(out)
    assert "cycle_diff: not in this bundle (no --previous run and no --first given)" in out


# ---------------------------------------------------------------- optional components: published and fetched whole

def test_optional_members_are_published_authenticated_and_fetched(tmp_path):
    run = cf.make_run(tmp_path / "snaps", status=cf.CLOSURE_STATUS, rank_files=True, closure=True)
    out = tmp_path / "bundle"
    m = cf.bundle(run, out, "laptop/watchdog", require_closure=True)
    assert ca.CLOSURE_GRAPH in m["members"] and m["receipt"]["closure_graph_sha256"] == m["members"][
        ca.CLOSURE_GRAPH]["sha256"]
    gh = FakeGitHub()
    pc.publish(out, REPO, gh=gh)
    (release,) = gh.releases
    assert {a["name"] for a in release["assets"]} == set(ca.MEMBERS) | {
        ca.MANIFEST, ca.CLOSURE_GRAPH, ca.CLOSURE_ROOTS, ca.CLOSURE_BLOCKERS}
    assert ("closure report (conditional-single-address-gain/1; measured graph, bound to the receipt): 2 scored "
            "root(s)") in release["notes"]
    assert "cycle_diff.json: not included" in release["notes"] and "is history" in release["notes"]
    store = tmp_path / "fetched"
    got, _, pointer = ca.fetch(REPO, store, gh=gh)
    assert got["tag"] == m["tag"] and files_of(installed_dir(store, got)) == files_of(out)
    assert pointer["latest_closure_ready"] == pointer["latest_measurement"]
    # an optional asset the release lists but did not finish uploading makes the release incomplete
    view = gh._rest_view(release)
    next(a for a in view["assets"] if a["name"] == ca.CLOSURE_ROOTS)["state"] = "starter"
    assert ca.release_problem(view) == "incomplete: no uploaded closure_roots.json.gz"
    view = gh._rest_view(release)
    view["assets"].append({"name": "extra.zip", "state": "uploaded"})
    assert ca.release_problem(view) == "holds assets that are not bundle members: extra.zip"


def test_a_bundle_without_a_closure_report_is_an_explicit_diagnostic_publication(tmp_path, capsys):
    run = cf.make_run(tmp_path / "snaps", rank_files=True)
    with pytest.raises(pc.RunError, match="holds no closure report .*closure_report.py replay.*--diagnostic-only"):
        cf.bundle(run, tmp_path / "strict", "x", require_closure=True)
    assert not (tmp_path / "strict").exists()
    assert pc.main(["bundle", str(run), "--out", str(tmp_path / "cli"), "--producer", "x"]) == 1   # the CLI's default
    assert pc.main(["bundle", str(run), "--out", str(tmp_path / "cli"), "--producer", "x", "--diagnostic-only"]) == 0
    m = ca.validate(tmp_path / "cli")
    assert m["components"]["closure_report"]["status"] == "diagnostic-only"
    assert "closure_report: NOT included (published diagnostic-only" in capsys.readouterr().out
    gh = FakeGitHub()
    pc.publish(tmp_path / "cli", REPO, gh=gh)
    assert "DIAGNOSTIC-ONLY: no closure report" in gh.releases[0]["notes"]


# ---------------------------------------------------------------- cycle_diff.json (tools/cycle_diff.py, when present)

def test_a_bundle_is_valid_without_cycle_diff(tmp_path, monkeypatch):
    run = cf.make_run(tmp_path / "snaps", rank_files=True)
    assert cf.bundle(run, tmp_path / "a", "x")["components"]["cycle_diff"] == {
        "included": False, "why": "no --previous run and no --first given"}
    monkeypatch.setattr(pc, "cycle_diff_module", lambda: None)               # a checkout without the tool
    m = cf.bundle(run, tmp_path / "b", "x", first=True)
    assert m["components"]["cycle_diff"] == {"included": False,
                                             "why": "tools/cycle_diff.py is not in the producer's checkout"}
    assert ca.CYCLE_DIFF not in m["members"] and ca.validate(tmp_path / "b")
    with pytest.raises(pc.RunError, match="exclude each other"):
        cf.bundle(run, tmp_path / "c", "x", first=True, previous=tmp_path / "a")


def test_the_bundle_embeds_and_binds_the_cycle_diff_report(tmp_path):
    import cycle_diff as cd                                                   # lands in the same push: no skip
    grown = cf.STATUS + [["?new@@YAXXZ", "real", "Code/n.cpp", "0x00007000", 36, "0x00007000", 1, "", 1, 1, 1, 1, 1,
                          0, 0, ""]]
    old_run = cf.make_run(tmp_path / "s-old", commit=cf.OTHER, rank_files=True, date_utc="2026-10-10 10:00:00")
    new_run = cf.make_run(tmp_path / "s-new", rank_files=True, status=grown, credit=100)
    old = tmp_path / "old"
    first = cf.bundle(old_run, old, "x", first=True)                     # no predecessor
    c = first["components"]["cycle_diff"]
    assert c["included"] and c["comparison"] is False and c["predecessor"] is None
    assert json.loads((old / ca.CYCLE_DIFF).read_text())["comparison"] is False
    new = tmp_path / "new"
    m = cf.bundle(new_run, new, "x", previous=old)                       # the predecessor: a fetched bundle
    c = m["components"]["cycle_diff"]
    assert c["included"] and c["comparison"] is True and c["schema_version"] == cd.SCHEMA_VERSION
    assert c["predecessor"] == {"commit": cf.OTHER, "core_sha256": first["receipt"]["core_sha256"],
                                "tag": first["tag"], "receipt_sha256": first["instance"]["receipt_sha256"],
                                "measured_end_utc": "2026-10-10T10:00:00Z"}   # named as a MEASUREMENT
    text = (new / ca.CYCLE_DIFF).read_text(encoding="utf-8")
    assert text == cd.dumps(cd.compare(str(old), str(new_run)))               # the public serializer's bytes
    report = json.loads(text)
    assert report["identity"]["new"]["commit"] == cf.COMMIT and report["identity"]["old"]["commit"] == cf.OTHER
    assert m["members"][ca.CYCLE_DIFF]["sha256"] == ca.sha256_file(new / ca.CYCLE_DIFF)   # bound in the manifest
    b = ca.load_bundle(new)
    assert b.cycle_diff == new / ca.CYCLE_DIFF
    gh = FakeGitHub()
    pc.publish(new, REPO, gh=gh)
    assert ca.CYCLE_DIFF in {a["name"] for a in gh.releases[0]["assets"]}
    assert f"cycle_diff.json: credit against `{first['tag']}`" in gh.releases[0]["notes"]
    # a report swapped for another run's, with the manifest's member hash made to agree, is still refused
    shutil.copyfile(old / ca.CYCLE_DIFF, new / ca.CYCLE_DIFF)
    _rewrite_manifest(new, lambda mm: mm["members"][ca.CYCLE_DIFF].update(
        sha256=ca.sha256_file(new / ca.CYCLE_DIFF), size=(new / ca.CYCLE_DIFF).stat().st_size))
    with pytest.raises(ca.BundleError, match="its NEW run 31d8b0fddd01 is not this bundle's"):
        ca.validate(new)
    with pytest.raises(pc.RunError, match="is this measurement itself"):
        cf.bundle(new_run, tmp_path / "self", "x", previous=new_run)
    with pytest.raises(pc.RunError, match="was measured after this run"):     # a predecessor is EARLIER
        cf.bundle(old_run, tmp_path / "backwards", "x", previous=new_run)
    assert not (tmp_path / "self").exists() and not (tmp_path / "backwards").exists()


def test_a_rerun_of_the_predecessors_commit_is_a_legitimate_predecessor(tmp_path):
    """Same commit, same core, another measurement time: the predecessor record tells them apart."""
    import cycle_diff                                                         # lands in the same push: no skip
    assert cycle_diff.SCHEMA_VERSION
    a = cf.make_run(tmp_path / "s-a", rank_files=True, date_utc="2026-10-10 10:00:00")
    b = cf.make_run(tmp_path / "s-b", rank_files=True, date_utc="2026-10-11 10:00:00")
    first = cf.bundle(a, tmp_path / "a", "x", first=True)
    m = cf.bundle(b, tmp_path / "b", "x", previous=tmp_path / "a")
    pred = m["components"]["cycle_diff"]["predecessor"]
    assert pred["tag"] == first["tag"] != m["tag"] and pred["core_sha256"] == m["receipt"]["core_sha256"]
    _rewrite_manifest(tmp_path / "b", lambda mm: mm["components"]["cycle_diff"]["predecessor"].update(
        tag="link-cycle/275a758e4cbb-7566f388"))
    with pytest.raises(ca.BundleError, match="predecessor is not named by its measurement"):
        ca.validate(tmp_path / "b")


def test_the_closure_queue_and_status_choose_by_the_complete_rules_tuple(tmp_path, capsys):
    """Final review 1: an older closure bundle of this checkout's rules beside a newer one of
    other rules. status named the older while serve chose, and refused, the newer."""
    old = closure_quick(tmp_path, "old", commit=cf.OTHER, date_utc="2026-10-11 15:00:00")
    new = closure_quick(tmp_path, "new", date_utc="2026-10-11 16:00:00", rules="link-cycle-3")
    gh = FakeGitHub()
    released(gh, old, "2026-10-11T16:00:00Z")
    released(gh, new, "2026-10-11T17:00:00Z")
    store = tmp_path / "store"
    manifest, notes, pointer = ca.fetch(REPO, store, gh=gh)          # one fetch acquires both
    old_tag, new_tag = ca.read_manifest(old)["tag"], ca.read_manifest(new)["tag"]
    assert manifest["tag"] == new_tag and pointer["latest_measurement"] == ca.bundle_id(new_tag)
    assert any("was measured under other link_cycle rules: also installed" in n and old_tag in n for n in notes)
    assert ca.closure_choice(pointer) == (ca.bundle_id(old_tag), True)
    now = ca.parse_utc("2026-10-11 18:00:00")
    b, _, lines = ca.serve(store, now=now, need_closure=True)
    assert b.tag == old_tag
    (note,) = b.notes
    assert note.startswith(f"NOT THE NEWEST MEASUREMENT: serving {old_tag}") and new_tag in note and note in lines
    assert "carries one measured under other link_cycle rules (link-cycle-3 " in note
    with pytest.raises(ca.Refused) as e:                              # the measurement queue: the newest, refused
        ca.serve(store, now=now)
    assert e.value.reason == "incompatible-rules"
    capsys.readouterr()
    ca.status(store, now=now)
    out = capsys.readouterr().out.splitlines()
    assert out[0].startswith(f"latest measurement: {new_tag} ") and "(NOT this checkout's link-cycle-2 " in out[0]
    assert out[1].startswith(f"latest compatible closure-ready bundle: {old_tag} measured 2026-10-11T15:00:00Z; "
                             "3.0 h old; rules link-cycle-2; ")
    assert out[1].endswith("<- the closure queue serves THIS one")
    assert out[2].startswith("measurement queue: NOT SERVED: refused [reason=incompatible-rules]")
    assert "credit" not in out[2]
    assert out[3] == f"closure queue: serves {old_tag}, measured 2026-10-11T15:00:00Z, 3.0 h ago"
    # past the window status promises nothing: the line is labelled and the queue's own refusal is shown
    ca.status(store, now=ca.parse_utc("2026-10-13 18:00:00"))
    out = capsys.readouterr().out.splitlines()
    assert out[1].startswith(f"latest compatible closure-ready bundle: {old_tag} ") and ", STALE; " in out[1]
    assert "serves THIS one" not in out[1]
    assert out[3].startswith("closure queue: NOT SERVED: refused [reason=stale]")
    # with only the other-rules bundle installed there is no compatible one, and the queue is refused by rules
    lone = tmp_path / "lone"
    gh2 = FakeGitHub()
    released(gh2, new, "2026-10-11T17:00:00Z")
    _, notes, pointer = ca.fetch(REPO, lone, gh=gh2)
    assert ca.closure_choice(pointer) == (ca.bundle_id(new_tag), False) and not notes
    with pytest.raises(ca.Refused) as e:
        ca.serve(lone, now=now, need_closure=True)
    assert e.value.reason == "incompatible-rules"
    ca.status(lone, now=now)
    out = capsys.readouterr().out.splitlines()
    assert out[1] == "latest compatible closure-ready bundle: none"
    assert out[3].startswith("closure queue: NOT SERVED: refused [reason=incompatible-rules]")


@pytest.mark.parametrize("change", [{"rules": "link-cycle-3"}, {"shadow_rules": []}, {"shadow_rules": ["another-fold"]},
                                    {"canon_rules": "another-canon"}])
def test_a_shadow_or_canon_rule_difference_alone_is_another_rule_set(change):
    mine = ca.local_rules()
    assert mine and mine["shadow_rules"] and mine["canon_rules"]

    def entry(ident, rules, **kw):
        return {"id": ident, "authenticated": True, "closure_report": True, "rules_tuple": rules, **kw}
    newer, older = entry("newer", {**mine, **change}), entry("older", dict(mine))
    assert ca.closure_choice({"bundles": [newer, older]}) == ("older", True)
    assert ca.closure_choice({"bundles": [newer]}) == ("newer", False)
    assert ca.closure_choice({"bundles": [newer, entry("older", dict(mine), authenticated=False)]}) == ("newer", False)
    assert ca.closure_choice({"bundles": [newer, entry("older", dict(mine), closure_report=False)]}) == ("newer", False)
    assert ca.closure_choice({"bundles": [newer, {k: v for k, v in older.items() if k != "rules_tuple"}]}) == (
        "newer", False)                                               # an entry that does not say is not compatible
    assert ca.closure_choice({"bundles": []}) == (None, False)


def test_fetch_gives_up_on_the_closure_queue_after_a_bounded_look_back(tmp_path, monkeypatch):
    gh = FakeGitHub()
    for hour in range(4):
        b = closure_quick(tmp_path, f"b{hour}", date_utc=f"2026-10-11 1{hour}:00:00", rules="link-cycle-3")
        released(gh, b, f"2026-10-11T1{hour}:30:00Z")
    monkeypatch.setattr(ca, "CLOSURE_LOOKBACK", 2)
    _, notes, pointer = ca.fetch(REPO, tmp_path / "store", gh=gh)
    assert len(pointer["bundles"]) == 3                               # the newest and two older ones, no more
    assert any("none of the 2 older closure-ready release(s) tried is of this checkout's rules" in n for n in notes)
    assert ca.closure_choice(pointer)[1] is False


def test_fetch_prints_the_authenticated_figure_and_age_or_the_refusal(tmp_path, monkeypatch, capsys):
    """Final review 2: the advertised command printed no figure."""
    stamp = lambda hours: time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(time.time() - hours * 3600))  # noqa: E731
    fresh = closure_quick(tmp_path, "fresh", date_utc=cf.recent(2))
    gh = FakeGitHub()
    released(gh, fresh, stamp(1))
    monkeypatch.setattr(ca, "Gh", lambda: gh)
    assert ca.main(["fetch", "--latest", "--store", str(tmp_path / "store")]) == 0
    out = capsys.readouterr().out.splitlines()
    tag = ca.read_manifest(fresh)["tag"]
    (line,) = [x for x in out if x.startswith("measurement queue: ")]
    assert line.startswith(f"measurement queue: serves {tag}, measured ")
    assert "2.0 h ago; link-cycle figure of this bundle: credit 64 B (placed closed-strict real unique bytes)" in line
    assert any(x.startswith(f"closure queue: serves {tag}, measured ") and x.endswith("2.0 h ago") for x in out)
    # a bundle past the window is fetched, and its figure is NOT printed as the current one
    stale = quick_bundle(tmp_path, "stale", commit=cf.OTHER, date_utc="2026-10-01 10:00:00")
    gh2 = FakeGitHub()
    released(gh2, stale, "2026-10-01T12:00:00Z")
    monkeypatch.setattr(ca, "Gh", lambda: gh2)
    assert ca.main(["fetch", "--latest", "--store", str(tmp_path / "old-store")]) == 0
    out = capsys.readouterr().out.splitlines()
    (line,) = [x for x in out if x.startswith("measurement queue: ")]
    assert line.startswith("measurement queue: NOT SERVED: refused [reason=stale]") and "credit" not in line
    assert any(x.startswith("closure queue: NOT SERVED: refused [reason=no-closure-report]") for x in out)
