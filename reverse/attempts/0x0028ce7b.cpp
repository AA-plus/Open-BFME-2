// ?rva0028CE7B@Object@@QBECXZ
// partial score=0.87 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0028CE7B@Object@@QBECXZ, retail 0x0028CE7B..0x0028CECF (84 B, RET0).
// Crush-level query between the rowed findAttributeModifierPoolUpdate
// 0x0028BDD7 and the Object accessors: read the template's alternate-crushable
// byte at +0x5FC, fall back to the crushable byte at +0x5FA when it is -1 or
// when bit 22 of the object's +0x124 flags is clear, and add the 0x19 attribute
// modifier the pool reports (cvttss2si of the returned float).
// Callees are the rowed Object::findAttributeModifierPoolUpdate
// (?findAttributeModifierPoolUpdate@Object@@ABEPAVAttributeModifierPoolUpdate@@XZ
// 0x0028BDD7) and the rowed
// ?rva00403382@AttributeModifierPoolUpdate@@QAE_NHPAMH@Z 0x00403382.  The
// template view and the flag word keep address-derived member names.
class AttributeModifierPoolUpdate {
public:
	bool rva00403382(int id, float *value, int index);
};

struct Rva0028CE7BTemplateView {
	char pad00[0x5fa];
	signed char m_crushable;		// +0x5FA
	char pad5fb;
	signed char m_alternateCrushable;	// +0x5FC
};

class Object {
public:
	signed char rva0028CE7B() const;
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;	// 0x0028BDD7
	char pad00[4];
	const Rva0028CE7BTemplateView *m_template;	// +0x04
	char pad08[0x124 - 0x08];
	unsigned m_flags124;				// +0x124
};

signed char Object::rva0028CE7B() const
{
	const Rva0028CE7BTemplateView *tpl = m_template;
	float bonus;
	signed char add = 0;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool && pool->rva00403382(0x19, &bonus, 0))
		add = (signed char)(int)bonus;
	signed char level = tpl->m_alternateCrushable;
	if (level == -1 || ((m_flags124 >> 22) & 1) == 0)
		level = tpl->m_crushable;
	return level + add;
}
