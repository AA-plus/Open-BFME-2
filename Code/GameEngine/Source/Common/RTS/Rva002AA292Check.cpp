// cl: /DNDEBUG /MD /EHsc
// ?rva002AA292@Rva002AA292@@QBE_NPBH@Z 0x002AA292 41B
// Checks 32 dwords: (m_bits[i] & mask[i]) == mask[i] for all i.
// Evidence: callers 0x40C739 0x480C2E 0x4B419B etc.; lane unlock.
class Rva002AA292
{
	int m_bits[32];
public:
	bool rva002AA292(const int* mask) const;
};

bool Rva002AA292::rva002AA292(const int* mask) const
{
	for (unsigned i = 0; i < 32; ++i) {
		if ((m_bits[i] & mask[i]) != mask[i])
			return false;
	}
	return true;
}

// ?rva002AA8E4@Rva002AA8E4Owner@@QBE_NPBH@Z @0x002AA8E4 11B: offsets this to the Rva002AA292 embedded at +0x13C and
// tail-jumps Rva002AA292::rva002AA292. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva002AA8E4Owner
{
public:
	bool rva002AA8E4(const int *mask) const;
};

bool Rva002AA8E4Owner::rva002AA8E4(const int *mask) const
{
	return ((const Rva002AA292 *)((const char *)this + 0x13C))->rva002AA292(mask);
}
