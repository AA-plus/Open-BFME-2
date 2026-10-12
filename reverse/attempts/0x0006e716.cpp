// ?updateFixedLightEnvironments@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.98 date=2026-10-12
// ?updateFixedLightEnvironments@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.98 date=2026-10-12
// Intended home: new unit Code/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DSceneUpdateFixedLightEnvironments.cpp (retail builds this body at /O1,
// EBP frame; W3DScene.cpp is overridden to /O2), and the present-unmatched
// Zero Hour copy in W3DScene.cpp must then be deleted (duplicate definition).
// State: full 1061/1061 bytes; frame, loop, LOD scale and env scaling match.
// Blockers:
//  1. LightEnvironmentClass::Reset must be declared plain out of line (an
//     inline wrapper over the rowed placeholder Gen_0094AC70::bfmeSetPair
//     loses the early LEA EDI and is 2 bytes short), so
//     ?Reset@LightEnvironmentClass@@QAEXABVVector3@@0@Z needs to resolve to
//     0x0013F620: rename that placeholder row (Bfme5EightyEight.cpp) or admit
//     a pin.
//  2. Scratch-diffuse block (~6E954): retail loads m_scratchLight (+0x140)
//     before the colour and does ADD EAX,EBX before the stores; cl loads it
//     after. Tried Scale-return chaining, k*v, local scratch, member-wise.
//  3. First environment ambient scale (~6EA0E): retail X*s.X for all three;
//     cl emits s.X*X for X only (second/third environments match).
// Fogged ambient needs foggedLightFrac * Get_Ambient_Light() (fixed here).
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?updateFixedLightEnvironments@RTS3DScene@@IAEXAAVRenderInfoClass@@@Z,
// retail 0x0006E716..0x0006EB3B (1061 bytes, RET 4). Zero Hour's
// RTS3DScene::updateFixedLightEnvironments as Open-BFME-1 reconstructed it
// for BFME (game/.../W3DScene.cpp: three light environments, the infantry
// lights feeding the third, the scratch light carrying fogged copies), with
// BFME 2's additions read from retail: below static LOD 2 (the owned
// g_Va00DB5FA0) every light's diffuse is scaled by the global data's
// low-LOD light scale (+0x944) while it is added and then restored, the
// fogged copies take the scaled diffuse, and each environment's ambient
// (+0x164) is scaled afterwards. BFME 2's scene keeps the lights at
// +0x130 (globals), +0x140 (scratch), +0x144 (infantry ambient), +0x150
// (infantry), +0x160 (count) and the environments at +0x164/+0x38C/+0x5B4;
// the fog fraction is the global data's byte +0xBE9 over +0xBE8. Retail
// builds this body at /O1 (EBP frame), unlike the /O2 rows of W3DScene.cpp.

typedef int Int;
typedef float Real;

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
	void Scale(const Vector3 &scale)
	{
		X *= scale.X;
		Y *= scale.Y;
		Z *= scale.Z;
	}
	friend Vector3 operator*(const Vector3 &a, Real k) { return Vector3(a.X * k, a.Y * k, a.Z * k); }
	friend Vector3 operator*(Real k, const Vector3 &a) { return Vector3(a.X * k, a.Y * k, a.Z * k); }

	Real X;
	Real Y;
	Real Z;
};

class Matrix3D;

#define PAD_VIRTUAL10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

// The RenderObjClass transform protocol: slot 20 validates the transform at
// +0x18, slot 21 sets it.
class RenderObjClass
{
public:
	PAD_VIRTUAL10(a) PAD_VIRTUAL10(b)
	virtual void Validate_Transform(void) const;		// slot 20
	virtual void Set_Transform(const Matrix3D &m);		// slot 21
	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *reinterpret_cast<const Matrix3D *>(Transform);
	}
protected:
	char m_pad04[0x18 - 0x04];
	char Transform[0x30];					// +0x18
};

class LightClass : public RenderObjClass
{
public:
	void Get_Ambient(Vector3 *color) const;
	void Get_Diffuse(Vector3 *color) const;
	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
private:
	char m_pad48[0xD4 - 0x48];
	Vector3 Ambient;					// +0xD4
	Vector3 Diffuse;					// +0xE0
};

class CameraClass : public RenderObjClass
{
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

// The environment's Reset is rowed under its placeholder spelling.
class BfmeVecHF;
class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *cameraPosition, const BfmeVecHF *ambient);
};

class LightEnvironmentClass
{
public:
	void Reset(const Vector3 &cameraPosition, const Vector3 &ambient);
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera);

	unsigned char m_flag;					// +0x00
	char m_pad01[0x164 - 0x01];
	Vector3 m_outputAmbient;				// +0x164
	char m_pad170[0x228 - 0x170];
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct SceneLightGlobalView
{
	char m_pad000[0x944];
	Real m_lowLODLightScaleRed;				// +0x944
	Real m_lowLODLightScaleGreen;
	Real m_lowLODLightScaleBlue;
	char m_pad950[0xBE8 - 0x950];
	unsigned char m_fogAlpha;				// +0xBE8
	unsigned char m_clearAlpha;				// +0xBE9
};
extern int g_Va00DB5FA0;

