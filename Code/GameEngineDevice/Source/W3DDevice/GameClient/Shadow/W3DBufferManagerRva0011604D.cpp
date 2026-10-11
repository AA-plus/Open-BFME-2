// cl: /DNDEBUG /MD /EHsc

// ?ReAcquireResources@W3DBufferManager@@QAE_NXZ, retail 0x0011604D, 198 bytes.
// Evidence: __thiscall bool with no args (ret, al 1/0); loops 0x12 VB heads at
// this+0x9000 via +0x10 chain allocating BfmeDynamicNativeVB with table at
// 0x00DB5F30 indexed by m_format plus (ushort)m_size then IB list at
// this+0x263D0 allocating DX8IndexBufferClass; callers 0x000F0A50; neighbours
// 0x00115FF1/0x00116113 prove W3DBufferManager class and /O1 /DNDEBUG /MD /EHsc /G7 flags.

typedef int Int;

class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned fvf, unsigned short count, unsigned usage, unsigned fvfSize);

private:
	char m_pad[32];
};

class DX8IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(unsigned indexCount, UsageType usage);

private:
	char m_pad[24];
};

// Retail's own per-format FVF table at RVA 0x009B5F30 (.data, file offset
// 0x00975FB0): eighteen unsigned entries in the order of W3DBufferManager's
// VBM_FVF_TYPES, so the D3D flexible vertex format the rowed body below hands to
// the dynamic vertex buffer. XYZ is D3DFVF_XYZ (0x002); the D suffix adds
// D3DFVF_DIFFUSE (0x040); UV is D3DFVF_TEX1 (0x100) and UV2 D3DFVF_TEX2 (0x200);
// the N prefix adds D3DFVF_NORMAL (0x010); and XYZRHW is D3DFVF_XYZRHW (0x004).
// Eighteen entries is MAX_FVF, and 72 bytes is all but eight of the ledger's
// bound - the words that follow belong to retail's next object. The words are
// transcribed verbatim from retail's own .data.
// Symbol ?g_00DB5F30@@3PAIA, transcribed below.
extern unsigned g_00DB5F30[] =
{
	0x002, 0x042, 0x102, 0x142, 0x202, 0x242,
	0x012, 0x052, 0x112, 0x152, 0x212, 0x252,
	0x004, 0x044, 0x104, 0x144, 0x204, 0x244
};

class W3DBufferManager
{
public:
	enum VBM_FVF_TYPES
	{
		VBM_FVF_XYZ,
		VBM_FVF_XYZD,
		VBM_FVF_XYZUV,
		VBM_FVF_XYZDUV,
		VBM_FVF_XYZUV2,
		VBM_FVF_XYZDUV2,
		VBM_FVF_XYZN,
		VBM_FVF_XYZND,
		VBM_FVF_XYZNUV,
		VBM_FVF_XYZNDUV,
		VBM_FVF_XYZNUV2,
		VBM_FVF_XYZNDUV2,
		VBM_FVF_XYZRHW,
		VBM_FVF_XYZRHWD,
		VBM_FVF_XYZRHWUV,
		VBM_FVF_XYZRHWDUV,
		VBM_FVF_XYZRHWUV2,
		VBM_FVF_XYZRHWDUV2,
		MAX_FVF
	};

	struct W3DRenderTask
	{
		W3DRenderTask *m_nextTask;
	};

	struct W3DVertexBufferSlot
	{
		Int m_size;
		Int m_start;
		struct W3DVertexBuffer *m_VB;
		W3DVertexBufferSlot *m_prevSameSize;
		W3DVertexBufferSlot *m_nextSameSize;
		W3DVertexBufferSlot *m_prevSameVB;
		W3DVertexBufferSlot *m_nextSameVB;
	};

	struct W3DVertexBuffer
	{
		VBM_FVF_TYPES m_format;
		W3DVertexBufferSlot *m_usedSlots;
		Int m_startFreeIndex;
		Int m_size;
		W3DVertexBuffer *m_nextVB;
		BfmeDynamicNativeVB *m_DX8VertexBuffer;
		W3DRenderTask *m_renderTaskList;
	};

	struct W3DIndexBufferSlot
	{
		Int m_size;
		Int m_start;
		struct W3DIndexBuffer *m_IB;
		W3DIndexBufferSlot *m_prevSameSize;
		W3DIndexBufferSlot *m_nextSameSize;
		W3DIndexBufferSlot *m_prevSameIB;
		W3DIndexBufferSlot *m_nextSameIB;
	};

	struct W3DIndexBuffer
	{
		W3DIndexBufferSlot *m_usedSlots;
		Int m_startFreeIndex;
		Int m_size;
		W3DIndexBuffer *m_nextIB;
		DX8IndexBufferClass *m_DX8IndexBuffer;
	};

	bool ReAcquireResources();

protected:
	W3DVertexBufferSlot *m_W3DVertexBufferSlots[MAX_FVF][512];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];
	W3DVertexBufferSlot m_W3DVertexBufferEmptySlots[4096];
	Int m_numEmptySlotsAllocated;
	W3DVertexBuffer m_W3DEmptyVertexBuffers[32];
	Int m_numEmptyVertexBuffersAllocated;
	W3DIndexBufferSlot *m_W3DIndexBufferSlots[1024];
	W3DIndexBuffer *m_W3DIndexBuffers;
	W3DIndexBufferSlot m_W3DIndexBufferEmptySlots[4096];
	Int m_numEmptyIndexSlotsAllocated;
	W3DIndexBuffer m_W3DEmptyIndexBuffers[32];
	Int m_numEmptyIndexBuffersAllocated;
};

bool W3DBufferManager::ReAcquireResources()
{
	for (int i = 0; i < MAX_FVF; ++i)
	{
		W3DVertexBuffer *vb = m_W3DVertexBuffers[i];
		while (vb)
		{
			vb->m_DX8VertexBuffer = new BfmeDynamicNativeVB(g_00DB5F30[vb->m_format], (unsigned short)vb->m_size, 0, 0);
			if (!vb->m_DX8VertexBuffer)
				return false;
			vb = vb->m_nextVB;
		}
	}
	W3DIndexBuffer *ib = m_W3DIndexBuffers;
	while (ib)
	{
		ib->m_DX8IndexBuffer = new DX8IndexBufferClass(ib->m_size, DX8IndexBufferClass::USAGE_DEFAULT);
		if (!ib->m_DX8IndexBuffer)
			return false;
		ib = ib->m_nextIB;
	}
	return true;
}
