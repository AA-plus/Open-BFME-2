// ?Rva001DAB3F@@YAXPAHPAVRva001DA112@@1@Z
// partial score=0.85 date=2026-10-13
// cl: /DNDEBUG /MD /EHsc /Oy- /Os
// scratch for 0x001DAB3F
class Rva001DA112
{
public:
	void rva001DA112(int a, int b, char *p);
};

void Rva001DAB3F(int *range, Rva001DA112 *a, Rva001DA112 *b)
{
	a->rva001DA112(range[0], range[1], (char *)&range + 3);
	*(int *)b = 0;
	for (int *p = (int *)range[0]; p != (int *)range[1]; p += 2)
		*(int *)b += p[1];
}
