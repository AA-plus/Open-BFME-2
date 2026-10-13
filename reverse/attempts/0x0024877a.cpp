// ?rva0024877A@GameLogic@@QAE_NXZ
// partial score=0.97 date=2026-10-13
// ?rva0024877A@GameLogic@@QAE_NXZ
// partial score=0.97 date=2026-10-13
// Apply the patch below to Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (git apply after stripping the #if 0 wrapper; base 1a1c54e0ff). It adds the
// experience-refresh pass (destroy and recreate objects keeping experience,
// container and rider links) with its views: Matrix3D (forceinline operator=),
// Object/Drawable/ExperienceTracker/ExperienceLevelSystem accessors, the record
// class Rva0024076D and its STLport list.
// Compiled 404 insns, 394 exact. The residue is one stack-slot swap: retail puts
// the list's default allocator temp and 'all' at [ebp-0xf] and the loop's
// 'hidden' at [ebp-0xe]; MSVC 7.1 here assigns them the other way round.
// Declaration order, block scope, address-taking, a derived list with explicit
// allocator, hidden as char/uchar, extra hidden references and a function-scope
// hidden all leave the slots unchanged.
// Fixes already in the patch: obj->m_experienceTracker read directly for the
// last tracker call (the inline getter hoisted a +0x264 load); the
// if (lastFrame < m_40) wrapper with a single return false.
// Landing also needs placeholder pins (pin_consistency first):
//   _List_base ctor 0x0023E83A, _List_base dtor 0x002461DA,
//   ~Rva0024076D 0x00240831, list::insert 0x00247089.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index eb8b155e6d..0dedb1aed8 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -611,6 +611,8 @@ public:
 	bool rva0042219(void);
 	void processCommandList(void);
 	void processDestroyList(void);
+	void destroyObject(Object *obj);
+	bool rva0024877A(void);
 	void logicMessageDispatcher(GameMessage *msg, void *userData);
 	unsigned int getCRC(int mode);
 	void rva00240EBC(void);
@@ -1386,6 +1388,36 @@ private:
 class Dict;
 
 class Drawable;
+class Team;
+class ContainModuleInterface;
+class ExperienceTracker;
+
+class Matrix3D
+{
+public:
+	// dllimport+forceinline: expanded at its one use and never emitted, so this
+	// view no longer leaves a non-retail Matrix3D(bool) copy (retail 0x0004C91A)
+	// ahead of the real one in link order.
+	__declspec(dllimport) __forceinline explicit Matrix3D(bool init)
+	{
+		if (init) {
+			m_row[0][0] = 1.0f; m_row[0][1] = 0.0f; m_row[0][2] = 0.0f; m_row[0][3] = 0.0f;
+			m_row[1][0] = 0.0f; m_row[1][1] = 1.0f; m_row[1][2] = 0.0f; m_row[1][3] = 0.0f;
+			m_row[2][0] = 0.0f; m_row[2][1] = 0.0f; m_row[2][2] = 1.0f; m_row[2][3] = 0.0f;
+		}
+	}
+
+	__forceinline Matrix3D &operator=(const Matrix3D &m)
+	{
+		m_row[0][0] = m.m_row[0][0]; m_row[0][1] = m.m_row[0][1]; m_row[0][2] = m.m_row[0][2]; m_row[0][3] = m.m_row[0][3];
+		m_row[1][0] = m.m_row[1][0]; m_row[1][1] = m.m_row[1][1]; m_row[1][2] = m.m_row[1][2]; m_row[1][3] = m.m_row[1][3];
+		m_row[2][0] = m.m_row[2][0]; m_row[2][1] = m.m_row[2][1]; m_row[2][2] = m.m_row[2][2]; m_row[2][3] = m.m_row[2][3];
+		return *this;
+	}
+
+private:
+	float m_row[3][4];
+};
 
 class Thing
 {
@@ -1436,11 +1468,25 @@ public:
 	void rva002903C3(void);
 	void rva002903EF(void);
 	void rva00297612(void);
+	const Matrix3D *getTransformMatrix(void) const { return &m_transform; }
+	ObjectID getID(void) const { return m_id; }
+	Team *getTeam(void) const { return m_team; }
+	ContainModuleInterface *getContain(void) const { return m_contain; }
+	ExperienceTracker *getExperienceTracker(void) const { return m_experienceTracker; }
+	Object *getContainedBy(void) const { return m_containedBy; }
+	bool rva0028C428(void) const;
+	void *rva0028C197(void) const;
+	void rva0028D412(const Matrix3D *transform);
+	void *rva0029439D(void);
+	void setProducer(Object *obj);
 
 private:
 	void *m_vtbl;
 	const ThingTemplate *m_template;
-	char m_pad08[0x8c - 0x08];
+	Matrix3D m_transform;                                                // +0x08
+	char m_pad38[0x74 - 0x38];
+	ObjectID m_id;                                                       // +0x74
+	char m_pad78[0x8c - 0x78];
 	Object *m_next;
 	char m_pad090[0x94 - 0x90];
 
@@ -1452,8 +1498,16 @@ public:
 
 private:
 	DisabledMaskType m_disabledMask;                                     // +0x1C8
-	char m_pad1CC[0x258 - 0x1cc];
+	char m_pad1CC[0x250 - 0x1cc];
+	ContainModuleInterface *m_contain;                                   // +0x250
+	char m_pad254[0x258 - 0x254];
 	AIUpdateInterface *m_ai;                                             // +0x258
+	char m_pad25C[0x264 - 0x25c];
+public: ExperienceTracker *m_experienceTracker; private:                              // +0x264
+	char m_pad268[0x274 - 0x268];
+	Object *m_containedBy;                                               // +0x274
+	char m_pad278[0x304 - 0x278];
+	Team *m_team;                                                        // +0x304
 };
 
 void GameLogic::addTOCEntry(AsciiString name, unsigned short id)
