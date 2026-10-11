// _LoopDeringBlock
// partial score=0.5 date=2026-10-11
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d8b40.md plus retail only.
// No decoder source was consulted.
//
// LoopDeringBlock (retail 0x001D8B40, 655 bytes, unreferenced): in-place
// adaptive smoothing of a width by height block, a horizontal pass over each
// row and then a vertical pass over each column, both staged in a 16-byte
// stack buffer.
extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

struct DecoderLoopDering
{
	unsigned char m_pad0000[0x453C];
	unsigned int m_threshold[256]; // 0x453C
};

extern "C" void __cdecl LoopDeringBlock(DecoderLoopDering *decoder, unsigned char *block,
	unsigned int stride, unsigned int width, unsigned int height)
{
	unsigned char buffer[16];
	unsigned char lowest = 0xff;
	unsigned char highest = 0;
	unsigned char *scan = block;
	unsigned int x;
	unsigned int y;
	int threshold;
	unsigned int a;
	unsigned int b;
	int s = (int)stride;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			unsigned char value = *scan;
			if (value < lowest)
				lowest = value;
			if (value > highest)
				highest = value;
			scan++;
		}
		scan += stride - width;
	}
	a = decoder->m_threshold[highest];
	b = decoder->m_threshold[255 - lowest];
	threshold = (int)(b > a ? b : a);
	threshold += (highest - lowest) >> 5;

	{
		unsigned char *row = block;
		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				int center = row[x];
				int right = row[x + 1];
				int left = row[x - 1];
				int sum = center * 2;
				int dr = center - right;
				int dl = center - left;
				if (dr < 0) dr = -dr;
				if (dl < 0) dl = -dl;
				sum += (dl > threshold) ? center : left;
				sum += (dr > threshold) ? center : right;
				buffer[x] = (unsigned char)((sum + 2) >> 2);
			}
			memcpy(row, buffer, width);
			row += stride;
		}
	}
	{
		unsigned char *column = block;
		for (x = 0; x < width; x++) {
			unsigned char *p = column;
			for (y = 0; y < height; y++) {
				int center = p[0];
				int down = p[s];
				int up = p[-s];
				int sum = center * 2;
				int dd = center - down;
				int du = center - up;
				if (dd < 0) dd = -dd;
				if (du < 0) du = -du;
				sum += (du > threshold) ? center : up;
				sum += (dd > threshold) ? center : down;
				buffer[y] = (unsigned char)((sum + 2) >> 2);
				p += s;
			}
			p = column;
			for (y = 0; y < height; y++) {
				*p = buffer[y];
				p += s;
			}
			column++;
		}
	}
}
