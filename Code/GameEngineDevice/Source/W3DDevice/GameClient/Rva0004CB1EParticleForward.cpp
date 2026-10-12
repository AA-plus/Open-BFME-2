// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva0004CB1E@@YAXH@Z, retail 0x0004CB1E (20 bytes): forwards its argument to the particle
// system manager's slot 16 (+0x40) when TheParticleSystemManager exists. Its one caller
// (0x00071DB0) is not rowed and the slot's name is not established, so the names stay
// address-derived.
class ParticleSystemManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void slot16(int value);	// +0x40
};
extern ParticleSystemManager *TheParticleSystemManager;

void Rva0004CB1E(int value)
{
	if (TheParticleSystemManager)
		TheParticleSystemManager->slot16(value);
}