@@ -1660,25 +1714,6 @@ public:
 extern ThingFactory *TheThingFactory;
 extern PlayerList *ThePlayerList;
 
-class Matrix3D
-{
-public:
-	// dllimport+forceinline: expanded at its one use and never emitted, so this
-	// view no longer leaves a non-retail Matrix3D(bool) copy (retail 0x0004C91A)
-	// ahead of the real one in link order.
-	__declspec(dllimport) __forceinline explicit Matrix3D(bool init)
-	{
-		if (init) {
-			m_row[0][0] = 1.0f; m_row[0][1] = 0.0f; m_row[0][2] = 0.0f; m_row[0][3] = 0.0f;
-			m_row[1][0] = 0.0f; m_row[1][1] = 1.0f; m_row[1][2] = 0.0f; m_row[1][3] = 0.0f;
-			m_row[2][0] = 0.0f; m_row[2][1] = 0.0f; m_row[2][2] = 1.0f; m_row[2][3] = 0.0f;
-		}
-	}
-
-private:
-	float m_row[3][4];
-};
-
 // 0x00271058 compares, unregisters and re-registers the ID at +0x100 (the
 // ZH Drawable::setID shape); the row keeps its address name.
 class Rva00271058
@@ -1838,6 +1873,9 @@ public:
 	}
 };
 
+struct BfmeAudioEventPrefix136;
+struct MiscAudio;
+
 class AudioManager
 {
 public:
@@ -1847,7 +1885,9 @@ public:
 	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
 	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
 	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
-	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
+	virtual void v18();
+	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd); // +0x64
+	virtual void v1a(); virtual void v1b();
 	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
 	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
 	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
@@ -1860,7 +1900,9 @@ public:
 	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
 	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
 	virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
-	virtual void v4c(); virtual void v4d(); virtual void v4e(); virtual void v4f();
+	virtual void v4c(); virtual void v4d();
+	virtual MiscAudio *getMiscAudio(void);                               // +0x138
+	virtual void v4f();
 	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
 	virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
 	virtual void v58(); virtual void v59(); virtual void v5a(); virtual void v5b();
@@ -2128,10 +2170,15 @@ class InGameUI
 	friend class GameLogic;
 
 public:
+	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
+	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
+	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
+	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
+	virtual void __cdecl message(UnicodeString format, ...);            // +0x40
 	void setClientQuiet(bool quiet) { m_clientQuiet = quiet; }
 
 private:
-	char m_pad000[0x8c5];
+	char m_pad004[0x8c5 - 4];
 	bool m_clientQuiet;                                                  // +0x8C5
 };
 
