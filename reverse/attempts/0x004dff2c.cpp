// ?rva004DFF2C@Rva004E00BAOwner@@QAEXPAVObject@@@Z
// partial score=0.77 date=2026-10-13
// cl: /DNDEBUG /MD /EHs /Oy-
#pragma optimize("s",on)
// ?rva004DFF2C@Rva004E00BAOwner@@QAEXPAVObject@@@Z, RVA 0x004DFF2C, 306 bytes RET4.
// WB 0x129C960 (730B) gives the template shape: zero each item flag over the vector
// at this+0x10, look the object up with the rowed 0x004DFE4F, else allocate a 0x28
// item, set it up through the matched 0x00281A76 ctor with this->vslot0(), insert it
// with the pinned 0x004DFCE6, push it on the vector; if the object was found, walk the
// flagged items, move each flagged item's +0x1C list through the pinned insert into the
// found item, erase the list, delete the item and erase it from the vector.
// Callees: 0x4DFE4F row, 0x4DFCB0 row (vector<const ModuleData*>::push_back),
// 0x31BD55 row (vector<void*>::erase(first,last)), 0x1FF51F row (erase(pos)),
// 0x281A76 row (item ctor), 0x4DFCE6 pin, free 0x30830, operator delete 0x2FD60.

extern "C" void __cdecl free(void *block);

class Object;
class ModuleData;

typedef void *(*DefenseInsertFn)(void *);

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	T *erase(T *first, T *last);
	T *erase(T *pos);
	void push_back(const T &value);
	~vector() { if (m_start) free(m_start); }
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};
}

// The 0x28-byte tree item; the matched ctor 0x00281A76 writes the float block.
class Rva00281A76
{
public:
	Rva00281A76(float value);
	unsigned char m_flag;			// +0x00
	unsigned char m_pad01[3];
	float m_f04;				// +0x04
	float m_f08;				// +0x08
	float m_f0C;				// +0x0C
	float m_f10;				// +0x10
	float m_f14;				// +0x14
	unsigned char m_pad18[4];
	_STL::vector<void *, _STL::allocator<void *> > m_list;	// +0x1C
};

class Rva004DFE4F
{
public:
	int rva004DFE4F(void *value);
};

class Rva004DFCE6
{
public:
	void rva004DFCE6(void *value, void *(*callback)(void *));
};

class Rva004E00BAOwner
{
public:
	virtual float slot0();			// +0x00 vtable
private:
	unsigned char m_pad04[0x0C];		// +0x04 object vector (the caller's, unused here)
	_STL::vector<void *, _STL::allocator<void *> > m_items;	// +0x10
	unsigned char m_pad1C[4];		// +0x1C
	DefenseInsertFn m_callback;		// +0x20
public:
	void rva004DFF2C(Object *object);
};

void Rva004E00BAOwner::rva004DFF2C(Object *object)
{
	typedef _STL::vector<void *, _STL::allocator<void *> > VoidVector;
	typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ItemVector;

	VoidVector *items = &m_items;
	Rva00281A76 **begin = (Rva00281A76 **)items->m_start;
	Rva00281A76 **end = (Rva00281A76 **)items->m_finish;
	for (Rva00281A76 **slot = begin; slot != end; ++slot)
		*(unsigned char *)*slot = 0;

	Rva00281A76 *item = (Rva00281A76 *)((Rva004DFE4F *)this)->rva004DFE4F(object);
	if (!item)
	{
		Rva00281A76 *node = new Rva00281A76(slot0());
		((Rva004DFCE6 *)node)->rva004DFCE6(object, m_callback);
		((ItemVector *)&m_items)->push_back(*(const ModuleData *const *)&node);
	}
	else
	{
		Rva00281A76 **slot = begin;
		Rva00281A76 *found = 0;
		while (!found && slot != end)
		{
			Rva00281A76 *candidate = *slot;
			if (candidate->m_flag)
				found = candidate;
			++slot;
		}
		while (slot != end)
		{
			Rva00281A76 *current = *slot;
			if (current->m_flag)
			{
				void **listSlot = (void **)current->m_list.m_start;
				for (; listSlot != (void **)current->m_list.m_finish; ++listSlot)
					((Rva004DFCE6 *)found)->rva004DFCE6(*listSlot, m_callback);
				current->m_list.erase((void **)current->m_list.m_start, (void **)current->m_list.m_finish);
				if (current->m_list.m_start)
					free(current->m_list.m_start);
				::operator delete(current);
				slot = (Rva00281A76 **)items->erase((void **)slot);
				end = (Rva00281A76 **)items->m_finish;
			}
			else
			{
				++slot;
			}
		}
	}
}
