// cl: /GX /MD /O1
//
// BFME2's online quick match screen Apt callbacks
// "AptOnline::OnlineQuickMatch::WidenSearch" (0x005BAA2B) and "::Cancel"
// (0x005BAAA3), bound by those names as member pointers by the screen's
// registration; that binding is their only reference. Each posts a peer
// thread request (Rva0059FF9DDo.cpp's record and queue views).

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();

	int unknown_00;
	unsigned char m_rest[0x1EC - 0x04];
};

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(PeerRequest *rec);
};

class GameSpyPeerMessageQueueInterface;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class Rva00222A8BTarget
{
public:
	int invoke(void *movie, const char *name, int count, const char *arg, void *a, void *b, void *c, void *d);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

// The owner keeps its Apt movie at +0x274 (as the custom match screen's).
struct AptOnlineQuickMatchOwnerView
{
	unsigned char m_pad000[0x274];
	void *m_movie;	// +0x274
};

// Native Cancel forwards through the screen's +0x58 owner to the verified
// AptOnline::rva00516F08 body. Represent its named nested screen as a nested
// class so the owner uses that same AptOnline identity; no owner layout is
// accessed here. The registered callback names and screen layout are retained.
class AptOnline
{
public:
    void rva00516F08();

    class OnlineQuickMatch
    {
    public:
        void WidenSearch(const char *unused);
        void Cancel(const char *unused);
        int rva005BAECA(int window, int msg, unsigned char key, int flags);

    private:
        unsigned char m_pad00[0x58];
        AptOnline *m_owner; // +0x58
        unsigned char m_pad5c[0x60 - 0x5C];
        int m_state; // +0x60
    };
};

// Retail 0x005BAA2B, 88 bytes: "AptOnline::OnlineQuickMatch::WidenSearch"
// posts request 0x11.
void AptOnline::OnlineQuickMatch::WidenSearch(const char *unused)
{
	PeerRequest request;
	request.unknown_00 = 0x11;
	((Global003EF728V6 *)TheGameSpyPeerMessageQueue)->f6(&request);
}

// Retail 0x005BAAA3, 104 bytes: "AptOnline::OnlineQuickMatch::Cancel" posts
// request 0x12, resets the state and tells the owner.
void AptOnline::OnlineQuickMatch::Cancel(const char *unused)
{
	PeerRequest request;
	request.unknown_00 = 0x12;
	((Global003EF728V6 *)TheGameSpyPeerMessageQueue)->f6(&request);
	m_state = 0;
	m_owner->rva00516F08();
}

// Retail 0x005BAECA, 105 bytes (RET 0x10): the screen's keyboard handler
// (vtable 0x00873E24 slot 4, shaped as the custom match screen's). Escape
// pressed (message 0x15, key 1, flag 1) while searching (state 1) tells the
// movie "CallChild" with "EscapeKeyPressed" and cancels the search; in
// states 2 and 3 the key is swallowed. Anything else is not handled.
int AptOnline::OnlineQuickMatch::rva005BAECA(int window, int msg, unsigned char key, int flags)
{
	if (msg == 0x15)
	{
		switch (key)
		{
		case 1:
			if (flags & 1)
			{
				if (m_state == 1)
				{
					(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(((AptOnlineQuickMatchOwnerView *)m_owner)->m_movie, "CallChild", 1, "EscapeKeyPressed", 0, 0, 0, 0);
					Cancel(0);
					return 1;
				}
				if (m_state == 3)
					return 1;
				if (m_state == 2)
					return 1;
			}
			break;
		}
	}
	return 0;
}
