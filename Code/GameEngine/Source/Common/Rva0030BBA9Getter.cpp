// ?getTextureName@RiverArea@@QAEPAXH@Z, retail 0x0030BBA9, 11 bytes.
// Indexed getter: address of void* slot i in array at +0x40 via lea with index*4.
// Evidence: callers at 0x0007EED4 0x00082092 0x00082108 0x00083610 plus jmp 0x0007E0E5; prev Disp8Lea next Disp8Dword both no-flags.
class RiverArea
{
public:
	void *getTextureName(int i);

private:
	char m_pad[0x40];
	void *m_arr[1];
};

void *RiverArea::getTextureName(int i)
{
	return &m_arr[i];
}
