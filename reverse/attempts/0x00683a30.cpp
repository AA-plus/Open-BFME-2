// _CommUdpProcess
// partial score=0.65 date=2026-10-12
// cl: /DNDEBUG /MD /GX /Od /GZ /GS

#define _DLL
#include <string.h>

// EA's DirtySock CommUDP transport, which BFME uses for its GameSpy/online
// traffic. It has no counterpart in the vendored Zero Hour reference, and no
// __FILE__ string for it survives in the executable, so the directory name here
// is inferred from the module prefixes retail logs -- commudp, commtcp,
// protoadvt, NetGameUtil -- and from the sibling EA middleware that already
// lives under Code/Libraries/Source (Compression/EAC). Move it if better
// evidence turns up; only the `source` column of these rows has to follow.
//
// The surviving log strings establish the named entry points; the address-
// derived Rva helpers are retained by their retail RVAs and call graph. They
// are declared extern "C" because DirtySock is a C library.
//
// The lockstep path does not run through here -- that is SAGE's own udp.cpp.

struct Rva007FD4E0Socket;
struct Rva007FF720SockAddr;
struct Rva00816BF0Comm;
struct Rva00816F60Message;

extern "C" {
	int CommUDPWrite(void *ref, void *packet);
	int CommUDPConnect(void *ref, const char *addr, int bind, int peer);
	int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider);
	int Rva007FD920(void *socket, const void *data, int length, int flags, void *address, int addressLength);
	unsigned int Rva007FEA00();
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void *Rva007FD2D0(int family, int type, int protocol);
	int Rva007FD510(void *socket, const void *address, int addressLength);
	void Rva007FD3F0(void *socket);
	void Rva00818FF0(void *ref, const char *text);
	int Rva00819590(void *ref, void *socket, const void *peerAddress);
	void Rva007FEBD0(void *lock);
	void Rva007FECB0(void *lock);
	void Rva00817640(void *ref);
	int Rva007FDA50(struct Rva007FD4E0Socket *socket, char *buffer, int length, int flags, char *from, int *fromLength);
	int Rva007FF720(const struct Rva007FF720SockAddr *first, const struct Rva007FF720SockAddr *second);
	int CommUdpProcess(unsigned int tick);
	void Rva008186C0(struct Rva00816BF0Comm *comm, struct Rva00816F60Message *message);
	int Rva008187E0(struct Rva00816BF0Comm *comm, struct Rva00816F60Message *record);
	int Rva00818620(struct Rva00816BF0Comm *comm);
	void Rva00818AD0(struct Rva00816BF0Comm *comm);
	int Rva00816F60(struct Rva00816BF0Comm *comm);
	struct Rva00816BF0Comm *g_Rva0130B188List;
}

extern "C" char g_Rva0130AF38Lock[4];
extern int g_Rva0130AD08Count;

int Rva007FE780Printf(const char *format, ...);
// The C++ printf spelling and rowed C printer both resolve to retail VA 0x0066AC50.
#pragma comment(linker, "/alternatename:?Rva007FE780Printf@@YAHPBDZZ=_Rva007FE780")

// Always fails: it logs "CommUDPResolve: Resolve functionality not supported by
// CommUDP" and returns the error.
int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider)
{
	Rva007FE780Printf("CommUDPResolve: Resolve functionality not supported by CommUDP\n");
	return -1;
}

extern "C" void Rva00817230(void)
{
}

// Hands a datagram to the socket layer, logging "CommUDPWrite: SocketSendto
// returned %d" on the way out.
int CommUDPWrite(void *ref, void *packet)
{
	int result;
	int packetLength = *(int *)packet + 8;
	result = Rva007FD920(*(void **)((char *)ref + 0x7C),
	                     (char *)packet + 8, packetLength, 0,
	                     (char *)ref + 0x80, 0x10);
	if (result == packetLength) {
		*(unsigned int *)((char *)ref + 0xD8) = Rva007FEA00();
		*(int *)((char *)ref + 0x5C) += packetLength;
		++*(int *)((char *)ref + 0x64);
		if (*(int *)((char *)packet + 8) != 6) {
			*(int *)((char *)ref + 0xB4) = 0;
		}
	} else {
		Rva007FE780Printf("CommUDPWrite: SocketSendto returned %d\n", result);
		*(int *)((char *)ref + 0xD4) = result;
		result = -1;
	}
	return result;
}

