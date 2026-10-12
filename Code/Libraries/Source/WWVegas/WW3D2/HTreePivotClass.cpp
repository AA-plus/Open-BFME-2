// cl: /DNDEBUG /MD /EHsc
//
// PivotClass, BFME 2's 0x58-byte hierarchy pivot.
//
// The layout is read from the constructor at 0x00197830 and the member-wise
// assignment at 0x00197950: the name, the parent, two blocks each holding an
// identity rotation (0,0,0,1) and a zero translation, the index, the
// visibility flag and a float that starts at 1.0.  The constructor clears the
// name last, the way Zero Hour's PivotClass constructor does.  Only the
// offsets and initial values are proven; the block and float names are not
// recovered.  HTreeClass's copy constructor (0x001662A0) builds these through
// the vector constructor iterator and copies them with operator=.  The copy
// constructor at 0x001978A0 (between the two) copies each block (rotation then
// translation, the translation through its own copy constructor) and the name
// last; that shape needs the block to be one sub-object with a copy constructor.

// An identity rotation (0,0,0,1) and a zero translation, by the values the
// constructor stores.  Both assign member by member: retail's operator= copies
// every float with its own move, where a compiler-generated block assignment
// would move each block as a unit.
struct BfmePivotRotation
{
	BfmePivotRotation() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
	BfmePivotRotation &operator=(const BfmePivotRotation &that) { X = that.X; Y = that.Y; Z = that.Z; W = that.W; return *this; }
	float X, Y, Z, W;
};

struct BfmePivotTranslation
{
	BfmePivotTranslation() : X(0.0f), Y(0.0f), Z(0.0f) {}
	BfmePivotTranslation(const BfmePivotTranslation &that) : X(that.X), Y(that.Y), Z(that.Z) {}
	BfmePivotTranslation &operator=(const BfmePivotTranslation &that) { X = that.X; Y = that.Y; Z = that.Z; return *this; }
	float X, Y, Z;
};

struct BfmePivotBlock
{
	BfmePivotBlock() {}
	BfmePivotBlock(const BfmePivotBlock &that) : R(that.R), T(that.T) {}
	BfmePivotBlock &operator=(const BfmePivotBlock &that) { R = that.R; T = that.T; return *this; }
	BfmePivotRotation R;
	BfmePivotTranslation T;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
#pragma intrinsic(memcpy)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
struct PivotClass
{
public:
	PivotClass();
	PivotClass(const PivotClass &that);
	PivotClass &operator=(const PivotClass &that);

	char Name[16];
	PivotClass *Parent;					// +0x10
	BfmePivotBlock m_bfme14;			// +0x14
	BfmePivotBlock m_bfme30;			// +0x30
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};

PivotClass::PivotClass() :
	Parent(0),
	Index(0),
	IsVisible(true),
	m_bfme54(1.0f)
{
	Name[0] = 0;
}

PivotClass::PivotClass(const PivotClass &that) :
	Parent(that.Parent),
	m_bfme14(that.m_bfme14),
	m_bfme30(that.m_bfme30),
	Index(that.Index),
	IsVisible(that.IsVisible),
	m_bfme54(that.m_bfme54)
{
	memcpy(Name, that.Name, sizeof(Name));
}

PivotClass &PivotClass::operator=(const PivotClass &that)
{
	if (this != &that) {
		memcpy(Name, that.Name, sizeof(Name));
		Parent = that.Parent;
		m_bfme14 = that.m_bfme14;
		m_bfme30 = that.m_bfme30;
		Index = that.Index;
		IsVisible = that.IsVisible;
		m_bfme54 = that.m_bfme54;
	}
	return *this;
}
