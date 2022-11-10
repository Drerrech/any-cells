#ifndef Display_hpp
#define Display_hpp

#include <SFML/Graphics.hpp>
#include <string>

#include "variables.h"
#include "cells.h"

using namespace std;

struct Display //make ur own
{
    sf::RenderWindow window;
    
    sf::View cam;

    sf::Vector2f camPos;
    sf::Vector2f size;

    //sf::Texture textures[20];

    sf::Event event;
    sf::Clock clock;
    
    Display(string title, int FPS);
    void update();
    void draw();
    void show();
};

extern Display display;


#endif /* Display_hpp */
