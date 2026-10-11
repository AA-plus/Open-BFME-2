// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class BfmeMade_009CB5F0
{
private:
	int m_bfmeFields[0xA];
};

// LINK: the made object's constructor (retail 0x009CB4E0) is rowed as
// MemoryWriteFile::MemoryWriteFile(const char *); the owner word is passed the same way.
class MemoryWriteFile
{
public:
	MemoryWriteFile(const char *name);

private:
	int m_bfmeFields[0xA];
};

BfmeMade_009CB5F0 * __cdecl bfmeMake_009CB5F0(void *owner)
{
	return reinterpret_cast<BfmeMade_009CB5F0 *>(new MemoryWriteFile(reinterpret_cast<const char *>(owner)));
}
