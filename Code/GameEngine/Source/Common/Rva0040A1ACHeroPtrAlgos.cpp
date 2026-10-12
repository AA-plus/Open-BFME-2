// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 pointer-range algorithms over the CreateAHeroData* vector
// (see Rva0040A3F9Find.cpp): for_each releasing every element through
// TheHeroManager (rowed 0x21929D), and the 4x unrolled random-access
// __find_if with the two by-value comparison functors rowed at 0x40A16E and
// 0x40A187 (one resp. two dwords of state). Evidence: target bytes of
// 0x40A1AC/0x40A1D7/0x40A283; functor spelling is donor inference.
#include <algorithm>
#include <vector>

class CreateAHeroData;

class Rva00219251
{
public:
	void rva0021929D(CreateAHeroData **data);
};

// 0x009FE344 under its data-ledger primary name (defined in CreateAHero.cpp).
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva0040A16E
{
public:
	bool rva0040A16E(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A16E(p); }
private:
	int m_val0;
};

class Rva0040A187
{
public:
	Rva0040A187(int major, int minor) : m_val0(major), m_val4(minor) {}
	bool rva0040A187(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A187(p); }
private:
	int m_val0;
	int m_val4;
};

struct Rva0040A1ACRelease
{
	void operator()(CreateAHeroData *p) const { ((Rva00219251 *)TheCreateAHeroManager)->rva0021929D(&p); }
};

template Rva0040A1ACRelease _STL::for_each<CreateAHeroData **, Rva0040A1ACRelease>(CreateAHeroData **, CreateAHeroData **, Rva0040A1ACRelease);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A16E>(CreateAHeroData **, CreateAHeroData **, Rva0040A16E, const _STL::random_access_iterator_tag &);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A187>(CreateAHeroData **, CreateAHeroData **, Rva0040A187, const _STL::random_access_iterator_tag &);
template CreateAHeroData **_STL::find_if<CreateAHeroData **, Rva0040A187>(CreateAHeroData **, CreateAHeroData **, Rva0040A187);

// Native 0x0040A59B..0x0040A5CF (52 bytes): clears the hero-data list: when
// it owns its elements (+0xC) each is released through the for_each above
// (the empty functor value-initialised, hence retail's STOSB), then the range
// is erased (STLport pointer-vector erase folded at 0x0031BD55).
class Rva0040A59B
{
public:
	void rva0040A59B();
private:
	_STL::vector<CreateAHeroData *> m_data;	// +0x00
	bool m_ownsData;			// +0x0C
};

void Rva0040A59B::rva0040A59B()
{
	if (m_ownsData)
		_STL::for_each(m_data.begin(), m_data.end(), Rva0040A1ACRelease());
	m_data.erase(m_data.begin(), m_data.end());
}
