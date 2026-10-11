// ?ConstructBigCommandPacketList@NetPacket@@SA?AV?$list@PAVNetPacket@@V?$allocator@PAVNetPacket@@@_STL@@@_STL@@PAVNetCommandRef@@@Z
// partial score=0.992481203007519 date=2026-10-11
// Banked body for the existing NetPacket.cpp home; not a standalone TU.
// At BFME2 30db2925bb the whole home was read and all 99 existing rows passed.
// Required local declarations: public static list<NetPacket*> factory;
// NetWrapperCommandMsg ctor, setters, and fields data1c/length20/offset24/
// totalLength28/chunkNumber2c/numChunks30/wrappedID34 (size38).
// Required flags: original O1/MD/NDEBUG plus EHs, STLport, bfmealloc,
// _STLP_USE_STATIC_LIB, _STLP_USE_MALLOC, _CRTIMP=, _STLP_NO_EXCEPTIONS=1,
// __PLACEMENT_VEC_NEW_INLINE. memcpy and _mbscpy keep explicit throw().
// Whole-home trial emits exactly532B: all instructions and slots exact;
// only the copy-constructor REL32 remains unadmitted. Do not assert matched.
// Base ctor4EC36C and insert5925E2 passed full recursive pin_admission proof
// with fold-proof=Code/GameEngine/Source/GameNetwork/NetPacket.cpp; those trial
// pins were reverted. Clear/base dtor were independently recognized folds.
// Copy constructor88 at594689 differs from existing short owner only in
// unresolved typed callees and distinct TU-local associative EH symbol.
// pin_admission recursively proved all those callees, then refused the EH
// DIR32 binding at+1. eh_verify reported EXACT for both copy and parent;
// any future admission must also prove every EH relocation's actual target,
// not merely rely on eh_verify's masked comparison. Never bypass the gate.
// Proven copy EH placements: text$x79D17F(18B), xdata$x952F40(36B),
// handler79D187, FuncInfo952F48, unwind cleanup79D17F -> base dtor4EC395.
// A compact standalone donor produces534B: extra xor eax before wrappedID
// load; keep the actual home context rather than claiming that trial exact.
// Clean BFME1 donor revision and path below preserve the semantic source.

// BFME 1 clean donor 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// NetPacket_ConstructBigCommandPacketList.cpp; BFME 2 adds timestamp timing.
enum NetCommandType { NETCOMMANDTYPE_ZERO = 0 };
extern Bool DoesCommandRequireACommandID(NetCommandType type);
extern UnsignedShort GenerateNextCommandID();
typedef _STL::list<NetPacket *> NetPacketList;

// ?NetPacket::ConstructBigCommandPacketList present-unmatched
NetPacketList NetPacket::ConstructBigCommandPacketList(NetCommandRef *ref)
{
	NetCommandMsg *msg = ncrCommand(ref);

	if (!(UnsignedByte)DoesCommandRequireACommandID((NetCommandType)msg->getNetCommandType()))
	{
		return NetPacketList();
	}

	UnsignedInt bufferSize = GetBufferSizeNeededForCommand(msg);
	UnsignedByte *bigPacketData = 0;

	NetPacketList packetList;

	UnsignedInt bigPacketCurrentOffset = 0;
	bigPacketData = new UnsignedByte[bufferSize];
	FillBufferWithCommand(bigPacketData, ref);

	NetWrapperCommandMsg *wrapperMsg = new NetWrapperCommandMsg;
	UnsignedInt wrapperSize = GetBufferSizeNeededForCommand(wrapperMsg);
	UnsignedInt commandSizePerPacket = MAX_PACKET_SIZE - wrapperSize;

	UnsignedInt numChunks = bufferSize / commandSizePerPacket;
	if ((bufferSize % commandSizePerPacket) > 0)
	{
		++numChunks;
	}
	UnsignedInt currentChunk = 0;

	while (currentChunk < numChunks)
	{
		NetPacket *packet = new NetPacket;

		UnsignedShort dataSizeThisPacket = (UnsignedShort)commandSizePerPacket;
		if ((bufferSize - bigPacketCurrentOffset) < dataSizeThisPacket)
		{
			dataSizeThisPacket = (UnsignedShort)(bufferSize - bigPacketCurrentOffset);
		}

		if ((UnsignedByte)DoesCommandRequireACommandID((NetCommandType)wrapperMsg->getNetCommandType()))
		{
			wrapperMsg->setID(GenerateNextCommandID());
		}
		wrapperMsg->setPlayerID(msg->getPlayerID());
		wrapperMsg->setTiming(msg->getTimestamp(), msg->getExecutionFrame());

		wrapperMsg->setChunkNumber(currentChunk);
		wrapperMsg->setNumChunks(numChunks);
		wrapperMsg->setDataOffset(bigPacketCurrentOffset);
		wrapperMsg->setData(bigPacketData + bigPacketCurrentOffset, dataSizeThisPacket);
		wrapperMsg->setTotalDataLength(bufferSize);
		wrapperMsg->setWrappedCommandID(msg->getID());

		bigPacketCurrentOffset += dataSizeThisPacket;

		NetCommandRef *newref = new NetCommandRef(wrapperMsg);
		ncrSetRelay(newref, ncrRelay(newref));

		if (packet->addCommand(newref) == false)
		{
		}

		packetList.push_back(packet);

		delete newref;
		newref = 0;

		++currentChunk;
	}

	wrapperMsg->detach();
	wrapperMsg = 0;

	delete bigPacketData;
	bigPacketData = 0;

	return packetList;
}
