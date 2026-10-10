// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E5A78@@QAE@XZ @0x004E5A78 (118B)
// Destructor over vector<void*>: deletes each element via Rva004E5821 cleanup
// plus operator delete, then erases the range; storage freed by vector dtor.
// Evidence: unlock lane, callees rowed, callers 0x004E5AEE deleting dtor and
// 0x004E5CB0 deleter both call here.
#include <vector>

// vector<void*> members otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

class Rva004E5821
{
public:
	void rva004E5821();
};

class Rva004E5A78
{
public:
	_STL::vector<void *> m_vec;
	~Rva004E5A78();
};

Rva004E5A78::~Rva004E5A78()
{
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		Rva004E5821 *p = (Rva004E5821 *)m_vec[i];
		if (p != 0) {
			p->rva004E5821();
			::operator delete(p);
		}
	}
	m_vec.erase(m_vec.begin(), m_vec.end());
}
