
#include "game.hpp"
#include "textManager.hpp"
#include "renderer.hpp"

GameState Game::currentGameState = GameState::MAIN_MENU;

Game::Game()
{
    InitWindow(windowWidth, windowHeight, "Snake");
    SetTargetFPS(targetFPS);

    TextManager::update();
    
    m_renderer = std::make_unique<Renderer>();
}

Game::~Game()
{
    TextManager::unloadAllFonts();
    CloseWindow();
}

void Game::run()
{
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(BLACK);

        m_renderer->draw();

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