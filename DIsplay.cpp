#include <iostream>

#include "Display.hpp"

Display::Display(string title, int FPS)
{

    size = sf::Vector2f(screen_w, screen_h);
    
    //window creating
    window.create(sf::VideoMode(screen_w, screen_h), title);

    //setting view
    cam.setCenter(screen_w/2.f, screen_h/2.f);
    cam.setSize(screen_w, screen_h);
    
    window.setView(cam);
    
    window.setFramerateLimit(FPS);

    sf::Event event;
    sf::Clock clock;
    
    
    //loading stuff
//    for(int i = 0; i < 20; ++i){
//        textures[i].loadFromFile(resourcePath() + "Blobs_textures.png", sf::IntRect(i*8, 0, 8, 8));
//    }
    

    // Set the Icon
//    sf::Image icon;
//    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
//        return EXIT_FAILURE;
//    }
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Display::update(){
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            cam.move(sf::Vector2f(0.f, -10.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            cam.move(sf::Vector2f(-10.f, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            cam.move(sf::Vector2f(0.f, 10.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            cam.move(sf::Vector2f(10.f, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            cam.zoom(1.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            cam.zoom(0.9f);
        }
    }
}

void Display::draw(){
    window.clear(sf::Color(0, 0, 0));

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(screen_w/world_w, screen_h/world_h));

    for (int x = 0; x < world_w; ++x) {
        for (int y = 0; y < world_h; ++y) {
            int *our_cell = worlds[world_type][x][y];

            float x_ratio = screen_w/world_w;
            float y_ratio = screen_h/world_h;

            rect.setPosition(x * x_ratio, y * y_ratio);

            rect.setFillColor(sf::Color(our_cell[1], our_cell[2], our_cell[3]));

            window.draw(rect);
        }
    }

}

void Display::show(){
    window.setView(cam);
    window.display();
}

Display display("Cells", 50);
