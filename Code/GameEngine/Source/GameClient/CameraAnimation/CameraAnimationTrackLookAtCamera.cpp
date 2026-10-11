// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// stlport
//
// CameraAnimationTrack<T>::getFrameData for the LookAt camera channel,
// retail 0x00541955 (281 bytes, ret 8). WorldBuilder's debug twin 0x00454320
// is CameraAnimationTrack<class LookAtCameraAnimationCameraFrameData>::
// getFrameData (CameraAnimationTrack.h, asserts at lines 124..139); the frame
// data keeps the address name of the rowed interpolator's result
// Rva00540D94 (0x00540DCA). A negative frame returns the first key; else the
// pinned locator 0x00541579 moves the last used key to the floored frame,
// the last key (or a key whose successor shares its frame) is returned as
// is, and otherwise the four surrounding keys (clamped at both ends) are
// interpolated at the fraction between the key and its successor.
//
// The frame data's out-of-line copy constructor is ICF-folded with the rowed
// Region3D copy constructor 0x0009AC04 (six dword copies, ret 4).
#include <math.h>
#include <vector>

struct Rva00540E9DSrc
{
	int a, b, c;
};
class Rva00540D94
{
public:
	__declspec(noinline) Rva00540D94(const Rva00540D94 &other);
	int mode;
	Rva00540E9DSrc position;
	float scalar10, scalar14;
};

Rva00540D94::Rva00540D94(const Rva00540D94 &other)
{
	mode = other.mode;
	position.a = other.position.a;
	position.b = other.position.b;
	position.c = other.position.c;
	scalar10 = other.scalar10;
	scalar14 = other.scalar14;
}

Rva00540D94 Rva00540DCAGet(float t, Rva00540D94 *a, int ta, Rva00540D94 *b, int tb, Rva00540D94 *c, int tc, Rva00540D94 *d, int td);

// The banked sorted-key locator, pinned under its address name.
class Rva00541579
{
public:
	bool rva00541579(int frame);
};

template <class T>
struct CameraAnimationKeyFrame
{
	int m_frame;
	T m_data;
};

template <class T>
class CameraAnimationTrack
{
public:
	T getFrameData(float frameNum);
private:
	typedef CameraAnimationKeyFrame<T> KeyFrame;
	char m_pad00[0x10];
	_STL::vector<KeyFrame> m_keyFrames;	// +0x10
	int m_lastUsedKeyFrame;		// +0x1C
};

template <class T>
T CameraAnimationTrack<T>::getFrameData(float frameNum)
{
	if (frameNum < 0.0f)
		return m_keyFrames[0].m_data;
	((Rva00541579 *)this)->rva00541579((int)floor(frameNum));
	if ((unsigned int)m_lastUsedKeyFrame >= m_keyFrames.size() - 1)
		return m_keyFrames[m_lastUsedKeyFrame].m_data;
	const KeyFrame &k0 = m_keyFrames[m_lastUsedKeyFrame];
	const KeyFrame &k1 = m_keyFrames[m_lastUsedKeyFrame + 1];
	if (k0.m_frame == k1.m_frame)
		return k0.m_data;
	frameNum = (frameNum - k0.m_frame) / (k1.m_frame - k0.m_frame);
	const KeyFrame &kPrev = m_lastUsedKeyFrame > 0 ? m_keyFrames[m_lastUsedKeyFrame - 1] : k0;
	const KeyFrame &kNext = m_lastUsedKeyFrame + 2 < m_keyFrames.size() ? m_keyFrames[m_lastUsedKeyFrame + 2] : k1;
	return Rva00540DCAGet(frameNum, (T *)&kPrev.m_data, kPrev.m_frame, (T *)&k0.m_data, k0.m_frame,
		(T *)&k1.m_data, k1.m_frame, (T *)&kNext.m_data, kNext.m_frame);
}

template Rva00540D94 CameraAnimationTrack<Rva00540D94>::getFrameData(float frameNum);
