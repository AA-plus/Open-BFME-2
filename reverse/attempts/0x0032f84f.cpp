// ?parseCastleTemplateMaps@SidesList@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?parseCastleTemplateMaps@SidesList@@QAEXXZ
// partial score=0.93 date=2026-10-13
// Retail 0x0032F84F (439B). Owner-embedded port in
// Code/GameEngine/Source/GameLogic/Map/SidesListDataChunks.cpp compiles 444B
// (standalone bank was 440B); head exact through the rva0032ED61 call.
// Walls:
// (1) ebx-zero (THE wall, ~all remaining bytes): retail pins ebx=0 before the
//     loop (xor after the empty-list check) and reuses it 4x: mapName-null
//     cmp, EH-state store, fileFound cmp (cmp al,bl), parse(0) push, plus the
//     loop-tail EH byte store (mov [ebp-4],bl). Every spelling tried uses
//     immediates (test eax,eax / and [ebp-4],0 / test al,al / push 0).
//     The zero has no home (no int local in retail) yet gets a callee-saved
//     reg hoisted out of the loop. Next: find what seeds ebx (try explicit
//     str()==0 forms, fileFound as enrollment, parse(NULL); compare against
//     the rowed sibling rva0032D554 which uses immediates everywhere).
// (2) filename/lab swap (packet note, downstream): verify binding arg order
//     once (1) lands (push 0xde0878/label/file/0/method/this).
// Kept in owner file (build-green): SidesList::rva0032ED61 +
// parseCastleTemplateMaps decls, m_castleTemplateMaps member (+0x20),
// Rva0032ED61 class decl. Method body reverted below.
// t=30 model=muse-spark
void SidesList::parseCastleTemplateMaps()
{
	((Rva0032ED61 *)this)->rva0032ED61();
	for (_STL::list<AsciiString>::iterator it = m_castleTemplateMaps.begin(); it != m_castleTemplateMaps.end(); ++it) {
		AsciiString mapName = *it;
		if (mapName.isEmpty())
			return;
		AsciiString path("Bases\\");
		path.concat(mapName);
		path.concat("\\");
		path.concat(mapName);
		path.concat(".bse");
		AsciiString fileName = path;
		Rva00240000 fileStrm;
		bool fileFound = fileStrm.rva00308050(fileName);
		if (fileFound) {
			DataChunkInput file(&fileStrm);
			BfmeParserBindingVE parser(this, &SidesList::parseCastleTemplateDataChunk, &file,
				AsciiString("CastleTemplates"), AsciiString::TheEmptyString);
			if (!file.parse(0))
				throw ERROR_CORRUPT_FILE_FORMAT;
			((Rva003079ED *)&fileStrm)->rva003079ED();
		}
	}
}
// SidesList::parseSidesDataChunk, retail 0x0032F13C (820 bytes): the sides,
// their build lists and (before version 5) the teams and player scripts are
// read into a scratch SidesList that is then swapped in. Identity (target):
// WorldBuilder's debug twin wb 0xa82370 (SidesList.cpp:729) makes the same
// calls; retail's ret 8 drops BFME 1's userData. The scratch list's ctor and
// dtor are 0x0032EE24 and 0x0032EC63, its +0xF44 TeamsInfoRec takes the
// teams, and a build count over 9999 reads as none.
bool SidesList::parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info)
{
	SidesList newSides;
	if (info->version >= 6)
		newSides.m_cleared = file.readByte() != 0;
	else
		newSides.m_cleared = true;
	int count = file.readInt();
	int i, j;
	for (i = 0; i < count; i++) {
		if (i >= 20)
			break;
		Dict d = file.readDict();
		newSides.addSide(&d);
		int numBuildings = file.readInt();
		if (numBuildings > 9999)
			numBuildings = 0;
		for (j = 0; j < numBuildings; j++) {
			BuildListInfo *pBuildList = new BuildListInfo;
			reinterpret_cast<Rva0032A438 *>(pBuildList)->rva0032A438(file.readAsciiString());
			reinterpret_cast<Rva002AAE81 *>(pBuildList)->rva002AAE81(file.readAsciiString());
			Coord3D loc;
			loc.x = file.readReal();
			loc.y = file.readReal();
			loc.z = file.readReal();
			loc.z = 0;
			pBuildList->setLocation(loc);
			pBuildList->setAngle(file.readReal());
			pBuildList->setInitiallyBuilt(file.readByte() != 0);
			pBuildList->setNumRebuilds(file.readInt());
			if (info->version >= 3) {
				reinterpret_cast<Rva0032A46C *>(pBuildList)->rva0032A46C(file.readAsciiString());
				pBuildList->setHealth(file.readInt());
				pBuildList->setWhiner(file.readByte() != 0);
				pBuildList->setUnsellable(file.readByte() != 0);
				pBuildList->setRepairable(file.readByte() != 0);
			}
			newSides.getSideInfo(i)->addToBuildList(pBuildList, j);
		}
	}
	if (info->version >= 2 && info->version < 5) {
		count = file.readInt();
		for (i = 0; i < count; i++) {
			Dict d = file.readDict();
			newSides.m_teamrec.addTeam(&d);
		}
	}
	if (info->version < 5) {
		ScriptList *scripts[20];
		count = 0;
		Rva003B3417 parser(scripts, &count, reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
		if (!file.parse(0))
			throw ERROR_CORRUPT_FILE_FORMAT;
		for (i = 0; i < count; i++) {
			if (i < newSides.m_numSides)
				newSides.getSideInfo(i)->setScriptList(scripts[i]);
			::delete scripts[i];
			scripts[i] = 0;
		}
	}
	swap(&newSides);
	return true;
}

// SidesList::parseBuildListDataChunk, retail 0x0032CE9E (410 bytes): up to 20
// factions, each a name key and a build list read into one reused entry that
// is appended to the faction's list userData selects. Identity (target): the
// WorldBuilder debug twin wb 0xa832c0 (SidesList.cpp:950 atEndOfChunk assert)
// aligns read for read, with the ctor/dtor 0x0032A0CE/0x0032A186 and
// addToFactionBuildListMap 0x0032CDFE as retail's own callees.
bool SidesList::parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	int count = file.readInt();
	for (int i = 0; i < count; i++) {
		if (i >= 20)
			break;
		NameKeyType faction = file.readNameKey();
		BuildListInfo buildInfo;
		int numBuildings = file.readInt();
		for (int j = 0; j < numBuildings; j++) {
			reinterpret_cast<Rva0032A438 *>(&buildInfo)->rva0032A438(file.readAsciiString());
			reinterpret_cast<Rva002AAE81 *>(&buildInfo)->rva002AAE81(file.readAsciiString());
			Coord3D loc;
			loc.x = file.readReal();
			loc.y = file.readReal();
			loc.z = file.readReal();
			buildInfo.setLocation(loc);
			buildInfo.setAngle(file.readReal());
			buildInfo.setInitiallyBuilt(file.readByte() != 0);
			buildInfo.setNumRebuilds(file.readInt());
			reinterpret_cast<Rva0032A46C *>(&buildInfo)->rva0032A46C(file.readAsciiString());
			buildInfo.setHealth(file.readInt());
			buildInfo.setWhiner(file.readByte() != 0);
			buildInfo.setUnsellable(file.readByte() != 0);
			buildInfo.setRepairable(file.readByte() != 0);
			addToFactionBuildListMap(faction, reinterpret_cast<const BfmePod128 &>(buildInfo), (int)userData);
		}
	}
	return true;
}

