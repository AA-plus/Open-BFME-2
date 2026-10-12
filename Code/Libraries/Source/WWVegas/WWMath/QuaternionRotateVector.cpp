// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
// ?Rotate_Vector@Quaternion@@QBE?AVVector3@@ABV2@@Z, retail 0x001A0AF0 (306 bytes, RET 8),
// the out-of-line copy of the WWMath quat.h inline placed with the particle emitter code:
// q * v * conj(q) expanded through the intermediate (x, y, z, w) product.
class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X, Y, Z;
};

class Quaternion
{
public:
	Vector3 Rotate_Vector(const Vector3 &v) const;
	float X, Y, Z, W;
};

Vector3 Quaternion::Rotate_Vector(const Vector3 &v) const
{
	float x = W*v.X + (Y*v.Z - v.Y*Z);
	float y = W*v.Y - (X*v.Z - v.X*Z);
	float z = W*v.Z + (X*v.Y - v.X*Y);
	float w = -(X*v.X + Y*v.Y + Z*v.Z);

	return Vector3
	(
		W*x - w*X + (Y*z - y*Z),
		W*y - w*Y - (X*z - x*Z),
		W*z - w*Z + (X*y - Y*x)
	);
}
