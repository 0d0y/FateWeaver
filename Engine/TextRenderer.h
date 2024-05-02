#pragma once
#include "BaseRenderer.h"
#include <dwrite.h>
#include <unordered_map>

#define FONT_ENUM(F) static_cast<size_t>(F)

enum class FontWeight
{
    NORMAL,
    LIGHT,
    REGULAR,
    BOLD,
    BLACK,
    END
};

enum class FontStyle
{
    NORMAL,
    OBLIQUE,
    ITALIC
};

namespace McCol
{
    class TextRenderer : public McCol::BaseRenderer
    {
    public:
        TextRenderer(GameObject* owner);
        ~TextRenderer() override;

    protected:
        ID2D1SolidColorBrush* m_Brush;
        D2D1::ColorF::Enum m_BrushColor;
        bool m_IsShowLayout;
        D2D1_RECT_F m_LayoutRect;
        float m_LayoutWidth;
        float m_LayoutHeight;

        IDWriteTextLayout* m_pDWriteTextLayout;

        std::wstring m_SrcText;
        std::wstring m_FontName;

        bool IsTextChange;

        int m_FontWeightIndex;
        std::unordered_map<int, DWRITE_FONT_WEIGHT> m_FontWeights;

        int m_FontStyleIndex;
        std::unordered_map<int, DWRITE_FONT_STYLE> m_FontStyles;

        float m_FontSize;
        UINT32 m_StartRange;
        UINT32 m_EndRange;
        

    public:
        void Initialize() override;
        void Render(D2DRender* renderer) override;

        void SetSrcText(const std::wstring_view srcText);
        void SetLayoutRect(const float& layoutWidth, const float& layoutHeight);  
        void SetBrushColor(D2D1::ColorF::Enum brushColor);        
        void ShowLayoutRect(const bool& isShowLayout);

        void SetFontName(const std::wstring_view fontName);
        void SetFontWeight(FontWeight fontWeight);
        void SetFontStyle(FontStyle fontStyle);
        void SetFontSize(const float& fontSize);
        void SetFontRange(const UINT32& start, const UINT32& end);

        void SetTextAttribute(const std::wstring_view srcText, const float& fontSize, FontWeight fontWeight);

    private:
        void CreateTextLayout(D2DRender* renderer);
        void GetBrush(D2DRender* renderer, D2D1::ColorF color);
        
    };
}

