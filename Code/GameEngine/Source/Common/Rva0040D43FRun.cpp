// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva0040D43FRun@@YAXPAVLivingWorldBattle@@@Z, retail 0x0040D43F, 46 bytes.
//
// Evidence: the stack callback temp at [ebp-0x10] stores vtable 0x00C394C8
// (the rowed 9-byte ctor ??0Rva0040CFFF@@QAE@XZ 0x0040CFFF), then the rowed
// LivingWorldBattle::rva003F498A (0x003F498A) is called with the temp. The
// EH prolog and state 0 need a destructible temp; an inline-empty virtual
// destructor supplies it without emitting a call on the normal path.

class Rva003F498ACallback;

class Rva0040CFFF
{
public:
	virtual void s0();
	virtual ~Rva0040CFFF() {}
};

class LivingWorldBattle
{
public:
	void rva003F498A(Rva003F498ACallback *callback);
};

class Rva003F468D;

class ArmySummarySystem
{
public:
	void rva0040D43F(Rva003F468D *arg);
};

void ArmySummarySystem::rva0040D43F(Rva003F468D *arg)
{
	Rva0040CFFF callback;
	((LivingWorldBattle *)arg)->rva003F498A((Rva003F498ACallback *)&callback);
}
