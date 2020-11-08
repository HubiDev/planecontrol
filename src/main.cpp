#include "game/game.hpp"
#include <stdio.h>

int main(int argc, const char* argv[])
{
    game::Game game;
    game.initialize();
    game.loadContent();
    game.run();

    return 0;
}