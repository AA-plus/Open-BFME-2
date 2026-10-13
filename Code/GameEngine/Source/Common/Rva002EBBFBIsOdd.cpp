// cl: /MD
// ?Rva002EBBFBIsOdd@@YAEPAX@Z @0x002EBBFB 25B
// Free __cdecl unsigned char (void*) wrapping ?Rva002E9B31Get@@YAHPAX@Z parity test.
// Evidence: 12 callers pass single pointer and use result as bool for WorldToCell;
// retail cdq/idiv 2 plus dec/neg/sbb/inc is (Get(p)%2)==1; unblocks 0x002EBC14 etc.
int __cdecl Rva002E9B31Get(void *p);
unsigned char __cdecl Rva002EBBFBIsOdd(void *p)
{
	int v = Rva002E9B31Get(p) % 2;
	return (unsigned char)(v == 1 ? 1 : 0);
}
