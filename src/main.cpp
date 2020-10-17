#include "game/game.hpp"
#include <stdio.h>
#include "core/image/png_image.hpp"

int main(int argc, const char* argv[])
{
    game::Game game;
    game.initialize();
    game.loadContent();
    game.run();

    return 0;
}