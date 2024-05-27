#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    /*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);*/
    Player spaceship;
     

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        spaceship.update();

        window.clear();

        window.draw(spaceship);

        window.display();
    }

    return 0;
}