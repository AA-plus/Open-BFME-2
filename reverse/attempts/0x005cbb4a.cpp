// ?rva005CBB4A@Rva005CBB4A@@QAEXPAXHH@Z
// partial score=1.0 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native5CBB4A..5CBC95331B RET12: three category queries construct
// the rowed5CB91E classifier, then route selected records to slot callbacks.
// WB LivingWorldThingPicker operator() is a relationship lead only.
class Rva005CBB0A {public:void *rva005CBB0A(void *,const int*);};
class Rva0020EE29 {public:void *rva0020FAB4(int,int);};
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
struct PickerWorldView {char pad[0xb0];Rva0020EE29 *lookup;};
struct PickerRecordView {char pad[0x38];void *child;};
extern "C" void *Rva003FE245Lookup(int);
unsigned Rva0052B225(unsigned);
unsigned Rva0059E0F7(unsigned);
class Rva005CBB4A;
class Rva005CB91E {public:
 Rva005CBB4A *owner;bool first,second,third;
 int rva005CB91E(int);
};
struct PickerChosenView {char pad[0x10];int key;};
class Rva005CBB4A {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual bool slot7(void*);virtual bool slot8(int);virtual void slot9();virtual void slot10(void*);virtual void slot11(void*);virtual void slot12(void*);virtual void slot13(void*);virtual void slot14(void*);virtual void slot15(void*);virtual void slot16(void*);
 void rva005CBB4A(void*,int,int);
};
void Rva005CBB4A::rva005CBB4A(void *map,int point,int mode) {
 bool first=slot8(0);bool second=slot8(1);bool third=slot8(2);
 if(first||second||third) {
  Rva005CB91E classifier;classifier.owner=this;classifier.first=first;classifier.second=second;classifier.third=third;
  PickerChosenView *chosen=(PickerChosenView*)((Rva005CBB0A*)map)->rva005CBB0A((void*)point,(const int*)&classifier);
  if(chosen) {
   int key=chosen->key;
   if(key) {
    switch(classifier.rva005CB91E(key)) {
    case 0:{PickerRecordView *record=(PickerRecordView*)Rva003FE245Lookup(key);slot15(record->child);break;}
    case 1:{void *record=Rva003FE245Lookup(key);slot12(record);break;}
    case 2:{PickerRecordView *record=(PickerRecordView*)Rva0052B225(key);slot14(record->child);break;}
    case 3:{void *record=(void*)Rva0052B225(key);slot11(record);break;}
    case 4:{PickerRecordView *record=(PickerRecordView*)Rva0059E0F7(key);slot13(record->child);break;}
    case 5:{void *record=(void*)Rva0059E0F7(key);slot10(record);break;}
    }
    return;
   }
  }
 }
 if(slot8(3)) {
  void *result=((PickerWorldView*)TheLivingWorldLogic)->lookup->rva0020FAB4(point,mode);
  if(result &&slot7(result)){slot16(result);return;}
 }
 slot9();
}
