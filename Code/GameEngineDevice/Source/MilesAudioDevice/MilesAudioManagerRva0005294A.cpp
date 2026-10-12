// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?getScreenToTerrainPositions@MilesAudioManager@@QAEXPAUScreenToTerrainSet@@@Z @0x0005294A 499B.
// MilesAudioManager::getScreenToTerrainPositions: fills five listener sample
// points (screen centre and the four corners, in that order) with the terrain
// position under each pixel. The mode at +0x678 selects the tactical view
// (screenToTerrain, vslot 90, result is the validity byte) or the second
// host (g_00DFEF18 vslot 14, validity always true); any other mode, or a
// missing host, leaves five zeroed invalid entries.
// Evidence (target): WorldBuilder twin 0x78A0C0 is
// MilesAudioManager::getScreenToTerrainPositions (MilesAudioManager.cpp 4934).
// Display widths and heights are unsigned (shr 1); the tactical view's are
// signed (cdq/sub/sar). Entry stride 0x10 = Coord3D + validity byte at +0xC.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"

struct ScreenToTerrainEntry
{
	Coord3D m_pos;
	bool m_valid;
};

struct ScreenToTerrainSet
{
	ScreenToTerrainEntry m_entry[5];
};

class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual int getWidth();	// slot 15
	virtual void v16();
	virtual int getHeight();	// slot 17
	virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89();
	virtual bool screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);	// slot 90
};

class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15();
	virtual unsigned int getWidth();	// slot 16
	virtual unsigned int getHeight();	// slot 17
};

class Rva002D3627Host
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world);	// slot 14
};

extern View *TheTacticalView;
extern Display *TheDisplay;
extern Rva002D3627Host *g_00DFEF18;

class MilesAudioManager
{
public:
	void getScreenToTerrainPositions(ScreenToTerrainSet *out);
private:
	char m_pad000[0x678];
	int m_mode;
};

void MilesAudioManager::getScreenToTerrainPositions(ScreenToTerrainSet *out)
{
	ICoord2D pixel;
	switch (m_mode) {
	case 1:
		if (g_00DFEF18 != 0 && TheDisplay != 0) {
			pixel.x = TheDisplay->getWidth() >> 1;
			pixel.y = TheDisplay->getHeight() >> 1;
			out->m_entry[0].m_valid = true;
			g_00DFEF18->screenToTerrain(&pixel, &out->m_entry[0].m_pos);
			pixel.x = 0;
			pixel.y = 0;
			out->m_entry[1].m_valid = true;
			g_00DFEF18->screenToTerrain(&pixel, &out->m_entry[1].m_pos);
			pixel.y = TheDisplay->getHeight() - 1;
			out->m_entry[2].m_valid = true;
			g_00DFEF18->screenToTerrain(&pixel, &out->m_entry[2].m_pos);
			pixel.x = TheDisplay->getWidth() - 1;
			out->m_entry[3].m_valid = true;
			g_00DFEF18->screenToTerrain(&pixel, &out->m_entry[3].m_pos);
			pixel.y = 0;
			out->m_entry[4].m_valid = true;
			g_00DFEF18->screenToTerrain(&pixel, &out->m_entry[4].m_pos);
			return;
		}
		break;
	case 0:
		if (TheTacticalView != 0) {
			pixel.x = TheTacticalView->getWidth() / 2;
			pixel.y = TheTacticalView->getHeight() / 2;
			out->m_entry[0].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[0].m_pos, false);
			pixel.x = 0;
			pixel.y = 0;
			out->m_entry[1].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[1].m_pos, false);
			pixel.y = TheTacticalView->getHeight() - 1;
			out->m_entry[2].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[2].m_pos, false);
			pixel.x = TheTacticalView->getWidth() - 1;
			out->m_entry[3].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[3].m_pos, false);
			pixel.y = 0;
			out->m_entry[4].m_valid = TheTacticalView->screenToTerrain(&pixel, &out->m_entry[4].m_pos, false);
			return;
		}
		break;
	}
	for (int i = 0; i < 5; ++i) {
		out->m_entry[i].m_valid = false;
		out->m_entry[i].m_pos.x = 0.0f;
		out->m_entry[i].m_pos.y = 0.0f;
		out->m_entry[i].m_pos.z = 0.0f;
	}
}
