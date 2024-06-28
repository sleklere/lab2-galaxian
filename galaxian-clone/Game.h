#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "Player.h"
#include "Projectile.h"
#include "GalaxianRed.h"
#include "GalaxianCyan.h"
#include "GalaxianPink.h"
#include "GalaxianCommander.h"
#include "Grid.h"
#include "FilesManager.h"
#include "Score.h"
#include "Menu.h"
#include "GameOver.h"
#include "Screen.h"
#include "Round.h"

class Game: public Screen
{
private:
    Player player;
    Grid enemiesGrid;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> enemyProjectiles;
    sf::Clock clock;
    sf::Font font;
    sf::Text pointsText;
    sf::Text highScoreText;
    sf::Sprite lifeSprites[3];
    Score score;
    sf::Sprite _spriteFlag;
    sf::Texture _textureFlag;
    sf::Text _roundsText;
    float time; 
    int rounds;
public:
    sf::Texture generalTexture;
	Game();
	void update(sf::RenderWindow& window, float deltaTime, Menu& menu, FilesManager<Score> scoresFile, int highScore, GameOver& gameOver);
    void reset();
};

