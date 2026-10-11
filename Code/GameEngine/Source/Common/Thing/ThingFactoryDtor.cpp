// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1ThingFactory@@UAE@XZ, retail 0x002D0588 (71 bytes, EH): the destructor
// of the subsystem whose vtable 0x00C0233C its constructor 0x002D0E14 and
// deleting destructor 0x002D09F5 install (opaque pin ??1Rva002D0588). As in
// Zero Hour's ThingFactory::~ThingFactory it frees the template database
// (rowed ThingFactory::freeDatabase 0x002D0469, called on the same object),
// then the template hash map at +0x14 is destroyed (its own EH copy of the
// AsciiString-keyed table destructor at 0x002CFF2D, pinned under an
// address-named member class) and the SubsystemInterface base destructor
// 0x001B4E74 runs.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_base04[8];
};

class Rva002CFF2D
{
public:
	~Rva002CFF2D();
private:
	char m_data[0x14];
};

class ThingFactory : public SubsystemInterface
{
public:
	virtual ~ThingFactory();
private:
	void freeDatabase();
	void *m_firstTemplate;	// +0x0C
	unsigned int m_nextTemplateID;	// +0x10
	Rva002CFF2D m_templateHashMap;	// +0x14
};

ThingFactory::~ThingFactory()
{
	freeDatabase();
}
