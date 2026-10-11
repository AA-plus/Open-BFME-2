// cl: /MD
// ??_GTerrainResourceBehaviorModuleData@@UAEPAXI@Z @0x00482259
class TerrainResourceBehaviorModuleData { public: __declspec(noinline) virtual ~TerrainResourceBehaviorModuleData(); private: int m_famgen; };
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline TerrainResourceBehaviorModuleData::~TerrainResourceBehaviorModuleData() { m_famgen = 0; }

// ?bfmeAnchorTerrainResourceBehaviorModuleDataDtor absent-from-retail
void bfmeAnchorTerrainResourceBehaviorModuleDataDtor(TerrainResourceBehaviorModuleData *p)
{
	p->TerrainResourceBehaviorModuleData::~TerrainResourceBehaviorModuleData();
}
void famgenDelete(TerrainResourceBehaviorModuleData *p) { delete p; }
