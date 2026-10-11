// ?popSqrt@Rva009F2FA0Reader@@QAEHPAM@Z
// LINK: hide math.h's inline float sqrt wrapper (r3 LK4 recipe; dllimport
// extern keeps math.h's indirect-call shape). This TU's ?sqrt@@YAMM@Z/_sqrtf
// copies lose (first-copy); the call inlines but still emits loser COMDATs.
// No flags touched.
#define sqrt bfme_hidden_sqrt
#include <math.h>
#undef sqrt
extern "C" __declspec(dllimport) double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)
struct Rva009F2FA0Elem { int m_key; float m_value; };
struct Rva009F2FA0Queue { int m_0; Rva009F2FA0Elem* m_end; int m_8; Rva009F2FA0Elem* m_read; };
struct Rva009F2FA0Reader {
	Rva009F2FA0Queue* m_queue;
	int popSqrt(float* out);
};
int Rva009F2FA0Reader::popSqrt(float* out)
{
	Rva009F2FA0Elem* e = m_queue->m_read;
	if (e == m_queue->m_end)
		return 0;
	*out = (float)sqrt(e->m_value);
	e = m_queue->m_read;
	int key = e->m_key;
	m_queue->m_read = e + 1;
	return key;
}
