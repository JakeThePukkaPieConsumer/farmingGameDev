#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP

#include <raylib.h>
#include <unordered_map>
#include <string>

class TextManager
{
public:
    static void update();

    static void loadFont(const std::string& fontName, const char* fontPath);
    static void setDefaultFont(const std::string& fontName);
    static void unloadAllFonts();
 
    static void drawCenterText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

    static void drawLeftText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

    static void drawRightText(
        const char* text, 
        int fontSize, 
        Color color, 
        int paddingX = 0, 
        int paddingY = 0, 
        const std::string& fontName = "default"
    );

private:
    static int m_screenWidth;
    static int m_screenHeight;

    static std::unordered_map<std::string, Font> m_loadedFonts;
    static std::string m_defaultFontName;

    static int getCenteredY(int fontSize, int paddingY);
    static int getTextWidth(const char* text, int fontSize, const Font& font);
    static int getRightAlignedX(const char* text, int fontSize, int paddingX, const Font& font);

    static Font& getFont(const std::string& fontName);
};

#endif // TEXTMANAGER_HPP