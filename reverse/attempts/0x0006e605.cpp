// ?rva0006E605@RTS3DScene@@QAEXPAVVector3@@_N@Z
// partial score=0.55 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0006E605@RTS3DScene@@QAEXPAVVector3@@_N@Z (bank; receiver is W3DDisplay::m_3DScene, light at +0x130)
class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	float X;
	float Y;
	float Z;
};
inline Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
inline Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
inline Vector3 operator*(const Vector3 &a, float k) { return Vector3(a.X * k, a.Y * k, a.Z * k); }
inline Vector3 operator*(float k, const Vector3 &a) { return Vector3(a.X * k, a.Y * k, a.Z * k); }
class LightClass
{
public:
	void Get_Ambient(Vector3 *color) const;
	void Get_Diffuse(Vector3 *color) const;
	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
private:
	char m_00[0xD4];
	Vector3 Ambient;
	Vector3 Diffuse;
};
class RTS3DScene
{
public:
	void rva0006E605(Vector3 *delta, bool remove);
private:
	char m_00[0x130];
	LightClass *m_light;
};

void RTS3DScene::rva0006E605(Vector3 *delta, bool remove)
{
	Vector3 diffuse;
	m_light->Get_Diffuse(&diffuse);
	Vector3 ambient;
	m_light->Get_Ambient(&ambient);
	Vector3 newDiffuse;
	Vector3 newAmbient;
	if (remove) {
		Vector3 half = *delta * 0.5f;
		newDiffuse = diffuse - *delta;
		newAmbient = ambient - half;
	} else {
		Vector3 half = *delta * 0.5f;
		newDiffuse = *delta + diffuse;
		newAmbient = half + ambient;
	}
	m_light->Set_Diffuse(newDiffuse);
	m_light->Set_Ambient(newAmbient);
}
