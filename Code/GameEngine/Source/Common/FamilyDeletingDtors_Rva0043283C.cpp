// cl: /MD
// ??_GAptTranslator@@QAEPAXI@Z @0x00432A1F 28B: scalar deleting dtor calls rowed ??1Rva0043283C at 0x0043283C plus rowed operator delete 0x0002FD60; vtable slot 1 of 0x0083CA28.
class AptTranslator {
public:
	~AptTranslator();
};

void Rva0043283C_Delete(AptTranslator *p) { delete p; }
