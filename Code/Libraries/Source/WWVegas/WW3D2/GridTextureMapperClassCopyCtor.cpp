// cl: /O2 /G7 /MD
//
// GridTextureMapperClass copy constructor, retail 0x00184420, 127 bytes.
// Dedicated TU so mapper.cpp keeps its matched bodies. Reset is inlined.

class WW3D
{
public:
private:
	static unsigned int SyncTime;
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
};

// WW3D::SyncTime is owned by ww3d.cpp (private static ?SyncTime@WW3D@@0IA
// at VA 0x00DEC3CC); this unit merely declares it via the class above.

class RefCountClass
{
public:
	// Match the retail base constructor and donor virtual order. Its inline
	// copies initialize one reference; Delete_This occupies slot zero.
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs;
};

class TextureMapperClass : public RefCountClass
{
public:
	TextureMapperClass(const TextureMapperClass &src);
	virtual ~TextureMapperClass();
	unsigned Stage;
};

class GridTextureMapperClass : public TextureMapperClass
{
public:
	GridTextureMapperClass(const GridTextureMapperClass &src);
	virtual ~GridTextureMapperClass();
	virtual void Reset();

	int Unk;
	int Sign;
	unsigned MSPerFrame;
	float OOGridWidth;
	unsigned GridWidthLog2;
	unsigned LastFrame;
	unsigned Offset;
	unsigned Remainder;
	unsigned CurrentFrame;
	unsigned LastUsedSyncTime;
};

// ??0TextureMapperClass@@QAE@ABV0@@Z is owned by mapper.cpp; kept inline
// here so Grid's copy ctor can inline it. Emitted as select-any; the owner
// keeps the strong copy.
inline TextureMapperClass::TextureMapperClass(const TextureMapperClass &src)
{
	Stage = src.Stage;
}

inline void GridTextureMapperClass::Reset()
{
	Remainder = 0;
	if (Sign >= 0)
		CurrentFrame = Offset;
	else
		CurrentFrame = (LastFrame - 1) - Offset;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
}

inline GridTextureMapperClass::GridTextureMapperClass(const GridTextureMapperClass &src)
	: TextureMapperClass(src)
{
	Unk = src.Unk;
	Sign = src.Sign;
	MSPerFrame = src.MSPerFrame;
	OOGridWidth = src.OOGridWidth;
	GridWidthLog2 = src.GridWidthLog2;
	LastFrame = src.LastFrame;
	Offset = src.Offset;
	Reset();
}

// The copy constructor is a header inline in mapper.cpp. This anchor retains
// its matched row body here, but the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeGridTextureMapperInlineAnchor@@YAXPAVGridTextureMapperClass@@@Z absent-from-retail
void _bfmeGridTextureMapperInlineAnchor(GridTextureMapperClass *mapper)
{
	mapper->GridTextureMapperClass::GridTextureMapperClass(*mapper);
	mapper->GridTextureMapperClass::Reset();
}
#pragma inline_depth()
