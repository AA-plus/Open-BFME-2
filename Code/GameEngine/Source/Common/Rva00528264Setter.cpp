// cl: /MD
// ?rva00528264@Rva00528264@@QAEXH@Z retail 0x00528264 15B
// Evidence: mov eax [esp+4]; cmp [ecx+0x1C]; je skip; mov [ecx+0x1C] eax; ret 4; callers 0x0052855E 0x0052827C
class Rva00528264
{
public:
	void rva00528264(int v);
private:
	char m_pad1C[0x1C];
	int m_1C;
};

void Rva00528264::rva00528264(int v)
{
	if (v != m_1C)
		m_1C = v;
}

// ?rva0052827A@Rva0052827AOwner@@QAEXH@Z @0x0052827A 7B: forwards to rva00528264 above through the pointer held at +0
// (load ecx; tail jump). Owner and name are address-derived; no referencing
// site was found in this pass.
class Rva0052827AOwner
{
public:
	void rva0052827A(int v);
private:
	Rva00528264 *m_target00;
};

void Rva0052827AOwner::rva0052827A(int v)
{
	m_target00->rva00528264(v);
}
