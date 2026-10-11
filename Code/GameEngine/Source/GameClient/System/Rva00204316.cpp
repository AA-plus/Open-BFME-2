// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00204316@Rva00204316@@QAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z,
// retail 0x00204316 (112 bytes, RET 8): a vtable slot (table 0x007E39E8)
// that registers a copy of a particle system template under a name: the
// 0xD4-byte copy (rowed ParticleSystemTemplate copy constructor 0x001FCE6B)
// and the name as a temporary string go to TheParticleSystemManager
// (0x00DFDD04) through 0x001FCF11 (pinned by address). The receiver is
// unused.
#include "ascii_string.h"

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);
private:
	unsigned char m_bytes[0xD4];
};
}

class ParticleSystemManager
{
public:
	void rva001FCF11(const AsciiString &name, FXParticleSystem::ParticleSystemTemplate *tmpl);
};

extern ParticleSystemManager *TheParticleSystemManager;

struct Rva00204316
{
	void rva00204316(const char *name, const FXParticleSystem::ParticleSystemTemplate &src);
};

void Rva00204316::rva00204316(const char *name, const FXParticleSystem::ParticleSystemTemplate &src)
{
	FXParticleSystem::ParticleSystemTemplate *tmpl = new FXParticleSystem::ParticleSystemTemplate(src);
	TheParticleSystemManager->rva001FCF11(AsciiString(name), tmpl);
}
