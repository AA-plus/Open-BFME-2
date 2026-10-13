// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB AF8520 names LinearCampaign::restartCurrentCampaignMission (lines890..901).
// Native1ECE98..1ECEF6 RET; +C0/+C3 select completion1EB68A or restart1EB456.
// Current carryover vector is+A4; consumed vector+B4; element stride172.
// The two-way switch preserves native's early completion tail jump. The local
// view used for erase avoids retaining a separate finish-field address in EBX.
// Native1ECD19 forwards this vector in ECX; its old free owner was repaired.
#include <vector>
struct BfmeAssignRecord172 {
    ~BfmeAssignRecord172();
    unsigned char bytes[172];
};
class Rva001ECD19 : public _STL::vector<BfmeAssignRecord172> {
public:
    void rva001ECD19(BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *);
};
class Rva001EB6FE { public: void rva001EB68A(); };
class Rva001EB456 { public: void rva001EB456(int, int); };
class LinearCampaign {
public:
    void restartCurrentCampaignMission();
private:
    unsigned char unknown00[0xA4];
    Rva001ECD19 current;
    unsigned unknownB0;
    _STL::vector<BfmeAssignRecord172> previous;
    bool won, restarting, unknownC2, advanced;
};
void LinearCampaign::restartCurrentCampaignMission() {
switch(won || advanced) { case 0: {
    restarting = false;
    current.rva001ECD19(current.end(), previous.begin(), previous.end());
    _STL::vector<BfmeAssignRecord172> *history=&previous;
    history->erase(history->begin(), history->end());
    reinterpret_cast<Rva001EB456 *>(this)->rva001EB456(1, 0);
break; } default: reinterpret_cast<Rva001EB6FE *>(this)->rva001EB68A(); break; }
}
