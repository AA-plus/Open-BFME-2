// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// Retail 0x00461DB5, 18 bytes, RET.
// Two flag bytes (+0x30, +0x31) gate a tail-jump into an unnamed member at
// 0x00461C1F (address-derived pin). Owner class name is address-derived.
// LINK: 0x461C1F is rowed as FakePathfindPortalBehaviour::rva00461C1F; bind it through a view of this object.
class FakePathfindPortalBehaviour
{
public:
 void rva00461C1F();
};
class Rva00461DB5Owner
{
public:
 void rva00461DB5();
private:
 char unknown00[0x30];
 bool flag30;
 bool flag31;
};
void Rva00461DB5Owner::rva00461DB5()
{
 if (flag31)
  return;
 if (flag30)
  return;
 ((FakePathfindPortalBehaviour *)this)->rva00461C1F();
}
