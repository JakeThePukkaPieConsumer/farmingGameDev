#include "textManager.hpp"
#include "errorHandling.hpp"
#include "config.hpp"
#include "iostream"

int TextManager::m_screenWidth = windowWidth;
int TextManager::m_screenHeight = windowHeight;
std::unordered_map<std::string, Font> TextManager::m_loadedFonts;
std::string TextManager::m_defaultFontName = "default";

int TextManager::getCenteredY(int fontSize, int paddingY) 
{
    return (m_screenHeight / 2) - (fontSize / 2) + paddingY;
}

int TextManager::getTextWidth(const char* text, int fontSize, const Font& font) 
{
    return MeasureTextEx(font, text, fontSize, 1).x;
}

int TextManager::getRightAlignedX(const char* text, int fontSize, int paddingX, const Font& font)
{
    return (m_screenWidth - getTextWidth(text, fontSize, font)) - paddingX;
}

void TextManager::loadFont(const std::string& fontName, const char* fontPath) 
{
    if (m_loadedFonts.find(fontName) != m_loadedFonts.end())
    {
        THROW_CUSTOM_EXCEPTION(
            ErrorCategory::ResourceLoading, 
            "Font already loaded: " + fontName
        );
        return;
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

void TextManager::setDefaultFont(const std::string& fontName) 
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

void TextManager::unloadAllFonts() 
{
    for (auto& fontPair : m_loadedFonts) 
    {
        UnloadFont(fontPair.second);
    }
    m_loadedFonts.clear();
    m_defaultFontName = "default";
}

Font& TextManager::getFont(const std::string& fontName) 
{
    if (fontName != "default" && m_loadedFonts.find(fontName) != m_loadedFonts.end()) {
        std::cout << "Requested font: " << fontName << ", Found and using font: " << fontName << "\n";
        return m_loadedFonts[fontName];
    }
    
    // If we're here, either:
    // 1. "default" was explicitly requested, or
    // 2. The requested font doesn't exist in our map
    
    // Check if we have any fonts loaded at all
    if (m_loadedFonts.empty()) {
        std::cout << "No custom fonts available, using raylib default font" << "\n";
        static Font defaultFont = GetFontDefault();
        return defaultFont;
    }
    
    std::cout << "Requested font: " << fontName 
              << ", Using default font: " << m_defaultFontName << "\n";
    return m_loadedFonts[m_defaultFontName];
}

void TextManager::drawCenterText(
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

    Font& font = getFont(fontName);

    int textWidth = getTextWidth(text, fontSize, font);
    int centerX = (m_screenWidth / 2) - (textWidth / 2) + paddingX;
    int centerY = getCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)centerX, (float)centerY}, fontSize, 1, color);
}

void TextManager::drawLeftText(
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

    Font& font = getFont(fontName);
    int centerY = getCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)paddingX, (float)centerY}, fontSize, 1, color);
}

void TextManager::drawRightText(
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

    Font& font = getFont(fontName);
    int rightX = getRightAlignedX(text, fontSize, paddingX, font);
    int centerY = getCenteredY(fontSize, paddingY);

    DrawTextEx(font, text, Vector2{(float)rightX, (float)centerY}, fontSize, 1, color);
}

void TextManager::update()
{
    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();
}