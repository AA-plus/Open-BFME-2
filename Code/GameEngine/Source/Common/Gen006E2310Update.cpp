// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva000982F9@Gen006E2310@@QAEXXZ retail 0x000982F9, 382 bytes: slot 10 of
// Gen006E2310's vtable 0x00BC8208 (slot 0 is its scalar deleting dtor
// 0x000982DD), the object the game client factory 0x0004C62D builds over
// the CloudEffect record class Rva009519B. Once per client frame it follows
// the global weather system's +0x10 state into its own +0xBC/+0xC0 pair
// (re-reading the cloud settings through virtual slot 14, 0x00214F14, when
// the state turns to 1), drops a pending light change at +0xC8 when the
// weather system's 0x003182CD check fails (restoring the scene light from
// +0xE0 and the shadow colour from +0xF8 when the record's +0x5C flag is
// set, then resetting the scene through 0x0006E605), steps the +0xC4 fade
// level down to 0 or up to 0xFF while the 0x00DB47EC mode is 2, and ends in
// the cloud/thunder update 0x000953B3.
//
// Its own unit, not Gen006E2310Ctor.cpp: that unit links today, and the two
// unrowed callees 0x0006E605 and 0x000953B3 (pinned) would stop it linking.
//
// Target facts: boundary, vtable slot, callees, globals, member offsets and
// store order are from retail. The member names and the method name are
// address-derived; the receivers of 0x0006E5C8 and 0x0006E605 are the scene
// pointer W3DDisplay::m_3DScene (VA 0x00DE1B34) that each call loads into ecx.

class GameClient
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual unsigned int getFrame();
};
extern GameClient *TheGameClient;

// The weather system's check 0x003182CD, rowed under an address-derived owner.
class Rva003182CD
{
public:
	unsigned char rva003182CD();
};

// The weather system's state word at +0x10.
class GlobalWeatherSystem
{
public:
	char m_pad[0x10];
	int m_state;
};
extern GlobalWeatherSystem *TheGlobalWeatherSystem;

class W3DShadowManager
{
public:
	int m_00;
	unsigned int m_shadowColor;
};
extern W3DShadowManager *TheW3DShadowManager;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RTS3DScene
{
public:
	void rva0006E5C8(Vector3 *src);
	void rva0006E605(Vector3 *src, bool flag);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

extern int g_Va00DB47EC;

// The CloudEffect record class (Rva009519BCtor.cpp), only as a base here;
// the +0x5C byte is the one this body tests.
class Rva009519B
{
public:
	virtual ~Rva009519B();
	// Slot 14, 0x00214F14 (Rva00214F14Init.cpp), as the call reaches it.
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13();
	virtual void rva00214F14();
protected:
	unsigned char m_04[0x5C - 4];
	unsigned char m_5C;
	unsigned char m_5D[0xBC - 0x5D];
};

struct Gen006E2310Triple
{
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	float X;
	float Y;
	float Z;
};

class Gen006E2310 : public Rva009519B
{
public:
	void rva000982F9();
	void rva000953B3();

private:
	int m_BC;
	int m_C0;
	int m_C4;
	bool m_C8;
	int m_CC;
	float m_D0;
	Gen006E2310Triple m_D4;
	Gen006E2310Triple m_E0;
	Gen006E2310Triple m_EC;
	unsigned int m_F8;
	int m_FC;
	int m_100;
	int m_104;
};

void Gen006E2310::rva000982F9()
{
	int frame = TheGameClient->getFrame();
	bool sameFrame = false;
	if (m_100 == frame)
		sameFrame = true;
	m_100 = frame;
	if (sameFrame)
		return;

	int state = TheGlobalWeatherSystem->m_state;
	if (state == 1) {
		if (m_BC != 1) {
			rva00214F14();
			m_C0 = 1;
			m_BC = 1;
		}
	} else if (m_BC == 1) {
		m_C0 = 3;
		m_BC = state;
	}

	unsigned char keep = TheGlobalWeatherSystem ? ((Rva003182CD *)TheGlobalWeatherSystem)->rva003182CD() : 0;
	if (!keep && m_C8) {
		m_C8 = false;
		m_CC = 0;
		m_D0 = 0.0f;
		m_104 = 0;
		m_D4.Set(0.0f, 0.0f, 0.0f);
		if (m_5C) {
			W3DDisplay::m_3DScene->rva0006E5C8((Vector3 *)&m_E0);
			if (TheW3DShadowManager)
				TheW3DShadowManager->m_shadowColor = m_F8;
		}
		W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, true);
		m_E0.Set(0.0f, 0.0f, 0.0f);
		m_EC.Set(0.0f, 0.0f, 0.0f);
	}

	if (g_Va00DB47EC == 2) {
		if (m_C0 == 1) {
			if (--m_C4 <= 0) {
				m_C4 = 0;
				m_C0 = 2;
			}
		} else if (m_C0 == 3) {
			if (++m_C4 >= 0xff) {
				m_C4 = 0xff;
				m_C0 = 0;
			}
		}
	}
	rva000953B3();
}
