"""Indexed lookup preserves COFF definitions, local ambiguity and relocations."""
import os
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import build
from test_gate_exploits import coff, TEXT, RDATA


def write_object(tmp_path, sections, symbols, name='lookup.obj'):
    path = tmp_path / name
    path.write_bytes(coff(sections, symbols))
    return path


def test_undefined_and_aux_before_definition_keep_real_index(tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xe8\0\0\0\0\xc3', [(1, 4, 0x14)])], [
        ('entry', 0, 0, 0x20, 105, 1),
        ('entry', 0, 1, 0x20, 2, 1),
        ('callee', 0, 0, 0x20, 2, 0)])
    body, relocs, details = build.read_object_symbol_bytes(path, 'entry', detail=True, code_only=True)
    assert body == b'\xe8\0\0\0\0\xc3'
    assert relocs == [(1, 0x14, 'callee')]
    assert details['reloc_symbols'] == [4]
    assert details['symbols'][2]['name'] == 'entry'
    assert details['symbols'][3]['section'] == 0


def test_repeated_local_name_keeps_first_definition(tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xc3', []),
                                   ('.text', TEXT, b'\xcc', [])], [
        ('$L123', 0, 1, 0, 3, 0), ('$L123', 0, 2, 0, 3, 0)])
    assert build.read_object_symbol_bytes(path, '$L123', detail=True)[2]['section'] == 1
    assert build.read_object_symbol_bytes(path, '$L123')[0] == b'\xc3'


def test_first_data_definition_does_not_fall_through_to_code(tmp_path):
    path = write_object(tmp_path, [('.rdata', RDATA, b'\xc3', []),
                                   ('.text', TEXT, b'\xc3', [])], [
        ('entry', 0, 1, 0x20, 2, 0), ('entry', 0, 2, 0x20, 2, 0)])
    with pytest.raises(SystemExit, match='non-code COFF section'):
        build.read_object_symbol_bytes(path, 'entry', code_only=True)


def test_unique_anonymous_hash_fallback_remains(tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xc3', [])], [
        ('?entry@?A0x11111111@@YAXXZ', 0, 1, 0x20, 2, 0)])
    assert build.read_object_symbol_bytes(path, '?entry@?A0x22222222@@YAXXZ')[0] == b'\xc3'


def test_ambiguous_anonymous_hash_stays_refused(tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xc3', [])], [
        ('?entry@?A0x11111111@@YAXXZ', 0, 1, 0x20, 2, 0),
        ('?entry@?A0x33333333@@YAXXZ', 0, 1, 0x20, 2, 0)])
    with pytest.raises(ValueError, match='symbol not found'):
        build.read_object_symbol_bytes(path, '?entry@?A0x22222222@@YAXXZ')


@pytest.mark.parametrize('duplicate', [False, True])
def test_initializer_size_still_requires_unique_match(tmp_path, duplicate):
    sections = [('.text', TEXT, b'\xc3\xcc\xcc', [])]
    symbols = [('_$E1', 0, 1, 0x20, 2, 0)]
    if duplicate:
        symbols.append(('_$E2', 0, 1, 0x20, 2, 0))
    path = write_object(tmp_path, sections, symbols)
    if duplicate:
        with pytest.raises(ValueError, match='symbol not found'):
            build.read_object_symbol_bytes(path, '_$E3', 1)
    else:
        assert build.read_object_symbol_bytes(path, '_$E3', 1)[0] == b'\xc3\xcc\xcc'


def test_object_change_does_not_reuse_old_definition(tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xc3', [])], [('old', 0, 1, 0x20, 2, 0)])
    assert build.read_object_symbol_bytes(path, 'old')[0] == b'\xc3'
    before = path.stat()
    path.write_bytes(coff([('.text', TEXT, b'\x90\xc3', [])], [('new', 0, 1, 0x20, 2, 0)]))
    os.utime(path, ns=(before.st_atime_ns, before.st_mtime_ns+10_000_000))
    with pytest.raises(ValueError, match='symbol not found'):
        build.read_object_symbol_bytes(path, 'old')
    assert build.read_object_symbol_bytes(path, 'new')[0] == b'\x90\xc3'


def test_plain_symbol_sequence_fixture_is_compatible(monkeypatch, tmp_path):
    path = write_object(tmp_path, [('.text', TEXT, b'\xc3', [])], [('entry', 0, 1, 0x20, 2, 0)])
    stat = path.stat()
    data, sections, symbols = build._object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    monkeypatch.setattr(build, '_object_layout', lambda *args: (data, sections, list(symbols)))
    assert build.read_object_symbol_bytes(path, 'entry')[0] == b'\xc3'
