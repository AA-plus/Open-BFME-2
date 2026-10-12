// ?rva006D5160@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.98 date=2026-10-13
// ?rva006D5160@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.98 date=2026-10-13
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// In-TU rebuild beside the landed sibling overload: everything exact
// through both memcpys, SetSize and the copy call; remaining is pure
// register coloring at the tail (retail hidden=esi/m_pData=edi/&result=eax
// vs ours hidden=esi/m_pData=eax/&result=ecx, plus the post-copy reload,
// +4B). Named temp, pointer spelling and asymmetric forms all recolor
// identically. Caller 0x6FF980 (unrowed Apt worker) supports the free
// left-C-string concatenation identity. t=30 model=muse-spark
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

	StringDataC *m_pData;

	EAStringC(const EAStringC &other);
	EAStringC(unsigned int nSize);
	EAStringC(const char *s) : m_pData(0) { Assign(s); }
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	void Assign(const char *s);
	EAStringC operator+(const EAStringC &other) const;
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
// Retail 0x006D5160..0x006D5292 (306 bytes): free concatenation with a C
// string on the left. Empty right side returns the C string (inline char
// constructor above, same proven-zero substitution as the member overload);
// empty left side returns a copy of the right string; otherwise a sized
// result takes the left text then the right text, terminator, SetSize, and
// the result hash reset. Address-derived name; original identity unproven.
EAStringC rva006D5160(const char *left, const EAStringC &right)
{
	unsigned int size = right.m_pData->m_uSize;
	if (size == 0)
		return EAStringC(left);
	unsigned int otherSize = strlen(left);
	if (otherSize == 0)
		return right;
	unsigned int total = otherSize + size;
	EAStringC result(total);
	char *text = (char *)result.m_pData + sizeof(EAStringC::StringDataC);
	memcpy(text, left, otherSize);
	memcpy(text + otherSize, (char *)right.m_pData + sizeof(EAStringC::StringDataC), size);
	text[otherSize + size] = 0;
	EAStringC *presult = &result;
	presult->SetSize(total);
	presult->m_pData->m_uHash = 0;
	return *presult;
}
