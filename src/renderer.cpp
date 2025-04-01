#include "renderer.hpp"
#include "game.hpp"
#include "config.hpp"

void Renderer::draw()
{
    GameState currentState = Game::getGameState();
    
    switch (currentState)
    {
        case GameState::MAIN_MENU:
            drawMainMenu();
            break;
            
        case GameState::PLAYING:
            drawGameScreen();
            break;
            
        case GameState::PAUSED:
            drawGameScreen();
            drawPauseMenu();
            break;
            
        case GameState::GAME_OVER:
            drawGameOver();
            break;
    }
    
    drawUI();
}

void Renderer::drawUI()
{
    
}

void Renderer::drawMainMenu()
{
    TextManager::drawCenterText("YayFont", 50, BLUE, 0, 100, "aqdf");
}

void Renderer::drawGameScreen()
{
}

void Renderer::drawPauseMenu()
{
}

void Renderer::drawGameOver()
{
}