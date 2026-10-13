// cl: /DNDEBUG /MD /EHsc /Ob2

// Open-BFME5: DefaultAlphaModuleInfo default constructor @0x55B44D.
// Retail: own vtable, then eight RandomAlphaKeyframe elements at +4 built by
// the rowed vector_constructor_iterator helper through the rowed element
// default at 0x00001E7F. The element's declared (never defined) destructor
// is what carries the EH frame.

namespace FXParticleSystem
{

class Xfer;

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class RandomAlphaKeyframe
{
public:
	RandomAlphaKeyframe();

private:
	char m_data[0x10];
};

class DefaultAlphaModuleInfo : public Snapshot
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();

private:
	RandomAlphaKeyframe m_keys[8];
};

// ??0DefaultAlphaModuleInfo@FXParticleSystem@@QAE@XZ
DefaultAlphaModuleInfo::DefaultAlphaModuleInfo()
{
}

}
