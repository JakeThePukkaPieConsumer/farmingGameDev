#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP

#include <raylib.h>
#include <unordered_map>
#include <string>

class TextManager
{
public:
    static void Update();

    static void LoadTextManagerFont(const std::string& fontName, const char* fontPath);
    static void SetDefaultFont(const std::string& fontName);
    static void UnloadAllFonts();
 
    static void DrawCenterText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

    static void DrawLeftText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

    static void DrawRightText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

private:
    static int screenWidth;
    static int screenHeight;

    static std::unordered_map<std::string, Font> m_loadedFonts;
    static std::string m_defaultFontName;

    static int GetCenteredY(int fontSize, int paddingY);
    static int GetTextWidth(const char* text, int fontSize);
    static int GetRightAlignedX(const char* text, int fontSize, int paddingX);

    static Font& GetFont(const std::string& fontName);
};

#endif // TEXTMANAGER_HPP