// cl: /O1 /G7 /arch:SSE /MD
// Rva001048C0::update, retail 0x0033EC93 (402 B; WB 0x00E86940, unnamed): the
// intensity envelope W3DLaserDraw keeps at +0x34 (its doDrawModule calls this
// at 0x000C9952). A five-stage state machine (+0x24): wait out the delay
// (+0x10 frames, counter +0x0C) then start at the base level (+0x00); rise to
// the peak (+0x04) over +0x14 frames; fall to the sustain level (+0x08) over
// +0x18 frames; hold it for +0x1C frames; then fall to zero over +0x20
// frames. Each stage steps *out by its span divided by its frame count
// (at least one frame). Returns false once finished. Names are structural.

class Rva001048C0
{
public:
	bool update(const float *in, float *out);

private:
	float m_base;					// +0x00
	float m_peak;					// +0x04
	float m_sustain;				// +0x08
	unsigned int m_counter;			// +0x0C
	unsigned int m_delayFrames;		// +0x10
	unsigned int m_attackFrames;	// +0x14
	unsigned int m_decayFrames;		// +0x18
	unsigned int m_sustainFrames;	// +0x1C
	unsigned int m_releaseFrames;	// +0x20
	int m_state;					// +0x24
};

static __forceinline float atLeastOneFrame(unsigned int frames)
{
	float f = (float)frames;
	return 1.0f > f ? 1.0f : f;
}
bool Rva001048C0::update(const float *in, float *out)
{
	switch (m_state)
	{
		case 0:
			if (m_counter++ >= m_delayFrames)
			{
				m_state = 1;
				m_counter = 0;
				*out = m_base;
			}
			*out = 0.0f;
			return true;

		case 1:
			*out += (m_peak - m_base) / atLeastOneFrame(m_attackFrames);
			if (*out >= m_peak)
			{
				*out = m_peak;
				m_state = 2;
			}
			return true;

		case 2:
			*out -= (m_peak - m_sustain) / atLeastOneFrame(m_decayFrames);
			if (*out <= m_sustain)
			{
				*out = m_sustain;
				m_state = 3;
				m_counter = 0;
			}
			return true;

		case 3:
			if (m_counter++ >= m_sustainFrames)
				m_state = 4;
			*out = m_sustain;
			return true;

		case 4:
			*out -= m_sustain / atLeastOneFrame(m_releaseFrames);
			if (*out <= 0.0f)
			{
				*out = 0.0f;
				m_state = 5;
				m_counter = 0;
			}
			return true;
	}
	*out = 0.0f;
	return false;
}
