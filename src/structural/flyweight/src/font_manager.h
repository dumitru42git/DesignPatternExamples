#pragma once
#include "font.h"

#include <format>
#include <string>
#include <string_view>
#include <unordered_map>

class FontManager
{
public:
    const Font* getFont(std::string_view name)
    {
        const Font* font = nullptr;

        auto it = m_fontMap.find(name);
        if (it != m_fontMap.cend())
            font = &it->second;
        else
            font = addFont(name);

        return font;
    }

private:
    const Font* addFont(std::string_view name)
    {
        std::string path  = std::format("fonts/{}", name);
        auto [it, result] = m_fontMap.try_emplace(std::string{name}, fontDescription(path));
        return &it->second;
    }

    std::string fontDescription(std::string_view path_unused)
    {
        static int                        i = 0;
        static constexpr std::string_view descriptions[3]{"bold", "italic", "won't hit this"};

        const int index = (i++) % 3;
        return std::string{descriptions[index]};
    }

private:
    struct string_hash
    {
        using hash_type      = std::hash<std::string_view>;
        using is_transparent = void;

        std::size_t operator()(const char* str) const { return hash_type{}(str); }
        std::size_t operator()(std::string_view str) const { return hash_type{}(str); }
        std::size_t operator()(std::string const& str) const { return hash_type{}(str); }
    };

    std::unordered_map<std::string, Font, string_hash, std::equal_to<>> m_fontMap;
};
