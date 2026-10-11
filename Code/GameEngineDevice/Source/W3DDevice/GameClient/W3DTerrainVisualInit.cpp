// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ?init@W3DTerrainVisual@@UAEXXZ, retail 0x00091AEA..0x00091CA7 (445 bytes,
// EH): BFME2's W3DTerrainVisual::init. Under the DX8 device lock it runs the
// base init (the shared bare return 0x000B3FD0), creates the height-map
// render object (0x393C bytes, constructor 0x000E3BFE(false); slot 121 with
// (2, 0)) and publishes it as TheTerrainRenderObject, the terrain tracks
// system (0x28 bytes, constructor 0x00084CA5, init 0x00084D01 with the 3D
// scene), TheW3DShadowManager (constructor 0x0009A710, then 0x0009A254), the
// water render object (0x264 bytes, constructor 0x00082329; 0x0007FC38 with
// TheWritableGlobalData's water height, size and type, then placed at its
// water position through render-object slot 22) and the smudge manager
// (constructor 0x000A60F0, slot 1). Unless 0x00DFE7A8 is set or the water
// type is 1 the water object joins the scene (slot 2). Views carry only what
// this body touches; global spellings are the data ledger's.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class SceneClass;
class RTS3DScene;

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

struct Vector3
{
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class Rva00091AEARenderObj
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21)
#undef V
	virtual void Set_Position(const Vector3 &position);	// slot 22
};

class Rva00091AEAScene
{
public:
	virtual void v0();
	virtual void v1();
	virtual void Add_Render_Object(Rva00091AEARenderObj *obj);	// slot 2
};

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

// The height-map render object.
class Rva000E3BFE
{
public:
	Rva000E3BFE(bool flag);
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114) V(115) V(116) V(117) V(118) V(119)
	V(120)
#undef V
	virtual void slot121(int a, int b);
private:
	unsigned char m_pad04[0x393C - 4];
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// The terrain tracks system.
class Rva00084CA5
{
public:
	Rva00084CA5();
private:
	unsigned char m_data[0x28];
};

class Rva00084C05System
{
public:
	void init(SceneClass *scene);
};

class TerrainTracksRenderObjClassSystem;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;

class W3DShadowManager
{
public:
	W3DShadowManager();
	void rva0009A254();
private:
	unsigned char m_data[0x18];
};

extern W3DShadowManager *TheW3DShadowManager;

enum WaterType { WATER_TYPE_DEFAULT };

// The water render object; its render-object part sits at +4.
class Rva00082329
{
public:
	Rva00082329();
	int m_00;
	Rva00091AEARenderObj m_renderObj;		// +0x04
private:
	unsigned char m_pad08[0x264 - 8];
};

class Rva0007FC38
{
public:
	int rva0007FC38(float waterHeight, float waterSizeX, float waterSizeY, SceneClass *scene, WaterType type);
};

extern void *W3DGCData00DE2000;

class W3DSmudgeManager
{
public:
	W3DSmudgeManager();
	virtual void v0();
	virtual void init();				// slot 1
private:
	unsigned char m_pad04[0x44 - 4];
};

class BfmeB991;
extern BfmeB991 *g_bfmeB991;

extern unsigned int g_Va00DFE7A8;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva00091AEAGlobalView
{
	unsigned char m_pad00[0x6C];
	float m_waterPositionX;				// +0x6C
	float m_waterPositionY;				// +0x70
	float m_waterPositionZ;				// +0x74
	float m_waterExtentX;				// +0x78
	float m_waterExtentY;				// +0x7C
	WaterType m_waterType;				// +0x80
};

class W3DTerrainVisual
{
public:
	virtual void init();
private:
	unsigned char m_pad04[0x10 - 4];
	Rva000E3BFE *m_terrainRenderObject;		// +0x10
	Rva00082329 *m_waterRenderObject;		// +0x14
};

void W3DTerrainVisual::init()
{
	BFMEDX8DeviceLock lock;
	((Rva000B3FD0 *)this)->rva000B3FD0();

	m_terrainRenderObject = new Rva000E3BFE(false);
	m_terrainRenderObject->slot121(2, 0);
	TheTerrainRenderObject = (BaseHeightMapRenderObjClass *)m_terrainRenderObject;

	Rva00084CA5 *tracks = new Rva00084CA5;
	TheTerrainTracksRenderObjClassSystem = (TerrainTracksRenderObjClassSystem *)tracks;
	((Rva00084C05System *)tracks)->init((SceneClass *)W3DDisplay::m_3DScene);

	TheW3DShadowManager = new W3DShadowManager;
	TheW3DShadowManager->rva0009A254();

	m_waterRenderObject = new Rva00082329;
	W3DGCData00DE2000 = m_waterRenderObject;
	Rva00091AEAGlobalView *data = (Rva00091AEAGlobalView *)TheWritableGlobalData;
	((Rva0007FC38 *)m_waterRenderObject)->rva0007FC38(data->m_waterPositionZ, data->m_waterExtentX, data->m_waterExtentY,
		(SceneClass *)W3DDisplay::m_3DScene, data->m_waterType);
	data = (Rva00091AEAGlobalView *)TheWritableGlobalData;
	Vector3 position(data->m_waterPositionX, data->m_waterPositionY, data->m_waterPositionZ);
	m_waterRenderObject->m_renderObj.Set_Position(position);

	W3DSmudgeManager *smudge = new W3DSmudgeManager;
	g_bfmeB991 = (BfmeB991 *)smudge;
	smudge->init();

	if (!*(unsigned char *)&g_Va00DFE7A8 && ((Rva00091AEAGlobalView *)TheWritableGlobalData)->m_waterType != 1 && m_waterRenderObject)
		((Rva00091AEAScene *)W3DDisplay::m_3DScene)->Add_Render_Object(&m_waterRenderObject->m_renderObj);
}
