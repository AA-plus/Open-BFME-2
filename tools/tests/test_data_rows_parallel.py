import threading
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows


def setup_rows(monkeypatch, rows, workers=3):
    monkeypatch.setattr(data_rows, '_tools', lambda: (
        SimpleNamespace(_pool_size=lambda: workers), SimpleNamespace(Image=lambda: object())))
    monkeypatch.setattr(data_rows, 'load', lambda: rows)
    monkeypatch.setattr(data_rows, 'Resolver', lambda every: object())


def test_sources_overlap_but_rows_and_diagnostics_keep_order(monkeypatch):
    rows = [{'source': source, 'name': name} for source, name in
            [('a.cpp', 'a1'), ('b.cpp', 'b1'), ('a.cpp', 'a2'), ('c.cpp', 'c1')]]
    setup_rows(monkeypatch, rows)
    barrier = threading.Barrier(3)
    guard = threading.Lock()
    active = set()
    checked = []

    def check(row, img, resolve, compile):
        assert compile is False
        with guard:
            assert row['source'] not in active
            active.add(row['source'])
        if row['name'] != 'a2':
            barrier.wait(timeout=5)
        with guard:
            active.remove(row['source'])
            checked.append(row['name'])
        return False, 'rejected ' + row['name']

    monkeypatch.setattr(data_rows, 'verify_row', check)
    logged = []
    with pytest.raises(SystemExit) as failure:
        data_rows.verify(compile=False, log=logged.append)
    assert failure.value.code == 1
    assert sorted(checked) == ['a1', 'a2', 'b1', 'c1']
    assert checked.index('a1') < checked.index('a2')
    assert logged == [f"    {r['name']} ({r['source']}): rejected {r['name']}" for r in rows] + [
        'Data rows: FAIL 4 of 4']


@pytest.mark.parametrize('compile,workers', [(True, 24), (False, 1)])
def test_serial_mode_keeps_call_order_and_compile_flag(monkeypatch, compile, workers):
    rows = [{'source': 'a.cpp', 'name': 'a'}, {'source': 'b.cpp', 'name': 'b'}]
    setup_rows(monkeypatch, rows, workers)
    checked = []

    def check(row, img, resolve, received):
        checked.append((row['name'], received))
        return True, 'valid'

    monkeypatch.setattr(data_rows, 'verify_row', check)
    assert data_rows.verify(compile=compile, log=lambda message: None) == 2
    assert checked == [('a', compile), ('b', compile)]


def test_parallel_worker_exception_fails_verification(monkeypatch):
    rows = [{'source': 'a.cpp', 'name': 'a'}, {'source': 'b.cpp', 'name': 'b'}]
    setup_rows(monkeypatch, rows)

    def check(row, *args):
        if row['name'] == 'b':
            raise OSError('probe failed')
        return True, 'valid'

    monkeypatch.setattr(data_rows, 'verify_row', check)
    with pytest.raises(OSError, match='probe failed'):
        data_rows.verify(compile=False, log=lambda message: None)


def test_source_filter_does_not_verify_other_providers(monkeypatch):
    rows = [{'source': 'a.cpp', 'name': 'a'}, {'source': 'b.cpp', 'name': 'b'}]
    setup_rows(monkeypatch, rows)
    checked = []

    def check(row, *args):
        checked.append(row['name'])
        return True, 'valid'

    monkeypatch.setattr(data_rows, 'verify_row', check)
    assert data_rows.verify(sources=['source:b.cpp'], compile=False, log=lambda message: None) == 1
    assert checked == ['b']
