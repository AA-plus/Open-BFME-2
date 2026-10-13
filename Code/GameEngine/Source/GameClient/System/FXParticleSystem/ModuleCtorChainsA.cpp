// cl: /MD
// ??0Rva003ABAC3@@QAE@PAX0@Z @0x003ABAC3 42B
// ??0Rva003ABAF3@@QAE@PAX0@Z @0x003ABAF3 42B
// ??0Rva003ABB23@@QAE@PAX0@Z @0x003ABB23 42B
// ??0Rva003ABB93@@QAE@PAX0@Z @0x003ABB93 42B
// ??0Rva003ABBCB@@QAE@PAX0@Z @0x003ABBCB 42B
// ??0Rva003ABC6E@@QAE@PAX0@Z @0x003ABC6E 49B
// ??0Rva003ABCB5@@QAE@PAX0@Z @0x003ABCB5 49B
// ??0Rva003ABE40@@QAE@PAX0@Z @0x003ABE40 49B
// ??0Rva003ABE8D@@QAE@PAX0@Z @0x003ABE8D 49B
// ??0Rva003ABDC8@@QAE@PAX0@Z @0x003ABDC8 49B
// ??0Rva003ABECC@@QAE@PAX0@Z @0x003ABECC 49B
// ??0Rva003ACDA0Module@@QAE@PAXPAVRva003AD71BTemplate@@@Z @0x003ACDA0 42B
// ??0Rva003ACE5CModule@@QAE@PAXPAVRva003AD80BTemplate@@@Z @0x003ACE5C 42B
// ??0Rva003ABB53@@QAE@PAX0@Z @0x003ABB53 42B
// ??0Rva003ABDF9@@QAE@PAX0@Z @0x003ABDF9 49B
// ??0Rva005E7420Object@@QAE@PAXPAVV3HostRva005E7420@@@Z @0x003ACE2D 42B
// ??0Rva003ACEFCModule@@QAE@PAXPAVRva003AD886Template@@@Z @0x003ACEFC 49B
// ??0Rva003AD0CAModule@@QAE@PAXPAVRva003AD9BBTemplate@@@Z @0x003AD0CA 49B
// ??0Rva003AD100Module@@QAE@PAXPAVRva003AD9F7Template@@@Z @0x003AD100 49B
// ??0Rva005E7AD0Object@@QAE@PAXPAVV3HostRva005E7AD0@@@Z @0x003AD136 49B
// ??0Rva005E76E0Object@@QAE@PAXPAVV3HostRva005E76E0@@@Z @0x003ACE8B 42B
// ??0Rva003ACDCFModule@@QAE@PAXPAVRva003AD757Template@@@Z @0x003ACDCF 42B
// ??0Rva003ACDFEModule@@QAE@PAXPAVRva003AD793Template@@@Z @0x003ACDFE 42B
// ??0Rva003ACF32Module@@QAE@PAXPAVRva003AD8C5Template@@@Z @0x003ACF32 49B
// ??0Rva003ACFCFModule@@QAE@PAXPAVRva003AD904Template@@@Z @0x003ACFCF 49B
// ??0Rva003AD005Module@@QAE@PAXPAVRva003AD940Template@@@Z @0x003AD005 49B
// ??0Rva003AD094Module@@QAE@PAXPAVRva003AD97FTemplate@@@Z @0x003AD094 49B
// ??0Rva003AD278Module@@QAE@PAXPAVRva003ADB21Template@@@Z @0x003AD278 49B
// ??0Rva003AD2B3Module@@QAE@PAXPAVRva003ADB44Template@@@Z @0x003AD2B3 49B
// ??0Rva003AD38BModule@@QAE@PAXPAVRva003ADBD0Template@@@Z @0x003AD38B 49B
//
// Particle-module constructor chains, two links each. Every body forwards its
// two stack arguments to one base constructor, then stamps the vtables of its
// three or four subobjects at +0, +0x14, +0x18 and +0x1C (Rva003ACD71Ctor.cpp
// and Rva003AD355ModuleCtor.cpp are landed members of the same family, written
// the same way). The module constructors are the ones the slot-2 template
// factories in ModuleTemplateFactorySlots.cpp call (pinned there); each calls
// one of the six intermediate constructors below, or an already-rowed one, and
// each intermediate calls a rowed module constructor. Call targets, store
// offsets and vtable addresses are read from retail; every class is
// address-named and no identity is inferred beyond the rowed callees.

extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BModuleInfoSecondBase@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE4E5@@6B@")[];
extern const void *const g_00C1C388[];
extern const void *const g_00C1C3C8[];
extern const void *const g_00C1C404[];
extern const void *const g_00C1C538[];
extern const void *const g_00C1C53C[];
extern "C" const void *const __identifier("??_7Rva003ABD20@@6BDefaultModuleSecondBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003ABD81@@6BDefaultModuleSecondBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@")[];
extern "C" const void *const __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@")[];
extern const void *const g_00C1C620[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B1C@@@")[];
extern const void *const g_00C1C6DC[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BIntermediate3AFC6FC@@@")[];
extern "C" const void *const __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BEmissionVolumeInfo4AA@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF57F@@6BLineEmissionVolumeInfo@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE4E5@@6BModuleInfoHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AE56F@@6B@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE56F@@6BModuleInfoHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AE5F9@@6B@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE5F9@@6BModuleInfoHeadBase@@@")[];
extern const void *const g_00C1CDE0[];
extern const void *const g_00C1CDF0[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003ABD20@@6B@")[];
extern const void *const g_00C1CE64[];
extern "C" const void *const __identifier("??_7Rva003ABD81@@6B@")[];
extern const void *const g_00C1CE98[];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6B@")[];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot0@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BModuleInfoHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF57F@@6BModuleInfoHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B00@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@")[];
extern const void *const g_00C1C444[];
extern "C" const void *const __identifier("??_7Rva003AE683@@6B@")[];
extern const void *const g_00C1C620[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6B@")[];
extern "C" const void *const __identifier("??_7Rva003AE683@@6BModuleInfoHeadBase_3AE683@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern const void *const g_00C1CDCC[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleHeadBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern const void *const g_00C1CF38[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6BDefaultModuleHeadBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot0@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE928@@6BModuleInfoHeadBase_3AE94E@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern const void *const g_00C1C488[];
extern "C" const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@")[];
extern const void *const g_00C1C4C8[];
extern "C" const void *const __identifier("??_7Rva003AE928@@6B@")[];
extern const void *const g_00C1C508[];
extern const void *const g_00C1C504[];
extern const void *const g_00C1CDBC[];
extern const void *const g_00C1C644[];
extern const void *const g_00C1C640[];
extern const void *const g_00C1CF28[];
extern const void *const g_00C1C6A4[];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6BDefaultModuleSecondBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6B@")[];

struct Rva0055BF4BSrc;
class RvaSmartPtr12;

namespace FXParticleSystem
{
class ParticleSystem;
template <class T> class TrackingPtr;
class DefaultModuleTemplate7;
class LightningEmissionModuleTemplate;
class PointEmissionVolumeModuleTemplate;

class Rva005FEAD0DefaultModule7
{
public:
	Rva005FEAD0DefaultModule7(TrackingPtr<ParticleSystem> &system, const DefaultModuleTemplate7 *moduleTemplate);
};

class LightningEmissionModule
{
public:
	LightningEmissionModule(TrackingPtr<ParticleSystem> &system, const LightningEmissionModuleTemplate *moduleTemplate);
};

class LightningDrawModuleTemplate;
class LightningDrawModule
{
public:
	LightningDrawModule(TrackingPtr<ParticleSystem> &system, const LightningDrawModuleTemplate *moduleTemplate);
};
}

struct Rva005648FEInput;
struct Rva005641EDInput;
struct DrawInfo2;
class Rva005634F7 { public: Rva005634F7(void *a, DrawInfo2 *b); };
class Rva003AE94E { public: Rva003AE94E(void *a, void *b); };
class Rva003AEA42 { public: Rva003AEA42(const RvaSmartPtr12 &a, int b); };
class Rva003AEF9B { public: Rva003AEF9B(const RvaSmartPtr12 &a, int b); };
class Rva003AF076 { public: Rva003AF076(const RvaSmartPtr12 &a, const Rva005648FEInput &b); };

class Rva003AE50B { public: Rva003AE50B(void *a, void *b); };
class Rva00560A1B { public: Rva00560A1B(void *a, void *b); };
class Rva003AE61F { public: Rva003AE61F(void *a, void *b); };
class Rva003ACC7C { public: Rva003ACC7C(void *a, void *b); };
class Rva0055BF4B { public: Rva0055BF4B(const RvaSmartPtr12 &a, const Rva0055BF4BSrc *b); };
class Rva003ABD20 { public: Rva003ABD20(const RvaSmartPtr12 &a, int b); };
class Rva003ABD81 { public: Rva003ABD81(const RvaSmartPtr12 &a, int b); };
struct Rva005641EDInput;
// Borrowed footprint of the existing constructor/copy owner. Its native
// fields extend through byte+0x3C; four-byte alignment gives a0x40 footprint.
// this declaration only calls that provider and emits no base lifetime code.
class Rva003AEE16
{
public:
    Rva003AEE16(const RvaSmartPtr12 &, const Rva005641EDInput &);
private:
    unsigned int m_unmodeled[0x40 / 4];
};
class Rva003ACC4B
{
public:
	Rva003ACC4B(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const FXParticleSystem::PointEmissionVolumeModuleTemplate *moduleTemplate);
};

#define STAMP(off, vtable) (*(const void **)((char *)this + (off)) = (const void *)(vtable))

// ---- intermediate constructors over rowed module constructors ----

class Rva003ABAC3 : public Rva003AE50B
{
public:
	Rva003ABAC3(void *a, void *b);
};

Rva003ABAC3::Rva003ABAC3(void *a, void *b)
	: Rva003AE50B(a, b)
{
	STAMP(0x00, g_00C1C388);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE4E5@@6B@"));
}

class Rva003ABAF3 : public Rva00560A1B
{
public:
	Rva003ABAF3(void *a, void *b);
};

Rva003ABAF3::Rva003ABAF3(void *a, void *b)
	: Rva00560A1B(a, b)
{
	STAMP(0x00, g_00C1C3C8);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE56F@@6B@"));
}

class Rva003ABB23 : public Rva003AE61F
{
public:
	Rva003ABB23(void *a, void *b);
};

Rva003ABB23::Rva003ABB23(void *a, void *b)
	: Rva003AE61F(a, b)
{
	STAMP(0x00, g_00C1C404);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE5F9@@6B@"));
}

class Rva003ABCB5 : public Rva0055BF4B
{
public:
	Rva003ABCB5(void *a, void *b);
};

Rva003ABCB5::Rva003ABCB5(void *a, void *b)
	: Rva0055BF4B(*(const RvaSmartPtr12 *)a, (const Rva0055BF4BSrc *)b)
{
	STAMP(0x00, g_00C1C53C);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, g_00C1CDE0);
}

class Rva003ABDC8 : public FXParticleSystem::Rva005FEAD0DefaultModule7
{
public:
	Rva003ABDC8(void *a, void *b);
};

Rva003ABDC8::Rva003ABDC8(void *a, void *b)
	: FXParticleSystem::Rva005FEAD0DefaultModule7(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::DefaultModuleTemplate7 *)b)
{
	STAMP(0x00, __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@"));
	STAMP(0x14, __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@"));
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@"));
}

// Native 0x003ABDF9..0x003ABE2A,49B RET8: forwards both arguments to the
// independently recovered Rva003AEE16 constructor at0x005641ED and installs
// four target vtables at+0/+0x14/+0x18/+0x20. The neighbouring ctor pattern
// is a structural guide; the target call and stores establish this relation.
// The derived class identity remains address-derived. No donor name is claimed.
class Rva003ABDF9 : public Rva003AEE16
{
public:
    Rva003ABDF9(void *a, void *b);
};

Rva003ABDF9::Rva003ABDF9(void *a, void *b)
    : Rva003AEE16(*(const RvaSmartPtr12 *)a, *(const Rva005641EDInput *)b)
{
    STAMP(0x00, g_00C1C620);
    STAMP(0x14, __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@"));
    STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
    STAMP(0x20, __identifier("??_7Rva003AEDE9@@6B@"));
}

class Rva003ABECC : public FXParticleSystem::LightningEmissionModule
{
public:
	Rva003ABECC(void *a, void *b);
};

Rva003ABECC::Rva003ABECC(void *a, void *b)
	: FXParticleSystem::LightningEmissionModule(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::LightningEmissionModuleTemplate *)b)
{
	STAMP(0x00, g_00C1C6DC);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@"));
	STAMP(0x1C, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B1C@@@"));
}

// ---- module constructors the template factories call ----

class Rva003AD71BTemplate;
class Rva003ACDA0Module : public Rva003ABAC3
{
public:
	Rva003ACDA0Module(void *a, Rva003AD71BTemplate *b);
};

Rva003ACDA0Module::Rva003ACDA0Module(void *a, Rva003AD71BTemplate *b)
	: Rva003ABAC3(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AE4E5@@6BModuleInfoHeadBase@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE4E5@@6B@"));
}

class Rva003AD757Template;
class Rva003ACDCFModule : public Rva003ABAF3
{
public:
	Rva003ACDCFModule(void *a, Rva003AD757Template *b);
};

Rva003ACDCFModule::Rva003ACDCFModule(void *a, Rva003AD757Template *b)
	: Rva003ABAF3(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AE56F@@6BModuleInfoHeadBase@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE56F@@6B@"));
}

class Rva003AD793Template;
class Rva003ACDFEModule : public Rva003ABB23
{
public:
	Rva003ACDFEModule(void *a, Rva003AD793Template *b);
};

Rva003ACDFEModule::Rva003ACDFEModule(void *a, Rva003AD793Template *b)
	: Rva003ABB23(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AE5F9@@6BModuleInfoHeadBase@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE5F9@@6B@"));
}

class Rva003AD8C5Template;
class Rva003ACF32Module : public Rva003ABCB5
{
public:
	Rva003ACF32Module(void *a, Rva003AD8C5Template *b);
};

Rva003ACF32Module::Rva003ACF32Module(void *a, Rva003AD8C5Template *b)
	: Rva003ABCB5(a, b)
{
	STAMP(0x00, g_00C1CDF0);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, g_00C1CDE0);
}

class Rva003AD904Template;
class Rva003ACFCFModule : public Rva003ABD20
{
public:
	Rva003ACFCFModule(void *a, Rva003AD904Template *b);
};

Rva003ACFCFModule::Rva003ACFCFModule(void *a, Rva003AD904Template *b)
	: Rva003ABD20(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1CE64);
	STAMP(0x14, __identifier("??_7Rva003ABD20@@6BDefaultModuleSecondBase@@@"));
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABD20@@6B@"));
}

class Rva003AD940Template;
class Rva003AD005Module : public Rva003ABD81
{
public:
	Rva003AD005Module(void *a, Rva003AD940Template *b);
};

Rva003AD005Module::Rva003AD005Module(void *a, Rva003AD940Template *b)
	: Rva003ABD81(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1CE98);
	STAMP(0x14, __identifier("??_7Rva003ABD81@@6BDefaultModuleSecondBase@@@"));
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABD81@@6B@"));
}

class Rva003AD97FTemplate;
class Rva003AD094Module : public Rva003ABDC8
{
public:
	Rva003AD094Module(void *a, Rva003AD97FTemplate *b);
};

Rva003AD094Module::Rva003AD094Module(void *a, Rva003AD97FTemplate *b)
	: Rva003ABDC8(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot0@@@"));
	STAMP(0x14, __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@"));
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@"));
}

class Rva003ADB21Template;
class Rva003AD278Module : public Rva003ACC4B
{
public:
	Rva003AD278Module(void *a, Rva003ADB21Template *b);
};

Rva003AD278Module::Rva003AD278Module(void *a, Rva003ADB21Template *b)
	: Rva003ACC4B(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::PointEmissionVolumeModuleTemplate *)b)
{
	STAMP(0x00, __identifier("??_7Rva003AF47D@@6BModuleInfoHeadBase@@@"));
	STAMP(0x14, __identifier("??_7Rva003AF47D@@6BModuleInfoSecondBase@@@"));
	STAMP(0x18, __identifier("??_7Rva003AF47D@@6BIntermediate3AFC6FC@@@"));
	STAMP(0x1C, __identifier("??_7Rva003AF47D@@6BEmissionVolumeInfo4AA@FXParticleSystem@@@"));
}

class Rva003ADB44Template;
class Rva003AD2B3Module : public Rva003ACC7C
{
public:
	Rva003AD2B3Module(void *a, Rva003ADB44Template *b);
};

Rva003AD2B3Module::Rva003AD2B3Module(void *a, Rva003ADB44Template *b)
	: Rva003ACC7C(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AF57F@@6BModuleInfoHeadBase@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@"));
	STAMP(0x1C, __identifier("??_7Rva003AF57F@@6BLineEmissionVolumeInfo@FXParticleSystem@@@"));
}

class Rva003ADBD0Template;
class Rva003AD38BModule : public Rva003ABECC
{
public:
	Rva003AD38BModule(void *a, Rva003ADBD0Template *b);
};

Rva003AD38BModule::Rva003AD38BModule(void *a, Rva003ADBD0Template *b)
	: Rva003ABECC(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B00@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@"));
	STAMP(0x1C, __identifier("??_7Rva003AF89A@@6BRva003AF8C7B1C@@@"));
}

// ---- five more intermediate constructors (same shape, rowed bases) ----

class Rva003ABB93 : public FXParticleSystem::LightningDrawModule
{
public:
	Rva003ABB93(void *a, void *b);
};

Rva003ABB93::Rva003ABB93(void *a, void *b)
	: FXParticleSystem::LightningDrawModule(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::LightningDrawModuleTemplate *)b)
{
	STAMP(0x00, g_00C1C488);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@"));
}

class Rva003ABBCB : public Rva003AE94E
{
public:
	Rva003ABBCB(void *a, void *b);
};

Rva003ABBCB::Rva003ABBCB(void *a, void *b)
	: Rva003AE94E(a, b)
{
	STAMP(0x00, g_00C1C4C8);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE928@@6B@"));
}

class Rva003ABC6E : public Rva003AEA42
{
public:
	Rva003ABC6E(void *a, void *b);
};

Rva003ABC6E::Rva003ABC6E(void *a, void *b)
	: Rva003AEA42(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1C508);
	STAMP(0x14, g_00C1C504);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, g_00C1CDBC);
}