// SidesList::writeSidesDataChunk, retail 0x0032E542 (434 bytes): the version 6
// "SidesList" chunk, the cleared flag, then each side's dict and build list.
// Identity (target): WorldBuilder's debug twin wb 0xa82a60 (SidesList.cpp:744
// "had to clean up sideslist on write" after validateSides 0x0032E02B) aligns
// write for write. Unlike BFME 1's static writer it is a member, runs
// validateSides first and leaves teams and scripts to other chunks. The
// getters' layout is the target's BuildListInfo above; the two name getters
// are folded bodies called under their pinned spellings.
void SidesList::writeSidesDataChunk(DataChunkOutput &chunkWriter)
{
	rva0032E02B();
	chunkWriter.openDataChunk("SidesList", 6);
	chunkWriter.writeByte(m_cleared);
	chunkWriter.writeInt(m_numSides);
	for (int i = 0; i < m_numSides; i++) {
		chunkWriter.writeDict(*getSideInfo(i)->getDict());
		BuildListInfo *pBuildList = getSideInfo(i)->getBuildList();
		int count = 0;
		while (pBuildList) {
			count++;
			pBuildList = pBuildList->getNext();
		}
		chunkWriter.writeInt(count);
		pBuildList = getSideInfo(i)->getBuildList();
		while (pBuildList) {
			chunkWriter.writeAsciiString(reinterpret_cast<const Rva00564DF2NameView *>(pBuildList)->rva00564DF2());
			chunkWriter.writeAsciiString(pBuildList->rva000AF1DD());
			chunkWriter.writeReal(pBuildList->getLocation()->x);
			chunkWriter.writeReal(pBuildList->getLocation()->y);
			chunkWriter.writeReal(pBuildList->getLocation()->z);
			chunkWriter.writeReal(pBuildList->getAngle());
			chunkWriter.writeByte(pBuildList->isInitiallyBuilt());
			chunkWriter.writeInt(pBuildList->getNumRebuilds());
			chunkWriter.writeAsciiString(pBuildList->getScript());
			chunkWriter.writeInt(pBuildList->getHealth());
			chunkWriter.writeByte(pBuildList->getWhiner());
			chunkWriter.writeByte(pBuildList->getUnsellable());
			chunkWriter.writeByte(pBuildList->getRepairable());
			pBuildList = pBuildList->getNext();
		}
	}
	chunkWriter.closeDataChunk();
}

