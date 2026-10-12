// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG
// Out-of-line copies of the ref-counted impl constructors that
// Rva00080221Ctor.cpp's wrapper constructors inline: the base zeroes the
// count (+0x04), then the impl's vftable, then the copied value (+0x08).
// Class names and vftables follow Rva00080221Ctor.cpp; retail keeps these
// copies out of line beside their callers. Each constructor is select-any
// like the inline copies elsewhere, and an anchor keeps the noinline body
// emitted.
inline void *operator new(unsigned int, void *p) { return p; }

struct Rva00080221RefImpl
{
	virtual ~Rva00080221RefImpl() {}
	int m_ref;
	Rva00080221RefImpl() : m_ref(0) {}
};

// vftable 0x00BC6FF4: Rva007C6FF4Impl, out-of-line constructor copy at 0x0014F3CF (24B).
struct Rva007C6FF4Impl : Rva00080221RefImpl
{
	int m_value;
	Rva007C6FF4Impl(const int &value);
};

__declspec(noinline) inline Rva007C6FF4Impl::Rva007C6FF4Impl(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva0014F3CF absent-from-retail
void *bfmeAnchorRva0014F3CF(void *where, const int &value)
{
	return ::new (where) Rva007C6FF4Impl(value);
}

// vftable 0x00BE5128: Impl00211E75, out-of-line constructor copy at 0x002111FE (24B).
struct Impl00211E75 : Rva00080221RefImpl
{
	int m_value;
	Impl00211E75(const int &value);
};

__declspec(noinline) inline Impl00211E75::Impl00211E75(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva002111FE absent-from-retail
void *bfmeAnchorRva002111FE(void *where, const int &value)
{
	return ::new (where) Impl00211E75(value);
}

// vftable 0x00C02AEC: Impl002D4594, out-of-line constructor copy at 0x002D399D (24B).
struct Impl002D4594 : Rva00080221RefImpl
{
	int m_value;
	Impl002D4594(const int &value);
};

__declspec(noinline) inline Impl002D4594::Impl002D4594(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva002D399D absent-from-retail
void *bfmeAnchorRva002D399D(void *where, const int &value)
{
	return ::new (where) Impl002D4594(value);
}

// vftable 0x00C02AF4: Impl002D45C9, out-of-line constructor copy at 0x002D39B5 (24B).
struct Impl002D45C9 : Rva00080221RefImpl
{
	int m_value;
	Impl002D45C9(const int &value);
};

__declspec(noinline) inline Impl002D45C9::Impl002D45C9(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva002D39B5 absent-from-retail
void *bfmeAnchorRva002D39B5(void *where, const int &value)
{
	return ::new (where) Impl002D45C9(value);
}

// vftable 0x00C02AFC: Impl002D45FE, out-of-line constructor copy at 0x002D39CD (24B).
struct Impl002D45FE : Rva00080221RefImpl
{
	int m_value;
	Impl002D45FE(const int &value);
};

__declspec(noinline) inline Impl002D45FE::Impl002D45FE(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva002D39CD absent-from-retail
void *bfmeAnchorRva002D39CD(void *where, const int &value)
{
	return ::new (where) Impl002D45FE(value);
}

// vftable 0x00C6E970: Impl005773DB, out-of-line constructor copy at 0x0057738E (24B).
struct Impl005773DB : Rva00080221RefImpl
{
	int m_value;
	Impl005773DB(const int &value);
};

__declspec(noinline) inline Impl005773DB::Impl005773DB(const int &value) : m_value(value)
{
}

// ?bfmeAnchorRva0057738E absent-from-retail
void *bfmeAnchorRva0057738E(void *where, const int &value)
{
	return ::new (where) Impl005773DB(value);
}
