// cl: /O1 /MD /arch:SSE /Oy- /G7 /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Include
//
// Track samplers of the shader-parameter "Bases" object (Rva003093F6Bases, the
// class of the effect callbacks in Rva000806F3BasesParams.cpp): four getters
// that return a Vector4 by value, 0x0030822F for the "Mean" parameter and
// 0x00308325 / 0x00308417 / 0x00308509 for the X / Y / Z axes of "Bases..".
//
// Target facts (retail bytes): an unsigned key count at +0xA0 (zero returns a
// zero vector, 0x0030822F returns (0, 0, 1, 0)), a time scale at +0xA4, the
// "Mean" track pointer at +0xA8 and three Vector4 track pointers per axis at
// +0xAC (X), +0xB8 (Y) and +0xC4 (Z) indexed by the group argument. The time
// times the scale selects key r = (int)(time * scale) mod count and its
// successor (r + 1) mod count; the result is key(r) * (1 - f) + key(r + 1) * f
// with f the fractional part. Vector4 and its operators are WWMath's (BFME 1
// donor); the successor key reference is bound before the first one, which is
// what orders retail's loads and registers. The derived return struct carries
// forceinline constructors so the by-value return builds in place (a plain
// struct, or out-of-line copies, adds a copy or a call).
#include "vector4.h"

struct Rva000806F3Vector4 : public Vector4
{
	__forceinline Rva000806F3Vector4() {}
	__forceinline Rva000806F3Vector4(const Vector4 &v) : Vector4(v) {}
	__forceinline Rva000806F3Vector4(const Rva000806F3Vector4 &v) : Vector4(v) {}
};

class Rva003093F6Bases
{
public:
	Rva000806F3Vector4 rva0030822F(float time);
	Rva000806F3Vector4 rva00308325(float time, int group);
	Rva000806F3Vector4 rva00308417(float time, int group);
	Rva000806F3Vector4 rva00308509(float time, int group);
private:
	char m_pad00[0xA0];
	unsigned int m_keyCount; // +0xA0
	float m_timeScale;       // +0xA4
	Vector4 *m_meanTrack;    // +0xA8
	Vector4 *m_trackX[3];    // +0xAC
	Vector4 *m_trackY[3];    // +0xB8
	Vector4 *m_trackZ[3];    // +0xC4
};

Rva000806F3Vector4 Rva003093F6Bases::rva0030822F(float time)
{
	if (m_keyCount > 0) {
		float scaled = time * m_timeScale;
		int whole = (int)scaled;
		float f = scaled - (float)whole;
		unsigned int r = (unsigned int)whole % m_keyCount;
		unsigned int r2 = (r + 1) % m_keyCount;
		Vector4 *track = m_meanTrack;
		const Vector4 &b = track[r2];
		const Vector4 &a = track[r];
		return a * (1.0f - f) + b * f;
	}
	return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
}

Rva000806F3Vector4 Rva003093F6Bases::rva00308325(float time, int group)
{
	if (m_keyCount > 0) {
		float scaled = time * m_timeScale;
		int whole = (int)scaled;
		float f = scaled - (float)whole;
		unsigned int r = (unsigned int)whole % m_keyCount;
		unsigned int r2 = (r + 1) % m_keyCount;
		Vector4 *track = m_trackX[group];
		const Vector4 &b = track[r2];
		const Vector4 &a = track[r];
		return a * (1.0f - f) + b * f;
	}
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Rva000806F3Vector4 Rva003093F6Bases::rva00308417(float time, int group)
{
	if (m_keyCount > 0) {
		float scaled = time * m_timeScale;
		int whole = (int)scaled;
		float f = scaled - (float)whole;
		unsigned int r = (unsigned int)whole % m_keyCount;
		unsigned int r2 = (r + 1) % m_keyCount;
		Vector4 *track = m_trackY[group];
		const Vector4 &b = track[r2];
		const Vector4 &a = track[r];
		return a * (1.0f - f) + b * f;
	}
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Rva000806F3Vector4 Rva003093F6Bases::rva00308509(float time, int group)
{
	if (m_keyCount > 0) {
		float scaled = time * m_timeScale;
		int whole = (int)scaled;
		float f = scaled - (float)whole;
		unsigned int r = (unsigned int)whole % m_keyCount;
		unsigned int r2 = (r + 1) % m_keyCount;
		Vector4 *track = m_trackZ[group];
		const Vector4 &b = track[r2];
		const Vector4 &a = track[r];
		return a * (1.0f - f) + b * f;
	}
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}
