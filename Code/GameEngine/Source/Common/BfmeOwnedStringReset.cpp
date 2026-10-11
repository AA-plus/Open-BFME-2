// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib

// Link: declare ~AsciiString only (the shim's documented per-unit switch) so this TU calls the out-of-line
// retail destructor instead of emitting a non-retail ??_GAsciiString copy; the // cl: line is untouched.
#ifndef BFME_ASCII_DTOR_DECL
#define BFME_ASCII_DTOR_DECL
#endif
void __cdecl operator delete(void *);

#include "ascii_string.h"

class Gen_dtor_0034dd90
{
public:
	virtual ~Gen_dtor_0034dd90();
};

class BfmeOwnedStringState
{
public:
	void resetOwnedObject();

private:
	int m_head;
	AsciiString m_name;
	int m_reset;
	Gen_dtor_0034dd90 *m_owned;
};

void BfmeOwnedStringState::resetOwnedObject()
{
	m_name.~AsciiString();
	Gen_dtor_0034dd90 *owned = m_owned;
	m_reset = 1;
	if (owned != 0) {
		owned->Gen_dtor_0034dd90::~Gen_dtor_0034dd90();
		operator delete(owned);
		m_owned = 0;
	}
}