// SidesList::parseLibraryMapListsChunk, retail 0x0032C779 (214 bytes): the
// "LibraryMaps" binding 0x00329F83 parses up to 20 lists of map names and
// their count, and each list read is swapped into its side (SidesInfo +0x54).
// Identity (target): WorldBuilder's debug twin wb 0xa81bb0 (SidesList.cpp:529)
// builds the same 20-element vector<AsciiString> array through the eh vector
// constructor iterator 0x00629512 and walks the count down. The binding's
// inline base destructor is the one Rva003B3417 uses; swap 0x00567ECD is the
// folded vector swap.
bool SidesList::parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info)
{
	_STL::vector<AsciiString> lists[20];
	int count;
	LibraryMapsParser parser(lists, &count, &file, info);
	if (!file.parse(0))
		return false;
	while (count > 0) {
		--count;
		if (count < m_numSides) {
			_STL::vector<AsciiString> *maps = &getSideInfo(count)->m_libraryMaps;
			maps->swap(lists[count]);
		}
	}
	return true;
}

// SidesList::writeCastleTemplateDataChunk, retail 0x0032B88C (1177 bytes): the
// version 5 "CastleTemplates" chunk of a .bse castle map.
//
// Identity (target): WorldBuilder's debug twin (wb 0xa8ac80, SidesList.cpp
// asserts 2756 and 2770) aligns call for call: the "bse" suffix test, the name
// key of the map name up to its '.', the kind-of bit 18 test on each object's
// template, the objectIsABase / objectBaseName / objectName / objectBasePriority
// / objectBasePhase keys (VA 0x00DBDD0C, 0x00DBDD14, 0x00DBDCC4, 0x00DBDD84,
// 0x00DBDD8C) with 40 as the missing priority and phase, then each path's name,
// point count and centre-relative points through 0x002E3A8D.
//
// Shape (target): retail inlines the one-character append as
// StringBase<char>::concat(&c, 1); the base sum reads its location through a
// local (an inline add straight on the call result loads the sum first); and
// the relative point is a pair whose x is never stored. The list<MapObject *>
// base constructor, _M_create_node, insert and base destructor fold onto the
// list<int> rows 0x004EC36C, 0x000B6447, 0x005925E2 and 0x004EC395.
static __forceinline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

