// ?rva00044018@Rva00044018@@QAEXI@Z
// cl: /O1 /G7 /arch:SSE /MD
// Rva00044018::rva00044018, retail 0x00044018 (479 B): the fade/letterbox bar
// update on the rowed bar painter 0x0004263F (callers at 0x0004A913). While
// the +0xD8 flag is set the bars grow in: progress (+0xD4) rises over
// 1000 ms from the start time (+0xDC) to 1, and the top and bottom bars of a
// 16:9 frame inside the +0x0C x +0x10 viewport are drawn with that alpha; with
// the flag clear they fade back out to 0 (top bar only) and the flag-off state
// ends there. Constants are compiler literals (1.0f, 0.001f, 255, 0.5625f,
// 0.5f); unsigned dimensions convert through x87 as retail does. Names are
// structural. Semantic donor: BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp:1794,
// W3DDisplay::renderLetterBox. The caller, fields, branches, constants and
// complete native 44018..441F7 body support that role; original target
// member spelling is not independently named, so the bank's neutral name stays.

class Rva0004263F
{
	virtual void slot00();
public:
	void rva0004263F(float x0, float y0, float x1, float y1, int color);	// 0x0004263F
};

class Rva00044018 : public Rva0004263F
{
	char m_pad04[8];
	unsigned int m_width;		// +0x0C
	unsigned int m_height;		// +0x10
	char m_pad14[0xD4 - 0x14];
	float m_progress;			// +0xD4
	unsigned char m_fadingIn;	// +0xD8
	char m_padD9[3];
	unsigned int m_startTime;	// +0xDC
public:
	void rva00044018(unsigned int now);
};

// Retail uses the single-precision 255.0f literal at VA 0x00BC2900 in
// an x87 multiply before _ftol2. Volatile reference reads prevent VC7.1
// from replacing that sequence with SSE conversion or a double literal.
static const volatile float letterboxAlphaScale = 255.0f;
inline double scaleLetterboxAlpha(const volatile float &progress)
{
    return (double)progress * letterboxAlphaScale;
}

void Rva00044018::rva00044018(unsigned int now)
{
	if (m_fadingIn)
	{
		if (m_progress != 1.0f)
		{
			now -= m_startTime;
			float f = (float)now * 0.001f;
			m_progress = f;
			if (f > 1.0f)
				m_progress = 1.0f;
		}
		int alpha = (int)scaleLetterboxAlpha(m_progress) << 24;
		rva0004263F(0.0f, 0.0f, (float)m_width, ((float)m_height - (float)m_width * 0.5625f) * 0.5f, alpha);
		rva0004263F(0.0f, (float)m_height - ((float)m_height - (float)m_width * 0.5625f) * 0.5f, (float)m_width, (float)m_height, alpha);
	}
	else if (m_progress != 0.0f)
	{
		now -= m_startTime;
		float f = 1.0f - (float)now * 0.001f;
		m_progress = f;
		if (f < 0.0f)
			m_progress = 0.0f;
		rva0004263F(0.0f, 0.0f, (float)m_width, ((float)m_height - (float)m_width * 0.5625f) * 0.5f, (int)scaleLetterboxAlpha(m_progress) << 24);
	}
	else
	{
		m_fadingIn = 0;
	}
}
