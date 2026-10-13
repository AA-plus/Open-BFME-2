// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// W3DShroud::interpolateFogLevels, retail 0x00073426..0x00073628 (RET 4) and its
// EH handler 0x0075EE4A.
// Identity: Zero Hour W3DShroud.cpp interpolateFogLevels(RECT *) (protected; the
// timeGetTime static, the 255 clamp, setShroudLevel(i, j, level, TRUE) per changed
// cell) and the BFME 1 9cbfb551 W3DShroudBfme.cpp body of the same name, which adds
// the m_dirty walk. Target evidence: WB 0x7FDD90 (unnamed) called from the shroud
// render body WB 0x7FD800 = retail 0x00073628 with a local RECT address; retail
// rate 0.255f, dirty flag +0x48, dirty set +0x4C.
// Same-TU lever: the visible STLport push_back body proves it does not keep the
// address of `index`, so retail holds the cell index in EBX across the appends.
#include <set>
#include <vector>
typedef float Real;
typedef bool Bool;
struct tagRECT; typedef tagRECT RECT;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class TextureClass;
struct ShroudTextureHandle { TextureClass *m_p; };
void Rva00030830GameFree(void *);
namespace _STL { template<> inline void allocator<int>::deallocate(int *p, unsigned) const {
	if (p) Rva00030830GameFree(p);
} }

// The retiring list appends through the ICF-folded 4-byte pointer-vector
// push_back (0x004DFCB0); the int instance at 0x00688940 is a different body.
class ModuleData;
inline void appendFogIndex(_STL::vector<int> &values, const int &index)
{
	reinterpret_cast<_STL::vector<const ModuleData *> &>(values).push_back(
		reinterpret_cast<const ModuleData * const &>(index));
}

// set<int>::erase(const key_type &), rowed at 0x000733D8.
struct Rva00072FE6 { unsigned rva000733D8(const int &); };

class W3DShroud
{
public:
	void setShroudLevel(int, int, unsigned char, bool);

protected:
	void interpolateFogLevels(RECT *rect);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned short *m_shroudData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_shroudFilter;
	Real m_drawOriginX;
	Real m_drawOriginY;
	unsigned char m_drawFogOfWar;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	unsigned char *m_finalFogData;
	unsigned char *m_currentFogData;
	unsigned char m_partialRenderer[8];
	unsigned char m_trackDirtyCells;
	unsigned char m_pad49[3];
	_STL::set<int> m_dirty;
};

void W3DShroud::interpolateFogLevels(RECT *rect)
{
	static unsigned int prevTime = (unsigned int)timeGetTime();
	unsigned int timeDiff = (unsigned int)timeGetTime() - prevTime;
	if (timeDiff == 0)
		return;
	prevTime += timeDiff;

	int maxFogChange = (int)((float)timeDiff * 0.255f);
	if (maxFogChange > 255)
		maxFogChange = 255;
	unsigned char levelDelta = (unsigned char)maxFogChange;

	unsigned char *startLevel = m_currentFogData;
	unsigned char *finalLevel = m_finalFogData;
	if (m_trackDirtyCells)
	{
		int dirtyCount = (int)m_dirty.size();
		int width = m_numCellsX;
		if (width <= 0 || dirtyCount <= 0)
			return;

		_STL::vector<int> remove;
		for (_STL::set<int>::iterator it = m_dirty.begin();
			it != m_dirty.end(); ++it)
		{
			int index = *it;
			unsigned char *current = startLevel + index;
			unsigned char *target = finalLevel + index;
			unsigned char start = *current;
			unsigned char final = *target;

			if (final != start)
			{
				if (final < start)
				{
					if ((int)start - (int)final < (int)levelDelta)
					{
						*current = final;
						appendFogIndex(remove, index);
					}
					else
						*current = (unsigned char)(start - levelDelta);
				}
				else
				{
					if ((int)final - (int)start < (int)levelDelta)
					{
						*current = final;
						appendFogIndex(remove, index);
					}
					else
						*current = (unsigned char)(start + levelDelta);
				}

				setShroudLevel(index % m_numCellsX, index / m_numCellsX,
					*current, true);
			}
			else
				appendFogIndex(remove, index);
		}

		for (_STL::vector<int>::iterator it = remove.begin();
			it != remove.end(); ++it)
			reinterpret_cast<Rva00072FE6 *>(&m_dirty)->rva000733D8(*it);
	}
	else
	{
		for (int j = 0; j < m_numCellsY; ++j)
		{
			for (int i = 0; i < m_numCellsX; ++i, ++startLevel, ++finalLevel)
			{
				unsigned char start = *startLevel;
				unsigned char final = *finalLevel;
				if (final == start)
					continue;

				if (final < start)
				{
					if ((int)start - (int)final < (int)levelDelta)
						*startLevel = final;
					else
						*startLevel = (unsigned char)(start - levelDelta);
				}
				else
				{
					if ((int)final - (int)start < (int)levelDelta)
						*startLevel = final;
					else
						*startLevel = (unsigned char)(start + levelDelta);
				}

				setShroudLevel(i, j, *startLevel, true);
			}
		}
	}
}
