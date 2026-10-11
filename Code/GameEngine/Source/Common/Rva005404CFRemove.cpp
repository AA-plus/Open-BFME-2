// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva005404CF@Rva0054034A@@QAEXH@Z @ 0x005404CF 72B
// The free-camera channel's guarded key removal, the 0x28-stride twin of
// the rowed 0x00541883 (Rva00541883Remove.cpp, same spelling): rejects
// non-positive keys, validates the hint through the pinned locator
// 0x0054034A, notifies the +0x00 listener list through rowed forEach
// 0x005402DC with the raw pmf constant (union-punned), erases the hinted
// element through the rowed BfmePod40 vector erase 0x005401B4 over a
// minimal view, then notifies again. Names are generated.
struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};


namespace _STL
{
	template <class _Tp>
	class allocator
	{
	};
	template <class _Tp, class _Alloc>
	class vector
	{
	public:
		_Tp *erase(_Tp *__pos);
	private:
		_Tp *_M_start;
		_Tp *_M_finish;
		_Tp *_M_end;
	};
}

class Rva005402DCListener
{
public:
	virtual void notify(void *, int);
};

class Rva005402DCList
{
public:
	void forEach(void (Rva005402DCListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005402DCListener **m_begin;
	Rva005402DCListener **m_end;
	Rva005402DCListener **m_capacity;
	unsigned int m_index;
};

union Rva005404CFPmf
{
	int i;
	void (Rva005402DCListener::*m)(void *, int);
};

class Rva0054034A
{
public:
	bool rva0054034A(int key);
	void rva005404CF(int key);
private:
	Rva005402DCList m_list00;
	BfmePod40 *m_begin10;
	BfmePod40 *m_end14;
	int m_pad18;
	int m_hint1C;
};

void Rva0054034A::rva005404CF(int key)
{
	if (key <= 0)
		return;
	if (!rva0054034A(key))
		return;
	Rva005404CFPmf before;
	before.i = 0x9CB27E;
	m_list00.forEach(before.m, this, key);
	((_STL::vector<BfmePod40, _STL::allocator<BfmePod40> > *)&m_begin10)->erase(&m_begin10[m_hint1C]);
	Rva005404CFPmf after;
	after.i = 0x9CB274;
	m_list00.forEach(after.m, this, key);
}
