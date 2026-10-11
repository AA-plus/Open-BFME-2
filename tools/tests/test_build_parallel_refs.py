"""Complete reference gates may run together, but failures cannot disappear."""
import concurrent.futures
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import build


@pytest.mark.parametrize('code', [1, 7, 'unverifiable input'])
def test_worker_preserves_output_and_system_exit(monkeypatch, capsys, code):
    def check(rows):
        assert rows == [{'source': 'Code/example.cpp'}]
        print('complete check refused')
        raise SystemExit(code)
    monkeypatch.setattr(build, 'verify_float_refs', check)
    result = build._reference_check_worker('float-refs', [{'source': 'Code/example.cpp'}])
    assert result == ('complete check refused\n', True, code)
    with pytest.raises(SystemExit) as exc:
        build._report_reference_result(result)
    assert exc.value.code == code
    assert capsys.readouterr().out == 'complete check refused\n'


def test_worker_does_not_turn_internal_error_into_success(monkeypatch):
    def broken(rows):
        raise ValueError('corrupt object reader')
    monkeypatch.setattr(build, 'verify_import_refs', broken)
    with pytest.raises(ValueError, match='corrupt object reader'):
        build._reference_check_worker('import-refs', [])


def test_every_worker_receives_entire_cross_source_scope(monkeypatch):
    rows = [{'source': 'Code/a.cpp'}, {'source': 'Code/b.cpp'}]
    submitted = []
    class Pool:
        def __init__(self, workers):
            assert workers == 4
        def __enter__(self):
            return self
        def __exit__(self, *args):
            pass
        def submit(self, fn, label, scope):
            assert scope is rows
            assert fn is build._reference_check_worker
            submitted.append(label)
            future = concurrent.futures.Future()
            future.set_result((label+'\n', False, None))
            return future
    monkeypatch.setattr(build.concurrent.futures, 'ProcessPoolExecutor', Pool)
    results = build._parallel_reference_checks(rows, 4)
    assert submitted == list(build._REFERENCE_GATES)
    assert results == [(label+'\n', False, None) for label in build._REFERENCE_GATES]


def test_worker_transport_error_is_fatal_after_all_checks_dispatched(monkeypatch):
    submitted = []
    class Pool:
        def __init__(self, workers):
            pass
        def __enter__(self):
            return self
        def __exit__(self, *args):
            pass
        def submit(self, fn, label, scope):
            submitted.append(label)
            future = concurrent.futures.Future()
            if label == 'float-refs':
                future.set_exception(RuntimeError('worker died'))
            else:
                future.set_result(('', False, None))
            return future
    monkeypatch.setattr(build.concurrent.futures, 'ProcessPoolExecutor', Pool)
    with pytest.raises(RuntimeError, match='worker died'):
        build._parallel_reference_checks([], 4)
    assert submitted == list(build._REFERENCE_GATES)


@pytest.mark.parametrize('bad_gate', range(4))
def test_full_gate_reports_each_parallel_refusal_and_runs_later_checks(monkeypatch, capsys, bad_gate):
    import pin_consistency
    import check_module_registry
    import data_rows
    calls = []
    monkeypatch.setattr(build, 'ensure_case_shims', lambda: None)
    monkeypatch.setattr(build, 'ensure_reference_current', lambda: None)
    monkeypatch.setattr(build, 'verify_baseline', lambda: None)
    monkeypatch.setattr(build, 'verify_functions', lambda: [])
    rows = [{'name': 'f', 'source': 'Code/example.cpp'}]*1024
    monkeypatch.setattr(build, 'load_function_rows', lambda: rows)
    monkeypatch.setattr(build, '_pool_size', lambda: 4)
    def parallel(scope, workers):
        assert scope is rows and workers == 4
        return [(label+'\n', i == bad_gate, 1 if i == bad_gate else None)
                for i, label in enumerate(build._REFERENCE_GATES)]
    monkeypatch.setattr(build, '_parallel_reference_checks', parallel)
    monkeypatch.setattr(pin_consistency, 'verify', lambda: calls.append('pins'))
    monkeypatch.setattr(check_module_registry, 'verify', lambda: calls.append('modules'))
    monkeypatch.setattr(build, 'verify_source_claims', lambda: calls.append('source claims'))
    monkeypatch.setattr(data_rows, 'verify', lambda: calls.append('data'))
    monkeypatch.setattr(build, 'verify_noop_patch', lambda patches: calls.append('no-op'))
    with pytest.raises(SystemExit) as exc:
        build.main()
    assert exc.value.code == 1
    assert calls == ['pins', 'modules', 'source claims', 'data', 'no-op']
    output = capsys.readouterr().out
    assert all(label in output for label in build._REFERENCE_GATES)
    assert 'FULL GATE: FAIL' in output
    assert '1 red: '+build._REFERENCE_GATES[bad_gate] in output


def test_small_full_gate_retains_serial_checks(monkeypatch):
    import pin_consistency
    import check_module_registry
    import data_rows
    calls = []
    monkeypatch.setattr(build, 'ensure_case_shims', lambda: None)
    monkeypatch.setattr(build, 'ensure_reference_current', lambda: None)
    monkeypatch.setattr(build, 'verify_baseline', lambda: None)
    monkeypatch.setattr(build, 'verify_functions', lambda: [])
    monkeypatch.setattr(build, 'load_function_rows', lambda: [])
    monkeypatch.setattr(build, '_pool_size', lambda: 4)
    for label, name in zip(build._REFERENCE_GATES,
        ('verify_string_refs', 'verify_float_refs', 'verify_import_refs', 'verify_dir32_consistency')):
        monkeypatch.setattr(build, name, lambda rows, label=label: calls.append(label))
    monkeypatch.setattr(pin_consistency, 'verify', lambda: None)
    monkeypatch.setattr(check_module_registry, 'verify', lambda: None)
    monkeypatch.setattr(build, 'verify_source_claims', lambda: None)
    monkeypatch.setattr(data_rows, 'verify', lambda: None)
    monkeypatch.setattr(build, 'verify_noop_patch', lambda patches: None)
    monkeypatch.setattr(build, '_parallel_reference_checks', lambda *args: pytest.fail('small scope starts no pool'))
    build.main()
    assert calls == list(build._REFERENCE_GATES)
