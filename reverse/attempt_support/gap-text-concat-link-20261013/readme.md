# Gap text concat dependency repair

The link-repair queue and local preview identified a selected non-retail
AsciiString::concat(const char *) dependency in GapBodiesS3L.cpp. The
21-byte matched member at RVA 0x00419BB8 appends the text argument to its
existing one-pointer string at +8 when the flag at +4 is set. Retail's call
at 0x00419BC5 targets 0x00005629, independently decoded in retail-call.txt.
That target already has the matched StringBase<char>::concat(const char *)
provider in string_base.cpp. Bind this call through the existing canonical
StringBase view; no class identity or additional layout is inferred.
receipt-and-call.json confirms the emitted 21-byte extent and REL32 +14
bound to the real provider. No pin, alias, marker, header, flags or ledger
range changes are needed.

Reviewed BFME 1 donor repair 5f05cce4e52a5f69608af60cc2bfa2a8e78d9187
(direct StringBase comparison bindings, reported 36/36 gate), including
its Rva000D4360Owner.cpp member call. Its canonical-provider binding principle
applies; neither its compare body nor its addresses are imported. The
committed verified donor input remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
Official master was fetched at 61a7c39c3dd2b0e327fc71e28d22f37c02d9f2ce;
the foreign file:reference/open-bfme-1 claim prevents the overdue pointer
update here. The clean verified checkout and freshness stamp were retained.

Acceptance at checkout 85ce71a8bd4bdebfd8b1e9a308ec4141928b0046:

- Full byte gate on consumer and provider: 45/45 functions, seven literals,
  15 empty-string references and three imports; zero baseline/skips.
- Explicit consumer --prepare-current: strict reusable self-verification
  receipt and normal 8/8 byte gate. Source/object hashes and strict currency
  are recorded in receipt-and-call.json.
- Before/after local link previews use the same cb660e4d97 census index
  (2026-10-13 04:02). Exactly one selected-provider finding disappears;
  the three unresolved findings remain. The provider stays LINKS with
  1,185 bytes, the consumer stays blocked with 426 own matched bytes.
  Both previews return 1 because the consumer remains blocked.
- find_declared_unmatched.py passes before and after; check_csv.py and
  git diff --check pass.

This is a dependency improvement with zero new authored C++ bytes and
zero newly linked bytes in the legacy preview. Strict self-verification
does not establish closed-strict closure or an actual link.exe gain.
No census/status counters were changed, no per-row data-back ranking was
manufactured, and no maintainer-only runner was started.

Remaining unresolved names: InGameUI::rva0029FCD9, rva00343DD8 and
rva004E3BD8. These need separate provider/identity investigation.
