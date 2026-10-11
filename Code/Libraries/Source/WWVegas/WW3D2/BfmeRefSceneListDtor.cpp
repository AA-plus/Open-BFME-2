// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1BfmeRefSceneList@@UAE@XZ, retail 0x0006F29B, 68 bytes.
// Dtor drains the list via the rowed Release_Head, then the rowed generic
// base dtor runs. Single-inheritance chain so one vtable store lands.

inline void *operator new(unsigned int, void *p) { return p; }
class MultiListObjectClass;
class RenderObjClass;

class MultiListNodeClass
{
public:
	class MultiListNodeClass *Prev;
	class MultiListNodeClass *Next;
	class MultiListNodeClass *NextList;
	class MultiListObjectClass *Object;
	class GenericMultiListClass *List;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass();
	virtual ~GenericMultiListClass();

	bool Is_Empty(void)
	{
		return (Head.Next == &Head);
	}

private:
	MultiListNodeClass Head;
};

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Release_Head(void);
};

class BfmeRefSceneList : public RefMultiListClass<RenderObjClass>
{
public:
	BfmeRefSceneList();
	virtual ~BfmeRefSceneList();
};

// ??0BfmeRefSceneList@@QAE@XZ, retail 0x0006E518 (18B): the rowed
// GenericMultiListClass constructor 0x00065815 (RefMultiListClass's own is
// empty) then vtable 0x00BC6260, the one the destructor below restores.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline BfmeRefSceneList::BfmeRefSceneList()
{
}

// ?bfmeAnchorBfmeRefSceneListCtor absent-from-retail
void *bfmeAnchorBfmeRefSceneListCtor(void *where)
{
	return ::new (where) BfmeRefSceneList();
}

BfmeRefSceneList::~BfmeRefSceneList()
{
	while (!Is_Empty())
		Release_Head();
}
