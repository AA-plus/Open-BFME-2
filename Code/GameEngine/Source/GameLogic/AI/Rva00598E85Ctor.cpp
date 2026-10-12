// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00598E85@@QAE@PAX@Z, retail 0x00598E85..0x00598F08 (131 bytes, EH,
// ret 4): the constructor AIBuilder's constructor (??0AIBuilder@@QAE@PAVPlayer@@@Z)
// calls with its argument (pinned under this address name). Over the rowed
// Rva00506B1B base (ctor 0x00506B1B) it installs table 0x00C70D2C and builds
// the members through the rowed STLport instantiations each call names: the
// int-keyed map at +0x08 (0x0033C432), the observer list at +0x14 (list base
// 0x004EC36C), the int-keyed hash_map at +0x18 (0x00598E66) and two vectors
// at +0x3C/+0x4C (folded vector base 0x00211E58), each after a -1 word; the
// argument at +0x30 and two flags at +0x2C/+0x34. Element identities are the
// existing address-derived spellings.
#include <map>
#include <list>
#include <hash_map>
#include <vector>

struct Rva00501875Count
{
	int m_count;
};

struct Rva004FA1FObserver;

struct Rva00598E66Element
{
	char bytes[1];
	bool operator<(const Rva00598E66Element &) const;
	bool operator==(const Rva00598E66Element &) const;
};

class Rva00506B1B
{
public:
	Rva00506B1B();										// 0x00506B1B
	virtual ~Rva00506B1B() {}
	virtual void v1();
	bool m_04;
};

class Rva00598E85 : public Rva00506B1B
{
public:
	Rva00598E85(void *owner);
	virtual ~Rva00598E85();
	virtual void v1();

private:
	_STL::map<int, Rva00501875Count> m_counts;			// +0x08
	_STL::list<Rva004FA1FObserver *> m_observers;		// +0x14
	_STL::hash_map<int, Rva00598E66Element> m_table;	// +0x18
	bool m_2C;											// +0x2C
	void *m_owner;										// +0x30
	bool m_34;											// +0x34
	int m_38;											// +0x38
	_STL::vector<int> m_3C;								// +0x3C
	int m_48;											// +0x48
	_STL::vector<int> m_4C;								// +0x4C
};

Rva00598E85::Rva00598E85(void *owner)
	: m_2C(true), m_owner(owner), m_34(false), m_38(-1), m_48(-1)
{
}
