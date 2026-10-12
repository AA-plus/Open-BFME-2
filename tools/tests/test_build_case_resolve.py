"""_case_resolve must return the on-disk spelling, also on a case-folding host.

Wine's /showIncludes prints the requested spelling of a path, often with a
lowercased prefix. On Linux that path does not exist, so _case_resolve walks
the directory listings. On macOS (APFS/HFS+ fold case by default) the
misspelled path *does* exist, and returning it unchanged left receipts with
`/users/...` paths that no case-sensitive comparison against the include
search roots could match: every TU reported "an included header lies outside
the inventoried search roots", and link_census could not prove
VersionDestructor.cpp at all.
"""
import os
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
import pytest

_ROOT = str(Path(__file__).resolve().parents[2])
FOLDS = os.name != "nt" and _ROOT.swapcase() != _ROOT and os.path.exists(_ROOT.swapcase())

folding_only = pytest.mark.skipif(
    not FOLDS, reason="behaviour specific to case-folding hosts (macOS)")


def _layout(tmp_path):
    root = Path(os.path.realpath(tmp_path))
    header = root / "Shims" / "BFME2_Ascii" / "String_Base.h"
    header.parent.mkdir(parents=True)
    header.write_text("// header\n")
    return root, header


def test_lowercased_path_resolves_to_disk_spelling(tmp_path):
    build._CASEDIR_MEMO.clear()
    root, header = _layout(tmp_path)
    requested = str(header).lower()
    assert build._case_resolve(requested) == str(header)


def test_resolved_path_is_inside_its_search_root(tmp_path):
    # The inventory check compares with Path.is_relative_to, which is
    # case-sensitive on POSIX: the resolved spelling has to match the root's.
    build._CASEDIR_MEMO.clear()
    root, header = _layout(tmp_path)
    resolved = build._case_resolve(str(header).lower())
    assert Path(resolved).is_relative_to(root / "Shims" / "BFME2_Ascii")


def test_exact_and_missing_paths(tmp_path):
    build._CASEDIR_MEMO.clear()
    root, header = _layout(tmp_path)
    assert build._case_resolve(str(header)) == str(header)
    assert build._case_resolve(str(root / "Shims" / "missing.h")) is None


@folding_only
def test_file_added_after_a_cached_listing_still_resolves(tmp_path):
    build._CASEDIR_MEMO.clear()
    root, header = _layout(tmp_path)
    assert build._case_resolve(str(header).lower()) == str(header)
    added = header.parent / "Added_Later.h"
    added.write_text("// added\n")
    assert build._case_resolve(str(added).lower()) == str(added)


@folding_only
def test_dot_dot_components(tmp_path):
    build._CASEDIR_MEMO.clear()
    root, header = _layout(tmp_path)
    requested = str(root / "shims" / "bfme2_ascii" / ".." / "bfme2_ascii" / "string_base.h")
    resolved = build._case_resolve(requested)
    assert resolved is not None
    assert os.path.normpath(resolved) == str(header)


def test_non_folding_host_keeps_the_original_path(tmp_path, monkeypatch):
    # Linux and Windows hosts take the original code unchanged: a path that
    # exists as typed is returned as typed.
    build._CASEDIR_MEMO.clear()
    monkeypatch.setattr(build, "_FOLDS_CASE", False, raising=False)
    root, header = _layout(tmp_path)
    assert build._case_resolve(str(header)) == str(header)
    assert build._case_resolve(str(root / "Shims" / "missing.h")) is None
