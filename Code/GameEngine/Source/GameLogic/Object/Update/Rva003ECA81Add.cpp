// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva003ECA81@Rva003ECA4BElement@@QAEPAV1@PBV1@@Z, retail 0x003ECA81 (50 bytes).
// Target evidence: element-wise add of two 0x44-byte float records (the element
// whose ctor/clear are rowed at 0x003ECA4B/0x003ECA69); called by
// ThreatFinder::getThreatForPlayer, which ignores the result.
// Codegen finding: retail returns this in eax (the copy of ecx and the esi loop
// counter exist because this stays live to the epilogue); peeling element 0
// reproduces the push 0x10 / pop count idiom and the dst-src delta loop.
class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement *rva003ECA81(const Rva003ECA4BElement *other);

private:
	float m_values[17];
};

Rva003ECA4BElement *Rva003ECA4BElement::rva003ECA81(const Rva003ECA4BElement *other)
{
	m_values[0] += other->m_values[0];
	for (int i = 1; i < 17; ++i)
		m_values[i] += other->m_values[i];
	return this;
}
