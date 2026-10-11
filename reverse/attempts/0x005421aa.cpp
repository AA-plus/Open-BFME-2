// ?rva005421AA@Rva00541F1F@@QBE?AVRva0053FC99@@XZ
// partial score=0.9 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
//
// The camera animations' clone slots: each copies the animation into a new
// object and hands it back in a reference-counted pointer, built from the
// raw object (0x0053FC81) and copied out (0x0053FC99); the local pointer's
// inline destructor releases its reference through the rowed 0x0053FA32.
//  - ?rva005421AA@Rva00541F1F@@QBE?AVRva0053FC99@@XZ retail 0x005421AA
//    (123 bytes, EH, ret 4): the look-at animation (table 0x00C69510, 0x64
//    bytes, rowed copy constructor 0x00541F1F).
//  - ?rva00540A88@Rva00540845@@QBE?AVRva0053FC99@@XZ retail 0x00540A88
//    (123 bytes, EH, ret 4): the free-camera animation (table 0x00C694F8,
//    0x44 bytes, rowed copy constructor 0x00540845).
// The pointer's two constructors are rowed under address-named member
// spellings and pinned here as constructors. Method names are placeholders.

class Rva0053F8E5DwordCounter;
class Rva0053FA0A
{
public:
	void rva0053FA32();
};
class Rva0053FC81
{
public:
	Rva0053FC81(Rva0053F8E5DwordCounter *object);
	~Rva0053FC81()
	{
		if (m_object)
			((Rva0053FA0A *)m_object)->rva0053FA32();
	}
	Rva0053F8E5DwordCounter *m_object;
};
// The returned base-typed pointer, converted from the derived one.
class Rva0053FC99
{
public:
	Rva0053FC99(const Rva0053FC81 &other);
	~Rva0053FC99()
	{
		if (m_object)
			((Rva0053FA0A *)m_object)->rva0053FA32();
	}
private:
	Rva0053F8E5DwordCounter *m_object;
};

class Rva00541F1F
{
public:
	Rva00541F1F(const Rva00541F1F &other);
	Rva0053FC99 rva005421AA() const;
private:
	char m_data[0x64];
};

Rva0053FC99 Rva00541F1F::rva005421AA() const
{
	return Rva0053FC81((Rva0053F8E5DwordCounter *)new Rva00541F1F(*this));
}

class Rva00540845
{
public:
	Rva00540845(const Rva00540845 &other);
	Rva0053FC99 rva00540A88() const;
private:
	char m_data[0x44];
};

Rva0053FC99 Rva00540845::rva00540A88() const
{
	return Rva0053FC81((Rva0053F8E5DwordCounter *)new Rva00540845(*this));
}
