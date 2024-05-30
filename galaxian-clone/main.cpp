#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    Player spaceship;
    Projectile projectile;
    std::vector<Projectile> projectiles;

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
        spaceship.update(projectiles);

        //DRAW
        //window.draw(spaceship);
        spaceship.draw(window, sf::RenderStates::Default);
        //window.draw(projectile);
        for (auto& projectile : projectiles) {
            projectile.update();
            window.draw(projectile, sf::RenderStates::Default);
        }

        //DISPLAY
        window.display();
    }

    return 0;
}