"""Path reuse must keep members distinct and refuse a remapped verifier input."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
from test_gate_exploits import Gate, TEXT, coff


def test_members_are_distinct_and_no_mapping_survives_a_pass():
    calls = []

    def mapped(row):
        calls.append(dict(row))
        return Path("objects") / build.ledger_member(row)

    first = {"source": "Code/library.lib", "name": "first", "notes": "member=a.obj"}
    second = dict(first, name="second", notes="member=b.obj")
    lookup = build.RowObjectPaths(mapped)
    for _ in range(5):
        assert lookup.get(first) == Path("objects/a.obj")
        assert lookup.get(second) == Path("objects/b.obj")
    assert len(calls) == 2
    lookup.check()
    assert len(calls) == 4
    another = build.RowObjectPaths(mapped)
    another.get(first)
    another.check()
    assert len(calls) == 6


def test_remapped_object_is_not_reported_green():
    paths = iter([Path("old.obj"), Path("new.obj")])
    lookup = build.RowObjectPaths(lambda _row: next(paths))
    lookup.get({"source": "Code/a.cpp", "notes": ""})
    with pytest.raises(SystemExit, match="object path changed"):
        lookup.check()


def test_byte_gate_refuses_mapping_change_after_exact_bytes(tmp_path, monkeypatch):
    gate = Gate(monkeypatch, tmp_path)
    gate.row("?body@@YAXXZ", 0x1000, 1)
    gate.memory[0x1000] = b"\xc3"
    gate.obj.write_bytes(coff([(".text", TEXT, b"\xc3", [])],
                              [("?body@@YAXXZ", 0, 1, 0x20, 2, 0)]))
    assert gate.gate()
    paths = iter([gate.obj, tmp_path / "different.obj"])
    monkeypatch.setattr(build, "row_object", lambda _row: next(paths))
    assert not gate.gate()


@pytest.mark.parametrize("name", ["verify_string_refs", "verify_float_refs",
                                  "verify_import_refs", "verify_dir32_consistency"])
def test_literal_and_data_gates_recheck_mapping_before_green(name, tmp_path, monkeypatch):
    class Spy:
        def __init__(self, getter):
            pass

        def get(self, row):
            raise AssertionError("empty rows should not read objects")

        def check(self):
            raise SystemExit("path mapping moved")

    image = tmp_path / "retail.dat"
    image.write_bytes(b"")
    monkeypatch.setattr(build, "EXE", image)
    monkeypatch.setattr(build, "pe_sections", lambda _data: [])
    import pe_imports
    monkeypatch.setattr(pe_imports, "read_imports", lambda _data: {})
    monkeypatch.setattr(build, "RowObjectPaths", Spy)
    with pytest.raises(SystemExit, match="path mapping moved"):
        getattr(build, name)([])
