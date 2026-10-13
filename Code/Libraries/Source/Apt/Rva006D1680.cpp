// cl: /MD /EHsc
// Native6D1680..6D17E9 RET0 361B; WB1752110 guides tracker load-state
// progression. Existing266B rva006D0C60 checks dependencies. The four-byte
// counted owner at node0 and next4, states1..5, loader callback taking
// C-string plus counted value, and object14/buffer18 come from retail.
// Explicit scopes release saved/key values before restarting/walking nodes.
// Barrier fixes store type4 before loading the callback arguments; explicit
// common restart retains the native nonzero-refcount branch target.
// Call6D1520 remains an opaque address-derived cdecl counted-value provider.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class EAStringC {void *data;public:const char*rva00620090()const;};
class Rva006E3E20Object {public:void rva006E3E20(void*,void*);};
class Rva006D0280 {public:int m_useCount;int unused4;EAStringC name8;int typeC;int argument10;void*object14;void*buffer18;~Rva006D0280();};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&o):m_object(o.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*p=m_object;if(p&&--p->m_useCount==0){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}
 Rva006D0280*m_object;
};
struct Rva006D0A30Node {Rva006D0280 *entry;Rva006D0A30Node *next;};
extern void *g_aptLoadAnimationSlot;
void Rva006D1520(Rva006D07E0Key);
class Rva006D0A30List {public:Rva006D0A30Node *head;bool rva006D0C60(Rva006D07E0Key);void rva006D1680();};
void Rva006D0A30List::rva006D1680(){
 bool again;
 do{
  again=false;
  Rva006D0A30Node *node=head;
  while(node){
   {Rva006D07E0Key key(node->entry);
   for(;;){
    Rva006D0280*p=key.m_object;
    if(p->typeC==1){p->typeC=2;((void(__cdecl*)(const char*,Rva006D07E0Key))g_aptLoadAnimationSlot)(p->name8.rva00620090(),key);node=head;}
    else if(p->typeC==2)break;
    else if(p->typeC==3){if(!rva006D0C60(key))break;p->typeC=4;_ReadWriteBarrier();again=true;((Rva006E3E20Object*)((char*)p->object14+8))->rva006E3E20(p->object14,p->buffer18);{Rva006D07E0Key saved(key);Rva006D1520(saved);}node=head;}
    else if(p->typeC==4||p->typeC==5)break;
    else {}
    node=head;
   }
   }node=node->next;
  }
 }while(again);
}

// Native6D1600..6D1671 RET4 forwards a copied counted owner to6D1520,
// then releases its by-value parameter through6D0280 and the1C-byte pool.
// BFME1 cee35b7d Rva00896540RefHolderForward supplies the ownership-pattern
// lead; the argument ABI, count at0, target teardown and pool size are retail
// facts. The original callback identity remains unknown.
void __stdcall Rva006D1600(Rva006D07E0Key key)
{
 Rva006D1520(key);
}

// Native6D1520..6D15B0 RET0 consumes the four-byte counted owner and publishes
// it to the Apt linker global E176F8 through the rowed lookup 6D1450; when the
// E176D4 flag is set, the playback cell E176EC records (name,1,3,2) through the
// rowed 6D0930 (row spelled under its Rva006CE660Vec owner). Retail materialises
// the string argument's lea between the 3 and 1 argument pushes, so the address
// is a named local.
class AptLinker {public:void *rva006D1450(Rva006D07E0Key);};
extern AptLinker *g_bfmeAptLinkerAtE176F8;
extern int g_bfmeAptFlagAtE176D4;
class Rva006CE660Vec {public:void rva006D0930(const EAStringC *,int,int,int);};
extern Rva006CE660Vec *g_aptPlaybackCheckpoints;
void Rva006D1520(Rva006D07E0Key key){
 g_bfmeAptLinkerAtE176F8->rva006D1450(key);
 if(g_bfmeAptFlagAtE176D4){const EAStringC *name8=&key.m_object->name8;((Rva006CE660Vec *)g_aptPlaybackCheckpoints)->rva006D0930(name8,1,3,2);}
}
