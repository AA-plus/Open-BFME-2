// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /Gy
// stlport
//
// ?GetBlingIndex@CreateAHeroSubClass@CreateAHeroManager@@QAEHHABVAsciiString@@@Z
// @0x0021BD41 106B (WorldBuilder CreateAHeroManager::CreateAHeroSubClass::
// GetBlingIndex): looks the bling key up through the rowed map find 0x0021BC0D
// and returns the index of the first bling whose name (+8, rowed
// StringBase::compare) equals the given name, else -1.
//
// Evidence: retail walks the found node's vector (+0x14/+0x18) with the size
// computed begin-first (`end - begin`, begin kept in eax for the element push),
// and keeps the node in esi with no copy of `this`: the compiler knew the find
// leaves ecx alone. MSVC only knows that for an out-of-line callee defined
// earlier in the same TU, so the find body (identical to Rva0021BC0DFind.cpp)
// is defined here ahead of the caller; /Gy makes the duplicate a COMDAT.
#include <map>
#include <vector>
#include "ascii_string.h"

class CreateAHeroManager
{
public:
	struct CreateAHeroSubClass;
	void *GetBling(unsigned int index);
};

extern CreateAHeroManager *TheCreateAHeroManager;

struct MapNodeVec2
{
	char hdr[0x14];
	_STL::vector<unsigned int> m_vec;
};

struct CreateAHeroManager::CreateAHeroSubClass
{
	char pad[0x24];
	_STL::map<int, _STL::vector<unsigned int> > m_map;
	unsigned char rva0021BC0D(int key, void **out);
	int GetBlingIndex(int key, const AsciiString &name);
};

unsigned char CreateAHeroManager::CreateAHeroSubClass::rva0021BC0D(int key, void **out)
{
	_STL::map<int, _STL::vector<unsigned int> >::iterator it = m_map.find(key);
	*out = it._M_node;
	return it._M_node != m_map.end()._M_node;
}

int CreateAHeroManager::CreateAHeroSubClass::GetBlingIndex(int key, const AsciiString &name)
{
	void *node = 0;
	if (rva0021BC0D(key, &node))
	{
		MapNodeVec2 *n = (MapNodeVec2 *)node;
		for (unsigned int i = 0; i < (unsigned int)(n->m_vec.end() - n->m_vec.begin()); ++i) {
			void *elem = TheCreateAHeroManager->GetBling(n->m_vec[i]);
			if (elem && ((const StringBase<char> *)((const char *)elem + 8))->compare(*(const StringBase<char> *)&name) == 0)
				return (int)i;
		}
	}
	return -1;
}
