#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Menu.h"
#include "Game.h"
#include "Scoreboard.h"
#include "FilesManager.h"
#include "Score.h"
#include "GameOver.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "Galaxian");
    window.setFramerateLimit(MAX_FPS);
    sf::Clock clock;
    Menu menu;
    Game game;
    Scoreboard scoreboard;
    GameOver gameOver;
    FilesManager<Score> scoresFile("scores.dat");

    int highScore = 0;



    while (window.isOpen()) {
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

        //para obtener el highscore
        int numSavedScores = scoresFile.countEntries();
        if (numSavedScores > 0) {
            for (int i = 0; i < numSavedScores; i++) {
                Score scoreEntry = scoresFile.read(i);

                if (scoreEntry.getPoints() > highScore) {
                    highScore = scoreEntry.getPoints();
                }
            }
        }

        //float deltaTime = clock.restart().asSeconds();
        float deltaTime = 0.015f;

        if (menu.getActive()) {
            //muestro menu
            menu.update(window, deltaTime);
        }

        if(!menu.getActive() && !gameOver.getActive()) {
            switch (menu.getChoice()) {
                case 1:
                    //muestro juego
                     game.update(window, deltaTime, menu, scoresFile, highScore, gameOver);
                    break;
                case 2:
                    //muestro scoreboard
                     scoreboard.update(window, menu, scoresFile, deltaTime);
                    break;
            }
        }

        if (gameOver.getActive() && !menu.getActive()) {
            //muestro game over
            gameOver.update(window, menu, deltaTime);
        }

        //DISPLAY
        window.display();
    }

    return 0;
}