#include "game/game.hpp"
#include <stdio.h>

int main(int argc, const char* argv[])
{
    game::Game game;
    game.intialize();
    game.run();

    return 0;
}