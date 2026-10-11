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
};

class Rva00160150
{
public:
	void rva00160150(float *out, int frame, int extra) const;
private:
	Rva00160150Channel *m_x;	// +0x00
	Rva00160150Channel *m_y;	// +0x04
	Rva00160150Channel *m_z;	// +0x08
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
