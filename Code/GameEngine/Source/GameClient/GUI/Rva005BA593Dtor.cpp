// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// Complete native 5BA593..5BA621 and WB 15875B0 establish the QuickMatch
// singleton cleanup, non-owning window reference+80, preferences+64 and base.
// The constructor at5BAB7E installs this same C73E24 vptr and binds the
// named AptOnline::OnlineQuickMatch callbacks; reconcile its real owner here.
#include "ascii_string.h"
class Rva005248D0 {
public:
    virtual ~Rva005248D0();
private:
    unsigned char unknown04[0x58-4];
};
class Rva0056DC4C:public Rva005248D0 {
public:
    Rva0056DC4C(void*);
    // ?Rva0056DC4C::~Rva0056DC4C present-unmatched
    virtual ~Rva0056DC4C() {}
private:
    void *owner58;
    int unknown5c;
};
class QuickMatchPreferences {
public:
    virtual ~QuickMatchPreferences();
private:
    unsigned char unknown04[0x14-4];
};
class GameWindow;
class OnlineQuickMatchWindowRef {
public:
    ~OnlineQuickMatchWindowRef();
private:
    GameWindow *m_window;
};
extern int g_Va00E06550;
void _bfme_closeAptScreen(const AsciiString&);
class AptOnline { public: class OnlineQuickMatch; };
class AptOnline::OnlineQuickMatch:public Rva0056DC4C {
public:
    virtual ~OnlineQuickMatch();
private:
    int state60;
    QuickMatchPreferences preferences;
    bool flag78,simple79,found7a;
    int gadgets7c;
    OnlineQuickMatchWindowRef color;
    GameWindow *numPlayers84,*side88,*connection8c,*ladder90;
    void *selected94,*unselected98,*unknown9c;
};
AptOnline::OnlineQuickMatch::~OnlineQuickMatch()
{
    if((int)this==g_Va00E06550) {
        _bfme_closeAptScreen("AptOnlineQuickMatch::InitGadgets");
        g_Va00E06550=0;
    }
}