// Opens the port. Logs "CommUdpConnect: addr=%08x, bind=%d, peer=%d
// connident=0x%08x" on entry and "CommUDPConnect: bind to %d failed with %d"
// when the bind is refused, then retries with port 0.
int CommUDPConnect(void *ref, const char *addr, int bind, int peer)
{
	int result;
	int iConnPort;
	int iListenPort;
	unsigned int uAddr;
	void *socket;
	unsigned char bindaddr[0x10];
	unsigned char peeraddr[0x10];
	unsigned int temp;

	*(unsigned short *)&peeraddr[0] = 2;
	*(unsigned short *)&peeraddr[2] = 0;
	*(unsigned int *)&peeraddr[4] = 0;
	*(unsigned int *)&peeraddr[8] = 0;
	*(unsigned int *)&peeraddr[12] = 0;
	*(unsigned short *)&bindaddr[0] = 2;
	*(unsigned short *)&bindaddr[2] = 0;
	*(unsigned int *)&bindaddr[4] = 0;
	*(unsigned int *)&bindaddr[8] = 0;
	*(unsigned int *)&bindaddr[12] = 0;
	result = Rva007FFDD0(&uAddr, &iListenPort, &iConnPort, addr);
	if ((result & 3) != 3) {
		return -3;
	}
	if (iConnPort == 0) {
		iConnPort = iListenPort;
		++iListenPort;
	}
	Rva00818FF0(ref, addr);
	Rva007FE780Printf("CommUdpConnect: addr=%08x, bind=%d, peer=%d connident=0x%08x\n",
	                   uAddr, iListenPort, iConnPort, *(int *)((char *)ref + 0x94));
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	bindaddr[2] = (unsigned char)(iListenPort >> 8);
	bindaddr[3] = (unsigned char)iListenPort;
	result = Rva007FD510(socket, bindaddr, 0x10);
	if (result < 0) {
		Rva007FE780Printf("CommUDPConnect: bind to %d failed with %d\n", iListenPort, result);
		bindaddr[2] = 0;
		bindaddr[3] = 0;
		result = Rva007FD510(socket, bindaddr, 0x10);
		Rva007FE780Printf("CommUDPConnect: bind to 0 with result %d\n", result);
	}
	if (result < 0) {
		Rva007FD3F0(socket);
		return -5;
	}
	temp = uAddr;
	peeraddr[7] = (unsigned char)temp; temp >>= 8;
	peeraddr[6] = (unsigned char)temp; temp >>= 8;
	peeraddr[5] = (unsigned char)temp; temp >>= 8;
	peeraddr[4] = (unsigned char)temp;
	peeraddr[2] = (unsigned char)(iConnPort >> 8);
	peeraddr[3] = (unsigned char)iConnPort;
	*(int *)((char *)ref + 0xD4) = 0;
	return Rva00819590(ref, socket, peeraddr);
}

extern "C" {
	void CommUdpSetup(void *ref, void *packet, void *from);
	int CommUdpPoke(void *ref);
	int CommUdpListen(void *ref, const char *text);
	int CommUDPSend(void *ref, const void *buffer, int length, int flags);
	void Rva00818500(void *ref, void *from);
	int Rva00819090(void *ref, void *socket, const void *address);
}

