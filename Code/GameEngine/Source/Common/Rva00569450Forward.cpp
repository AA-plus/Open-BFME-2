// cl: /MD
//
// ?rva00569450@@YAHPAX00@Z @0x00569450 27B.
// __cdecl forwarder: bool out-param at [ebp-1] plus the three arguments go
// to the pinned 4-arg __cdecl 0x00569109, whose return passes through.
// Honest address-derived names; return-bool-vs-int unproven, int-sized.
struct Rva00569109Input;
struct Rva00569109Output;
struct Rva00569109IteratorTag;
Rva00569109Output *__cdecl Rva00569109RangeForward(Rva00569109Input *first, Rva00569109Input *last, Rva00569109Output *result, const Rva00569109IteratorTag &tag);

int __cdecl rva00569450(void *a, void *b, void *c)
{
	bool out;
	return (int)Rva00569109RangeForward((Rva00569109Input *)a, (Rva00569109Input *)b, (Rva00569109Output *)c, *(const Rva00569109IteratorTag *)&out);
}
