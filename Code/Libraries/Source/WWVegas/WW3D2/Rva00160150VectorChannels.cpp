// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00160150@Rva00160150@@QBEXPAMHH@Z, retail 0x00160150 (113 bytes,
// RET 0x0C): a three-channel vector read placed after
// MotionChannelClass::Get_Vector_As_Quat in the raw-animation code. Each of
// the X/Y/Z channel pointers (+0/+4/+8) fills its component of the output
// through its slot 3 (+0x0C) with the frame and the extra word; a missing
// channel leaves 0. No direct caller or table slot was found, so the owner
// and channel interface keep address-derived names.
class Rva00160150Channel
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void getValue(int frame, float *out, int extra);	// +0x0C
	virtual void s04();
	virtual void getValues(int frame, float *out, int extra);	// +0x14
};

class Rva00160150
{
public:
	void rva00160150(float *out, int frame, int extra) const;
	bool rva001601D0(float *out, int frame, int extra) const;
	void rva00160200(float *out, int frame, int extra) const;
private:
	Rva00160150Channel *m_x;	// +0x00
	Rva00160150Channel *m_y;	// +0x04
	Rva00160150Channel *m_z;	// +0x08
	Rva00160150Channel *m_rotation;	// +0x0C
	Rva00160150Channel *m_scale;	// +0x10
};

void Rva00160150::rva00160150(float *out, int frame, int extra) const
{
	if (m_x)
		m_x->getValue(frame, &out[0], extra);
	else
		out[0] = 0.0f;
	if (m_y)
		m_y->getValue(frame, &out[1], extra);
	else
		out[1] = 0.0f;
	if (m_z)
		m_z->getValue(frame, &out[2], extra);
	else
		out[2] = 0.0f;
}

// Retail 0x001601D0 (39 bytes) and 0x00160200 (51 bytes), the next two readers of the same
// record: the +0x0C channel fills a multi-component value through its slot 5 (+0x14) and
// reports whether the channel exists; the +0x10 channel fills one float through slot 3, or
// leaves 1.0 when it is missing. Neither has a direct caller or table slot.
bool Rva00160150::rva001601D0(float *out, int frame, int extra) const
{
	if (!m_rotation)
		return false;
	m_rotation->getValues(frame, out, extra);
	return true;
}

void Rva00160150::rva00160200(float *out, int frame, int extra) const
{
	if (!m_scale) {
		*out = 1.0f;
		return;
	}
	m_scale->getValue(frame, out, extra);
}