// Answers an INIT with a CONN, and warns "commudp: warning - connident
// mismatch" when the connection identifier does not line up.
void CommUdpSetup(void *ref, void *packet, void *from)
{
	if (*(int *)packet != 0) {
		return;
	}

		if (*(int *)((char *)packet + 0x0C) != *(int *)((char *)ref + 0x94)) {
			Rva007FE780Printf("commudp: warning - connident mismatch\n");
			if (*(int *)((char *)packet + 8) == 1) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		} else {
			*(unsigned int *)((char *)ref + 0xDC) = Rva007FEA00() - 1000;
			if (*(int *)((char *)packet + 8) == 1) {
				Rva00818500(ref, from);
				Rva007FE780Printf("CommUdpSetup: sending CONN in response to INIT\n");
				*(int *)((char *)packet + 8) = 2;
				((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, packet);
			} else if (*(int *)((char *)packet + 8) == 2) {
				if (*(int *)((char *)ref + 0x90) == 2) {
					Rva00818500(ref, from);
					*(int *)((char *)ref + 0x90) = 4;
				}
			} else if (*(int *)((char *)packet + 8) == 3 &&
			           *(int *)((char *)ref + 0x90) == 4) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		}
}

// Sends a poke packet to prod a peer whose address may have moved.
int CommUdpPoke(void *ref)
{
	char packet[0x228];
	Rva007FE780Printf("CommUdpPoke: sending poke packet\n");
	*(int *)&packet[0] = 0;
	*(int *)&packet[8] = 5;
	*(int *)&packet[12] = *(int *)((char *)ref + 0x94);
	return ((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, &packet);
}

// Puts the socket into listening mode for an incoming CommUDP connection.
int CommUdpListen(void *ref, const char *text)
{
	int result;
	int iListenPort;
	int iConnPort;
	unsigned int poke;
	void *socket;
	unsigned char bindaddr[0x10];
	unsigned int temp;

	*(unsigned short *)&bindaddr[0] = 2;
	*(unsigned short *)&bindaddr[2] = 0;
	*(unsigned int *)&bindaddr[4] = 0;
	*(unsigned int *)&bindaddr[8] = 0;
	*(unsigned int *)&bindaddr[12] = 0;
	if ((Rva007FFDD0(&poke, &iListenPort, &iConnPort, text) & 2) == 0) {
		return -3;
	}
	bindaddr[2] = (unsigned char)(iListenPort >> 8);
	bindaddr[3] = (unsigned char)iListenPort;
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	result = Rva00819090(ref, socket, bindaddr);
	Rva00818FF0(ref, text);
	Rva007FE780Printf("CommUdpListen: err=%d, bind=%d, connident=0x%08x\n",
	                   result, iListenPort, *(int *)((char *)ref + 0x94));
	if (result == 0 && poke != 0) {
		if (iConnPort == 0) {
			iConnPort = iListenPort + 1;
		}
		Rva007FE780Printf("CommUdpListen: poke=%08x:%d\n", poke, iConnPort);
		*(unsigned short *)((char *)ref + 0x80) = 2;
		*(unsigned short *)((char *)ref + 0x82) = 0;
		*(unsigned int *)((char *)ref + 0x84) = 0;
		*(unsigned int *)((char *)ref + 0x88) = 0;
		*(unsigned int *)((char *)ref + 0x8C) = 0;
		temp = poke;
		*((unsigned char *)ref + 0x87) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x86) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x85) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x84) = (unsigned char)temp;
		*((unsigned char *)ref + 0x82) = (unsigned char)(iConnPort >> 8);
		*((unsigned char *)ref + 0x83) = (unsigned char)iConnPort;
	}
	*(int *)((char *)ref + 0xD4) = 0;
	return result;
}

// Queues an outbound packet, rejecting anything past the limit with
// "CommUDP: Oversized packet send (%d bytes)".
int CommUDPSend(void *ref, const void *buffer, int length, int flags)
{
	int queued;
	char *packet;
	unsigned int tick;

	if (*(int *)((char *)ref + 0x90) != 4) {
		return -2;
	}
	if ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
	        *(int *)((char *)ref + 0xBC) == *(int *)((char *)ref + 0xC4)) {
		return 0;
	}
	if (length > *(int *)((char *)ref + 0xB8) - 0x10) {
		Rva007FE780Printf("CommUDP: Oversized packet send (%d bytes)\n", length);
		return -6;
	}
	if (length == 0) {
		queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
		           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
		         *(int *)((char *)ref + 0xB8);
		return queued + 1;
	}
	packet = *(char **)((char *)ref + 0xCC) + *(int *)((char *)ref + 0xC0);
	*(int *)packet = length;
	memcpy(packet + 0x10, buffer, length);
	*(unsigned int *)(packet + 4) = Rva007FEA00();
	if ((flags & 1) != 0) {
		Rva007FEBD0(g_Rva0130AF38Lock);
		*(int *)(packet + 8) = 6;
		*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
		CommUDPWrite(ref, packet);
		Rva007FECB0(g_Rva0130AF38Lock);
		return 1;
	}
	*(int *)(packet + 8) = *(int *)((char *)ref + 0xD0);
	++*(int *)((char *)ref + 0xD0);
	*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
	*(int *)((char *)ref + 0xC0) =
		(*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
		*(int *)((char *)ref + 0xBC);
	queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
	           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
	         *(int *)((char *)ref + 0xB8);
	if (queued < 0x10) {
		Rva007FEBD0(g_Rva0130AF38Lock);
		Rva00817640(ref);
		if (g_Rva0130AD08Count != 0) {
			tick = Rva007FEA00();
			while (CommUdpProcess(tick) > 0) {
			}
			g_Rva0130AD08Count = 0;
		}
		Rva007FECB0(g_Rva0130AF38Lock);
	}
    return queued > 0 ? queued : 1;
}

