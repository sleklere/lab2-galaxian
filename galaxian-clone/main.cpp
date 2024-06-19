#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Menu.h"
#include "Game.h"
#include "Scoreboard.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    sf::Clock clock;
    Menu menu;
    Game game;
    Scoreboard scoreboard;

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (menu.getActive()) {
            menu.update(window);
        }

        if(!menu.getActive()) {
            switch (menu.getChoice()) {
                case 1:
                     game.update(window, deltaTime);
                    break;
                case 2:
                     scoreboard.update(window, menu);
                    break;
            }
        }

        //DISPLAY
        window.display();
    }

    return 0;
}