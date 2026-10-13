// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// STLport 4.5.3 src/time_facets.cpp -- the locale-driven half of the
// _Time_Info initializer plus the date-order probe.  Both bodies come from the
// BFME 1 donor reference/open-bfme-1/game/stlport/X4TimeFacets.cpp, which
// lotrbfme.exe and game.dat keep byte-identical once relocation slots are set
// aside (tools/bfme1_sweep.py: ?_Init_timeinfo 0x00847050 -> 0x000193A0 686B,
// ?__get_date_order 0x00845C10 -> 0x00018500 198B).
//
// The donor calls its locale accessors through the Rva* probe names the BFME 1
// sweep invented for that tree.  game.dat names the same addresses from this
// repo's own recovered TUs, so each call site here uses the name that already
// owns the address:
//
//   donor Rva0084DE20 -> ?Rva000210A0TableSlot@@YAPAXPAUT2TableOwner6C@@H@Z
//   donor Rva0084DE10 -> ?Rva00021090TableSlot@@YAPAXPAUT2TableOwner3C@@H@Z
//   donor Rva0084DE00 -> ?Rva00021080TableSlot@@YAPAXPAUT2TableOwner0C@@H@Z
//   donor t2_table_slot -> ?t2_table_slot@@YAPAXPAUT2TableOwner@@H@Z
// The four table accessors keep the donor's call order, which is also the
// destination-offset order the retail loops walk: dayname[0..6] from the
// generic accessor, dayname[7..13] from 0x000210A0, monthname[0..11] from
// 0x00021090 and monthname[12..23] from 0x00021080.  Only one identity may own
// an address, so none of them is re-pinned under its donor name.
//
// The remaining four accessors are the locale-buffer getters recovered in
// stlport_LocaleCodePageQueries.c: _Rva0084EED0 (0x00022060), _Rva0084EF00
// (0x00022090), _Rva0084ECA0 (0x00021E30, the donor's __Locale_d_fmt) and
// _Rva0084ECE0 (0x00021E70).  Three more addresses have no ledger identity yet
// and are reached only from this TU, so they carry address-derived pins
// (reverse/symbols.csv): _Rva0084ED20Tail 0x00021EB0, _Rva008504C0 0x00023650
// and _Rva00850560 0x000236F0.  Their names keep the BFME 1 donor's own
// symbols.csv spellings.
//
// The string copies stay visible but out of line, exactly as in
// stlport_timeinfo.cpp: MSVC's side-effect information lets the dead incoming
// parameter slot carry the hidden return object and the empty dispatch tag.
// The first (default-table) initializer in that other TU and the seven default
// names and format literals it copies are NOT repeated here.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
#include <locale>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> char * _STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> void basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >::reserve(unsigned int); }
// bfme link decl-only end
// bfme link decl-only begin
namespace _STL { template <> char * _STLP_alloc_proxy<char *, char, allocator<char> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1, 0>::allocate(unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

// index-and-load accessors over a pointer table in the owner object; defined
// in Code/GameEngine/Source/Common/T2IndexedArrayAccessors.cpp.
struct T2TableOwner;
struct T2TableOwner0C;
struct T2TableOwner3C;
struct T2TableOwner6C;
void *t2_table_slot(T2TableOwner *, int);
void *Rva00021080TableSlot(T2TableOwner0C *, int);
void *Rva00021090TableSlot(T2TableOwner3C *, int);
void *Rva000210A0TableSlot(T2TableOwner6C *, int);

// locale-buffer getters; defined in stlport_LocaleCodePageQueries.c.
extern "C" {
char *Rva0084EED0(_Locale_time *);
char *Rva0084EF00(_Locale_time *);
char *Rva0084ED20Tail(_Locale_time *);
char *Rva0084ECA0(_Locale_time *);
char *Rva008504C0(_Locale_time *);
char *Rva0084ECE0(_Locale_time *);
char *Rva00850560(_Locale_time *);
}

namespace _STL {

typedef back_insert_iterator<string> _TimeOut;
typedef char _TimeInfoStorage[(sizeof(_Time_Info) == 540) ? 1 : -1];

template<> inline __declspec(noinline) _TimeOut
__copy<const char*, _TimeOut, int>(const char* first, const char* last,
                                 _TimeOut result,
                                 const random_access_iterator_tag&, int*) {
  for (int count = last - first; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}

// The function copy_cstring is used to initialize a string with a C-style
// string.  Called only by the two _Init_timeinfo overloads, so its name does
// not require leading underscores.
static inline void copy_cstring(const char * s, string& v) {
  copy(s, s + strlen(s), back_insert_iterator<string >(v));
}

void _STLP_CALL _Init_timeinfo(_Time_Info& table, _Locale_time * time) {
  int i;
  for (i = 0; i < 7; ++i)
    copy_cstring((const char *)::t2_table_slot(
                     (T2TableOwner *)time, i),
                 table._M_dayname[i]);
  for (i = 0; i < 7; ++i)
    copy_cstring((const char *)::Rva000210A0TableSlot(
                     (T2TableOwner6C *)time, i),
                 table._M_dayname[i+7]);
  for (i = 0; i < 12; ++i)
    copy_cstring((const char *)::Rva00021090TableSlot(
                     (T2TableOwner3C *)time, i),
                 table._M_monthname[i]);
  for (i = 0; i < 12; ++i)
    copy_cstring((const char *)::Rva00021080TableSlot(
                     (T2TableOwner0C *)time, i),
                 table._M_monthname[i+12]);
  copy_cstring(::Rva0084EED0(time),
               table._M_am_pm[0]);
  copy_cstring(::Rva0084EF00(time),
               table._M_am_pm[1]);
  copy_cstring(::Rva0084ED20Tail(time), table._M_time_format);
  copy_cstring(::Rva0084ECA0(time), table._M_date_format);
  copy_cstring(::Rva008504C0(time), table._M_date_time_format);
  copy_cstring(::Rva0084ECE0(time), table._M_long_date_format);
  copy_cstring(::Rva00850560(time), table._M_long_date_time_format);
}

time_base::dateorder _STLP_CALL
__get_date_order(_Locale_time* time)
{
  const char * fmt = ::Rva0084ECA0(time);
  char first, second, third;

  while (*fmt != 0 && *fmt != '%') ++fmt;
  if (*fmt == 0)
    return time_base::no_order;
  first = *++fmt;
  while (*fmt != 0 && *fmt != '%') ++fmt;
  if (*fmt == 0)
    return time_base::no_order;
  second = *++fmt;
  while (*fmt != 0 && *fmt != '%') ++fmt;
  if (*fmt == 0)
    return time_base::no_order;
  third = *++fmt;

  switch (first) {
    case 'd':
      return (second == 'm' && third == 'y') ? time_base::dmy
                                             : time_base::no_order;
    case 'm':
      return (second == 'd' && third == 'y') ? time_base::mdy
                                             : time_base::no_order;
    case 'y':
      switch (second) {
        case 'd':
          return third == 'm' ? time_base::ydm : time_base::no_order;
        case 'm':
          return third == 'd' ? time_base::ymd : time_base::no_order;
        default:
          return time_base::no_order;
      }
    default:
      return time_base::no_order;
  }
}

}
