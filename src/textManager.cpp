#include "../include/textManager.hpp"
#include "../include/errorHandling.hpp"

int TextManager::screenWidth = 0;
int TextManager::screenHeight = 0;
std::unordered_map<std::string, Font> TextManager::m_loadedFonts;
std::string TextManager::m_defaultFontName = "default";

int TextManager::GetCenteredY(int fontSize, int paddingY) 
{
    return (screenHeight / 2) - (fontSize / 2) + paddingY;
}

int TextManager::GetTextWidth(const char* text, int fontSize) 
{
    return MeasureText(text, fontSize);
}

int TextManager::GetRightAlignedX(const char* text, int fontSize, int paddingX)
{
    return (screenWidth - GetTextWidth(text, fontSize)) - paddingX;
}

void TextManager::LoadTextManagerFont(const std::string& fontName, const char* fontPath) 
{
    if (m_loadedFonts.find(fontName) != m_loadedFonts.end())
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::ResourceLoading, 
            "Font already loaded: " + fontName
        );
    }

    Font newFont = LoadFont(fontPath);

    if (!newFont.texture.id) 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::ResourceLoading, 
            "Failed to load font: " + std::string(fontPath)
        );
    }

    m_loadedFonts[fontName] = newFont;

    if (m_defaultFontName == "default") 
    {
        m_defaultFontName = fontName;
    }
}

void TextManager::SetDefaultFont(const std::string& fontName) 
{
    if (m_loadedFonts.find(fontName) == m_loadedFonts.end()) 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::ResourceLoading, 
            "Cannot set default. Font not loaded: " + fontName
        );
    }

    m_defaultFontName = fontName;
}

void TextManager::UnloadAllFonts() 
{
    for (auto& fontPair : m_loadedFonts) 
    {
        UnloadFont(fontPair.second);
    }
    m_loadedFonts.clear();
    m_defaultFontName = "default";
}

Font& TextManager::GetFont(const std::string& fontName) 
{
    if (fontName == "default" || m_loadedFonts.find(fontName) == m_loadedFonts.end()) 
    {
        if (m_loadedFonts.empty()) 
        {
            static Font defaultFont = GetFontDefault();
            return defaultFont;
        }
        
        return m_loadedFonts[m_defaultFontName];
    }
    
    return m_loadedFonts[fontName];
}
void TextManager::DrawCenterText(
    const char* text, 
    int fontSize, 
    Color color, 
    int paddingX, 
    int paddingY, 
    const std::string& fontName
) 
{
    if (!text || *text == '\0') 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Attempt to draw empty text"
        );
    }
    
    if (fontSize <= 0) 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Invalid font size"
        );
    }

    Font& font = GetFont(fontName);

    int textWidth = MeasureTextEx(font, text, fontSize, 1).x;
    int centerX = (screenWidth / 2) - (textWidth / 2) + paddingX;
    int centerY = GetCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)centerX, (float)centerY}, fontSize, 1, color);
}

void TextManager::DrawLeftText(
    const char* text, 
    int fontSize, 
    Color color, 
    int paddingX, 
    int paddingY, 
    const std::string& fontName
) 
{
    if (!text || *text == '\0') 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Attempt to draw empty text"
        );
    }
    
    if (fontSize <= 0) 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Invalid font size"
        );
    }

    Font& font = GetFont(fontName);
    int centerY = GetCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)paddingX, (float)centerY}, fontSize, 1, color);
}

void TextManager::DrawRightText(
    const char* text, 
    int fontSize, 
    Color color, 
    int paddingX, 
    int paddingY, 
    const std::string& fontName
) 
{
    if (!text || *text == '\0') 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Attempt to draw empty text"
        );
    }
    
    if (fontSize <= 0) 
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::TextRendering, 
            "Invalid font size"
        );
    }

    Font& font = GetFont(fontName);
    int textWidth = MeasureTextEx(font, text, fontSize, 1).x;
    int rightX = (screenWidth - textWidth) - paddingX;
    int centerY = GetCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)rightX, (float)centerY}, fontSize, 1, color);
}

void TextManager::Update()
{
    screenWidth  = GetScreenWidth();
    screenHeight = GetScreenHeight();
}