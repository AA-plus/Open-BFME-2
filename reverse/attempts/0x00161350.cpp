// ?rva00161350CopyForward@Rva00161350@@YAPAUElem36@@PAU1@00@Z
// partial score=0.9 date=2026-10-12
// cl: /O2 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
struct Elem36Block16
{
	int m_words[4];
};

struct Elem36Tail
{
	Elem36Block16 m_block;
	int m_word14;
	int m_word18;
	int m_word1C;
};

struct Elem36
{
	int m_word00;
	Elem36Tail m_tail;
	bool m_flag20;

	Elem36(const Elem36 &other)
		: m_word00(other.m_word00), m_tail(other.m_tail), m_flag20(other.m_flag20)
	{
	}
	Elem36 &operator=(const Elem36 &other)
	{
		m_word00 = other.m_word00;
		m_tail.m_block.m_words[0] = other.m_tail.m_block.m_words[0];
		m_tail.m_block.m_words[1] = other.m_tail.m_block.m_words[1];
		m_tail.m_block.m_words[2] = other.m_tail.m_block.m_words[2];
		m_tail.m_block.m_words[3] = other.m_tail.m_block.m_words[3];
		m_tail.m_word14 = other.m_tail.m_word14;
		m_tail.m_word18 = other.m_tail.m_word18;
		m_tail.m_word1C = other.m_tail.m_word1C;
		m_flag20 = other.m_flag20;
		return *this;
	}
};

Elem36 *copyFwd(Elem36 *first, Elem36 *last, Elem36 *dest)
{
	unsigned chunks;
	unsigned n = (unsigned)(last - first);
	Elem36 *s = first;
	Elem36 *d = dest;
	if ((int)n >= 4)
	{
		chunks = (n - 4) / 4 + 1;
		n -= chunks * 4;
		do
		{
			d[0] = s[0];
			d[1] = s[1];
			d[2] = s[2];
			d[3] = s[3];
			s += 4;
			d += 4;
		} while (--chunks > 0);
	}
	while (n > 0)
	{
		*d = *s;
		++s;
		++d;
		--n;
	}
	return d;
}

Elem36 *copyBwd(Elem36 *first, Elem36 *last, Elem36 *destEnd)
{
	unsigned chunks;
	int n = last - first;
	Elem36 *s = last;
	Elem36 *d = destEnd;
	if (n >= 4)
	{
		chunks = ((unsigned)n - 4) / 4 + 1;
		int rem = n - (int)(chunks * 4);
		n = rem;
		do
		{
			s -= 4;
			d -= 4;
			d[0] = s[0];
			d[1] = s[1];
			d[2] = s[2];
			d[3] = s[3];
		} while (--chunks > 0);
	}
	if (n > 0)
	{
		do
		{
			--s;
			--d;
			*d = *s;
		} while (--n > 0);
	}
	return d;
}