void SidesList::writeCastleTemplateDataChunk(DataChunkOutput &out, MapObject *pMapObjs, const AsciiString &mapName, Rva002E3A8DHolder *paths)
{
	out.openDataChunk("CastleTemplates", 5);
	if (!mapName.endsWithNoCase("bse")) {
		out.writeNameKey(TheNameKeyGenerator->nameToKey("UNKNOWN"));
		out.writeInt(0);
		return;
	}
	AsciiString name;
	for (int i = 0; mapName.getCharAt(i) != '.'; i++)
		concatChar(name, mapName.getCharAt(i));
	out.writeNameKey(TheNameKeyGenerator->nameToKey(name));

	bool exists = false;
	int count = 0;
	Coord3D center;
	center.zero();
	Coord3D baseSum;
	baseSum.zero();
	Coord3D pieceSum;
	pieceSum.zero();
	int baseCount = 0;
	AsciiString templateName("");
	_STL::list<MapObject *> pieces;
	for (MapObject *obj = pMapObjs; obj; obj = obj->getNext()) {
		const ThingTemplate *tt = obj->getThingTemplate();
		if (tt && tt->isKindOf(18)) {
			const Coord3D *loc = obj->getLocation();
			baseSum.add(loc);
			baseCount++;
			continue;
		}
		bool isABase = obj->getProperties()->getBool(TheKey_objectIsABase, &exists);
		if (exists && isABase)
			continue;
		AsciiString baseName = obj->getProperties()->getAsciiString(TheKey_objectBaseName, &exists);
		if (exists && !baseName.isEmpty()) {
			pieces.push_back(obj);
			count++;
			pieceSum.add(obj->getLocation());
		}
	}
	if (baseCount == 0) {
		center.x = pieceSum.x / count;
		center.y = pieceSum.y / count;
		center.z = pieceSum.z / count;
	} else {
		center.x = baseSum.x / baseCount;
		center.y = baseSum.y / baseCount;
		center.z = baseSum.z / baseCount;
	}

	out.writeInt(count);
	if (count > 0) {
		for (_STL::list<MapObject *>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
			MapObject *building = *it;
			if (!building)
				return;
			templateName = building->getProperties()->getAsciiString(TheKey_objectName, &exists);
			out.writeAsciiString(exists ? templateName : AsciiString::TheEmptyString);
			const ThingTemplate *tt = building->getThingTemplate();
			out.writeAsciiString(tt ? tt->getName() : AsciiString::TheEmptyString);
			Coord3D pos = *building->getLocation();
			pos.sub(&center);
			out.writeReal(pos.x);
			out.writeReal(pos.y);
			out.writeReal(pos.z);
			out.writeReal(building->getAngle());
			int priority = building->getProperties()->getInt(TheKey_objectBasePriority, &exists);
			out.writeInt(exists ? priority : 40);
			int phase = building->getProperties()->getInt(TheKey_objectBasePhase, &exists);
			out.writeInt(exists ? phase : 40);
		}
	}

	int numPaths = 0;
	Rva002E3A8DHolder *path;
	for (path = paths; path; path = path->getNext())
		numPaths++;
	out.writeInt(numPaths);
	for (path = paths; path; path = path->getNext()) {
		out.writeAsciiString(path->getName());
		int numPoints = path->getNumPoints();
		out.writeInt(numPoints);
		for (int j = 0; j < numPoints; j++) {
			Rva002E3A8DPair pt;
			path->get(&pt, j);
			Rva002E3A8DPair rel;
			rel.m_x = pt.m_x - center.x;
			rel.m_y = pt.m_y - center.y;
			out.writeReal(rel.m_x);
			out.writeReal(rel.m_y);
		}
	}
	out.closeDataChunk();
}

// The cached file stream (ZH CachedFileInputStream) rowed under its
// constructor's address: open takes the path by value; close (0x003079ED)
// keeps an address-era class of its own.
class Rva00240000 : public ChunkInputStream
{
public:
	Rva00240000() throw();				// 0x00240000
	~Rva00240000();						// 0x0023F4F0
	bool rva00308050(AsciiString path);	// 0x00308050, open

private:
	char m_body[0x20 - 4];
};

class Rva003079ED { public: void rva003079ED(); };	// close

// The castle build-list and path maps' clear (this +0x24 and +0x30).
class Rva0032ED61 { public: void rva0032ED61(); };

// The SidesList chunk binding (BfmeDataChunkParserBinding.cpp): its callback
// is an 8-byte member pointer, its base destructor the inline one above.
#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef bool (SidesList::*BfmeSidesListChunkCallback)(DataChunkInput &, DataChunkInfo *);

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
		DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel);	// 0x000AD73D

	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	SidesList *m_owner;
	BfmeSidesListChunkCallback m_callback;
};
