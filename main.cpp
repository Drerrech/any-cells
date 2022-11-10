#include <SFML/Graphics.hpp>

#include <random>
#include <iostream>

#include "Display.hpp"
#include "cells.h"


void fill_world() {
    sf::Image image;
    if (!image.loadFromFile("lolxd.jpeg"))
    {
        std::cout << "er" << std::endl;
    }

    for (int x = 0; x < world_w; ++x) {
        for (int y = 0; y < world_h; ++y) {
            worlds[0][x][y][0] = 2;

            sf::Color clr = image.getPixel(x, y);

            worlds[0][x][y][1] = clr.r;
            worlds[0][x][y][2] = clr.g;
            worlds[0][x][y][3] = clr.b;
        }
    }
}

int main() {
    fill_world();

    float dt = 0.0;
    float dt_delay = 0.0;

    sf::Clock clock;
    sf::Time elapsed = clock.restart();

    sf::RenderWindow& window = display.window;

    while (window.isOpen()) {
        //update cells
        if (dt > dt_delay) {
            dt = 0.0;

            update_world();
        }

        //update display and draw
        display.update();
        display.draw();
        display.show();

        //time
        dt += elapsed.asSeconds();
        elapsed = clock.restart();
    }
}