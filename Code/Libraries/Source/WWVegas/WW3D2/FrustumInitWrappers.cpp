// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x00133400 and 0x00133430 (35 bytes each, RET 0x14), beside the camera code: two
// FrustumClass entry points that forward their five arguments to the rowed FrustumClass::Init
// (0x0031E050) with its trailing flag false and true respectively. Their names are not
// recovered.
// Retail compiled these speed-tuned: the float arguments move as plain dwords.
#pragma optimize("t", on)

class Matrix3D;
class Vector2;

class FrustumClass
{
public:
	void Init(const Matrix3D &camera, const Vector2 &viewport_min, const Vector2 &viewport_max,
		float znear, float zfar, bool flag);
	void rva00133400(const Matrix3D &camera, const Vector2 &viewport_min, const Vector2 &viewport_max,
		float znear, float zfar);
	void rva00133430(const Matrix3D &camera, const Vector2 &viewport_min, const Vector2 &viewport_max,
		float znear, float zfar);
};

void FrustumClass::rva00133400(const Matrix3D &camera, const Vector2 &viewport_min, const Vector2 &viewport_max,
	float znear, float zfar)
{
	Init(camera, viewport_min, viewport_max, znear, zfar, false);
}

void FrustumClass::rva00133430(const Matrix3D &camera, const Vector2 &viewport_min, const Vector2 &viewport_max,
	float znear, float zfar)
{
	Init(camera, viewport_min, viewport_max, znear, zfar, true);
}
