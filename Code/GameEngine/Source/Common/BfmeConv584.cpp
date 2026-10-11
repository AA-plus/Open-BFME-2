// LINK: the second part is a vector<Rva0026F4F4Element>; its copy is the rowed
// vector operator= (0x0026F4F4).
struct Rva0026F4F4Element;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	vector &operator=(const vector &other);
};
}
typedef _STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > Rva0026F4F4Vector;

struct BfmePartCDF
{
	void bfmeCopyOneCDF(BfmePartCDF *other);
	unsigned char m_bfmeHead[0xc];
};

struct BfmeThingCDF
{
	BfmeThingCDF *bfmeGoCDF(BfmeThingCDF *other);
	unsigned char m_bfmeHead[4];
	BfmePartCDF m_bfmeA;
	BfmePartCDF m_bfmeB;
};

BfmeThingCDF *BfmeThingCDF::bfmeGoCDF(BfmeThingCDF *other)
{
	m_bfmeA.bfmeCopyOneCDF(&other->m_bfmeA);
	*(Rva0026F4F4Vector *)&m_bfmeB = *(const Rva0026F4F4Vector *)&other->m_bfmeB;
	return this;
}
