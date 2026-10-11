// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ SphericalEmissionVelocityModuleTemplate default constructor.

namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
    ModuleTemplate() {}
    virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    virtual void unusedVirtual();

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplateBase() {}
    virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplate() {}
    virtual ~CategoryModuleTemplate() {}
};

class SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityInfo();
    virtual ~SphericalEmissionVelocityInfo();

private:
    unsigned char m_body[0x2c];
};

class SphericalEmissionVelocityModuleTemplate : public CategoryModuleTemplate<4>,
    public SphericalEmissionVelocityInfo
{
public:
    SphericalEmissionVelocityModuleTemplate();
};

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
inline SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), SphericalEmissionVelocityInfo()
{
}

}

// LINK-OWNER anchor: this unit owns ??0SphericalEmissionVelocityModuleTemplate; other units emit
// it inline, so the owner must also emit a select-any (inline) copy.
#pragma inline_depth(0)
// ?bfmeEmitSphericalEmissionVelocityModuleTemplateCtorThunk@@YAXPAVSphericalEmissionVelocityModuleTemplate@FXParticleSystem@@@Z present-unmatched
void bfmeEmitSphericalEmissionVelocityModuleTemplateCtorThunk(FXParticleSystem::SphericalEmissionVelocityModuleTemplate *p)
{
	p->SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate();
}
#pragma inline_depth()
