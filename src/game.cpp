#include "game.hpp"

Game::Game()
{
    InitWindow(windowHeight, windowWidth, "Farming Game");
    SetTargetFPS(targetFPS);
}

Game::~Game()
{
    CloseWindow();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Renderer::draw();

        EndDrawing();
    }
}

GameState Game::getGameState()
{
    return currentGameState;
}

void Game::changeGameState(GameState newState)
{
    currentGameState = newState;
}