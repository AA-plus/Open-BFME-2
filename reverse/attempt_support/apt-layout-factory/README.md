# Apt layout allocation factory

Retail `0x002223FE..0x00222435` is a complete 55-byte function ending in
`RET 4`. Debug counterpart `0x00B93C20` allocates `0x2C` bytes, forwards
its sole argument to `AptWindowLayout::AptWindowLayout`, and returns the
constructed pointer. The debug function's original name is unknown; the
factory retains an address-derived name and the measured stdcall ABI.

The constructor at `0x0040FDD1` became a verified 169-byte provider in upstream
`61c21cdfe2`, resolving the recorded dependency. The existing layout init
callback at `0x0040FB9C` and the constructor establish the class extent and
window/initialized fields. The factory is ordinary `new AptWindowLayout(info)`
in the existing `AptWindowLayout.cpp` home; it adds no pin, compiler setting,
global, assembly, or private helper body.

The ordinary byte gate verifies both home rows (221 + 55 bytes). The factory's
compiler-generated EH graph and cleanup target are exact. Frozen-source and
data checks pass. Rescanning the home and constructor units finds no additional
bodies or pins. Rebuilding both units after moving the trial factory removes
the stale constructor object's duplicate definition; the final scoped identity
check reports two rows and zero new findings (`identity-final.txt`).

The available local link index is from `7bcd61f5c1` and predates both layout
units, so `link_check.py` cannot preview them. The latest committed census
already reports the init home linking. Inspection of the current object shows
the factory adds only the now-rowed constructor, ordinary operator new/delete,
and compiler EH runtime references. No new whole-repository census was run.
