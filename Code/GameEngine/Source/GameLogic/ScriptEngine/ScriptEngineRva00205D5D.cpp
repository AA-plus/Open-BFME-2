// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva00205D5D@ScriptEngine@@QAEPAURva00205D5DEntry@@ABVAsciiString@@_N@Z, retail 0x00205D5D, 128 bytes.
// ScriptEngine attack-priority-set table: 256 entries of 0x10 at 0x19100 with
// AsciiString at +4, count at 0x1A100. Searches index 1.. for compare==0,
// returns entry start (string-4); else if create and count<0x100 appends via
// AsciiString::operator=, bumps count and returns new entry; else null.
// Evidence: chain caller 0x002061D7 shares this with ScriptEngine::
// AppendDebugMessage (same this) and names the "***Error allocating attack
// priority set" limit; callees are rowed StringBase::compare and pinned
// AsciiString::operator=.
#include "ascii_string.h"
struct Rva00205D5DEntry
{
	int m_00;
	AsciiString m_name;
	int m_08;
	int m_0C;
};
class AttackPriorityInfo;
class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

// BFME 2 keeps the AI's attack priority sets in a list under TheAI's data
// (+0x18, sets at +0xFC); each set owns a list of (template name, priority).
struct Rva00205DDDItem
{
	Rva00205DDDItem *m_next;
	Rva00205DDDItem *m_prev;
	AsciiString m_templateName;
	int m_priority;
};
struct Rva00205DDDSet
{
	int m_00;
	AsciiString m_name;
	int m_defaultPriority;
	Rva00205DDDItem *m_priorityList;
	Rva00205DDDSet *m_next;
};
struct Rva00205DDDData
{
	char m_pad[0xFC];
	Rva00205DDDSet *m_attackPrioritySets;
};
struct Rva00205DDDAI
{
	char m_pad[0x18];
	Rva00205DDDData *m_data;
};
class AI;
extern AI *TheAI;

class Overridable;
class Image;
// The rowed 0x358333 provider keeps neutral pointer-valued ABI names.
class Rva0034C5E0 { public: void rva00358333(Overridable *, Image *); };

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};
extern Debug *theDebug;
template <class T> Debug &operator<<(Debug &debug, const StringBase<T> &string);
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

// Retail's debug-message locals: the ctor/dtor are the out-of-line
// StringBase(const char *) and releaseBuffer, so the view declares them only.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *string);
	~BFMERetailAsciiString();

private:
	void releaseBuffer();
	char *m_data;
};

class Parameter
{
public:
	int getInt(void) const { return m_integer; }
	const AsciiString &getString(void) const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters[12];
};

// 0x002041AC: bounds-checked name getter over the vector at +8/+0xC.
class Rva002041AC
{
public:
	AsciiString rva002041AC(unsigned int index) const;
};

