// ?rva00218C2B@Rva00218C2B@@QAEHABVAsciiString@@@Z
// partial score=0.95 date=2026-10-13
// ?rva00218C2B@Rva00218C2B@@QAEHABVAsciiString@@@Z @0x00218C2B 87B
// IN-TU (CreateAHeroDataRva004080DD.cpp, /Ob2): builds clean, existing rows
// intact, all 5 calls resolve. 84/87, SOLE wall = home packing: retail
// vec-home@-4 (and-zero) + alloc-temp@[ebp+0xb] (dead key-tail byte); ours
// vec-home@-8 + temp@-1 (extra scratch push). All structure/calls/regs exact.
// Levers proven: /Ob2 REQUIRED (else map::find/tree::find emit + _M_find
// explicit-spec ICEs C1001); base-ctor throw() kills placement-new EH;
// find via 001F8ACB-pinned IntMetaDataMap view (no new pin); operator[] via
// explicit-spec (no emission); vec=0+if/else-null/ctor shape for the
// test+je+xor+jmp. Missing: force vec-home to -4 (first home) so -1 is
// occupied and the temp spills to +0xb; decl-order/vec-first/combined-assign
// all keep -8. t=70.
// ?rva00218C2B@Rva00218C2B@@QAEHABVAsciiString@@@Z @0x00218C2B 87B.
// Lazy map-of-vectors at +0x20: find the key in the TreeHint map, else heap a
// 12B vector header (operator new + rowed _Vector_base 0x00211E58), publish it
// through the rowed TreeHint operator[] 0x00218AA4 (explicit specialization
// below, defined in its hint TU), re-find and return the payload vector at
// node+0x14. map::find/end/iterator traffic inlines (this TU's /Ob2, same as
// the StringPayloadMap user above); the _M_find leaf resolves through this
// TU's pinned TreeHintPayload001F8ACB spelling (same 78B key-only ICF body at
// 0x001F8437). Evidence: retail lea/push/call order, and-zero home, re-find
// convergence, [eax+0x14] payload return.
struct TreeHintPayload00217DE3 { int m_val; TreeHintPayload00217DE3() : m_val(0) {} TreeHintPayload00217DE3(const TreeHintPayload00217DE3 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload00217DE3> TreeHintPair00217DE3;
typedef _STL::map<AsciiString, TreeHintPayload00217DE3, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00217DE3> > TreeHintMap00217DE3;
namespace _STL {
template<> TreeHintPayload00217DE3 &TreeHintMap00217DE3::operator[](const AsciiString &);
}
struct BfmeVectorRecord00319C84;
namespace _STL {
template<> _Vector_base<BfmeVectorRecord00319C84, allocator<BfmeVectorRecord00319C84> >::_Vector_base(const allocator<BfmeVectorRecord00319C84> &) throw();
}
void *operator new(unsigned int);
class Rva00218C2B {
public:
	int rva00218C2B(const AsciiString &key);
private:
	char m_pad[0x20];
	TreeHintMap00217DE3 m_map;
};

int Rva00218C2B::rva00218C2B(const AsciiString &key)
{
	StringPayloadMap::iterator it = ((StringPayloadMap *)&m_map)->find(key);
	if (it != ((StringPayloadMap *)&m_map)->end())
		return it->second.value;
	_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *vec = 0;
	if ((vec = (_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *)operator new(sizeof(_STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >))) == 0)
		vec = 0;
	else {
		new (vec) _STL::_Vector_base<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >(_STL::allocator<BfmeVectorRecord00319C84>());
	}
	((TreeHintMap00217DE3 *)&m_map)->operator[](key).m_val = (int)vec;
	it = ((StringPayloadMap *)&m_map)->find(key);
	return it->second.value;
}

class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
};

enum NameKeyType;

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class CreateAHeroData : public Snapshot
{
public:
	bool rva004080DD(const AsciiString &key, unsigned int *out);
	unsigned int rva00408109(const NameKeyType *p);
private:
	unsigned char m_pad04[0x4C];
	StringPayloadMap m_map50;
};

bool CreateAHeroData::rva004080DD(const AsciiString &key, unsigned int *out)
{
	if (out == 0)
		return false;
	StringPayloadMap::iterator it = m_map50.find(key);
	if (it != m_map50.end())
	{
		*out = (*it).second.value;
		return true;
	}
	return false;
}

unsigned int CreateAHeroData::rva00408109(const NameKeyType *p)
{
	if (p == 0)
		return 0;
	AsciiString tmp = TheNameKeyGenerator->keyToName(*p);
	unsigned int out = 0;
	rva004080DD(tmp, &out);
	return out;
}
