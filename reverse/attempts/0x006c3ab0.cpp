// ?rva006C3AB0@GeneralAllocatorDebug@@QAEPAXPAXGPBXIH@Z
// partial score=0.9 date=2026-10-13
// ?rva006C3AB0@GeneralAllocatorDebug@@QAEPAXPAXGPBXIH@Z
// partial score=0.9 date=2026-10-13
// ?rva006C3AB0@GeneralAllocatorDebug@@QAEPAXPAXGPBXIH@Z
// partial score=0.9 date=2026-10-11
// cl: /O2 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva006C3AB0@GeneralAllocatorDebug@@QAEPAXPAXGPBXIH@Z @ 0x006C3AB0 514B, ret 0x14
//
// Debug-allocator setter that stores one tagged debug-data field for a
// block: (block, 16-bit field id, data, length, location). Under the scoped
// +0x4E4 lock, location 2 means "choose": field id 0xB always goes inline,
// any other id takes the allocator default at +0x67C. Location 0 writes the
// field into the block's own trailing space (usable size less eight) through
// 0x006C20A0. Otherwise, if external records are enabled (+0x680), the
// block's record slot is found in the hash at +0x684 (0x006C1850). An
// existing record (16-bit total size first) is searched for the id
// (0x006C2010); when absent it is regrown by length + 4 through 0x006C3940,
// the old record copied to the new block's tail and freed (0x006C1A50). A
// missing record is created with length + 8 bytes and a zero terminator word.
// The field is then written through 0x006C20A0; a record this call created is
// released again if that write fails. Returns 0x006C20A0's result, or null.
//
// Evidence: retail body, its callees' rows, and WorldBuilder's unoptimized
// twin at 0x0070E3B0 (same control flow plus "dataLength < UINT16_MAX" and
// "bResult" asserts that retail drops; WB's fields sit eight bytes later).
// The original names are not established; the name is address-derived.

#include <string.h>

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva006C1850
{
public:
	bool rva006C1850(unsigned key, void **value);
};

class Rva006C1A50Owner
{
public:
	void rva006C1A50(int block);
};

class Rva006C39F0Owner
{
public:
	void *rva006C3940Alloc(unsigned size);
};

class GeneralAllocatorDebug
{
public:
	void *rva006C3AB0(void *block, unsigned short id, const void *data, unsigned length, int location);
	void *rva006C20A0(void *field, unsigned space, unsigned short id, const void *data, unsigned length);
	void *rva006C2010Run6(void *field, unsigned space, unsigned short id, void *a, unsigned b, unsigned *found);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x67c - 0x4e4 - 4];
	int m_defaultLocation;
	bool m_externalRecords;
	unsigned char m_pad2[3];
	Rva006C1850 m_records;
};

class Rva006C3AB0Guard
{
public:
	Rva006C3AB0Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva006C3AB0Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}
private:
	Rva00030DD0Lock *m_lock;
};

void *GeneralAllocatorDebug::rva006C3AB0(void *block, unsigned short id, const void *data, unsigned length, int location)
{
	Rva006C3AB0Guard guard(m_lock);
	void *result = 0;

	if (location == 2) {
		if (id == 0xb)
			location = 0;
		else
			location = m_defaultLocation;
	}

	if (location == 0) {
		unsigned n = ((unsigned *)block)[-1];
		unsigned usable = !(n & 2) ? (n & 0x7ffffff8) + 4 : (n & 0x7ffffff8);
		result = rva006C20A0(block, usable - 8, id, data, length);
	} else if (m_externalRecords) {
		unsigned short **records = 0;
		if (m_records.rva006C1850((unsigned)block, (void **)&records)) {
			bool created = false;
			unsigned short *record = *records;
			unsigned short size;
			if (record != 0) {
				size = *record;
				unsigned grown;
				if (rva006C2010Run6(record + 1, size - 2, id, 0, 0, &grown) == 0) {
					grown = size + length + 4;
					unsigned short *bigger = (unsigned short *)((Rva006C39F0Owner *)this)->rva006C3940Alloc(grown);
					if (bigger != 0) {
						memcpy((char *)bigger + grown - size, record, size);
						((Rva006C1A50Owner *)this)->rva006C1A50((int)record);
						record = bigger;
						size = (unsigned short)grown;
						*record = size;
						*records = record;
						created = true;
					}
				}
			} else {
				size = (unsigned short)(length + 8);
				record = (unsigned short *)((Rva006C39F0Owner *)this)->rva006C3940Alloc(size);
				if (record != 0) {
					*(unsigned short *)((char *)record + size - 2) = 0;
					*record = size;
					*records = record;
					created = true;
				}
			}
			if (record != 0) {
				result = rva006C20A0(record + 1, size - 2, id, data, length);
				if (result == 0 && created)
					((Rva006C1A50Owner *)this)->rva006C1A50((int)record);
			}
		}
	}
	return result;
}
