// cl: /O1 /DNDEBUG /MD /EHsc
// DllHandle exception hierarchy named by catchable-type RTTI at 0x00D11F4C.
// Its two adjacent copy constructors at 0x0020426C and 0x00204285 copy the
// exception base in order, each installing the folded vtable at 0x00BD3B54.

extern "C" const void *const vtbl_00BD3B54[];  // ??_7FunctorNotSet@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD3B54=??_7FunctorNotSet@@6B@")

class __declspec(dllimport) exception
{
public:
    exception(const exception &other);
    virtual ~exception();
private:
    const char *m_what;
    int m_doFree;
};

class DllHandle
{
public:
    class Exception : public exception
    {
    public:
        Exception(const Exception &other);
        virtual ~Exception();
    };
    class LoadFailure : public Exception
    {
    public:
        LoadFailure(const LoadFailure &other);
    };
};

inline DllHandle::Exception::Exception(const Exception &other)
    : exception(other)
{
    *(unsigned int *)this = ((unsigned int)vtbl_00BD3B54);
}

inline DllHandle::LoadFailure::LoadFailure(const LoadFailure &other)
    : Exception(other)
{
    *(unsigned int *)this = ((unsigned int)vtbl_00BD3B54);
}

// DllHandle exception copies are header inlines elsewhere: other units emit
// select-any copies, so strong definitions here were duplicates in the linked
// build. This anchor only makes this unit emit its copies for the ledger rows;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitScriptEngineDllHandleExceptionCopies@@YAXPAVException@DllHandle@@PBV12@PAVLoadFailure@2@PBV32@@Z present-unmatched
void bfmeEmitScriptEngineDllHandleExceptionCopies(DllHandle::Exception *p0, const DllHandle::Exception *q0, DllHandle::LoadFailure *p1, const DllHandle::LoadFailure *q1)
{
	p0->Exception::Exception(*q0);
	p1->LoadFailure::LoadFailure(*q1);
}
#pragma inline_depth()
