// cl: /MD
//
// ?rva00330BDB@Rva00330BDB@@QBEMXZ retail 0x00330BDB 8B this-adjusting
// forwarder: this-0x34 then tail-jmp to rowed Rva0030B719Shape::rva0030B706
// 0x0030B706 float at +0x1C. Callers tail-jmp here; same adjustor family as
// the 0x00330C22 this-0x3C center forwarder. Honest address names.

typedef float Real;

class Rva0030B719Shape
{
public:
	Real rva0030B706() const;
	Real getRadius() const;
};

class Rva00330BDB
{
public:
	Real rva00330BDB() const;
	Real rva00330BE3() const;
};

Real Rva00330BDB::rva00330BDB() const
{
	const Rva0030B719Shape *shape = (const Rva0030B719Shape *)((const char *)this - 0x34);
	return shape->rva0030B706();
}

// Native 330BE3..330BEB is the adjacent eight-byte float forwarder.
// Its receiver adjustment is independently -0x34 and its target is the
// rowed 30B719 radius getter. The rowed 330C50 constructor and its seven
// vtordisp thunks establish a virtual interface at +3C over the +8 shape;
// this source keeps the existing address-derived interface view.
Real Rva00330BDB::rva00330BE3() const
{
	const Rva0030B719Shape *shape = (const Rva0030B719Shape *)((const char *)this - 0x34);
	return shape->getRadius();
}
