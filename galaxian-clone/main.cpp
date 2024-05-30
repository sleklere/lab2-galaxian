#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    /*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);*/
    Player spaceship;
    Projectile projectile;


    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //CMD

        //UPDATE
        spaceship.update();
        projectile.update();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            projectile.fire(spaceship.getCoordinates());
        }


        //DRAW
        window.draw(spaceship);
        window.draw(projectile);

        //DISPLAY
        window.display();
    }

    return 0;
}