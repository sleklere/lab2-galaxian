#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Menu.h"
#include "Game.h"
#include "Scoreboard.h"
#include "FilesManager.h"
#include "Score.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    sf::Clock clock;
    Menu menu;
    Game game;
    Scoreboard scoreboard;
    FilesManager<Score> scoresFile("scores.dat");

    int numSavedScores = scoresFile.countEntries();

    int highScore = 0;


    if (numSavedScores > 0) {
        std::cout << numSavedScores << " scores" << std::endl;
        // get highscore
        for (int i = 0; i < numSavedScores; i++) {
            Score scoreEntry = scoresFile.read(i);

            std::cout << "score points: " << scoreEntry.getPoints() << std::endl;
            std::cout << "-------------" << std::endl;
            if (scoreEntry.getPoints() > highScore) {
                highScore = scoreEntry.getPoints();
            }
        }
    }

    std::cout << "high score is: " << highScore << std::endl;

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

        //float deltaTime = clock.restart().asSeconds();
        float deltaTime = 0.015f;

        if (menu.getActive()) {
            menu.update(window);
        }

        if(!menu.getActive()) {
            switch (menu.getChoice()) {
                case 1:
                    // TODO: player username
                     game.update(window, deltaTime, menu, scoresFile, highScore);
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