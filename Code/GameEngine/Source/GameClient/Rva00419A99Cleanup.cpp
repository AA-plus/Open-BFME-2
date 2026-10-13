// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?Rva00419A99Cleanup@@YAXXZ, retail 0x00419A99 31B.
// Free cleanup: if global g_00E030C8 != 0, call its slot-0 virtual with 0,
// operator-delete the returned pointer via rowed ??3@YAXPAX@Z, clear global.
// Evidence: mov ecx,[0x00E030C8]; test; je; mov eax,[ecx]; push 0; call [eax];
// push eax; call 0x0002FD60 row; and [0x00E030C8],0; pop ecx; ret. Caller
// at 0x002306A9 in 62B Catch body (free call, no args).
class Rva00419A99Item
{
public:
	virtual void *rvaSlot0(unsigned int arg);
};

Rva00419A99Item * g_00E030C8;	// retail RVA 0x00A030C8 (.data, 4 bytes), defined here: nothing else owns it
extern void __cdecl operator delete(void *p);

void __cdecl Rva00419A99Cleanup()
{
	Rva00419A99Item *p = g_00E030C8;
	if (p != 0)
	{
		void *q = p->rvaSlot0(0);
		operator delete(q);
		g_00E030C8 = 0;
	}
}
