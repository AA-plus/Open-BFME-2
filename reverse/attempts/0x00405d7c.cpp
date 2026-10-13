// ?rva00405D7C@Rva00405B60@@UBE?AU?$Rva00567FBCHandle@VRva00405B60@@@@XZ
// partial score=0.98 date=2026-10-13
// ?rva00405D7C@Rva00405B60@@UBE?AU?$Rva00567FBCHandle@VRva00405B60@@@@XZ
// partial score=0.93 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHa
//
// ?rva00405D7C@Rva00405B60@@UBE?AU?$Rva00567FBCHandle@VRva00405B60@@@@XZ,
// retail 0x00405D7C, 64 bytes.
//
// Evidence: new 0x10, the rowed copy ctor ??0Rva00405B60@@QAE@ABV0@@Z
// (0x405B60) and the const virtual clone returning the 4-byte
// Rva00567FBCHandle by value (sret pointer argument, ret 4). The prior wall was
// the EH frame: a declared non-trivial handle destructor supplies the
// return-value flag at [ebp-0x10] without a new-cleanup state.

template <class T>
struct Rva00567FBCHandle
{
	Rva00567FBCHandle(T *pointer = 0) : m_pointer(pointer) {}
	~Rva00567FBCHandle();

	T *m_pointer;
};

class Rva00405B60
{
public:
	Rva00405B60(const Rva00405B60 &other) throw();

	virtual Rva00567FBCHandle<Rva00405B60> rva00405D7C() const;

private:
	int m_0;
	int m_4;
	int m_8;
};

Rva00567FBCHandle<Rva00405B60> Rva00405B60::rva00405D7C() const
{
	return Rva00567FBCHandle<Rva00405B60>(new Rva00405B60(*this));
}
