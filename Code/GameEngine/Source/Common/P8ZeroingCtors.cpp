// cl: /DNDEBUG /MD /EHsc

// Trimmed port of Open-BFME-1
// Code/GameEngine/Source/Common/P8ZeroingCtors.cpp (near-miss donor:
// ??0Gen0090BE20@@QAE@PAX@Z @0x0090BE20, 73B). Only the one constructor served
// for BFME2 is carried here; the donor's other nine share the shape but their
// BFME2 addresses are unserved, so they stay out (the gate refuses unrowed
// definitions in a staged TU).
//
// WHAT THE BODY IS. A constructor that zeroes one owned member and hands its
// argument to a private initialiser. The exception frame is the tell: `this`
// is saved into a frame slot, state 0 is set across the call and fs:[0]
// restored afterwards -- MSVC arranging to destroy an ALREADY-CONSTRUCTED
// member if the call throws. So the class owns a member with a non-trivial
// destructor whose default constructor is inline and only zeroes a pointer.
// Written as a plain field assignment the frame vanishes, because nothing
// would need unwinding.
//
// IDENTITY IS NOT RECOVERED. Owner and initialiser are named for the
// constructor's BFME2 address; the owned member is modelled as one pointer
// because that is all the body touches.

class BfmeMapPictureTexture
{
public:
	BfmeMapPictureTexture() : m_bfmeData( 0 ) {}
	~BfmeMapPictureTexture();
	void *m_bfmeData;
};

class Gen001811E0
{
public:
	Gen001811E0( void *source );

private:
	Gen001811E0 *bfmeInit( void *source );

	BfmeMapPictureTexture m_bfmeOwned;
};

// ??0Gen001811E0@@QAE@PAX@Z
Gen001811E0::Gen001811E0( void *source )
{
	bfmeInit( source );
}
