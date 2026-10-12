// ?setCaptionText@Drawable@@QAEXABVUnicodeString@@@Z
// partial score=0.9156312056737588 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 cee35b7d8c Drawable_setCaptionText.cpp / ZH Drawable.cpp semantic
// guide. Native 278064..27818E and WB CB0420 retain those branches, with
// target offsets and currently owned providers. No donor ILT casts or pins.
#include "ascii_string.h"
#include "unicode_string.h"

template <> __declspec(nothrow) int StringBase<unsigned short>::compare(const StringBase<unsigned short> &) const;

class GameFont;
class DisplayString
{
public:
    virtual void v00();
    virtual void setText(UnicodeString text);
    virtual UnicodeString getText();
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void setFont(GameFont *font);
};
class DisplayStringManager
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;
class LanguageFilter { public: void filterLine(UnicodeString &line); };
extern LanguageFilter *TheLanguageFilter;
class GlobalLanguage { public: int adjustFontSize(int size); };
extern GlobalLanguage *TheGlobalLanguageData;
class FontLibrary { public: GameFont *getFont(const AsciiString *name, float size, bool bold); };
extern FontLibrary *TheFontLibrary;
class InGameUI;
extern InGameUI *TheInGameUI;
struct CaptionUIFields
{
    char pad[0x7A0];
    int pointSize;
    bool bold;
};
class Rva00274DB6AsciiField { public: AsciiString get() const; };
class Rva00271496 { public: void rva00271496(); };
class Drawable
{
public:
    void setCaptionText(const UnicodeString &captionText);
private:
    char pad[0x344];
    DisplayString *m_caption;
};

void Drawable::setCaptionText(const UnicodeString &captionText)
{
    if (captionText.isEmpty())
    {
        ((Rva00271496 *)this)->rva00271496();
        return;
    }
    UnicodeString sanitized = captionText;
    TheLanguageFilter->filterLine(sanitized);
    if (!m_caption)
    {
        m_caption = TheDisplayStringManager->newDisplayString();
        volatile bool bold = ((CaptionUIFields *)TheInGameUI)->bold;
        GameFont *font = TheFontLibrary->getFont(&((Rva00274DB6AsciiField *)TheInGameUI)->get(),
            (float)TheGlobalLanguageData->adjustFontSize(((CaptionUIFields *)TheInGameUI)->pointSize), bold);
        m_caption->setFont(font);
        m_caption->setText(sanitized);
    }
    else
    {
        if (m_caption->getText().compare(sanitized) != 0)
            m_caption->setText(sanitized);
    }
}
