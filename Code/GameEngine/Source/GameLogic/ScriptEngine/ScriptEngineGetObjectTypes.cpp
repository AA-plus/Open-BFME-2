// cl: /O1 /G7 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?getObjectTypes@ScriptEngine@@QAEPAVObjectTypes@@ABVAsciiString@@@Z @0x00357651 60B
// ScriptEngine::getObjectTypes: search m_allObjectTypeLists (+0x1A4C8 vector) by list name.
// Donor: ZH ScriptEngine::getObjectTypes (ScriptEngine.cpp:5860) loop with null skip and
// getListName compare. Target evidence: adjacent ScriptEngine::getQualifiedTriggerAreaByName
// at 0x0035768D, callers 0x00358286 (doObjectTypeListMaintenance push_back to +0x1A4C8) and
// 0x003C449C pass ScriptEngine this, callee 0x005C4AD1 lea+4 is ObjectTypes name field and
// 0x000069D6 is StringBase<char>::compare. Layout +0x1A4C8 from matched removeObjectTypes.

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

#include "ascii_string.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &,unsigned int const &); }
// bfme link decl-only end


class ObjectTypes {
public:
 ObjectTypes(const AsciiString &);
 virtual ~ObjectTypes();
 void remove(const AsciiString &);
 unsigned getListSize() const { return m_types.size(); }
private:
 AsciiString m_name;
 _STL::vector<AsciiString> m_types;
};
class Rva00376A62 { public: void rva00376B50(const AsciiString &); };

class ScriptEngine
{
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
 void doObjectTypeListMaintenance(const AsciiString &,const AsciiString &,bool);

protected:
 void removeObjectTypes(ObjectTypes *);

private:
	char m_pad[0x1A4C8];
	_STL::vector<ObjectTypes *> m_lists; // +0x1A4C8
};

ObjectTypes *ScriptEngine::getObjectTypes(const AsciiString &objectTypeList)
{
	for (ObjectTypes **it = m_lists.begin(); it != m_lists.end(); ++it) {
		if (*it == 0)
			continue;
		void *nameField = ((Rva005C4AD1LeaField *)*it)->get();
		if (((const StringBase<char> *)nameField)->compare((const StringBase<char> &)objectTypeList) == 0)
			return *it;
	}
	return 0;
}

// Native358286..358317 RET12; ScriptEngine getObjectTypes/list ownership
// and the named ObjectTypes constructor establish the operation independently
// of WB's enclosing PerfTimer inline name. ZH doObjectTypeListMaintenance at
// donor9e3be919b10a supplies semantics; target uses global new and vector1A4C8.
void ScriptEngine::doObjectTypeListMaintenance(const AsciiString &list,const AsciiString &type,bool add) {
 ObjectTypes *current = getObjectTypes(list);
 if(!current) {
  ObjectTypes *newVec = new ObjectTypes(list);
  m_lists.push_back(newVec);
  current = newVec;
 }
 if(add) ((Rva00376A62*)current)->rva00376B50(type);
 else current->remove(type);
 if(current->getListSize()==0) removeObjectTypes(current);
}
