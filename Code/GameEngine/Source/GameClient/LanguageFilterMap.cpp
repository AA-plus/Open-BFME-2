// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// The target word map is at LanguageFilter+0xC. Its 24-byte nodes contain
// the UnicodeString/bool pair at +0x10; filterLine calls _M_find at 0x3881F8.
// String copies and cleanup use the independently matched StringBase helpers.
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"


struct UnicodeStringLessThan
{
    bool operator()(UnicodeString a, UnicodeString b) const
    {
        return static_cast<const StringBase<unsigned short>&>(a).compareNoCase(
            static_cast<const StringBase<unsigned short>&>(b)) < 0;
    }
};

typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::_Rb_tree<UnicodeString, LanguageFilterValue,
    _STL::_Select1st<LanguageFilterValue>, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterTree;

template _STL::_Rb_tree_node<LanguageFilterValue>*
LanguageFilterTree::_M_find<UnicodeString>(const UnicodeString&) const;

template _STL::_Rb_tree_node<LanguageFilterValue>*
LanguageFilterTree::_M_lower_bound(const UnicodeString&) const;

template void LanguageFilterTree::_M_erase(_STL::_Rb_tree_node<LanguageFilterValue>*);
template void LanguageFilterTree::clear();

// BFME1 donor874e38488 UnicodeStringBoolTreeFind.cpp under BFME2 O1/G7
// served this public const find. Native387F00..387F14 calls the existing
// exact LanguageFilter _M_find387DD8 and returns its pointer as an iterator.
template LanguageFilterTree::const_iterator LanguageFilterTree::find<UnicodeString>(const UnicodeString&) const;
