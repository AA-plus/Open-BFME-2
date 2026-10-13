// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00420E67@@QAE@XZ, retail 0x00420E0D, 82 bytes. MI ctor over
// GameEngineDeletingBase-size base plus Snapshot plus Coord3D list at +0x10
// plus bool at +0x14: baseConstruct then Snapshot base vtable then derived
// vtables then List_base then bool false with EH prolog. Evidence: dtor
// 0x00420E67 same class; callees rowed baseConstruct 0x001B4E63 plus
// List_base 0x00280A8D; layouts +0xC/+0x10/+0x14 match dtor.
#include <list>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) Rva00420E67Base
{
public:
	Rva00420E67Base() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	~Rva00420E67Base();
	virtual void unused();
	char m_pad04[8];
};

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"


class Rva00420E67 : public Rva00420E67Base, public Snapshot
{
public:
	Rva00420E67();
private:
	_STL::list<Coord3D> m_list10;
	bool m_14;
};

Rva00420E67::Rva00420E67()
: m_list10(), m_14(false)
{
}
