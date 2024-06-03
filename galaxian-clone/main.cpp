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
    GalaxianCyan galaxianCyan;
    GalaxianRed galaxianRed;
    GalaxianPink galaxianPink;
    GalaxianCommander galaxianCommander;
    //std::vector<Enemy> enemies;
    std::vector<GalaxianCyan> galaxianCyanEnemies;
    std::vector<GalaxianRed> galaxianRedEnemies;
    std::vector<GalaxianPink> galaxianPinkEnemies;
    std::vector<GalaxianCommander> galaxianCommanderEnemies;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> enemyProjectiles;
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
    galaxianCyanEnemies.push_back(galaxianCyan);
    galaxianRedEnemies.push_back(galaxianRed);
    galaxianPinkEnemies.push_back(galaxianPink);
    galaxianCommanderEnemies.push_back(galaxianCommander);

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

        for (auto& enemy : galaxianCyanEnemies) {
            enemy.update(deltaTime, enemyProjectiles);
            enemy.updateDrawing();

            for (auto& projectile : enemyProjectiles) {
               projectile.update();
               if (projectile.isCollision(player)) {
                   player.setLives(player.getLives() - 1);
                   player._isHitted = true;
                   projectile.remove = true;
               }
               window.draw(projectile, sf::RenderStates::Default);
            }
        }

        for (auto& enemy : galaxianRedEnemies) {
            enemy.update(deltaTime, enemyProjectiles);
            enemy.updateDrawing();

            for (auto& projectile : enemyProjectiles) {
                projectile.update();
                if (projectile.isCollision(player)) {
                    player.setLives(player.getLives() - 1);
                    player._isHitted = true;
                    projectile.remove = true;
                }
                window.draw(projectile, sf::RenderStates::Default);
            }
        }

        for (auto& enemy : galaxianPinkEnemies) {
            enemy.update(deltaTime, enemyProjectiles);
            enemy.updateDrawing();

            for (auto& projectile : enemyProjectiles) {
                projectile.update();
                if (projectile.isCollision(player)) {
                    player.setLives(player.getLives() - 1);
                    player._isHitted = true;
                    projectile.remove = true;
                }
                window.draw(projectile, sf::RenderStates::Default);
            }
        }

        for (auto& enemy : galaxianCommanderEnemies) {
            enemy.update(deltaTime, enemyProjectiles);
            enemy.updateDrawing();

            for (auto& projectile : enemyProjectiles) {
                projectile.update();
                if (projectile.isCollision(player)) {
                    player.setLives(player.getLives() - 1);
                    player._isHitted = true;
                    projectile.remove = true;
                }
                window.draw(projectile, sf::RenderStates::Default);
            }
        }

        for (auto& projectile : playerProjectiles) {  
            projectile.update();
            
            for (auto& enemy : galaxianCyanEnemies) {
                if (projectile.isCollision(enemy)) {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
            }
            for (auto& enemy : galaxianRedEnemies) {
                if (projectile.isCollision(enemy)) {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
            }
            for (auto& enemy : galaxianPinkEnemies) {
                if (projectile.isCollision(enemy)) {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
            }
            for (auto& enemy : galaxianCommanderEnemies) {
                if (projectile.isCollision(enemy)) {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
            }
            window.draw(projectile, sf::RenderStates::Default);
        }


        //Borrar enemigos y proyectiles
        playerProjectiles.erase(
            std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
                [](const Projectile& p) { return p.remove; }),
            playerProjectiles.end());
        enemyProjectiles.erase(
            std::remove_if(enemyProjectiles.begin(), enemyProjectiles.end(),
                [](const Projectile& p) { return p.remove; }),
            enemyProjectiles.end());
        galaxianCyanEnemies.erase(
            std::remove_if(galaxianCyanEnemies.begin(), galaxianCyanEnemies.end(),
                [](const GalaxianCyan& e) { return e.remove; }),
            galaxianCyanEnemies.end());
        galaxianRedEnemies.erase(
            std::remove_if(galaxianRedEnemies.begin(), galaxianRedEnemies.end(),
                [](const GalaxianRed& e) { return e.remove; }),
            galaxianRedEnemies.end());
        galaxianPinkEnemies.erase(
            std::remove_if(galaxianPinkEnemies.begin(), galaxianPinkEnemies.end(),
                [](const GalaxianPink& e) { return e.remove; }),
            galaxianPinkEnemies.end());
        galaxianCommanderEnemies.erase(
            std::remove_if(galaxianCommanderEnemies.begin(), galaxianCommanderEnemies.end(),
                [](const GalaxianCommander& e) { return e.remove; }),
            galaxianCommanderEnemies.end());

        //textos
        livesText.setString(std::to_string(player.getLives()));
        pointsText.setString(std::to_string(points));

        //end game
        //if (player.getLives() == 0) {
        //}

        // DRAW
        for (auto& enemy : galaxianCyanEnemies) {
            enemy.draw(window, sf::RenderStates::Default);
        }
        for (auto& enemy : galaxianRedEnemies) {
            enemy.draw(window, sf::RenderStates::Default);
        }
        for (auto& enemy : galaxianPinkEnemies) {
            enemy.draw(window, sf::RenderStates::Default);
        }
        for (auto& enemy : galaxianCommanderEnemies) {
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