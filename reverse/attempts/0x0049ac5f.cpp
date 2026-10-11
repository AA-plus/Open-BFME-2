// ?bfmePrivateCommand42@HordeAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z
// partial score=0.65 date=2026-10-11
// Banked near-miss body for ?bfmePrivateCommand42@HordeAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z
// retail 0x0049AC5F (53 bytes), sole blocker for HordeAIUpdatePrivateCommands.cpp (1,247 B).
//
// Recovered control flow (retail bytes, read-only decode):
//   mov eax, <funclet>; call __EH_prolog     <- EH frame this seat could not spell
//   push esi; mov esi,ecx
//   mov ecx,[esi+8]; call Object::rva0028C197   (getObject()->rva0028C197())
//   test eax,eax; je L
//     push [ebp+0xc]; mov ecx,esi; push [ebp+8]; call AIUpdateInterface::bfmePrivateCommand42
//   L: mov ecx,[ebp-0xc]; pop esi; mov fs:[0],ecx; leave; ret 8
//
// The plain C++ below reproduces the control flow and both calls but compiles to
// 34 bytes with esp-relative arguments: retail is 53 bytes with ebp-relative
// arguments and a leading `mov eax, 0x0078D644; call __EH_prolog` frame. The
// funclet at RVA 0x0078D644 is `mov eax, 0x0093D650; jmp ___CxxFrameHandler`,
// and the 36-byte scope record at 0x0093D650 carries the single action
// 0x0078D64E = `mov eax,[0x009E3B24]; and al,0xfe; mov [0x009E3B24],eax; ret`
// (the /G7 byte-narrowing of `flag &= ~1` on a byte global in .data's zero
// tail). No construct this seat tried reproduces a frame whose action is
// never invoked on the normal path: a destructible local always yields a
// ctor call and a normal-path dtor call (probe matrix: inline dtor,
// out-of-line dtor, empty inline dtor -> no frame, __try/__except,
// __try/__finally -> `push <trylevel>; push handler; call` form).
void HordeAIUpdate::bfmePrivateCommand42(Object *obj, CommandSourceType cmdSource)
{
	if (getObject()->rva0028C197())
		AIUpdateInterface::bfmePrivateCommand42(obj, cmdSource);
}
