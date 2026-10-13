// ?rva0051E96B@Rva0051E96B@@UAEMH@Z @0x0051E96B, 103 bytes.
// Target evidence: virtual slot 1 at 0x00867270 (sibling slot at 0x00867278
// rowed 0x0051E9D2); bounds an index against 20-byte records; switch on
// selector with cases 0,1,2,4 (3 missing, like sibling's missing 2).
// Record layout from retail loads: int +0x04, float +0x08, shorts +0x0C/+0x0E.
// Array pad 0x14 from begin/end offsets (sibling uses 0x20).
// cl: /O1 /arch:SSE /G7
struct Rva0051E96BRecord
{
	int m00;
	int m04;
	float m08;
	short m0C;
	short m0E;
	char mPad10[0x14 - 0x10];
};

struct Rva0051E96BArray
{
	char pad[0x14];
	char *begin;
	char *end;
};

class Rva0051E96B
{
public:
	virtual float rva0051E96B(int index);

private:
	Rva0051E96BArray *m_array;
	int m_selector;
};

float Rva0051E96B::rva0051E96B(int index)
{
	if (index >= 0)
	{
		Rva0051E96BArray *array = m_array;
		char *beginRef = array->begin;
		int count = (array->end - array->begin) / 20;
		if ((unsigned)index <= (unsigned)count)
		{
			Rva0051E96BRecord *record = (Rva0051E96BRecord *)(array->begin + index * 20);
			int selector = m_selector;
			switch (selector)
			{
			case 0:
				return record->m0C;
			case 1:
				return record->m0E;
			case 2:
				return (float)record->m04;
			case 4:
				return record->m08;
			}
		}
	}
	return 0.0f;
}
