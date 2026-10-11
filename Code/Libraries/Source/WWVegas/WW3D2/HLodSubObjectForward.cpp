// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0019BA70@HLodClass@@UAEXHH@Z, retail 0x0019BA70 (87 bytes, RET 8): the
// RenderObjClass slot +0x1F8 HLodClass fills (table 0x007D6780), right after
// its Delete_Decal (+0x1F4, 0x0019BA20 in hlod.cpp) and before the protected
// Update_Cached_Bounding_Volumes. BFME 2 adds this two-argument virtual to
// RenderObjClass; HLod forwards it, like Delete_Decal, to every sub-object it
// enumerates (Get_Num_Sub_Objects +0x70, Get_Sub_Object +0x78) and releases
// each acquired reference (Delete_This in slot 0 at zero). The shared
// rendobj.h does not declare the slot yet, so this storage view spells the
// table by position; it defines no constructor and emits no vtable.
class HLodChildView
{
public:
	virtual void Delete_This(void);	// +0x00
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual int Get_Num_Sub_Objects(void) const;	// +0x70
	virtual void s029();
	virtual HLodChildView *Get_Sub_Object(int index) const;	// +0x78
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void rva0019BA70(int a, int b);	// +0x1F8
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }
private:
	int NumRefs;	// +0x04
};

class HLodClass : public HLodChildView
{
public:
	virtual void rva0019BA70(int a, int b);
};

void HLodClass::rva0019BA70(int a, int b)
{
	const int count = Get_Num_Sub_Objects();
	for (int i = 0; i < count; ++i) {
		HLodChildView *object = Get_Sub_Object(i);
		object->rva0019BA70(a, b);
		object->Release_Ref();
	}
}
