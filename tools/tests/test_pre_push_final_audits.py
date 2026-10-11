"""Complete independent final push audits overlap; either refusal stays fatal."""
import json
import os
import subprocess
from pathlib import Path

import pytest
import test_hook_fail_closed as hooks
from test_hook_argmax import _definition

ROOT = Path(__file__).resolve().parents[2]
HOOK = ROOT / '.githooks/pre-push'
STUB = '''import json, os, signal, sys, time
from pathlib import Path
name = Path(__file__).stem
other = 'data_check' if name == 'eh_verify' else 'eh_verify'
sources = [entry.decode('utf-8') for entry in sys.stdin.buffer.read().split(b'\\0') if entry] if name == 'eh_verify' else []
Path(name + '.started').write_text('started')
if os.environ.get('BARRIER'):
    deadline = time.monotonic() + 10
    while not Path(other + '.started').exists():
        if time.monotonic() > deadline:
            raise SystemExit('other audit never started')
        time.sleep(.01)
Path(name + '.json').write_text(json.dumps(dict(argv=sys.argv[1:], sources=sources)), encoding='utf-8')
print(name + ' diagnostic', flush=True)
if name == 'eh_verify' and os.environ.get('KILL_EH'):
    os.kill(os.getpid(), signal.SIGTERM)
Path(name + '.finished').write_text('finished')
raise SystemExit(int(os.environ.get(name.upper() + '_EXIT', '0')))
'''


def run(tmp_path, sources, *, count=None, missing=False, shell_prefix='', **extra):
    tools = tmp_path / 'tools'
    tools.mkdir()
    for tool in ('eh_verify', 'data_check'):
        (tools / (tool + '.py')).write_text(STUB, encoding='utf-8')
    listing = tmp_path / 'source list.txt'
    if not missing:
        listing.write_bytes(b''.join(source.encode('utf-8') + b'\0' for source in sources))
    harness = 'set -euo pipefail\nfail() { echo "PRE-PUSH FAILED: $*" >&2; exit 1; }\n'
    harness += _definition(HOOK, 'run_final_audits') + '\n' + shell_prefix
    harness += f'run_final_audits pushed base "source list.txt" "{len(sources) if count is None else count}"\n'
    return subprocess.run([hooks._bash(), '--noprofile', '--norc'], input=harness,
        text=True, encoding='utf-8', capture_output=True, cwd=tmp_path,
        env=dict(os.environ, **extra), timeout=30)


def test_complete_audits_overlap_and_preserve_scopes_and_output(tmp_path):
    sources = ['Code/space and quote\'.cpp', 'Code/semicolon;dollar$.c', 'Code/\u00e9.asm']
    done = run(tmp_path, sources, BARRIER='1')
    assert done.returncode == 0, done.stderr
    eh = json.loads((tmp_path / 'eh_verify.json').read_text())
    data = json.loads((tmp_path / 'data_check.json').read_text())
    assert eh == dict(argv=['--sources-from', '-'], sources=sources)
    assert data == dict(argv=['--converged', '--ref', 'pushed', '--converged-base', 'base', '--all'], sources=[])
    assert done.stdout.splitlines() == ['eh_verify diagnostic', 'data_check diagnostic']


@pytest.mark.parametrize('eh_code,data_code,reason', [(7, 0, 'exception data'),
    (0, 9, 'data identity'), (7, 9, 'exception data')])
def test_either_refusal_is_fatal_and_both_workers_are_joined(tmp_path, eh_code, data_code, reason):
    done = run(tmp_path, ['Code/A.cpp'], EH_VERIFY_EXIT=str(eh_code), DATA_CHECK_EXIT=str(data_code), BARRIER='1')
    assert done.returncode == 1 and reason in done.stderr
    assert (tmp_path / 'eh_verify.finished').exists()
    assert (tmp_path / 'data_check.finished').exists()
    assert 'eh_verify diagnostic' in done.stdout and 'data_check diagnostic' in done.stdout


def test_empty_scope_still_audits_all_data_without_spurious_eh(tmp_path):
    done = run(tmp_path, [])
    assert done.returncode == 0, done.stderr
    assert not (tmp_path / 'eh_verify.started').exists()
    assert (tmp_path / 'data_check.finished').exists()


def test_audit_process_termination_is_fatal_and_other_worker_is_joined(tmp_path):
    done = run(tmp_path, ['Code/A.cpp'], KILL_EH='1', BARRIER='1')
    assert done.returncode == 1 and 'exception data' in done.stderr
    assert (tmp_path / 'data_check.finished').exists()


def test_second_tempfile_failure_starts_no_worker(tmp_path):
    done = run(tmp_path, ['Code/A.cpp'], shell_prefix='mktemp() { if [ -f temp-made ]; then return 8; fi; touch temp-made; command mktemp; }\n')
    assert done.returncode == 1 and 'temporary data audit output' in done.stderr
    assert not (tmp_path / 'eh_verify.started').exists()
    assert not (tmp_path / 'data_check.started').exists()


@pytest.mark.parametrize('broken', ['missing', 'bad-count', 'wrong-count', 'overflow-count', 'tempfile', 'output'])
def test_orchestration_errors_never_publish(tmp_path, broken):
    done = run(tmp_path, ['Code/A.cpp'], missing=broken == 'missing',
        count={'bad-count': 'broken', 'wrong-count': 2, 'overflow-count': 2**80}.get(broken),
        shell_prefix={'tempfile': 'mktemp() { return 5; }\n', 'output': 'cat() { return 6; }\n'}.get(broken, ''))
    assert done.returncode == 1 and 'PRE-PUSH FAILED' in done.stderr
    if broken == 'output':
        assert (tmp_path / 'eh_verify.finished').exists()
        assert (tmp_path / 'data_check.finished').exists()
    else:
        assert not (tmp_path / 'eh_verify.started').exists()
        assert not (tmp_path / 'data_check.started').exists()
