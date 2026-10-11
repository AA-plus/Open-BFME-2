// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Subsystem singleton pointers that retail keeps in .data (zero until GameEngine::init registers
// the subsystems). The ledger listed them as unowned globals, so every unit that reads one saw an
// unresolved name. Each row is the pointer only; the classes stay opaque here.
class TerrainRoadCollection;
class BfmeTaintManager;
class Rva0022AD10Subsystem;
class CrateSystem;
class PingerInterface;

TerrainRoadCollection *TheTerrainRoads = 0;		// retail 0x009FF084
BfmeTaintManager *TheTaintManager = 0;			// retail 0x009FE750
Rva0022AD10Subsystem *TheFormationAssistant = 0;	// retail 0x00A03160
CrateSystem *TheCrateSystem = 0;			// retail 0x00A01E58
PingerInterface *ThePinger = 0;				// retail 0x00A05FB8