class ObjectTypes
{
public:
	unsigned int getListSize(void) const { return m_end - m_begin; }

private:
	void *m_vptr;
	AsciiString m_listName;
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

class ScriptEngine
{
public:
	Rva00205D5DEntry *rva00205D5D(const AsciiString &s, bool create);
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	void AppendDebugMessage(const AsciiString &message, bool forcePause);

protected:
	void setPriorityThing(ScriptAction *action);

private:
	char m_pad[0x19100];
	Rva00205D5DEntry m_table[256];
	int m_count;
};

extern ScriptEngine *TheScriptEngine;

Rva00205D5DEntry *ScriptEngine::rva00205D5D(const AsciiString &s, bool create)
{
	for (int i = 1; i < m_count; ++i)
	{
		if (m_table[i].m_name.compare(s) == 0)
			return &m_table[i];
	}
	if (create && m_count < 0x100)
	{
		m_table[m_count].m_name = s;
		++m_count;
		return &m_table[m_count - 1];
	}
	return 0;
}

// ?getAttackInfo@ScriptEngine@@QAEPBVAttackPriorityInfo@@ABVAsciiString@@@Z,
// retail 0x00205DDD, 271 bytes. Open-BFME-1 ScriptEngineAttackInfo.cpp (same
// shape): look the name up in the live table (entry 0 is the default), else
// find the AI's attack priority set of that name, create the table entry with
// the set's default priority and its (template, priority) list, else report an
// undefined priority through the debug stream and return the default entry.
const AttackPriorityInfo *ScriptEngine::getAttackInfo(const AsciiString &name)
{
	int i;
	for (i = 1; i < m_count; ++i)
	{
		if (m_table[i].m_name.compare(name) == 0)
			return reinterpret_cast<const AttackPriorityInfo *>(&m_table[i]);
	}

	for (Rva00205DDDSet *set = ((Rva00205DDDAI *)TheAI)->m_data->m_attackPrioritySets; set; set = set->m_next)
	{
		if (set->m_name.compare(name) == 0)
		{
			Rva00205D5DEntry *info = rva00205D5D(name, true);
			if (!info)
				break;

			info->m_08 = set->m_defaultPriority;
			Rva00205DDDItem *item = set->m_priorityList->m_next;
			while (item != set->m_priorityList)
			{
				const ThingTemplate *thing = TheThingFactory->findTemplate(item->m_templateName);
				if (thing)
					reinterpret_cast<Rva0034C5E0 *>(info)->rva00358333((Overridable *)thing, (Image *)item->m_priority);
				item = item->m_next;
			}
			return reinterpret_cast<const AttackPriorityInfo *>(info);
		}
	}

	if (bfmeRva000387C0())
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		Debug &dbg = theDebug->CrashBegin(0, 0, 0);
		(dbg << "Attempting to use an undefined attack priority - '" << (const StringBase<char> &)name << "'\n").CrashDone(2);
	}
	return reinterpret_cast<const AttackPriorityInfo *>(&m_table[0]);
}

// ?setPriorityThing@ScriptEngine@@IAEXPAVScriptAction@@@Z, retail 0x00205EEC,
// 561 bytes. Zero Hour's ScriptEngineSetPriorityThing.cpp is the semantic
// donor; the BFME 2 body differs only in the table lookups (rva00205D5D and
// the 0x002041AC name getter) and in the outer-branch message spellings, which
// the bytes fix: the "invalid thing" message is a call temporary (its release
// is emitted between the two AppendDebugMessage calls) and the "error
// allocating" message is a named AsciiString local. The two inner message
// sites keep the donor's scoped BFMERetailAsciiString, whose declared-only
// ctor/dtor are retail's out-of-line StringBase and releaseBuffer.
void ScriptEngine::setPriorityThing(ScriptAction *action)
{
	AsciiString typeArgument = action->getParameter(1)->getString();
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeArgument);
	if (!types)
	{
		Overridable *thingTemplate = (Overridable *)TheThingFactory->findTemplate(typeArgument);
		if (!thingTemplate)
		{
			AppendDebugMessage(AsciiString("***Attempting to set attack priority on an invalid thing:***"), false);
			AppendDebugMessage(action->getParameter(0)->getString(), false);
			return;
		}

		Rva00205D5DEntry *info = rva00205D5D(action->getParameter(0)->getString(), true);
		if (!info)
		{
			AsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
			AppendDebugMessage(message, false);
			return;
		}
		reinterpret_cast<Rva0034C5E0 *>(info)->rva00358333(thingTemplate, (Image *)action->getParameter(2)->getInt());
		return;
	}
	else
	{
		for (unsigned int typeIndex = 0; typeIndex < types->getListSize(); typeIndex++)
		{
			AsciiString thisTypeName = ((const Rva002041AC *)types)->rva002041AC(typeIndex);
			Overridable *thisType = (Overridable *)TheThingFactory->findTemplate(thisTypeName);
			if (!thisType)
			{
				{
					BFMERetailAsciiString message("***Attempting to set attack priority on an invalid thing:***");
					AppendDebugMessage(*(const AsciiString *)&message, false);
				}
				AppendDebugMessage(action->getParameter(0)->getString(), false);
				return;
			}

			Rva00205D5DEntry *info = rva00205D5D(action->getParameter(0)->getString(), true);
			if (!info)
			{
				BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
				AppendDebugMessage(*(const AsciiString *)&message, false);
				return;
			}
			reinterpret_cast<Rva0034C5E0 *>(info)->rva00358333(thisType, (Image *)action->getParameter(2)->getInt());
		}
		return;
	}
}
