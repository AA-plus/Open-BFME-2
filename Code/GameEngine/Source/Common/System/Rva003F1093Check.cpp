// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX-
// ?rva003F1093@Rva003F1093@@QAE_NPAVCreateAHeroData@@PAH@Z @0x003F1093 61B:
// __thiscall bool check: hero+0x1c must equal this else *out=2 false;
// hero+0x20 must be nonzero else *out=1 false; else *out=0 true.
// Caller 0x003F1CB6 passes esi and null out. Sibling of Rva003F1C22Check.
class Rva004FC470 { public: void rva004FC470(bool); };
class CreateAHeroData : public Rva004FC470
{
public:
	char m_pad1C[0x1c];
	void *m_1C;
	int m_20;
	char unknown24[0x34 - 0x24];
	unsigned char m_x34;
};
class Rva003F1093
{
public:
	bool rva003F1093(CreateAHeroData *hero, int *out);
	void rva003F1CA2(CreateAHeroData *, bool);
private:
	char unknown00[0x17C];
	CreateAHeroData *activePlot;
	char unknown180[0x1A3 - 0x180];
	bool active;
};

class Rva003F11C7Listener { public: virtual void unknown00(); virtual void unknown04(); virtual void unknown08(); virtual void notify(void *, int); };
struct Rva003F1A25 { void rva003F1A25(void (Rva003F11C7Listener::*)(void *, int), void *, int); };
// Native3F1CA2..3F1CFE RET8 and WB1041330 read a byte boolean argument.
// Keep the exact61B CanDestroyBuilding view below in this unit: it preserves
// ECX, as the retail check does, eliminating a spurious receiver restore.
// The notification is the existing folded slot3 callback, not an animation
// method cast. Plot20/34 and region17C/1A3 roles come from native/WB evidence;
// original type and method names remain unresolved.
void Rva003F1093::rva003F1CA2(CreateAHeroData *hero, bool v)
{
    if (hero->m_20 != 0)
    {
        if (rva003F1093(hero, 0))
        {
            reinterpret_cast<Rva003F1A25 *>(this)->rva003F1A25(
                &Rva003F11C7Listener::notify,
                this, reinterpret_cast<int>(hero));
            bool b;
            if (hero->m_x34 == 0)
                b = false;
            else
            {
                b = true;
                if (hero->m_20 == 0)
                    b = false;
            }
            hero->rva004FC470(v);
            if (b)
            {
                active = false;
                activePlot = 0;
            }
        }
    }
}

bool Rva003F1093::rva003F1093(CreateAHeroData *hero, int *out)
{
	if (hero->m_1C != this)
	{
		if (out)
			*out = 2;
		return false;
	}
	if (hero->m_20 == 0)
	{
		if (out)
			*out = 1;
		return false;
	}
	if (out)
		*out = 0;
	return true;
}
