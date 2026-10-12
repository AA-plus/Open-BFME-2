// cl: /I. /O1 /MD /EHsc /DNDEBUG /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 clean W3DShadow.cpp 874e38488c semantic lead; target layout/scale
// and four allocations come from native9A710..9A8D3 and WB777D40.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "reference/shims/bfme_colmathaabox/wwmath.h"
#include "reference/shims/bfme_colmathaabox/vector3.h"
// Native ctor callback47A6A9 is empty; native iterator initializes one12B
// coordinate at receiver+C. Element original type unknown; this address view
// inherits canonical Coord3D storage and emits the proven3B ICF callback.
struct Rva0009A710LightPosition : Coord3D { __declspec(noinline) Rva0009A710LightPosition(); };
Rva0009A710LightPosition::Rva0009A710LightPosition() {}
class Rva000F1A32 {public:Rva000F1A32();private:char body[12];};
class Rva005D2575 {
public:Rva005D2575();private:char body[0x1c];
};
class Rva00108DBC {public:Rva00108DBC();bool rva00108DBC();private:char body[0x274];};
class Rva0007C50B {public:Rva0007C50B();private:char body[0x2c];};
class W3DVolumetricShadowManager;
class W3DProjectedShadowManager;
class Rva00108660ResourceManager;
class Rva0007DA23ResourceManager;
class AudioManager0029E159;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern AudioManager0029E159 *g_00DEC2D4;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
struct ShadowTerrainLight {float x,y,z;};
class GlobalData {public:char prefix[0x920];ShadowTerrainLight light[1];};
extern GlobalData *TheWritableGlobalData;
class W3DGameClientShadowShim {
public:void setLightPosition(int,float,float,float);
};

// Target evidence: retail 0x0009A383 checks four global pointers in order and
// calls each manager only when its pointer is non-null. The 91-byte body is
// byte-verified.
// Donor evidence: Zero Hour W3DShadow.cpp gives the same aggregate purpose
// and names its first two checks as volumetric and projected shadow managers.
// Inference: the target function keeps that owner and appends two checks. The
// latter helpers retain address-derived names because their owners are unknown.

typedef bool Bool;

class W3DVolumetricShadowManager
{
public:
	Bool ReAcquireResources();
};

class RenderInfoClass;

class W3DProjectedShadowManager
{
public:
	Bool ReAcquireResources();
	int rva0010DF33(RenderInfoClass &rinfo);
};

class Rva00108660ResourceManager
{
public:
	Bool ReAcquireResources();
};

class Rva0007DA23ResourceManager
{
public:
	Bool ReAcquireResources();
};

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
// TheW3DVolumetricShadowManager: matched references place it at VA 0xdebcd8 (zero-filled .bss).
W3DVolumetricShadowManager * TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
// TheW3DProjectedShadowManager: matched references place it at VA 0xdec2cc (zero-filled .bss).
W3DProjectedShadowManager * TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
// Rva00DE1FF8Manager: matched references place it at VA 0xde1ff8 (zero-filled .bss).
Rva0007DA23ResourceManager * Rva00DE1FF8Manager;

class W3DShadowManager {
public:W3DShadowManager(); Bool ReAcquireResources(); Bool rva0009A254();
 void rva0009A348(RenderInfoClass &rinfo);
private:
 bool m_isShadowScene;char padding[3];unsigned m_shadowColor;
 int m_stencilShadowMask;Rva0009A710LightPosition m_lightPos[1];
};

Bool W3DShadowManager::ReAcquireResources()
{
	Bool result = true;
	if (TheW3DVolumetricShadowManager && !TheW3DVolumetricShadowManager->ReAcquireResources())
		result = false;
	if (TheW3DProjectedShadowManager && !TheW3DProjectedShadowManager->ReAcquireResources())
		result = false;
	if (Rva00DEC2D8Manager && !Rva00DEC2D8Manager->ReAcquireResources())
		result = false;
	if (Rva00DE1FF8Manager && !Rva00DE1FF8Manager->ReAcquireResources())
		result = false;
	return result;
}

