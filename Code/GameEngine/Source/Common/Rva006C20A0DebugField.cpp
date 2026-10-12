// cl: /DNDEBUG /MD
//
// ?rva006C20A0@GeneralAllocatorDebug@@QAEPAXPAXIGPBXI@Z @ 0x006C20A0 261B, ret 0x14 (Ghidra 254 stops before the null-return epilogue)
//
// Writes one tagged debug-data field into a debug block: (block, block
// length, field id, data, data length). The block's last 16-bit word is the
// size of the field area, which grows down from it; each field is its data
// followed by a 16-bit id and a 16-bit data size. Walking down from the end,
// a field with the same id is overwritten in place when the data fits (the
// rest of the field zeroed) and its data address returned; when it does not
// fit the field is zeroed and null returned. Without a match, a new field is
// appended below the existing ones if the block has room for the data and
// its four-byte header, and the area size word grows by both; otherwise null.
// Null data only reserves the field. `this` is unused.
//
// Evidence: retail body, and WorldBuilder's unoptimized twin at 0x0070E670,
// whose asserts ("nDebugDataSize <= nDebugBlockLength", "dataLength <=
// nFieldSize", "pPosition == pPositionEnd", "((pPosition -
// kDebugRecordOverheadSize) - dataLength) >= pDebugBlock") give the control
// flow and the variable roles. The name is address-derived.

#include <string.h>

class GeneralAllocatorDebug
{
public:
	void *rva006C20A0(void *block, unsigned length, unsigned short id, const void *data, unsigned dataLength);
	static unsigned rva006C16D0(const void *chunk);
	void rva006C1710(int a, int b, int c);
	int rva006C1770(short option);
};

void *GeneralAllocatorDebug::rva006C20A0(void *block, unsigned length, unsigned short id, const void *data, unsigned dataLength)
{
	char *position = (char *)block + length - 2;
	unsigned short *sizeWord = (unsigned short *)position;
	unsigned short dataSize = *(unsigned short *)position;
	const char *positionEnd = position - dataSize;

	while (position > positionEnd) {
		position -= 2;
		const unsigned short fieldSize = *(unsigned short *)position;
		position -= 2;
		const unsigned short fieldId = *(unsigned short *)position;
		position -= fieldSize;

		if (fieldId == id) {
			if (dataLength <= fieldSize) {
				if (data) {
					memcpy(position, data, dataLength);
					if (dataLength < fieldSize)
						memset(position + dataLength, 0, fieldSize - dataLength);
				}
				return position;
			}
			memset(position, 0, fieldSize);
			return 0;
		}
	}

	if (position - 4 - dataLength >= (char *)block) {
		position -= 2;
		*(unsigned short *)position = (unsigned short)dataLength;
		position -= 2;
		*(unsigned short *)position = id;
		position -= dataLength;
		if (data)
			memcpy(position, data, dataLength);
		dataSize = (unsigned short)(dataSize + dataLength + 4);
		*sizeWord = dataSize;
		return position;
	}
	return 0;
}

// Three Ghidra-unlisted debug-allocator leaves near 0x006C1700, address-named
// with only the offsets they touch (no layout is claimed):
// 0x006C16D0 (26B, static): a chunk's usable size from its +4 header word,
// masked to 0x7FFFFFF8, plus 4 unless the mapped bit (2) is set.
unsigned GeneralAllocatorDebug::rva006C16D0(const void *chunk)
{
	unsigned header = ((const unsigned *)chunk)[1];
	if (!(header & 2))
		return (header & 0x7FFFFFF8) + 4;
	return header & 0x7FFFFFF8;
}

// 0x006C1710 (24B): stores three values at +0x14/+0x18/+0x1C.
void GeneralAllocatorDebug::rva006C1710(int a, int b, int c)
{
	int *fields = (int *)((char *)this + 0x14);
	fields[0] = a;
	fields[1] = b;
	fields[2] = c;
}

// 0x006C1770 (22B): option 11 reads as 0, any other as the +0x67C word.
int GeneralAllocatorDebug::rva006C1770(short option)
{
	if (option == 11)
		return 0;
	return *(int *)((char *)this + 0x67C);
}
