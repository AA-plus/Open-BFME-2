// cl: /Ireference/shims/bfme2_ascii /MD
//
// AsciiString field setters: one shape, add ecx, <field>; jmp
// StringBase<char>::set (rowed 0x000366F0), i.e. assign an AsciiString member
// at a fixed offset of the receiver. Same recipe as the rowed Rva004EC1CE.cpp
// (+0x148). Each body sits in a gap between rowed functions; receivers and
// field purposes are unknown, so each gets a per-address name, and no
// referencing site was found for these in this pass.
#include "ascii_string.h"

#define BFME_ASCII_FIELD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(const AsciiString &s); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::set(const AsciiString &s) \
	{ \
		return ((StringBase<char> &)m_str).set((const StringBase<char> &)s); \
	}

BFME_ASCII_FIELD_SETTER(Rva001ED634StringField, 0x4)
BFME_ASCII_FIELD_SETTER(Rva0023D467StringField, 0x34)
BFME_ASCII_FIELD_SETTER(Rva0030C951StringField, 0x9C)
BFME_ASCII_FIELD_SETTER(Rva00318E28StringField, 0x20)
BFME_ASCII_FIELD_SETTER(Rva0039558BStringField, 0x98)
BFME_ASCII_FIELD_SETTER(Rva0039D91FStringField, 0x318)
BFME_ASCII_FIELD_SETTER(Rva00406FF9StringField, 0x41C)
BFME_ASCII_FIELD_SETTER(Rva0041E70FStringField, 0x2C)
BFME_ASCII_FIELD_SETTER(Rva0045515CStringField, 0x424)
BFME_ASCII_FIELD_SETTER(Rva0059804AStringField, 0x3C)
BFME_ASCII_FIELD_SETTER(Rva0059EF95StringField, 0xFDC)
