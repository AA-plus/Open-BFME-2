// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0008FF84Create@@YGPAVRva0008FF3E@@PAX@Z @0x0008FF84 58B: factory creating Rva0008FF3E.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then the rowed ctor 0x0008FF3E with the
// void* argument; same new+ctor shape as the sibling factories (0x0008F78F and others). It is
// the draw factory installed by the W3D gadget creator slot at 0x0008FFE0.

class Rva0008FF3E
{
public:
	Rva0008FF3E(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva0008FF3E *__stdcall Rva0008FF84Create(void *context)
{
	return new Rva0008FF3E(context);
}
