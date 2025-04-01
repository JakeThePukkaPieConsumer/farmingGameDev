
#include "game.hpp"
#include "textManager.hpp"
#include "renderer.hpp"

GameState Game::currentGameState = GameState::MAIN_MENU;

Game::Game()
{
    InitWindow(windowWidth, windowHeight, "Snake");
    SetTargetFPS(targetFPS);
    /**
     * TO DO: Fix one font only being loaded;
     *      Usually the first font being called so in this case, 
     *      "test1.ttf" would be used even if "test2" is expected to be used.
     *      TextManager::loadFont("test1", "../assets/fonts/test1.ttf");
     *      TextManager::loadFont("test1", "../assets/fonts/test2.ttf");
     * 
     *      I'm not sure why this is happening.
     * */
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