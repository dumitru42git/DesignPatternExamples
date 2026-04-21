#pragma once
#include "font.h"
#include "font_manager.h"

#include <print>
#include <string_view>

class Renderer
{
public:
    Renderer(FontManager& fontManager)
            : m_fontManager{fontManager}
    {
    }

    void drawText(std::string_view text, std::string_view fontName)
    {
        const Font* font = m_fontManager.getFont(fontName);
        for (auto ch : text)
        {
            std::println("Draw character {} with {}({}).", ch, fontName, font->description());
        }
        std::println();
    }

private:
    FontManager& m_fontManager;
};
