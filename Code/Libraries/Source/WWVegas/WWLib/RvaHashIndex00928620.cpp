// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport's hash_map index over the pair<int, int> table whose lookup and
// insertion bodies are already recovered at 0x00927800 and 0x00928590.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> Rva00928590Key;
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;

struct Rva00928590Hash
{
	UnsignedInt operator()( const Rva00928590Key &key ) const
	{
		return ( static_cast<UnsignedInt>( key.second ) << 16 )
			+ static_cast<UnsignedInt>( key.first );
	}
};

struct Rva00928590Eq
{
	bool operator()( const Rva00928590Key &left,
		const Rva00928590Key &right ) const
	{
		return left.first == right.first && left.second == right.second;
	}
};

typedef _STL::hash_map<Rva00928590Key, int, Rva00928590Hash,
	Rva00928590Eq,
	_STL::allocator<_STL::pair<const Rva00928590Key, int> > >
	Rva00928620Map;

template int &Rva00928620Map::operator[]( const Rva00928590Key & );
