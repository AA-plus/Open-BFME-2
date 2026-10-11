"""Retail EH ownership must survive removal of generated handler ledger rows."""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eh_verify
import gen_small


BASE = 0x400000


@pytest.fixture
def retail(monkeypatch):
    data = bytearray(0x3000)
    entries = []
    rows = []

    def put(rva, blob):
        data[rva:rva + len(blob)] = blob

    def frame(parent=0x1000, stub=0x1700, info=0x2000,
              unwind=0x2100, target=0x1500, magic=0x19930522):
        put(parent, b'\x6a\xff\x68' + struct.pack('<I', BASE + stub))
        put(stub, b'\xb8' + struct.pack('<I', BASE + info) + b'\xe9\0\0\0\0')
        put(info, struct.pack('<IIIIIIII', magic, 1, BASE + unwind, 0, 0, 0, 0, 0))
        put(unwind, struct.pack('<II', 0xffffffff, BASE + target))
        entries.append((parent, 64, 'parent'))

    image = eh_verify.Image.__new__(eh_verify.Image)
    image.base = BASE
    image.size = len(data)
    # Preserve the real frame parser; only image loading is replaced.
    image.bytes = data
    monkeypatch.setattr(eh_verify, 'Image', lambda: image)
    monkeypatch.setattr(gen_small, 'image_base', lambda: BASE)
    monkeypatch.setattr(gen_small.B, 'exe_image', lambda: (
        bytes(data), [{'name': '.text', 'rva': 0x1000, 'size': 0x800}]))
    monkeypatch.setattr(gen_small.B, 'read_target_bytes',
                        lambda rva, size: bytes(data[rva:rva + size]))
    monkeypatch.setattr(gen_small.B, 'load_function_rows', lambda: rows)
    return frame, put, entries, rows


def test_parent_without_generated_handler_row(retail):
    frame, _, entries, rows = retail
    frame()
    # The real parent can also come solely from the ledger boundary.
    rows.append({'target_rva': '0x1000', 'target_size': '64', 'notes': 'real C++ parent'})
    ownership, counts = gen_small.funcinfo_ownership([])
    assert ownership == {0x1500: 0x1000}
    assert counts['stubs'] == 1


def test_shared_handler_has_no_unique_parent(retail):
    frame, _, entries, _ = retail
    frame()
    frame(parent=0x1100)
    ownership, counts = gen_small.funcinfo_ownership(entries)
    assert ownership == {}
    assert counts['stub-owner-ambiguous'] == 1


def test_folded_cleanup_has_no_unique_parent(retail):
    frame, _, entries, _ = retail
    frame()
    frame(parent=0x1100, stub=0x1710, info=0x2020, unwind=0x2110)
    ownership, counts = gen_small.funcinfo_ownership(entries)
    assert ownership == {}
    assert counts['funclet-folded-across-owners'] == 1


def test_late_handler_looking_push_is_not_a_frame(retail):
    frame, put, entries, _ = retail
    frame()
    put(0x1100 + 20, b'\x6a\xff\x68' + struct.pack('<I', BASE + 0x1700))
    entries.append((0x1100, 64, 'unrelated'))
    ownership, _ = gen_small.funcinfo_ownership(entries)
    assert ownership == {0x1500: 0x1000}


def test_invalid_funcinfo_is_not_an_owner(retail):
    frame, _, entries, _ = retail
    frame(magic=0)
    ownership, counts = gen_small.funcinfo_ownership(entries)
    assert ownership == {}
    assert counts['stubs'] == 0


def test_cleanup_outside_code_is_not_admitted(retail):
    frame, _, entries, _ = retail
    frame(target=0x2200)
    ownership, _ = gen_small.funcinfo_ownership(entries)
    assert ownership == {}
