// cl: /DNDEBUG /MD
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

class RefCountedShadowResource
{
public:
	virtual void deleteThis(void) = 0;
	unsigned long referenceCount;
};

// Partial observed view: pool recycling calls retail 0x007AEC10 on the
// unchanged shadow receiver. This is separate from complete destruction
// at 0x007AFF00; retain an address-qualified method until its name is proven.
class W3DProjectedShadow
{
public:
	void rva007AEC10(void);
	void rva00108931(void);
	void rva00108951(void);

private:
	unsigned char m_shadowData00[0x08];
	float m_value08[3];			// +0x08
	unsigned char m_shadowData14[0x20 - 0x14];
	float m_value20;			// +0x20
	unsigned char m_shadowData24[0x28 - 0x24];
	int m_index28;				// +0x28
	unsigned char m_shadowData2C[0x68 - 0x2C];
	RefCountedShadowResource *m_references68[2];
	RefCountedShadowResource *m_reference70;
};

static void releaseReference(RefCountedShadowResource *resource)
{
	if (--resource->referenceCount == 0)
		resource->deleteThis();
}

void W3DProjectedShadow::rva007AEC10(void)
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_references68[i] != 0)
		{
			releaseReference(m_references68[i]);
			m_references68[i] = 0;
		}
	}
	if (m_reference70 != 0)
	{
		releaseReference(m_reference70);
		m_reference70 = 0;
	}
}

// Retail 0x00108931 (32 bytes), between the two bodies above and below it:
// sets +0x28 to -1, drops the first reference slot without releasing it, and
// zeroes the floats at +0x10, +0x0C, +0x08 and +0x20. No direct call or
// address reference reaches it in retail, so its name stays address-derived.
void W3DProjectedShadow::rva00108931(void)
{
	m_index28 = -1;
	m_references68[0] = 0;
	m_value08[2] = 0.0f;
	m_value08[1] = 0.0f;
	m_value08[0] = 0.0f;
	m_value20 = 0.0f;
}

void W3DProjectedShadow::rva00108951(void)
{
	RefCountedShadowResource *p = m_references68[0];
	if (p != 0)
	{
		if (--p->referenceCount == 0)
			p->deleteThis();
		m_references68[0] = 0;
	}
}
