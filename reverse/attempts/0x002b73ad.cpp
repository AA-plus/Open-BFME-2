// ??$__linear_insert@PAVRva004F6093Holder@@V1@URva002BBC1CCmp@@@_STL@@YAXPAVRva004F6093Holder@@0V1@URva002BBC1CCmp@@@Z
// partial score=0.9 date=2026-10-13
// ??$__linear_insert@PAVRva004F6093Holder@@V1@URva002BBC1CCmp@@@_STL@@YAXPAVRva004F6093Holder@@0V1@URva002BBC1CCmp@@@Z
// ? at 0x002B73AD, 135B (symbols.csv: address read from the retail REL32 in
// __insertion_sort 0x002B833C; body unrowed, codegen differs).
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Bank 2026-10-13 W7-MP5: the 130B shape (Holder copy ctor declared out-of-line)
// becomes size-exact 135B once the copy ctor is DEFINED INLINE in this TU
// (`: m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->m_ac.references; }`), exactly as
// the matched adjust_heap/pop_heap TUs define it: the by-value temp then inlines
// as `mov [esp],val; inc [m_ptr+0xB0]` like retail instead of calling 0x004F6093.
// Sole residual is allocator-level: retail loads the value param once into ESI
// (`mov esi,[ebp+0x10]`, push esi/pop esi) and reuses it for the temp, the
// __unguarded_linear_insert argument and the value-param dtor; this toolchain
// reloads [ebp+0x10] per use into eax/ecx and never claims ESI. const-by-value,
// named locals and explicit instantiations all reproduce the same reload shape.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva002BBC1CTarget
{
	char m_pad00[0xAC];
	TargetRef00217D4C m_ac; // +0xAC, references at +0xB0
};

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other);

private:
	Rva002BBC1CTarget *m_ptr;
};

struct Rva002BBC1CCmp
{
	bool operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const;
};

namespace _STL
{

template <class _RandomAccessIter, class _OutputIter>
_OutputIter copy_backward(_RandomAccessIter __first, _RandomAccessIter __last,
	_OutputIter __result);

template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_linear_insert(_RandomAccessIter __last, _Tp __val,
	_Compare __comp);

template <class _RandomAccessIter, class _Tp, class _Compare>
void __linear_insert(_RandomAccessIter __first, _RandomAccessIter __last,
	_Tp __val, _Compare __comp)
{
	if (__comp(__val, *__first))
	{
		copy_backward(__first, __last, __last + 1);
		*__first = __val;
	}
	else
	{
		__unguarded_linear_insert(__last, __val, __comp);
	}
}

template void __linear_insert<Rva004F6093Holder *, Rva004F6093Holder,
	Rva002BBC1CCmp>(Rva004F6093Holder *, Rva004F6093Holder *,
	Rva004F6093Holder, Rva002BBC1CCmp);

}
