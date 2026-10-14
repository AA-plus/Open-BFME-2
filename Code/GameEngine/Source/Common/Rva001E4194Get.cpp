// cl: /MD
// ?rva001E4194@Locomotor@@QAE_NPAVObject@@@Z @0x001E4194 24B, RET4.
// Native 471500 passes unitAI->loco in ECX and Object* on the stack.
// WB AF0CF0 retains that receiver and reads Object+264 (native +25C), then
// the nullable component's byte+5C. The receiver is unused inside the body;
// its presence still matters to callers. Original method spelling is unknown.
class Rva001E4194Component { public: char pad00[0x5c]; bool value; };
class Object { public: char pad00[0x25c]; Rva001E4194Component *component; };
class Locomotor { public: bool rva001E4194(Object *object); };

bool Locomotor::rva001E4194(Object *object)
{
    Rva001E4194Component *component = object->component;
    if (component)
        return component->value;
    return false;
}
