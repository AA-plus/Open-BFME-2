// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// ?rva005E5BF7@Rva005CDA3D@@QAEHPAVGameMessage@@@Z, retail 0x005e5bf7, 30 bytes. Banked partial (score 0.83) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
class GameMessage;
class Rva005E5A8B { public:int rva005E5B82(GameMessage*); };
// LINK: the direct callee is rowed as RenderObjClass::Remove_Sub_Object (0x005DAA6C); called qualified.
class RenderObjClass { public:virtual int Remove_Sub_Object(RenderObjClass*); };
class Rva005CDA3D { public:int rva005E5BF7(GameMessage*);private:char prefix[8];Rva005E5A8B* delegate; };
int Rva005CDA3D::rva005E5BF7(GameMessage*msg){
 int result=((RenderObjClass*)this)->RenderObjClass::Remove_Sub_Object((RenderObjClass*)msg);
 if(result==1)return result;
 return (delegate?delegate:delegate)->rva005E5B82(msg);
}
