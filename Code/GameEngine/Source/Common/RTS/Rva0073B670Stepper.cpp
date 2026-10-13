// cl: /O2 /DNDEBUG /MD
// Retail 0x0073B670 (49 B, ret 0xC), among the shroud-raster helpers
// (0x0073B600 ShroudManagerImpl element ctor, 0x0073BAA0 range updaters):
// initialises an 8.8 fixed-point stepper for walking `steps` cells from
// `from` to `to`. It stores the count and, when positive, the per-step
// increment ((to - from) << 8) / steps and the start value (from << 8) plus
// half a step. Owner and member names are address-derived.
class Rva0073B670Stepper
{
public:
	void init(int from, int to, int steps);
private:
	int m_value;
	int m_step;
	int m_steps;
};
void Rva0073B670Stepper::init(int from, int to, int steps)
{
	m_steps = steps;
	if (steps > 0)
	{
		m_step = ((to - from) << 8) / steps;
		m_value = (from << 8) + m_step / 2;
	}
}
