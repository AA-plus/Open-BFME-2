// cl: /O1 /G7 /DNDEBUG /MD
// BF1 f989 multilist.h structural candidate, not a target template identity.
// Native 6EF7D calls Internal_Remove_List_Head6109A0 then preserves null
// while adjusting a nonnull result -8. The concrete payload remains unknown.
class MultiListObjectClass { public: void *ListNode; };
class RefCountClass { public: virtual void Delete_This(); int RefCount; };
class RenderObjClass : public RefCountClass, public MultiListObjectClass {};
class GenericMultiListClass {
protected: MultiListObjectClass *Internal_Remove_List_Head();
};
template<class T> class MultiListClass : public GenericMultiListClass {
public: T *Remove_Head();
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline RenderObjClass *MultiListClass<RenderObjClass>::Remove_Head() {
    return static_cast<RenderObjClass *>(Internal_Remove_List_Head());
}

// ?bfmeAnchorMultiListRenderObjRemoveHead absent-from-retail
RenderObjClass *bfmeAnchorMultiListRenderObjRemoveHead(MultiListClass<RenderObjClass> *p)
{
	return p->Remove_Head();
}
