// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Semantic donor: BFME1 ba7ddda7e8 game/GameEngine/Source/Common/FCurve.cpp.
// Target facts: 00504AB4..00504BA9 RET4/ST0, 16-byte keys, cached key+18,
// coefficients+1C..28. Both calls in the independently measured 00504BA9
// evaluator retain this receiver, supporting the existing neutral class view.
// Target changes from donor: range search through the measured 34-byte member
// at 005049A4, register-only delta and explicit 2/3 coefficient factors/order.
// Original class and search-container identities remain unknown.
// 00504BA9..00504D57 RET4/ST0 evaluates the curve: empty and single-key
// curves, then out-of-range times wrapped by whole periods and resolved per
// end through the modes at +0x00/+0x04 (WB twin 012CBF10, same FCurve.cpp
// lead). The CRT's C++ floorf inline gives retail's pop/fstp/pop cleanup.
#include <math.h>

struct Rva00504AB4Key
{
    float time, value, tangentIn, tangentOut;
};

class Rva005049A4KeyRange
{
public:
    Rva00504AB4Key *rva005049A4(const float &time) const;
    Rva00504AB4Key *begin;
    Rva00504AB4Key *end;
    char unknown08[5];
    unsigned char flag;
    char unknown0E[2];
};

class FCurve
{
public:
    float eval(float time) const;
    float rva00504BA9(float time);
private:
    int unknown00, unknown04;
    Rva005049A4KeyRange keys;
    mutable Rva00504AB4Key *volatile current;
    mutable float coefficientA, coefficientB, coefficientC, coefficientD;
};

float FCurve::eval(float time) const
{
    Rva00504AB4Key *end = keys.end;
    Rva00504AB4Key *next = current + 1;
    Rva00504AB4Key *left = current;
    if (left == end || left->time > time || next == end || time >= next->time)
    {
        next = keys.rva005049A4(time);
        if (next == end)
            next = end - 1;
        left = next - 1;
        current = left;
        float delta = next->time - left->time;
        float leftValue = left->value;
        float leftTangent = delta * left->tangentOut;
        float rightValue = next->value;
        float rightTangent = delta * next->tangentIn;
        coefficientA = (leftValue - rightValue) * 2.0f + rightTangent + leftTangent;
        coefficientB = (rightValue - leftValue) * 3.0f - leftTangent * 2.0f - rightTangent;
        coefficientC = leftTangent;
        coefficientD = leftValue;
    }
    left = current;
    float leftTime = left->time;
    time = (time - leftTime) / (next->time - leftTime);
    return (((time * coefficientA + coefficientB) * time + coefficientC) * time + coefficientD);
}

// /arch:SSE and /QIfist are refused together by this compiler. Native and
// WB both use FISTP in the ambient rounding mode; an ordinary cast uses ftol.
static __forceinline int curveRound(float value) {
    int rounded;
    __asm { fld value
            fistp rounded }
    return rounded;
}

float FCurve::rva00504BA9(float time)
{
    Rva00504AB4Key *first=keys.begin;
    Rva00504AB4Key *end=keys.end;
    if (first==end) return 0.0f;
    float firstTime=first->time;
    Rva00504AB4Key *last=end-1;
    if (first==last) {
        if (time<firstTime) {
            if (unknown00==1) return (time-firstTime)*first->tangentIn+first->value;
        } else if (time>firstTime) {
            if (unknown04==1) return (time-firstTime)*first->tangentOut+first->value;
        }
        return first->value;
    }
    float lastTime=last->time;
    if (time<firstTime || time>=lastTime) {
        float period=lastTime-firstTime;
        int cycles=curveRound(floorf((time-firstTime)/period));
        time-=cycles*period;
        if (cycles<0) {
            switch (unknown00) {
            case 0:return first->value;
            case 1:return (time+cycles*period-firstTime)*first->tangentIn+first->value;
            case 2:return eval(time);
            case 3: {
                float firstValue=first->value;
                float delta=last->value-firstValue;
                return eval(time)+cycles*delta+firstValue;
            }
            case 4:
                if (time!=firstTime && (cycles&1)) return eval(lastTime-time);
                return eval(time);
            }
        } else if (cycles>0) {
            switch (unknown04) {
            case 0:return last->value;
            case 1:return (time+(cycles-1)*period-firstTime)*last->tangentOut+last->value;
            case 2:return eval(time);
            case 3: {
                float lastValue=last->value;
                float delta=lastValue-first->value;
                return eval(time)+cycles*delta+lastValue;
            }
            case 4:
                if (time!=firstTime && (cycles&1)) return eval(lastTime-time);
                return eval(time);
            }
        }
    }
    return eval(time);
}
