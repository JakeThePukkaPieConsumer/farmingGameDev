#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <raylib.h>
#include "textManager.hpp"

// Forward declaration to resolve circular dependency
enum class GameState;

class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    void draw();

private:
    void drawUI();
    void drawMainMenu();
    void drawGameScreen();
    void drawPauseMenu();
    void drawGameOver();
};

#endif // RENDERER_HPP