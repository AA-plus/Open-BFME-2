// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva000481AA@W3DDisplay@@UAE?AV?$StringBase@D@@ABV2@@Z, retail 0x000481AA (194 bytes, EH,
// RET 8), W3DDisplay vtable 0x007C3C80 slot 34. Returns the given name with a variant suffix
// ("L" for mode 0, "M" for mode 1, none for 2/3; the mode is +0x1774 of
// TheGameLODManager) when the rowed 0x0021F3E0 accepts that variant, else the name unchanged. The
// two return statements give the construct-on-return flag retail keeps in its frame.
#include <new>

template <typename T> class StringBase
{
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &src);
	void set(const T *str);
	void clear()
	{
		releaseBuffer();
	}
	void concat(const StringBase<T> &str);
	~StringBase() { releaseBuffer(); }
};


class GameLODManager
{
public:
	char m_pad[0x1774];
	int m_detailVariant;		// +0x1774
};
extern GameLODManager *TheGameLODManager;

struct BfmeR1025
{
	char *m_bfmeName;
};
char bfmeGo1025F(BfmeR1025 *p);

class W3DDisplay
{
public:
	virtual StringBase<char> rva000481AA(const StringBase<char> &name);
};

StringBase<char> W3DDisplay::rva000481AA(const StringBase<char> &name)
{
	StringBase<char> suffix;
	StringBase<char> full;
	switch (TheGameLODManager->m_detailVariant)
	{
	case 0:
		suffix.set("L");
		break;
	case 1:
		suffix.set("M");
		break;
	case 2:
	case 3:
		suffix.clear();
		break;
	default:
		break;
	}
	full.set(name);
	full.concat(suffix);
	if (bfmeGo1025F((BfmeR1025 *)&full))
		return full;
	return name;
}
