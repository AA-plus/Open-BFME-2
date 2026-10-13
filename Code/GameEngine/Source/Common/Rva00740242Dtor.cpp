// cl: /O1 /DNDEBUG /MD /GX
// ??1W3DAptComponentView3D@@UAE@XZ, retail 0x00740242, 126 bytes.
// Derived dtor releasing three RefCounts then Rva0074011F at +0x20 then base Rva007401F6.
// Evidence: vtable 0x008F1600 at +0; callees rowed 0x0074011F 0x007401F6; caller 0x00740590 deleting dtor.
class RefCountClass
{
public:
	virtual void Delete_This() = 0;
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
	int m_refs;
};
class Rva0074011F
{
public:
	~Rva0074011F();
	void rva0074011F();
	RefCountClass *m_p0;
	RefCountClass *m_p1;
};
class Rva007401F6
{
public:
	virtual ~Rva007401F6();
private:
	char m_pad04[8];
};
class W3DAptComponentView3D : public Rva007401F6
{
public:
	virtual ~W3DAptComponentView3D();
private:
	RefCountClass *m_0C;
	RefCountClass *m_10;
	int m_14;
	RefCountClass *m_18;
	int m_1C;
	Rva0074011F m_20;
};
// ??1Rva0074011F@@QAE@XZ present-unmatched
Rva0074011F::~Rva0074011F()
{
	rva0074011F();
}
W3DAptComponentView3D::~W3DAptComponentView3D()
{
	if (m_10)
	{
		m_10->Release_Ref();
		m_10 = 0;
	}
	if (m_0C)
	{
		m_0C->Release_Ref();
		m_0C = 0;
	}
	if (m_18)
	{
		m_18->Release_Ref();
		m_18 = 0;
	}
}
