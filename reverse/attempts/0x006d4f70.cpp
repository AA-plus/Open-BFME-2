// ??HEAStringC@@QBE?AV0@PBD@Z
// partial score=0.998 date=2026-10-13
#include <string.h>
#include <stdlib.h>
// ??HEAStringC@@QBE?AV0@PBD@Z
// partial score=0.98 date=2026-10-13
// ??HEAStringC@@QBE?AV0@PBD@Z
// partial score=0.98 date=2026-10-13
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// In-TU rebuild beside the landed 300B sibling overload: empty path now
// exact (inline char ctor + proven-zero-ebp substitution for the null root,
// discovered 2026-10-13); first memcpy also exact through the uint-ctor
// call. Remaining is a 6-line scheduling rotation at +0x90 (retail
// source-load, text-load, text-add, count-setup, source-add vs ours with
// the loads swapped and source-add early); source-first/text-first,
// +sizeof/+1 symmetric and asymmetric, and source+8-in-call spellings all
// keep the frame-load first. Pure emission-order coin. t=60 model=muse-spark
class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	static void FreeData(StringDataC *data);

	StringDataC *volatile m_pData;

	EAStringC(const EAStringC &other);
	EAStringC(unsigned int nSize);
	// Inline C-string constructor (same shape as rowed 0x006D4C80): roots a
	// null data pointer, then delegates the whole build to Assign. Visible
	// here so the empty-receiver path below inlines; on the size==0 path
	// cl substitutes the proven-zero size register for the null root.
	EAStringC(const char *s) : m_pData(0) { Assign(s); }
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	void Assign(const char *s);
	EAStringC operator+(const EAStringC &other) const;
	EAStringC operator+(const char *other) const;
};

EAStringC EAStringC::operator+(const EAStringC &other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = other.m_pData->m_uSize;
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	const char *source = (char *)m_pData + sizeof(StringDataC);
	char *text = (char *)result.m_pData + sizeof(StringDataC);
	memcpy(text, source, size);
	memcpy(text + size, (char *)other.m_pData + sizeof(StringDataC), otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}
// Retail 0x006D4F70..0x006D509D (301 bytes): the const char* overload of the
// concatenation above. Empty receiver returns a copy of the C string (rowed
// EAStringC(const char*) 0x006D4C80 through Assign 0x006D4BF0); empty C
// string returns a copy of the receiver; otherwise identical shape to the
// EAStringC overload (sized result, two intrinsic memcpys, terminator,
// SetSize, receiver hash reset).
EAStringC EAStringC::operator+(const char *other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	const char *source = (char *)m_pData + sizeof(StringDataC);
	char *text = (char *)(result.m_pData + 1);
	memcpy(text, source, size);
	memcpy(text + size, other, otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}
