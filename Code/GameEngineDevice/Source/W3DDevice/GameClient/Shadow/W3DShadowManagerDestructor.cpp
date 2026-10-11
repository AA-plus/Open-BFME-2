// cl: /O1 /MD /EHsc /DNDEBUG
// ??1Rva009A500@@UAE@XZ, retail 0x0009A500..0x0009A587 (135 bytes):
// by shape BFME2's W3DShadowManager::~W3DShadowManager (address-derived name
// kept to agree with the pin its scalar deleting destructor 0x00091ACE
// calls). As in Zero Hour it deletes and clears the projected and volumetric
// shadow managers; BFME2 then ::deletes the 0x00DEC2D8 resource manager,
// clears 0x00DEC2D4 (Zero Hour's TheProjectedShadowManager slot) and deletes
// the 0x00DE1FF8 resource manager (rowed destructor 0x0007C0F5). The class
// stores no table of its own (novtable view). The global spellings are the
// data ledger's (see W3DShadowManagerReAcquire.cpp).
class W3DVolumetricShadowManager
{
public:
	~W3DVolumetricShadowManager();
};

class W3DProjectedShadowManager;
class Rva00108660ResourceManager
{
public:
	virtual ~Rva00108660ResourceManager();
};
class Rva0007DA23ResourceManager;
class AudioManager0029E159;

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern AudioManager0029E159 *g_00DEC2D4;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;

// The projected shadow manager's destructor (rowed 0x001076E9).
class Rva0009A200
{
public:
	~Rva0009A200();
};

// The 0x00DE1FF8 manager's destructor (rowed 0x0007C0F5).
class Rva0007BAD6
{
public:
	~Rva0007BAD6();
};

class __declspec(novtable) Rva009A500
{
public:
	virtual ~Rva009A500();
};

Rva009A500::~Rva009A500()
{
	delete (Rva0009A200 *)TheW3DProjectedShadowManager;
	TheW3DProjectedShadowManager = 0;

	delete TheW3DVolumetricShadowManager;
	TheW3DVolumetricShadowManager = 0;

	::delete Rva00DEC2D8Manager;
	Rva00DEC2D8Manager = 0;
	g_00DEC2D4 = 0;

	delete (Rva0007BAD6 *)Rva00DE1FF8Manager;
	Rva00DE1FF8Manager = 0;
}
