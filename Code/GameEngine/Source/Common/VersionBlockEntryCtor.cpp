// cl: /EHsc
// stlport
//
// ??0VersionBlockEntry@@QAE@XZ at retail 0x00427E88 (49B).
// Default-constructs the 0x18-byte version record with key string at +0
// and value string at +0xC through the rowed narrow-string default ctor
// at 0x00007850. Single EH state from the second member. Callers construct
// the temp entry before assigning key/value and pushing it into the record
// vector: parse at 0x00428A8C and 0x00428B27 path at 0x00428B6D. Layout
// matches the rowed dtor at 0x00238580 freeing [esi] then [esi+0xC].
#include <string>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

struct VersionBlockEntry
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	VersionBlockEntry();
};

VersionBlockEntry::VersionBlockEntry() {}
