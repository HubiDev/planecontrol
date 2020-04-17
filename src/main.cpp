#include "SDL2/SDL.h"
#include <stdio.h>
#include "game/game.hpp"

int main(int argc, const char *argv[])
{
    game::Game game;
    game.intialize();
    game.run();

    return 0;
}