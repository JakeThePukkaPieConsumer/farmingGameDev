#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <memory>
#include "config.hpp"

class Renderer;

enum class GameState
{
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game
{
public:
    Game();
    ~Game();

    void run();

    static void changeGameState(GameState newState);
    static GameState getGameState();

private:
    static GameState currentGameState;
    std::unique_ptr<Renderer> m_renderer;
};

#endif // GAME_HPP