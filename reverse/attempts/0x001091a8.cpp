// ?rva001091A8@Rva00108660ResourceManager@@QAEXPAX@Z
// partial score=0.8 date=2026-10-11
// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// Reference lead: BFME 1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// S3GuardedGlobalTriples.cpp: three guarded manager calls and boolean list walks.
// Target wrappers 9A4A4/46 and 9A4D2/46 follow the rowed getLightPosWorld
// at 9A497/13 and end at 9A500. Native globals are DEBCD8, DEC2CC, DEC2D8;
// use their existing providers. The donor's manager order differs, so retain
// the target's volumetric/projected/opaque-manager mapping and existing names.
// Native third-manager callees are closed extents 1087BB/66 and 1087FD/69,
// with three list heads at +0C/+04/+08. Each detaches the head, then sets
// the node's byte at +04 while following +114. Node type, flag meaning and
// original method names remain unknown; these views carry address names.
// Reconstructed list walks adapt the donor's established boolean traversal
// pattern using those target-proven offsets and head-detachment stores.
struct Rva001087BBNode
{
    char m_unknown00[4];
    bool m_flag04;
    char m_unknown05[0x114-5];
    Rva001087BBNode *m_next114;
};
class W3DProjectedShadow;
class Rva00108660ResourceManager
{
    void *m_unknown00;
    Rva001087BBNode *m_head04;
    Rva001087BBNode *m_head08;
    Rva001087BBNode *m_head0C;
    char m_unknown10[0x1c - 0x10];
    Rva001087BBNode *m_head1C;
public:
    void rva001087BB();
    void rva001087FD();
    void rva001091A8(void *shadowArg);
};
void Rva00108660ResourceManager::rva001087BB()
{
    Rva001087BBNode *node=m_head0C;
    m_head0C=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
    node=m_head04;
    m_head04=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
    node=m_head08;
    m_head08=0;
    for(;node;node=node->m_next114) node->m_flag04=false;
}
void Rva00108660ResourceManager::rva001087FD()
{
    Rva001087BBNode *node=m_head0C;
    m_head0C=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
    node=m_head04;
    m_head04=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
    node=m_head08;
    m_head08=0;
    for(;node;node=node->m_next114) node->m_flag04=true;
}
class W3DVolumetricShadowManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
class W3DProjectedShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
class GenAlpha
{
public:
    void h00040601();
    void h000053B7();
};
class GenBeta
{
public:
    void h000217DD();
    void h00005592();
};
void rva0009A4A4()
{
    if(TheW3DVolumetricShadowManager)
        reinterpret_cast<GenAlpha *>(TheW3DVolumetricShadowManager)->h00040601();
    if(TheW3DProjectedShadowManager)
        reinterpret_cast<GenBeta *>(TheW3DProjectedShadowManager)->h000217DD();
    if(Rva00DEC2D8Manager) Rva00DEC2D8Manager->rva001087BB();
}
void rva0009A4D2()
{
    if(TheW3DVolumetricShadowManager)
        reinterpret_cast<GenAlpha *>(TheW3DVolumetricShadowManager)->h000053B7();
    if(TheW3DProjectedShadowManager)
        reinterpret_cast<GenBeta *>(TheW3DProjectedShadowManager)->h00005592();
    if(Rva00DEC2D8Manager) Rva00DEC2D8Manager->rva001087FD();
}

// The shadow fields 0x001091A8 reads: the type word at +0x34, the fade's
// expiry frame (+0x3C) and timings (+0x40..+0x54), and the two list
// selectors at +0x84/+0x85.
class W3DProjectedShadow
{
public:
    char m_unknown00[0x34];
    unsigned short m_type;          // +0x34
    char m_unknown36[0x3c - 0x36];
    unsigned int m_expireFrame;     // +0x3C
    int m_40;
    int m_unknown44;
    int m_48;
    int m_elapsed;                  // +0x4C, -1 when unset
    int m_total;                    // +0x50
    int m_54;
    char m_unknown58[0x84 - 0x58];
    bool m_list0C;                  // +0x84
    bool m_list1C;                  // +0x85

};
class Rva00330A37 { public: void rva00330A37(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8); };
struct ShadowList;
class Rva00109129 { public: bool rva00109129(W3DProjectedShadow *shadow, ShadowList *list); };
class Rva001091A8ClientView
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B(); virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual unsigned int getFrame();    // slot 31 (+0x7C)
};
class GameClient;
extern GameClient *TheGameClient;

// Retail 0x001091A8, 142 bytes (RET 4; caller 0x00109DA6): queue one
// shadow. A 0x0C00-type shadow whose fade has not expired restarts it from
// its stored timings (0x00330A37); any other shadow of a 0x3C61 type goes
// into the +0x0C, +0x1C or +0x08 list by its +0x84/+0x85 selectors, and
// whatever that refuses lands in the +0x04 list (0x00109129).
void Rva00108660ResourceManager::rva001091A8(void *shadowArg)
{
    W3DProjectedShadow *shadow = (W3DProjectedShadow *)shadowArg;
    if ((shadow->m_type & 0x0C00) && shadow->m_expireFrame > ((Rva001091A8ClientView *)TheGameClient)->getFrame())
    {
        int v40 = shadow->m_40;
        int elapsed = shadow->m_elapsed;
        int total = elapsed == -1 ? shadow->m_total : shadow->m_total - elapsed;
        int v48 = shadow->m_48;
        int v54 = shadow->m_54;
        ((Rva00330A37 *)shadow)->rva00330A37(0, total, v40, 0, v48, 0, total, v54);
        return;
    }
    if (shadow->m_type & 0x3C61)
    {
        Rva001087BBNode **list;
        if (shadow->m_list0C)
            list = &m_head0C;
        else if (shadow->m_list1C)
            list = &m_head1C;
        else
            list = &m_head08;
        if (((Rva00109129 *)this)->rva00109129(shadow, (ShadowList *)list))
            return;
    }
    ((Rva00109129 *)this)->rva00109129(shadow, (ShadowList *)&m_head04);
}
