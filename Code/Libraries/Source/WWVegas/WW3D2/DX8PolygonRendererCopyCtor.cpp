// cl: /DNDEBUG /MD /EHsc
//
// ??0DX8PolygonRendererClass@@QAE@ABV0@PAVMeshModelClass@@@Z at retail
// 0x00187E90 (149B). Dedicated TU: same reason as DX8PolygonRendererCtor.cpp
// (the Code/ dx8polygonrenderer.cpp TU is a ZH port whose renderer class
// lacks the BFME split-table members). Class decls mirror that TU exactly:
// the copy reads src at the same measured offsets (mmc +8, texture_category
// +C, strip +2C, pass +0x30) and reaches MeshModelClass::PolygonRendererList
// at +0x9C (BFME2 0x8C geometry base).
// No new pins: the single call decodes to the matched
// ?Internal_Add_Tail@GenericMultiListClass @0x00610820 (same as the primary
// ctor). The near tool's only drift (scope-table push VA) is cross-image
// layout noise: retail carries the same table as the primary ctor.

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
		const DX8PolygonRendererClass &src,
		MeshModelClass *mmc_);

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

// ??0DX8PolygonRendererClass@@QAE@ABV0@PAVMeshModelClass@@@Z
DX8PolygonRendererClass::DX8PolygonRendererClass(const DX8PolygonRendererClass& src,MeshModelClass* mmc_)
	:
	mmc(mmc_),
	texture_category(src.texture_category),
	index_offset(src.index_offset),
	vertex_offset(src.vertex_offset),
	min_vertex_index(src.min_vertex_index),
	vertex_index_range(src.vertex_index_range),
	min_vertex_index2(src.min_vertex_index2),
	vertex_index_range2(src.vertex_index_range2),
	index_count(src.index_count),
	strip(src.strip),
	pass(src.pass)
{
	mmc->PolygonRendererList.Internal_Add_Tail(this, true);
}
