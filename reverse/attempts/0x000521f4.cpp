// ?rva000521F4@GlobalVolumeData@MilesAudioManager@@QAEXM@Z
// partial score=0.9 date=2026-10-12
// ?rva000521F4@GlobalVolumeData@MilesAudioManager@@QAEXM@Z
// builds inside Code/GameEngine/Source/Common/Rva00699180Volume_Refresh.cpp
// ?rva000521F4@GlobalVolumeData@MilesAudioManager@@QAEXM@Z retail 0x000521F4 235B
// Smoothed m_scale setter: accumulates the 0.001-scaled volume, walks a
// multi-stage ramp (rate, limit, divisor segments with lerp tails), clamps
// m_scale to 0..1 like rva000522DF, then refreshAll. Evidence: prev/next in
// this TU, m_scale store +0x9C, ramp members +0xAC..+0xC4, 0.001 pool float,
// single refreshAll call 0x0005202C, ret 4.
void MilesAudioManager::GlobalVolumeData::rva000521F4(float volume)
{
	if (m_rampActive)
	{
		float acc = volume * 0.001f + m_rampAccum;
		m_rampAccum = acc;
		if (m_rampRate >= acc)
		{
			m_scale = (m_rampTarget - m_rampBase) * (acc / m_rampRate) + m_rampBase;
		}
		else
		{
			acc -= m_rampRate;
			if (m_rampLimit >= acc)
			{
				m_scale = m_rampTarget;
			}
			else
			{
				acc -= m_rampLimit;
				if (m_rampDivisor >= acc)
				{
					m_scale = (m_rampTarget - m_rampBase) * (acc / m_rampDivisor) + m_rampBase;
				}
				else
				{
					m_scale = m_rampBase;
					m_rampActive = 0;
				}
			}
		}
		float v;
		if (0.0f > m_scale)
			v = 0.0f;
		else if (m_scale > 1.0f)
			v = 1.0f;
		else
			v = m_scale;
		m_scale = v;
	}
	refreshAll();
}

