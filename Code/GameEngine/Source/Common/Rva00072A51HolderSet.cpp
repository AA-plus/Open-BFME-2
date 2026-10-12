// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// RVA 0x00072A51, 67B (vtable entries in 0x00BC655C, 0x00BC6584 and
// 0x00BC6C40): stores a by-value ref-counted holder into the member at +8
// through the rowed assignment ??4Rva00072A94 (0x00072A94); the argument's
// destructor then drops the caller's reference under EH protection.
class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &);
	~Rva00072A94()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	RefCountClass *m_ptr;
};

class Rva00072A51
{
public:
	virtual void rva00072A51(Rva00072A94 value);

private:
	int m_field04;
	Rva00072A94 m_value;	// +8
};

void Rva00072A51::rva00072A51(Rva00072A94 value)
{
	m_value = value;
}