@@ -2195,6 +2242,7 @@ class TeamFactory : public SubsystemInterface
 public:
 	virtual void tf0b(); virtual void tf0c(); virtual void tf0d(); virtual void tf0e(); virtual void tf0f(); virtual void tf10(); virtual void tf11();
 	void rva003A262C(void);
+	Team *findTeamByID(unsigned int id);
 };
 
 class Rva0023C666
@@ -2689,10 +2737,13 @@ class Drawable
 public:
 	void rva00278C6B(void);
 	Drawable *getNextDrawable(void) const { return m_next; }
+	bool isVisible(void) const { return m_visible; }
 
 private:
 	char m_pad000[0x104];
 	Drawable *m_next;                                                    // +0x104
+	char m_pad108[0x43c - 0x108];
+	bool m_visible;                                                      // +0x43C
 };
 
 class ClientFrameSubsystem
@@ -2709,7 +2760,9 @@ public:
 	virtual void v20(); virtual void v21(); virtual void v22();
 	virtual Drawable *getDrawableList(void);                             // +0x8C
 
-	char m_pad004[0xc8 - 4];
+	char m_pad004[0xb8 - 4];
+	int m_b8;
+	char m_padBC[0xc8 - 0xbc];
 	bool m_c8;
 };
 
@@ -4737,3 +4790,282 @@ void GameLogic::CreateWOTRMPPlayers()
  ThePlayerList->p0e();
  g_00E03138->slot44();
 }
