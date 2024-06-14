#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"
#include "GalaxianRed.h"
#include "GalaxianCyan.h"
#include "GalaxianPink.h"
#include "GalaxianCommander.h"
#include "Grid.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    Player player;
    GalaxianCyan galaxianCyan;
    GalaxianRed galaxianRed1;
    GalaxianRed galaxianRed2;
    GalaxianPink galaxianPink;
    GalaxianCommander galaxianCommander;
    Grid enemiesGrid(3, 6);
    //std::vector<GalaxianRed> redEnemies = { galaxianRed1, galaxianRed2 };
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

        for (auto& projectile : enemyProjectiles)
        {
            projectile.update();

            if (projectile.remove)
            {
                continue;
            }
            
            // using matrix
            /*for (auto& row : enemiesGrid.getCells()) {
                for (auto& enemy : row) {
                    enemy.update(deltaTime, enemyProjectiles);
                    if (projectile.isCollision(player)) {
                        player.setLives(player.getLives() - 1);
                        player._isHitted = true;
                        projectile.remove = true;
                    }
                }
            }*/

            // using vector
            for (auto& enemy : enemiesGrid.getCells())
            {
                enemy.update(deltaTime, enemyProjectiles);
                if (projectile.isCollision(player))
                {
                    player.setLives(player.getLives() - 1);
                    player._isHitted = true;
                    projectile.remove = true;
                }
            }
        }

        for (auto& projectile : playerProjectiles) {  
            projectile.update();

            if (projectile.remove) {
                continue;
            }

            // matrix
            /*for (auto& row : enemiesGrid.getCells())
            {
                for (auto& enemy : row) 
                {
                    if (projectile.isCollision(enemy)) 
                    {
                        points += enemy.pointsValue;
                        projectile.remove = true;
                        enemy.remove = true;
                    }
                }
            }*/

            // 1d vector
            for (auto& enemy : enemiesGrid.getCells())
            {
                if (projectile.isCollision(enemy))
                {
                    points += enemy.pointsValue;
                    projectile.remove = true;
                    enemy.remove = true;
                }
                
            }
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

        /*for (auto& row : enemiesGrid.getCells()) {
            row.erase(
                std::remove_if(row.begin(), row.end(),
                    [](const GalaxianCyan& enemy) { return enemy.remove; }),
                row.end());
        }*/

        std::vector<GalaxianCyan>& enemySprites = enemiesGrid.getCells();

        enemySprites.erase(
            std::remove_if(enemySprites.begin(), enemySprites.end(),
                [](const GalaxianCyan& e) { return e.remove; }),
            enemySprites.end());

        //textos
        livesText.setString(std::to_string(player.getLives()));
        pointsText.setString(std::to_string(points));

        //end game
        //if (player.getLives() == 0) {
        //}

        /* ---------------------------------------------------------------------- */
        //                                 DRAW                                   //
        /* ---------------------------------------------------------------------- */

        for (const auto& projectile : enemyProjectiles) {
            window.draw(projectile, sf::RenderStates::Default);
        }

        for (const auto& projectile : playerProjectiles) {
            window.draw(projectile, sf::RenderStates::Default);
        }

        //for (const auto& row : enemiesGrid.getCells()) {
        //    for (const auto& cell : row) {
        //        cell.draw(window, sf::RenderStates::Default);
        //    }
        //}

        enemiesGrid.display(window, sf::RenderStates::Default);

        //for (const auto& galRed : redEnemies) {
        //    window.draw(galRed, sf::RenderStates::Default);
        //}

        player.draw(window, sf::RenderStates::Default);
        window.draw(livesText);
        window.draw(pointsText);

        //DISPLAY
        window.display();
    }

    return 0;
}