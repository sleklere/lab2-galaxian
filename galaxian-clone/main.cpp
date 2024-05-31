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
    Player player;
    GalaxianRed galaxianRed;
    GalaxianCyan galaxianCyan;
    GalaxianPink galaxianPink;
    GalaxianCommander galaxianCommander;
    std::vector<Enemy> enemies;
    std::vector<Projectile> playerProjectiles;
    sf::Clock clock;
    sf::Font font;
    sf::Text livesText;
    sf::Text pointsText;
    font.loadFromFile("ARCADE_I.ttf");
    livesText.setFont(font);
    livesText.setPosition(0, 30);
    pointsText.setFont(font);
    int points = 0;

    // JUST FOR TESTING
    enemies.push_back(galaxianRed);
    enemies.push_back(galaxianCyan);
    enemies.push_back(galaxianPink);
    enemies.push_back(galaxianCommander);

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // UPDATE
        player.update(deltaTime, playerProjectiles);

        for (auto& projectile : playerProjectiles) {  
            projectile.update();
            for (auto& enemy : enemies) {
                if (projectile.isCollision(enemy)) {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
            }
            window.draw(projectile, sf::RenderStates::Default);
        }
        pointsText.setString(std::to_string(points));

        playerProjectiles.erase(
            std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
                [](const Projectile& p) { return p.remove; }),
            playerProjectiles.end());

        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [](const Enemy& e) { return e.remove; }),
            enemies.end());

        // DRAW
        for (auto& enemy : enemies) {
            enemy.draw(window, sf::RenderStates::Default);
        }
        player.draw(window, sf::RenderStates::Default);
        window.draw(livesText);
        window.draw(pointsText);

        //DISPLAY
        window.display();
    }

    return 0;
}