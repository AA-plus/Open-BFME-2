# Narrow StringBase teardown provider repair, 2026-10-13

At BFME 2 base `80028c7373`, the local index measured at `d753dedd98`
(2026-10-12 22:16 UTC) contains exactly one definition of the public narrow
StringBase destructor: W3DDisplayRva000481AA's forwarding COMDAT, judged wrong.
It overrides existing alternatename bindings to the real releaseBuffer body.
The committed link status instead names `d9e9abdc70`; it supplied queue leads,
not this before/after measurement. No per-row data-back artifact was used.

## Target evidence and change

The ledger owns the complete 133-byte native worker at RVA `0x00036410` as
`StringBase<char>::releaseBuffer`, in StringBaseWideReleaseBuffer.cpp.
W3DDisplay's complete 194-byte variant-name selector calls that RVA twice,
and its existing 10-byte EH handler also remains exact. Suppress the extra
forwarding destructor with a declaration-only narrow specialization, matching
the existing teardown policy in the representative consumers. Keep their
already established linker aliases; add no alias, pin, class view, marker,
header change, compiler flag, row or extent.

The StringBase receiver and destructor spelling are the existing TU view;
the independent target facts are its two native call destinations and complete
byte match. No original source destructor identity or new target layout is
claimed. Relocation evidence also covers the four corresponding calls in the
three unchanged consumers. The current changed object references the destructor
but no longer defines it; existing aliases resolve it to the verified provider.

## Donor review and freshness

Retained clean verified BFME 1 input `cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Reviewed official donor repair `5fa9bfd662c427a198176b0b727c4c11d0965733`,
which removes a private string cleanup binding in favor of canonical string
release. The direct-provider principle applies, supported here by BFME 2's
native destinations and existing teardown declarations. No donor implementation
or ABI was imported. Earlier compare-provider repair `5f05cce4e52a` was also
reviewed; its compare implementation is inapplicable to teardown.

Official BFME 1 freshness fetch reached
`99bac2eef90bc03cb73aff3aa3b024912e3a2d69`. Another worker (`codex-a44d-root`)
holds `file:reference/open-bfme-1`, so preserve the committed checkout. The
previously recorded update blocker remains; no pointer change or freshness
success stamp was made. Comparative full verification is still pending.

## Acceptance

- Changed caller's ordinary byte gate: 2/2 rows exact, including the EH handler.
- Bounded `link_check.py --prepare-current --paths-from sources.txt`: 24/24 rows
  exact across five providers/consumers, four strings and five named imports,
  zero skipped or baselined references; all five self-strict receipts current.
- Local ordinary link preview checks the changed emitter, release provider and
  three unchanged consumers together: **5/5 LINKS**, before **1/5**;
  **940 -> 2,250 existing authored bytes (+1,310)**. Selection and COMDAT
  blockers disappear. This is a legacy census preview, not closed-strict
  closure or an actual link.exe result.
- Six direct teardown relocations independently target native RVA `0x00036410`.
- Converged-data check: five sources, eight addresses, zero second names or
  unjudged rows. Declared-definition check and `git diff --check` pass.
- Census/index/status were not rewritten; authored C++ byte growth is zero.

The old census identifies the same selected name in 95 units, 65 as sole
blocker, but this receipt claims only the five explicitly checked units and
+1,310 bytes. Broader gains need refreshed consumer evidence. No full link
cycle, census build/history, nightly or boot operation was started.
