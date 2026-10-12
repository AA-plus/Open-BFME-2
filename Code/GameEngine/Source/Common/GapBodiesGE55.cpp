// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (fifty-fifth
// batch; see GapBodiesGE01.cpp), all from the /O1 /arch:SSE /G7 retail region
// that starts at 0x001D8E99 (reverse/retail_inventory/flag_regions.csv). Each
// begins after its neighbour's padding or ret and ends in its own ret or tail
// jump. Retail bytes establish every shape; owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees use the ledger's existing spellings.

// --- 0x002190AF (62B) / 0x002190ED (64B): two default sets of four tuning
// floats and a zero (0.3, 0.2, 50, 30 and 0.4, 0.3, 70, 50).
class Rva002190AF
{
public:
	Rva002190AF();
	Rva002190AF(int variant);
private:
	float m_a;
	float m_b;
	float m_c;
	float m_d;
	float m_e;
};

Rva002190AF::Rva002190AF() : m_a(0.3f), m_b(0.2f), m_c(50.0f), m_d(30.0f), m_e(0.0f)
{
}

Rva002190AF::Rva002190AF(int variant) : m_a(0.4f), m_b(0.3f), m_c(70.0f), m_d(50.0f), m_e(0.0f)
{
}

// --- 0x00219964 (22B): a string copied through the rowed private
// StringBase<char> copy constructor 0x000365F0 and a cleared flag.
class Rva00219964;

template <class T> class StringBase
{
	friend class Rva00219964;
	StringBase(const StringBase<T> &that);
	T *m_data;
};

class Rva00219964
{
public:
	Rva00219964(const StringBase<char> &name);
private:
	StringBase<char> m_name;
	bool m_flag;											// +0x04
};

Rva00219964::Rva00219964(const StringBase<char> &name) : m_name(name), m_flag(false)
{
}

// --- 0x0021FAE8 (9B): destroy a Rva0021F876 in place through its rowed
// destructor 0x0021F8F3.
class Rva0021F876
{
public:
	~Rva0021F876();
};

void rva0021FAE8(Rva0021F876 *object)
{
	object->~Rva0021F876();
}

// --- 0x0021FAF1 (27B): append a CreateAHeroSubClass to the +0x14 vector
// through its rowed push_back and return the new last element.
class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
		char m_bytes[0xD8];
	};
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		void push_back(const T &value);
		T &back() { return *(m_finish - 1); }
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva0021FAF1
{
public:
	CreateAHeroManager::CreateAHeroSubClass *rva0021FAF1(const CreateAHeroManager::CreateAHeroSubClass &value);
private:
	char m_pad00[0x14];
	_STL::vector<CreateAHeroManager::CreateAHeroSubClass> m_subClasses;	// +0x14
};

CreateAHeroManager::CreateAHeroSubClass *Rva0021FAF1::rva0021FAF1(const CreateAHeroManager::CreateAHeroSubClass &value)
{
	m_subClasses.push_back(value);
	return &m_subClasses.back();
}
