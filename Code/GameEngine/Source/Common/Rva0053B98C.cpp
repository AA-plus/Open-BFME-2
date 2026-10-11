// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
// ?Rva0053B98CUpdate@@YAXPAVObject@@PAX@Z, retail 0x0053B98C, 193 bytes.
// Chain from Object::rva0028FBBE: list fill over Info {cur,max,arr} with
// global 8B entry array at g_00E05E20, Image via getButtonImage, count via
// rva0028FBBE, Gadget image plus userdata helpers, first-item select.
// Evidence: free __cdecl 2 args, rowed callees, offsets +4/+0x74, stride 8.

class ThingTemplate;
class Image;
class GameWindow
{
public:
	int winEnable(bool enable);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
};

struct Rva0053E754Entry
{
	GameWindow *win;
	int unk;
};
// Retail's own 32-entry window/id array at RVA 0x00A05E20: past .data's raw end
// (file offset 0x009DCC08), so the image loads it zero and the two rowed bodies
// below fill it as buttons are registered (this unit's writer and the rowed
// ControlBar reader that scans it). A tentative definition: the slots are store
// targets, so zero is the initial value both bodies are written against. MSVC
// mangles a namespace-scope array through its decayed pointer, so this is the
// symbol the reader's `g_00E05E20[i].m_window == window` scan already names.
// Symbol ?g_00E05E20@@3PAURva0053E754Entry@@A, defined below.
extern Rva0053E754Entry g_00E05E20[];
Rva0053E754Entry g_00E05E20[32];

struct Info0053B98C
{
	int cur;
	int max;
	GameWindow **arr;
};

class Object
{
public:
	int rva0028FBBE();
};

const Image *__cdecl getButtonImage(ThingTemplate *tmpl, Object *obj);
void __cdecl GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *win, const Image *img);
void __cdecl Rva003284ED(GameWindow *win, int v);

void __cdecl Rva0053B98CUpdate(Object *obj, void *infoParam)
{
	Info0053B98C *info = (Info0053B98C *)infoParam;
	if (info->cur > info->max)
		return;
	ThingTemplate *tmpl = *(ThingTemplate **)((char *)obj + 4);
	const Image *img = getButtonImage(tmpl, obj);
	int count = obj->rva0028FBBE();
	int i = 0;
	if (count <= 0)
		return;
	do {
		GameWindow *w = info->arr[info->cur];
		g_00E05E20[info->cur].win = w;
		g_00E05E20[info->cur].unk = *(int *)((char *)obj + 0x74);
		info->cur++;
		GadgetButtonSetEnabledImage_Rva002C0433(w, img);
		Rva003284ED(w, 0);
		if (i == 0) {
			w->winEnable(true);
			w->winSetStatus(8);
			w->winClearStatus(0x200);
		}
		else {
			w->winEnable(false);
			w->winClearStatus(8);
			w->winSetStatus(0x200);
		}
		i++;
	} while (i < count);
}