class Rva003ABE40 : public Rva003AEF9B
{
public:
	Rva003ABE40(void *a, void *b);
};

Rva003ABE40::Rva003ABE40(void *a, void *b)
	: Rva003AEF9B(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1C644);
	STAMP(0x14, g_00C1C640);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, g_00C1CF28);
}

class Rva003ABE8D : public Rva003AF076
{
public:
	Rva003ABE8D(void *a, void *b);
};

Rva003ABE8D::Rva003ABE8D(void *a, void *b)
	: Rva003AF076(*(const RvaSmartPtr12 *)a, *(const Rva005648FEInput *)b)
{
	STAMP(0x00, g_00C1C6A4);
	STAMP(0x14, __identifier("??_7Gen005ED0D0@@6BDefaultModuleSecondBase_3AEE16@@@"));
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x20, __identifier("??_7Gen005ED0D0@@6B@"));
}

// ---- the two module constructors over 0x003ABB93 and 0x003ABBCB, under the
// names their factory call sites (0x003AD80B, 0x003AD84A) pin ----

class Rva003AD80BTemplate;
class Rva003ACE5CModule : public Rva003ABB93
{
public:
	Rva003ACE5CModule(void *a, Rva003AD80BTemplate *b);
};

Rva003ACE5CModule::Rva003ACE5CModule(void *a, Rva003AD80BTemplate *b)
	: Rva003ABB93(a, b)
{
	STAMP(0x00, __identifier("??_7Rva005EBCC0Object@@6BV3Slot0@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@"));
}

