#pragma once
// WorldBuilder animasset.cpp call graphs identify this static factory's
// GetAnim, HasAnim and Get methods at native14CF5F,14CE16 and14CF01.
// Native a* registry keys, animation virtual calls and counted ownership
// independently establish the operation. HAnimPrototypeOwner retains the
// existing four-byte ABI view; its original type spelling is not established.
class HAnimClass;
class HAnimPrototypeOwner;
class AnimationAsset
{
public:
    static HAnimClass *GetAnim(const char *name);
    static bool HasAnim(const char *name);
    static HAnimPrototypeOwner Get(const char *name);
};
