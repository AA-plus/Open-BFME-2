// ?rva005DE926@Rva005DE5B5@@QAEXXZ
// partial score=0.95 date=2026-10-13
// ?rva005DE926@Rva005DE5B5@@QAEXXZ
// partial score=0.97 date=2026-10-13
namespace _STL
{
template <> class vector<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >
{
public:
	typedef BfmeStringRecord005DDD40 *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

class Rva005DE5B5
{
public:
	void rva005DE926();
private:
	UnicodeString m_00;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > m_04;
	char m_10[4];
	unsigned char m_14;
};

// Retail 0x005DE926, 44 bytes: erases every element of the +0x04 vector,
// resizes it back to the count it held, and clears the +0x14 flag. The
// count is the inline pointer-difference size held across the erase call;
// the vector address stays put while the count is computed, as retail does.
void Rva005DE5B5::rva005DE926()
{
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > *vec = &m_04;
	unsigned int count = vec->size();
	_ReadWriteBarrier();
	vec->erase(vec->begin(), vec->end());
	((Rva005DE7D1Vector *)vec)->resize(count);
	m_14 = 0;
}
