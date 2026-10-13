# Particle subsystem handle cleanups

Read the complete Rva00098690Destructor.cpp and ParticleSystemHandle_dtor.cpp.
The parent remains address-derived: its existing target evidence associates
shutdown 0x00098690 with two twelve-byte particle-system handles at +0x4C and
+0x58 and the subsystem base. No original subsystem class name is asserted.
The provider retains its documented BFME1 list-clear idiom and target-measured
ParticleSystem head/tail offsets +0x9C/+0xA0; this work adds no donor claims.

The full 85-byte destructor at 0x000986E7 and its complete native associative
exception graph verify EXACT. The graph owns two Ghidra-bounded cleanups:

* 0x00760411, 11 bytes, $L353: `8b4df083c14ce9a911abff`.
* 0x0076041C, 11 bytes, $L354: `8b4df083c158e99e11abff`.

Both load saved this at EBP-0x10, adjust respectively to +0x4C and +0x58,
and jump to the existing 0x002115C5 handle destructor. The owning source's
inline RvaSmartPtr12 destructor compiles to that entire eleven-byte body and
its relocation to the actual 0x0004CBC0 unlink routine. verify.py checks the
whole inline copy, the existing ledger owner's whole eleven-byte copy, and
the complete 55-byte unlink provider, in addition to the parent, native graph,
both full cleanups and every relocation. All three provider bodies have no
exception data on either side. No new alias or pin is needed: the existing
RvaSmartPtr12 gen-alias already describes this exact destructor twin.

Normal builds pass all three original owning rows and four provider rows.
The before-row identity audit has zero findings (identity-before.json).
No source, header, flag, pin, alias, global or marker is edited. The source's
real C++ member lifetimes emit these cleanups naturally. Native exception
ownership proves their relationship; adjacency does not establish it.
place_bodies finds zero further bodies or pins. The old local census
(2026-10-02, 6963cc017c) lacks this file; no new linking result is claimed.
Run normal builds of both source files before replaying verify.py.
