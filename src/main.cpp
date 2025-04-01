#include "game.hpp"
#include "errorHandling.hpp"
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
        return 0;
    }
    catch (const CustomException& e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 2;
    }
}