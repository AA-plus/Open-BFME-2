// ?rva001F8CC2@Rva001F8CC2@@QAEAAV1@ABV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@@Z
// partial score=0.9 date=2026-10-14
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001F8CC2@Rva001F8CC2@@QAEAAV1@ABV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@@Z,
// retail 0x001F8CC2, 174 bytes.
//
// Assignment counterpart of the vector constructor Rva001F8C5B (Rva001F8C5BCtor.cpp):
// build a temporary pointer vector holding the owned result of virtual slot 1 of
// every source element (reserve src.size, push_back each), swap it into this+0
// and let the temporary delete what it still owns (::delete of each element
// through the virtual destructor with flag 0, then the storage free) on the way
// out. Returns this (ret 4).
//
// Evidence: rowed Vector_base 0x00211E58, reserve 0x002B712E, push_back
// 0x004DFCB0, swap 0x00567ECD; the allocator temporary is passed as
// lea eax,[ebp+0xb] (see Rva003F3B28Resize.cpp: the base constructor is visible
// in the header).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "../../../../Libraries/Include/Lib/BfmeE16.h"

struct BfmeE12 { float x, y, z; };
// bfme link decl-only BfmeE16
namespace _STL {
template <> vector<BfmeE16, allocator<BfmeE16> >::~vector();
template <> void vector<BfmeE12, allocator<BfmeE12> >::swap(vector<BfmeE12, allocator<BfmeE12> > &);
}

class ModuleData
{
public:
	virtual ~ModuleData();
};

class Rva001F8CC2Iface
{
public:
	virtual void dummy0();
	virtual ModuleData *clone();
};

// Temporary pointer vector that owns what it holds.
class Rva001F8CC2Owned : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva001F8CC2Owned() : _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
	__forceinline ~Rva001F8CC2Owned() throw()
	{
		for (ModuleData **p = (ModuleData **)_M_start; p != (ModuleData **)_M_finish; ++p)
			::delete *p;
	}
};

class Rva001F8CC2
{
public:
	Rva001F8CC2 &rva001F8CC2(const _STL::vector<void *> &src);
private:
	_STL::vector<BfmeE12> m_vec;
};

Rva001F8CC2 &Rva001F8CC2::rva001F8CC2(const _STL::vector<void *> &src)
{
	Rva001F8CC2Owned tmp;
	((_STL::vector<const ModuleData *> &)tmp).reserve(src.size());
	for (void *const *it = (void *const *)src.begin(); it != (void *const *)src.end(); ++it) {
		Rva001F8CC2Iface *obj = (Rva001F8CC2Iface *)*it;
		const ModuleData *md = obj->clone();
		((_STL::vector<const ModuleData *> &)tmp).push_back(md);
	}
	((_STL::vector<BfmeE12> &)tmp).swap(m_vec);
	return *this;
}
