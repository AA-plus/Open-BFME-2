// cl: /DNDEBUG /MD /EHsc
//
// ??0DX8PolygonRendererClass@@QAE@IPAVMeshModelClass@@PAVDX8TextureCategoryClass@@II_NI@Z
// at retail 0x00187DE0 (139B). Dedicated TU: the Code/ dx8polygonrenderer.cpp
// TU is a ZH port whose renderer class lacks the BFME split-table members,
// so this body cannot live there.
//
// Two measured BFME2 repairs vs the BFME1 donor (kept verbatim otherwise):
// - MeshModelClass::PolygonRendererList sits at +0x9C (retail `add ecx,0x9C`
//   ahead of the Internal_Add_Tail call), not BFME1's +0xA4. A sibling TU
//   (MeshModelClass_ComputeRamSize.cpp) independently proves the BFME2
//   geometry base is 0x8C, 8 less than BFME1's 0x94, so the list is reached
//   through a TU-local MeshModelClass stand-in with the proven pad.
// - Retail reads texture_category at +0xC (dtor @0x187CE0 `mov ecx,[esi+0xC]`,
//   matched in the home TU), i.e. a NULL member precedes mmc exactly as the
//   inherited MultiListObjectClass::ListNode does; the TU-local renderer
//   decl mirrors that shape.
// No new pins: the body's single call decodes to 0x00610820, the MATCHED
// ?Internal_Add_Tail@GenericMultiListClass (multilist.cpp); the sweep's
// b_009dbfe0 pin is stale. WWASSERT compiles out under /DNDEBUG.

#define WWASSERT(x) ((void)0)

class MultiListObjectClass
{
public:
	__declspec(dllimport) __forceinline MultiListObjectClass() : ListNode(0) { }
	virtual ~MultiListObjectClass();

private:
	void *ListNode;
};

class MultiListNodeClass
{
public:
	void *Prev;
	void *Next;
	void *NextList;
	void *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();

protected:
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce = true);

	friend class DX8PolygonRendererClass;

private:
	MultiListNodeClass Head;
};

class DX8PolygonRendererClass;
class DX8TextureCategoryClass;
class MeshModelClass;

class DX8PolygonRendererList : public GenericMultiListClass
{
};

class MeshModelClass
{
public:
	char _pad[0x9C];
	DX8PolygonRendererList PolygonRendererList;
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
	DX8PolygonRendererClass(
		unsigned index_count_,
		MeshModelClass *mmc_,
		DX8TextureCategoryClass *tex_cat,
		unsigned vertex_offset_,
		unsigned index_offset_,
		bool strip_,
		unsigned pass_);

private:
	MeshModelClass *mmc;
	DX8TextureCategoryClass *texture_category;
	unsigned index_offset;
	unsigned vertex_offset;
	unsigned index_count;
	unsigned min_vertex_index;
	unsigned vertex_index_range;
	unsigned min_vertex_index2;
	unsigned vertex_index_range2;
	bool strip;
	unsigned pass;
};

// ??0DX8PolygonRendererClass@@QAE@IPAVMeshModelClass@@PAVDX8TextureCategoryClass@@II_NI@Z
DX8PolygonRendererClass::DX8PolygonRendererClass(
	unsigned index_count_,
	MeshModelClass *mmc_,
	DX8TextureCategoryClass *tex_cat,
	unsigned vertex_offset_,
	unsigned index_offset_,
	bool strip_,
	unsigned pass_)
	:
	mmc(mmc_),
	texture_category(tex_cat),
	index_offset(index_offset_),
	vertex_offset(vertex_offset_),
	min_vertex_index(0),
	vertex_index_range(0),
	min_vertex_index2(0),
	vertex_index_range2(0),
	index_count(index_count_),
	strip(strip_),
	pass(pass_)
{
	WWASSERT(index_count);
	mmc->PolygonRendererList.Internal_Add_Tail(this, true);
}
