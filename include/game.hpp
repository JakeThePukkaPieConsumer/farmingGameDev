#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include "config.hpp"
#include "renderer.hpp"

enum class GameState
{
    MAIN_MENU
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
};

#endif // GAME_HPP