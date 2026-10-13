// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPA_N@Z
// partial score=0.88 date=2026-10-13
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPA_N@Z
// partial score=0.95 date=2026-10-13
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPA_N@Z
// partial score=0.97 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z, retail 0x00218468,
// 278 bytes. FontLibrary font-substitution adjustment: look the name up in the
// substitution tree at this+0x20, and when a non-empty substitution list is
// found, replace the name/size/style with the neighbouring record's values,
// interpolating the size when the request falls between two records.
//
// BFME1 donor game/GameEngine/Source/GameClient/GUI/FontLibraryBFMEAdjustFont.cpp
// (Rva00476B00FontLibrary::adjustFont, retail 0x00476B00, 260 bytes) supplies
// the whole shape: tree find, empty-list early-out, __upper_bound over the
// 16-byte records, interpolating vs flat branch, flag bits 1/2 to style.
// BFME2 deltas (all retail-measured): tree at this+0x20 (not +0x1C); the int
// key comes from the float via cvttss2si (/arch:SSE, no __ftol2 call); both
// name assignments go through the direct StringBase::set worker at 0x000366F0
// (no out-of-line operator=); the flat branch takes the if/else form
// (previous = last - 1 vs previous = first) rather than the donor's
// unconditional-assign shape. Original method name unknown: honest
// address-derived name. Callees Gen00473A40 at 0x0021764D and the
// AsciiString-keyed _M_find worker at 0x001F8437 are rowed.
#include <map>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL
{
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits> &a,
			      const _Rb_tree_iterator<T, RightTraits> &b)
{
	return a._M_node != b._M_node;
}
}

struct Rva004779C0Vector
{
	char *m_first;
	char *m_last;
	char *m_end;
};

struct Rva00475680Node
{
	int m_color;
	Rva00475680Node *m_parent;
	Rva00475680Node *m_left;
	Rva00475680Node *m_right;
	AsciiString m_key;
	Rva004779C0Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *find(const AsciiString &key) const
	{
		return reinterpret_cast<Rva00475680Node *>(
			reinterpret_cast<const _STL::map<AsciiString, AsciiString> *>(this)
				->find(key)
				._M_node);
	}

	Rva00475680Node *m_header;
};

struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	AsciiString m_name;
};

// The comparator carries one byte retail zeroes with stosb before pushing the
// whole dword to the by-value __upper_bound parameter; an empty functor
// elides that store and the body comes out short.
struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;

	unsigned char m_pad0x00;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first, Gen00473A40Elem *last,
	const int &value, Gen00473A40Less, int *);

class FontLibrary
{
public:
	void rva00218468(AsciiString *name, float *size, bool *style);

	// Nothing before the tree is read here; the landed sibling
	// FontLibraryFontList.cpp spells the real prefix (font list at +0x0C,
	// count at +0x10, table map at +0x14), so this stays a pad.
	char m_pad0x00[0x20];
	Rva00475680Tree m_fontSubstitution;
};

// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
void FontLibrary::rva00218468(AsciiString *name, float *size, bool *style)
{
	Rva00475680Tree *tree = &m_fontSubstitution;
	Rva00475680Node *node = tree->find(*name);
	if (node == tree->m_header)
		return;

	Rva004779C0Vector *list = node->m_value;
	if (list == 0)
		return;

	Gen00473A40Elem *first = (Gen00473A40Elem *)list->m_first;
	Gen00473A40Elem *last = (Gen00473A40Elem *)list->m_last;
	if ((((char *)last - (char *)first) & ~0x0f) == 0)
		return;

	float *sizePtr;
	// Retail reuses the dead size-argument slot [ebp+0xc] for the converted
	// key: spilling the pointer first, then converting through the spill and
	// storing the key over the argument word forces that exact coloring.
	sizePtr = size;
	*(int *)&size = (int)*sizePtr;

	Gen00473A40Elem *previous;
	int flags;
	Gen00473A40Elem *next =
		Gen00473A40(first, last, *(const int *)&size, Gen00473A40Less(), 0);

	if (next != last && next != first)
	{
		previous = next - 1;
		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;

		flags = previous->m_flags;
		*sizePtr = (float)previous->m_outputSize +
			(*sizePtr - (float)previous->m_inputSize) *
				((float)next->m_outputSize -
					(float)previous->m_outputSize) /
				((float)next->m_inputSize -
					(float)previous->m_inputSize);
	}
	else
	{
		if (next == last)
			previous = last - 1;
		else
			previous = first;

		if (previous->m_name.getLength() != 0)
			((StringBase<char> *)name)
				->set(*(const StringBase<char> *)&previous->m_name);
		flags = previous->m_flags;
		*sizePtr = (float)previous->m_outputSize;
	}

	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
