// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
// partial score=0.99 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Object;
class ThingTemplate;
enum ObjectStatusTypes
{
	STATUS_2 = 2
};
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x438 - 0x08];
	unsigned char m_dead;
};
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void countObjectsByThingTemplate(int count, const ThingTemplate *const *templates, bool flag1, int *counts, bool flag2) const;
};
// ?countObjectsByThingTemplate@Team@@QBEXHPBQBVThingTemplate@@_NPAH1@Z present-unmatched
void Team::countObjectsByThingTemplate(int count, const ThingTemplate *const *templates, bool flag1, int *counts, bool flag2) const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		ThingTemplate *tmpl = obj->m_template;
		for (int i = 0; i < count; i++) {
			if (!tmpl->isEquivalentTo(templates[i]))
				continue;
			if (flag1) {
				if ((obj->m_dead & 1) != 0)
					continue;
			}
			if (flag2) {
				if (obj->testStatus(STATUS_2))
					continue;
			}
			counts[i]++;
			break;
		}
	}
}
