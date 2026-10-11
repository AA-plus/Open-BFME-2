// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// LINK: the counted object destroys through the rowed destructor of an STLport
// vector<BfmeE8>; the head words are the vector plus its owner, so the delete
// below binds that destructor.
struct BfmeE8;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	~vector();

	unsigned char m_bfmeHeadCF[0x10];
	int m_bfmeCountCF;
};
}
typedef _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > BfmeObjCF;

class BfmeRefCF
{
public:
	BfmeRefCF *bfmeAssignCF(const BfmeRefCF &other);

	BfmeObjCF *m_bfmePtrCF;
};

BfmeRefCF *BfmeRefCF::bfmeAssignCF(const BfmeRefCF &other)
{
	if (this != &other)
	{
		--m_bfmePtrCF->m_bfmeCountCF;

		if (m_bfmePtrCF->m_bfmeCountCF == 0)
			delete m_bfmePtrCF;

		m_bfmePtrCF = other.m_bfmePtrCF;
		m_bfmePtrCF->m_bfmeCountCF++;
	}

	return this;
}
