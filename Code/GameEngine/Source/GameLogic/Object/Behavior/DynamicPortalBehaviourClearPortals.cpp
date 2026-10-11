// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0046094C@DynamicPortalBehaviour@@QAEXXZ, retail 0x0046094C (112 bytes):
// called by the destructor 0x00460C18 and upgradeRemovalImplementation
// 0x00460C7D. With the +0x3C portals-created flag set it removes each of the
// six waypoint slots at +0x24 from TheAI's +0x10 pathfinder (rowed
// 0x002E9042) when the waypoint reports so (rowed 0x002E6ECA), deletes it
// through its slot-0 destructor and clears the slot, then lets the
// pathfinder rebuild (rowed 0x002E7023) and clears the flag. The same body
// as FakePathfindPortalBehaviour's two-slot 0x0046183B. The method name is a
// placeholder.

class AI;
extern AI *TheAI;

class Rva002E9042
{
public:
	void rva002E9042(void *arg);
};

class Rva004618D4Caller
{
public:
	void rva002E7023();
};

struct Rva004618D4AI
{
	char m_pad00[0x10];
	Rva002E9042 *m_p10;
};

class Rva002E6ECA { public: virtual void *destroy(unsigned); int get() const; };
typedef Rva002E6ECA Rva0046094CWaypoint;

class DynamicPortalBehaviour
{
public:
	void rva0046094C();
private:
	char m_pad00[0x24];
	Rva0046094CWaypoint *m_24[6];	// +0x24
	bool m_3C;	// +0x3C
};

void DynamicPortalBehaviour::rva0046094C()
{
 if(m_3C) {
  Rva0046094CWaypoint **p=m_24;
  for(int i=0;i<6;++i,++p) {
   Rva0046094CWaypoint *wp=*p;
   if(wp) {
    if((unsigned char)wp->get()) (*reinterpret_cast<Rva004618D4AI**>(&TheAI))->m_p10->rva002E9042(wp);
    ::operator delete(*p ? (*p)->destroy(0) : 0);
    *p=0;
   }
  }
  reinterpret_cast<Rva004618D4Caller*>((*reinterpret_cast<Rva004618D4AI**>(&TheAI))->m_p10)->rva002E7023();
  m_3C=false;
 }
}
