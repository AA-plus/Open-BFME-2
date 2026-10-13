// ?copyFrom@Rva000A9851PairTable3@@QAEXPBURva000A9851Pair@@@Z
// partial score=0.85 date=2026-10-13
// cl: /O1 /Op /MD
struct Rva000A9851Pair
{
	float f;
	unsigned u;
};

class Rva000A9851PairTable3
{
public:
	void copyFrom(const Rva000A9851Pair *src);
	void copyFrom2(const Rva000A9851Pair *src);
private:
	Rva000A9851Pair m_pairs[3];
};

void Rva000A9851PairTable3::copyFrom(const Rva000A9851Pair *src)
{
	const Rva000A9851Pair *s = src;
	Rva000A9851Pair *du = m_pairs;
	Rva000A9851Pair *d = m_pairs;
	int n = 3;
	do
	{
		du->u = s->u;
		d->f = s->f;
		++s;
		++du;
		++d;
	} while (--n);
}

void Rva000A9851PairTable3::copyFrom2(const Rva000A9851Pair *src)
{
	const Rva000A9851Pair *s = src;
	Rva000A9851Pair *du = m_pairs;
	Rva000A9851Pair *d = m_pairs;
	int n = 2;
	do
	{
		du->u = s->u;
		d->f = s->f;
		++s;
		++du;
		++d;
	} while (--n);
}