class V3HostRva005E76E0;
class Rva005E76E0Object : public Rva003ABBCB
{
public:
	Rva005E76E0Object(void *a, V3HostRva005E76E0 *b);
};

Rva005E76E0Object::Rva005E76E0Object(void *a, V3HostRva005E76E0 *b)
	: Rva003ABBCB(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AE928@@6BModuleInfoHeadBase_3AE94E@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE928@@6B@"));
}

// ---- two more intermediates over rowed bases, then the five module
// constructors their factory call sites pin ----

class Rva003ABB53 : public Rva005634F7
{
public:
	Rva003ABB53(void *a, void *b);
};

Rva003ABB53::Rva003ABB53(void *a, void *b)
	: Rva005634F7(a, (DrawInfo2 *)b)
{
	STAMP(0x00, g_00C1C444);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE683@@6B@"));
}

class V3HostRva005E7420;
class Rva005E7420Object : public Rva003ABB53
{
public:
	Rva005E7420Object(void *a, V3HostRva005E7420 *b);
};

Rva005E7420Object::Rva005E7420Object(void *a, V3HostRva005E7420 *b)
	: Rva003ABB53(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AE683@@6BModuleInfoHeadBase_3AE683@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva003AE683@@6B@"));
}

class Rva003AD886Template;
class Rva003ACEFCModule : public Rva003ABC6E
{
public:
	Rva003ACEFCModule(void *a, Rva003AD886Template *b);
};