// ?g_Rva0130AD08Count@@3HA: matched references place it at VA 0xe0a720; also referenced as _g_Rva0130AD08Count.
int g_Rva0130AD08Count;
#pragma comment(linker, "/alternatename:_g_Rva0130AD08Count=?g_Rva0130AD08Count@@3HA")

// g_Rva0130AD10Packet: the inbound-datagram slot at VA 0xe0a728 (BFME1 VA
// 0x130ad10): the length minus eight, the sender, the kind and the connident,
// then the 0x220-byte datagram. 0x228 bytes in all, ending where the DirtySock
// lock lives; the reassembly slot below has the same shape.
char g_Rva0130AD10Packet[0x228] = { 0 };
// g_Rva0130AF60Packet: the reassembly slot at VA 0xe0a978 (BFME1 VA 0x130af60),
// same shape; ends where the connection list head lives.
char g_Rva0130AF60Packet[0x228] = { 0 };

// The CommUDP tick. Receives one pending datagram, then walks the connection
// list: routing control packets (INIT/CONN/ack/close/data/poke) at or below
// 0x10000000 through the transport, reassembling larger fragmented ones, and
// doing per-connection timeout, poke and resend maintenance. Returns the
// number of datagrams received. The frame keeps four untouched dwords (the
// 0x44 frame against 0x34 of live locals); they are padding below.
extern "C" int CommUdpProcess(unsigned int tick)
{
	int len; // -0xc, "len"
	unsigned int count; // -0x14
	void *ref; // -0x18
	void *saved; // -0x1c
	unsigned char sin[0x10]; // -0x30, "sin"
	void *sock; // -0x38
	unsigned int lastAck; // -0x3c
	int frags; // -0x40
	unsigned int dt; // -0x44

	count = 0;
	saved = 0;
	memset(sin, 0, 0x10);
	*(int *)g_Rva0130AD10Packet = -1;
	sock = 0;
	for (ref = g_Rva0130B188List; ref != 0;
	     ref = *(void **)((char *)ref + 0x78)) {
		if (*(void **)((char *)ref + 0x7c) != 0
		    && *(void **)((char *)ref + 0x7c) != sock) {
			sock = *(void **)((char *)ref + 0x7c);
			len = 0x10;
			len = Rva007FDA50((struct Rva007FD4E0Socket *)sock,
			                  g_Rva0130AD10Packet + 8, 0x220, 0,
			                  (char *)sin, &len);
			if (len > 0) {
				*(int *)g_Rva0130AD10Packet = len - 8;
				*(int *)(g_Rva0130AD10Packet + 4)
					= ((sin[8] << 8 | sin[9]) << 8 | sin[10]) << 8 | sin[11];
				if (*(int *)(g_Rva0130AD10Packet + 8) == 1) {
					Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_INIT\n");
				}
				if (*(int *)(g_Rva0130AD10Packet + 8) == 2) {
					Rva007FE780Printf("CommUdpProcess: got RAW_PACKET_CONN\n");
				}
				++count;
				break;
			}
		}
		continue;
	}
	for (ref = g_Rva0130B188List; ref != 0;
	     ref = *(void **)((char *)ref + 0x78)) {
		tick = Rva007FEA00();
		if (saved == 0
		    && sock == *(void **)((char *)ref + 0x7c)
		    && *(int *)((char *)ref + 0x90) == 3
		    && *(int *)g_Rva0130AD10Packet == 0
		    && *(int *)(g_Rva0130AD10Packet + 8) == 1
		    && *(int *)((char *)ref + 0x94)
		        == *(int *)(g_Rva0130AD10Packet + 12)) {
			saved = ref;
		}
		if (*(int *)g_Rva0130AD10Packet >= 0
		    && *(int *)((char *)ref + 0x90) != 3
		    && *(int *)((char *)ref + 0x90) != 5
		    && sock == *(void **)((char *)ref + 0x7c)
		    && Rva007FF720((const struct Rva007FF720SockAddr *)((char *)ref + 0x80),
		                   (const struct Rva007FF720SockAddr *)sin) == 0) {
			*(int *)((char *)ref + 0x60) += *(int *)g_Rva0130AD10Packet;
			++*(int *)((char *)ref + 0x68);
			if (*(int *)(g_Rva0130AD10Packet + 8) == 1
			    || *(int *)(g_Rva0130AD10Packet + 8) == 2
			    || *(int *)(g_Rva0130AD10Packet + 8) == 3) {
				CommUdpSetup(ref, g_Rva0130AD10Packet, sin);
				goto recv_done;
			} else if (*(int *)((char *)ref + 0x90) != 4) {
				goto recv_done;
			} else {
				if (*(int *)(g_Rva0130AD10Packet + 8) == 4) {
					*(int *)((char *)ref + 0xdc)
						= *(int *)(g_Rva0130AD10Packet + 4);
					Rva008186C0((struct Rva00816BF0Comm *)ref,
					            (struct Rva00816F60Message *)g_Rva0130AD10Packet);
					goto recv_done;
				}
				if (*(unsigned int *)(g_Rva0130AD10Packet + 8) > 0x10000000) {
					lastAck = *(int *)((char *)ref + 0xac);
					frags = *(unsigned int *)(g_Rva0130AD10Packet + 8) >> 28;
					*(int *)(g_Rva0130AF60Packet + 4)
						= *(int *)(g_Rva0130AD10Packet + 4);
					*(int *)(g_Rva0130AF60Packet + 8)
						= (*(int *)(g_Rva0130AD10Packet + 8) & 0x0fffffff) - frags;
					*(int *)(g_Rva0130AF60Packet + 12)
						= *(int *)(g_Rva0130AD10Packet + 12);
					*(int *)((char *)ref + 0xdc)
						= *(int *)(g_Rva0130AD10Packet + 4);
					for (; frags >= 0; frags--) {
						if (frags > 0) {
							--*(int *)g_Rva0130AD10Packet;
							*(int *)g_Rva0130AF60Packet
								= *(unsigned char *)(g_Rva0130AD10Packet + 16
								                      + *(int *)g_Rva0130AD10Packet);
						} else {
							*(int *)g_Rva0130AF60Packet = *(int *)g_Rva0130AD10Packet;
						}
						*(int *)g_Rva0130AD10Packet -= *(int *)g_Rva0130AF60Packet;
						memcpy(g_Rva0130AF60Packet + 16,
						       g_Rva0130AD10Packet + 16 + *(int *)g_Rva0130AD10Packet,
						       *(int *)g_Rva0130AF60Packet);
						Rva008186C0((struct Rva00816BF0Comm *)ref,
						            (struct Rva00816F60Message *)g_Rva0130AF60Packet);
						if (Rva008187E0((struct Rva00816BF0Comm *)ref,
						                (struct Rva00816F60Message *)g_Rva0130AF60Packet) < 0) {
							frags = 0;
						}
						if (frags > 0
						    && lastAck != *(int *)((char *)ref + 0xac)) {
							lastAck = *(int *)((char *)ref + 0xac);
						}
						++*(int *)(g_Rva0130AF60Packet + 8);
					}
					goto recv_done;
				}
				*(int *)((char *)ref + 0xdc)
					= *(int *)(g_Rva0130AD10Packet + 4);
				Rva008186C0((struct Rva00816BF0Comm *)ref,
				            (struct Rva00816F60Message *)g_Rva0130AD10Packet);
				Rva008187E0((struct Rva00816BF0Comm *)ref,
				            (struct Rva00816F60Message *)g_Rva0130AD10Packet);
			}
		recv_done:
			*(int *)g_Rva0130AD10Packet = -1;
		}
		if (*(int *)((char *)ref + 0x90) == 2
		    && tick - *(unsigned int *)((char *)ref + 0xd8) > 1000) {
			Rva00818620((struct Rva00816BF0Comm *)ref);
		}
		if (*(int *)((char *)ref + 0x90) == 4
		    && *(int *)((char *)ref + 0xc8) != *(int *)((char *)ref + 0xc0)) {
			Rva00817640(ref);
		}
		if (*(int *)((char *)ref + 0x90) == 4
		    && tick - *(unsigned int *)((char *)ref + 0xdc) > 120000
		    && tick - *(unsigned int *)((char *)ref + 0xd8) < 2000) {
			Rva007FE780Printf("CommUDP: closing connection due to timeout\n");
			Rva007FE780Printf("CommUDP: tick=%d, rtick=%d, stick=%d\n",
			                   tick,
			                   *(int *)((char *)ref + 0xdc),
			                   *(int *)((char *)ref + 0xd8));
			Rva00816F60((struct Rva00816BF0Comm *)ref);
		}
		if (*(int *)((char *)ref + 0x90) == 3
		    && *(unsigned short *)((char *)ref + 0x80) == 2
		    && tick > *(unsigned int *)((char *)ref + 0xd8) + 1000) {
			CommUdpPoke(ref);
		}
		if (*(int *)((char *)ref + 0x21c) == 0
		    && tick > *(unsigned int *)((char *)ref + 0xe0) + 250) {
			*(unsigned int *)((char *)ref + 0xe0) = tick;
			*(int *)((char *)ref + 0x21c) |= 4;
		}
		if (*(int *)((char *)ref + 0x218) == 0
		    && *(int *)((char *)ref + 0x21c) != 0) {
			++*(int *)((char *)ref + 0x218);
			if (*(void **)((char *)ref + 0x220) != 0) {
				((void (__cdecl *)(void *, int))*(void **)((char *)ref + 0x220))(
					ref, *(int *)((char *)ref + 0x21c));
			}
			*(int *)((char *)ref + 0x218) -= 1;
			*(int *)((char *)ref + 0x21c) = 0;
			tick = Rva007FEA00();
		}
		if (*(int *)((char *)ref + 0x90) == 4
		    && *(int *)((char *)ref + 0xc8) == *(int *)((char *)ref + 0xc0)) {
			dt = tick - *(unsigned int *)((char *)ref + 0xd8);
			if ((dt > 100
			     && *(int *)((char *)ref + 0xac) != *(int *)((char *)ref + 0xb0))
			    || (dt > 100
			        && *(int *)((char *)ref + 0xc0) != *(int *)((char *)ref + 0xc4))
			    || dt > 2500
			    || *(int *)((char *)ref + 0xb4) >= 0x800) {
				*(int *)((char *)ref + 0xb4) = 0;
				Rva00818AD0((struct Rva00816BF0Comm *)ref);
			}
		}
	}
	if (*(int *)g_Rva0130AD10Packet >= 0
	    && *(int *)(g_Rva0130AD10Packet + 8) == 5
	    && *(unsigned short *)sin == 2) {
		Rva007FE780Printf("CommUDP: received poke packet (from=%08x)\n",
		                   ((sin[4] << 8 | sin[5]) << 8 | sin[6]) << 8 | sin[7]);
		for (ref = g_Rva0130B188List; ref != 0;
		     ref = *(void **)((char *)ref + 0x78)) {
			if (*(int *)((char *)ref + 0x90) == 2
			    && *(unsigned short *)((char *)ref + 0x80) == 2
			    && *(int *)((char *)ref + 0x94)
			        == *(int *)(g_Rva0130AD10Packet + 12)) {
				Rva007FE780Printf("CommUdp: poke source = %08x -- forcing match\n",
				                   ((*(unsigned char *)((char *)ref + 0x84) << 8
				                     | *(unsigned char *)((char *)ref + 0x85)) << 8
				                    | *(unsigned char *)((char *)ref + 0x86)) << 8
				                   | *(unsigned char *)((char *)ref + 0x87));
				if (*(void **)((char *)ref + 0x7c) == sock) {
					Rva007FE780Printf("CommUDP: changing peer to %08x:%d due to poke (was expecting %08x:%d)\n",
					                   ((sin[4] << 8 | sin[5]) << 8 | sin[6]) << 8 | sin[7],
					                   (sin[2] << 8) | sin[3],
					                   ((*(unsigned char *)((char *)ref + 0x84) << 8
					                     | *(unsigned char *)((char *)ref + 0x85)) << 8
					                    | *(unsigned char *)((char *)ref + 0x86)) << 8
					                   | *(unsigned char *)((char *)ref + 0x87),
					                   (*(unsigned char *)((char *)ref + 0x82) << 8)
					                   | *(unsigned char *)((char *)ref + 0x83));
					memcpy((char *)ref + 0x80, sin, 0x10);
					break;
				}
			}
			continue;
		}
	}
	if (saved != 0 && *(int *)g_Rva0130AD10Packet == 0) {
		ref = saved;
		if (*(int *)((char *)ref + 0x94)
		    == *(int *)(g_Rva0130AD10Packet + 12)) {
			memcpy((char *)ref + 0x80, sin, 0x10);
			*(int *)((char *)ref + 0x90) = 4;
			CommUdpSetup(ref, g_Rva0130AD10Packet, sin);
		}
	}
	return count;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_Rva00817030=_CommUDPWrite")
#pragma comment(linker, "/alternatename:_Rva00817210Op=_CommUDPResolve")
#pragma comment(linker, "/alternatename:_Rva008173C0Op=_CommUDPSend")
#pragma comment(linker, "/alternatename:_Rva00818D90Op=_CommUdpListen")
#pragma comment(linker, "/alternatename:_Rva00819300Op=_CommUDPConnect")
