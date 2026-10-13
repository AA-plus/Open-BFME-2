// ?friend_xferSubAudioEventRTS@MilesAudioManager@@QAEXPAVXfer@@PAVBfmePoolRef10@@@Z
// partial score=0.99 date=2026-10-13
// ?friend_xferSubAudioEventRTS@MilesAudioManager@@QAEXPAVXfer@@PAVBfmePoolRef10@@@Z
// partial score=0.99 date=2026-10-12
// ?friend_xferSubAudioEventRTS@MilesAudioManager@@QAEXPAVXfer@@PAVBfmePoolRef10@@@Z
// Bank for 0x0005987D (406 B, RET 8; WB 0x0079AEB0) as a diff against
// MilesAudioManager.cpp (2026-10-12). Compiles to 406 B; every instruction
// matches except the stack slots of the +0xB78 insert's pair temporary and
// result (retail: pair at [ebp-0x34], result [ebp-0x2c] overlapping the
// dead found/map-result slots, frame 0x28; ours: frame 0x2C, result at the
// bottom). The result is a by-value return temporary in retail: the call
// would have to return the hashtable pair by value, but its row is the
// address-derived ?fwd@Rva00057D38Owner@@QAEHHH@Z (explicit result pointer)
// forwarding to the pinned Rva000556ABSub::run, so respelling it means
// changing that helper family. Named buffers of any type/scope, an inline
// by-value wrapper and 12-byte results all stay at the frame bottom.
// Needs too: 0x000519DF respelled as the constructor
// ??0Rva000519DF@@QAE@PAPAXABVBfmePoolRef10@@@Z (its body is unchanged and
// still exact; retail sets the EH state after it and releases its +4 ref).
// Levers found: the present flag read through the raw pointer (cmp [esi],0),
// found in its own block with an early return, if/else for the absent case.
#if 0
--- a/MilesAudioManager.cpp
+++ b/MilesAudioManager.cpp
@@ -1040,6 +1040,7 @@
     void rva000562A2(int key, const void *value);
     void rva0005A92A(int key, Rva0005A084Vector *output);
     void rva0005AE2B(int type, Rva0005A084Vector *output);
+    void friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef);
     void rva0005AEDD(int type, Rva0005A084Vector *output);
     void rva0005B137(void);
     void recalculateMicrophone(void);
@@ -5439,6 +5440,7 @@
 class Rva005813E
 {
 public:
+    Rva005813E(void);  // 0x00051DF9
     Rva005813E(const BfmeAudioEventPrefix136 &source);
 private:
     char m_opaque[0x90];
@@ -5510,3 +5512,66 @@
         }
     }
 }
+
+// The (saved id, event) pair 0x0005987D hands to the +0xB78 table's insert
+// (constructor 0x000519DF, insert 0x00057D38 under an address-derived owner).
+class Rva000519DF
+{
+public:
+    Rva000519DF(void **id, const BfmePoolRef10 &event);
+private:
+    void *m_id;
+    BfmePoolRef10 m_event;
+};
+class Rva00057D38Owner { public: int fwd(int result, int value); };
+class Rva002D9F9FArg;
+class Rva002D9F9FOwner;
+
+// Retail 0x0005987D (RET 8; WorldBuilder 0x0079AEB0 names it
+// MilesAudioManager::friend_xferSubAudioEventRTS): xfers a pooled event that
+// several saved objects may share. A saved id (the event pointer at save time)
+// keys the +0xB78 table so later references load the event already read; a
+// newly loaded event gets a fresh playing handle, recorded against its saved
+// handle in the +0xB6C map (or the one already mapped), before its own xfer.
+void MilesAudioManager::friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef)
+{
+    XferVersion version;
+    version.m_version = 1;
+    version.m_currentVersion = 1;
+    xfer->xferVersion(&version);
+    bool present = *reinterpret_cast<AudioEventRTS *const *>(eventRef) != 0;
+    xfer->xferBool(&present);
+    if (present) {
+        unsigned int id = reinterpret_cast<unsigned int>(eventRef->get());
+        xfer->xferInt(reinterpret_cast<int *>(&id));
+        MilesHandleMap *loaded = reinterpret_cast<MilesHandleMap *>(atB78);
+        {
+            MilesHandleMap::iterator found = loaded->find(id);
+            if (found != loaded->end()) {
+                if (xfer->isLoading())
+                    *eventRef = *reinterpret_cast<const BfmePoolRef10 *>(&found->second);
+                return;
+            }
+        }
+        {
+            char inserted[8];
+            if (xfer->isLoading())
+                eventRef->rva00053D26(reinterpret_cast<BfmePoolHolder88 *>(new Rva005813E()));
+            unsigned int savedHandle = (*eventRef)->m_playingHandle;
+            xfer->xferUnsignedInt(&savedHandle);
+            if (xfer->isLoading()) {
+                reinterpret_cast<GameMessage *>(eventRef->get())->friend_setList(reinterpret_cast<GameMessageList *>(allocateNewHandle()));
+                _STL::pair<Rva0005B256HandleMap::iterator, bool> result =
+                    reinterpret_cast<Rva0005B256HandleMap *>(atB6C)->insert(
+                        Rva0005B256HandleMap::value_type(savedHandle, reinterpret_cast<Image *>((*eventRef)->m_playingHandle)));
+                if (!result.second)
+                    reinterpret_cast<GameMessage *>(eventRef->get())->friend_setList(reinterpret_cast<GameMessageList *>(result.first->second));
+            }
+            reinterpret_cast<Rva00057D38Owner *>(loaded)->fwd(reinterpret_cast<int>(inserted),
+                reinterpret_cast<int>(&Rva000519DF(reinterpret_cast<void **>(&id), *eventRef)));
+            reinterpret_cast<Rva002D9F9FOwner *>(eventRef->get())->rva002D9F9F(reinterpret_cast<Rva002D9F9FArg *>(xfer));
+        }
+    } else if (xfer->isLoading()) {
+        eventRef->rva000519BD();
+    }
+}
#endif
