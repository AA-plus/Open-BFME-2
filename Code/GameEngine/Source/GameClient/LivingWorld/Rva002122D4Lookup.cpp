// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002122D4@Rva002122D4@@QAEHH@Z, retail 0x002122D4 (41 bytes).
// Evidence: direct REL32 target at 0x00212313 from Rva002122FD (the
// LivingWorldManager caller); map<int,int> at this+0x2B4 searched through the
// rowed _M_find 0x00388F63; key 0 or a miss gives 0, a hit gives the mapped
// value at node+0x14. Owner identity is address-derived.
// Codegen finding: every early-return and conditional-return spelling put the
// shared xor eax,eax at the end of the body; retail keeps it right after the
// first compare with the miss path jumping back to it. Only an int result
// assigned in an if/else (both arms), returned once, reproduces that layout.
#include <map>

// The find otherwise instantiates the less<int>::operator() COMDAT (one byte
// shape per TU flags); an explicit dllimport+forceinline specialization takes
// those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Rva002122D4
{
public:
	int rva002122D4(int key);

private:
	char m_pad[0x2B4];
	_STL::map<int, int> m_map;	// +0x2B4
};

int Rva002122D4::rva002122D4(int key)
{
	int result;
	if (key == 0)
		result = 0;
	else
	{
		_STL::map<int, int>::iterator it = m_map.find(key);
		if (it == m_map.end())
			result = 0;
		else
			result = (*it).second;
	}
	return result;
}
