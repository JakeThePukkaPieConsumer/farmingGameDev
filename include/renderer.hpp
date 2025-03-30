#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <raylib.h>
#include "textManager.hpp"
#include "game.hpp"

class Renderer
{
public:
    static void draw();

private:
    void drawUI();
    void drawMainMenu();
};

#endif // RENDERER_HPP  