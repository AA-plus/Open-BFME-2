// ?calcBlendHeight@W3DTerrainBackground@@QAEXMHPAM@Z
// partial score=0.974 date=2026-10-13
// ?calcBlendHeight@W3DTerrainBackground@@QAEXMHPAM@Z
// partial score=0.93 date=2026-10-13
// ?calcBlendHeight@W3DTerrainBackground@@QAEXMHPAM@Z
// partial score=0.93 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Retail 0x00115A5B (844B). Port target: Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva001159F1.cpp
// (appends after rowed rva001159F1; reuse its Rva000AD9AB/Rva00113110Holder/Rva001159F1 views, do not redefine).
// 844/844 size-exact in the TU (existing row re-verified). rva00113DE0 now rowed (3083B) - pin retired, same spelling.
// RESIDUE (43 diff lines, all same-size; three independent roots + cascades):
// (A) Limits prologue: retail ebx=mapXMax(+0x8 first) eax=mapYMax, yLimit home -0x18; ours ebx=mapYMax(+0xC first) eax=mapXMax, yLimit home -0x14.
//     Load order is STICKY (+0xC first) across decl orders (mapYMax-first AND mapXMax-first both give +0xC first) -
//     the compiler canonicalizes independent of source. Interleaving compute+clamp per axis reshapes the prologue (840B, worse).
//     _ReadWriteBarrier between the loads scrambles scheduling (+10B, worse). Both reverted.
// (B) Heights-fill: retail evaluates x-clamp (cmovge) before y-clamp (cmovl) then index; ours y-first (args evaluate right-to-left).
//     Hoisting Int cxx=clampMin(x) backfires (extra home, index interleaves early, 72 diffs). Reverted.
// (C) yLimit home cascade (-0x18 vs -0x14): ndx phase, blend index/yOrigin slots, edge block - all follow (A).
// (D) fabs tail: retail fst delta; fld largest; pop; fcomip; fstp; pop - ours pops before fld (pure x87/integer scheduling trivia).
// (E) Edge block eax<->ecx swap for (i-xOrigin)/width - likely cascade of (A) via the J-counter home.
// Prescription: fix (A) first (load order + regs + yLimit home); (C) and (E) should follow; then (B) via forced x-first eval without extra homes; (D) last (try if/else form for the largest update).
// t=35 model=muse-spark (seat W7-MP6).

#include <string.h>

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

#define MAP_HEIGHT_SCALE (10.0f / 256.0f)

extern "C" double __cdecl fabs(double);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

template <class T> inline T clampMin(T a, T b) { return a < b ? a : b; }

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

class BoundedShortGrid
{
public:
	short rva00062A58(Int x, Int y);
};

class Rva00729300BitPlane
{
public:
	bool test(Int x, Int y) const;
};

class Rva000AD9AB
{
public:
	void rva000AD9FE();
};

class Rva00113110Holder
{
public:
	void rva00112898(int, int, void *);
};

class Rva001159F1
{
public:
	void rva001159F1(void *value);
};

class WorldHeightMap
{
public:
	Int getXExtent() { return m_width; }
	Int getYExtent() { return m_height; }
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	bool isInMesh(Int x, Int y) { return ((const Rva00729300BitPlane *)this)->test(x, y); }
	void refreshBitPlane() { ((Rva000AD9AB *)this)->rva000AD9FE(); }

private:
	unsigned char m_pad00[0x08];
	Int m_width;
	Int m_height;
};

class Rva0011216CSlotQuartet
{
public:
	void rva00112153();
};

class W3DTerrainBackground
{
public:
	void calcBlendHeight(Real param, Int mode, Real *maxDelta);
	void rva00113DE0(UnsignedShort *ib, Vector3 *heights, Int xOffset, Int yOffset, Int width,
		UnsignedShort *ndx, Int &curIndex);

private:
	void setInMeshRecursive(Int xOffset, Int yOffset, Int width)
	{
		((Rva00113110Holder *)this)->rva00112898(xOffset, yOffset, (void *)width);
	}

	unsigned char m_pad00[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0x88 - 0x60];
	Int m_step;
	Int m_savedStep;
	unsigned char m_pad90[0x94 - 0x90];
	Int m_coarseStep;
	unsigned char m_pad98[0xC8 - 0x98];
	Int m_mode;
	Real m_blend;
	Vector3 *m_heights;
};

void W3DTerrainBackground::calcBlendHeight(Real param, Int mode, Real *maxDelta)
{
	Int xOrigin = m_xOrigin;
	Int yOrigin = m_yOrigin;
	Int xLimit = m_xOrigin + m_width;
	Int yLimit = m_yOrigin + m_width;
	Int mapYMax = m_map->getYExtent() - 1;
	Int mapXMax = m_map->getXExtent() - 1;
	if (xLimit > mapXMax)
		xLimit = mapXMax;
	if (yLimit > mapYMax)
		yLimit = mapYMax;

	Int x, y;
	if (param == 0.0f) {
		((Rva0011216CSlotQuartet *)this)->rva00112153();
		Int count = (m_width + 1) * (m_width + 1);
		m_heights = new Vector3[count];
		for (y = yOrigin; y <= yLimit; y++) {
			for (x = xOrigin; x <= xLimit; x++) {
				Int idx = (x - xOrigin) + (m_width + 1) * (y - yOrigin);
				m_heights[idx].X = m_map->getHeight(clampMin(x, mapXMax), clampMin(y, mapYMax)) * MAP_HEIGHT_SCALE;
				m_heights[idx].Z = m_heights[idx].X;
				m_heights[idx].Y = m_heights[idx].Z;
			}
		}

		if (m_mode == 2) {
			m_savedStep = m_step;
			m_step = m_coarseStep;
		}
		m_map->refreshBitPlane();
		setInMeshRecursive(0, 0, m_width);

		Int ndxCount = 0;
		UnsignedShort *ndx = new UnsignedShort[count];
		memset(ndx, 0, count * sizeof(UnsignedShort));
		for (y = yOrigin; y <= yLimit; y += m_step) {
			for (x = xOrigin; x <= xLimit; x += m_step) {
				if (m_map->isInMesh(x, y)) {
					ndx[(y - yOrigin) * (m_width + 1) + (x - xOrigin)] = ndxCount++;
				}
			}
		}
		Int curIndex = 0;
		rva00113DE0(0, m_heights, 0, 0, m_width, ndx, curIndex);
		delete[] ndx;

		if (mode == 2)
			m_step = m_savedStep;
		if (mode == 1)
			((Rva001159F1 *)this)->rva001159F1((void *)m_coarseStep);
	}

	m_map->refreshBitPlane();
	setInMeshRecursive(0, 0, m_width);

	Real largest = 0.0f;
	for (Int j = yOrigin; j <= yLimit; j += m_step) {
		for (Int i = xOrigin; i <= xLimit; i += m_step) {
			if (m_map->isInMesh(i, j)) {
				Int idx = (j - yOrigin) * (m_width + 1) + (i - xOrigin);
				m_heights[idx].Z = (1.0f - m_blend) * m_heights[idx].X + m_heights[idx].Y * m_blend;
				Real delta = fabs(m_heights[idx].Y - m_heights[idx].X);
				if (!(largest > delta))
					largest = delta;
				if (i - xOrigin == 0 || j - yOrigin == 0 || i - xOrigin == m_width || j - yOrigin == m_width) {
					if (mode == 1)
						m_heights[idx].Z = m_heights[idx].Y;
					else if (mode == 2)
						m_heights[idx].Z = m_heights[idx].X;
				}
			}
		}
	}
	if (param == 0.0f)
		*maxDelta = largest;
}
