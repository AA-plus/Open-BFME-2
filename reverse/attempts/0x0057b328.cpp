// ?rva0057B328@Rva0057B328@@QAEXM@Z
// partial score=0.95 date=2026-10-13
// ?rva0057B328@Rva0057B328@@QAEXM@Z
// partial score=0.95 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0057B328@Rva0057B328@@QAEXM@Z 0x0057B328 91B. Walks the list at +0x44 and,
// for each node's object, adds the float field's value to the offset value and
// hands it back to the field's setter; then calls the owner's finish at +0x40.
// The incoming offset is replaced by (+0x30 - value) before the walk.
class Rva004987FEFloatField
{
public:
	float get() const;
};

class Rva005D3FE4
{
public:
	void rva005D3FE4(float value);
};

namespace StrategicHUD
{
class ChecklistUIImpl;
}

struct Rva0057B328Node;

struct Rva0057B328Obj
{
	unsigned char m_pad00[8];
	Rva004987FEFloatField m_field; // +0x08
};

struct Rva0057B328Node
{
	Rva0057B328Node *m_next; // +0x00
	unsigned char m_pad04[4];
	Rva0057B328Obj *m_obj; // +0x08
};

struct Rva0057B328List
{
	Rva0057B328Node *m_head; // +0x00
};

namespace StrategicHUD
{
class ChecklistUIImpl
{
public:
	void rva0057B16D();
	unsigned char m_pad00[0x30];
	Rva0057B328Node *m_end; // +0x30
};
}

class Rva0057B328
{
public:
	void rva0057B328(float value);
private:
	unsigned char m_pad00[0x30];
	float m_30; // +0x30
	unsigned char m_pad34[0x0C];
	StrategicHUD::ChecklistUIImpl *m_40; // +0x40
	Rva0057B328List *m_44; // +0x44
};

void Rva0057B328::rva0057B328(float value)
{
	Rva0057B328 *self = this;
	StrategicHUD::ChecklistUIImpl *owner = self->m_40;
	Rva0057B328List *list = self->m_44;
	Rva0057B328Node *end = owner->m_end;
	Rva0057B328Node *node = list->m_head;
	value = self->m_30 - value;
	if (node != end)
	{
		do
		{
			Rva004987FEFloatField *field = &node->m_obj->m_field;
			float sum = field->get() + value;
			reinterpret_cast<Rva005D3FE4 *>(field)->rva005D3FE4(sum);
			node = node->m_next;
		} while (node != end);
	}
	self->m_40->rva0057B16D();
}
