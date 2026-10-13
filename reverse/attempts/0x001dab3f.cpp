// ?Rva001DAB3F@@YAXPAHPAVRva001DA112@@1@Z
// partial score=0.97 date=2026-10-13
// cl: /DNDEBUG /MD /EHsc /Oy- /Os
class Rva001DA112
{
public:
	void rva001DA112(int a, int b, char *p);
};
void Rva001DAB3F(int *range, Rva001DA112 *a, Rva001DA112 *b)
{
	int *r = range;
	a->rva001DA112(r[0], r[1], (char *)&range + 3);
	*(int *)b = 0;
	for (int *p = (int *)range[0]; p != (int *)r[1]; p += 2)
		*(int *)b += p[1];
}
