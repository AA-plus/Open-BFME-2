// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
// ?Has_Color_Array@MeshMatDescClass@@QAE_NH@Z, retail 0x00187F70 (14 bytes plus 2 padding), the header inline
// between the rowed Has_UV (0x00187F50) and Has_Texture_Data (0x00187F80): whether the
// per-vertex colour array (+0x50) of the given index is present, as in Zero Hour meshmatdesc.h.
class VertexMaterialClass;

class MeshMatDescClass
{
public:
	bool Has_Color_Array(int array);
	void rva00188010(int pass, int value);

private:
	char m_pad0[0x50];
	unsigned int *ColorArray[2];
	int m_perPass58[4];
	char m_pad1[0x118 - 0x68];
};

bool MeshMatDescClass::Has_Color_Array(int array)
{
	return ColorArray[array] != 0;
}

// ?rva00188010@MeshMatDescClass@@QAEXHH@Z, retail 0x00188010 (15 bytes, RET 8), the inline
// placed after Has_Texture_Data's neighbours: stores a per-pass value into the four-entry
// array at +0x58. Which per-pass source it is is not established, so the name is address-derived.
void MeshMatDescClass::rva00188010(int pass, int value)
{
	m_perPass58[pass] = value;
}