Rva003ACEFCModule::Rva003ACEFCModule(void *a, Rva003AD886Template *b)
	: Rva003ABC6E(a, b)
{
	STAMP(0x00, g_00C1CDCC);
	STAMP(0x14, g_00C1C504);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, g_00C1CDBC);
}

class Rva003AD9BBTemplate;
class Rva003AD0CAModule : public Rva003ABDF9
{
public:
	Rva003AD0CAModule(void *a, Rva003AD9BBTemplate *b);
};

Rva003AD0CAModule::Rva003AD0CAModule(void *a, Rva003AD9BBTemplate *b)
	: Rva003ABDF9(a, b)
{
	STAMP(0x00, __identifier("??_7Rva003AEDE9@@6BDefaultModuleHeadBase_3AEE16@@@"));
	STAMP(0x14, __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@"));
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x20, __identifier("??_7Rva003AEDE9@@6B@"));
}

class Rva003AD9F7Template;
class Rva003AD100Module : public Rva003ABE40
{
public:
	Rva003AD100Module(void *a, Rva003AD9F7Template *b);
};

Rva003AD100Module::Rva003AD100Module(void *a, Rva003AD9F7Template *b)
	: Rva003ABE40(a, b)
{
	STAMP(0x00, g_00C1CF38);
	STAMP(0x14, g_00C1C640);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, g_00C1CF28);
}

class V3HostRva005E7AD0;
class Rva005E7AD0Object : public Rva003ABE8D
{
public:
	Rva005E7AD0Object(void *a, V3HostRva005E7AD0 *b);
};

Rva005E7AD0Object::Rva005E7AD0Object(void *a, V3HostRva005E7AD0 *b)
	: Rva003ABE8D(a, b)
{
	STAMP(0x00, __identifier("??_7Gen005ED0D0@@6BDefaultModuleHeadBase_3AEE16@@@"));
	STAMP(0x14, __identifier("??_7Gen005ED0D0@@6BDefaultModuleSecondBase_3AEE16@@@"));
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x20, __identifier("??_7Gen005ED0D0@@6B@"));
}