+
+#include "../../../Include/Common/BfmeAudioEventPrefix136.h"
+
+// The audio manager's +0x138 result holds the refresh sound reference at +0xCC.
+struct MiscAudio
+{
+	char m_pad000[0xcc];
+	OpaqueRefElement4 m_cc;                                              // +0xCC
+};
+
+class Team
+{
+public:
+	unsigned int getID(void) const { return m_id; }
+
+private:
+	char m_pad00[0x34];
+	unsigned int m_id;                                                   // +0x34
+};
+
+class ExperienceLevelSystem
+{
+public:
+	bool getFlag24(void) const { return m_24; }
+
+private:
+	char m_pad00[0x24];
+	bool m_24;                                                           // +0x24
+};
+
+// TheExperienceLevelSystem is read through the ExperienceLevelStore view at its
+// rank lookup 0x00288CA6.
+extern ExperienceLevelSystem *TheExperienceLevelSystem;
+
+class ExperienceLevelStore
+{
+public:
+	int rva00288CA6(const ExperienceTracker *tracker, int level, int *required) const;
+};
+
+class ExperienceTracker
+{
+public:
+	int getLevel(void) const { return m_level; }
+	bool isTrainable(void) const;                                        // 0x0039ADAF
+	void setExperienceSink(ObjectID sink);                               // 0x003B23AF
+
+private:
+	char m_pad00[0x24];
+	int m_level;                                                         // +0x24
+};
+
+class RevivalExperienceView
+{
+public:
+	int rva000B49A1(void) const;
+};
+
+class Rva003BD306Target
+{
+public:
+	void rva0039B3D1(float level, bool flag);
+};
+
+class Rva0039B20C
+{
+public:
+	void rva0039B227(int value);
+};
+
+// The interface the +0x250 contain module's slot 31 (and Object 0x0029439D)
+// returns.
+class Rva0024877AProducer
+{
+public:
+	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
+	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
+	virtual void p08(); virtual void p09(); virtual void p0a();
+	virtual void slot2C(Object *obj);                                    // +0x2C
+	virtual void p0c(); virtual void p0d(); virtual void p0e(); virtual void p0f();
+	virtual void slot40(void);                                           // +0x40
+	virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
+	virtual void p15(); virtual void p16(); virtual void p17();
+	virtual void slot60(void);                                           // +0x60
+};
+
+class ContainModuleInterface
+{
+public:
+	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
+	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
+	virtual void c08(); virtual void c09(); virtual void c0a(); virtual void c0b();
+	virtual void c0c(); virtual void c0d(); virtual void c0e(); virtual void c0f();
+	virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13();
+	virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17();
+	virtual void c18(); virtual void c19(); virtual void c1a(); virtual void c1b();
+	virtual void c1c(); virtual void c1d(); virtual void c1e();
+	virtual Rva0024877AProducer *slot7C(void);                           // +0x7C
+	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
+	virtual void c24(); virtual void c25(); virtual void c26();
+	virtual void slot9C(Object *obj);                                    // +0x9C
+	virtual void c28(); virtual void c29();
+	virtual void slotA8(int arg);                                        // +0xA8
+	virtual void c2b(); virtual void c2c(); virtual void c2d(); virtual void c2e();
+	virtual void c2f(); virtual void c30(); virtual void c31(); virtual void c32();
+	virtual void c33(); virtual void c34(); virtual void c35(); virtual void c36();
+	virtual void c37(); virtual void c38(); virtual void c39(); virtual void c3a();
+	virtual void c3b(); virtual void c3c(); virtual void c3d(); virtual void c3e();
+	virtual void c3f(); virtual void c40(); virtual void c41(); virtual void c42();
+	virtual void c43();
+	virtual void slot110(void (*func)(void *, IntList *), IntList *ids, int mask); // +0x110
+};
+
+// The interface Object 0x0028C197 returns.
+class Rva0024877ABody
+{
+public:
+	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
+	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
+	virtual void b08(); virtual void b09(); virtual void b0a(); virtual void b0b();
+	virtual void b0c(); virtual void b0d(); virtual void b0e(); virtual void b0f();
+	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13();
+	virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17();
+	virtual void b18(); virtual void b19(); virtual void b1a(); virtual void b1b();
+	virtual void b1c(); virtual void b1d(); virtual void b1e(); virtual void b1f();
+	virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
+	virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27();
+	virtual void b28(); virtual void b29(); virtual void b2a(); virtual void b2b();
+	virtual void b2c(); virtual void b2d(); virtual void b2e(); virtual void b2f();
+	virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33();
+	virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37();
+	virtual void b38(); virtual void b39(); virtual void b3a(); virtual void b3b();
+	virtual void b3c(); virtual void b3d(); virtual void b3e(); virtual void b3f();
+	virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43();
+	virtual void b44(); virtual void b45(); virtual void b46();
+	virtual int slot11C(void);                                           // +0x11C
+	virtual void slot120(int value);                                    // +0x120
+};
+
+void Rva0024080FAdd(void *obj, IntList *ids);
+
+// The 0x50-byte snapshot 0x0024877A records per object (ctor 0x0024076D, dtor
+// 0x00240831): template name, transform, team, ID, container ID, the +0x40
+// value of the 0x0028C197 interface, the contained IDs and the experience
+// tracker's level and experience.
+class Rva0024076D
+{
+public:
+	Rva0024076D();
+	~Rva0024076D();
+
+	AsciiString m_name;                                                  // +0x00
+	Matrix3D m_transform;                                                // +0x04
+	unsigned int m_teamID;                                               // +0x34
+	ObjectID m_id;                                                       // +0x38
+	ObjectID m_containerID;                                              // +0x3C
+	int m_40;                                                            // +0x40
+	IntList m_contained;                                                 // +0x44
+	int m_level;                                                         // +0x48
+	int m_experience;                                                    // +0x4C
+};
+
+// 0x0024877A, once per logic frame: snapshot and destroy every object (only
+// those with a visible drawable, or contained in one, when TheGameClient's
+// +0xB8 is set; only 0x0028C428 objects unless TheExperienceLevelSystem's
+// +0x24 is set), then recreate each from its snapshot ("The object, '%S' was
+// refreshed.") and relink the containers and their contents.
+bool GameLogic::rva0024877A(void)
+{
+	static unsigned int lastFrame;
+	if (lastFrame < m_40) {
+	lastFrame = m_40;
+
+	bool destroyed = false;
+	_STL::list<Rva0024076D> records;
+	bool all = false;
+	bool visibleOnly = TheGameClient->m_b8 != 0;
+	if (TheExperienceLevelSystem->getFlag24()) {
+		all = true;
+		visibleOnly = false;
+	}
+
+	for (Object *obj = getFirstObject(); obj; obj = obj->getNextObject()) {
+		if (visibleOnly) {
+			bool hidden = true;
+			if (obj->getDrawable() && obj->getDrawable()->isVisible())
+				hidden = false;
+			if (obj->getContainedBy() && obj->getContainedBy()->getDrawable()
+				&& obj->getContainedBy()->getDrawable()->isVisible())
+				hidden = false;
+			if (hidden)
+				continue;
+		}
+		if (!all && !obj->rva0028C428())
+			continue;
+
+		Rva0024076D record;
+		record.m_name = obj->getTemplate()->getName();
+		record.m_transform = *obj->getTransformMatrix();
+		record.m_teamID = obj->getTeam()->getID();
+		record.m_id = obj->getID();
+		if (obj->getExperienceTracker()) {
+			record.m_level = obj->getExperienceTracker()->getLevel();
+			record.m_experience = ((RevivalExperienceView *)obj->getExperienceTracker())->rva000B49A1();
+		}
+		if (obj->getContain()) {
+			obj->getContain()->slot110(Rva0024080FAdd, &record.m_contained, 1);
+			obj->getContain()->slot110(Rva0024080FAdd, &record.m_contained, 0x10);
+			obj->getContain()->slotA8(0);
+		}
+		if (obj->getContainedBy())
+			record.m_containerID = obj->getContainedBy()->getID();
+		if (obj->rva0028C197())
+			record.m_40 = ((Rva0024877ABody *)obj->rva0028C197())->slot11C();
+		records.push_back(record);
+		destroyObject(obj);
+		destroyed = true;
+	}
+	if (destroyed)
+		processDestroyList();
+
+	_STL::list<Rva0024076D>::iterator it;
+	for (it = records.begin(); it != records.end(); ++it) {
+		Rva0024076D &record = *it;
+		const ThingTemplate *tt = TheThingFactory->findTemplate(record.m_name);
+		Team *team = TheTeamFactory->findTeamByID(record.m_teamID);
+		if (!tt || !team)
+			continue;
+
+		TheInGameUI->message(UnicodeString(L"The object, '%S' was refreshed."), record.m_name.str());
+		BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_cc, 0);
+		TheAudio->addAudioEvent(&sound);
+		Object *obj = TheThingFactory->rva002D0A23(tt, team, CreateMask(), record.m_id);
+		if (obj) {
+			obj->rva0028D412(&record.m_transform);
+			if (obj->rva0028C197())
+				((Rva0024877ABody *)obj->rva0028C197())->slot120(record.m_40);
+			if (obj->getExperienceTracker() && obj->getExperienceTracker()->isTrainable()) {
+				int level = ((const ExperienceLevelStore *)TheExperienceLevelSystem)->rva00288CA6(
+					obj->getExperienceTracker(), record.m_level, 0);
+				((Rva003BD306Target *)obj->getExperienceTracker())->rva0039B3D1((float)level, true);
+				((Rva0039B20C *)obj->m_experienceTracker)->rva0039B227(record.m_experience);
+			}
+		}
+	}
+
+	for (it = records.begin(); it != records.end(); ++it) {
+		Object *obj = findObjectByID(it->m_id);
+		if (!obj)
+			continue;
+		Object *container = findObjectByID(it->m_containerID);
+		if (container && container->getContain()) {
+			container->getContain()->slot9C(obj);
+			if (container->getContain()->slot7C()) {
+				obj->setProducer(container);
+				obj->getExperienceTracker()->setExperienceSink(container->getID());
+				container->getContain()->slot7C()->slot2C(obj);
+				container->getContain()->slot7C()->slot60();
+				container->getContain()->slot7C()->slot60();
+			}
+		}
+		for (IntList::iterator id = it->m_contained.begin(); id != it->m_contained.end(); ++id) {
+			Object *rider = findObjectByID((ObjectID)*id);
+			if (rider && obj->getContain()) {
+				obj->getContain()->slot9C(rider);
+				if (obj->rva0029439D()) {
+					rider->setProducer(obj);
+					rider->getExperienceTracker()->setExperienceSink(obj->getID());
+					((Rva0024877AProducer *)obj->rva0029439D())->slot2C(rider);
+				}
+			}
+		}
+		if (obj->getContain() && obj->getContain()->slot7C())
+			obj->getContain()->slot7C()->slot40();
+	}
+	return destroyed;
+	}
+	return false;
+}
#endif
