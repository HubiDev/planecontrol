#include "SDL2/SDL.h"
#include <stdio.h>
#include "core/engine/game.hpp"

int main(int argc, const char *argv[])
{
    core::engine::Game game;
    game.intialize();
    game.run();

    return 0;
}