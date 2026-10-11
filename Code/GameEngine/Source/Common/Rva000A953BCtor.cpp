// cl: /DNDEBUG /MD
// ??0Rva000A953B@@QAE@XZ @0x000A953B 22B
// Honest address ctor for class whose only member is Coord2D m_arr[3] at +0.
// Retail pushes element ctor VA 0x87A6A9 (rowed Coord2D empty ctor at
// 0x47A6A9, ICF twin with Region2D/Region3D), count 3, stride 8, and calls
// rowed vector_constructor_iterator at 0x1423. Precedent Rva0007671FCtor
// (22B, 4x0x10 Region2D) same recipe. Evidence: unlock lane, caller 0xAB5D7.
class Coord2D
{
public:
	Coord2D();
	float x;
	float y;
};
class Rva000A953B
{
public:
	Rva000A953B();
private:
	Coord2D m_arr[3];
};
Rva000A953B::Rva000A953B()
{
}
class Rva000A9551
{
public:
	Rva000A9551();
private:
	Coord2D m_arr[2];
};
Rva000A9551::Rva000A9551()
{
}

static __declspec(noinline) void rva000A94F9(Coord2D &low, Coord2D &high, const Coord2D &point)
{
	if (point.x < low.x) low.x = point.x;
	else if (point.x > high.x) high.x = point.x;
	if (point.y < low.y) low.y = point.y;
	else if (point.y > high.y) high.y = point.y;
}

// ?callerA94F9 absent-from-retail
void callerA94F9(Coord2D &low, Coord2D &high, const Coord2D &point)
{
	rva000A94F9(low, high, point);
}