// ?Rva00DEC2D8Manager@@3PAVRva00108660ResourceManager@@A: matched references place it at VA 0xdec2d8; also referenced as ?R2Ptr01306DF0@@3PAVR2GlobalReceiver@@A.
Rva00108660ResourceManager * Rva00DEC2D8Manager = 0;

W3DShadowManager::W3DShadowManager() {
 m_shadowColor=0x7fa0a0a0;
 m_isShadowScene=false;
 m_stencilShadowMask=0;
 Vector3 lightRay(-TheWritableGlobalData->light[0].x,
 -TheWritableGlobalData->light[0].y,-TheWritableGlobalData->light[0].z);
 lightRay.Normalize();
 Vector3 scaled=lightRay*10000000.0f;
 Coord3D *out=&m_lightPos[0];out->x=scaled.X;out->y=scaled.Y;out->z=scaled.Z;
 // Existing ledger provider names are retained; the physical targets,
 // not the historical class spellings, identify each submanager here.
 TheW3DVolumetricShadowManager=(W3DVolumetricShadowManager*)new Rva000F1A32;
 TheW3DProjectedShadowManager=(W3DProjectedShadowManager*)new Rva005D2575;
 Rva00108DBC *projected=new Rva00108DBC;
 Rva00DEC2D8Manager=(Rva00108660ResourceManager*)projected;
 g_00DEC2D4=(AudioManager0029E159*)projected;
 Rva00DE1FF8Manager=(Rva0007DA23ResourceManager*)new Rva0007C50B;
 ((W3DGameClientShadowShim*)this)->setLightPosition(0,m_lightPos[0].x,m_lightPos[0].y,m_lightPos[0].z);
}

// Retail 0x0009A254 (121 bytes), the guarded re-acquire its caller 0x00091AEA
// uses: the volumetric shadows only when their slot predicate (0x0050B5C6)
// holds, the projected shadows through 0x001076EE (pinned by address), the
// 0x00DEC2D8 manager when 0x00108DBC holds, and the 0x00DE1FF8 manager's
// 0x0007B6EC check; any failure makes the result false.
class Rva0050B5C6 { public: bool rva0050B5C6(); };
class Rva001076EE { public: bool rva001076EE(); };
class Rva0007B6EC { public: unsigned char rva0007B6EC(); };
Bool W3DShadowManager::rva0009A254()
{
	Bool result = true;
	if (TheW3DVolumetricShadowManager && ((Rva0050B5C6 *)TheW3DVolumetricShadowManager)->rva0050B5C6() && !TheW3DVolumetricShadowManager->ReAcquireResources())
		result = false;
	if (TheW3DProjectedShadowManager && !((Rva001076EE *)TheW3DProjectedShadowManager)->rva001076EE())
		result = false;
	if (Rva00DEC2D8Manager && ((Rva00108DBC *)Rva00DEC2D8Manager)->rva00108DBC() && !Rva00DEC2D8Manager->ReAcquireResources())
		result = false;
	if (Rva00DE1FF8Manager && !((Rva0007B6EC *)Rva00DE1FF8Manager)->rva0007B6EC())
		result = false;
	return result;
}

// Retail 0x0009A348 (25 bytes), called from 0x00071606: when the 0x00DEC2D8
// manager exists and this frame is a shadow scene, it tail-calls that
// manager's renderShadows-style 0x0010DF33 with the caller's render info, the
// projected half of Zero Hour's DoShadows. The method name stays
// address-derived.
void W3DShadowManager::rva0009A348(RenderInfoClass &rinfo)
{
	if (Rva00DEC2D8Manager && m_isShadowScene)
		((W3DProjectedShadowManager *)Rva00DEC2D8Manager)->rva0010DF33(rinfo);
}
