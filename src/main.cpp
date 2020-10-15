#include "game/game.hpp"
#include <stdio.h>
#include "core/graphics/image_helper.hpp"

int main(int argc, const char* argv[])
{
    core::graphics::loadPng();

    game::Game game;
    game.initialize();
    game.loadContent();
    game.run();

    return 0;
}