#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"
#include "GalaxianRed.h"
#include "GalaxianCyan.h"
#include "GalaxianPink.h"
#include "GalaxianCommander.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    Player spaceship;
    Projectile projectile;
    GalaxianRed galaxianRed;
    GalaxianCyan galaxianCyan;
    GalaxianPink galaxianPink;
    GalaxianCommander galaxianCommander;
    std::vector<Projectile> projectiles;
    sf::Clock clock;

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

        float deltaTime = clock.restart().asSeconds();

        //UPDATE
        spaceship.update(deltaTime, projectiles);
        galaxianRed.update();
        galaxianCyan.update();
        galaxianPink.update();

        //DRAW
        spaceship.draw(window, sf::RenderStates::Default);
        for (auto& projectile : projectiles) {
            projectile.update();
            window.draw(projectile, sf::RenderStates::Default);
        }
        galaxianRed.draw(window, sf::RenderStates::Default);
        galaxianCyan.draw(window, sf::RenderStates::Default);
        galaxianPink.draw(window, sf::RenderStates::Default);
        galaxianCommander.draw(window, sf::RenderStates::Default);

        //DISPLAY
        window.display();
    }

    return 0;
}