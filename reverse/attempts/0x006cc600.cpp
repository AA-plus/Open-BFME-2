// ?Rva006CC600@@YAXPBDPAD@Z
// partial score=0.45 date=2026-10-11
// Banked structure for ?Rva006CC600@@YAXPBDPAD@Z, retail 0x006CC600 (305 B),
// sole blocker for Code/GameEngine/Source/GameClient/GUI/AptPlayer.cpp (2,315 B).
// File identity: the assert macro's file string at 0x008E8D70 is
//   C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\Apt.cpp
// and its expressions are "bInitialized" (line 802) and
//   sTarget != AptNativeString("#import") && "Please use AptPreloadFile instead of a ..."
// (0x008E8DB8, line 805). The string constant 0x008E8E24 is "#import".
//
// Recovered control flow (all RVA targets read from the retail bytes):
//   push -1; push 0x007A80D1; mov eax,fs:[0]; push eax; mov fs:[0],esp; sub esp,0xc   [/EHsc]
//   if (g_00E17700 == 0) { assert("bInitialized", "Apt.cpp", 802); if (g_00DDC01C) int3; }
//   local A = EAString(suffix)                       ctor 0x006D4C80, this = R-0x18
//   local B = EAString("#import")                    ctor 0x006D4C80, this = R-0x10
//   local A.m_flag = 1                               [R-0x14] = 1
//   bl = (A == B)                                    call 0x006D30D0 (compares the word at ptr+2)
//   B.~EAString()                                    dtor 0x006D3010 (??1Gen_uw_006d3010@@QAE@XZ, pinned)
//   if (bl) { assert("sTarget != AptNativeString(\"#import\") && ...", "Apt.cpp", 805); if (g_00DDC01C) int3; }
//   copy-construct EAString(A) on the stack          copy ctor 0x006D2FC0 (dest R-0x20)
//   g_00E176FC = 0                                   byte store
//   local C = EAString(path)                          ctor, this = R-0x10 (B's slot reused)
//   TheAptLinker->Load(<copy of A>, C)                this = [0x00E176F8], 0x006D1F80
//                                                   = ?Load@AptLinker@@QAEXABVEAStringC@@V2@@Z (ROWED)
//   C.~EAString(); A.~EAString();                     EH states 0,1,2,4 cleaned
//
// Still unknown: the DEBUG_ASSERT spelling (the two gating globals and the
// indirect call through [0x00E17734]); the class behind 0x006D4C80/0x006D3010/
// 0x006D2FC0 (the rowed pin names it ??1Gen_uw_006d3010@@QAE@XZ, so the
// destructor is pinned machinery); the member at A+4 that is set to 1; and the
// local at [R-0x14] zero-initialised before the first assert.
//
// Candidate C++ shape (not byte-verified):
//   void Rva006CC600(const char *path, char *suffix)
//   {
//       assert(bInitialized);
//       AptNativeString a(suffix);
//       AptNativeString b("#import");
//       if (a == b)
//           assert(sTarget != AptNativeString("#import") && "Please use AptPreloadFile instead of a #import");
//       g_aptFlagE176FC = 0;
//       TheAptLinker->Load(a, AptNativeString(path));
//   }