class RTS3DScene
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual const Vector3 &Get_Ambient_Light(void);		// slot 7
protected:
	void updateFixedLightEnvironments(RenderInfoClass &rinfo);
private:
	char m_pad004[0x130 - 0x04];
	LightClass *m_globalLight[4];				// +0x130
	LightClass *m_scratchLight;				// +0x140
	Vector3 m_infantryAmbient;				// +0x144
	LightClass *m_infantryLight[4];				// +0x150
	Int m_numGlobalLights;					// +0x160
	LightEnvironmentClass m_defaultLightEnv;		// +0x164
	LightEnvironmentClass m_foggedLightEnv;			// +0x38C
	LightEnvironmentClass m_ambientLightEnv;		// +0x5B4
	unsigned char m_lightEnvironmentFlag;			// +0x7DC
};

void RTS3DScene::updateFixedLightEnvironments(RenderInfoClass &rinfo)
{
	const SceneLightGlobalView *global = reinterpret_cast<const SceneLightGlobalView *>(TheWritableGlobalData);
	Real foggedLightFrac = (Real)global->m_clearAlpha / (Real)global->m_fogAlpha;
	Vector3 lodScale(1.0f, 1.0f, 1.0f);
	if (g_Va00DB5FA0 < 2)
	{
		lodScale.X = global->m_lowLODLightScaleRed;
		lodScale.Y = global->m_lowLODLightScaleGreen;
		lodScale.Z = global->m_lowLODLightScaleBlue;
	}

	m_defaultLightEnv.Reset(Vector3(0, 0, 0), Get_Ambient_Light());
	m_foggedLightEnv.Reset(Vector3(0, 0, 0), foggedLightFrac * Get_Ambient_Light());
	m_ambientLightEnv.Reset(Vector3(0, 0, 0), m_infantryAmbient);

	for (Int globalLightIndex = 0; globalLightIndex < m_numGlobalLights; globalLightIndex++)
	{
		Vector3 diffuse;
		m_globalLight[globalLightIndex]->Get_Diffuse(&diffuse);
		m_globalLight[globalLightIndex]->Set_Diffuse(Vector3(diffuse.X * lodScale.X, diffuse.Y * lodScale.Y, diffuse.Z * lodScale.Z));
		m_defaultLightEnv.Add_Light(*m_globalLight[globalLightIndex]);
		m_globalLight[globalLightIndex]->Set_Diffuse(diffuse);
		if (m_infantryLight[globalLightIndex])
		{
			Vector3 infantryDiffuse;
			m_infantryLight[globalLightIndex]->Get_Diffuse(&infantryDiffuse);
			m_infantryLight[globalLightIndex]->Set_Diffuse(Vector3(infantryDiffuse.X * lodScale.X, infantryDiffuse.Y * lodScale.Y, infantryDiffuse.Z * lodScale.Z));
			m_ambientLightEnv.Add_Light(*m_infantryLight[globalLightIndex]);
			m_infantryLight[globalLightIndex]->Set_Diffuse(infantryDiffuse);
		}

		m_scratchLight->Set_Transform(m_globalLight[globalLightIndex]->Get_Transform());
		Vector3 oldLightColor;
		m_globalLight[globalLightIndex]->Get_Diffuse(&oldLightColor);
		oldLightColor.Scale(lodScale);
		m_scratchLight->Set_Diffuse(oldLightColor * foggedLightFrac);
		m_globalLight[globalLightIndex]->Get_Ambient(&oldLightColor);
		m_scratchLight->Set_Ambient(oldLightColor * foggedLightFrac);
		m_foggedLightEnv.Add_Light(*m_scratchLight);
	}

	m_defaultLightEnv.m_outputAmbient = Vector3(m_defaultLightEnv.m_outputAmbient.X * lodScale.X,
		m_defaultLightEnv.m_outputAmbient.Y * lodScale.Y, m_defaultLightEnv.m_outputAmbient.Z * lodScale.Z);
	m_foggedLightEnv.m_outputAmbient = Vector3(m_foggedLightEnv.m_outputAmbient.X * lodScale.X,
		m_foggedLightEnv.m_outputAmbient.Y * lodScale.Y, m_foggedLightEnv.m_outputAmbient.Z * lodScale.Z);
	m_ambientLightEnv.m_outputAmbient = Vector3(m_ambientLightEnv.m_outputAmbient.X * lodScale.X,
		m_ambientLightEnv.m_outputAmbient.Y * lodScale.Y, m_ambientLightEnv.m_outputAmbient.Z * lodScale.Z);

	m_defaultLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_defaultLightEnv.m_flag = m_lightEnvironmentFlag;
	m_foggedLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_foggedLightEnv.m_flag = m_lightEnvironmentFlag;
	m_ambientLightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
	m_ambientLightEnv.m_flag = m_lightEnvironmentFlag;
}
