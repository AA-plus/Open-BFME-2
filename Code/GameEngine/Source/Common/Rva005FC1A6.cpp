// cl: /MD
// ?rva005FC1A6@Rva005FC1A6@@QAEXXZ @0x005FC1A6 8B.
// Forwarder thunk: the receiver at +4 of this object is handed to the rowed
// 0x005FC02A body with a tail jump. Evidence: retail bytes 8b 49 04 e9 and the
// owner file Rva005FC02A.cpp, whose comment records this caller thunk loading
// ecx+4.
class Rva005FC02A
{
public:
	void rva005FC02A();
};

class Rva005FC1A6
{
public:
	void rva005FC1A6();
private:
	char m_pad00[4];
	Rva005FC02A *m_object;	// +0x04
};

void Rva005FC1A6::rva005FC1A6()
{
	m_object->rva005FC02A();
}
