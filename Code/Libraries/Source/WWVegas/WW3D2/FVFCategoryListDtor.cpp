// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ??1FVFCategoryList@@UAE@XZ at retail 0x00144750 (95B) with its scalar
// deleting destructor ??_GFVFCategoryList@@UAEPAXI@Z at 0x00144890 (27B).
// Dedicated TU: BFME2 made the category lists real classes (vtables
// 0xBD34E8/0xBD34E4/0xBD34E0 with ICF-folded tails) instead of ZH/BFME1
// MultiListClass typedefs, so neither dx8renderer.cpp (ZH header, statics)
// nor dx8fvf.cpp can host these bodies.
//
// Minimal TU-local hierarchy with real manglings for the two resolved
// callees: Remove_Head inlines to matched Internal_Remove_List_Head
// @0x6109A0; the base dtor resolves to matched ??1GenericMultiListClass
// @0x610640. Base flags (-EHsc-) kept: the retail dtor carries an SEH
// prolog with states that /EHsc does not reproduce.

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class MultiListNodeClass
{
public:
	MultiListNodeClass(void) { Prev = Next = NextList = 0; Object = 0; List = 0; }
	void *Prev;
	void *Next;
	void *NextList;
	void *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	MultiListNodeClass Head;

	GenericMultiListClass(void) { Head.Next = Head.Prev = &Head; Head.Object = 0; Head.NextList = 0; }
	virtual ~GenericMultiListClass();

protected:
	MultiListObjectClass *Internal_Remove_List_Head();
};

class FVFCategoryList : public GenericMultiListClass
{
public:
	FVFCategoryList(void);
	virtual ~FVFCategoryList();
};

// ??1FVFCategoryList@@UAE@XZ
FVFCategoryList::~FVFCategoryList()
{
	while (Head.Next != (void *)&Head) {
		Internal_Remove_List_Head();
	}
}

// ??0FVFCategoryList@@QAE@XZ at retail 0x00143D90 (39B): the constructor, the Zero
// Hour multilist node and list-head constructors inlined (an empty circular
// head) before the vtable store. No direct caller remains in retail.
FVFCategoryList::FVFCategoryList(void)
{
}
