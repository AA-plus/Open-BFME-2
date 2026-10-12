// cl: /O1 /arch:SSE /G7 /Ob0
// Complete18B RET4 output-buffer contract. Native56503D calls this body,
// then565048 pushes EAX as the next callee's first argument. The callee
// returns the supplied8B buffer after copying float10 and raw word14.
// Original receiver and explicit-output versus hidden aggregate-return
// spelling remain unknown; address-owned names expose physical behavior.
struct Rva00564BF6Out
{
	float m_00;
	int m_04;
};

class Rva00564BF6
{
public:
	Rva00564BF6Out *rva00564BF6(Rva00564BF6Out *out);
private:
	char m_pad[0x10];
	float m_10;
	int m_14;
};

Rva00564BF6Out *Rva00564BF6::rva00564BF6(Rva00564BF6Out *out)
{
	out->m_00 = m_10;
	out->m_04 = m_14;
	return out;
}
